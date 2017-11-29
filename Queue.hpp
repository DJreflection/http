//
// Created by zy on 17-11-29.
//

#ifndef HTTP_QUEUE_HPP
#define HTTP_QUEUE_HPP

#include <mutex>
#include <memory>
#include <condition_variable>

template <typename T>
class QueueThread {

private:
    struct Node
    {
        std::shared_ptr<T> data;
        std::unique_ptr<Node> next;
    };

    std::mutex head_mutex;
    std::unique_ptr<Node> head;
    std::mutex tail_mutex;
    Node *tail;
    std::condition_variable data_cond;

    Node* get_tail()
    {
        std::lock_guard<std::mutex> tail_lock(tail_mutex);
        return tail;
    }

    std::unique_ptr<Node> pop_head()
    {
        std::unique_ptr<Node> old_head = std::move(head);
        head=std::move(old_head->next);
        return old_head;
    }

    std::unique_ptr<Node> try_pop_head()
    {
        std::lock_guard<std::mutex> head_lock(head_mutex);

        if(head.get() == get_tail())
            return std::unique_ptr<Node>{};

        return pop_head();
    }


    std::unique_ptr<Node> try_pop_head(T& value)
    {
        std::lock_guard<std::mutex> head_lock(head_mutex);

        if(head.get() == get_tail())
            return std::unique_ptr<Node>{};

        value = std::move(head.get()->data);
        return pop_head();
    }

    std::unique_lock<std::mutex> wait_for_data()
    {
        std::unique_lock<std::mutex> head_lock(head_mutex);

        data_cond.wait(head_lock, [&]()->bool{
            return head.get() != get_tail();
        });

        return std::move(head_lock);
    }


    std::unique_ptr<Node> wait_pop_head()
    {
        std::unique_lock<std::mutex> head_lock(wait_for_data());
        return pop_head();
    }

    std::unique_ptr<Node> wait_pop_head(T& value)
    {
        std::unique_lock<std::mutex> head_lock(wait_for_data());
        value = std::move(head.get()->data);
        return pop_head();
    }

public:
    QueueThread():head(new Node), tail(head.get()) {}

    QueueThread(const QueueThread& tmp) = delete;
    QueueThread& operator=(const QueueThread& tmp) = delete;

    std::shared_ptr<T> try_pop()
    {
        std::unique_ptr<Node> old_head = try_pop_head();
        return old_head ? old_head->data : std::shared_ptr<T>{};
    }

    bool try_pop(T& value)
    {
        std::unique_ptr<Node> old_head = try_pop_head(value);
        return old_head ? true : false;
    }

    std::shared_ptr<T> wait_and_pop()
    {
        std::unique_ptr<Node> const old_head = wait_pop_head();
        return old_head->data;
    }

    void wait_and_pop(T& value)
    {
        std::unique_ptr<Node> const old_head = wait_pop_head(value);
    }

    void push(T new_value)
    {
        /*
        * make_shared()函数创建一个shared_ptr<T>的对象并返回。
        * make_shared()函数要比直接创建shared_ptr对象的方式快且高效，因为它内部仅分配一次内存，消除了shared_ptr 构造时的开销
        */
        std::shared_ptr<T> new_data(std::make_shared<T>(std::move(new_value)));

        std::unique_ptr<Node> new_node(new Node);

        Node * const new_tail = new_node.get();

        std::lock_guard <std::mutex> tail_lock(tail_mutex);
        tail->data = new_data;
        tail->next = std::move(new_node);
        tail = new_tail;

        data_cond.notify_one();
    }

    bool empty()
    {
        std::lock_guard<std::mutex> head_lock(head_mutex);
        return (head.get() == get_tail());
    }
};

#endif //HTTP_QUEUE_HPP
