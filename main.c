//46*189
//x:1-32 y:1-179
//back button
//load game
//music
//forgot password
//min doors and pillars 
#include<stdio.h>
#include<ncurses.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <time.h>
#include<stdbool.h>
#include <ncursesw/ncurses.h>
#include <locale.h>
#include <wchar.h>
typedef struct {
    int x, y;
} pos;
pos doors[6], IJ[3];
typedef struct {
    char name[100], pass[100], mail[100], weapon[15];
    int points, score, gold, exp, health, color, x, y, hunger;
} att;
att player;
typedef struct {
    int x, y;
    char c[100][100];
    int pass;
} Room;
Room** room;
typedef struct {
    int x, y, health, damage;
} boss;
boss demon[5], fire[5], giant[5], snake[5], undeed[5];
int mark[46][189];
int floor = 1, T = 0, reg_food = 0; 
int dagger = 0, wand = 0, arrow = 0, sword = 0, mace = 0;
int health = 0, damage = 0, speed = 0, s = 0, d = 0, scount = 0, dcount = 0;
char c1, c2, c3, c4, c5, c6, c7;
int hidden = 0, trap = 0;
char** board1;
char** board2;
char** board3;
char** board4;
int check = 0;
void initialize();
void sign_up();
void sign_in();
void menu();
void scoreboard();
void setting();
void quit();
void input(char, char**, char**);
void create_map(char***);
void print_map(char**);
int check_room(Room**);
void Doors(pos*, char***);
void print_character(int, int, char**, char**);
void save_borad();
void create_board(char***);
void food_list(char**);
void loading(int);
void weapon_list(char**);
void talisman_list(char**);
void enchant();
void boss_init();
void dfs_boss(char**, int*, int*, int, int, int);
int check_dfs(char**, int, int);
int main() {
    setlocale(LC_ALL, "");
    initscr();
    keypad(stdscr, TRUE);
    start_color();
    if(has_colors() == FALSE){	
        endwin();
	    printf("Your terminal does not support color\n");
	    exit(1);
    }
    init_color(COLOR_BLACK, 0, 0, 0);
    init_color(COLOR_RED, 1000, 0, 0);
    init_color(1, 700, 330, 330);
    init_color(19, 500, 0, 700);
    init_color(20, 500, 0, 100);
    init_color(15, 240, 90, 90);
    init_pair(11, COLOR_RED, COLOR_BLACK);
    init_pair(14, 15, COLOR_BLACK);
    init_pair(8, COLOR_GREEN, COLOR_BLACK);
    init_pair(10, COLOR_BLUE, COLOR_BLACK);
    init_pair(9, COLOR_WHITE, COLOR_BLACK);
    init_pair(12, 1, COLOR_BLACK);
    init_pair(13, COLOR_YELLOW, COLOR_BLACK);
    init_pair(15, COLOR_BLACK, COLOR_BLUE);
    init_pair(16, 19, COLOR_BLACK);
    init_pair(17, 20, COLOR_BLACK);
    attron(COLOR_PAIR(8));
    //initialize();
    for(int i = 0; i < 46; i++) {
        for(int j = 0; j < 189; j++) {
            mark[i][j] = 0;
        }
    }
    board1 = (char**)malloc(47 * sizeof(char*));
    for(int i = 0; i <= 50; i++) {
        *(board1 + i) = (char*)malloc(190);
    }
    for(int i = 0; i <= 46; i++) {
        for(int j = 0; j <= 189; j++) {
            board1[i][j] = ' ';
        }
    }    
    board2 = (char**)malloc(47 * sizeof(char*));
    for(int i = 0; i <= 50; i++) {
        *(board2 + i) = (char*)malloc(190);
    }
    for(int i = 0; i <= 46; i++) {
        for(int j = 0; j <= 189; j++) {
            board2[i][j] = ' ';
        }
    }    
    board3 = (char**)malloc(47 * sizeof(char*));
    for(int i = 0; i <= 50; i++) {
        *(board3 + i) = (char*)malloc(190);
    }
    for(int i = 0; i <= 46; i++) {
        for(int j = 0; j <= 189; j++) {
            board3[i][j] = ' ';
        }
    }    
    board4 = (char**)malloc(47 * sizeof(char*));
    for(int i = 0; i <= 50; i++) {
        *(board4 + i) = (char*)malloc(190);
    }
    for(int i = 0; i <= 46; i++) {
        for(int j = 0; j <= 189; j++) {
            board4[i][j] = ' ';
        }
    }
    room = (Room**)malloc(5 * sizeof(Room*));
    for(int i = 0; i < 6; i++) {
        *(room + i) = (Room*)malloc(6 * sizeof(Room));
    }
    for(int i = 1; i <= 4; i++) {
        room[i][4].pass = 0;
    }
    boss_init();
    loading(floor);
    create_map(&board1);
    napms(1000);
    floor++; 
    loading(floor);
    create_map(&board2);
    napms(1000);
    floor++;  
    loading(floor);
    create_map(&board3);
    napms(1000);
    floor++;  
    loading(floor);
    create_map(&board4);
    napms(500);
    floor = 1;
    print_map(board1); 
    player.health = 900;
    player.hunger = 200;
    player.gold = 0;
    strcpy(player.weapon, "mace");
    player.score = 0;
    while(1) {
        mvprintw(0,184, "0:quit");
        refresh();
        char c;
        mvprintw(46, 0, "HP:");
        mvprintw(46, 9, "Gold:%d", player.gold);
        if(1000 <= player.health) {
            mvprintw(46, 3, "%d", player.health);
        }
        else if(100 <= player.health && player.health <= 999) {
            mvprintw(46, 3, " %d", player.health);
        }
        else if(10 <= player.health && player.health <= 99) {
            mvprintw(46, 3, "  %d", player.health);
        }
        else {
            mvprintw(46, 3, "   %d", player.health);
        }
        if(player.health <= 0) {
            clear();
            mvprintw(21, 86, "GAME OVER!!");
            refresh();
            getchar();
            break;
        }
        if(player.hunger <= 0) {
            player.health -= 10;
            player.hunger = 0;
        }
        mvprintw(2, 0, "%d", s);
        if(s == 1 && scount != 10 ) {
            scount++;
        }
        else {
            s = 0;
            scount = 0;
        }
        if(d == 1 && dcount != 10 ) {
            dcount++;
        }
        else {
            d = 0;
            dcount = 0;
        }
        c = getchar();
        if(c == '0') {quit(); break;}
        switch (floor)
        {
        case 1:
            input(c, board1, board2);
            break;
        case 2:
            input(c, board2, board3);
            break;
        case 3:
            input(c, board3, board4);
            break;
        case 4:
            input(c, board4, board4);
            break;
        }
    }
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
        if(n == '1') {
            clear();
            sign_up();
            break;
        }
        else if(n == '2') {
            clear();
            sign_in();
            break;
        } 
        else if(n == '3') {
            clear();
            break;
        }
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
            if(player.mail[i] == 'H') {
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
        if(n == '1') {
            clear();
            break;
        }
        else if(n == '2') {
            clear();
            break;
        } 
        else if(n == '3') {
            clear();
            scoreboard();
            break;
        }
        else if(n == '4') {
            clear();
            setting();
            break;
        }
        else if(n == '5') {
            clear();
            break;
        }
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
                if(n == '1') {player.health = 900;}
                else if(n == '2') {player.health = 700;}
                else if(n == '3') {player.health = 500;}
                else if(n == '4') {player.health = 300;}
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
                else if(n == '0') {
                    setting();
                    break;
                }
                else{continue;}
            }
            break;
        } 
        else if(n == '3') {
            clear(); 
            break;
        }
        else if(n == '0') {
            menu();
            break;
        }
        else {continue;}
    }

}

void create_map(char*** board) {
    srand(time(NULL));
    for(int i = 0; i < 6; i++) {
        if(floor == 2 && i == 0) {
            room[floor][0].x = room[floor - 1][0].x;
            room[floor][0].y = room[floor - 1][0].y;
            continue;
        }
        else if(floor == 3 && i == 1) {
            room[floor][1].x = room[floor - 1][1].x;
            room[floor][1].y = room[floor - 1][1].y;
            continue;
        }
        else if(floor == 4 && i == 2) {
            room[floor][2].x = room[floor - 1][2].x;
            room[floor][2].y = room[floor - 1][2].y;
            continue;
        }
        room[floor][i].x = rand() % (35) + 3;
        room[floor][i].y = rand() % (158) + 16;
    }
    int x = check_room(room);
    while(x == 0) {
        for(int i = 0; i < 6; i++) {
            if(floor == 2 && i == 0) {
                continue;
            }
            else if(floor == 3 && i == 1) {
                continue;
            }
            else if(floor == 4 && i == 2) {
                continue;
            }
            room[floor][i].x = rand() % (35) + 3;
            room[floor][i].y = rand() % (158) + 16;
        }
        x = check_room(room);
    }
    srand(time(NULL));
    int nfood = rand() % (4) + 3;
    int ngold = rand() % (4) + 3;
    for(int i = 0; i < 6; i++) {
        int I = rand() % (5) + 6;
        int J = rand() % (7) + 6;
        int x = rand() % (2) + 1;
        int X = rand() % (I - 2) + room[floor][i].x + 1;
        int Y = rand () % (J - 2) + room[floor][i].y + 1;
        int food_x = rand() % (I - 2) + room[floor][i].x + 1;
        int gold_x = rand() % (I - 2) + room[floor][i].x + 1;
        int door;
        if(floor == 1 && i == 0) {
            IJ[0].x = I;
            IJ[0].y = J;
        }
        else if(floor == 2 && i == 1) {
            IJ[1].x = I;
            IJ[1].y = J;
        }
        else if(floor == 3 && i == 2) {
            IJ[2].x = I;
            IJ[2].y = J;
        }
        if(floor == 2 && i == 0) {
            I = IJ[0].x;
            J = IJ[0].y;
        }
        else if(floor == 3 && i == 1) {
            I = IJ[1].x;
            J = IJ[1].y;
        }
        else if(floor == 4 && i == 2) {
            I = IJ[2].x;
            J = IJ[2].y;
        }
        if(x == 1) {
            door = rand() % (I) + room[floor][i].x;
        }
        else {
            door = rand () % (J) + room[floor][i].y;
        }
        while (abs(door - X) < 1 || abs(door - Y) < 1) {
            if(x == 1) {
                door = rand() % (I) + room[floor][i].x;
            }
            else {
                door = rand () % (J) + room[floor][i].y;
            }
        }
        if(floor == 1 && i == 1) {
            player.x = X;
            player.y = Y + 1;
        }
        for(int j = room[floor][i].x; j < room[floor][i].x + I; j++) {
            for(int q = room[floor][i].y; q < room[floor][i].y + J; q++) {
                if(j == X && q == Y) {
                    (*board)[j][q] = 'O';
                    room[floor][i].c[j][q] = 'O';
                    continue;
                }
                else if(floor == 2 && i == 1 && j == X + 1 && q == Y + 1) {
                    (*board)[j][q] = '<';
                    room[floor][i].c[j][q] = '<';
                    continue;
                }
                else if(floor == 3 && i == 2 && j == X + 1 && q == Y + 1) {
                    (*board)[j][q] = '<';
                    room[floor][i].c[j][q] = '<';
                    continue;
                }
                else if(floor == 1 && i == 0 && j == X + 1 && q == Y + 1) {
                    (*board)[j][q] = '<';
                    room[floor][i].c[j][q] = '<';
                    continue;
                }
                else if(i == 5 && j == room[floor][i].x + I - 1 && q == room[floor][i].y) {
                    (*board)[j][q] = '?';
                    room[floor][i].c[j][q] = '?';
                    continue;
                }
                else if(i == 5 && j == room[floor][i].x + I - 1 && q == room[floor][i].y + 2) {
                    (*board)[j][q] = 'd';
                    room[floor][i].c[j][q] = 'd';
                    continue;
                }
                else if(i == 4 && j == room[floor][i].x + I - 1 && q == room[floor][i].y + 1) {
                    (*board)[j][q] = 'a';
                    room[floor][i].c[j][q] = 'a';
                    continue;
                }
                else if(i == 3 && j == room[floor][i].x + I - 1 && q == room[floor][i].y + 3) {
                    (*board)[j][q] = 'm';
                    room[floor][i].c[j][q] = 'm';
                    continue;
                }
                else if(i == 1 && j == room[floor][i].x + I - 1 && q == room[floor][i].y + 5) {
                    (*board)[j][q] = 'e';
                    room[floor][i].c[j][q] = 'e';
                    demon[floor].x = j;
                    demon[floor].y = q;
                    continue;
                }
                else if(i == 2 && j == room[floor][i].x + I - 1 && q == room[floor][i].y + 4) {
                    (*board)[j][q] = 'f';
                    room[floor][i].c[j][q] = 'f';
                    fire[floor].x = j;
                    fire[floor].y = q;
                    continue;
                }
                else if(i == 3 && j == room[floor][i].x + I - 1 && q == room[floor][i].y + 4) {
                    (*board)[j][q] = 'i';
                    room[floor][i].c[j][q] = 'i';
                    giant[floor].x = j;
                    giant[floor].y = q;
                    continue;
                }
                else if(i == 4 && j == room[floor][i].x + I - 1 && q == room[floor][i].y + 4) {
                    (*board)[j][q] = 'n';
                    room[floor][i].c[j][q] = 'n';
                    snake[floor].x = j;
                    snake[floor].y = q;
                    continue;
                }
                else if(i == 5 && j == room[floor][i].x + I - 1 && q == room[floor][i].y + 4) {
                    (*board)[j][q] = 'u';
                    room[floor][i].c[j][q] = 'u';
                    undeed[floor].x = j;
                    undeed[floor].y = q;
                    continue;
                }
                else if(i == 2 && j == room[floor][i].x + I - 1 && q == room[floor][i].y + 3 && floor == 2) {
                    (*board)[j][q] = 's';
                    room[floor][i].c[j][q] = 's';
                    continue;
                }
                else if(i == 1 && j == room[floor][i].x + I - 1 && q == room[floor][i].y + 3) {
                    (*board)[j][q] = 'h';
                    room[floor][i].c[j][q] = 'h';
                    continue;
                }
                else if(i == 0 && j == room[floor][i].x + I - 1 && q == room[floor][i].y + 2 && (floor == 2 || floor == 3 || floor == 4)) {
                    (*board)[j][q] = 'S';
                    room[floor][i].c[j][q] = 'S';
                    continue;
                }
                else if(i == 3 && j == room[floor][i].x + I - 1 && q == room[floor][i].y + 2 && (floor == 3 || floor == 4)) {
                    (*board)[j][q] = 'D';
                    room[floor][i].c[j][q] = 'D';
                    continue;
                }
                else if(j == X - 1 && q == Y) {
                    (*board)[j][q] = '^';
                    room[floor][i].c[j][q] = '.';
                    refresh();
                    continue;
                }
                else if(j == X - 1 && q == Y + 1 && i == 4) {
                    (*board)[j][q] = '@';
                    room[floor][i].c[j][q] = '@';
                    attron(COLOR_PAIR(8));
                    refresh();
                    continue;
                }
                else if(j == room[floor][i].x + I - 1 && q == room[floor][i].y + J - 1 && i == 4) {
                    (*board)[j][q] = '&';
                    room[floor][i].c[j][q] = '&';
                    attron(COLOR_PAIR(8));
                    refresh();
                    continue;
                }
                else if(j == room[floor][i].x && q == room[floor][i].y + J - 1 && i == 1) {
                    (*board)[j][q] = 'T';
                    room[floor][i].c[j][q] = 'T';
                    attron(COLOR_PAIR(8));
                    refresh();
                    continue;
                }
                (*board)[j][q] = '.';
                room[floor][i].c[j][q] = '.';
                refresh();
            }
        }
        if(nfood) {
            if((*board)[food_x][J + room[floor][i].y - 1] != 'T' && (*board)[food_x][J + room[floor][i].y - 1] != '@' && (*board)[food_x][J + room[floor][i].y - 1] != '&' && (*board)[gold_x][room[floor][i].y] != '<' && (*board)[gold_x - 1][room[floor][i].y] != '+') {
                (*board)[food_x][J + room[floor][i].y - 1] = 'F';
                nfood--;
            }
        }
        if(ngold) {
            if((*board)[gold_x][room[floor][i].y] != 'T' && (*board)[gold_x][room[floor][i].y] != '@' && (*board)[gold_x][room[floor][i].y] != '&' && (*board)[gold_x][room[floor][i].y] != '<') {
                (*board)[gold_x][room[floor][i].y] = 'G';
                ngold--;
            }
        }
        if((*board)[gold_x][room[floor][i].y] != 'T' && (*board)[gold_x][room[floor][i].y] != '@' && (*board)[gold_x][room[floor][i].y] != '&' && (*board)[gold_x][room[floor][i].y] != '<' && floor == 3 && i == 3) {
                (*board)[gold_x][room[floor][i].y] = 'g';
            }
        for(int j = room[floor][i].y; j < room[floor][i].y + J; j++) {
            if(x == 2 && door == j) {
                (*board)[room[floor][i].x - 1][j] = '+';
                room[floor][i].c[room[floor][i].x][j] = '+';
                (*board)[room[floor][i].x + I][j] = '_';
                room[floor][i].c[room[floor][i].x + I][j] = '_';
                doors[i].x = room[floor][i].x - 1;
                doors[i].y = j;
                continue;
            }
            (*board)[room[floor][i].x - 1][j] = '_';
            room[floor][i].c[room[floor][i].x][j] = '_';
            (*board)[room[floor][i].x + I][j] = '_';
            room[floor][i].c[room[floor][i].x + I][j] = '_';
        }
        for(int j = room[floor][i].x; j < room[floor][i].x + I; j++) {
            if(x == 1 && door == j) {
                (*board)[j][room[floor][i].y - 1] = '+';
                room[floor][i].c[j][room[floor][i].y] = '+';
                (*board)[j][room[floor][i].y + J] = '|';
                room[floor][i].c[j][room[floor][i].y + J] = '|';
                doors[i].x = j;
                doors[i].y = room[floor][i].y - 1;
                continue;
            }
                (*board)[j][room[floor][i].y - 1] = '|';
                room[floor][i].c[j][room[floor][i].y] = '|';
                (*board)[j][room[floor][i].y + J] = '|';
                room[floor][i].c[j][room[floor][i].y + J] = '|';
        }
    }
    Doors(doors, board);
}

int check_room(Room** room) {
    for(int i = 0; i < 5; i++) {
        for(int j = i + 1; j < 6; j++) {
            if(abs(room[floor][i].y - room[floor][j].y) <= 18 ) {
                return 0;
            }
        }
    }
    return 1;
}

void print_map(char** board) {
    clear();
    for(int i = 0; i <= 46; i++) {
        for(int j = 0; j <= 189; j++) {
            if(board[i][j] == '<') {
                attron(COLOR_PAIR(12));
                mvprintw(i, j, "%c", board[i][j]);
                refresh();
                attroff(COLOR_PAIR(12));
            }
            else if(board[i][j] == '&') {
                attron(COLOR_PAIR(9));
                mvprintw(i, j, "%c", board[i][j]);
                refresh();
                attroff(COLOR_PAIR(9));
            }
            else if(board[i][j] == '@') {
                attron(COLOR_PAIR(11));
                mvprintw(i, j, "%c", board[i][j]);
                refresh();
                attroff(COLOR_PAIR(11));
            }
            else if(board[i][j] == '^') {
                attron(COLOR_PAIR(8));
                mvprintw(i, j, ".");
                refresh();
                attroff(COLOR_PAIR(8));            
            }
            else if(board[i][j] == 'T') {
                attron(COLOR_PAIR(13));
                mvaddstr(i, j, "\U000025B2");
                attroff(COLOR_PAIR(13));
            }
            else if(board[i][j] == '#') {
                attron(COLOR_PAIR(9));
                mvprintw(i, j, "#");
                attroff(COLOR_PAIR(9));
            }
            else if(board[i][j] == '_') {
                attron(COLOR_PAIR(14));
                mvprintw(i, j, "_");
                attroff(COLOR_PAIR(14));
            }
            else if(board[i][j] == '|') {
                attron(COLOR_PAIR(14));
                mvprintw(i, j, "|");
                attroff(COLOR_PAIR(14));
            }
            else if(board[i][j] == 'F') {
                attron(COLOR_PAIR(8));
                mvaddstr(i, j, "\U000101DB");
                refresh();
                attroff(COLOR_PAIR(8));
            }
            else if(board[i][j] == 'G') {
                attron(COLOR_PAIR(13));
                mvaddstr(i, j, "\U000020BF");
                refresh();
                attroff(COLOR_PAIR(13));
            }
            else if(board[i][j] == 'g') {
                attron(COLOR_PAIR(15));
                mvaddstr(i, j, "\U000020AC");
                refresh();
                attroff(COLOR_PAIR(15));
            }
            else if(board[i][j] == 'a') {
                attron(COLOR_PAIR(9));
                mvaddstr(i, j, "\U000027B3");
                refresh();
                attroff(COLOR_PAIR(9));
            }
            else if(board[i][j] == 'm') {
                attron(COLOR_PAIR(9));
                mvaddstr(i, j, "\U00002133");
                refresh();
                attroff(COLOR_PAIR(9));
            }
            else if(board[i][j] == 'd') {
                attron(COLOR_PAIR(9));
                mvaddstr(i, j, "\U0001F5E1");
                refresh();
                attroff(COLOR_PAIR(9));
            }
            else if(board[i][j] == 's') {
                attron(COLOR_PAIR(9));
                mvaddstr(i, j, "\U00002694");
                refresh();
                attroff(COLOR_PAIR(9));
            }
            else if(board[i][j] == 'h') {
                attron(COLOR_PAIR(16));
                mvaddstr(i, j, "\U00002671");
                refresh();
                attroff(COLOR_PAIR(16));
            }
            else if(board[i][j] == 'S') {
                attron(COLOR_PAIR(16));
                mvaddstr(i, j, "\U0001F6E6");
                refresh();
                attroff(COLOR_PAIR(16));
            }
            else if(board[i][j] == 'D') {
                attron(COLOR_PAIR(16));
                mvaddstr(i, j, "\U00002622");
                refresh();
                attroff(COLOR_PAIR(16));
            }
            else if(board[i][j] == 'e') {
                attron(COLOR_PAIR(17));
                mvprintw(i, j, "D");
                refresh();
                attroff(COLOR_PAIR(17));
            }
            else if(board[i][j] == 'f') {
                attron(COLOR_PAIR(17));
                mvprintw(i, j, "F");
                refresh();
                attroff(COLOR_PAIR(17));
            }
            else if(board[i][j] == 'i') {
                attron(COLOR_PAIR(17));
                mvprintw(i, j, "G");
                refresh();
                attroff(COLOR_PAIR(17));
            }
            else if(board[i][j] == 'n') {
                attron(COLOR_PAIR(17));
                mvprintw(i, j, "S");
                refresh();
                attroff(COLOR_PAIR(17));
            }
            else if(board[i][j] == 'u') {
                attron(COLOR_PAIR(17));
                mvprintw(i, j, "U");
                refresh();
                attroff(COLOR_PAIR(17));
            }
            else if(board[i][j] == '?') {
                if(hidden) {
                    attron(COLOR_PAIR(16));
                    mvaddstr(i, j, "?");
                    refresh();
                    attroff(COLOR_PAIR(16));
                }
                else {
                    attron(COLOR_PAIR(8));
                    mvaddstr(i, j, ".");
                    refresh();
                    attroff(COLOR_PAIR(8));  
                }
            }
            else {
                attron(COLOR_PAIR(8));
                mvprintw(i, j, "%c", board[i][j]);
                refresh();
                attroff(COLOR_PAIR(8));
            }
        }
    }
    attron(COLOR_PAIR(10));
    mvprintw(player.x, player.y, "H"); 
    attroff(COLOR_PAIR(10));
    refresh();
}

void Doors(pos* doors, char*** board) {
    for(int i = 0; i < 6; i++) {
        int p = i;
        pos temp;
        temp.x = doors[p].x;
        temp.y = doors[p].y;
        if((*board)[temp.x - 1][temp.y] == ' ') {
            temp.x = temp.x - 1;
            (*board)[temp.x][temp.y] = '#';
            refresh();
        }
        
        else if((*board)[temp.x][temp.y - 1] == ' ') {
            temp.y = temp.y - 1;
            (*board)[temp.x][temp.y] = '#';
            refresh();
        }
        if(i == 5) {p = -1;}
        while (1) {
            while(temp.x < doors[p + 1].x) {
                if(temp.x == doors[p + 1].x && temp.y + 1 == doors[p + 1].y) {
                    break;
                }
                else if(temp.x + 1 == doors[p + 1].x && temp.y == doors[p + 1].y) {
                    break;
                }
                else if(temp.x == doors[p + 1].x && temp.y - 1 == doors[p + 1].y) {
                    break;
                }
                else if(temp.x - 1 == doors[p + 1].x && temp.y == doors[p + 1].y) {
                    break;
                }
                if(((*board)[temp.x + 1][temp.y] == ' ') || ((*board)[temp.x + 1][temp.y] == '#')) {
                    refresh();
                    temp.x++;
                    (*board)[temp.x][temp.y] = '#';
                    continue;
                }
                else if(((*board)[temp.x][temp.y - 1] == ' ') || ((*board)[temp.x][temp.y - 1] == '#')) {
                    refresh();
                    temp.y--;
                    (*board)[temp.x][temp.y] = '#';
                    continue;
                }
                else if(((*board)[temp.x][temp.y + 1] == ' ') || ((*board)[temp.x][temp.y + 1] == '#')) {
                    refresh();
                    temp.y++;
                    (*board)[temp.x][temp.y] = '#';
                    continue;
                }
                else if(((*board)[temp.x - 1][temp.y] == ' ') || ((*board)[temp.x - 1][temp.y] == '#')) {
                    refresh();
                    temp.x--;
                    (*board)[temp.x][temp.y] = '#';
                    continue;
                }
            }
            while(temp.x > doors[p + 1].x) {
                if(temp.x == doors[p + 1].x && temp.y + 1 == doors[p + 1].y) {
                    break;
                }
                else if(temp.x + 1 == doors[p + 1].x && temp.y == doors[p + 1].y) {
                    break;
                }
                else if(temp.x == doors[p + 1].x && temp.y - 1 == doors[p + 1].y) {
                    break;
                }
                else if(temp.x - 1 == doors[p + 1].x && temp.y == doors[p + 1].y) {
                    break;
                }
                if(((*board)[temp.x - 1][temp.y] == ' ') || ((*board)[temp.x - 1][temp.y] == '#')) {
                    refresh();
                    temp.x--;
                    (*board)[temp.x][temp.y] = '#';
                    continue;
                }
                else if(((*board)[temp.x][temp.y - 1] == ' ') || ((*board)[temp.x][temp.y - 1] == '#')) {
                    refresh();
                    temp.y--;
                    (*board)[temp.x][temp.y] = '#';
                    continue;
                }
                else if(((*board)[temp.x + 1][temp.y] == ' ') || ((*board)[temp.x + 1][temp.y] == '#')) {
                    refresh();
                    temp.x++;
                    (*board)[temp.x][temp.y] = '#';
                    continue;
                }
                else if(((*board)[temp.x][temp.y + 1] == ' ') || ((*board)[temp.x][temp.y + 1] == '#')) {
                    refresh();
                    temp.y++;
                    (*board)[temp.x][temp.y] = '#';
                    continue;
                }
            }
            while(temp.y < doors[p + 1].y) {
                if(temp.x == doors[p + 1].x && temp.y + 1 == doors[p + 1].y) {
                    break;
                }
                else if(temp.x + 1 == doors[p + 1].x && temp.y == doors[p + 1].y) {
                    break;
                }
                else if(temp.x == doors[p + 1].x && temp.y - 1 == doors[p + 1].y) {
                    break;
                }
                else if(temp.x - 1 == doors[p + 1].x && temp.y == doors[p + 1].y) {
                    break;
                }
                if(((*board)[temp.x][temp.y + 1] == ' ') || ((*board)[temp.x][temp.y + 1] == '#')) {
                    refresh();
                    temp.y++;
                    (*board)[temp.x][temp.y] = '#';
                    continue;
                }
                else if(((*board)[temp.x - 1][temp.y] == ' ') || ((*board)[temp.x - 1][temp.y] == '#')) {
                    refresh();
                    temp.x--;
                    (*board)[temp.x][temp.y] = '#';
                    continue;
                }
                else if(((*board)[temp.x + 1][temp.y] == ' ') || ((*board)[temp.x + 1][temp.y] == '#')) {
                    refresh();
                    temp.x++;
                    (*board)[temp.x][temp.y] = '#';
                    continue;
                }
                else if(((*board)[temp.x][temp.y - 1] == ' ') || ((*board)[temp.x][temp.y - 1] == '#')) {
                    refresh();
                    temp.y--;
                    (*board)[temp.x][temp.y] = '#';
                    continue;
                }
            }
            while(temp.y > doors[p + 1].y) {
                if(temp.x == doors[p + 1].x && temp.y + 1 == doors[p + 1].y) {
                    break;
                }
                else if(temp.x + 1 == doors[p + 1].x && temp.y == doors[p + 1].y) {
                    break;
                }
                else if(temp.x == doors[p + 1].x && temp.y - 1 == doors[p + 1].y) {
                    break;
                }
                else if(temp.x - 1 == doors[p + 1].x && temp.y == doors[p + 1].y) {
                    break;
                }
                if(((*board)[temp.x][temp.y - 1] == ' ') || ((*board)[temp.x][temp.y - 1] == '#')) {
                    refresh();
                    temp.y--;
                    (*board)[temp.x][temp.y] = '#';
                    continue;
                }
                else if(((*board)[temp.x - 1][temp.y] == ' ') || ((*board)[temp.x - 1][temp.y] == '#')) {
                    refresh();
                    temp.x--;
                    (*board)[temp.x][temp.y] = '#';
                    continue;
                }
                else if(((*board)[temp.x + 1][temp.y] == ' ') || ((*board)[temp.x + 1][temp.y] == '#')) {
                    refresh();
                    temp.x++;
                    (*board)[temp.x][temp.y] = '#';
                    continue;
                }
                else if(((*board)[temp.x][temp.y + 1] == ' ') || ((*board)[temp.x][temp.y + 1] == '#')) {
                    refresh();
                    temp.y++;
                    (*board)[temp.x][temp.y] = '#';
                    continue;
                }
            }
            if(temp.x == doors[p + 1].x && temp.y + 1 == doors[p + 1].y) {
                move(temp.x, temp.y + 1);
                break;
            }
            else if(temp.x + 1 == doors[p + 1].x && temp.y == doors[p + 1].y) {
                move(temp.x + 1, temp.y);
                break;
            }
            else if(temp.x == doors[p + 1].x && temp.y - 1 == doors[p + 1].y) {
                move(temp.x, temp.y - 1);
                break;
            }
            else if(temp.x - 1 == doors[p + 1].x && temp.y == doors[p + 1].y) {
                move(temp.x - 1, temp.y);
                break;
            }
        }
    }
}

void input(char c, char** board, char** next_board) {
    int x = player.x , y = player.y;
    switch (c) {
        case 't':
            talisman_list(board);
            break;
        case 'i':
            weapon_list(board);
            break;
        case 'E':
            food_list(board);
            break;
        case 'w': 
            if(s) {
                player.x -= 2;
            }
            else {
                player.x--;
            }
            print_character(x, y, board, next_board);
            break;
        case 's':
            if(s) {
                player.x += 2;
            }
            else {
                player.x++;
            }
            print_character(x, y, board, next_board);
            break;
        case 'a':
            if(s) {
                player.y -= 2;
            }
            else {
                player.y--;
            }
            print_character(x, y, board, next_board);
            break;
        case 'd':
            if(s) {
                player.y += 2;
            }
            else {
                player.y++;
            }
            print_character(x, y, board, next_board);
            break;
        case 'e':
            if(s) {
                player.x -= 2;
                player.y += 2;
            }
            else {
                player.x--;
                player.y++;
            }
            print_character(x, y, board, next_board);
            break;
        case 'q':
            if(s) {
                player.x -= 2;
                player.y -= 2;
            }
            else {
                player.x--;
                player.y--;
            }
            print_character(x, y, board, next_board);
            break;
        case 'z':
            if(s) {
                player.x += 2;
                player.y -= 2;
            }
            else {
                player.x++;
                player.y--;
            }
            print_character(x, y, board, next_board);
            break;
        case 'x':
            if(s) {
                player.x += 2;
                player.y += 2;
            }
            else {
                player.x++;
                player.y++;
            }
            print_character(x, y, board, next_board);
            break;
        case 'f':
            char c = getchar();
            if(c == 'w') {
                while(board[player.x - 1][player.y] != ' ' && board[player.x - 1][player.y] != '_' && board[player.x - 1][player.y] != '|' && board[player.x - 1][player.y] != 'O') {
                    player.x--;
                    player.hunger--;
                }
            }
            else if(c == 's') {
                while(board[player.x + 1][player.y] != ' ' && board[player.x + 1][player.y] != '_' && board[player.x + 1][player.y] != '|' && board[player.x + 1][player.y] != 'O') {
                    player.x++;
                    player.hunger--;
                }
            }
            else if(c == 'a') {
                while(board[player.x][player.y - 1] != ' ' && board[player.x][player.y - 1] != '_' && board[player.x][player.y - 1] != '|' && board[player.x][player.y - 1] != 'O') {
                    player.y--;
                    player.hunger--;
                }
            }
            else if(c == 'd') {
                while(board[player.x][player.y + 1] != ' ' && board[player.x][player.y + 1] != '_' && board[player.x][player.y + 1] != '|' && board[player.x][player.y + 1] != 'O') {
                    player.y++;
                    player.hunger--;
                }
            }
            if(board[x][y] == '.') {
                attron(COLOR_PAIR(8));
                mvprintw(x, y, ".");
                attroff(COLOR_PAIR(8));
            }
            else if(board[x][y] == '#') {
                attron(COLOR_PAIR(9));
                mvprintw(x, y, "#");
                attroff(COLOR_PAIR(9));
            }
            else if(board[x][y] == '+') {
                attron(COLOR_PAIR(8));
                mvprintw(x, y, "+");
                attroff(COLOR_PAIR(8));
            }
            else if(board[x][y] == 'T') {
                attron(COLOR_PAIR(8));
                mvprintw(x, y, ".");
                attroff(COLOR_PAIR(8));
            }
            print_character(x, y, board, next_board);
            break;
        // case 'g':
        //     char cc = getchar();
        //     if(cc == 'w') {
        //         mvprintw(2,0,"w");
        //         while(board[player.x - 1][player.y] != ' ' && board[player.x - 1][player.y] != '_' && board[player.x - 1][player.y] != '|' && board[player.x - 1][player.y] != 'O') {
        //             player.x--;
        //         }
        //     }
        //     else if(cc == 's') {
        //         mvprintw(2,0,"s");
        //         while(board[player.x + 1][player.y] != ' ' && board[player.x + 1][player.y] != '_' && board[player.x + 1][player.y] != '|' && board[player.x + 1][player.y] != 'O') {
        //             player.x++;
        //         }
        //     }
        //     else if(cc == 'a') {
        //         mvprintw(2,0,"a");
        //         while(board[player.x][player.y - 1] != ' ' && board[player.x][player.y - 1] != '_' && board[player.x][player.y - 1] != '|' && board[player.x][player.y - 1] != 'O') {
        //             player.y--;
        //         }
        //     }
        //     else if(cc == 'd') {
        //         while(board[player.x][player.y + 1] != ' ' && board[player.x][player.y + 1] != '_' && board[player.x][player.y + 1] != '|' && board[player.x][player.y + 1] != 'O') {
        //         mvprintw(2,0,"d");
        //             player.y++;
        //         }
        //     }
        //     if(board[x][y] == '.') {
        //     attron(COLOR_PAIR(8));
        //     mvprintw(x, y, ".");
        //     attroff(COLOR_PAIR(8));
        //     }
        //     if(board[x][y] == '#') {
        //     attron(COLOR_PAIR(9));
        //     mvprintw(x, y, "#");
        //     attroff(COLOR_PAIR(9));
        //     }
        //     print_character(x, y, board, next_board);
        //     break;
        case 'S':
            mvprintw(x + 1, y, "%c", board[x + 1][y]);
            mvprintw(x + 1, y - 1, "%c", board[x + 1][y - 1]);
            mvprintw(x + 1, y + 1, "%c", board[x + 1][y + 1]);
            mvprintw(x, y - 1, "%c", board[x][y - 1]);
            mvprintw(x, y + 1, "%c", board[x][y + 1]);
            mvprintw(x - 1, y, "%c", board[x - 1][y]);
            mvprintw(x - 1, y + 1, "%c", board[x - 1][y + 1]);
            mvprintw(x - 1, y - 1, "%c", board[x - 1][y - 1]);
            refresh();
            break;
        default:
            break;
    }
}

void print_character(int ox, int oy, char** board, char** next_board) {
    switch (board[player.x][player.y]) {
        case '?':
            enchant();
            hidden = 1;
            if(board[ox][oy] == '.') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            break;
        case 'h':
            attron(COLOR_PAIR(8));
            mvprintw(ox, oy, ".");
            attroff(COLOR_PAIR(8));
            attron(COLOR_PAIR(10));
            mvprintw(player.x, player.y, "H"); 
            attroff(COLOR_PAIR(10));
            refresh();
            c1 = getchar();
            if(c1 == 'p') {
                health++;
            }
            break;

        case 'S':
            attron(COLOR_PAIR(8));
            mvprintw(ox, oy, ".");
            attroff(COLOR_PAIR(8));
            attron(COLOR_PAIR(10));
            mvprintw(player.x, player.y, "H"); 
            attroff(COLOR_PAIR(10));
            refresh();
            c2 = getchar();
            if(c2 == 'p') {
                speed++;
            }
            break;
        case 'D':
            if(board[ox][oy] == '.' || board[ox][oy] == 'm') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            c3 = getchar();
            if(c3 == 'p') {
                damage++;
            }
            break;
            
        case 'a':
            if(board[ox][oy] == 'g' || board[ox][oy] == 'G' || board[ox][oy] == '.') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            c4 = getchar();
            if(c4 == 'p') {
                arrow += 20;
            }
            break;
        case 'm':
            if(board[ox][oy] == 'g' || board[ox][oy] == 'G' || board[ox][oy] == '.') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            c5 = getchar();
            if(c5 == 'p') {
                wand += 8;
            }
            break;
        case 'd':
            if(board[ox][oy] == 'g' || board[ox][oy] == 'G' || board[ox][oy] == '.') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            c6 = getchar();
            if(c6 == 'p') {
                dagger += 10;
            }
            break;
        case 's':
            if(board[ox][oy] == 'g' || board[ox][oy] == 'G' || board[ox][oy] == '.') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            c7 = getchar();
            if(c7 == 'p') {
                sword++;
            }
            
            break;
        case 'g':
            if(board[ox][oy] == '.') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == '#') {
                attron(COLOR_PAIR(9));
                mvprintw(ox, oy, "#");
                attroff(COLOR_PAIR(9));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == '+') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, "+");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == '^') {
                attron(COLOR_PAIR(11));
                mvprintw(ox, oy, "^");
                attroff(COLOR_PAIR(11));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            srand(time(NULL));
            int g = rand() % (41) + 10;
            mvprintw(0, 0, "               ");
            mvprintw(0, 0, "gold+%d", g);
            player.gold += g;
            break;
        case 'G':
            if(board[ox][oy] == '.') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == '#') {
                attron(COLOR_PAIR(9));
                mvprintw(ox, oy, "#");
                attroff(COLOR_PAIR(9));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == '+') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, "+");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == '^') {
                attron(COLOR_PAIR(11));
                mvprintw(ox, oy, "^");
                attroff(COLOR_PAIR(11));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            srand(time(NULL));
            int G = rand() % (5) + 1;
            mvprintw(0, 0, "               ");
            mvprintw(0, 0, "gold+%d", G);
            player.gold += G;
            break;
        case 'F':
            player.hunger--;
            if(board[ox][oy] == '.') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == '^') {
                attron(COLOR_PAIR(11));
                mvprintw(ox, oy, "^");
                attroff(COLOR_PAIR(11));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'T') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == '+') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, "+");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            reg_food++;
            break;
        case '#':
            player.hunger--;
            if(board[ox][oy] == '+') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, "+");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == '#') {
                attron(COLOR_PAIR(9));
                mvprintw(ox, oy, "#");
                attroff(COLOR_PAIR(9));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == '.') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            break;
        case ' ':
            player.x = ox;
            player.y = oy;   
            break;
        case '.':
            player.hunger--;
            if(board[ox][oy] == '.') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == '+') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, "+");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == '^') {
                attron(COLOR_PAIR(11));
                mvprintw(ox, oy, "^");
                attroff(COLOR_PAIR(11));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == '&') {
                attron(COLOR_PAIR(9));
                mvprintw(ox, oy, "&");
                attroff(COLOR_PAIR(9));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'T') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                board[ox][oy] = '.';
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == '@') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, "@");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'F') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                board[ox][oy] = '.';
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == '#') {
                attron(COLOR_PAIR(9));
                mvprintw(ox, oy, "#");
                attroff(COLOR_PAIR(9));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'G' || board[ox][oy] == 'g') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                board[ox][oy] = '.';
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
                
            }
            else if(board[ox][oy] == 'h') {
                if(c1 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    board[ox][oy] = '.';
                    attroff(COLOR_PAIR(8));
                    attron(COLOR_PAIR(10));
                    mvprintw(player.x, player.y, "H"); 
                    attroff(COLOR_PAIR(10));
                    refresh();
                }
                else {
                    attron(COLOR_PAIR(16));
                    mvprintw(ox, oy, "\U00002671");
                    attroff(COLOR_PAIR(16));
                    attron(COLOR_PAIR(10));
                    mvprintw(player.x, player.y, "H"); 
                    attroff(COLOR_PAIR(10));
                    refresh();
                }
            }
            else if(board[ox][oy] == 'S') {
                if(c1 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    board[ox][oy] = '.';
                    attroff(COLOR_PAIR(8));
                    attron(COLOR_PAIR(10));
                    mvprintw(player.x, player.y, "H"); 
                    attroff(COLOR_PAIR(10));
                    refresh();
                }
                else {
                    attron(COLOR_PAIR(16));
                    mvprintw(ox, oy, "\U0001F6E6");
                    attroff(COLOR_PAIR(16));
                    attron(COLOR_PAIR(10));
                    mvprintw(player.x, player.y, "H"); 
                    attroff(COLOR_PAIR(10));
                    refresh();
                }
            }
            else if(board[ox][oy] == 'D') {
                if(c1 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    board[ox][oy] = '.';
                    attroff(COLOR_PAIR(8));
                    attron(COLOR_PAIR(10));
                    mvprintw(player.x, player.y, "H"); 
                    attroff(COLOR_PAIR(10));
                    refresh();
                }
                else {
                    attron(COLOR_PAIR(16));
                    mvprintw(ox, oy, "\U00002622");
                    attroff(COLOR_PAIR(16));
                    attron(COLOR_PAIR(10));
                    mvprintw(player.x, player.y, "H"); 
                    attroff(COLOR_PAIR(10));
                    refresh();
                }
            }
            else if(board[ox][oy] == 'a') {
                if(c1 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    board[ox][oy] = '.';
                    attroff(COLOR_PAIR(8));
                    attron(COLOR_PAIR(10));
                    mvprintw(player.x, player.y, "H"); 
                    attroff(COLOR_PAIR(10));
                    refresh();
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvprintw(ox, oy, "\U000027B3");
                    attroff(COLOR_PAIR(9));
                    attron(COLOR_PAIR(10));
                    mvprintw(player.x, player.y, "H"); 
                    attroff(COLOR_PAIR(10));
                    refresh();
                }
            }
            else if(board[ox][oy] == 'm') {
                if(c1 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    board[ox][oy] = '.';
                    attroff(COLOR_PAIR(8));
                    attron(COLOR_PAIR(10));
                    mvprintw(player.x, player.y, "H"); 
                    attroff(COLOR_PAIR(10));
                    refresh();
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvprintw(ox, oy, "\U00002133");
                    attroff(COLOR_PAIR(9));
                    attron(COLOR_PAIR(10));
                    mvprintw(player.x, player.y, "H"); 
                    attroff(COLOR_PAIR(10));
                    refresh();
                }
            }
            else if(board[ox][oy] == 'd') {
                if(c1 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    board[ox][oy] = '.';
                    attroff(COLOR_PAIR(8));
                    attron(COLOR_PAIR(10));
                    mvprintw(player.x, player.y, "H"); 
                    attroff(COLOR_PAIR(10));
                    refresh();
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvprintw(ox, oy, "\U0001F5E1");
                    attroff(COLOR_PAIR(9));
                    attron(COLOR_PAIR(10));
                    mvprintw(player.x, player.y, "H"); 
                    attroff(COLOR_PAIR(10));
                    refresh();
                }
            }
            else if(board[ox][oy] == 's') {
                if(c1 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    board[ox][oy] = '.';
                    attroff(COLOR_PAIR(8));
                    attron(COLOR_PAIR(10));
                    mvprintw(player.x, player.y, "H"); 
                    attroff(COLOR_PAIR(10));
                    refresh();
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvprintw(ox, oy, "\U00002694");
                    attroff(COLOR_PAIR(9));
                    attron(COLOR_PAIR(10));
                    mvprintw(player.x, player.y, "H"); 
                    attroff(COLOR_PAIR(10));
                    refresh();
                }
            }
            break;
        case 'O': 
        case '_': 
        case '|': 
        case 'e':
        case 'f':
        case 'i':
        case 'n':
        case 'u':
            player.x = ox;
            player.y = oy;
            break;
        // case '_': 
        //     player.x = ox;
        //     player.y = oy;
        //     break;
        // case '|': 
        //     player.x = ox;
        //     player.y = oy;
        //     break;
        case '+':
            player.hunger--;
            if(board[ox][oy] == '.') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == '#') {
                attron(COLOR_PAIR(9));
                mvprintw(0,0,"%s", "new room");
                mvprintw(ox, oy, "#");
                attroff(COLOR_PAIR(9));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'T' || board[ox][oy] == 'G' || board[ox][oy] == 'g' || board[ox][oy] == 'F') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                board[ox][oy] = '.';
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == '?') {
                attron(COLOR_PAIR(9));
                mvprintw(ox, oy, "?");
                attroff(COLOR_PAIR(9));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            break;
        case '^':
            trap = 1;
            player.hunger--;
            if(board[ox][oy] == '.') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'F') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == '<') {
                attron(COLOR_PAIR(11));
                mvprintw(ox, oy, ".");
                attroff(COLOR_PAIR(11));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            mvprintw(0, 0, "TRAP!");
            player.health -= 30;
            break;
        case '<': 
            player.hunger--;
            floor++;
            clear();
            attron(COLOR_PAIR(8));
            //next_board[player.x][player.y] = '<';
            if(floor == 2) {
            print_map(board2);
            }
            else if(floor == 3) {
            print_map(board3);
            }
            else if(floor == 4) {
            print_map(board4);
            }
            //print_map(next_board);
            mvprintw(0,0,"next floor!");
            break;
        case '&':
            player.hunger--;
            attron(COLOR_PAIR(8));
            mvprintw(ox, oy, ".");
            attroff(COLOR_PAIR(8));
            attron(COLOR_PAIR(10));
            mvprintw(player.x, player.y, "H"); 
            attroff(COLOR_PAIR(10));
            room[floor][4].pass = rand() % (9000) + 1000;
            mvprintw(1,0, "%d", room[floor][4].pass);
            refresh();
            break;
        case '@':
            player.hunger--;
            if(T > 0) {
                mvprintw(0,0,"Opened the door with ancient key!");
                refresh();
            }
            else {
                clear();
                if(room[floor][4].pass == 0) {
                    mvprintw(20, 83, "You haven't created a password!");
                    mvprintw(21, 83, "type 0 to get back");
                    refresh();
                    char c = getchar();
                    while (c != '0') {
                        c = getchar();
                    }
                    print_map(board);
                }
                else {
                    int p;
                    mvprintw(20, 83, "Enter the password:");
                    scanw("%d", &p);
                    if(p == room[floor][4].pass) {
                        print_map(board);
                        mvprintw(1,0, "%d", room[floor][4].pass);
                        attron(COLOR_PAIR(8));
                        mvprintw(player.x, player.y, "@");
                        attroff(COLOR_PAIR(8));
                        player.x = ox;
                        player.y = oy;
                        player.score += 100;
                    }
                    else {
                        check++;
                        print_map(board);
                        mvprintw(1,0, "%d", room[floor][4].pass);
                        if(check == 1) {
                            attron(COLOR_PAIR(13));
                            mvprintw(player.x, player.y, "@");
                            attroff(COLOR_PAIR(13));
                        }
                        else if(check == 2) {
                            attron(COLOR_PAIR(11));
                            mvprintw(player.x, player.y, "@");
                            attroff(COLOR_PAIR(11));
                        }
                        player.x = ox;
                        player.y = oy;
                    }
                }
            }
            break;
        case 'T':
            player.hunger--;
            T++;
            board[player.x][player.y] = '.';
            if(board[ox][oy] == '.') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
            }
            else if(board[ox][oy] == 'F') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
            }
            else if(board[ox][oy] == '+') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, "+");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
            }
            else if(board[ox][oy] == '#') {
                attron(COLOR_PAIR(9));
                mvprintw(ox, oy, "#");
                attroff(COLOR_PAIR(9));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == '^') {
                attron(COLOR_PAIR(11));
                mvprintw(ox, oy, "^");
                attroff(COLOR_PAIR(11));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            break;
    }
    if((room[floor][1].x <= player.x && player.x <= room[floor][1].x + 10) && (room[floor][1].y <= player.y && player.y <= room[floor][1].y + 12)) {
        attron(COLOR_PAIR(8));
        mvprintw(demon[floor].x, demon[floor].y, ".");
        board[demon[floor].x][demon[floor].y] = '.';
        refresh();
        attroff(COLOR_PAIR(8));
        dfs_boss(board, &demon[floor].x, &demon[floor].y, ox, oy, 1);
        attron(COLOR_PAIR(17));
        mvprintw(demon[floor].x, demon[floor].y, "D");
        board[demon[floor].x][demon[floor].y] = 'e';
        refresh();
        attroff(COLOR_PAIR(17));
        }
    else if((room[floor][2].x <= player.x && player.x <= room[floor][2].x + 10) && (room[floor][2].y <= player.y && player.y <= room[floor][2].y + 12)) {
        attron(COLOR_PAIR(8));
        mvprintw(fire[floor].x, fire[floor].y, ".");
        board[fire[floor].x][fire[floor].y] = '.';
        refresh();
        attroff(COLOR_PAIR(8));
        dfs_boss(board, &fire[floor].x, &fire[floor].y,  ox, oy, 2);
        attron(COLOR_PAIR(17));
        mvprintw(fire[floor].x, fire[floor].y, "F");
        board[fire[floor].x][fire[floor].y] = 'f';
        refresh();
        attroff(COLOR_PAIR(17));
        }
    else if((room[floor][3].x <= player.x && player.x <= room[floor][3].x + 10) && (room[floor][3].y <= player.y && player.y <= room[floor][3].y + 12)) {
        attron(COLOR_PAIR(8));
        mvprintw(giant[floor].x, giant[floor].y, ".");
        board[giant[floor].x][giant[floor].y] = '.';
        refresh();
        attroff(COLOR_PAIR(8));
        dfs_boss(board, &giant[floor].x, &giant[floor].y, ox, oy, 3);
        attron(COLOR_PAIR(17));
        mvprintw(giant[floor].x, giant[floor].y, "G");
        board[giant[floor].x][giant[floor].y] = 'i';
        refresh();
        attroff(COLOR_PAIR(17));
        }
    else if((room[floor][4].x <= player.x && player.x <= room[floor][4].x + 10) && (room[floor][4].y <= player.y && player.y <= room[floor][4].y + 12)) {
        attron(COLOR_PAIR(8));
        mvprintw(snake[floor].x, snake[floor].y, ".");
        board[snake[floor].x][snake[floor].y] = '.';
        refresh();
        attroff(COLOR_PAIR(8));
        dfs_boss(board, &snake[floor].x, &snake[floor].y, ox, oy, 4);
        attron(COLOR_PAIR(17));
        mvprintw(snake[floor].x, snake[floor].y, "S");
        board[snake[floor].x][snake[floor].y] = 'n';
        refresh();
        attroff(COLOR_PAIR(17));
        }
    else if((room[floor][5].x <= player.x && player.x <= room[floor][5].x + 10) && (room[floor][5].y <= player.y && player.y <= room[floor][5].y + 12)) {
        attron(COLOR_PAIR(8));
        mvprintw(undeed[floor].x, undeed[floor].y, ".");
        board[undeed[floor].x][undeed[floor].y] = '.';
        refresh();
        attroff(COLOR_PAIR(8));
        dfs_boss(board, &undeed[floor].x, &undeed[floor].y, ox, oy, 5);
        attron(COLOR_PAIR(17));
        mvprintw(undeed[floor].x, undeed[floor].y, "U");
        board[undeed[floor].x][undeed[floor].y] = 'u';
        refresh();
        attroff(COLOR_PAIR(17));
        }
    refresh();
}

void save_borad(char** board) {
    FILE* f;
    for(int i = 0; i <= 46; i++) {
            f = fopen("map", "a");
            fprintf(f, "%s\n", board[i]);
            fclose(f);
    }
}

void food_list(char** board) {
    clear();
    mvprintw(0, 73, "hunger:");
    for(int i = 0 ; i < (player.hunger / 10); i++) {
        mvaddstr(0,80 + i,"\U000025A3");
    }
    while(1) {
        mvprintw(0, 0, "Type");
        mvprintw(0, 16, "numbers saved");
        mvprintw(0, 40, "health increase");
        mvprintw(2, 0, "1:regular food");
        mvprintw(2, 22, "%d", reg_food);
        mvprintw(2, 45, "50");
        refresh();
        char n = getchar();
        if(n == '1') {
            if(reg_food <= 0) {
                mvprintw(0, 175, "Not Enough Food");
                refresh();
                continue;
            }
            player.hunger += 80;
            reg_food--;
        }
        else if(n == '2') {

        } 
        else if(n == '3') {

        }
        else if(n == '4') {

        }
        else if(n == 'E') {
            clear();
            print_map(board);
            break;
        }
        else {continue;}
    }
}

void loading(int floor) {
    clear();
    mvprintw(22, 92, "loading");
    for(int i = 0; i < floor; i++) {
        mvaddstr(23, 93 + i, "\U000025A3");
    }
}

void weapon_list(char** board){
    clear();
    attron(COLOR_PAIR(9));
    mvprintw(0, 2, "name");
    mvprintw(0, 11, "sign");
    mvprintw(0, 19, "numbers saved");
    mvprintw(0, 37, "type");
    mvprintw(0, 47, "damage");
    mvprintw(0, 59, "range");
    mvprintw(2, 2, "1.mace    \U00002692             %d          close       5            -", mace);
    mvprintw(4, 2, "2.dagger  \U0001F5E1             %d          long        12           5", dagger);
    mvprintw(6, 2, "3.wand    \U00002133             %d          long        15           10", wand);
    mvprintw(8, 2, "4.arrow   \U000027B3             %d          long        5            5", arrow);
    mvprintw(10, 2, "5.sword   \U00002694             %d          close       5            -", sword);
    refresh();

    while(1) {
        attron(COLOR_PAIR(13));
        if(strcmp(player.weapon, "mace") == 0) {
            mvaddstr(2, 0, "\U000021FE");
        }
        else if(strcmp(player.weapon, "dagger") == 0) {
            mvaddstr(4, 0, "\U000021FE");
        }
        else if(strcmp(player.weapon, "wand") == 0) {
            mvaddstr(6, 0, "\U000021FE");
        }
        else if(strcmp(player.weapon, "arrow") == 0) {
            mvaddstr(8, 0, "\U000021FE");
        }
        else if(strcmp(player.weapon, "sword") == 0) {
            mvaddstr(10, 0, "\U000021FE");
        }
        refresh();
        attroff(COLOR_PAIR(13));

        char n = getchar();
        if(n == '1') {
            if(strcmp(player.weapon, " ") != 0) {
                mvprintw(0, 150, "put your current weapon in the bag first");
                refresh();
                napms(2500);
            }
            else {
                strcpy(player.weapon, "mace");
                mvprintw(0, 157, "your current weapon is now %s", player.weapon);
                refresh();
                napms(2500);
            }
            print_map(board);
            break;
        }
        else if(n == '2') {
            if(strcmp(player.weapon, " ") != 0) {
                mvprintw(0, 150, "put your current weapon in the bag first");
                refresh();
                napms(2500);
            }
            else {
                strcpy(player.weapon, "dagger");
                mvprintw(0, 157, "your current weapon is now %s", player.weapon);
                refresh();
                napms(2500);
            }
            print_map(board);
            break;
        } 
        else if(n == '3') {
            if(strcmp(player.weapon, " ") != 0) {
                mvprintw(0, 150, "put your current weapon in the bag first");
                refresh();
                napms(2500);
            }
            else {
                strcpy(player.weapon, "wand");
                mvprintw(0, 157, "your current weapon is now %s", player.weapon);
                refresh();
                napms(2500);
            }
            print_map(board);
            break;
        }
        else if(n == '4') {
            if(strcmp(player.weapon, " ") != 0) {
                mvprintw(0, 150, "put your current weapon in the bag first");
                refresh();
                napms(2500);
            }
            else {
                strcpy(player.weapon, "arrow");
                mvprintw(0, 157, "your current weapon is now %s", player.weapon);
                refresh();
                napms(2500);
            }
            print_map(board);
            break;
        }
        else if(n == '5') {
            if(strcmp(player.weapon, " ") != 0) {
                mvprintw(0, 150, "put your current weapon in the bag first");
                refresh();
                napms(2500);
            }
            else {
                strcpy(player.weapon, "sword");
                mvprintw(0, 157, "your current weapon is now %s", player.weapon);
                refresh();
                napms(2500);
            }
            print_map(board);
            break;
        }
        else if(n == 'e') {
            strcpy(player.weapon, " ");
            for(int i = 1; i <= 5; i++) {
                mvprintw(2 * i, 0, " ");
            }
        }
        else {continue;}
    }
    attroff(COLOR_PAIR(9));
}

void talisman_list(char** board) {
    clear();
    attron(COLOR_PAIR(9));
    mvprintw(0, 1, "name");
    mvprintw(0, 12, "sign");
    mvprintw(0, 19, "numbers saved");
    refresh();
    while(1) {
        mvprintw(2, 1, "1.health    \U00002671            %d", health);
        mvprintw(4, 1, "2.damage    \U00002622            %d", damage);
        mvprintw(6, 1, "3.speed     \U0001F6E6            %d", speed);
        refresh();
        char n = getchar();
        if(n == '1' && health > 0) {
            player.hunger += 100;
            player.health += 200;
            health--;
        }
        else if(n == '2' && damage > 0) {
            d = 1;
            damage--;
        } 
        else if(n == '3' && speed > 0) {
            s = 1;
            speed--;
        }
        else if(n == 't') {
            print_map(board);
            break;
        }
        else {continue;}
    }
    attroff(COLOR_PAIR(9));
}

void enchant() {
    clear();
    char** board = (char**)malloc(47 * sizeof(char*));
    for(int i = 0; i <= 50; i++) {
        *(board + i) = (char*)malloc(190);
    }
    for(int i = 0; i <= 46; i++) {
        for(int j = 0; j <= 189; j++) {
            board[i][j] = ' ';
        }
    }
    pos enchant;
    enchant.x = rand() % (35) + 3;
    enchant.y = rand() % (158) + 16;
    int I = rand() % (15) + 6;
    int J = rand() % (17) + 4;
    int X1 = rand() % (I - 2) + enchant.x + 1;
    int Y1 = rand () % (J - 2) + enchant.y + 1;
    int ox = rand() % (I - 2) + enchant.x + 1;
    int oy = rand () % (J - 2) + enchant.y + 1;
    int h1 = rand () % (J - 1) + enchant.y;
    int D1 = rand () % (J - 1) + enchant.y;
    int S1 = rand () % (J - 1) + enchant.y;
    int h2 = rand () % (J - 1) + enchant.y;
    int D2 = rand () % (J - 1) + enchant.y;
    int S2 = rand () % (J - 1) + enchant.y;
    for(int i = enchant.x; i < enchant.x + I; i++) {
        board[i][enchant.y - 1] = '|';
        board[i][enchant.y + J] = '|';
    }
    for(int j = enchant.y; j < enchant.y + J; j++) {
        board[enchant.x - 1][j] = '_';
        board[enchant.x + I][j] = '_';
    }
    for(int i = enchant.x; i < enchant.x + I; i++) {
        for(int j = enchant.y; j < enchant.y + J; j++) {
                if((i == X1 && j == Y1) || (i == ox && j == oy)) {
                    board[i][j] = 'O';
                    continue;
                }
                else if(i == enchant.x && j == enchant.y + h1) {
                    board[i][j] = 'h';
                }
                else if(i == enchant.x + 1 && j == enchant.y + D1) {
                    board[i][j] = 'D';
                }
                else if(i == enchant.x + 2 && j == enchant.y + S1) {
                    board[i][j] = 'S';
                }
                else if(i == enchant.x + 3 && j == enchant.y + h2) {
                    board[i][j] = 'h';
                }
                else if(i == enchant.x + 4 && j == enchant.y + D2) {
                    board[i][j] = 'D';
                }
                else if(i == enchant.x + 5 && j == enchant.y + S2) {
                    board[i][j] = 'S';
                }
                
                board[i][j] = '.';
        }
    }
    player.x = enchant.x + I - 1;
    player.y = enchant.y + J - 1;
    print_map(board);

}

void boss_init() {
    for(int i = 1; i <= 4; i++) {
        demon[floor].health = 5, demon[floor].damage = 40;
        fire[floor].health = 10, fire[floor].damage = 60;
        giant[floor].health = 15, giant[floor].damage = 80;
        snake[floor].health = 20, snake[floor].damage = 100;
        undeed[floor].health = 30, undeed[floor].damage = 140;
    }
}

void dfs_boss(char** board, int* x, int* y, int ox, int oy, int boss) {
    int xx = (*x);
    int yy = (*y);
    if((*x) == ox - 1 && (*y) == oy) {
        if(ox != player.x && oy != player.y) {
            (*x) = ox;
            (*y) = oy;
        }
        switch(boss) {
            case 1:
                player.health -= demon[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by demon");
                attroff(COLOR_PAIR(9));
                break;
            case 2:
                player.health -= fire[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by fire");
                attroff(COLOR_PAIR(9));
                break;
            case 3:
                player.health -= giant[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by giant");
                attroff(COLOR_PAIR(9));
                break;
            case 4:
                player.health -= snake[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by snake");
                attroff(COLOR_PAIR(9));
                break;
            case 5:
                player.health -= undeed[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by undeed");
                attroff(COLOR_PAIR(9));
                break;
        }
    }
    else if((*x) == ox - 1 && (*y) == oy - 1) {
        if(ox != player.x && oy != player.y) {
            (*x) = ox;
            (*y) = oy;    
        }
        switch(boss) {
            case 1:
                player.health -= demon[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by demon");
                attroff(COLOR_PAIR(9));
                break;
            case 2:
                player.health -= fire[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by fire");
                attroff(COLOR_PAIR(9));
                break;
            case 3:
                player.health -= giant[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by giant");
                attroff(COLOR_PAIR(9));
                break;
            case 4:
                player.health -= snake[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by snake");
                attroff(COLOR_PAIR(9));
                break;
            case 5:
                player.health -= undeed[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by undeed");
                attroff(COLOR_PAIR(9));
                break;
        }
    }
    else if((*x) == ox - 1 && (*y) == oy + 1) {
        if(ox != player.x && oy != player.y) {
            (*x) = ox;
            (*y) = oy;    
        }
        switch(boss) {
            case 1:
                player.health -= demon[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by demon");
                attroff(COLOR_PAIR(9));
                break;
            case 2:
                player.health -= fire[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by fire");
                attroff(COLOR_PAIR(9));
                break;
            case 3:
                player.health -= giant[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by giant");
                attroff(COLOR_PAIR(9));
                break;
            case 4:
                player.health -= snake[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by snake");
                attroff(COLOR_PAIR(9));
                break;
            case 5:
                player.health -= undeed[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by undeed");
                attroff(COLOR_PAIR(9));
                break;
        }
    }
    else if((*x) == ox && (*y) == oy - 1) {
        if(ox != player.x && oy != player.y) {
            (*x) = ox;
            (*y) = oy;
        }
        switch(boss) {
            case 1:
                player.health -= demon[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by demon");
                attroff(COLOR_PAIR(9));
                break;
            case 2:
                player.health -= fire[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by fire");
                attroff(COLOR_PAIR(9));
                break;
            case 3:
                player.health -= giant[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by giant");
                attroff(COLOR_PAIR(9));
                break;
            case 4:
                player.health -= snake[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by snake");
                attroff(COLOR_PAIR(9));
                break;
            case 5:
                player.health -= undeed[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by undeed");
                attroff(COLOR_PAIR(9));
                break;
        }
    }
    else if((*x) == ox && (*y) == oy + 1) {
        if(ox != player.x && oy != player.y) {
            (*x) = ox;
            (*y) = oy;    
        }
        switch(boss) {
            case 1:
                player.health -= demon[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by demon");
                attroff(COLOR_PAIR(9));
                break;
            case 2:
                player.health -= fire[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by fire");
                attroff(COLOR_PAIR(9));
                break;
            case 3:
                player.health -= giant[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by giant");
                attroff(COLOR_PAIR(9));
                break;
            case 4:
                player.health -= snake[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by snake");
                attroff(COLOR_PAIR(9));
                break;
            case 5:
                player.health -= undeed[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by undeed");
                attroff(COLOR_PAIR(9));
                break;
        }
    }
    else if((*x) == ox + 1 && (*y) == oy) {
        if(ox != player.x && oy != player.y) {
            (*x) = ox;
            (*y) = oy;
        }
        switch(boss) {
            case 1:
                player.health -= demon[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by demon");
                attroff(COLOR_PAIR(9));
                break;
            case 2:
                player.health -= fire[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by fire");
                attroff(COLOR_PAIR(9));
                break;
            case 3:
                player.health -= giant[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by giant");
                attroff(COLOR_PAIR(9));
                break;
            case 4:
                player.health -= snake[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by snake");
                attroff(COLOR_PAIR(9));
                break;
            case 5:
                player.health -= undeed[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by undeed");
                attroff(COLOR_PAIR(9));
                break;
        }
    }
    else if((*x) == ox - 1 && (*y) == oy - 1) {
        if(ox != player.x && oy != player.y) {
            (*x) = ox;
            (*y) = oy;   
        }
        switch(boss) {
            case 1:
                player.health -= demon[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by demon");
                attroff(COLOR_PAIR(9));
                break;
            case 2:
                player.health -= fire[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by fire");
                attroff(COLOR_PAIR(9));
                break;
            case 3:
                player.health -= giant[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by giant");
                attroff(COLOR_PAIR(9));
                break;
            case 4:
                player.health -= snake[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by snake");
                attroff(COLOR_PAIR(9));
                break;
            case 5:
                player.health -= undeed[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by undeed");
                attroff(COLOR_PAIR(9));
                break;
        }
    }
    else if((*x) == ox + 1 && (*y) == oy + 1) {
         if(ox != player.x && oy != player.y) {
            (*x) = ox;
            (*y) = oy;    
        }
        switch(boss) {
            case 1:
                player.health -= demon[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by demon");
                attroff(COLOR_PAIR(9));
                break;
            case 2:
                player.health -= fire[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by fire");
                attroff(COLOR_PAIR(9));
                break;
            case 3:
                player.health -= giant[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by giant");
                attroff(COLOR_PAIR(9));
                break;
            case 4:
                player.health -= snake[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by snake");
                attroff(COLOR_PAIR(9));
                break;
            case 5:
                player.health -= undeed[floor].damage;
                attron(COLOR_PAIR(9));
                mvprintw(0, 0, "Got hit by undeed");
                attroff(COLOR_PAIR(9));
                break;
        }
    }
    else {
        if((*x) < ox) {
            if(check_dfs(board, *x + 1, *y)) {
                (*x)++;
            }
            else if(check_dfs(board, *x, *y + 1)) {
                (*y)++;
            }
            else if(check_dfs(board, *x, *y - 1)) {
                (*y)--;
            }
            else if(check_dfs(board, *x - 1, *y)) {
                (*x)--;
            }
        }
        else if((*x) > ox) {
            if(check_dfs(board, *x - 1, *y)) {
                (*x)--;
            }
            else if(check_dfs(board, *x, *y - 1)) {
                (*y)--;
            }
            else if(check_dfs(board, *x, *y + 1)) {
                (*y)++;
            }
            else if(check_dfs(board, *x + 1, *y)) {
                (*x)++;
            }
        }
        else if((*y) < oy) {
            if(check_dfs(board, *x, *y + 1)) {
                (*y)++;
            }
            else if(check_dfs(board, *x - 1, *y)) {
                (*x)--;
            }
            else if(check_dfs(board, *x + 1, *y)) {
                (*x)++;
            }
            else if(check_dfs(board, *x, *y - 1)) {
                (*y)--;
            }
        }
        else if((*y) > oy) {
            if(check_dfs(board, *x, *y - 1)) {
                (*y)--;
            }
            else if(check_dfs(board, *x + 1, *y)) {
                (*x)++;
            }
            else if(check_dfs(board, *x - 1, *y)) {
                (*x)--;
            }
            else if(check_dfs(board, *x, *y + 1)) {
                (*y)++;
            }
        }
        
    }
    if((*x) == player.x && (*y) == player.y) {
        (*x) = xx;
        (*y) = yy;
    }
}

int check_dfs(char** board, int x, int y) {
    if(board[x][y] == '.') {
        return 1;
    }
    return 0;
}

void quit() {
    clear();
    mvprintw(20,83, "press any key to quit");
    refresh();
    char c = getchar();
}