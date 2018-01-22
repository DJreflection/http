## HttpServer

该HttpServer仅限交流学习使用；

写该项目目的是用来学习Linuxt套接字编程，以及Linux下多线程编程和面向过程的思想；

**项目进行第一次重构**

重构原因如下:

+ 代码混乱，代码风格很差
+ 没有进行模块化编程，代码耦合度太高

**重构各个模块的功能如下**

+ Buffer.class 作为缓存区；在用户态实现一个读取和写入的缓存区，进行健壮的IO操作


+ Configure.class 用于读取配置文件
+ EventLoop.class 一个基于回调的事件触发器（内部维护一个epoll），监听描述符状态，进行相应的操作
+ HttpServer.class 负责消息处理，以及消息回复，不涉及底层网络
+ HttpRequest.class 处理到来的消息，解析请求头，以及读取消息体
+ HttpResponse.class 用于处理Response的消息头的构建
+ Log.class 日志系统; 通过不定长可变参数以及宏不定项参数，将所以要目的输入构建为一条消息
+ Queue.class 消息队列；内部为一个细化锁的链表，写入和读出是可以同时进行的
+ TcpConnection.class 维护Tcp连接时的状态，以及记录连接信息
+ TcpServer.class 负责Tcp网络连接，以及传输数据，内部有多个EvenLoop.class来监听文件描述符
+ Time.class 负责得到当前时间

之前代码在master分支，当前分支为重构分支，完成后合并

------------

#### HttpServer架构

HttpServer

![](http://oqcswuw8q.bkt.clouddn.com/HttpServer.png)



HttpServer获得一个请求，并回复的过程；

+ 1.HttpServer以一个TcpServer服务器监听一个PORT

+ 2.连接到来时TcpServer获得一个连接描述符，并将该描述符分配给TcpServer中管理的EventLoop中

+ 3.将该连接描述符加入EventLoop中，通过epoll来监听描述符是否可读

+ 4.描述符可读时，调用读取函数，将数据读取到一个buffer中，并进行部分解析

+ 5.判断是否解析完全（HttpRequest请求头是否完整），如果不完全，就继续监听，即重复第三步

+ 6.完全解析后，将判断请求是否合法，以及是否有对应的文件；

+ 7.将HttpResponse头部和请求的文件写入buffer缓存，并在epoll中改变监听状态，判断是否可写

+ 8.描述符可写时，将该buffer中的缓存数据写入，并判断是否写入完全，如果没有继续监听，循环这一步

+ 9.写入完成时，根据之前的HttpRequest头部判断是否为长链接；如果是长链接，改变监听状态，重复第四步；如果短链接，断开连接，析构一系列数据结构。

  ​