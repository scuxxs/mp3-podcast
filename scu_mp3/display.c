#include "menu.h"
#include "music.h"
#include"lyric.h"
#include"list.h"
#include <time.h>


/*
*   展示歌曲信息
*/
void display(struct media* p)
{
	int i = 0;
	printf("哼，听着，这就是正在播放音乐的信息:\n");
	printf("序号：%d\n名称：%s", p->num, p->name);
	for (i = 0; p->comment[i][0] != '\0'; i++)
	{
	}
	printf("\n");
	printf("评论区：\n");
	commentRead(p);
	//system("pause");
}

/*
* 从文件中读取写过的评论
*/
void commentRead(struct media* p)
{
	FILE* fp = NULL;
	char str[100][100] = { "" };
	char name[50];
	strncpy(name, p->name, strlen(p->name) - 4);
	name[strlen(p->name) - 4] = '\0';
	char commenttxt[100];
	sprintf(commenttxt, "D://music//musicComment//%s.txt", name);
	fp = fopen(commenttxt, "rb");
	if (fp == NULL)
	{
		printf(" ");
	}
	else if (fp != NULL)
	{
		for (int i = 0; i < 100; i++)
		{
			fgets(str[i], 100, fp);
			if (strcmp(str[i], "") != 0)
			{
				char strcpy[100];
				printf("\r\r");
				strncpy(strcpy, str[i], 21);
				strcpy[21] = '\0';
				printf(">>%s\n", strcpy);

			}
			else
				break;
		}
		fclose(fp);
	}
	
}

/*
* 书写评论
*/
struct media* commentWrite(struct media* p)
{
	time_t time_comment = time(NULL);
	FILE* fp = NULL;
	char com[100];
	char name[50];
	strncpy(name, p->name,strlen(p->name)-4);
	name[strlen(p->name) - 4] = '\0';
	sprintf(com, "D://music//musicComment//%s.txt", name);

	char timeStr[32];
	char comment[1000];
	printf(">>请输入你的评论:(评论后将关闭歌曲）\n");
	gets(comment);
	strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localtime(&time_comment));
	if ((fp = fopen(com, "a+")) != NULL)
	{
		fprintf(fp, "[%s]-[%s]-[%s] :>   ",timeStr, "FATAL", __FILE__);
		fprintf(fp,"\n");
		fprintf(fp, "\t");
		fprintf(fp, comment);
		fprintf(fp,"\n");
		printf("评论成功！φ(゜▽゜*)♪\n");
		log_record(3, "LINE:  %d   successfully add comment to %s  ", __LINE__ - 2, p->name);
		fclose(fp);
		system("pause");
	}
	return p;
}

