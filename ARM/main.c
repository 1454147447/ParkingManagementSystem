/**********************************************************
问题描述：停车场是一个能放 n 辆车的狭长通道，只有一个大门，
汽车按到达的先后次序停放。若车场满了，车要在门外的便道上等候
，一旦有车走，则便道上第一辆车进入。当停车场中的车离开时，由
于通道窄，在它后面的车要先退出，待它走后依次进入。汽车离开
时按停放时间收费。
基本功能要求：
    1）建立三个数据结构分别是：停放队列，让路栈，等候队列
    2）输入数据模拟管理过程，数据（入或出，车号）。
***********************************************************/
#include <stdio.h>
#include "PLot.h"
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "db.h"

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#define LEDON _IO('L', 0)
#define LEDOFF _IO('L', 2)

DB database;
PE Personal;
DB database1;
int main()
{
	int fd_4 = open("/dev/led3", O_RDWR);
	int fd_3 = open("/dev/led2", O_RDWR);
	// 初始化
	s.top = -1;
	b.top = 0;
	p.rear = 0;
	p.count = 0;
	p.front = 0;
	//1. 向操作系统申请网卡功能
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == sockfd)
	{
		perror("socket");
		return -1;
	}
	db_init(&database);

	db_load(&database, "my.db");
	//2. 被动准备被客户端连接
	struct sockaddr_in serveraddr = {0};
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("0.0.0.0");
	serveraddr.sin_port = htons(8888);
	int len = sizeof(serveraddr);
	if (-1 == bind(sockfd, (struct sockaddr *)&serveraddr, len))
	{
		perror("connect");
		return -1;
	}
	listen(sockfd, 10); //开启监听

	//3. 提取一路客户端的接入
	int clientfd = accept(sockfd, NULL, NULL);
	char bufa[200] = {0};
	sprintf(bufa, "欢迎来到长江智星智能停车场！\n");
	write(clientfd, bufa, sizeof(bufa));
	char buf[200] = {0};
	int i = 0;
	
	bzero(buf,sizeof(buf));
	while (sockfd != -1)
	{
        sprintf(buf,"停车场共有%d个车位,当前停车场共有%d辆车,等候区共有%d辆车\n", MAX_STOP, s.top+1, (p.rear + MAX_PAVE - p.front)% MAX_PAVE);
	

	sleep(1);
	write(clientfd,buf,sizeof(buf));
        
	bzero(buf,sizeof(buf));
		welcome();
		//4.接收请求
		
		read(clientfd, buf, 100);
		printf("recv: %s\n", buf);
		char buf1[100] = {0};

		//5处理请求

		if (0 == strncmp(buf, "1", 1))
		{

			strcpy(buf1, "请输入即将停车的车牌号：");

			write(clientfd, buf1, sizeof(buf1));
			bzero(buf, sizeof(buf));
			read(clientfd, buf, 100);

			car_come(buf);
			bzero(buf1, sizeof(buf1));
			strcpy(buf1, "停车成功！");
			write(clientfd, buf1, sizeof(buf1));
			ioctl(fd_4, LEDON);
			sleep(3);
			ioctl(fd_4, LEDOFF);
			//continue;
		}

		if (0 == strncmp(buf, "2", 1))
		{

			strcpy(buf1, "请输入即将离开的车牌号：");
			write(clientfd, buf1, sizeof(buf1)); // 输入车牌号
			bzero(buf, sizeof(buf));
			read(clientfd, buf, 100);
			car_leave(buf);
			bzero(buf1, sizeof(buf1));
			write(clientfd, buf, sizeof(buf));
			strcpy(buf1, "请扫码缴费");
			write(clientfd, buf1, sizeof(buf1));
			//continue;
			ioctl(fd_3, LEDON);
			sleep(3);
			ioctl(fd_3, LEDOFF);
		}
		if (0 == strncmp(buf, "3", 1))
		{
			//char bufb[100] = {0};
			//bzero(bufb,sizeof(bufb));
			Display();
			continue;
		}
		if (0 == strcmp(buf, "show"))
		{
			bzero(buf, sizeof(buf));
			char buft[100] = {"请输入您的车牌号："};
			write(clientfd, buft, sizeof(buft));
			read(clientfd, buf, 100);
			Display(buf);
			bzero(buft, sizeof(buft));
			//bzero(buf1,sizeof(buf1));
			db_show(&database1, buf1);
			strcat(buft, buf1);
			write(clientfd, buft, 100);
		}
		if( 0 == strncmp(buf,"save",4))
		{
		db_save(&database,"my.db");
		printf("====%s===\n",buf);
		}
		if( 0 == strncmp(buf,"6",1))
		{
		char bufi[100] = {0};
		sprintf(bufi,"缴费成功!");
		write(clientfd,bufi,sizeof(bufi));
		}		
				
		if (0 == strncmp(buf, "4", 1))
			break;

		//5处理请求
		char a[30] = {"如需其他操作请先返回"};
		write(clientfd, a, 30);
		bzero(buf, sizeof(buf));
		read(clientfd, buf, 100);

		if (0 == strncmp(buf, "0", 1))
		{
			bzero(buf1, sizeof(buf1));
			strcpy(buf1, "返回成功！");
			write(clientfd, buf1, sizeof(buf1));
			continue;
		}
		else
		{
			char bufz[100] = {0};
			printf("您的输入有误，请重新输入\n");
			bzero(buf, sizeof(buf));
			sprintf(bufz, "您的输入有误，请重新输入\n");
			write(clientfd, bufz, sizeof(bufz));
			//  read(clientfd, buf, 100);

			continue;
		}
		//6. 反馈结果
		write(clientfd, buf1, sizeof(buf1));
	}
	//7. 关闭通道，归还网卡
	close(sockfd);
	close(clientfd);

	return 0;
}
