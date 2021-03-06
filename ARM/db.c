#include "db.h"
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int db_load(DB *database, const char *dbfile)
{
	//1. 只读方式打开文件，没有就创建
	int fd = open(dbfile, O_RDONLY|O_CREAT, 0666);
	if(-1 == fd)
	{
		perror("open");
		return -1;
	}
	
	//2. 读出文件内容到数据库内存（dbfile---->database）
	read(fd, database, sizeof(DB));
	
	//3. 关闭文件
	close(fd);
}

int db_save(DB *database, const char *dbfile)
{
	//1. 只写方式打开文件
	int fd = open(dbfile, O_WRONLY, 0666);
	if(-1 == fd)
	{
		perror("open");
		return -1;
	}
	
	//2. 将数据库内存写入文件（database---->dbfile）
	write(fd, database, sizeof(DB));
	
	//3. 关闭文件
	close(fd);
}

int db_init(DB *database)
{
	
	database->num = 0;
	return 0;
}

/*int db_insert(DB *database, const char *car)
{
	if(MAXSIZE == database->num)
		return DBFULL;

	strcpy(database->users[database->num].car,car);
	database->num++;

	return 0;
}*/

int db_insert1(PE *Personal, const char *carnum)
{
	if(MAXSIZE == Personal->num)
		return DBFULL;

	strcpy(Personal->Person[Personal->num].carnum,carnum);
	Personal->num++;

	return 0;
}

int db_delete(DB *database, const char *car)
{
	//find it
	int i = 0;
        for(;i<database->num; i++)
        {
                if( 0 == strcmp(database->users[i].car, car))
                         
                    {
                       //delete
			//move and cover
			while(i < database->num-1)
			{
				database->users[i] = database->users[i+1];
				i++;
			}
			database->num--;
			return 0;
                }
        }
	
	return -1;
}






void db_show(DB *database, char *buf)
{
	
	printf("车牌号\t\t\t停车时间\t\t当前所需金额\n");
	int i = 0;
	
	for(;i<database->num; i++)
	
	{
		char bufx[100] = {0};
		sprintf(bufx, "%s\t\n", database->users[i].car);
		printf("%s\t\n",bufx);
         	strcat(buf, bufx);
	}

	
	
	printf("\n");
}

