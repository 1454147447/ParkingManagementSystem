# Parking-management-system
本系统基于QT、ARM开发板、对接百度AI

1.1 项目目的
  创建一个简单的智能停车管理系统，能够停入车辆和取出车辆以及查询车辆停入停车场的状态并且计算车辆离开时收费情况。
1.2 项目意义
  实现停车场智能抬杆和智能收费系统，使停车场自动记录车辆停入停车场的车位时间和收费信息。
1.3 项目目标
  做一个QT客户端界面操作Linux系统下编写的服务器只想相应的操作，再将QT客户端获取的车牌号停入停车场写进数据库系统中实现进入停车场计时收费并离开停车场，数据库里记录车辆停车详细信息，最后完善Linux下服务器编写的代码。

2.1 项目需求概述
  实现停车场智能抬杆和智能收费系统，使停车场自动记录车辆停入停车场的车位时间和收费信息。   
2.2 详细需求描述
  1.问题描述：停车场是一个能放 n 辆车的狭长通道，只有一个大门，汽车按到达的先后次序停放。若车场满了，车要在门外的便道上等候，一旦有车走，则便道上第一辆车进入。当停车场中的车离开时，由于通道窄，在它后面的车要先退出，待它走后依次进入。汽车离开时按停放时间收费。
  2.基本功能要求： 
    1）建立三个数据结构分别是：停放队列，让路栈，等候队列。
    2）输入数据模拟管理过程，数据（入或出，车号）。
2.3 项目架构设计
  在Qt中设计好用户界面，连接数据库服务器，实现停车系统的各方面功能；调用百度AI与Qt界面进行网络交互，实现车牌识别的功能；设备扩展板与数据库和Qt进行对接，用LED灯模拟停车取车
2.4 项目UI设计
  主界面设计对应我们项目的名称《智能停车管理系统》，子界面根据数据库的需求以及车牌识别的需求进行设计，共有八个按钮用来控制数据库服务器的功能，显示屏用来显示数据库反馈回来的信息，文本框用来接收车牌识别返回的车牌号然后发送给数据库进行存档。
  