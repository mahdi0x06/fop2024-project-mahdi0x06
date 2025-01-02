//back button
//load game
#include<stdio.h>
#include<ncurses.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
void initialize();
void sign_up();
void sign_in();
void menu();
void scoreboard();
void setting();
void quit();
void start_game();
typedef struct {
    char name[100], pass[100], mail[100];
    int points, golds, exp, health, color;
} att;
att player;
int main() {
    initscr();
    keypad(stdscr, TRUE);
    start_color();
    if(has_colors() == FALSE){	
        endwin();
	    printf("Your terminal does not support color\n");
	    exit(1);
    }
    init_pair(8, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(8));
    initialize();
    while(1) {
        char message[100];
        start_game();
    }
    quit();
    refresh();
    endwin();
    return 0;
}
void initialize() {
    mvprintw(20,83, "enter 1 to sign up");
    mvprintw(21,83, "enter 2 to sign in");
    mvprintw(22,83, "enter 3 to log in as a guest");
    refresh();
    while(1) {
    char n = getchar();
        if(n == '1') {clear(),sign_up(); break;}
        else if(n == '2') {clear(),sign_in(); break;} 
        else if(n == '3') {clear();break;}
        else {continue;}
    }
}
void sign_up() {
    FILE* f;
    mvprintw(0, 0,"Enter your username:\n");
    refresh();
    while(1) {
        scanw(" %s", player.name);
        FILE* check = fopen(player.name, "r");
        if((check == NULL) && (strlen(player.name) >= 7)) {
            f = fopen(player.name, "w");
            fprintf(f, "username:%s \n",  player.name);
            fclose(f);
            break;
        }
        else if((check != NULL) || (strlen(player.name) < 7)){
            printw("Username has already been taken(at least 7 characters) or it's not long enough\nplease enter a new username\n");
        }
    }
    printw("Enter your password:\n");
    while(1) {
        scanw(" %s", player.pass);
        int u = 0, l = 0, n = 0;
        for(int i = 0; player.pass[i] != '\0'; i++) {
            if('A' <= player.pass[i] && player.pass[i] <= 'Z') {
                u = 1;
            }
            else if('a' <= player.pass[i] && player.pass[i] <= 'z') {
                l = 1;
            }
            else if('0' <= player.pass[i] && player.pass[i] <= '9') {
                n = 1;
            }
        }
        if(strlen(player.pass) >= 7 && u && l && n) {
            f = fopen(player.name, "a");
            fprintf(f, "\npassword:%s \n",  player.pass);
            fclose(f);
            break;
        }
        else if(strlen(player.pass) < 7) {
            printw("Password is not long enough(at least 7 characters)\nplease enter a new password\n");
        }
        else if(u == 0 || l == 0 || n == 0) {
            printw("Your password should at least contain an upper case and a lower case and a number\nplease enter a new password\n");
        }
    }
    printw("Enter your email:\n");
    while(1) {
        scanw(" %s", player.mail);
        int ad = 0, dot = 0;
        for(int i = 0; player.mail[i] != '\0'; i++) {
            if(player.mail[i] == '@') {
                ad = i;
            }
            else if(player.mail[i] == '.') {
                dot = i;
            }
        }
        if((ad > 0) && (dot - ad > 1) && (dot + 1 != strlen(player.mail))) {
            f = fopen(player.name, "a");
            fprintf(f, "\nemail:%s \n",  player.mail);
            fclose(f);
            break;
        }
        else {
            printw("invalid email please try again\n");
        }
    }
    menu();
}
void sign_in () {
    printw("Enter your username:\n");
    while(1) {
        scanw("%s", player.name);
        FILE* check = fopen(player.name, "r");
        if(check == NULL) {
            printw("username doesn't exist\nplease enter a another username.\n");
            continue;
        }
        break;
    }
    printw("Enter your password:\n");
    while(1) {
        char password[200];
        scanw("%s", password);
        int count = 1;
        FILE* f = fopen(player.name, "r");
        char* pass = (char*)malloc(200);
        char p[200];
        while (1) {
            fgets(p, 200, f);
            if (count == 3) {
                break;
            }
            else {
                count++;
            }
        }
        int flag = 0;
        pass = p;
        pass += 9;
        pass[strlen(pass) - 2] = '\0';
        refresh();
        if(strcmp(pass, password) == 0) {
            flag = 1;
        }
        if(!flag) {
            printw("Wrong password\nplease try again\n");
            continue;
        }
        fclose(f);
        break;
    }
    menu();
}
void menu() {
    clear();        
    mvprintw(20,83, "1:new game");
    mvprintw(21,83, "2:load game");
    mvprintw(22,83, "3:scoreboard");
    mvprintw(23,83, "4:setting");
    mvprintw(24,83, "5:profile");
    refresh();
    while(1) {
        char n = getchar();
        if(n == '1') {clear(); break;}
        else if(n == '2') {clear(); break;} 
        else if(n == '3') {clear(), scoreboard(); break;}
        else if(n == '4') {clear(), setting(); break;}
        else if(n == '5') {clear(); break;}
        else {continue;}
    }
}
void scoreboard() {
    char line[10][300];
    FILE* f = fopen("score", "a");
    if(f == NULL) {
        f = fopen("score", "w");
    }
    fprintf(f, "1.%s\n", player.name);
    attron(A_BOLD);
    fgets(line[0], 300, f);
    printw("%s", line[0]);
    refresh();
    attroff(A_BOLD);


}
void setting() {
    clear();
    mvprintw(0,0, "0:back");
    mvprintw(20,83, "1:Difficulty");
    mvprintw(21,83, "2:character's color");
    mvprintw(22,83, "3:select music");
    refresh();
    while(1) {
        char n = getchar();
        if(n == '1') {
            clear(); 
            mvprintw(0,0, "0:back");
            mvprintw(20,83, "1:easy");
            mvprintw(21,83, "2:medium");
            mvprintw(22,83, "3:hard");
            mvprintw(23,83, "4:miyazaki");
            refresh();
            while(1) {
                char n = getchar();
                if(n == '1') {player.health = 100;}
                else if(n == '2') {player.health = 70;}
                else if(n == '3') {player.health = 50;}
                else if(n == '4') {player.health = 30;}
                else if(n == '0') {break;}
            }
            setting();
            break;
        }
        else if(n == '2') {
            clear();
            mvprintw(0,0, "0:back");
            mvprintw(0,76, "select your character's color");
            mvprintw(20,88, "1:Red");
            mvprintw(21,88, "2:Green");
            mvprintw(22,88, "3:Blue");
            refresh();
            while(1) {
                char n = getchar();
                if(n == '1') {
                    player.color = 1;
                    break;
                }
                else if(n == '2') {
                    player.color = 2;
                    break;
                }
                else if(n == '3') {
                    player.color = 4;
                    break;
                }
                else if(n == '0') {setting();break;}
                else{continue;}
            }
            break;
        } 
        else if(n == '3') {clear(); break;}
        else if(n == '0') {menu();break;}
        else {continue;}
    }

}
void start_game() {

}

void quit() {
    char c;
    while(1) {
       c = getchar();
       if(c == 'q') {
        return;
       }
       else {
        clear();
       }
    }
}