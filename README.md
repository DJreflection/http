## HttpServer

该HttpServer只是用来学习linux网络编程，以及学习面向对象编程的思想

**项目进行第一次重构**

重构原因如下:

+ 代码混乱
+ 没有进行模块化编程，代码耦合度太高

**重构各个模块的功能如下**

+ Configure.class 负责读取配置文件
+ HttpServer.class 负责消息处理，以及消息回复，不涉及底层网络
+ Log.class 日志系统，内部为一个细化锁的链表，写入和读出是可以同时进行的
+ TcpConnection.class 维护Tcp连接时的状态
+ TcpServer.class 负责网络连接，以及传输数据，多线程方面
+ Time.class 负责得到当前时间

之前代码在master分支，当前分支为重构分支，完成后合并

