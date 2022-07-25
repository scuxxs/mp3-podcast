#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include"lyric.h"
#include"music.h"
#include<Windows.h>
#include"list.h"
#include <time.h>
#include <mmsystem.h>
#include<io.h>
#define PATH "D:\\music\\"  
#pragma comment(lib, "winmm.lib")

/*
* 裁剪歌词
*/
int cut_lyric(char* lyr_src, char* lyr_done[], char* str)
{
	int i = 0;
	lyr_done[i] = strtok(lyr_src, str);
	while (lyr_done[i] != NULL)
	{
		i++;
		lyr_done[i] = strtok(NULL, str);
	}
	return i;
}

/*
* 读取lrc文件
*/
char* read_file(struct media* p)
{
	FILE* fp = NULL;
	char* buf;
	unsigned long int file_length;
	char pathname[100];
	int len = 0;
	char* name;
	sprintf(pathname, "%s%s", PATH, p->name);
	GetShortPathName(pathname, pathname, 50);
	name = strtok(pathname, ".");
	strcat(name, ".lrc");
	fp = fopen(name, "rb");
	if (fp == NULL) {
		printf("null\n");
		return NULL;
	}
	fseek(fp, 0, SEEK_END);//计算文件长度
	file_length = ftell(fp);
	rewind(fp);//指针移回开头
	buf = malloc(file_length);
	fread(buf, 1, file_length, fp);
	fclose(fp);
	return buf;
}

/*
* 创建歌词链表
*/
LRC* link_insert(LRC* head, LRC* p_new)
{
	LRC* pb;
	if (head == NULL)//空链表时
	{
		head = p_new;
		head->next = p_new;
		head->front = p_new;
	}
	else//有一个或以上节点时
	{
		pb = head->next;
		head->next = p_new;
		p_new->next = pb;
		p_new->front = head;
		pb->front = p_new;
	}
	return head;
}

/*
* 根据总时长找到对应歌曲
*/
LRC* link_search(LRC* head, int sTime)
{
	LRC* p_mov = head;
	if (head == NULL)
	{
		return NULL;
	}
	else
	{
		while (p_mov->next != head)
		{
			if (p_mov->m_time == sTime)
			{
				return p_mov;
				break;
			}
			p_mov = p_mov->next;
		}
		if (p_mov->m_time == sTime)
		{
			return p_mov;
		}
		return NULL;
	}
}
