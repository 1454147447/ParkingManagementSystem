//
// Created by PC-Saw on 2018/12/17.
//

#include "PLot.h"
#include<string.h>
#include"db.h"
extern DB database;
extern PE Personal;
extern DB database1;
int db_insert(DB *database,  char *car)
{
	char *car1 = car;
	if(MAXSIZE == database->num)
		return DBFULL;
	

	strcpy(database->users[database->num].car,car);
	database->num++;
	

	return 0;
}
void stop_to_pave()                         // 车停入便道
{
    // 判断队满
    if (p.count > 0 && (p.front == (p.rear + 1) % MAX_PAVE))
    {
        printf ("便道已满，请下次再来\n");
    }
    else
    {
        strcpy(p.Pave[p.rear].plate, C);    // 车进入便道
        p.rear = (p.rear + 1) % MAX_PAVE;   // 队尾指示器加1
        p.count++;                          // 计数器加1
        printf ("牌照为%s的汽车停入便道上的%d的位置\n", C, p.rear);
    }
}

void car_come(char *buf)                             // 车停入停车位
{
	
    
    char *bufx = buf;
    if (s.top >= MAX_STOP - 1)              // 如果停车位已满，停入便道
    {
        stop_to_pave();                     // 停入便道
    }
    else
    {
	
        s.top++;                            // 停车位栈顶指针加1
        time_t t1;
        long int t = time(&t1);             // 记录进入停车场的时间
        char* t2;
	char bufz[100] = {0};
	char buf1[10] = {};
        t2 = ctime (&t1);                   // 将当前时间转换为字符串
        s.Stop[s.top].timeIn = t;

        strcpy(s.Stop[s.top].plate, bufx);     // 将车牌号登记
	    
	  printf ("牌照为%s的汽车停入停车位的%d车位, 当前时间:%s\n", bufx, s.top + 1, t2);
	  //sprintf(bufz,"牌照为%s的汽车停入停车位的%d车位, 当前时间:%s\n", bufx, (char)s.top + 1, t2);

	  db_insert1(&Personal,bufx);
	
    }

    
}

void stop_to_buff(char *buf)                         // 车进入让路栈
{	
	char *bufy = buf;
	//char  *bufa[200] = {0}; 
    // 停车位栈压入临时栈，为需要出栈的车辆让出道
    while (s.top >= 0)
    {
        if (0 == strcmp(s.Stop[s.top].plate, bufy))
        {
            break;
        }

        // 让出的车进入让路栈
        strcpy(b.Help[b.top++].plate, s.Stop[s.top].plate);
        printf ("牌照为%s的汽车暂时退出停车场\n", s.Stop[s.top--].plate);
    }

    // 如果停车位中的车都让了道，说明停车位中无车辆需要出行
    if (s.top < 0)
    {
        printf ("停车位上无此车消息\n");
    }
    else
    {
        printf ("牌照为%s的汽车从停车场开走\n", s.Stop[s.top].plate);
        time_t t1;
        long int t = time (&t1);
        c.timeOut = t;                        // 标记离开停车场的时间
        char* t2;
        t2 = ctime (&t1);                   // 获取当前时间
        printf ("离开时间%s\n需付%d元\n", t2, (Price * (c.timeOut - s.Stop[s.top].timeIn))/10 );
	bzero(bufy,sizeof(bufy));	
	sprintf(bufy,"牌照为%s的汽车从停车场开走\n离开时间%s\n需付%d元\n",s.Stop[s.top].plate, t2, (Price * (c.timeOut - s.Stop[s.top].timeIn))/10);
        s.top--;
    }

    // 将让路栈中的车辆信息压入停车位栈
    while (b.top > 0)
    {
        strcpy(s.Stop[++s.top].plate, b.Help[--b.top].plate);
        printf ("牌照为%s的汽车停回停车位%d车位\n", b.Help[b.top].plate, s.top);
    }

    // 从便道中 -> 停车位
    while (s.top < MAX_STOP-1)
    {
        if (0 == p.count)               // 判断队列是否为空
        {
            break;
        }   // 不为空，将便道中优先级高的车停入停车位
        else
        {
            strcpy(s.Stop[++s.top].plate, p.Pave[p.front].plate);
            printf ("牌照为%s的汽车从便道中进入停车位的%d车位\n", p.Pave[p.front].plate, s.top);
            p.front = (p.front + 1) % MAX_PAVE;
            p.count--;
        }
    }
}

void car_leave(char *buf)                        // 车离开
{
	char *bufx = buf ;
    if (s.top < 0)                      // 判断停车位是否有车辆信息
    {
        printf ("车位已空，无车辆信息！\n");
    }
    else
    {	db_delete(&database,bufx);
        stop_to_buff(bufx);
	//db_delete(&database,bufx);
    }
	//db_delete(&database,bufx);
}

void Display(char *buf)
{
	char *bufx = buf;
	char *bufy = buf;
	
	char buft[300] = {0};
    int i = s.top;
    if (-1 == i)
    {
        printf ("停车场为空\n");
    }
    time_t t1;
    long int t = time(&t1);             // 标记显示时的时间
    while (i != -1)
    {
       // printf ("%s\t\t%ld秒\t\t\t%ld元\n", bufx, t - s.Stop[i].timeIn, Price * (t - s.Stop[i].timeIn) / 10);
	sprintf(buft,"%s\t\t\t%ld秒\t\t\t%ld元\n", bufx, t - s.Stop[i].timeIn, Price * (t - s.Stop[i].timeIn) / 10);
	
	//db_insert(&database,buft);
        i--;
	
	//s.Stop[i].plate
    }
       db_insert(&database1,buft);
}

void welcome()
{
    printf ("\t*******************目前停车场状况***********************\n");
    printf ("\t停车场共有%d个车位,当前停车场共有%d辆车,等候区共有%d辆车\n", MAX_STOP, s.top+1, (p.rear + MAX_PAVE - p.front)
                                                                       % MAX_PAVE);
    printf ("\t********************************************************\n");
    printf ("\t---------------Welcome to our Car Parking---------------\n");
    printf ("\t*                     1.Parking                        *\n");
    printf ("\t*                     2.leaving                        *\n");
    printf ("\t*                     3.situation                      *\n");
    printf ("\t*                     4.exit                           *\n");
    printf ("\t*                     5.show                           *\n");
    printf ("\t--------------------------------------------------------\n");
}


