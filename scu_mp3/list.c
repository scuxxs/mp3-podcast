#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include"music.h"
#include"menu.h"
#include<Windows.h>
#include <mmsystem.h>
#include"lyric.h"
#include"list.h"
#include<io.h>
#define PATH "D:\\music\\"  
extern int inMyList;

/*
* 新建歌单
*/
void creat_list() {
	FILE* fp;
	char listname[100];
	char pathname[100];

	//用户输入，获取路径，用r打开检测歌单是否存在
	printf("请输入新建的歌单名称：");
	scanf_s("%s", listname, sizeof(listname));
	sprintf_s(pathname, sizeof(pathname), "%s%s.txt", PATH, listname);
	errno_t er = fopen_s(&fp, pathname, "r");

	if (er != 0) {  //打开失败，不存在，新建		
		fopen_s(&fp, pathname, "w");
		if (fp) {
			fclose(fp);
		}
		printf("新建歌单成功！");
		log_record(3, "LINE:  %d   Successfully create list called %s", __LINE__ - 2, listname);
		Sleep(3000);
	}
	else {         //打开成功，返回信息已存在
		printc(15, "歌单已存在！");
		fclose(fp);
	}
}

/*
* 删除歌单
*/
void remove_list() {
	FILE* fp;
	char listname[100], pathname[100], str[200], str1[20];
	int numb = 0;

	//用户输入，获取路径，用r打开检测歌单是否存在
	printf("删除歌单：");
	scanf("%s", listname);
	sprintf(pathname, "%s%s.txt", PATH, listname);
	errno_t er = fopen_s(&fp, pathname, "r");
	if (er != 0) {

		printc(20, "歌单不存在!");
	}
	else {
		fclose(fp);
		int i = remove(pathname);
		if (i == 0) {
			printf("删除成功！");
			Sleep(3000);
			log_record(3, "LINE:  %d   Successfully remove list called %s", __LINE__ - 2, listname);
		}
		else {
			printf("失败");
			Sleep(3000);
		}

	}

}

/*
* 打印全部歌单
*/
void print_all_list() {
	system("CLS");
	int i = 0;
	long long Handle;

	struct _finddata_t FileInfo;
	if ((Handle = _findfirst("D:\\music\\*.txt", &FileInfo)) == -1LL)
	{
		printf("\n\t暂无歌单，请创建歌单");
	}
	else
	{
		i++;
		printf("%s\n", FileInfo.name);
		while (_findnext(Handle, &FileInfo) == 0)
		{
			i++;
			printf("%s\n", FileInfo.name);
		}
		printf("共有%d个歌单\n", i);
	}
}

/*
* 创建歌单链表
*/
struct media* Creat_MyLitsHead(FILE* fp, struct media* head)
{
	struct media* myhead, * p, * q;
	int num;
	char temp[100];
	char str[200];

	p = (struct media*)malloc(sizeof(struct media));
	myhead = (struct media*)malloc(sizeof(struct media));
	q = myhead;

	while (fgets(str, 200, fp)) {        //读取一行
		for (int i = 0; (str[i] != '\n') && (str[i] != '\0'); i++) {
			if (str[i] != ',') {
				temp[i] = str[i];       //分割'，'前内容
			}
			else {
				temp[i + 1] = '\0';
				num = atoi(temp);       //歌曲序号
				p = (struct media*)malloc(sizeof(struct media));
				if (p && q) {
					p->num = num;
					strcpy_s(p->name,     //总歌单内检索，生成链表
						sizeof((findp_by_num(head, num))->name),
						(findp_by_num(head, num))->name);
					q->next = p;
					q = p;
					break;
				}
			}
		}
	}
	if (p) {
		p->next = NULL;
	}
	inMyList = 1;      //全局变量设为1，表明现在在歌单内
	return myhead;
}

/*
* 通过序号查找
*/
struct media* findp_by_num(struct media* head, int num)
{
	struct media* p = head;
	while (p->next) {
		p = p->next;
		if (p->num == num) {
			break;
		}
	}
	return p;
}

/*
* 展示某一歌单
*/
struct media* display_one_list(struct media* head) {
	FILE* fp;
	char listname[100];
	char pathname[100];

	printf("展示歌单（输入名称）：");
	scanf("%s", listname);
	sprintf(pathname, "%s%s.txt", PATH, listname);
	errno_t er = fopen_s(&fp, pathname, "r");

	if (er != 0) {  //不存在
		printc(30, "歌单不存在，请先创建歌单！");
		system("cls");
		return NULL;
	}
	else if (fgetc(fp) == EOF) {  //歌单为空
		fclose(fp);
		system("CLS");
		printf("\n\t歌单为空\n");
		return NULL;
	}
	else {
		struct media* myhead = Creat_MyLitsHead(fp, head);
		fclose(fp);
		inMyList = 1;
		return myhead;
	}

}

/*
* 将歌曲添加至歌单
*/
void add_to_List(struct media* head) {

	FILE* fp;
	char listname[100], pathname[100], str[200], str1[20];
	int numb = 0;
	int isFound = 0;

	//用户输入，获取路径，用r打开检测歌单是否存在
	printf("添加到歌单：");
	scanf("%s", listname);
	sprintf(pathname, "%s%s.txt", PATH, listname);
	errno_t er = fopen_s(&fp, pathname, "r");

	if (er != 0) {                //不存在则自动创建一个
		printc(50, "歌单不存在，已创建该歌单！");
		fopen_s(&fp, pathname, "w");
	}
	else if (fgetc(fp) == EOF) {	   //存在为空，用w打开
		fclose(fp);
		fopen_s(&fp, pathname, "w");
	}
	else if (fgetc(fp) != EOF) {    //存在不为空，用a打开，先追加一个换行到末尾
		fclose(fp);
		fopen_s(&fp, pathname, "a");
		fputc('\n', fp);
	}

	if (fp) {
		printf("添加的歌曲序号：");
		scanf("%s", str);  //用户输入一个或多个序号，中间用','隔开
		sprintf(str, "%s,", str);

		//把输入的字符串变成一个个合适的int用head检索信息并输入
		int j = 0;
		int first = 0;

		if (str[0] > '9' || str[0] < '0') {
			printc(20, "退出添加");
			return;
		}
		for (int i = 0; str[i] != '\0'; i++) {
			if (str[i] <= '9' && str[i] >= '0') { //连着的数字视为一个，赋给承接数组str1
				str1[j] = str[i];
				j++;
			}
			else {
				str1[j] = '\0';  //不连着了就算做一个字符串结束
				numb = atoi(str1);

				//写入文件，一些格式的调整
				struct media* p;
				for (p = head; p; p = p->next) {
					if (p->num == numb) {
						if (fp) {
							if (first == 0) {
								fprintf(fp, " %d, %s", p->num, p->name);
								first = 1;
							}
							else
								fprintf(fp, "\n %d, %s", p->num, p->name);
							isFound = 1;
							break;
						}
					}
				}
				if (isFound == 0) {
					printf("未找到编号为%d的歌曲\n", numb);
				}
				memset(str1, 0, j); //承接数组str1清0
				j = 0;
			}
		}
	}
	if (fp) {
		fclose(fp);
	}
	printf("\n");
	printf("添加成功");
	Sleep(3000);
}

/*
* 在歌单中删除歌曲
*/
struct media* remove_in_list(struct media* head) {
	FILE* fp;
	struct media* myhead, * p, * q;
	char listname[100], pathname[100];
	int num;

	//用户输入，获取路径，用r打开检测歌单是否存在
	printf("删改歌单：");
	scanf("%s", listname);
	sprintf(pathname,"%s%s.txt", PATH, listname);
	errno_t er = fopen_s(&fp, pathname, "r");
	if (er != 0) {
		printc(20, "歌单不存在！");
		return NULL;
	}
	else if (fgetc(fp) == EOF) {  //歌单为空
		system("CLS");
		printf("\n\t歌单为空\n");
		fclose(fp);
		return NULL;
	}
	else {
		myhead = Creat_MyLitsHead(fp, head);   //生成歌单链表
		int n = Print_musicList(myhead);
		printMyList();
		printf("删除的歌曲序号：");
		scanf("%d", &num);

		//歌单内检索歌曲
		p = myhead->next;
		if (p->num == num) {
			myhead->next = p->next;
		}
		else {
			//找到后把该节点的前一节点指向后一节点
			q = (struct media*)malloc(sizeof(struct media));
			while (p->num != num) {
				q = p;
				if (p->next == NULL) {
					printf("未找到对应歌曲");
					Sleep(2500);
					fclose(fp);
					system("CLS");
					return myhead;
				}
				p = p->next;
			}
			q->next = p->next;
		}
		fclose(fp);

		//用w打开并清空文件，把删改过的链表信息按格式写进去
		p = myhead->next;
		fopen_s(&fp, pathname, "w");
		if (fp) {
			if (p == NULL) {
				fclose(fp);
				printf("删除成功");
				Sleep(2500);
				system("CLS");
				log_record(3, "LINE:  %d   remove the %dst in %s", __LINE__ - 2, num, listname);
				return NULL;

			}
			else {
				fprintf(fp, " %d, %s", p->num, p->name);
				while (p->next != NULL) {
					p = p->next;
					fprintf(fp, "\n %d, %s", p->num, p->name);
				}
				fclose(fp);
				printf("删除成功");
				Sleep(2500);
				system("CLS");
			}

		}
	}
	return myhead;

}

/*
* 在歌单中选择歌曲播放
*/
struct media* List_Choose_Song(struct media* myhead, struct media* P) {

	if (myhead == NULL)//文件夹为空，头指针设为空
		return myhead;
	else
	{
		int num;
		int right = 1;
		struct media* p;//返回该工作指针
		p = myhead->next;
		do
		{
			printf("\n\t请输入歌曲序号: ");
			scanf("%d", &num);

			//清除缓冲区，如果用户输入字符将会死循环
			while (getchar() != '\n')
				continue;

			//检测输入序号是不是歌单内有的歌曲序号
			while (p->num != num) {
				p = p->next;
				if (p == NULL) {
					right = 0;
					break;
				}
			}
			if (right == 0)
			{
				printf("\t请输入歌曲对应序号！\n");
				fflush(stdin);
				
			}
		} while (right == 0);

		if (P != NULL) close_Song(P); //有正在播放的先退出
		return p;
	}

}