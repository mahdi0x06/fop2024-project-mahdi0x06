#include<stdio.h>
#include<ncurses.h>
#include<stdlib.h>
#include<string.h>
char name[200], pass[200], mail[200];
void sign_up();
void sign_in();
void quit();
void username();
void password();
void email();
int main() {
    initscr();
    start_color();
    if(has_colors() == FALSE){	
        endwin();
	    printf("Your terminal does not support color\n");
	    exit(1);
    }
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    mvprintw(20,83, "enter 1 to sign up");
    mvprintw(21,83, "enter 2 to sign in");
    refresh();
    char onetwo = getchar();
    if(onetwo == '1') {clear(),sign_up();}
    else if(onetwo == '2'){clear(),sign_in();} 
    quit();
    refresh();
    endwin();
    return 0;
}
void username() {
    while(1) {
        scanw(" %s", name);
        FILE* check = fopen(name, "r");
        if((check == NULL) && (strlen(name) >= 7)) {
            FILE* f = fopen(name, "w");
            fprintf(f, "username:%s \n",  name);
            fclose(f);
            return;
        }
        else if((check != NULL) || (strlen(name) < 7)){
            printw("Username has already been taken(at least 7 characters) or it's not long enough\nplease enter a new username\n");
        }
    }
}
void password() {
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
            FILE* f = fopen(pass, "w");
            fprintf(f, "password:%s \n",  pass);
            fclose(f);
            return;
        }
        else if(strlen(pass) < 7) {
            printw("Password is not long enough(at least 7 characters)\nplease enter a new password\n");
        }
        else if(u == 0 || l == 0 || n == 0) {
            printw("Your password should at least contain an upper case and a lower case and a number\nplease enter a new password\n");
        }
    }
}
void email() {
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
            FILE* f = fopen(mail, "a");
            fprintf(f, "email:%s \n",  mail);
            return;
        }
        else {
            printw("invalid email please try again\n");
        }
    }
}
void sign_up() {
    printw("Enter your username:\n");
    username();
    printw("Enter your password:\n");
    password();
    printw("Enter your email:\n");
    email();
}
void sign_in () {
    printw("Enter your username:\n");
    scanw("%s", name);
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