#include "Header.h"

int field[field_height][field_width];

char colorname[type_max][5 + 1]={
	"WHITE",
	"BLACK"
};

position user;
int re;
int turn = black, gameset=0;
int count[type_max];

int main(void)
{
	system("stty -icanon -echo");
	user.x=0;
	user.y=0;
	makefield(field);
	while (1) {
		drawfield(field, user, turn, colorname);
		switch (inputKey())
		{
		case up:
			if (user.y > 0)
				user.y--;
			break;
		case down:
			if (user.y < field_height - 1)
				user.y++;
			break;
		case left:
			if (user.x > 0)
				user.x--;
			break;
		case right:
			if (user.x < field_width - 1)
				user.x++;
			break;
		case Esc:
			printf("強制終了\n");
			system("stty icanon echo");
			return 0;
		case enter:
			switch (Turn(field, user, &turn, colorname, count))   //ひっくりかえす関数
			{
			case 0:
				printf("again\n");
				break;
			case 1:
				break;
			case 2:
				printf("END\n");
				return 0;
			case 3:
				printf("%s pass\n", colorname[turn]);
				break;
			default:
				printf("error\n");
				break;
			}
		case other:
			break;
		default:
			break;
		}
		usleep(2*100000);// 1 秒
	}
	printf("終了する。\n");
	system("stty icanon echo");
}

enum keycode inputKey() {
    int kn = getchar(); //1:通常キー
    if (kn == 0x1b){
        kn = getchar(); //2:特殊キー
        if(kn==0x5b){
            kn=getchar();
            switch (kn)
            {
            case 0x41:  // ↑
                return up;
            case 0x42:  // ↓
                return down;
            case 0x43:  // →
                return right;
            case 0x44:  // ←
                return left;
            default:
                return other;
            }
        }else if(kn==0x1b){ //Twice Esc is exit(0).
            return Esc;
        }else{
            return other;
        }
    }else if(kn==0x0a){
        return enter;
    }else{
        return other;
    }
	return other;
}

void makefield(int field[field_height][field_width]) {
	for (int y = 0; y < field_height; y++) {
		for (int x = 0; x < field_width; x++) {
			field[y][x] = none;
			if (((x == 3) && (y == 3)) || ((x == 4) && (y == 4)))
				field[y][x] = white;
			if (((x == 3) && (y == 4)) || ((x == 4) && (y == 3)))
				field[y][x] = black;
		}
	}
}

void drawfield(int field[field_height][field_width],position user,int turn, char colorname[type_max][6]) {
	system("clear");
	for (int y = 0; y < field_height; y++) {
		for (int x = 0; x < field_width; x++) {
			if (x == user.x&&y == user.y)
				printf("%s", USER);
			else
				switch (field[y][x]) {
				case none:
					printf("%s", NONE);
					break;
				case white:
					printf("%s", WHITE);
					break;
				case black:
					printf("%s", BLACK);
					break;
				default:
					printf("e");
				}
		}
		printf("\n");
	}
	printf("You use these keys.\n");
	printf("KEY_UP\n");
	printf("KEY_DOWN\n");
	printf("KEY_LEFT\n");
	printf("KEY_RIGHT\n");
	printf("KEY_Esc\n");
	printf("KEY_Enter\n");
	printf("\n%s turn.\n\n", colorname[turn]);
}
