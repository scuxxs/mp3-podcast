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
* �½��赥
*/
void creat_list() {
	FILE* fp;
	char listname[100];
	char pathname[100];

	//�û����룬��ȡ·������r�򿪼��赥�Ƿ����
	printf("�������½��ĸ赥���ƣ�");
	scanf_s("%s", listname, sizeof(listname));
	sprintf_s(pathname, sizeof(pathname), "%s%s.txt", PATH, listname);
	errno_t er = fopen_s(&fp, pathname, "r");

	if (er != 0) {  //��ʧ�ܣ������ڣ��½�		
		fopen_s(&fp, pathname, "w");
		if (fp) {
			fclose(fp);
		}
		printf("�½��赥�ɹ���");
		log_record(3, "LINE:  %d   Successfully create list called %s", __LINE__ - 2, listname);
		Sleep(3000);
	}
	else {         //�򿪳ɹ���������Ϣ�Ѵ���
		printc(15, "�赥�Ѵ��ڣ�");
		fclose(fp);
	}
}

/*
* ɾ���赥
*/
void remove_list() {
	FILE* fp;
	char listname[100], pathname[100], str[200], str1[20];
	int numb = 0;

	//�û����룬��ȡ·������r�򿪼��赥�Ƿ����
	printf("ɾ���赥��");
	scanf("%s", listname);
	sprintf(pathname, "%s%s.txt", PATH, listname);
	errno_t er = fopen_s(&fp, pathname, "r");
	if (er != 0) {

		printc(20, "�赥������!");
	}
	else {
		fclose(fp);
		int i = remove(pathname);
		if (i == 0) {
			printf("ɾ���ɹ���");
			Sleep(3000);
			log_record(3, "LINE:  %d   Successfully remove list called %s", __LINE__ - 2, listname);
		}
		else {
			printf("ʧ��");
			Sleep(3000);
		}

	}

}

/*
* ��ӡȫ���赥
*/
void print_all_list() {
	system("CLS");
	int i = 0;
	long long Handle;

	struct _finddata_t FileInfo;
	if ((Handle = _findfirst("D:\\music\\*.txt", &FileInfo)) == -1LL)
	{
		printf("\n\t���޸赥���봴���赥");
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
		printf("����%d���赥\n", i);
	}
}

/*
* �����赥����
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

	while (fgets(str, 200, fp)) {        //��ȡһ��
		for (int i = 0; (str[i] != '\n') && (str[i] != '\0'); i++) {
			if (str[i] != ',') {
				temp[i] = str[i];       //�ָ�'��'ǰ����
			}
			else {
				temp[i + 1] = '\0';
				num = atoi(temp);       //�������
				p = (struct media*)malloc(sizeof(struct media));
				if (p && q) {
					p->num = num;
					strcpy_s(p->name,     //�ܸ赥�ڼ�������������
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
	inMyList = 1;      //ȫ�ֱ�����Ϊ1�����������ڸ赥��
	return myhead;
}

/*
* ͨ����Ų���
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
* չʾĳһ�赥
*/
struct media* display_one_list(struct media* head) {
	FILE* fp;
	char listname[100];
	char pathname[100];

	printf("չʾ�赥���������ƣ���");
	scanf("%s", listname);
	sprintf(pathname, "%s%s.txt", PATH, listname);
	errno_t er = fopen_s(&fp, pathname, "r");

	if (er != 0) {  //������
		printc(30, "�赥�����ڣ����ȴ����赥��");
		system("cls");
		return NULL;
	}
	else if (fgetc(fp) == EOF) {  //�赥Ϊ��
		fclose(fp);
		system("CLS");
		printf("\n\t�赥Ϊ��\n");
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
* ������������赥
*/
void add_to_List(struct media* head) {

	FILE* fp;
	char listname[100], pathname[100], str[200], str1[20];
	int numb = 0;
	int isFound = 0;

	//�û����룬��ȡ·������r�򿪼��赥�Ƿ����
	printf("��ӵ��赥��");
	scanf("%s", listname);
	sprintf(pathname, "%s%s.txt", PATH, listname);
	errno_t er = fopen_s(&fp, pathname, "r");

	if (er != 0) {                //���������Զ�����һ��
		printc(50, "�赥�����ڣ��Ѵ����ø赥��");
		fopen_s(&fp, pathname, "w");
	}
	else if (fgetc(fp) == EOF) {	   //����Ϊ�գ���w��
		fclose(fp);
		fopen_s(&fp, pathname, "w");
	}
	else if (fgetc(fp) != EOF) {    //���ڲ�Ϊ�գ���a�򿪣���׷��һ�����е�ĩβ
		fclose(fp);
		fopen_s(&fp, pathname, "a");
		fputc('\n', fp);
	}

	if (fp) {
		printf("��ӵĸ�����ţ�");
		scanf("%s", str);  //�û�����һ��������ţ��м���','����
		sprintf(str, "%s,", str);

		//��������ַ������һ�������ʵ�int��head������Ϣ������
		int j = 0;
		int first = 0;

		if (str[0] > '9' || str[0] < '0') {
			printc(20, "�˳����");
			return;
		}
		for (int i = 0; str[i] != '\0'; i++) {
			if (str[i] <= '9' && str[i] >= '0') { //���ŵ�������Ϊһ���������н�����str1
				str1[j] = str[i];
				j++;
			}
			else {
				str1[j] = '\0';  //�������˾�����һ���ַ�������
				numb = atoi(str1);

				//д���ļ���һЩ��ʽ�ĵ���
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
					printf("δ�ҵ����Ϊ%d�ĸ���\n", numb);
				}
				memset(str1, 0, j); //�н�����str1��0
				j = 0;
			}
		}
	}
	if (fp) {
		fclose(fp);
	}
	printf("\n");
	printf("��ӳɹ�");
	Sleep(3000);
}

/*
* �ڸ赥��ɾ������
*/
struct media* remove_in_list(struct media* head) {
	FILE* fp;
	struct media* myhead, * p, * q;
	char listname[100], pathname[100];
	int num;

	//�û����룬��ȡ·������r�򿪼��赥�Ƿ����
	printf("ɾ�ĸ赥��");
	scanf("%s", listname);
	sprintf(pathname,"%s%s.txt", PATH, listname);
	errno_t er = fopen_s(&fp, pathname, "r");
	if (er != 0) {
		printc(20, "�赥�����ڣ�");
		return NULL;
	}
	else if (fgetc(fp) == EOF) {  //�赥Ϊ��
		system("CLS");
		printf("\n\t�赥Ϊ��\n");
		fclose(fp);
		return NULL;
	}
	else {
		myhead = Creat_MyLitsHead(fp, head);   //���ɸ赥����
		int n = Print_musicList(myhead);
		printMyList();
		printf("ɾ���ĸ�����ţ�");
		scanf("%d", &num);

		//�赥�ڼ�������
		p = myhead->next;
		if (p->num == num) {
			myhead->next = p->next;
		}
		else {
			//�ҵ���Ѹýڵ��ǰһ�ڵ�ָ���һ�ڵ�
			q = (struct media*)malloc(sizeof(struct media));
			while (p->num != num) {
				q = p;
				if (p->next == NULL) {
					printf("δ�ҵ���Ӧ����");
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

		//��w�򿪲�����ļ�����ɾ�Ĺ���������Ϣ����ʽд��ȥ
		p = myhead->next;
		fopen_s(&fp, pathname, "w");
		if (fp) {
			if (p == NULL) {
				fclose(fp);
				printf("ɾ���ɹ�");
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
				printf("ɾ���ɹ�");
				Sleep(2500);
				system("CLS");
			}

		}
	}
	return myhead;

}

/*
* �ڸ赥��ѡ���������
*/
struct media* List_Choose_Song(struct media* myhead, struct media* P) {

	if (myhead == NULL)//�ļ���Ϊ�գ�ͷָ����Ϊ��
		return myhead;
	else
	{
		int num;
		int right = 1;
		struct media* p;//���ظù���ָ��
		p = myhead->next;
		do
		{
			printf("\n\t������������: ");
			scanf("%d", &num);

			//���������������û������ַ�������ѭ��
			while (getchar() != '\n')
				continue;

			//�����������ǲ��Ǹ赥���еĸ������
			while (p->num != num) {
				p = p->next;
				if (p == NULL) {
					right = 0;
					break;
				}
			}
			if (right == 0)
			{
				printf("\t�����������Ӧ��ţ�\n");
				fflush(stdin);
				
			}
		} while (right == 0);

		if (P != NULL) close_Song(P); //�����ڲ��ŵ����˳�
		return p;
	}

}