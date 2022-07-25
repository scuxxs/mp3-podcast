#ifndef _LYRIC_H_
#define _LYRIC_H_

typedef struct lrc {
	int m_time;
	char lrc_buf[200];
	struct lrc* front;
	struct lrc* next;
}LRC;

char* read_file(struct media* p);

LRC* link_search(LRC* head, int num);

int cut_lyric(char* msg_src, char* msg_done[], char* str);

LRC* link_insert(LRC* head, LRC* p_new);
#endif
