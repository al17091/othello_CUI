#include "Header.h"

enum {
	direction_up,
	direction_upleft,
	direction_left,
	direction_downleft,
	direction_down,
	direction_downright,
	direction_right,
	direction_upright,
	direction_max
};

int directions[][2] = {
	{0,-1}, //direction_up
	{-1,-1},//direction_upleft
	{-1,0},//direction_left
	{-1,1},//direction_downleft
	{0,1},//direction_down
	{1,1},//direction_downright
	{1,0},//direction_right,
	{1,-1}//direction_upright
};

int checkput(int field[field_height][field_width],int color, position user, int turnover) {//turnover=0,check  
	if (field[user.y][user.x] != none)															 //turnover=1,change
		return 0;
	for (int i = 0; i < direction_max; i++) {
		int x = user.x, y = user.y;
		x += directions[i][0];
		y += directions[i][1];
		if (field[y][x] != (color ^ 1))
			continue;
		while (1) {
			x += directions[i][0];
			y += directions[i][1];
			if ((x < 0) || (x >= field_width) || (y < 0) || (y >= field_height))
				break;
			if (field[y][x] == none)
				break;
			if (field[y][x] == color) {
				if (!turnover)
					return 1;
				int cx = user.x, cy = user.y;
				while (1) {//同一方向にひっくりかえしていく
					field[cy][cx] = color;
					cx += directions[i][0];
					cy += directions[i][1];
					if ((cx == x) && (cy == y))
						break;
				}
				return 1;
			}
		}
	}
	return 0;
}

int checkputall(int field[field_height][field_width], position user,int color) {
	for (user.y = 0; user.y < field_height; user.y++)
		for (user.x = 0; user.x < field_width; user.x++)
			if (checkput(field,color,user,0))
				return 1;

	return 0;
}

int Turn(int field[field_height][field_width], position user, int* turn, char colorname[type_max][6], int count[type_max]) {
	if (!checkput(field, *turn, user, 0)) {
		printf("You cannot put here!\n");
		return 0;
	}
	else {
		checkput(field, *turn, user, 1);
		field[user.y][user.x] = *turn;
		*turn ^= 1;

		if ((!checkputall(field, user, black)) && (!checkputall(field, user, white))) {
			drawfield(field, user, *turn, colorname);
			printf("Game set!\n");
			int count[type_max] = {};
			for (int y = 0; y < field_height; y++)
				for (int x = 0; x < field_width; x++)
					if (field[y][x] != none)
						count[field[y][x]]++;
			for (int i = 0; i < type_max; i++)
				printf("%s:%d\n", colorname[i], count[i]);
			if (count[black] == count[white])
				printf("Draw!\n");
			else {
				if (count[black] > count[white])
					printf("%s ", colorname[black]);
				else
					printf("%s ", colorname[white]);
			}
			printf("won!\n");
			return 2;
		}
		if (!checkputall(field, user, *turn)) {
			*turn ^= 1;
			return 3;
		}
		return 1;
	}
}