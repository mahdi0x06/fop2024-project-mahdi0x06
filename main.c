#include<stdio.h>
#include<ncurses.h>
#include<stdlib.h>
#include<string.h>
void username(char name[]) {
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
            printw("Username has already been taken or it's not long enough\nplease enter a new username\n");
        }
    }
}
void password(char pass[]) {
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
void email(char mail[]) {
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
int main() {
    char name[200], pass[200], mail[200];
    initscr();
    printw("Enter your username:\n");
    username(name);
    printw("Enter your password:\n");
    password(pass);
    printw("Enter your email:\n");
    email(mail);
    while(1) {
        char c  = getchar();
        if(c == 'q') {
            break;
        }
        else {
            clear();
        }
    }
    refresh();
    endwin();
    return 0;
}