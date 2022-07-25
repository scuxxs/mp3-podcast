#ifndef _MUSIC_H_
#define _MUSIC_H_
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include"lyric.h"
struct media
{
	int num;
	char name[1000];
	struct media* next;
	char comment[50][50];
	int commentnum;
};

void print_choice();

int Print_musicList(struct media* head);

struct media* CreatHead();

void switch_mode();

void display_mode();

void My_List();

struct media* Choose_Song(struct media* HEAD, struct media* P, int num, int max);

struct media* find_song(struct media* head, struct media* resultHead);

struct media* play(struct meida* head, struct media* p, int max);

int getSongTime(struct media* p);

void timeDisplay(struct media* p);

void display(struct media* p);

void commentRead(struct media* p);

struct media* commentWrite(struct media* p);

void close_Song(struct media* p);

struct media* Last_Play(struct media* head, struct media* p, int maxNum);

struct media* Next_Play(struct media* head, struct media* p, int maxNum);

void Pause_Play(struct media* p);

struct media* operation(struct media* head, struct media* p, int maxNum);

void delSpace(char* str);

void VoiceUp(struct media* p);

void VoiceDown(struct media* p);

void back(struct media* p);

void forward(struct media* p);

struct media* Player_Switch(struct media* HEAD, struct media* P, int max);

void DoubleBuffInitial();

void log_record(int error_level, const char* format, ...);
#endif