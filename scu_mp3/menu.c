#include<stdio.h>
#include"menu.h"
#include"music.h"
#include<string.h>
#include<stdlib.h>
#include"lyric.h"
#include"list.h"
#include <Windows.h>
#include <stdarg.h>

struct media* resultHead;
struct media* HEAD, * MYHEAD, * P;
char ch1 = 0;
int logocolor = 12;
int inMyList = 0;
enum { FATAL, ERROR_, WARNING, INFO, DEBUG };

/*
* ���˵����й���
*/
void show_Menu() {
	int flag = 1;
	int cho = 0;

	while (flag) {
		print_Menu();

		cho = _getch() - 48;
		switch (cho) {
		case 1:
			show_List();
			break;
		case 2:
			show_help();
			break;
		case 3:
			change_Color();
			break;
		case 4:
			flag = 0;
			break;
		default:
			break;

		}

	}
}

/*
* ��ӡ���˵�����
*/
void print_Menu() {
	system("CLS");
	setlogocolor();
	printf("\n\n\n");
	printf("\n\n\n");
	printf("\t\t\t /$$$$$$$                 /$$                                 /$$  \n ");
	printf("\t\t\t| $$__  $$               | $$                                | $$  \n  ");
	printf("\t\t\t| $$  \\ $$ /$$$$$$   /$$$$$$$  /$$$$$$$  /$$$$$$   /$$$$$$$ /$$$$$$ \n");
	printf("\t\t\t| $$$$$$$//$$__  $$ /$$__  $$ /$$_____/ |____  $$ /$$_____/|_  $$_/  \n");
	printf("\t\t\t| $$____/| $$  \\ $$| $$  | $$| $$        /$$$$$$$|  $$$$$$   | $$    \n");
	printf("\t\t\t| $$     | $$  | $$| $$  | $$| $$       /$$__  $$ \\____  $$  | $$ /$$\n");
	printf("\t\t\t| $$     |  $$$$$$/|  $$$$$$$|  $$$$$$$|  $$$$$$$ /$$$$$$$/  |  $$$$/\n");
	printf("\t\t\t|__/      \\______/  \\_______/ \\_______/ \\_______/|_______/    \\___/  \n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");

	printf("\t\t\t      1.�����б�\t\t\t2.ʹ��˵��\n\n");
	printf("\t\t\t      3.����Ƥ��\t\t\t4.�˳�����\n\n");

}

/*
* ��ӡ��������˵�
*/
void show_List() {
	P = NULL;
	int flag = 1;
	while (flag) {
		HEAD = CreatHead();
		int maxNum = Print_musicList(HEAD);
		inMyList = 0;
		int num = -1;
		print_choice();
		ch1 = _getch();
		switch (ch1) {
		case 'a': switch_mode(); break;
		case 'b': MYHEAD = NULL;  My_List(); break;
		case 'c':
			P = Choose_Song(HEAD, P, num, maxNum); 
			music_face();
			timeDisplay(P);
			P = Player_Switch(HEAD, P, maxNum);
			break;
		case 'd':
			resultHead = (struct media*)malloc(sizeof(struct media)); 
			system("CLS");
			resultHead = find_song(HEAD,resultHead); 
			if (resultHead->next != NULL) {
				Print_musicList(resultHead);
				P = Choose_Song(resultHead, P, num, maxNum);
				music_face();
				timeDisplay(P);
				P = Player_Switch(HEAD, P, maxNum);
			}
			
			break;
		case 'e':flag = 0; break;
		default: break;
		}
		
	}
	

}

/*
* ��ӡ��������
*/
void show_help() {
	system("CLS");
	printf("\n");
	printf("\t\t                        _ __   _____ ___  _  _________       _____ ______     \n");
	printf("\t\t                       / __ \\/  __  / /__\\ \\/  ___/ / \\ \\   / ____/__  __/      \n");
	printf("\t\t ________________     / /_/ / /  / / /   | / /   / /__| |  /_/_ _   / /     ________________   \n");
	printf("\t\t/___/___/___/___/    / ____/ /__/ / /___/ / /__   /___| | ____/ /  / /     /___/___/___/___/      \n");
	printf("\t\t                    /_/   /______/_/___/_/_/___/ /    | |/____ /  /_/          \n");
	printf("\n\n");
	COORD  point1 = { 25 ,  12 };
	HANDLE  HOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(HOutput, point1);
	printf("���������ֲ�������һ�����������������ء������򵥡�����ʱ�С����ٽ���!\n\n\n");
	COORD  point2 = { 25 ,  15 };
	SetConsoleCursorPosition(HOutput, point2);
	printf("������ò��Ų�����һ���ǵ������⣬������ò�����һ�����������!\n\n\n");
	COORD  point3 = { 25 ,  18 };
	SetConsoleCursorPosition(HOutput, point3);
	printf("�߻����û�ͬΪһ�ģ�������еĺ���!\n");
	getchar();

}

/*
* ����Ƥ��
*/
void change_Color() {
	system("CLS");
	printf("\n\n\n");
	log_record(3, "LINE:  %d   Successfully change color", __LINE__ - 2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("\t\t\t\t0 �� �� ��     ����");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	printf("\t\t8 �� �� ��     ǳ��\n\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	printf("\t\t\t\t1 �� �� ��     ����");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	printf("\t\t9 �� �� ��     ��ɫ\n\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	printf("\t\t\t\t2 �� �� ��     ����");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf("\t\t10�� �� ��     ǳ��\n\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	printf("\t\t\t\t3 �� �� ��     ����");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	printf("\t\t11�� �� ��     ǳ��\n\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf("\t\t\t\t4 �� �� ��     ���");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("\t\t12�� �� ��     ��ɫ\n\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
	printf("\t\t\t\t5 �� �� ��     �Ϻ�");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	printf("\t\t13�� �� ��     õ��\n\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("\t\t\t\t6 �� �� ��     ���");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("\t\t14�� �� ��     ��ɫ\n\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("\t\t\t\t7 �� �� ��     ��ɫ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("\t\t15�� �� ��     ����\n\n\n");
	printf("\t\t\t\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("\t\t\t\t�U    ����������Ҫ�ı��������ɫ��ţ��������� �U\n");
	printf("\t\t\t\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	scanf("%d", &logocolor);
}

/*
* ��ӡ�赥����˵�
*/
void printMyList()
{
	printf("\n");
	printf("\t\t                        _ __   _____ ___  _  _________       _____ ______     \n");
	printf("\t\t                       / __ \\/  __  / /__\\ \\/  ___/ / \\ \\   / ____/__  __/      \n");
	printf("\t\t ________________     / /_/ / /  / / /   | / /   / /__| |  /_/_ _   / /     ________________   \n");
	printf("\t\t/___/___/___/___/    / ____/ /__/ / /___/ / /__   /___| | ____/ /  / /     /___/___/___/___/      \n");
	printf("\t\t                    /_/   /______/_/___/_/_/___/ /    | |/____ /  /_/          \n");
	printf("\n\n");
	printf("\t\t\t\t\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("\t\t\t\t\t�U                                     �U\n");
	printf("\t\t\t\t\t�U *x.�½��赥           *t.ɾ���赥   �U\n");
	printf("\t\t\t\t\t�U                                     �U\n");
	printf("\t\t\t\t\t�U *p.չʾ�赥           *q.ѡ������   �U\n");
	printf("\t\t\t\t\t�U                                     �U\n");
	printf("\t\t\t\t\t�U *l.��Ӹ���           *d.ɾ������   �U\n");
	printf("\t\t\t\t\t�U                                     �U\n");
	printf("\t\t\t\t\t�U *a.���и赥           *e.���ز˵�   �U\n");
	printf("\t\t\t\t\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
}

/*
* �赥���ָ��ֹ���
*/
void My_List() {
	int flag = 1;
	int max;
	int num = -1;

	system("cls");
	if (MYHEAD != NULL) {
		Print_musicList(MYHEAD);
	}
	P = NULL;
	while (flag) {
		printMyList();
		ch1 = _getch();
		switch (ch1)
		{
		case 'x':creat_list(); system("cls"); break;
		case 't': remove_list(); system("cls"); break;
		case 'p':
			MYHEAD = display_one_list(HEAD);
			if (MYHEAD != NULL)
				max = Print_musicList(MYHEAD);
			break;
		case 'q':
			if (MYHEAD == NULL) {
				system("cls");
				printf("����ѡ��Ҫչʾ�ĸ赥");
			}
			else {
				P = List_Choose_Song(MYHEAD, P);
				music_face();
				timeDisplay(P);
				P = Player_Switch(MYHEAD, P, max);
			}
			break;
		case 'l':Print_musicList(HEAD); printMyList();
			add_to_List(HEAD); system("cls"); break;
		case 'd':MYHEAD = remove_in_list(HEAD); break;
		case 'a':print_all_list(); break;
		case 'e':flag = 0; break;
		default:system("cls");
		}
	}
	

}

/*
* ѡ����תҳ�档
*/
struct media* Player_Switch(struct media* HEAD, struct media* P, int max)
{
	//�رո���֮���Զ�������һ��ҳ��
	play(HEAD, P, max);
	if (inMyList == 0) {
		show_List();
	}
	else if (inMyList == 1) {
		My_List();
	}
	return P;
	
}

void setlogocolor() {
	switch (logocolor) {
		case 0:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
			break;
		case 1:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1); break;
		case 2:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); break;
		case 3:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); break;
		case 4:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); break;
		case 5:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5); break;
		case 6:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); break;
		case 7:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); break;
		case 8:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8); break;
		case 9:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); break;
		case 10:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); break;
		case 11:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); break;
		case 12:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); break;
		case 13:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); break;
		case 14:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); break;
		case 15:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); break;
		}
}

/*
* ��ӡ������Ϣ
*/
void printc(int len, char* str)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_INTENSITY | FOREGROUND_RED | COMMON_LVB_UNDERSCORE);
	printf("%s", str);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	Sleep(3000);
	printf("\r");
	for (int i = 0; i < len; i++) {
		printf(" ");
	}
	printf("\r");
}

