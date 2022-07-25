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
* �ü����
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
* ��ȡlrc�ļ�
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
	fseek(fp, 0, SEEK_END);//�����ļ�����
	file_length = ftell(fp);
	rewind(fp);//ָ���ƻؿ�ͷ
	buf = malloc(file_length);
	fread(buf, 1, file_length, fp);
	fclose(fp);
	return buf;
}

/*
* �����������
*/
LRC* link_insert(LRC* head, LRC* p_new)
{
	LRC* pb;
	if (head == NULL)//������ʱ
	{
		head = p_new;
		head->next = p_new;
		head->front = p_new;
	}
	else//��һ�������Ͻڵ�ʱ
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
* ������ʱ���ҵ���Ӧ����
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
