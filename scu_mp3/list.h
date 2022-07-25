#ifndef _LIST_H_
#define _LIST_H_
void creat_list();

void remove_list();

struct media* display_one_list(struct media* head);

void print_all_list();

void add_to_List(struct media* head);

struct media* remove_in_list(struct media* head);

struct media* List_Choose_Song(struct media* myhead, struct media* P);

struct media* Creat_MyLitsHead(FILE* fp, struct media* head);


struct media* findp_by_num(struct media* head, int num);
#endif