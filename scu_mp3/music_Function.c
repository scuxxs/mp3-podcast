#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include"music.h"
#include<Windows.h>
#include"menu.h"
#include <mmsystem.h>
#include"lyric.h"
#include<io.h>
#include"list.h"
#include <time.h>
#include <stdarg.h>
#define PATH "D:\\music\\"  
#pragma comment(lib, "winmm.lib")
#define LENGTH 5000

enum { FATAL, ERROR_, WARNING, INFO, DEBUG };
HANDLE hOutput, hOutBuf, hSet;                   //控制台屏幕缓冲区句柄
COORD coord;
DWORD bytes = 0;
char PrintfBuff[LENGTH];
HANDLE  hOut[2];                                 //两个缓冲区的句柄
HANDLE handle_out;

extern int logocolor;


int st = 0;
int is_Fir = 0;
int is_End = 0;
int min = 0;
int sec = 0;
int mode = 1;
int BuffSwitch;

/*去除歌曲名字中多余空格*/
void delSpace(char* str)
{
	char* str_c = str;
	int i, j = 0;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] != ' ' )
			str_c[j++] = str[i];
	}
	str_c[j] = '\0';
	str = str_c;
}

/*
* 展示选择歌曲的菜单
*/
void print_choice() {
	setlogocolor();
	printf("\t\t                        _ __   _____ ___  _  _________       _____ ______     \n");
	printf("\t\t                       / __ \\/  __  / /__\\ \\/  ___/ / \\ \\   / ____/__  __/      \n");
	printf("\t\t ________________     / /_/ / /  / / /   | / /   / /__| |  /_/_ _   / /     ________________   \n");
	printf("\t\t/___/___/___/___/    / ____/ /__/ / /___/ / /__   /___| | ____/ /  / /     /___/___/___/___/      \n");
	printf("\t\t                    /_/   /______/_/___/_/_/___/ /    | |/____ /  /_/          \n");
	printf("\n\n");
	printf("\t\t\t\t\t╔═════════════════════════════════════╗\n");
	printf("\t\t\t\t\t║                                     ║\n");
	printf("\t\t\t\t\t║ *a.切换播放模式       *b.我的歌单   ║\n");
	printf("\t\t\t\t\t║                                     ║\n");
	printf("\t\t\t\t\t║ *c.选曲播放           *d.搜索曲目   ║\n");
	printf("\t\t\t\t\t║                                     ║\n");
	printf("\t\t\t\t\t║ *e.返回菜单                         ║\n");
	printf("\t\t\t\t\t╚═════════════════════════════════════╝\n");
	switch (mode)
	{
	case 1:printf("当前播放模式：单曲循环\n"); break;
	case 2:printf("当前播放模式：顺序播放\n"); break;
	case 3:printf("当前播放模式：随机播放\n"); break;
	}
}

/*
* 打印歌曲列表
*/
int Print_musicList(struct media* head)
{
	log_record(3, "LINE:  %d   Successfully initial all songs", __LINE__ - 2);
	system("CLS");
	struct media* p1;
	p1 = head->next;
	int i = 0;
	printf("\t  ╔══════════════════════════════════════════════════════\n");
	while (p1 != NULL)
	{
		printf("\t  ║   %d. %s\n", p1->num, p1->name);
		memset(p1->comment, '\0', sizeof(p1->comment));
		p1->commentnum = 0;
		p1 = p1->next;
		i++;
	}
	return i;

}

/*
* 创建歌曲列表的链表
*/
struct media* CreatHead()
{
	struct media* head, * p, * q;
	head = (struct media*)malloc(sizeof(struct media));
	long long Handle;
	struct _finddata_t FileInfo;

	if ((Handle = _findfirst("D:\\music\\*.mp3", &FileInfo)) == -1LL)
	{
		printf("\n\t没有找到匹配的项目\n\t请将.mp3文件放入D:\\music\\文件夹中,再重新选曲播放\n");

		system("pause");
		head = NULL;
		log_record(ERROR_, "LINE:  Fail to initiall songs", __LINE__ - 3);
		return head;
	}
	else
	{
		int i = 1;
		p = (struct media*)malloc(sizeof(struct media));
		if (p != NULL) {
			q = head;
			p->num = i;
			strcpy(p->name, FileInfo.name);
			q->next = p;
			q = p;
		}


		while (_findnext(Handle, &FileInfo) == 0)
		{
			i++;
			p = (struct media*)malloc(sizeof(struct media));
			if (p != NULL) {
				p->num = i; 
				strcpy(p->name, FileInfo.name);
				q->next = p;
				q = p;
			}

		}
		p->next = NULL;
		_findclose(Handle);
		
	}
	return head;
}

/*
* 打印播放模式选择栏的菜单
*/
void display_mode() {
	system("CLS");
	setlogocolor();
	printf("\n\n\n");
	printf("\t\t                        _ __   _____ ___  _  _________       _____ ______     \n");
	printf("\t\t                       / __ \\/  __  / /__\\ \\/  ___/ / \\ \\   / ____/__  __/      \n");
	printf("\t\t ________________     / /_/ / /  / / /   | / /   / /__| |  /_/_ _   / /     ________________   \n");
	printf("\t\t/___/___/___/___/    / ____/ /__/ / /___/ / /__   /___| | ____/ /  / /     /___/___/___/___/      \n");
	printf("\t\t                    /_/   /______/_/___/_/_/___/ /    | |/____ /  /_/          \n");
	printf("\n\n");
	printf("\t\t\t\t\t╔══════════════════════════════════════╗\n");
	printf("\t\t\t\t\t║                                      ║\n");
	printf("\t\t\t\t\t║  *1.循环播放         *2.顺序播放     ║\n");
	printf("\t\t\t\t\t║                                      ║\n");
	printf("\t\t\t\t\t║             *3.随机播放              ║\n");
	printf("\t\t\t\t\t╚══════════════════════════════════════╝\n");

}

void switch_mode() {
	display_mode();
	mode = _getch() - 48;

}


/*
* 根据序号选择歌曲
*/
struct media* Choose_Song(struct media* HEAD, struct media* P, int num, int max)
{
	if (HEAD == NULL)
		return HEAD;
	else
	{
		struct media* p;
		p = HEAD->next;
		do
		{
			printf("\n\t请输入歌曲序号: ");
			scanf("%d", &num);
			while (getchar() != '\n')continue;//清除缓冲区，如果用户输入字符将会死循环
			if (!(num > 0 && num <= max))
			{
				log_record(ERROR_, "LINE:  %d   input error", __LINE__ - 3);
				printf("\t请输入歌曲对应序号1~ %d ！\n", max);
				fflush(stdin);
				
			}
		} while (!(num > 0 && num <= max));

		while (p->num != num) p = p->next;
		if (P != NULL)  close_Song(P);
		return p;
	}

}

/*
* 播放歌曲
*/
struct media* play(struct meida* head, struct media* p, int max)
{
	char cmd[100];
	char pathname[100];
	sprintf(pathname, "%s%s", PATH, p->name);
	GetShortPathName(pathname, pathname, 50);
	sprintf(cmd, "open %s", pathname);
	mciSendString(cmd, NULL, 0, NULL);
	sprintf(cmd, "play %s", pathname);
	mciSendString(cmd, NULL, 0, NULL);
	log_record(3, "LINE:  %d   play music named  %s  ", __LINE__ - 2, p->name);
	log_record(3, "LINE:  %d   read lyric named  %s  ", __LINE__ - 2, p->name);
	st = 1;
	p=operation(head, p, max);
	return p;
}

/*
* 双缓冲初始化
*/
void DoubleBuffInitial()
{
	//创建新的控制台缓冲区
	hOutBuf = CreateConsoleScreenBuffer(
		GENERIC_WRITE,           //定义进程可以往缓冲区写数据
		FILE_SHARE_WRITE,        //定义缓冲区可共享写权限
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);
	hOutput = CreateConsoleScreenBuffer(
		GENERIC_WRITE,           //定义进程可以往缓冲区写数据
		FILE_SHARE_WRITE,        //定义缓冲区可共享写权限
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);
	hOut[0] = hOutBuf;
	hOut[1] = hOutput;

	//隐藏两个缓冲区的光标
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = sizeof(cursor);

	SetConsoleCursorInfo(hOutput, &cursor);
	SetConsoleCursorInfo(hOutBuf, &cursor);
}

/*
* 打印音乐播放栏菜单
*/
void music_face() {
	setlogocolor();
	system("CLS");
	printf("\t\t                        _ __   _____ ___  _  _________       _____ ______     \n");
	printf("\t\t                       / __ \\/  __  / /__\\ \\/  ___/ / \\ \\   / ____/__  __/      \n");
	printf("\t\t ________________     / /_/ / /  / / /   | / /   / /__| |  /_/_ _   / /     ________________   \n");
	printf("\t\t/___/___/___/___/    / ____/ /__/ / /___/ / /__   /___| | ____/ /  / /     /___/___/___/___/      \n");
	printf("\t\t                    /_/   /______/_/___/_/_/___/ /    | |/____ /  /_/          \n");
	printf("\n\n");
	COORD  point1 = { 45 ,  9 };
	HANDLE  HOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(HOutput, point1);
	printf(" \t\t\t\t************************************************\n");
	COORD  point2 = { 45 ,  10};
	SetConsoleCursorPosition(HOutput, point2);
	printf(" \t\t\t\t*                                              *\n");
	COORD  point3 = { 45 ,  11 };
	SetConsoleCursorPosition(HOutput, point3);
	printf(" \t\t\t\t*  ▲ space:播放/暂停      ▲  ESC:写评论      *\n");
	COORD  point4 = { 45 ,  12 };
	SetConsoleCursorPosition(HOutput, point4);
	printf(" \t\t\t\t*                                              *\n");
	COORD  point5 = { 45 ,  13 };
	SetConsoleCursorPosition(HOutput, point5);
	printf(" \t\t\t\t*  ▲ ←:快退              ▲  →:快进         *\n");
	COORD  point6 = { 45 ,  14 };
	SetConsoleCursorPosition(HOutput, point6);
	printf(" \t\t\t\t*                                              *\n");
	COORD  point7 = { 45 ,  15 };
	SetConsoleCursorPosition(HOutput, point7);
	printf(" \t\t\t\t*  ▲ ↑:上一首            ▲  ↓:下一首       *\n");
	COORD  point8 = { 45 ,  16 };
	SetConsoleCursorPosition(HOutput, point8);
	printf(" \t\t\t\t*                                              *\n");
	COORD  point9 = { 45 ,  17 };
	SetConsoleCursorPosition(HOutput, point9);
	printf(" \t\t\t\t*  ▲ + :音量减            ▲  - :音量加       *\n");
	COORD  point10 = { 45 ,  18 };
	SetConsoleCursorPosition(HOutput, point10);
	printf(" \t\t\t\t*                                              *\n");
	COORD  point11 = { 45 ,  19 };
	SetConsoleCursorPosition(HOutput, point11);
	printf(" \t\t\t\t*              ▲TAB:退出播放                  *\n");
	COORD  point12 = { 45 ,  20 };
	SetConsoleCursorPosition(HOutput, point12);
	printf(" \t\t\t\t*                                              *\n");
	COORD  point13 = { 45 ,  21 };
	SetConsoleCursorPosition(HOutput, point13);
	printf(" \t\t\t\t************************************************\n");
	COORD  point14 = { 45 ,  22 };
	SetConsoleCursorPosition(HOutput, point14);

}

/*
* 获取歌曲播放总时长
*/
int getSongTime(struct media* p) {
		int time;
		char len[100];
		char pathname[100];
		char cmd[100];

		sprintf(pathname, "%s%s", PATH, p->name);
		GetShortPathName(pathname, pathname, 50);//获取短名
		sprintf(cmd, "status %s length", pathname);
		mciSendString(cmd, len, sizeof(len), NULL);//获取时间，单位为毫秒
		time = atoi(len) /1000;
		return time;
	
}

/*
* 展示进度条，时间等信息
*/
void timeDisplay(struct media* p)
{
	if (p == NULL) return;
	int time = getSongTime(p);
	min = time / 60;
	sec = time % 60;
	printf("\r%*c\r", 60, ' ');
	COORD  point = { 73 ,  24 }; 
	HANDLE  HOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(HOutput, point);
	printf("%c", '|');
	for (int i = 0; i < 37; i++) {
		printf("%c", '-');
	}
	COORD  point2 = { 111 ,  24 };
	SetConsoleCursorPosition(HOutput, point2);
	printf("%c", '|');
	COORD  point3 = { 112 ,  24 };
	SetConsoleCursorPosition(HOutput, point3);
	printf("%02d:%02d", min, sec);
	printf("\n");


}

/*
* 关闭歌曲
*/
void close_Song(struct media* p)
{

	char cmd[100];
	char pathname[100];

	sprintf(pathname, "%s%s", PATH, p->name);
	GetShortPathName(pathname, pathname, 50);
	sprintf(cmd, "stop %s", pathname);
	mciSendString(cmd, NULL, 0, NULL);
	sprintf(cmd, "close %s", pathname);
	mciSendString(cmd, NULL, 0, NULL);
	log_record(INFO, "LINE:  %d   close music named  %s  ", __LINE__ - 2, p -> name);
	st = 0;
}

/*
* 播放上一首歌曲
*/
struct media* Last_Play(struct media* head, struct media* p, int maxNum)//上一曲
{

	if (p != head->next) {
		close_Song(p);//关闭当前歌曲
		//system("CLS");
		struct media* q;
		q = (struct media*)malloc(sizeof(struct media));
		q = head->next;
		while (q->next != p) q = q->next;//将指针指向上一曲
		p = q;
		is_Fir = 0;
		music_face();
		timeDisplay(p);
		play(head, p, maxNum);
	}
	else
	{
		close_Song(p);
		while (p->next != NULL)
			p = p -> next;
		music_face();
		timeDisplay(p);
		play(head, p, maxNum);
		/*if (is_Fir == 1) {
			
		}
		is_Fir = 1;
		printf("\n");
		printf("\t\t\t当前已是第一首！即将返回上一菜单！");
		Sleep(1000);
		printf("\r");
		printf("\t\t\t                ");
		printf("\r");
		printf("\n");*/
	}
	return p;


}

/*
* 播放下一首歌曲
*/
struct media* Next_Play(struct media* head, struct media* p, int maxNum)//下一曲
{

	if (p->next != NULL)
	{
		close_Song(p);
		//system("CLS");
		p = p->next;
		is_End = 0;
		music_face();
		timeDisplay(p);
		play(head, p, maxNum);
	
	}
	else
	{
		close_Song(p);

		p = head->next;
		music_face();
		timeDisplay(p);
		play(head, p, maxNum);

		/*if (is_End == 1) {
			return p;
		}
		is_End = 1;
		printf("\n");
		printf("\t\t\t当前是最后一首！即将返回上一菜单！");
		Sleep(1000);
		printf("\r");
		printf("\t\t\t                 ");
		printf("\r");
		printf("\n");*/
	}
	return p;

}

/*
* 暂停/开始播放
*/
void Pause_Play(struct media* p)
{

	char pathname[200];
	char cmd[200];

	if (st == 1)
	{
		sprintf(pathname, "%s%s", PATH, p->name); 
		GetShortPathName(pathname, pathname, 50);  
		sprintf(cmd, "pause %s", pathname);   
		mciSendString(cmd, NULL, 0, NULL); 
		system("pause > nul");
		st = 0;
	}
	else if (st == 0)
	{
		sprintf(pathname,"%s%s", PATH, p->name);
		GetShortPathName(pathname, pathname, 50);
		sprintf(cmd, "resume %s", pathname);
		mciSendString(cmd, NULL, 0, NULL);
		st = 1;
	}

}

/*
* 提高音量
*/
void VoiceUp(struct media* p)
{

	TCHAR cmd[256]; 
	TCHAR Voice[256]; 
	int nVoice; 

	char pathname[100];
	sprintf(pathname, "%s%s", PATH, p->name);
	GetShortPathName(pathname, pathname, 50);

	sprintf(cmd, "status %s volume", pathname); 
	mciSendString(cmd, Voice, sizeof(Voice), 0); 

	nVoice = atoi(Voice); 

	sprintf(cmd, "setaudio %s volume to %i", pathname, nVoice + 100); 
	mciSendString(cmd, NULL, 0, NULL); 
}


/*
* 降低音量
*/
void VoiceDown(struct media* p)
{

	TCHAR cmd[256];
	TCHAR Voice[256];
	int nVoice;

	char pathname[100];
	sprintf(pathname, "%s%s", PATH, p->name);
	GetShortPathName(pathname, pathname, 50);

	sprintf(cmd, "status %s volume", pathname);
	mciSendString(cmd, Voice, sizeof(Voice), 0);

	nVoice = atoi(Voice); 

	sprintf(cmd, "setaudio %s volume to %i", pathname, nVoice - 100); 
	mciSendString(cmd, NULL, 0, NULL);
}

/*
* 快进5s
*/
void forward(struct media* p)
{
	int time = getSongTime(p) * 1000;
	int nPosition;
	char position[200];
	char pathname[200];
	char cmd[200];

	sprintf(pathname, "%s%s", PATH, p->name);
	GetShortPathName(pathname, pathname, 50);
	sprintf(cmd, "status %s position", pathname);
	mciSendString(cmd, position, sizeof(position), 0);
	nPosition = atoi(position) + 5 * 1000;

	if (nPosition > time) {
		nPosition = time;
	}
	sprintf(cmd, "play %s from %d", pathname, nPosition);
	mciSendString(cmd, NULL, 0, NULL); 
}

/*
* 快退5s
*/
void back(struct media* p)
{

	int itime;
	int nPosition;
	char position[200];
	char pathname[200];
	char cmd[200];

	sprintf(pathname, "%s%s", PATH, p->name);
	GetShortPathName(pathname, pathname, 50);
	sprintf(cmd, "status %s position", pathname);
	mciSendString(cmd, position, sizeof(position), 0);
	nPosition = atoi(position) - 5 * 1000;

	if (nPosition < 0) {
		nPosition = 0;
	}
	sprintf(cmd, "play %s from %d", pathname, nPosition);
	mciSendString(cmd, NULL, 0, NULL);
}

/*
* 展示时间、歌词的变化以及对用户的操作做出相应反应
*/
struct media* operation(struct media* head, struct media* p, int maxNum) {
	DoubleBuffInitial();
	srand((unsigned)time(NULL));	
	if (p == NULL) return;
		display(p);
		int minute = 0;
		int second = 0;
	    timeDisplay(p);
		double sta = 1 / (double)37;
		int time = getSongTime(p);
		int flag = 1;
		LRC* heads = NULL, * p_new = NULL, * t1 = NULL, * t0 = NULL, * t2 = NULL, *t3 = NULL;
		char* str = NULL, * lrc_buf = NULL;
		char file_name[20];
		int i, j, k, len;
		int time_buf[5];
		char* q[200];
		lrc_buf = read_file(p);
		len = cut_lyric(lrc_buf, q, "\r\n");
		int t = 0;

		//printf("%d", st);

			for (t; (t >= 0) && (t <= time) && flag == 1; t++) {
				for (k = 0; k < len; k++)
				{
					str = q[k];
					i = 0;
					while (*str == '[')
					{
						time_buf[i++] = atoi(str + 1) * 60 + atoi(str + 4);
						str += 10;
					}
					for (j = 0; j < i; j++)
					{
						p_new = (LRC*)malloc(sizeof(LRC));
						p_new->m_time = time_buf[j];
						strcpy(p_new->lrc_buf, str);
						heads = link_insert(heads, p_new);
					}
				}
				if (heads->next != NULL && t < heads->next->m_time - 6) {

					handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
					fflush(stdout);
					t2 = link_search(heads, t);
					if (t2 != NULL) {
						memset(PrintfBuff, 0, sizeof PrintfBuff);
						strcpy(PrintfBuff, t2->lrc_buf);
						COORD  point = { 80 ,  18 };
						HANDLE  HOutput = GetStdHandle(STD_OUTPUT_HANDLE);

						//setsyscolor();
						SetConsoleCursorPosition(HOutput, point);
						printf("\r%*c\r", 60, ' ');
						//WriteConsoleOutputCharacterA(hSet, PrintfBuff, LENGTH, point, &bytes);
						//SetConsoleActiveScreenBuffer(hOutBuf);
						printf(" \t\t%s\n", PrintfBuff);
						COORD point2 = { 80 ,  15 };
						SetConsoleCursorPosition(HOutput, point2);

						if (t1 != NULL) {
							//setTextcolor();
							memset(PrintfBuff, 0, sizeof PrintfBuff);
							strcpy(PrintfBuff, t1->lrc_buf);
							printf("\r%*c\r", 60, ' ');
							printf(" \t\t%s\n", t1->lrc_buf);
							//WriteConsoleOutputCharacterA(hSet, PrintfBuff, LENGTH, point2, &bytes);

						}
						COORD point3 = { 80 ,  12 };
						SetConsoleCursorPosition(HOutput, point3);
						if (t0 != NULL) {
							//setTextcolor();
							memset(PrintfBuff, 0, sizeof PrintfBuff);
							strcpy(PrintfBuff, t0->lrc_buf);
							printf("\r%*c\r", 60, ' ');
							printf(" \t\t%s\n", t0->lrc_buf);//打印所有时间
							//WriteConsoleOutputCharacterA(hSet, PrintfBuff, LENGTH, point3, &bytes);
						}
						COORD point4 = { 80 ,  9 };
						SetConsoleCursorPosition(HOutput, point4);
						if (t3 != NULL) {
							printf("\r%*c\r", 60, ' ');
							printf(" \t\t%s\n", t3->lrc_buf);//打印所有时间

						}
						t3 = t0;
						t0 = t1;
						t1 = t2;
					}
				}
				BuffSwitch = !BuffSwitch;
				hSet = hOut[BuffSwitch];
				COORD  point = { 68 ,  24 };
				HANDLE  HOutput = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleCursorPosition(HOutput, point);
				printf("%02d:%02d", minute, second);
				second++;
				if (second == 60) {
					second = 0;
					minute++;
				}
				double num = 0;
				double per = ((double)t / (double)time);
				for (; num < 37; num++) {
					if ((per >= (num * sta)) && (per <= ((num + 1) * sta))) {
						COORD  point = { 74 + num,  24 };
						HANDLE  HOutput = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleCursorPosition(HOutput, point);

						printf("%c", '>');
						break;
					}
				}
				for (int j = 0; j < 5; j++) {
					Sleep(190);
					if (GetKeyState(VK_SPACE) < 0)
					{
						
						Pause_Play(p);
					}
					else if (GetKeyState(VK_UP) < 0)
						p = Last_Play(head, p, maxNum);

					else if (GetKeyState(VK_DOWN) < 0)
						p = Next_Play(head, p, maxNum);
					else if (GetKeyState(VK_OEM_PLUS) < 0)
					{
						VoiceUp(p);
					}

					else if (GetKeyState(VK_OEM_MINUS) < 0)
					{
						VoiceDown(p);
					}
					else if (GetKeyState(VK_ESCAPE) < 0)
					{
						setlogocolor();
						system("CLS");
						printf("\n\n\n");
						printf("\t\t                        _ __   _____ ___  _  _________       _____ ______     \n");
						printf("\t\t                       / __ \\/  __  / /__\\ \\/  ___/ / \\ \\   / ____/__  __/      \n");
						printf("\t\t ________________     / /_/ / /  / / /   | / /   / /__| |  /_/_ _   / /     ________________   \n");
						printf("\t\t/___/___/___/___/    / ____/ /__/ / /___/ / /__   /___| | ____/ /  / /     /___/___/___/___/      \n");
						printf("\t\t                    /_/   /______/_/___/_/_/___/ /    | |/____ /  /_/          \n");
						printf("\n\n\n\n");
						printf("\t\t\t\t\t╔═══════════════════════════════════╗\n");
						printf("\t\t\t\t\t║                                   ║\n");
						printf("\t\t\t\t\t║             评 论 区              ║\n");
						printf("\t\t\t\t\t║                                   ║\n");
						printf("\t\t\t\t\t╚═══════════════════════════════════╝\n");
						p = commentWrite(p);
						close_Song(p);
						return p;

					}
					else if (GetKeyState(VK_TAB) < 0) { //停止
						close_Song(p);
						return;
					}
					else if (GetKeyState(VK_RIGHT) < 0) {
						forward(p);
						second += 5;
						if (second >= 60) {
							second = second - 60;
							minute++;
							if ((minute == min && second > sec) || (minute > min)) {
								minute = min;
								second = sec;
							}
						}
						t += 5;
						if (t > time) {
							t = time;
						}
						per = ((double)t / (double)time);
						for (; num < 37; num++) {
							if ((per >= (num * sta)) && (per <= ((num + 1) * sta))) {
								COORD  point = { 74 + num,  24 };
								HANDLE  HOutput = GetStdHandle(STD_OUTPUT_HANDLE);
								SetConsoleCursorPosition(HOutput, point);

								printf("%c", '>');
								break;
							}
						}
					}
					else if (GetKeyState(VK_LEFT) < 0) {
						back(p);
						second -= 5;
						if (second <= 0) {
							second = 60 + second;
							minute--;
							if (minute < 0) {
								minute = 0;
								second = 0;
							}
						}
						t -= 5;
						if (t < 0) {
							t = 0;
						}
						per = ((double)t / (double)time);
						for (; num >= 0; num--) {
							if ((per >= (num * sta)) && (per <= ((num + 1) * sta))) {
								COORD  point = { 74 + num,  24 };
								HANDLE  HOutput = GetStdHandle(STD_OUTPUT_HANDLE);
								SetConsoleCursorPosition(HOutput, point);
								printf("%c", '>');

								printf("%c", '-');
								printf("%c", '-');
								break;
							}
						}
					}

					/*else if (GetKeyState(13))
					{
						close_Song(p);
						return;
					}*/




				}
			

		}
		
		Sleep(1500);      
		/*
		* 切换播放模式
		*/
		if (mode == 1) { //单曲循环
			close_Song(p);
			play(head, p, maxNum);
		}
		else if (mode == 2) {//列表循环
			if (p->next == NULL) {
				p = head->next;
			}
			else {
				p = p->next;
			}
			play(head, p, maxNum);
		}
		else if (mode == 3) {//随机
			int r = rand() % maxNum + 1;
			for (int i = 0; i < r; i++) {
				if (p->next == NULL) {
					p = head->next;
				}
				else {
					p = p->next;
				}
			}
			play(head, p, maxNum);
		}

		return NULL;
}

/*
* 打印相关日志
*/
void log_record(int error_level, const char* format, ...)
{
	va_list args;
	FILE* fp = NULL;
	char time_str[32];
	char file_name[256];

	va_start(args, format);
	time_t time_log = time(NULL);
	strftime(file_name, sizeof(file_name), "%Y-%m-%d_log_history.log", localtime(&time_log));


	if ((fp = fopen(file_name, "a+")) != NULL)
	{
		strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&time_log));
		if (error_level == (int)FATAL)
		{
			fprintf(fp, "[%s]-[%s]-[%s] :>   ", time_str, "FATAL", __FILE__);
			vfprintf(fp, format, args);
			fprintf(fp, "\n");

		}
		if (error_level == (int)ERROR_)
		{
			fprintf(fp, "[%s]-[%s]-[%s] :>   ", time_str, "ERROR", __FILE__);
			vfprintf(fp, format, args);
			fprintf(fp, "\n");

		}
		else if (error_level == (int)WARNING)
		{
			fprintf(fp, "[%s]-[%s]-[%s] :> ", time_str, "WARNINGs", __FILE__);
			vfprintf(fp, format, args);
			fprintf(fp, "\n");
		}
		else if (error_level == (int)INFO)
		{
			fprintf(fp, "[%s]-[%s]-[%s] :>      ", time_str, "INFO", __FILE__);
			vfprintf(fp, format, args);
			fprintf(fp, "\n");
		}
		else if (error_level == (int)DEBUG)
		{
			fprintf(fp, "[%s]-[%s]-[%s] :>    ", time_str, "DEBUG", __FILE__);
			vfprintf(fp, format, args);
			fprintf(fp, "\n");
		}
		fclose(fp);
	}

	va_end(args);
}
