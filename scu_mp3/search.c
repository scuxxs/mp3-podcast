#include "lyric.h"
#include "menu.h"
#include "music.h"
#include <string.h>


/*
* 根据关键字查找相关歌曲
*/
struct media* find_song(struct media* head, struct media* resultHead)
{
	setlogocolor();
	printf("\n\n\n");
	printf("\t\t                        _ __   _____ ___  _  _________       _____ ______     \n");
	printf("\t\t                       / __ \\/  __  / /__\\ \\/  ___/ / \\ \\   / ____/__  __/      \n");
	printf("\t\t ________________     / /_/ / /  / / /   | / /   / /__| |  /_/_ _   / /     ________________   \n");
	printf("\t\t/___/___/___/___/    / ____/ /__/ / /___/ / /__   /___| | ____/ /  / /     /___/___/___/___/      \n");
	printf("\t\t                    /_/   /______/_/___/_/_/___/ /    | |/____ /  /_/          \n");
	printf("\n\n\n\n");
	printf("\t\t\t\t\t╔══════════════════════════════════╗\n");
	printf("\t\t\t\t\t║       请输入你要查找的关键字     ║\n");
	printf("\t\t\t\t\t╚══════════════════════════════════╝\n");
	int st = 0;
	int flag = 1;
	int i = 0;
	int j = 0;
	int cnt = 0;
	struct media* pt = (struct media*)malloc(sizeof(pt));
	struct media* p = head->next;
	pt = resultHead;
	char key[20] = { "\0" };
	
	scanf("%s", &key);
	getchar();

	
	for (flag = 1; p != NULL; p = p->next)
	{
		flag = 1;
		for (i = 0; i < strlen(key); i++)
		{
			for (j = 0; j < strlen(p->name); j++)
			{
				if (p->name[j] == key[i])
				{
					flag = 1;
					break;
				}

				else flag = 0;
			}
			if (flag == 0) break;
		}

		if (flag == 1)
		{
			pt->next = p;
			pt = p;
			st = 1;
			cnt++;
		}
	}
	pt->next = NULL;
	if (st == 0)
	{
		printf("\n\n");
		printc(20,"( ˙灬˙ ) orz输入的关键词不存在！\n\n");
		getchar();
		return resultHead;
		
	}
	return resultHead;
}
