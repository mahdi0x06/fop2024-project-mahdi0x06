//back button
#include<stdio.h>
#include<ncurses.h>
#include<stdlib.h>
#include<string.h>
char name[200], pass[200], mail[200];
void sign_up();
void sign_in();
void quit();
void initialize();
int main() {
    initscr();
    keypad(stdscr, TRUE);
    start_color();
    if(has_colors() == FALSE){	
        endwin();
	    printf("Your terminal does not support color\n");
	    exit(1);
    }
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    initialize();

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
    //mvprintw(50, 50, "0: back");
    FILE* f;
    mvprintw(0, 0,"Enter your username:\n");
    refresh();
    while(1) {
        scanw(" %s", name);
        FILE* check = fopen(name, "r");
        if((check == NULL) && (strlen(name) >= 7)) {
            f = fopen(name, "w");
            fprintf(f, "username:%s \n",  name);
            fclose(f);
            break;
        }
        else if((check != NULL) || (strlen(name) < 7)){
            printw("Username has already been taken(at least 7 characters) or it's not long enough\nplease enter a new username\n");
        }
    }
    printw("Enter your password:\n");
    while(1) {
        scanw(" %s", pass);
        int u = 0, l = 0, n = 0;
        for(int i = 0; pass[i] != '\0'; i++) {
            if('A' <= pass[i] && pass[i] <= 'Z') {
                u = 1;
            }
            else if('a' <= pass[i] && pass[i] <= 'z') {
                l = 1;
            }
            else if('0' <= pass[i] && pass[i] <= '9') {
                n = 1;
            }
        }
        if(strlen(pass) >= 7 && u && l && n) {
            f = fopen(name, "a");
            fprintf(f, "\npassword:%s \n",  pass);
            fclose(f);
            break;
        }
        else if(strlen(pass) < 7) {
            printw("Password is not long enough(at least 7 characters)\nplease enter a new password\n");
        }
        else if(u == 0 || l == 0 || n == 0) {
            printw("Your password should at least contain an upper case and a lower case and a number\nplease enter a new password\n");
        }
    }
    printw("Enter your email:\n");
    while(1) {
        scanw(" %s", mail);
        int ad = 0, dot = 0;
        for(int i = 0; mail[i] != '\0'; i++) {
            if(mail[i] == '@') {
                ad = i;
            }
            else if(mail[i] == '.') {
                dot = i;
            }
        }
        if((ad > 0) && (dot - ad > 1) && (dot + 1 != strlen(mail))) {
            f = fopen(name, "a");
            fprintf(f, "\nemail:%s \n",  mail);
            break;
        }
        else {
            printw("invalid email please try again\n");
        }
    }
    return;
}

void sign_in () {
    char name[200];
    printw("Enter your username:\n");
    while(1) {
        scanw("%s", name);
        FILE* check = fopen(name, "r");
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
        FILE* f = fopen(name, "r");
        char* pass = (char*)malloc(200);
        while (1) {
            fgets(pass, sizeof pass, f);
            if (count == 3) {
                break;
            }
            else {
                count++;
            }
        }
        int flag = 0;
        pass += 9;
        refresh();
        if(strcmp(pass, password) == 0) {
            flag = 1;
        }
        if(!flag) {
            printw("Wrong password\nplease try again\n");
            continue;
        }
        break;
    }
    return;
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