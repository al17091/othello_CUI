#include <stdio.h>
#include <stdlib.h>

enum keycode{
    Esc=-1,
    up=0,
    down,
    right,
    left,
    enter,
    other
};

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
    
}

int main(void){
    system("stty -icanon -echo");
    while(1){
        switch (inputKey())
        {
        case Esc:
            printf("Esc pushed\n");
            break;
        case up:
            printf("up pushed\n");
            break;
        case down:
            printf("down pushed\n");
            break;
        case right:
            printf("right pushed\n");
            break;
        case left:
            printf("left pushed\n");
            break;
        case other:
            printf("other pushed\n");
            break;
        case enter:
            printf("enter pushed\n");        
            break;
        default:
            system("stty icanon echo");
            exit(1);
        }
    }
    system("stty icanon echo");
}
