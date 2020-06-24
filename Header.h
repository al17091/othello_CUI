#pragma once
#ifndef ___prottype
#define ___prottype

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define field_height 8
#define field_width 8

typedef struct{
	int x;
	int y;
}position;

enum type{
	none = -1,//none
	white = 0,//white
	black,//black
	type_max
};

enum keycode{
    Esc=-1,
    up=0,
    down,
    right,
    left,
    enter,
    other
};

#define NONE  "[ ]"
#define WHITE "[●]"
#define BLACK "[○]"
#define USER  "[*]"

void makefield(int field[field_height][field_width]);
void drawfield(int field[field_height][field_width], position, int, char[type_max][6]);
int checkput(int field[field_height][field_width], int, position, int);
int checkputall(int field[field_height][field_width],position, int);
int Turn(int field[field_height][field_width], position, int*, char[type_max][6], int[type_max]);
enum keycode inputKey();

#endif // !___prottype
