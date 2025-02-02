//46*189
//x:1-32 y:1-179
//music
//forgot password
//messages
//g and f button
//scoreboard bug
//score += when kill boss
//other floor bus bug
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
pos IJ[3];
typedef struct {
    char name[100], pass[100], mail[100], weapon[15];
    int score, gold, exp, health, color, x, y, hunger;
} att;
att player;
typedef struct {
    int x, y;
    char c[100][100];
    int pass, I, J;
    pos door;
} Room;
Room** room;
typedef struct {
    int x, y, health, damage, end;
} boss;
typedef struct {
    int score, gold, n_login, exp;
    char name[20];
} at;
boss demon[6], fire[6], giant[6], snake[6], undeed[6];
int flag[6][47][190];
int floor = 1, T = 0, reg_food = 0, z_food = 0, y_food = 0, x_food = 0, M = 0; 
int dagger = 0, wand = 0, arrow = 0, sword = 0, mace = 1;
int health = 0, damage = 0, speed = 0, s = 0, d = 0, h = 0, scount = 0, dcount = 0, hcount = 0;
char c1, c2, c3, c4, c5, c6, c7;
int hidden = 0, check = 0,signin = 0, n_login = 0, karbar = 0, init_health = 0, win = 0, lose = 0, guest = 0;
pos ddagger, wwand, aarrow;
char** board1;
char** board2;
char** board3;
char** board4;
char** board5;
void color();
void board_init();
void initialize();
void sign_up();
void sign_in();
void menu();
void scoreboard();
void setting();
void difficulty();
void character_color();
void music();
void quit();
void input(char, char**);
void create_map(char***);
void print_map(char**);
int check_room(Room**);
void Doors(char***);
void print_character(int, int, char**);
void create_map(char***);
void food_list(char**);
void loading(int);
void weapon_list(char**);
void talisman_list(char**);
void enchant_check();
void boss_init();
void dfs_boss(char**, int*, int*, int, int, int);
int check_dfs(char**, int, int);
void damage_handle(int);
void attack(char**);
int check_attack(char**, char);
void find_boss(char**, char);
int throw(char**, char, int, int*, int*, int);
int find_boss2(char**, int, int, int);
void check_sharp(char**, int, int);
void check_door(char**, int, int);
void show_map(char**, int);
void save_borad();
void save_info();
void save_flag();
void save_boss();
void save_other();
void load_game();
void make_scoreboard();
void S(int, int, char**);
void random_password();
void generate_password();
int main() {
    setlocale(LC_ALL, "");
    initscr();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();
    if(has_colors() == FALSE){	
        endwin();
	    printf("Your terminal does not support color\n");
	    exit(1);
    }
    init_color(COLOR_BLACK, 0, 0, 0);
    init_pair(8, COLOR_GREEN, COLOR_BLACK);
    init_pair(9, COLOR_WHITE, COLOR_BLACK);
    attron(COLOR_PAIR(8));
    room = (Room**)malloc(5 * sizeof(Room*));
    for(int i = 0; i < 6; i++) {
        *(room + i) = (Room*)malloc(6 * sizeof(Room));
    }
    for(int i = 1; i <= 4; i++) {
        room[i][4].pass = 0;
    }
    
    board_init();
    if(n_login != 0) {
        FILE* f = fopen("winlose", "r");
        fscanf(f, "%d", &win);
        fscanf(f, "%d", &lose);
        fclose(f);
    }
    initialize();
    if(strcmp(player.name, "mahdi0x06") == 0) {
        karbar = 1;
    }
    else if(strcmp(player.name, "mahdi0110") == 0) {
        karbar = 2;
    }
    else if(strcmp(player.name, "TAmabani") == 0) {
        karbar = 3;
    }
    color();
    boss_init();
    napms(1000);
    if(signin == 0) {
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
        if(player.health != 300 && player.health != 500 && player.health != 700 && player.health != 900) {
            player.health = 900;
        }
        player.hunger = 200;
        player.gold = 0;
        strcpy(player.weapon, "mace");
        player.score = 0;
        player.exp = 0;
    }
    init_health = player.health;
    if(floor == 1) {
        print_map(board1); 
    }
    else if(floor == 2) {
        print_map(board2); 
    }
    else if(floor == 3) {
        print_map(board3); 
    }
    else if(floor == 4) {
        print_map(board4); 
    }
    n_login++;
    while(1) {
        enchant_check();
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
            lose = 1;
            FILE* f = fopen("winlose", "w");
            fprintf(f, "%d\n", win);
            fprintf(f, "%d\n", lose);
            fclose(f);
            mvprintw(21, 86, "GAME OVER!!");
            refresh();
            getchar();
            break;
        }
        if(player.hunger <= 0) {
            player.health -= 10;
            player.hunger = 0;
        }
        if(h == 1 && hcount != 10 ) {
            hcount++;
        }
        else {
            h = 0;
            hcount = 0;
        }
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
        if(c == '0') {
            FILE* f = fopen("winlose", "w");
            fprintf(f, "%d\n", win);
            fprintf(f, "%d\n", lose);
            fclose(f);
            quit(); 
            break;
        }
        if(win == 1){
            FILE* f = fopen("winlose", "w");
            fprintf(f, "%d\n", win);
            fprintf(f, "%d\n", lose);
            fclose(f);
            break;
        }
        switch (floor)
        {
        case 1:
            input(c, board1);
            break;
        case 2:
            input(c, board2);
            break;
        case 3:
            input(c, board3);
            break;
        case 4:
            input(c, board4);
            break;
        case 5:
            input(c, board5);
            break;
        }
        player.exp++;
        if(player.exp % 20 == 0) {
            for(int i = 0; i < 4; i++) {
                mvprintw(i , 0, "                  ");
                refresh();
            }
        }
    }
    endwin();
    return 0;
}

void enchant_check() {
    if(room[1][0].x <= player.x && player.x < room[1][0].x + room[1][0].I && room[1][0].y <= player.y && player.y < room[1][0].y + room[1][0].J) {
        player.health -= 15;
    }
}

void color() {
    init_color(COLOR_RED, 1000, 0, 0);
    init_color(1, 700, 330, 330);
    init_color(19, 500, 0, 700);
    init_color(20, 500, 0, 100);
    init_color(15, 240, 90, 90);
    init_color(30, 700, 0, 1000);
    init_pair(11, COLOR_RED, COLOR_BLACK);
    init_pair(14, 15, COLOR_BLACK);
    if(player.color == 1) {
        init_pair(10, 20, COLOR_BLACK);
    }
    else if(player.color == 2) {
        init_pair(10, COLOR_GREEN, COLOR_BLACK);
    }
    else if(player.color == 4) {
        init_pair(10, COLOR_BLUE, COLOR_BLACK);
    }
    else {
        init_pair(10, COLOR_BLUE, COLOR_BLACK);
    }
    init_pair(12, 1, COLOR_BLACK);
    init_pair(13, COLOR_YELLOW, COLOR_BLACK);
    init_pair(15, COLOR_BLACK, COLOR_BLUE);
    init_pair(16, 19, COLOR_BLACK);
    init_pair(17, 20, COLOR_BLACK);
    init_color(21, 255, 223, 0);
    init_pair(18, 21, COLOR_BLACK);
    init_pair(31, 30, COLOR_BLACK);
}

void board_init() {
    board1 = (char**)malloc(47 * sizeof(char*));
    for(int i = 0; i <= 46; i++) {
        *(board1 + i) = (char*)malloc(190);
    }
    for(int i = 0; i <= 46; i++) {
        for(int j = 0; j <= 189; j++) {
            board1[i][j] = ' ';
            flag[floor][i][j] = 0;
        }
    }    
    board2 = (char**)malloc(47 * sizeof(char*));
    for(int i = 0; i <= 46; i++) {
        *(board2 + i) = (char*)malloc(190);
    }
    for(int i = 0; i <= 46; i++) {
        for(int j = 0; j <= 189; j++) {
            board2[i][j] = ' ';
            flag[5][i][j] = 1;
        }
    }    
    board3 = (char**)malloc(47 * sizeof(char*));
    for(int i = 0; i <= 46; i++) {
        *(board3 + i) = (char*)malloc(190);
    }
    for(int i = 0; i <= 46; i++) {
        for(int j = 0; j <= 189; j++) {
            board3[i][j] = ' ';
        }
    }    
    board4 = (char**)malloc(47 * sizeof(char*));
    for(int i = 0; i <= 46; i++) {
        *(board4 + i) = (char*)malloc(190);
    }
    for(int i = 0; i <= 46; i++) {
        for(int j = 0; j <= 189; j++) {
            board4[i][j] = ' ';
        }
    }
    board5 = (char**)malloc(47 * sizeof(char*));
    for(int i = 0; i <= 46; i++) {
        *(board5 + i) = (char*)malloc(190);
    }
    for(int i = 0; i <= 46; i++) {
        for(int j = 0; j <= 189; j++) {
            board5[i][j] = ' ';
        }
    }
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
            guest = 1;
            menu();
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
    printw("Enter your password:(enter g to generate a random password)\n");
    while(1) {
        scanw(" %s", player.pass);
        if(strcmp(player.pass, "g") == 0) {
            //random_password();
            generate_password();
            printw("your generated password:%s\n", player.pass);
        }
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

void generate_password() {
    char uppers[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char lowers[] = "abcdefghijklmnopqrstuvwxyz";
    char number[] = "0123456789";
    srand(time(NULL));
    int len = rand() % (9) + 7;
    for (int i = 0; i < 3; i++) {
        int u = rand() % (sizeof(uppers) - 1);
        player.pass[i] = uppers[u];
    }
    for (int i = 3; i < 6; i++) {
        int l = rand() % (sizeof(lowers) - 1);
        player.pass[i] = lowers[l];
    }
    for (int i = 6; i < 9; i++) {
        int n = rand() % (sizeof(number) - 1);
        player.pass[i] = number[n];
    }
    player.pass[9] = '\0';
    
    refresh();
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
    printw("Enter your password:(enter f if you forgot your password)\n");
    while(1) {
        char password[200];
        scanw("%s", password);
        if(strcmp(password, "f") == 0) {
            FILE* f = fopen(player.name, "r");
            int count = 1;
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
            printw("your password is:%s\n", p);
            fclose(f);
            printw("Enter your password:(enter f if you forgot your password)\n");
            char password[200];
            scanw("%s", password);
            int countt = 1;
            f = fopen(player.name, "r");
            char* pass = (char*)malloc(200);
            char pp[200];
            while (1) {
                fgets(pp, 200, f);
                if (countt == 3) {
                    break;
                }
                else {
                    countt++;
                }
            }
            int flag = 0;
            pass = pp;
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
    attron(COLOR_PAIR(8));
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
        }
        else if(n == '2') {
            if(win == 1 || lose == 1) {
                mvprintw(0, 77, "you don't have any saved game");
                refresh();
                continue;
            }
            else if(guest = 1) {
                mvprintw(0, 77, "you have logged in as a guest");
                refresh();
                continue;
            }
            clear();
            signin = 1;
            load_game();
        } 
        else if(n == '3') {
            clear();
            scoreboard();
        }
        else if(n == '4') {
            clear();
            setting();
        }
        else if(n == '5') {
            clear();
        }
        else {continue;}
        break;
    }
}

void load_game() {
    FILE* f1;
    f1 = fopen("map1", "r");
    for(int i = 0; i <= 46; i++) {
        fgets(board1[i], 196, f1);
        board1[i][strcspn(board1[i], "\n")] = '\0';
    }
    fclose(f1);


    FILE* f2;
    f2 = fopen("map2", "r");
    for(int i = 0; i <= 46; i++) {
        fgets(board2[i], 196, f2);
        board2[i][strcspn(board2[i], "\n")] = '\0';
    }
    fclose(f2);

    FILE* f3;
    f3 = fopen("map3", "r");
    for(int i = 0; i <= 46; i++) {
        fgets(board3[i], 196, f3);
        board3[i][strcspn(board3[i], "\n")] = '\0';
    }
    fclose(f3);

    FILE* f4;
    f4 = fopen("map4", "r");
    for(int i = 0; i <= 46; i++) {
        fgets(board4[i], 196, f4);
        board4[i][strcspn(board4[i], "\n")] = '\0';
    }
    fclose(f4);

    FILE* f55;
    f55 = fopen("map5", "r");
    for(int i = 0; i <= 46; i++) {
        fgets(board5[i], 196, f55);
        board5[i][strcspn(board5[i], "\n")] = '\0';
    }
    fclose(f55);

    FILE* f5 = fopen("flag1", "r");
    for(int i = 0; i <= 46; i++) {
        for(int j = 0; j <= 189; j++) {
            fscanf(f5, "%d", &flag[1][i][j]);
        }
    }
    fclose(f5);

    FILE* f6 = fopen("flag2", "r");
    for(int i = 0; i <= 46; i++) {
        for(int j = 0; j <= 189; j++) {
            fscanf(f6, "%d", &flag[2][i][j]);
        }
    }
    fclose(f6);

    FILE* f7 = fopen("flag3", "r");
    for(int i = 0; i <= 46; i++) {
        for(int j = 0; j <= 189; j++) {
            fscanf(f7, "%d", &flag[3][i][j]);
        }
    }
    fclose(f7);

    FILE* f8 = fopen("flag4", "r");
    for(int i = 0; i <= 46; i++) {
        for(int j = 0; j <= 189; j++) {
            fscanf(f8, "%d", &flag[4][i][j]);
        }
    }
    fclose(f8);

    FILE* f9 = fopen("info", "r");
    fscanf(f9, "%d", &player.health);
    fscanf(f9, "%d", &player.score);
    fscanf(f9, "%d", &player.gold);
    fscanf(f9, "%d", &player.exp);
    fscanf(f9, "%d", &player.color);
    fscanf(f9, "%d", &player.x);
    fscanf(f9, "%d", &player.y);
    fscanf(f9, "%d", &player.hunger);
    fscanf(f9, "%s", player.weapon);
    fclose(f9);

    FILE* f10;
    f10 = fopen("room", "r");
    for(int i = 1; i <= 4; i++) {
        for(int j = 0; j < 6; j++) {
            fscanf(f10, "%d", &room[i][j].x);
            fscanf(f10, "%d", &room[i][j].y);
            fscanf(f10, "%d", &room[i][j].I);
            fscanf(f10, "%d", &room[i][j].J);
            fscanf(f10, "%d", &room[i][j].pass);
            fscanf(f10, "%d", &room[i][j].door.x);
            fscanf(f10, "%d", &room[i][j].door.y);
        }
    }
    fclose(f10);

    FILE* f11;
    f11 = fopen("boss", "r");
    for(int i = 1; i <= 4; i++) {
        fscanf(f11, "%d", &demon[i].x);
        fscanf(f11, "%d", &demon[i].y);
        fscanf(f11, "%d", &fire[i].x);
        fscanf(f11, "%d", &fire[i].y);
        fscanf(f11, "%d", &giant[i].x);
        fscanf(f11, "%d", &giant[i].y);
        fscanf(f11, "%d", &snake[i].x);
        fscanf(f11, "%d", &snake[i].y);
        fscanf(f11, "%d", &undeed[i].x);
        fscanf(f11, "%d", &undeed[i].y);
    }
    fclose(f11);

    FILE* f12;
    f12 = fopen("other", "r");
    fscanf(f12, "%d", &floor);
    fscanf(f12, "%d", &T);
    fscanf(f12, "%d", &reg_food);
    fscanf(f12, "%d", &dagger);
    fscanf(f12, "%d", &wand);
    fscanf(f12, "%d", &arrow);
    fscanf(f12, "%d", &sword);
    fscanf(f12, "%d", &health);
    fscanf(f12, "%d", &damage);
    fscanf(f12, "%d", &speed);
    fscanf(f12, "%d", &h);
    fscanf(f12, "%d", &d);
    fscanf(f12, "%d", &s);
    fscanf(f12, "%d", &hcount);
    fscanf(f12, "%d", &scount);
    fscanf(f12, "%d", &dcount);
    fscanf(f12, "%d", &hidden);
    fscanf(f12, "%d", &check);
    fscanf(f12, "%d", &n_login);
    fclose(f12);

}

void scoreboard() {
    while(1) {
        FILE* f1 = fopen("scoreboard1", "r");
        FILE* f2 = fopen("scoreboard2", "r");
        FILE* f3 = fopen("scoreboard3", "r");
        at p[3];
        fscanf(f1, "%s", p[0].name);
        fscanf(f1, "%d", &p[0].score);
        fscanf(f1, "%d", &p[0].gold);
        fscanf(f1, "%d", &p[0].n_login);
        fscanf(f1, "%d", &p[0].exp);
        fclose(f1);

        fscanf(f2, "%s", p[1].name);
        fscanf(f2, "%d", &p[1].score);
        fscanf(f2, "%d", &p[1].gold);
        fscanf(f2, "%d", &p[1].n_login);
        fscanf(f2, "%d", &p[1].exp);
        fclose(f2);

        fscanf(f3, "%s", p[2].name);
        fscanf(f3, "%d", &p[2].score);
        fscanf(f3, "%d", &p[2].gold);
        fscanf(f3, "%d", &p[2].n_login);
        fscanf(f3, "%d", &p[2].exp);
        fclose(f3);

        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(4, COLOR_BLUE, COLOR_BLACK);
        attron(COLOR_PAIR(9));
        mvprintw(0, 0, "        name                           score                gold                 n                 exp");
        mvprintw(0, 184, "0:back");
        refresh();
        attroff(COLOR_PAIR(9));

        if(p[0].score <= p[1].score && p[1].score <= p[2].score) {
            if(strcmp(player.name, "mahdi0x06") == 0) {
                attron(COLOR_PAIR(1));
                mvprintw(2, 0, "1.\U0001F947 %s(goat)                   %d                   %d                   %d                 %d", p[2].name, p[2].score, p[2].gold, p[2].n_login, p[2].exp);
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(2));
                mvprintw(4, 0, "2.\U0001F948 %s(legend)                 %d                   %d                   %d                 %d", p[1].name, p[1].score, p[1].gold, p[1].n_login, p[1].exp);
                attroff(COLOR_PAIR(2));
                attron(COLOR_PAIR(4));
                mvprintw(6, 0, "\U000027A13.\U0001F949 %s(champ)                  %d                   %d                   %d                 %d", p[0].name, p[0].score, p[0].gold, p[0].n_login, p[0].exp);
                attroff(COLOR_PAIR(4));
            }

            else if(strcmp(player.name, "mahdi0110") == 0) {
                attron(COLOR_PAIR(1));

                mvprintw(2, 0, "\U000027A11.\U0001F947 %s(goat)                   %d                   %d                   %d                 %d", p[2].name, p[2].score, p[2].gold, p[2].n_login, p[2].exp);
                attron(COLOR_PAIR(1));
                attron(COLOR_PAIR(2));

                mvprintw(4, 0, "2.\U0001F948 %s(legend)                 %d                   %d                   %d                 %d", p[1].name, p[1].score, p[1].gold, p[1].n_login, p[1].exp);
                attron(COLOR_PAIR(2));
                attron(COLOR_PAIR(4));

                mvprintw(6, 0, "3.\U0001F949 %s(champ)                  %d                   %d                   %d                 %d", p[0].name, p[0].score, p[0].gold, p[0].n_login, p[0].exp);
                attron(COLOR_PAIR(4));

            }
            else if(strcmp(player.name, "TAmabani") == 0) {
                attron(COLOR_PAIR(1));
                
                mvprintw(2, 0, "1.\U0001F947 %s(goat)                   %d                   %d                   %d                 %d", p[2].name, p[2].score, p[2].gold, p[2].n_login, p[2].exp);
                attron(COLOR_PAIR(1));
                attron(COLOR_PAIR(2));
                
                mvprintw(4, 0, "\U000027A12.\U0001F948 %s(legend)                 %d                   %d                   %d                 %d", p[1].name, p[1].score, p[1].gold, p[1].n_login, p[1].exp);
                attron(COLOR_PAIR(2));
                attron(COLOR_PAIR(4));
                
                mvprintw(6, 0, "3.\U0001F949 %s(champ)                  %d                   %d                   %d                 %d", p[0].name, p[0].score, p[0].gold, p[0].n_login, p[0].exp);
                attron(COLOR_PAIR(4));
            
            }
            refresh();
        }
        else if(p[0].score <= p[2].score && p[2].score <= p[1].score) {
            if(strcmp(player.name, "mahdi0x06") == 0) {
                attron(COLOR_PAIR(1));
                
                mvprintw(2, 0, "1.\U0001F947 %s(goat)                   %d                   %d                   %d                 %d", p[1].name, p[1].score, p[1].gold, p[1].n_login, p[1].exp);
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(2));
                
                mvprintw(4, 0, "2.\U0001F948 %s(legend)                 %d                   %d                   %d                 %d", p[2].name, p[2].score, p[2].gold, p[2].n_login, p[2].exp);
                attroff(COLOR_PAIR(2));
                attron(COLOR_PAIR(4));
                
                mvprintw(6, 0, "\U000027A13.\U0001F949 %s(champ)                  %d                   %d                   %d                 %d", p[0].name, p[0].score, p[0].gold, p[0].n_login, p[0].exp); 
                attroff(COLOR_PAIR(4));
            
            }
            else if(strcmp(player.name, "mahdi0110") == 0) {
                attron(COLOR_PAIR(1));
                
                mvprintw(2, 0, "\U000027A11.\U0001F947 %s(goat)                   %d                   %d                   %d                 %d", p[1].name, p[1].score, p[1].gold, p[1].n_login, p[1].exp);
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(2));
                
                mvprintw(4, 0, "2.\U0001F948 %s(legend)                 %d                   %d                   %d                 %d", p[2].name, p[2].score, p[2].gold, p[2].n_login, p[2].exp);
                attroff(COLOR_PAIR(2));
                attron(COLOR_PAIR(4));
                
                mvprintw(6, 0, "3.\U0001F949 %s(champ)                  %d                   %d                   %d                 %d", p[0].name, p[0].score, p[0].gold, p[0].n_login, p[0].exp); 
                attroff(COLOR_PAIR(4));
            
            }
            else if(strcmp(player.name, "TAmabani") == 0) {
                attron(COLOR_PAIR(1));
                
                mvprintw(2, 0, "1.\U0001F947 %s(goat)                   %d                   %d                   %d                 %d", p[1].name, p[1].score, p[1].gold, p[1].n_login, p[1].exp);
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(2));
                
                mvprintw(4, 0, "\U000027A12.\U0001F948 %s(legend)                 %d                   %d                   %d                 %d", p[2].name, p[2].score, p[2].gold, p[2].n_login, p[2].exp);
                attroff(COLOR_PAIR(2));
                attron(COLOR_PAIR(4));
                
                mvprintw(6, 0, "3.\U0001F949 %s(champ)                  %d                   %d                   %d                 %d", p[0].name, p[0].score, p[0].gold, p[0].n_login, p[0].exp); 
                attroff(COLOR_PAIR(4));
            
            }
           refresh(); 
        }
        else if(p[1].score <= p[0].score && p[0].score <= p[2].score) {
            if(strcmp(player.name, "mahdi0x06") == 0) {
                attron(COLOR_PAIR(1));
                
                mvprintw(2, 0, "1.\U0001F947 %s(goat)                   %d                   %d                   %d                 %d", p[2].name, p[2].score, p[2].gold, p[2].n_login, p[2].exp);
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(2));
                
                mvprintw(4, 0, "\U000027A12.\U0001F948 %s(legend)                 %d                   %d                   %d                 %d", p[0].name, p[0].score, p[0].gold, p[0].n_login, p[0].exp);
                attroff(COLOR_PAIR(2));
                attron(COLOR_PAIR(4));
                
                mvprintw(6, 0, "3.\U0001F949 %s(champ)                  %d                   %d                   %d                 %d", p[1].name, p[1].score, p[1].gold, p[1].n_login, p[1].exp); 
                attroff(COLOR_PAIR(4));
            
            }
            else if(strcmp(player.name, "mahdi0110") == 0) {
                attron(COLOR_PAIR(1));
            
                mvprintw(2, 0, "1.\U0001F947 %s(goat)                   %d                   %d                   %d                 %d", p[2].name, p[2].score, p[2].gold, p[2].n_login, p[2].exp);
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(2));
            
                mvprintw(4, 0, "2.\U0001F948 %s(legend)                 %d                   %d                   %d                 %d", p[0].name, p[0].score, p[0].gold, p[0].n_login, p[0].exp);
                attroff(COLOR_PAIR(2));
                attron(COLOR_PAIR(4));
            
                mvprintw(6, 0, "\U000027A13.\U0001F949 %s(champ)                  %d                   %d                   %d                 %d", p[1].name, p[1].score, p[1].gold, p[1].n_login, p[1].exp); 
                attroff(COLOR_PAIR(4));
            
            }
            else if(strcmp(player.name, "TAmabani") == 0) {
                attron(COLOR_PAIR(1));
            
                mvprintw(2, 0, "\U000027A11.\U0001F947 %s(goat)                   %d                   %d                   %d                 %d", p[2].name, p[2].score, p[2].gold, p[2].n_login, p[2].exp);
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(2));
            
                mvprintw(4, 0, "2.\U0001F948 %s(legend)                 %d                   %d                   %d                 %d", p[0].name, p[0].score, p[0].gold, p[0].n_login, p[0].exp);
                attroff(COLOR_PAIR(2));
                attron(COLOR_PAIR(4));
            
                mvprintw(6, 0, "3.\U0001F949 %s(champ)                  %d                   %d                   %d                 %d", p[1].name, p[1].score, p[1].gold, p[1].n_login, p[1].exp); 
                attroff(COLOR_PAIR(4));
            
            }
            refresh(); 
        }
        else if(p[1].score <= p[2].score && p[2].score <= p[0].score) {
            if(strcmp(player.name, "mahdi0x06") == 0) {
                attron(COLOR_PAIR(1));
            
                mvprintw(2, 0, "\U000027A11.\U0001F947 %s(goat)                   %d                   %d                   %d                 %d", p[0].name, p[0].score, p[0].gold, p[0].n_login, p[0].exp);
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(2));
            
                mvprintw(4, 0, "2.\U0001F948 %s(legend)                 %d                   %d                   %d                 %d", p[2].name, p[2].score, p[2].gold, p[2].n_login, p[2].exp);
                attroff(COLOR_PAIR(2));
                attron(COLOR_PAIR(4));
            
                mvprintw(6, 0, "3.\U0001F949 %s(champ)                  %d                   %d                   %d                 %d", p[1].name, p[1].score, p[1].gold, p[1].n_login, p[1].exp);  
                attroff(COLOR_PAIR(4));
            
            }
            else if(strcmp(player.name, "mahdi0110") == 0) {
                attron(COLOR_PAIR(1));
            
                mvprintw(2, 0, "1.\U0001F947 %s(goat)                   %d                   %d                   %d                 %d", p[0].name, p[0].score, p[0].gold, p[0].n_login, p[0].exp);
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(2));
            
                mvprintw(4, 0, "2.\U0001F948 %s(legend)                 %d                   %d                   %d                 %d", p[2].name, p[2].score, p[2].gold, p[2].n_login, p[2].exp);
                attroff(COLOR_PAIR(2));
                attron(COLOR_PAIR(4));
            
                mvprintw(6, 0, "\U000027A13.\U0001F949 %s(champ)                  %d                   %d                   %d                 %d", p[1].name, p[1].score, p[1].gold, p[1].n_login, p[1].exp);  
                attroff(COLOR_PAIR(4));
            
            }
            else if(strcmp(player.name, "TAmabani") == 0) {
                attron(COLOR_PAIR(1));
            
                mvprintw(2, 0, "1.\U0001F947 %s(goat)                   %d                   %d                   %d                 %d", p[0].name, p[0].score, p[0].gold, p[0].n_login, p[0].exp);
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(2));
            
                mvprintw(4, 0, "\U000027A12.\U0001F948 %s(legend)                 %d                   %d                   %d                 %d", p[2].name, p[2].score, p[2].gold, p[2].n_login, p[2].exp);
                attroff(COLOR_PAIR(2));
                attron(COLOR_PAIR(4));
            
                mvprintw(6, 0, "3.\U0001F949 %s(champ)                  %d                   %d                   %d                 %d", p[1].name, p[1].score, p[1].gold, p[1].n_login, p[1].exp);   
                attroff(COLOR_PAIR(4));
            
            }
            refresh();
        }
        else if(p[2].score <= p[1].score && p[1].score <= p[0].score) {
            if(strcmp(player.name, "mahdi0x06") == 0) {
                attron(COLOR_PAIR(1));
            
                mvprintw(2, 0, "\U000027A11.\U0001F947 %s(goat)                   %d                   %d                   %d                 %d", p[0].name, p[0].score, p[0].gold, p[0].n_login, p[0].exp);
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(2));
            
                mvprintw(4, 0, "2.\U0001F948 %s(legend)                  %d                   %d                   %d                 %d", p[1].name, p[1].score, p[1].gold, p[1].n_login, p[1].exp);
                attroff(COLOR_PAIR(2));
                attron(COLOR_PAIR(4));
            
                mvprintw(6, 0, "3.\U0001F949 %s(champ)                    %d                   %d                   %d                 %d", p[2].name, p[2].score, p[2].gold, p[2].n_login, p[2].exp);
                attroff(COLOR_PAIR(4));
            
            }
            else if(strcmp(player.name, "mahdi0110") == 0) {
                attron(COLOR_PAIR(1));
            
                mvprintw(2, 0, "1.\U0001F947 %s(goat)                   %d                   %d                   %d                 %d", p[0].name, p[0].score, p[0].gold, p[0].n_login, p[0].exp);
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(2));
            
                mvprintw(4, 0, "\U000027A12.\U0001F948 %s(legend)                  %d                   %d                   %d                 %d", p[1].name, p[1].score, p[1].gold, p[1].n_login, p[1].exp);
                attroff(COLOR_PAIR(2));
                attron(COLOR_PAIR(4));
            
                mvprintw(6, 0, "3.\U0001F949 %s(champ)                    %d                   %d                   %d                 %d", p[2].name, p[2].score, p[2].gold, p[2].n_login, p[2].exp);    
                attroff(COLOR_PAIR(4));
            
            }
            else if(strcmp(player.name, "TAmabani") == 0) {
                attron(COLOR_PAIR(1));
            
                mvprintw(2, 0, "1.\U0001F947 %s(goat)                   %d                   %d                   %d                 %d", p[0].name, p[0].score, p[0].gold, p[0].n_login, p[0].exp);
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(2));
            
                mvprintw(4, 0, "2.\U0001F948 %s(legend)                  %d                   %d                   %d                 %d", p[1].name, p[1].score, p[1].gold, p[1].n_login, p[1].exp);
                attroff(COLOR_PAIR(2));
                attron(COLOR_PAIR(4));
            
                mvprintw(6, 0, "\U000027A13.\U0001F949 %s(champ)                    %d                   %d                   %d                 %d", p[2].name, p[2].score, p[2].gold, p[2].n_login, p[2].exp);   
                attroff(COLOR_PAIR(4));
            
            }
            refresh();
        }
        else if(p[2].score <= p[0].score && p[0].score <= p[1].score) {
            if(strcmp(player.name, "mahdi0x06") == 0) {
                attron(COLOR_PAIR(1));
                
                mvprintw(2, 0, "1.\U0001F947 %s(goat)                   %d                   %d                   %d                 %d", p[1].name, p[1].score, p[1].gold, p[1].n_login, p[1].exp);
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(2));
            
                mvprintw(4, 0, "\U000027A12.\U0001F948 %s(legend)                 %d                   %d                   %d                 %d", p[0].name, p[0].score, p[0].gold, p[0].n_login, p[0].exp);
                attroff(COLOR_PAIR(2));
                attron(COLOR_PAIR(4));
            
                mvprintw(6, 0, "3.\U0001F949 %s(champ)                  %d                   %d                   %d                 %d", p[2].name, p[2].score, p[2].gold, p[2].n_login, p[2].exp);
                attroff(COLOR_PAIR(4));
            
            }
            else if(strcmp(player.name, "mahdi0110") == 0) {
                attron(COLOR_PAIR(1));
            
                mvprintw(2, 0, "\U000027A11.\U0001F947 %s(goat)                   %d                   %d                   %d                 %d", p[1].name, p[1].score, p[1].gold, p[1].n_login, p[1].exp);
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(2));
            
                mvprintw(4, 0, "2.\U0001F948 %s(legend)                 %d                   %d                   %d                 %d", p[0].name, p[0].score, p[0].gold, p[0].n_login, p[0].exp);
                attroff(COLOR_PAIR(2));
                attron(COLOR_PAIR(4));
            
                mvprintw(6, 0, "3.\U0001F949 %s(champ)                  %d                   %d                   %d                 %d", p[2].name, p[2].score, p[2].gold, p[2].n_login, p[2].exp);
                attroff(COLOR_PAIR(4));
            
            }
            else if(strcmp(player.name, "TAmabani") == 0) {
                attron(COLOR_PAIR(1));
            
                mvprintw(2, 0, "1.\U0001F947 %s(goat)                   %d                   %d                   %d                 %d", p[1].name, p[1].score, p[1].gold, p[1].n_login, p[1].exp);
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(2));
            
                mvprintw(4, 0, "2.\U0001F948 %s(legend)                 %d                   %d                   %d                 %d", p[0].name, p[0].score, p[0].gold, p[0].n_login, p[0].exp);
                attroff(COLOR_PAIR(2));
                attron(COLOR_PAIR(4));
            
                mvprintw(6, 0, "\U000027A13.\U0001F949 %s(champ)                  %d                   %d                   %d                 %d", p[2].name, p[2].score, p[2].gold, p[2].n_login, p[2].exp); 
                attroff(COLOR_PAIR(4));
            
            
            }
            refresh();
        }
        char c = getchar();
        if(c == '0') {
            break;
        }
    }
    menu();
}

void difficulty() {
    clear(); 
    mvprintw(0,0, "0:back");
    mvprintw(20,83, "1:easy");
    mvprintw(21,83, "2:medium");
    mvprintw(22,83, "3:hard");
    mvprintw(23,83, "4:miyazaki");
    refresh();
    while(1) {
        char n = getchar();
        if(n == '1') {
            player.health = 900;
        }
        else if(n == '2') {
            player.health = 700;
        }
        else if(n == '3') {
            player.health = 500;
        }
        else if(n == '4') {
            player.health = 300;
        }
        else if(n == '0') {
        }
        break;
    }
    // setting();
}

void character_color() {
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
        }
        else if(n == '2') {
            player.color = 2;
        }
        else if(n == '3') {
            player.color = 4;
        }
        else if(n == '0') {
        }
        else{continue;}
        break;
    }
    //setting();
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
            difficulty();
        }
        else if(n == '2') {
           character_color();
        } 
        else if(n == '3') {
            clear(); 
        }
        else if(n == '0') {
        }
        else {continue;}
        break;
    }
    menu();

}

void create_map(char*** board) {
    if(floor == 4) {
    for(int i = 20; i < 32; i++) {
        for(int j = 90; j < 102; j++) {
            if(i == 22 && j == 92) {
                board5[i][j] = 'e';
                demon[5].x = 22;
                demon[5].y = 92;
            }
            else if(i == 24 && j == 94) {
                board5[i][j] = 'f';
                fire[5].x = 24;
                fire[5].y = 94;
            }
            else if(i == 26 && j == 96) {
                board5[i][j] = 'i';
                giant[5].x = 26;
                giant[5].y = 96;
            }
            else if(i == 28 && j == 98) {
                board5[i][j] = 'n';  
                snake[5].x = 28;
                snake[5].y = 98; 
            }
            else if(i == 30 && j == 100) {
                board5[i][j] = 'u'; 
                undeed[5].x = 30;
                undeed[5].y = 100;   
            }
            else if(i == 22 && j == 94) {
                board5[i][j] = 'g';    
            }
            else if(i == 23 && j == 100) {
                board5[i][j] = 'g';    
            }
            else if(i == 30 && j == 101) {
                board5[i][j] = 'g';    
            }
            else if(i == 25 && j == 94) {
                board5[i][j] = 'G';    
            }
            else if(i == 21 && j == 101) {
                board5[i][j] = 'G';    
            }
            else if(i == 29 && j == 91) {
                board5[i][j] = 'G';    
            }
            else if(i == 30 && j == 92) {
                board5[i][j] = '^';    
            }
            else if(i == 29 && j == 100) {
                board5[i][j] = '^';    
            }
            else if(i == 30 && j == 101) {
                board5[i][j] = '^';    
            }
            else if(i == 22 && j == 101) {
                board5[i][j] = '^';    
            }
            else if(i == 23 && j == 97) {
                board5[i][j] = '^';    
            }
            else if(i == 26 && j == 97) {
                board5[i][j] = '^';    
            }
            else if(i == 20 && j == 93) {
                board5[i][j] = '^';    
            }
            else if(i == 20 && j == 94) {
                board5[i][j] = '^';    
            }
            else if(i == 31 && j == 101) {
                board5[i][j] = 'q';    
            }
            else {
                board5[i][j] = '.';
            }
        }
    }
    for(int i = 20; i < 32; i++) {
        board5[i][89] = '|';
        board5[i][102] = '|';
    }
    for(int j = 90; j < 102; j++) {
        board5[19][j] = '_';
        board5[32][j] = '_';
    }
    }
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
        room[floor][i].x = rand() % (34) + 4;
        room[floor][i].y = rand() % (157) + 19;
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
            room[floor][i].x = rand() % (34) + 4;
            room[floor][i].y = rand() % (157) + 19;
        }
        x = check_room(room);
    }
    int nfood = rand() % (4) + 3;
    int nfood1 = rand() % (4) + 3;
    int nfood2 = rand() % (4) + 3;
    int nfood3 = rand() % (4) + 3;
    int ngold = rand() % (4) + 3;
    for(int i = 0; i < 6; i++) {
        room[floor][i].I = rand() % (5) + 5;
        room[floor][i].J = rand() % (7) + 6;
        int x = rand() % (2) + 1;
        int X = rand() % (room[floor][i].I - 2) + room[floor][i].x + 1;
        int Y = rand () % (room[floor][i].J - 2) + room[floor][i].y + 1;
        int food_x = rand() % (room[floor][i].I - 2) + room[floor][i].x + 1;
        int food_x1 = rand() % (room[floor][i].I - 2) + room[floor][i].x + 1;
        int food_x2 = rand() % (room[floor][i].I - 2) + room[floor][i].x + 1;
        int food_x3 = rand() % (room[floor][i].I - 2) + room[floor][i].x + 1;
        int gold_x = rand() % (room[floor][i].I - 2) + room[floor][i].x + 1;
        int door;
        if(floor == 1 && i == 0) {
            IJ[0].x = room[floor][i].I;
            IJ[0].y = room[floor][i].J;
        }
        else if(floor == 2 && i == 1) {
            IJ[1].x = room[floor][i].I;
            IJ[1].y = room[floor][i].J;
        }
        else if(floor == 3 && i == 2) {
            IJ[2].x = room[floor][i].I;
            IJ[2].y = room[floor][i].J;
        }
        if(floor == 2 && i == 0) {
            room[floor][i].I = IJ[0].x;
            room[floor][i].J = IJ[0].y;
        }
        else if(floor == 3 && i == 1) {
            room[floor][i].I = IJ[1].x;
            room[floor][i].J = IJ[1].y;
        }
        else if(floor == 4 && i == 2) {
            room[floor][i].I = IJ[2].x;
            room[floor][i].J = IJ[2].y;
        }
        if(x == 1) {
            door = rand() % (room[floor][i].I) + room[floor][i].x;
        }
        else {
            door = rand () % (room[floor][i].J) + room[floor][i].y;
        }
        while (abs(door - X) < 1 || abs(door - Y) < 1) {
            if(x == 1) {
                door = rand() % (room[floor][i].I) + room[floor][i].x;
            }
            else {
                door = rand () % (room[floor][i].J) + room[floor][i].y;
            }
        }
        if(floor == 1 && i == 1) {
            player.x = X;
            player.y = Y + 1;
            for(int j = room[floor][i].x - 1; j <= room[floor][i].x + room[floor][i].I; j++) {
                for(int q = room[floor][i].y - 1; q <= room[floor][i].y  + room[floor][i].J; q++) {
                    flag[floor][j][q] = 1;
                }
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
        for(int j = room[floor][i].x; j < room[floor][i].x + room[floor][i].I; j++) {
            for(int q = room[floor][i].y; q < room[floor][i].y + room[floor][i].J; q++) {
                if(j == X && q == Y) {
                    (*board)[j][q] = 'O';
                    room[floor][i].c[j][q] = 'O';
                    continue;
                }
                else if(floor == 4 && i == 5 && j == room[floor][i].x + room[floor][i].I - 1 && q == room[floor][i].y + room[floor][i].J - 1) {
                    (*board)[j][q] = '>';
                    room[floor][i].c[j][q] = '>';
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
                else if(floor == 1 && i == 5 && j == room[floor][i].x + 3 && q == room[floor][i].y + room[floor][i].J) {
                    (*board)[j][q] = '?';
                    room[floor][i].c[j][q] = '?';
                    continue;
                }
                else if(i == 5 && j == room[floor][i].x + room[floor][i].I - 1 && q == room[floor][i].y + 2) {
                    (*board)[j][q] = 'd';
                    room[floor][i].c[j][q] = 'd';
                    continue;
                }
                else if(i == 4 && j == room[floor][i].x + room[floor][i].I - 1 && q == room[floor][i].y + 1) {
                    (*board)[j][q] = 'a';
                    room[floor][i].c[j][q] = 'a';
                    continue;
                }
                else if(i == 3 && j == room[floor][i].x + room[floor][i].I - 1 && q == room[floor][i].y + 3) {
                    (*board)[j][q] = 'm';
                    room[floor][i].c[j][q] = 'm';
                    continue;
                }
                else if(i == 1 && j == room[floor][i].x + room[floor][i].I - 1 && q == room[floor][i].y + 5) {
                    (*board)[j][q] = 'e';
                    room[floor][i].c[j][q] = 'e';
                    demon[floor].x = j;
                    demon[floor].y = q;
                    continue;
                }
                else if(i == 2 && j == room[floor][i].x + room[floor][i].I - 1 && q == room[floor][i].y + 4) {
                    (*board)[j][q] = 'f';
                    room[floor][i].c[j][q] = 'f';
                    fire[floor].x = j;
                    fire[floor].y = q;
                    continue;
                }
                else if(i == 3 && j == room[floor][i].x + room[floor][i].I - 1 && q == room[floor][i].y + 4) {
                    (*board)[j][q] = 'i';
                    room[floor][i].c[j][q] = 'i';
                    giant[floor].x = j;
                    giant[floor].y = q;
                    continue;
                }
                else if(i == 4 && j == room[floor][i].x + room[floor][i].I - 1 && q == room[floor][i].y + 4) {
                    (*board)[j][q] = 'n';
                    room[floor][i].c[j][q] = 'n';
                    snake[floor].x = j;
                    snake[floor].y = q;
                    continue;
                }
                else if(i == 5 && j == room[floor][i].x + room[floor][i].I - 1 && q == room[floor][i].y + 4) {
                    (*board)[j][q] = 'u';
                    room[floor][i].c[j][q] = 'u';
                    undeed[floor].x = j;
                    undeed[floor].y = q;
                    continue;
                }
                else if(i == 2 && j == room[floor][i].x + room[floor][i].I - 1 && q == room[floor][i].y + 3 && floor == 2) {
                    (*board)[j][q] = 's';
                    room[floor][i].c[j][q] = 's';
                    continue;
                }
                else if(i == 1 && j == room[floor][i].x + room[floor][i].I - 1 && q == room[floor][i].y + 3) {
                    (*board)[j][q] = 'h';
                    room[floor][i].c[j][q] = 'h';
                    continue;
                }
                else if(i == 0 && j == room[floor][i].x + room[floor][i].I - 1 && q == room[floor][i].y + 2 && (floor == 2 || floor == 3 || floor == 4)) {
                    (*board)[j][q] = 'S';
                    room[floor][i].c[j][q] = 'S';
                    continue;
                }
                else if(i == 3 && j == room[floor][i].x + room[floor][i].I - 1 && q == room[floor][i].y + 2 && (floor == 3 || floor == 4)) {
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
                else if(j == room[floor][i].x + room[floor][i].I - 1 && q == room[floor][i].y + room[floor][i].J - 1 && i == 4) {
                    (*board)[j][q] = '&';
                    room[floor][i].c[j][q] = '&';
                    attron(COLOR_PAIR(8));
                    refresh();
                    continue;
                }
                else if(j == room[floor][i].x && q == room[floor][i].y + room[floor][i].J - 1 && i == 1) {
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

        for(int j = room[floor][i].y; j < room[floor][i].y + room[floor][i].J; j++) {
            if(x == 2 && door == j) {
                (*board)[room[floor][i].x - 1][j] = '+';
                room[floor][i].c[room[floor][i].x][j] = '+';
                (*board)[room[floor][i].x + room[floor][i].I][j] = '_';
                room[floor][i].c[room[floor][i].x + room[floor][i].I][j] = '_';
                room[floor][i].door.x = room[floor][i].x - 1;
                room[floor][i].door.y = j;
                continue;
            }
            (*board)[room[floor][i].x - 1][j] = '_';
            room[floor][i].c[room[floor][i].x][j] = '_';
            (*board)[room[floor][i].x + room[floor][i].I][j] = '_';
            room[floor][i].c[room[floor][i].x + room[floor][i].I][j] = '_';
        }
        for(int j = room[floor][i].x; j < room[floor][i].x + room[floor][i].I; j++) {
            if(x == 1 && door == j) {
                (*board)[j][room[floor][i].y - 1] = '+';
                room[floor][i].c[j][room[floor][i].y] = '+';
                (*board)[j][room[floor][i].y + room[floor][i].J] = '|';
                room[floor][i].c[j][room[floor][i].y + room[floor][i].J] = '|';
                room[floor][i].door.x = j;
                room[floor][i].door.y = room[floor][i].y - 1;
                continue;
            }
                (*board)[j][room[floor][i].y - 1] = '|';
                room[floor][i].c[j][room[floor][i].y] = '|';
                (*board)[j][room[floor][i].y + room[floor][i].J] = '|';
                room[floor][i].c[j][room[floor][i].y + room[floor][i].J] = '|';
        }
        if(nfood) {
            if((*board)[food_x][room[floor][i].J + room[floor][i].y - 1] != 'T' && (*board)[food_x][room[floor][i].J + room[floor][i].y - 1] != '@' && (*board)[food_x][room[floor][i].J + room[floor][i].y - 1] != '&' && (*board)[food_x][room[floor][i].y + room[floor][i].J - 1] != '<' && (*board)[food_x][room[floor][i].y + room[floor][i].J - 1] != '+') {
                (*board)[food_x][room[floor][i].J + room[floor][i].y - 1] = 'F';
                nfood--;
            }
        }
        if(nfood1) {
            if((*board)[food_x1][room[floor][i].J + room[floor][i].y - 2] != 'T' && (*board)[food_x1][room[floor][i].J + room[floor][i].y - 2] != '@' && (*board)[food_x1][room[floor][i].J + room[floor][i].y - 2] != '&' && (*board)[food_x1][room[floor][i].y + room[floor][i].J - 2] != '<' && (*board)[food_x1][room[floor][i].y + room[floor][i].J - 2] != '+') {
                (*board)[food_x1][room[floor][i].J + room[floor][i].y - 2] = 'z';
                nfood1--;
            }
        }
        if(nfood2) {
            if((*board)[food_x2][room[floor][i].J + room[floor][i].y - 3] != 'T' && (*board)[food_x2][room[floor][i].J + room[floor][i].y - 3] != '@' && (*board)[food_x2][room[floor][i].J + room[floor][i].y - 3] != '&' && (*board)[food_x2][room[floor][i].y + room[floor][i].J - 3] != '<' && (*board)[food_x2][room[floor][i].y + room[floor][i].J - 3] != '+') {
                (*board)[food_x2][room[floor][i].J + room[floor][i].y - 3] = 'x';
                nfood2--;
            }
        }
        if(nfood3) {
            if((*board)[food_x3][room[floor][i].J + room[floor][i].y - 4] != 'T' && (*board)[food_x3][room[floor][i].J + room[floor][i].y - 4] != '@' && (*board)[food_x3][room[floor][i].J + room[floor][i].y - 4] != '&' && (*board)[food_x3][room[floor][i].y + room[floor][i].J - 4] != '<' && (*board)[food_x2][room[floor][i].y + room[floor][i].J - 4] != '+') {
                (*board)[food_x3][room[floor][i].J + room[floor][i].y - 4] = 'y';
                nfood3--;
            }
        }
    }
    (*board)[room[1][5].x + 3][room[1][5].y + room[1][5].J] = '?';

    Doors(board);
}

int check_room(Room** room) {
    for(int i = 0; i < 5; i++) {
        for(int j = i + 1; j < 6; j++) {
            if(abs(room[floor][i].y - room[floor][j].y) <= 23 ) {
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
            if(flag[floor][i][j]) {
                if(board[i][j] == '<') {
                    attron(COLOR_PAIR(12));
                    mvprintw(i, j, "%c", board[i][j]);
                    refresh();
                    attroff(COLOR_PAIR(12));
                }
                else if(board[i][j] == '>') {
                    attron(COLOR_PAIR(13));
                    mvprintw(i, j, "%c", board[i][j]);
                    refresh();
                    attroff(COLOR_PAIR(13));
                }
                else if(board[i][j] == 'q') {
                    //attron(COLOR_PAIR(18));
                    mvaddstr(i, j, "\U000023FB");
                    refresh();
                    //attroff(COLOR_PAIR(18));
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
                    mvprintw(i, j, "\U00002591");
                    attroff(COLOR_PAIR(9));
                }
                else if(board[i][j] == '_') {
                    if(floor == 5) {
                        attron(COLOR_PAIR(13));
                        mvprintw(i, j, "_");
                        attroff(COLOR_PAIR(13));     
                    }
                    else if(floor == 1 && (i == room[floor][0].x - 1 || i == room[floor][0].x + room[floor][0].I) && room[floor][0].y <= j && j < room[floor][0].y + room[floor][0].J) {
                        attron(COLOR_PAIR(31));
                        mvprintw(i, j, "_");
                        attroff(COLOR_PAIR(31));  
                    }
                    else {
                        attron(COLOR_PAIR(14));
                        mvprintw(i, j, "_");
                        attroff(COLOR_PAIR(14));
                    }
                }
                else if(board[i][j] == '|') {
                    if(floor == 5) {
                        attron(COLOR_PAIR(13));
                        mvprintw(i, j, "|");
                        attroff(COLOR_PAIR(13));     
                    }
                    else if(floor == 1 && (j == room[floor][0].y - 1 || j == room[floor][0].y + room[floor][0].J) && room[floor][0].x <= i && i < room[floor][0].x + room[floor][0].I) {
                        attron(COLOR_PAIR(31));
                        mvprintw(i, j, "|");
                        attroff(COLOR_PAIR(31));  
                    }
                    else {
                        attron(COLOR_PAIR(14));
                        mvprintw(i, j, "|");
                        attroff(COLOR_PAIR(14));
                    }
                }
                else if(board[i][j] == 'F' || board[i][j] == 'y') {
                    attron(COLOR_PAIR(8));
                    mvaddstr(i, j, "\U000101DB");
                    refresh();
                    attroff(COLOR_PAIR(8));
                }
                else if(board[i][j] == 'x') {
                    attron(COLOR_PAIR(31));
                    mvaddstr(i, j, "\U000027C1");
                    refresh();
                    attroff(COLOR_PAIR(31));
                }
                else if(board[i][j] == 'z') {
                    attron(COLOR_PAIR(13));
                    mvaddstr(i, j, "\U00002618");
                    refresh();
                    attroff(COLOR_PAIR(13));
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
                else if(board[i][j] == 'a' || board[i][j] == 'A') {
                    attron(COLOR_PAIR(9));
                    mvaddstr(i, j, "\U000027B3");
                    refresh();
                    attroff(COLOR_PAIR(9));
                }
                else if(board[i][j] == 'm' || board[i][j] == 'M') {
                    attron(COLOR_PAIR(9));
                    mvaddstr(i, j, "\U00002133");
                    refresh();
                    attroff(COLOR_PAIR(9));
                }
                else if(board[i][j] == 'd' || board[i][j] == 'r') {
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
                        attron(COLOR_PAIR(14));
                        mvaddstr(i, j, "|");
                        refresh();
                        attroff(COLOR_PAIR(14));  
                    }
                }
                else if(board[i][j] == '.' || board[i][j] == 'O' || board[i][j] == '+'){
                    attron(COLOR_PAIR(8));
                    mvprintw(i, j, "%c", board[i][j]);
                    refresh();
                    attroff(COLOR_PAIR(8));
                }
            }
        }
    }
    attron(COLOR_PAIR(10));
    mvprintw(player.x, player.y, "H"); 
    attroff(COLOR_PAIR(10));
    refresh();
}

void Doors(char*** board) {
    for(int i = 0; i < 6; i++) {
        int p = i;
        pos temp;
        temp.x = room[floor][p].door.x;
        temp.y = room[floor][p].door.y;
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
            while(temp.x < room[floor][p + 1].door.x) {
                if(temp.x == room[floor][p + 1].door.x && temp.y + 1 == room[floor][p + 1].door.y) {
                    break;
                }
                else if(temp.x + 1 == room[floor][p + 1].door.x && temp.y == room[floor][p + 1].door.y) {
                    break;
                }
                else if(temp.x == room[floor][p + 1].door.x && temp.y - 1 == room[floor][p + 1].door.y) {
                    break;
                }
                else if(temp.x - 1 == room[floor][p + 1].door.x && temp.y == room[floor][p + 1].door.y) {
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
            while(temp.x > room[floor][p + 1].door.x) {
                if(temp.x == room[floor][p + 1].door.x && temp.y + 1 == room[floor][p + 1].door.y) {
                    break;
                }
                else if(temp.x + 1 == room[floor][p + 1].door.x && temp.y == room[floor][p + 1].door.y) {
                    break;
                }
                else if(temp.x == room[floor][p + 1].door.x && temp.y - 1 == room[floor][p + 1].door.y) {
                    break;
                }
                else if(temp.x - 1 == room[floor][p + 1].door.x && temp.y == room[floor][p + 1].door.y) {
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
            while(temp.y < room[floor][p + 1].door.y) {
                if(temp.x == room[floor][p + 1].door.x && temp.y + 1 == room[floor][p + 1].door.y) {
                    break;
                }
                else if(temp.x + 1 == room[floor][p + 1].door.x && temp.y == room[floor][p + 1].door.y) {
                    break;
                }
                else if(temp.x == room[floor][p + 1].door.x && temp.y - 1 == room[floor][p + 1].door.y) {
                    break;
                }
                else if(temp.x - 1 == room[floor][p + 1].door.x && temp.y == room[floor][p + 1].door.y) {
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
            while(temp.y > room[floor][p + 1].door.y) {
                if(temp.x == room[floor][p + 1].door.x && temp.y + 1 == room[floor][p + 1].door.y) {
                    break;
                }
                else if(temp.x + 1 == room[floor][p + 1].door.x && temp.y == room[floor][p + 1].door.y) {
                    break;
                }
                else if(temp.x == room[floor][p + 1].door.x && temp.y - 1 == room[floor][p + 1].door.y) {
                    break;
                }
                else if(temp.x - 1 == room[floor][p + 1].door.x && temp.y == room[floor][p + 1].door.y) {
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
            if(temp.x == room[floor][p + 1].door.x && temp.y + 1 == room[floor][p + 1].door.y) {
                move(temp.x, temp.y + 1);
                break;
            }
            else if(temp.x + 1 == room[floor][p + 1].door.x && temp.y == room[floor][p + 1].door.y) {
                move(temp.x + 1, temp.y);
                break;
            }
            else if(temp.x == room[floor][p + 1].door.x && temp.y - 1 == room[floor][p + 1].door.y) {
                move(temp.x, temp.y - 1);
                break;
            }
            else if(temp.x - 1 == room[floor][p + 1].door.x && temp.y == room[floor][p + 1].door.y) {
                move(temp.x - 1, temp.y);
                break;
            }
        }
    }
}

void input(char c, char** board) {
    int x = player.x , y = player.y;
    switch (c) {
        case 'M':
            M++;
            show_map(board, M);
        case ' ':
            attack(board);
            print_character(x, y, board);
            break;
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
            if(player.health + 20 <= init_health) {
                if(h) {
                    player.health += 20;
                }
                else {
                    player.health += 10;
                }
            }
            print_character(x, y, board);
            break;
        case 's':
            if(s) {
                player.x += 2;
            }
            else {
                player.x++;
            }
            if(player.health + 20 <= init_health) {
                if(h) {
                    player.health += 20;
                }
                else {
                    player.health += 10;
                }
            }
            print_character(x, y, board);
            break;
        case 'a':
            if(s) {
                player.y -= 2;
            }
            else {
                player.y--;
            }
            if(player.health + 20 <= init_health) {
                if(h) {
                    player.health += 20;
                }
                else {
                    player.health += 10;
                }
            }
            print_character(x, y, board);
            break;
        case 'd':
            if(s) {
                player.y += 2;
            }
            else {
                player.y++;
            }
            if(player.health + 20 <= init_health) {
                if(h) {
                    player.health += 20;
                }
                else {
                    player.health += 10;
                }
            }
            print_character(x, y, board);
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
            if(player.health + 20 <= init_health) {
                if(h) {
                    player.health += 20;
                }
                else {
                    player.health += 10;
                }
            }
            print_character(x, y, board);
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
            if(player.health + 20 <= init_health) {
                if(h) {
                    player.health += 20;
                }
                else {
                    player.health += 10;
                }
            }
            print_character(x, y, board);
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
            if(player.health + 20 <= init_health) {
                if(h) {
                    player.health += 20;
                }
                else {
                    player.health += 10;
                }
            }
            print_character(x, y, board);
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
            if(player.health + 20 <= init_health) {
                if(h) {
                    player.health += 20;
                }
                else {
                    player.health += 10;
                }
            }
            print_character(x, y, board);
            break;
        case 'f':
            char c = getchar();
            if(c == 'w') {
                while(board[player.x - 1][player.y] != ' ' && board[player.x - 1][player.y] != '_' && board[player.x - 1][player.y] != '|' && board[player.x - 1][player.y] != 'O') {
                    player.x--;
                    player.health--;
                }
            }
            else if(c == 's') {
                while(board[player.x + 1][player.y] != ' ' && board[player.x + 1][player.y] != '_' && board[player.x + 1][player.y] != '|' && board[player.x + 1][player.y] != 'O') {
                    player.x++;
                    player.health--;
                }
            }
            else if(c == 'a') {
                while(board[player.x][player.y - 1] != ' ' && board[player.x][player.y - 1] != '_' && board[player.x][player.y - 1] != '|' && board[player.x][player.y - 1] != 'O') {
                    player.y--;
                    player.health--;
                }
            }
            else if(c == 'd') {
                while(board[player.x][player.y + 1] != ' ' && board[player.x][player.y + 1] != '_' && board[player.x][player.y + 1] != '|' && board[player.x][player.y + 1] != 'O') {
                    player.y++;
                    player.health--;
                }
            }
            if(board[x][y] == '.') {
                attron(COLOR_PAIR(8));
                mvprintw(x, y, ".");
                attroff(COLOR_PAIR(8));
            }
            else if(board[x][y] == '#') {
                attron(COLOR_PAIR(9));
                mvprintw(x, y, "\U00002591");
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
            print_character(x, y, board);
            break;
        case 'g':
            char cc = getchar();
            if(cc == 'w') {
                while(board[player.x - 1][player.y] != ' ' && board[player.x - 1][player.y] != '_' && board[player.x - 1][player.y] != '|' && board[player.x - 1][player.y] != 'O') {
                    player.x--;
                    player.health--;
                }
            }
            else if(cc == 's') {
                while(board[player.x + 1][player.y] != ' ' && board[player.x + 1][player.y] != '_' && board[player.x + 1][player.y] != '|' && board[player.x + 1][player.y] != 'O') {
                    player.x++;
                    player.health--;
                }
            }
            else if(cc == 'a') {
                while(board[player.x][player.y - 1] != ' ' && board[player.x][player.y - 1] != '_' && board[player.x][player.y - 1] != '|' && board[player.x][player.y - 1] != 'O') {
                    player.y--;
                    player.health--;
                }
            }
            else if(cc == 'd') {
                while(board[player.x][player.y + 1] != ' ' && board[player.x][player.y + 1] != '_' && board[player.x][player.y + 1] != '|' && board[player.x][player.y + 1] != 'O') {
                    player.y++;
                    player.health--;
                }
            }
            if(board[x][y] == '.') {
                attron(COLOR_PAIR(8));
                mvprintw(x, y, ".");
                attroff(COLOR_PAIR(8));
            }
            else if(board[x][y] == '#') {
                attron(COLOR_PAIR(9));
                mvprintw(x, y, "\U00002591");
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
            print_character(x, y, board);
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
            S(x, y, board);
            // mvprintw(x + 1, y, "%c", board[x + 1][y]);
            // mvprintw(x + 1, y - 1, "%c", board[x + 1][y - 1]);
            // mvprintw(x + 1, y + 1, "%c", board[x + 1][y + 1]);
            // mvprintw(x, y - 1, "%c", board[x][y - 1]);
            // mvprintw(x, y + 1, "%c", board[x][y + 1]);
            // mvprintw(x - 1, y, "%c", board[x - 1][y]);
            // mvprintw(x - 1, y + 1, "%c", board[x - 1][y + 1]);
            // mvprintw(x - 1, y - 1, "%c", board[x - 1][y - 1]);
            // refresh();
            break;
        default:
            break;
    }
}

void S(int x, int y, char** board) {
    if(board[x + 1][y] == '^' || board[x + 1][y] == '?') {
        attron(COLOR_PAIR(12));
        mvprintw(x + 1, y, "%c", board[x + 1][y]);
        attroff(COLOR_PAIR(12));
    }
    else if(board[x + 1][y - 1] == '^' || board[x + 1][y - 1] == '?') {
        attron(COLOR_PAIR(12));
        mvprintw(x + 1, y - 1, "%c", board[x + 1][y - 1]);
        attroff(COLOR_PAIR(12));
    }
    else if(board[x + 1][y + 1] == '^' || board[x + 1][y + 1] == '?') {
        attron(COLOR_PAIR(12));
        mvprintw(x + 1, y + 1, "%c", board[x + 1][y + 1]);
        attroff(COLOR_PAIR(12));   
    }
    else if(board[x][y - 1] == '^' || board[x][y - 1] == '?') {
        attron(COLOR_PAIR(12));
        mvprintw(x, y - 1, "%c", board[x][y - 1]);
        attroff(COLOR_PAIR(12));       
    }
    else if(board[x][y + 1] == '^' || board[x][y + 1] == '?') {
        attron(COLOR_PAIR(12));
        mvprintw(x, y + 1, "%c", board[x][y + 1]);
        attroff(COLOR_PAIR(12));      
    }
    else if(board[x - 1][y] == '^' || board[x - 1][y] == '?') {
        attron(COLOR_PAIR(12));
        mvprintw(x - 1, y, "%c", board[x - 1][y]);
        attroff(COLOR_PAIR(12));      
    }
    else if(board[x - 1][y + 1] == '^' || board[x - 1][y + 1] == '?') {
        attron(COLOR_PAIR(12));
        mvprintw(x - 1, y + 1, "%c", board[x - 1][y + 1]);
        attroff(COLOR_PAIR(12));      
    }
    else if(board[x - 1][y - 1] == '^' || board[x - 1][y - 1] == '?') {
        attron(COLOR_PAIR(12));
        mvprintw(x - 1, y - 1, "%c", board[x - 1][y - 1]);
        attroff(COLOR_PAIR(12));     
    }
    refresh();
}

void show_map(char** board, int M) {
    if(M % 2 == 1) {
        for(int i = 0; i <= 46; i++) {
            for(int j = 0; j <= 189; j++) {
                if(flag[floor][i][j] == 0) {
                    flag[floor][i][j] = 2;
                }
            }
        }
    }
    else {
        for(int i = 0; i <= 46; i++) {
            for(int j = 0; j <= 189; j++) {
                if(flag[floor][i][j] == 2) {
                    flag[floor][i][j] = 0;
                }
            }
        }
    }
    print_map(board);
}

void print_character(int ox, int oy, char** board) {
    switch (board[player.x][player.y]) {
        case 'q':
            if(board[ox][oy] == '.') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            win = 1;

            n_login++;
            player.score = player.gold * 10 + player.exp;
            clear();
            attron(COLOR_PAIR(9));
            mvprintw(23, 93, "You Won");
            mvprintw(24, 93, "Your score:%d", player.score);
            attroff(COLOR_PAIR(9));
            char cc = getchar();
            return;
            break;
        case '>':
            player.hunger--;
            M = 0;
            if(board[ox][oy] == '.') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            char xx = getchar();
            if(xx == '>') {
                floor++;
                player.x = 20;
                player.y = 90;
                print_map(board5);
                mvprintw(0, 0, "                    ");
                mvprintw(0,0,"next floor!");
                refresh();
            }
            //treasure_room();
            break;
        case '?':
            //enchant();
            attron(COLOR_PAIR(16));
            mvprintw(player.x, player.y, "?");
            refresh();
            attroff(COLOR_PAIR(16));
            hidden = 1;
            player.x = room[1][0].door.x;
            player.y = room[1][0].door.y;
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
                board[player.x][player.y] = '.';
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
                board[player.x][player.y] = '.';
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
                board[player.x][player.y] = '.';
                damage++;
            }
            break;
            
        case 'a':
        case 'A':
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
                if(board[player.x][player.y] == 'a') {
                    arrow += 20;
                }
                else if(board[player.x][player.y] == 'A'){
                    arrow ++;
                }
                board[player.x][player.y] = '.';
            }
            break;
        case 'm':
        case 'M':
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
                if(board[player.x][player.y] == 'm') {
                    wand += 8;
                }
                else if(board[player.x][player.y] == 'M') {
                    wand ++;
                }
                board[player.x][player.y] = '.';
            }
            break;
        case 'd':
        case 'r':
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
                if(board[player.x][player.y] == 'd') {
                    dagger += 10;
                }
                else if(board[player.x][player.y] == 'r') {
                    dagger ++;
                }
                board[player.x][player.y] = '.';
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
                board[player.x][player.y] = '.';
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
            if(reg_food <= 4) {
                reg_food++;
            }
            break;
        case 'x':
            player.hunger--;
            if(board[ox][oy] == '.' || board[ox][oy] == 'F' || board[ox][oy] == 'x' || board[ox][oy] == 'z') {
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
            else if(board[ox][oy] == 'y') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'z') {
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
            if(x_food <= 4) {
                x_food++;
            }
            break;
        case 'y':
            player.hunger--;
            if(board[ox][oy] == '.' || board[ox][oy] == 'F' || board[ox][oy] == 'x' || board[ox][oy] == 'z') {
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
            if(y_food <= 4) {
                y_food++;
            }
            break;
        case 'z':
            player.hunger--;
            if(board[ox][oy] == '.' || board[ox][oy] == 'F' || board[ox][oy] == 'x' || board[ox][oy] == 'z') {
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
            if(z_food <= 4) {
                z_food++;
            }
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
                mvprintw(ox, oy, "\U00002591");
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
            check_sharp(board, player.x, player.y);
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
            else if(board[ox][oy] == 'x') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                board[ox][oy] = '.';
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'y') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                board[ox][oy] = '.';
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'z') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                board[ox][oy] = '.';
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
            else if(board[ox][oy] == '<') {
                attron(COLOR_PAIR(11));
                mvprintw(ox, oy, "<");
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
            else if(board[ox][oy] == 'd' || board[ox][oy] == 'r') {
                attron(COLOR_PAIR(9));
                mvprintw(ox, oy, "\U0001F5E1");
                attroff(COLOR_PAIR(9));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'a' || board[ox][oy] == 'A') {
                attron(COLOR_PAIR(9));
                mvprintw(ox, oy, "\U000027B3");
                attroff(COLOR_PAIR(9));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'm' || board[ox][oy] == 'M') {
                attron(COLOR_PAIR(9));
                mvprintw(ox, oy, "\U00002133");
                attroff(COLOR_PAIR(9));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            check_door(board, player.x, player.y);
            break;
        case '^':
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
            M = 0;
            if(board[ox][oy] == '.') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            char x = getchar();
            if(x == '>') {
                floor++;
                clear();
                if(floor == 2) {
                    check_door(board, room[floor][0].door.x, room[floor][0].door.y);
                }
                else if(floor == 3) {
                    check_door(board, room[floor][1].door.x, room[floor][1].door.y);
                    
                }
                else if(floor == 4) {
                    check_door(board, room[floor][2].door.x, room[floor][2].door.y);
                }
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
                mvprintw(0, 0, "                    ");
                mvprintw(0,0,"next floor!");
            }
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
                //board[ox][oy] = '.';
                //mvprintw(ox, oy, ".");
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
    if(floor != 5) {
        if((room[floor][1].x <= player.x && player.x <= room[floor][1].x + room[floor][1].I) && (room[floor][1].y <= player.y && player.y <= room[floor][1].y + room[floor][1].J) && demon[floor].health > 0) {
        refresh();
        if(demon[floor].end-- > 0) {
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
        else {
            if(check_attack(board, 'e')) {
                damage_handle(1);
            }
        }
    }
        else if((room[floor][2].x <= player.x && player.x <= room[floor][2].x + room[floor][2].I) && (room[floor][2].y <= player.y && player.y <= room[floor][2].y + room[floor][2].J) && fire[floor].health > 0) {
        if(fire[floor].end-- > 0) {
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
        else {
            if(check_attack(board, 'f')) {
                damage_handle(2);
            }
        }
    }
        else if((room[floor][3].x <= player.x && player.x <= room[floor][3].x + room[floor][3].I) && (room[floor][3].y <= player.y && player.y <= room[floor][3].y + room[floor][3].J) && giant[floor].health > 0) {
        if(giant[floor].end-- > 0) {
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
        else {
            if(check_attack(board, 'i')) {
                damage_handle(3);
            }
        }
    }
        else if((room[floor][4].x <= player.x && player.x <= room[floor][4].x + room[floor][4].I) && (room[floor][4].y <= player.y && player.y <= room[floor][4].y + room[floor][4].J) && snake[floor].health > 0) {
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
        else if((room[floor][5].x <= player.x && player.x <= room[floor][5].x + room[floor][5].I) && (room[floor][5].y <= player.y && player.y <= room[floor][5].y + room[floor][5].J) && undeed[floor].health > 0) {
        if(undeed[floor].end-- > 0) {
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
        else {
            if(check_attack(board, 'u')) {
                damage_handle(5);
            }
        }
    }
    }
    else if(floor == 5) {
        if(demon[floor].end-- > 0) {
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
        else {
            if(check_attack(board, 'e')) {
                damage_handle(1);
            }
        }
        if(fire[floor].end-- > 0) {
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
        else {
            if(check_attack(board, 'f')) {
                damage_handle(2);
            }
        }
        if(giant[floor].end-- > 0) {
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
        else {
            if(check_attack(board, 'i')) {
                damage_handle(3);
            }
        }
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
        if(undeed[floor].end-- > 0) {
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
        else {
            if(check_attack(board, 'u')) {
                damage_handle(5);
            }
        }

    }
    refresh();
}

void check_sharp(char** board, int x, int y) {
    if(board[x - 1][y] == '#') {
        flag[floor][x - 1][y] = 1;
        attron(COLOR_PAIR(9));
        mvprintw(x - 1, y, "\U00002591");
        attroff(COLOR_PAIR(9));
    }
    else if(board[x - 1][y] == '+') {
        flag[floor][x - 1][y] = 1;
        attron(COLOR_PAIR(8));
        mvprintw(x - 1, y, "+");
        attroff(COLOR_PAIR(8));
    }
    if(board[x + 1][y] == '#') {
        flag[floor][x + 1][y] = 1;
        attron(COLOR_PAIR(9));
        mvprintw(x + 1, y, "\U00002591");
        attroff(COLOR_PAIR(9));
    }
    else if(board[x + 1][y] == '+') {
        flag[floor][x + 1][y] = 1;
        attron(COLOR_PAIR(8));
        mvprintw(x + 1, y, "+");
        attroff(COLOR_PAIR(8));
    }
    if(board[x][y - 1] == '#') {
        flag[floor][x][y - 1] = 1;
        attron(COLOR_PAIR(9));
        mvprintw(x, y - 1, "\U00002591");
        attroff(COLOR_PAIR(9));
    }
    else if(board[x][y - 1] == '+') {
        flag[floor][x][y - 1] = 1;
        attron(COLOR_PAIR(8));
        mvprintw(x, y - 1, "+");
        attroff(COLOR_PAIR(8));
    }
    if(board[x][y + 1] == '#') {
        flag[floor][x][y + 1] = 1;
        attron(COLOR_PAIR(9));
        mvprintw(x, y + 1, "\U00002591");
        attroff(COLOR_PAIR(9));
    } 
    else if(board[x][y + 1] == '+') {
        flag[floor][x][y + 1] = 1;
        attron(COLOR_PAIR(8));
        mvprintw(x, y + 1, "+");
        attroff(COLOR_PAIR(8));
    }
    if(board[x - 2][y] == '#') {
        flag[floor][x - 2][y] = 1;
        attron(COLOR_PAIR(9));
        mvprintw(x - 2, y, "\U00002591");
        attroff(COLOR_PAIR(9));
    }
    else if(board[x - 2][y] == '+') {
        flag[floor][x - 2][y] = 1;
        attron(COLOR_PAIR(8));
        mvprintw(x - 2, y, "+");
        attroff(COLOR_PAIR(8));
    }
    if(board[x + 2][y] == '#') {
        flag[floor][x + 2][y] = 1;
        attron(COLOR_PAIR(9));
        mvprintw(x + 2, y, "\U00002591");
        attroff(COLOR_PAIR(9));
    }
    else if(board[x + 2][y] == '+') {
        flag[floor][x + 2][y] = 1;
        attron(COLOR_PAIR(8));
        mvprintw(x + 2, y, "+");
        attroff(COLOR_PAIR(8));
    }
    if(board[x][y - 2] == '#') {
        flag[floor][x][y - 2] = 1;
        attron(COLOR_PAIR(9));
        mvprintw(x, y - 2, "\U00002591");
        attroff(COLOR_PAIR(9));
    }
    else if(board[x][y - 2] == '+') {
        flag[floor][x][y - 2] = 1;
        attron(COLOR_PAIR(8));
        mvprintw(x, y - 2, "+");
        attroff(COLOR_PAIR(8));
    }
    if(board[x][y + 2] == '#') {
        flag[floor][x][y + 2] = 1;
        attron(COLOR_PAIR(9));
        mvprintw(x, y + 2, "\U00002591");
        attroff(COLOR_PAIR(9));
    } 
    else if(board[x][y + 2] == '+') {
        flag[floor][x][y + 2] = 1;
        attron(COLOR_PAIR(8));
        mvprintw(x, y + 2, "+");
        attroff(COLOR_PAIR(8));
    }
    
    refresh();
}

void check_door(char** board, int x, int y) {
    for(int i = 0; i < 6; i++) {
        if(x == room[floor][i].door.x && y == room[floor][i].door.y) {
            for(int j = room[floor][i].x - 1; j <= room[floor][i].x + room[floor][i].I; j++) {
                for(int q = room[floor][i].y - 1; q <= room[floor][i].y + room[floor][i].J; q++) {
                    flag[floor][j][q] = 1;
                }
            }
        }
    }
    print_map(board);
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
        mvprintw(4, 0, "2.magical food");
        mvprintw(6, 0, "3.exquisite food");
        mvprintw(2, 22, "%d", reg_food + y_food);
        mvprintw(4, 22, "%d", x_food);
        mvprintw(6, 22, "%d", z_food);
        mvprintw(2, 45, "50");
        mvprintw(4, 45, "50");
        mvprintw(6, 45, "50");
        refresh();
        char n = getchar();
        if(n == '1') {
            if(y_food >= 0)  {
                player.health -= 50;
                mvprintw(0, 170, "                                 ");
                mvprintw(0, 169, "you ate expired food");
                y_food--;
                continue;
            }
            if(reg_food <= 0) {
                mvprintw(0, 170, "                                 ");
                mvprintw(0, 175, "Not Enough Food");
                refresh();
                continue;
            }
            player.hunger += 80;
            reg_food--;
        }
        else if(n == '2') {
            if(x_food <= 0) {
                mvprintw(0, 170, "                                 ");
                mvprintw(0, 175, "Not Enough Food");
                refresh();
                continue;
            }
            player.hunger += 80;
            x_food--;
            s = 1;
        } 
        else if(n == '3') {
            if(z_food <= 0) {
                mvprintw(0, 170, "                                 ");
                mvprintw(0, 175, "Not Enough Food");
                refresh();
                continue;
            }
            d = 1;
            player.hunger += 80;
            z_food--;
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
                mvprintw(0, 150, "                                        ");
                mvprintw(0, 150, "put your current weapon in the bag first");
                refresh();
                napms(2500);
            }
            else {
                strcpy(player.weapon, "mace");
                mvprintw(0, 157, "                                 ");
                mvprintw(0, 157, "your current weapon is now %s", player.weapon);
                refresh();
                napms(2500);
            }
            print_map(board);
            break;
        }
        else if(n == '2') {
            if(strcmp(player.weapon, " ") != 0) {
                mvprintw(0, 150, "                                        ");
                mvprintw(0, 150, "put your current weapon in the bag first");
                refresh();
                napms(2500);
            }
            else if(dagger == 0) {
                mvprintw(0, 165, "                         ");
                mvprintw(0, 165, "you don't have any dagger");
                refresh();
                napms(2500);
            }
            else {
                strcpy(player.weapon, "dagger");
                mvprintw(0, 157, "                                 ");
                mvprintw(0, 157, "your current weapon is now %s", player.weapon);
                refresh();
                napms(2500);
            }
            print_map(board);
            break;
        } 
        else if(n == '3') {
            if(strcmp(player.weapon, " ") != 0) {
                mvprintw(0, 150, "                                        ");
                mvprintw(0, 150, "put your current weapon in the bag first");
                refresh();
                napms(2500);
            }
            else if(wand == 0) {
                mvprintw(0, 165, "                       ");
                mvprintw(0, 165, "you don't have any wand");
                refresh();
                napms(2500);
            }
            else {
                strcpy(player.weapon, "wand");
                mvprintw(0, 157, "                                 ");
                mvprintw(0, 157, "your current weapon is now %s", player.weapon);
                refresh();
                napms(2500);
            }
            print_map(board);
            break;
        }
        else if(n == '4') {
            if(strcmp(player.weapon, " ") != 0) {
                mvprintw(0, 150, "                                        ");
                mvprintw(0, 150, "put your current weapon in the bag first");
                refresh();
                napms(2500);
            }
            else if(arrow == 0) {
                mvprintw(0, 165, "                        ");
                mvprintw(0, 165, "you don't have any arrow");
                refresh();
                napms(2500);
            }
            else {
                strcpy(player.weapon, "arrow");
                mvprintw(0, 157, "                                 ");
                mvprintw(0, 157, "your current weapon is now %s", player.weapon);
                refresh();
                napms(2500);
            }
            print_map(board);
            break;
        }
        else if(n == '5') {
            if(strcmp(player.weapon, " ") != 0) {
                mvprintw(0, 150, "                                        ");
                mvprintw(0, 150, "put your current weapon in the bag first");
                refresh();
                napms(2500);
            }
            else if(sword == 0) {
                mvprintw(0, 165, "                        ");
                mvprintw(0, 165, "you don't have any sword");
                refresh();
                napms(2500);
            }
            else {
                strcpy(player.weapon, "sword");
                mvprintw(0, 157, "                                 ");
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
        else {
            mvprintw(0, 159, "                              ");
            mvprintw(0, 159, "please choose the right number");
            refresh();
            napms(2500);
            continue;
        }
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
        mvprintw(2, 1, "1.health    \U00002671            %d ", health);
        mvprintw(4, 1, "2.damage    \U00002622            %d ", damage);
        mvprintw(6, 1, "3.speed     \U0001F6E6            %d ", speed);
        refresh();
        char n = getchar();
        if(n == '1' && health > 0) {
            h = 1;
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

void boss_init() {
    for(int i = 1; i <= 5; i++) {
        demon[i].health = 5, demon[i].damage = 40, demon[i].end = 15;
        fire[i].health = 10, fire[i].damage = 60, fire[i].end = 12;
        giant[i].health = 15, giant[i].damage = 80, giant[i].end = 10;
        snake[i].health = 20, snake[i].damage = 100;
        undeed[i].health = 30, undeed[i].damage = 140, undeed[i].end = 8;
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
        switch (boss) {
            case 1:
                damage_handle(1);
                break;
            case 2:
                damage_handle(2);
                break;
            case 3:
                damage_handle(3);
                break;
            case 4:
                damage_handle(4);
                break;
            case 5:
                damage_handle(5);
                break;
        }
    }
    else if((*x) == ox - 1 && (*y) == oy - 1) {
        if(ox != player.x && oy != player.y) {
            (*x) = ox;
            (*y) = oy;    
        }
                switch (boss) {
            case 1:
                damage_handle(1);
                break;
            case 2:
                damage_handle(2);
                break;
            case 3:
                damage_handle(3);
                break;
            case 4:
                damage_handle(4);
                break;
            case 5:
                damage_handle(5);
                break;
        }
    }
    else if((*x) == ox - 1 && (*y) == oy + 1) {
        if(ox != player.x && oy != player.y) {
            (*x) = ox;
            (*y) = oy;    
        }
        switch (boss) {
            case 1:
                damage_handle(1);
                break;
            case 2:
                damage_handle(2);
                break;
            case 3:
                damage_handle(3);
                break;
            case 4:
                damage_handle(4);
                break;
            case 5:
                damage_handle(5);
                break;
        }
    }
    else if((*x) == ox && (*y) == oy - 1) {
        if(ox != player.x && oy != player.y) {
            (*x) = ox;
            (*y) = oy;
        }
        switch (boss) {
            case 1:
                damage_handle(1);
                break;
            case 2:
                damage_handle(2);
                break;
            case 3:
                damage_handle(3);
                break;
            case 4:
                damage_handle(4);
                break;
            case 5:
                damage_handle(5);
                break;
        }
    }
    else if((*x) == ox && (*y) == oy + 1) {
        if(ox != player.x && oy != player.y) {
            (*x) = ox;
            (*y) = oy;    
        }
        switch (boss) {
            case 1:
                damage_handle(1);
                break;
            case 2:
                damage_handle(2);
                break;
            case 3:
                damage_handle(3);
                break;
            case 4:
                damage_handle(4);
                break;
            case 5:
                damage_handle(5);
                break;
        }
    }
    else if((*x) == ox + 1 && (*y) == oy) {
        if(ox != player.x && oy != player.y) {
            (*x) = ox;
            (*y) = oy;
        }
        switch (boss) {
            case 1:
                damage_handle(1);
                break;
            case 2:
                damage_handle(2);
                break;
            case 3:
                damage_handle(3);
                break;
            case 4:
                damage_handle(4);
                break;
            case 5:
                damage_handle(5);
                break;
        }
    }
    else if((*x) == ox - 1 && (*y) == oy - 1) {
        if(ox != player.x && oy != player.y) {
            (*x) = ox;
            (*y) = oy;   
        }
        switch (boss) {
            case 1:
                damage_handle(1);
                break;
            case 2:
                damage_handle(2);
                break;
            case 3:
                damage_handle(3);
                break;
            case 4:
                damage_handle(4);
                break;
            case 5:
                damage_handle(5);
                break;
        }
    }
    else if((*x) == ox + 1 && (*y) == oy + 1) {
         if(ox != player.x && oy != player.y) {
            (*x) = ox;
            (*y) = oy;    
        }
        switch (boss) {
            case 1:
                damage_handle(1);
                break;
            case 2:
                damage_handle(2);
                break;
            case 3:
                damage_handle(3);
                break;
            case 4:
                damage_handle(4);
                break;
            case 5:
                damage_handle(5);
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

void damage_handle(int boss) {
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

void attack(char** board) {
    if(strcmp(player.weapon, " ") == 0) {
        attron(COLOR_PAIR(9));
        mvprintw(0, 0, "                      ");
        mvprintw(0, 0, "No weapon in your hand");
        refresh();
        attroff(COLOR_PAIR(9));
    }
    else if(strcmp(player.weapon, "mace") == 0) {
        if(check_attack(board, 'e')) {
            if(d) {
            demon[floor].health -= 10;
            }
            else {
                demon[floor].health -= 5;
            }
            if(demon[floor].health <= 0){demon[floor].health = 0;}
            attron(COLOR_PAIR(9));
            mvprintw(0, 0, "             ");
            mvprintw(0, 0, "you hit demon");
            mvprintw(1, 0, "                 ");
            mvprintw(1, 0, "demon's health:%d", demon[floor].health);
            refresh();
            attroff(COLOR_PAIR(9));
            if(demon[floor].health <= 0) {
                attron(COLOR_PAIR(9));
                mvprintw(3, 0, "                  ");
                mvprintw(3, 0, "demon is dead");
                attroff(COLOR_PAIR(9));
                find_boss(board, 'e');
            }
        }
        else if(check_attack(board, 'f')) {
            if(d) {
                fire[floor].health -= 10;
            }
            else {
                fire[floor].health -= 5;
            }
            if(fire[floor].health <= 0){fire[floor].health = 0;}
            attron(COLOR_PAIR(9));
            mvprintw(0, 0, "             ");
            mvprintw(0, 0, "you hit fire");
            mvprintw(1, 0, "                 ");
            mvprintw(1, 0, "fire's health:%d", fire[floor].health);
            refresh();
            attroff(COLOR_PAIR(9));
            if(fire[floor].health <= 0) {
                attron(COLOR_PAIR(9));
                mvprintw(3, 0, "                  ");
                mvprintw(3, 0, "fire is dead");
                attroff(COLOR_PAIR(9));
                find_boss(board, 'f');
            }
        }
        else if(check_attack(board, 'i')) {
            if(d) {
                giant[floor].health -= 10;
            }
            else {
                giant[floor].health -= 5;
            }
            if(giant[floor].health <= 0){giant[floor].health = 0;}
            attron(COLOR_PAIR(9));
            mvprintw(0, 0, "             ");
            mvprintw(0, 0, "you hit giant");
            mvprintw(1, 0, "                 ");
            mvprintw(1, 0, "giant's health:%d", giant[floor].health);
            refresh();
            attroff(COLOR_PAIR(9));
            if(giant[floor].health <= 0) {
                attron(COLOR_PAIR(9));
                mvprintw(3, 0, "                  ");
                mvprintw(3, 0, "giant is dead");
                attroff(COLOR_PAIR(9));
                find_boss(board, 'i');
            }
        }
        else if(check_attack(board, 'n')) {
            if(d) {
                snake[floor].health -= 10;
            }
            else {
                snake[floor].health -= 5;
            }
            if(snake[floor].health <= 0){snake[floor].health = 0;}
            attron(COLOR_PAIR(9));
            mvprintw(0, 0, "             ");
            mvprintw(0, 0, "you hit snake");
            mvprintw(1, 0, "                 ");
            mvprintw(1, 0, "snake's health:%d", snake[floor].health);
            refresh();
            attroff(COLOR_PAIR(9));
            if(snake[floor].health <= 0) {
                attron(COLOR_PAIR(9));
                mvprintw(3, 0, "                ");
                mvprintw(3, 0, "sanke is dead");
                attroff(COLOR_PAIR(9));
                find_boss(board, 'n');
            }
        }
        else if(check_attack(board, 'u')) {
            if(d) {
                undeed[floor].health -= 10;
            }
            else {
                undeed[floor].health -= 5;
            }
            if(undeed[floor].health <= 0){undeed[floor].health = 0;}
            attron(COLOR_PAIR(9));
            mvprintw(0, 0, "              ");
            mvprintw(0, 0, "you hit undeed");
            mvprintw(1, 0, "                  ");
            mvprintw(1, 0, "undeed's health:%d", undeed[floor].health);
            refresh();
            attroff(COLOR_PAIR(9));
            if(undeed[floor].health <= 0) {
                attron(COLOR_PAIR(9));
                mvprintw(3, 0, "                      ");
                mvprintw(3, 0, "undeed is dead");
                attroff(COLOR_PAIR(9));
                find_boss(board, 'u');
            }
        }
    }

    else if(strcmp(player.weapon, "dagger") == 0) {
        dagger--;
        ddagger.x = player.x;
        ddagger.y = player.y;
        char c = getchar();
        int a = throw(board, c, 5, &ddagger.x, &ddagger.y, 12);
        if(a == 0) {
            attron(COLOR_PAIR(9));
            mvprintw(ddagger.x, ddagger.y, "\U0001F5E1");
            board[ddagger.x][ddagger.y] = 'r';
            attroff(COLOR_PAIR(9));
        }
    }

    else if(strcmp(player.weapon, "wand") == 0) {
        wand--;
        wwand.x = player.x;
        wwand.y = player.y;
        char c = getchar();
        int a = throw(board, c, 10, &wwand.x, &wwand.y, 15);
        if(a == 0) {
            attron(COLOR_PAIR(9));
            mvprintw(wwand.x, wwand.y, "\U00002133");
            board[wwand.x][wwand.y] = 'M';
            attroff(COLOR_PAIR(9));
        }
    }

    else if(strcmp(player.weapon, "arrow") == 0) {
        arrow--;
        aarrow.x = player.x;
        aarrow.y = player.y;
        char c = getchar();
        int a = throw(board, c, 5, &aarrow.x, &aarrow.y, 5);
        if(a == 0) {
            attron(COLOR_PAIR(9));
            mvprintw(aarrow.x, aarrow.y, "\U000027B3");
            board[aarrow.x][aarrow.y] = 'A';
            attroff(COLOR_PAIR(9));
        }
    }
    
    else if(strcmp(player.weapon, "sword") == 0) {
        if(check_attack(board, 'e')) {
            if(d) {
                demon[floor].health -= 20;
            }
            else {
                demon[floor].health -= 10;
            }
            if(demon[floor].health <= 0){demon[floor].health = 0;}
            attron(COLOR_PAIR(9));
            mvprintw(0, 0, "             ");
            mvprintw(0, 0, "you hit demon");
            mvprintw(1, 0, "                 ");
            mvprintw(1, 0, "demon's health:%d", demon[floor].health);
            refresh();
            attroff(COLOR_PAIR(9));
            if(demon[floor].health <= 0) {
                attron(COLOR_PAIR(9));
                mvprintw(3, 0, "                 ");
                mvprintw(3, 0, "demon is dead");
                attroff(COLOR_PAIR(9));
                find_boss(board, 'e');
            }
        }
        else if(check_attack(board, 'f')) {
            if(d) {
                fire[floor].health -= 20;
            }
            else {
                fire[floor].health -= 10;
            }
            if(fire[floor].health <= 0){fire[floor].health = 0;}
            attron(COLOR_PAIR(9));
            mvprintw(0, 0, "             ");
            mvprintw(0, 0, "you hit fire");
            mvprintw(1, 0, "                 ");
            mvprintw(1, 0, "fire's health:%d", fire[floor].health);
            refresh();
            attroff(COLOR_PAIR(9));
            if(fire[floor].health <= 0) {
                attron(COLOR_PAIR(9));
                mvprintw(3, 0, "                 ");
                mvprintw(3, 0, "fire is dead");
                attroff(COLOR_PAIR(9));
                find_boss(board, 'f');
            }
        }
        else if(check_attack(board, 'i')) {
            if(d) {
                giant[floor].health -= 20;
            }
            else {
                giant[floor].health -= 10;
            }
            if(giant[floor].health <= 0){giant[floor].health = 0;}
            attron(COLOR_PAIR(9));
            mvprintw(0, 0, "             ");
            mvprintw(0, 0, "you hit giant");
            mvprintw(1, 0, "                 ");
            mvprintw(1, 0, "giant's health:%d", giant[floor].health);
            refresh();
            attroff(COLOR_PAIR(9));
            if(giant[floor].health <= 0) {
                attron(COLOR_PAIR(9));
                mvprintw(3, 0, "                 ");
                mvprintw(3, 0, "giant is dead");
                attroff(COLOR_PAIR(9));
                find_boss(board, 'i');
            }
        }
        else if(check_attack(board, 'n')) {
            if(d) {
                snake[floor].health -= 20;
            }
            else {
                snake[floor].health -= 10;
            }
            if(snake[floor].health <= 0){snake[floor].health = 0;}
            attron(COLOR_PAIR(9));
            mvprintw(0, 0, "             ");
            mvprintw(0, 0, "you hit snake");
            mvprintw(1, 0, "                 ");
            mvprintw(1, 0, "snake's health:%d", snake[floor].health);
            refresh();
            attroff(COLOR_PAIR(9));
            if(snake[floor].health <= 0) {
                attron(COLOR_PAIR(9));
                mvprintw(3, 0, "                 ");
                mvprintw(3, 0, "snake is dead");
                attroff(COLOR_PAIR(9));
                find_boss(board, 'n');
            }
        }
        else if(check_attack(board, 'u')) {
            if(d) {
                undeed[floor].health -= 20;
            }
            else {
                undeed[floor].health -= 10;
            }
            if(undeed[floor].health <= 0){undeed[floor].health = 0;}
            attron(COLOR_PAIR(9));
            mvprintw(0, 0, "              ");
            mvprintw(0, 0, "you hit undeed");
            mvprintw(1, 0, "                  ");
            mvprintw(1, 0, "undeed's health:%d", undeed[floor].health);
            refresh();
            attroff(COLOR_PAIR(9));
            if(undeed[floor].health <= 0) {
                attron(COLOR_PAIR(9));
                mvprintw(3, 0, "                 ");
                mvprintw(3, 0, "undeed is dead");
                attroff(COLOR_PAIR(9));
                find_boss(board, 'u');
            }
        }
    }
}

int check_attack(char** board, char boss) {
    if(board[player.x - 1][player.y] == boss) {
        return 1;
    }
    else if(board[player.x - 1][player.y - 1] == boss) {
        return 2;
    }
    else if(board[player.x - 1][player.y + 1] == boss) {
        return 3;
    }
    else if(board[player.x][player.y - 1] == boss) {
        return 4;
    }
    else if(board[player.x][player.y + 1] == boss) {
        return 5;
    }
    else if(board[player.x + 1][player.y] == boss) {
        return 6;   
    }
    else if(board[player.x + 1][player.y - 1] == boss) {
        return 7;
    }
    else if(board[player.x + 1][player.y + 1] == boss) {
        return 8;
    }
    return 0;

}

void find_boss(char** board, char boss) {
    switch(check_attack(board, boss)) {
        case 1:
            attron(COLOR_PAIR(8));
            mvprintw(player.x - 1, player.y, ".");
            board[player.x - 1][player.y] = '.';
            refresh();
            attroff(COLOR_PAIR(8));
            break;
        case 2:
            attron(COLOR_PAIR(8));
            mvprintw(player.x - 1, player.y - 1, ".");
            board[player.x - 1][player.y - 1] = '.';
            refresh();
            attroff(COLOR_PAIR(8));
            break;
        case 3:
            attron(COLOR_PAIR(8));
            mvprintw(player.x - 1, player.y + 1, ".");
            board[player.x - 1][player.y + 1] = '.';
            refresh();
            attroff(COLOR_PAIR(8));
            break;
        case 4:
            attron(COLOR_PAIR(8));
            mvprintw(player.x, player.y - 1, ".");
            board[player.x][player.y - 1] = '.';
            refresh();
            attroff(COLOR_PAIR(8));
            break;
        case 5:
            attron(COLOR_PAIR(8));
            mvprintw(player.x, player.y + 1, ".");
            board[player.x][player.y + 1] = '.';
            refresh();
            attroff(COLOR_PAIR(8));
            break;
        case 6:
            attron(COLOR_PAIR(8));
            mvprintw(player.x + 1, player.y, ".");
            board[player.x + 1][player.y] = '.';
            refresh();
            attroff(COLOR_PAIR(8));
            break;
        case 7:
            attron(COLOR_PAIR(8));
            mvprintw(player.x + 1, player.y - 1, ".");
            board[player.x + 1][player.y - 1] = '.';
            refresh();
            attroff(COLOR_PAIR(8));
            break;
        case 8:
            attron(COLOR_PAIR(8));
            mvprintw(player.x + 1, player.y + 1, ".");
            board[player.x + 1][player.y + 1] = '.';
            refresh();
            attroff(COLOR_PAIR(8));
            break;
    }
}

int throw(char** board, char key, int range, int* x, int* y, int damage) {
    while(range--) {
        switch(key) {
            case 'w':
                (*x)--;
                int a = find_boss2(board, (*x), (*y), damage);
                if(a == 0) {
                    (*x)++;
                    return 0;
                }
                else if(a == 1) {
                    return 1;
                }
                break;
            case 'a':
                (*y)--;
                int b = find_boss2(board, (*x), (*y), damage);
                if(b == 0) {
                    (*y)++;
                    return 0;
                }
                else if(b == 1) {
                    return 1;
                }
                break;
            case 's':
                (*x)++;
                int c = find_boss2(board, (*x), (*y), damage);
                if(c == 0) {
                    (*x)--;
                    return 0;
                }
                else if(c == 1) {
                    return 1;
                }
                break;
            case 'd':
                (*y)++;
                int d = find_boss2(board, (*x), (*y), damage);
                if(d == 0) {
                    (*y)--;
                    return 0;
                }
                else if(d == 1) {
                    return 1;
                }
                break;
            case 'q':
                (*x)--;
                (*y)--;
                int e = find_boss2(board, (*x), (*y), damage);
                if(e == 0) {
                    (*x)++;
                    (*y)++;
                    return 0;
                }
                else if(e == 1) {
                    return 1;
                }
                break;
            case 'e':
                (*x)--;
                (*y)++;
                int f = find_boss2(board, (*x), (*y), damage);
                if(f == 0) {
                    (*x)++;
                    (*y)--;
                    return 0;
                }
                else if(f == 1) {
                    return 1;
                }            
                break;
            case 'z':
                (*x)++;
                (*y)--;
                int g = find_boss2(board, (*x), (*y), damage);
                if(g == 0) {
                    (*x)--;
                    (*y)++;
                    return 0;
                }
                else if(g == 1) {
                    return 1;
                }
                break;
            case 'x':
                (*x)++;
                (*y)++;
                int h = find_boss2(board, (*x), (*y), damage);
                if(h == 0) {
                    (*x)--;
                    (*y)--;
                    return 0;
                }
                else if(h == 1) {
                    return 1;
                }
                break;
        }
    }
    return 0;
}

int find_boss2(char** board, int x, int y, int damage) {
    switch(board[x][y]) {
        case 'e':
            demon[floor].health -= damage;
            if(demon[floor].health <= 0){demon[floor].health = 0;}
            attron(COLOR_PAIR(9));
            mvprintw(0, 0, "               ");
            mvprintw(0, 0, "you hit demon");
            mvprintw(1, 0, "                   ");
            mvprintw(1, 0, "demon's health:%d", demon[floor].health);
            refresh();
            attroff(COLOR_PAIR(9));
            if(demon[floor].health == 0) {
                attron(COLOR_PAIR(8));
                mvprintw(demon[floor].x, demon[floor].y, ".");
                board[demon[floor].x][demon[floor].y] = '.';
                refresh();
                attroff(COLOR_PAIR(8));
            }
            if(damage == 15) {
                demon[floor].end = 0;
            }
            return 1;
            break;
        case 'f':
            fire[floor].health -= damage;
            if(fire[floor].health <= 0){fire[floor].health = 0;}
            attron(COLOR_PAIR(9));
            mvprintw(0, 0, "               ");
            mvprintw(0, 0, "you hit fire");
            mvprintw(1, 0, "                   ");
            mvprintw(1, 0, "fire's health:%d", fire[floor].health);
            refresh();
            attroff(COLOR_PAIR(9));
            if(fire[floor].health == 0) {
                attron(COLOR_PAIR(8));
                mvprintw(fire[floor].x, fire[floor].y, ".");
                board[fire[floor].x][fire[floor].y] = '.';
                refresh();
                attroff(COLOR_PAIR(8));
            }
            if(damage == 15) {
                fire[floor].end = 0;
            }
            return 1;
            break;
        case 'i':
            giant[floor].health -= damage;
            if(giant[floor].health <= 0){giant[floor].health = 0;}
            attron(COLOR_PAIR(9));
            mvprintw(0, 0, "               ");
            mvprintw(0, 0, "you hit giant");
            mvprintw(1, 0, "                   ");
            mvprintw(1, 0, "giant's health:%d", giant[floor].health);
            refresh();
            attroff(COLOR_PAIR(9));
            if(giant[floor].health == 0) {
                attron(COLOR_PAIR(8));
                mvprintw(giant[floor].x, giant[floor].y, ".");
                board[giant[floor].x][giant[floor].y] = '.';
                refresh();
                attroff(COLOR_PAIR(8));
            }
            if(damage == 15) {
                giant[floor].end = 0;
            }
            return 1;
            break;
        case 'n':
            snake[floor].health -= damage;
            if(snake[floor].health <= 0){snake[floor].health = 0;}
            attron(COLOR_PAIR(9));
            mvprintw(0, 0, "               ");
            mvprintw(0, 0, "you hit snake");
            mvprintw(1, 0, "                   ");
            mvprintw(1, 0, "snake's health:%d", snake[floor].health);
            refresh();
            attroff(COLOR_PAIR(9));
            if(snake[floor].health == 0) {
                attron(COLOR_PAIR(8));
                mvprintw(snake[floor].x, snake[floor].y, ".");
                board[snake[floor].x][snake[floor].y] = '.';
                refresh();
                attroff(COLOR_PAIR(8));
            }
            if(damage == 15) {
                snake[floor].end = 0;
            }
            return 1;
            break;
        case 'u':
            undeed[floor].health -= damage;
            if(undeed[floor].health <= 0){undeed[floor].health = 0;}
            attron(COLOR_PAIR(9));
            mvprintw(0, 0, "               ");
            mvprintw(0, 0, "you hit undeed");
            mvprintw(1, 0, "                   ");
            mvprintw(1, 0, "undeed's health:%d", undeed[floor].health);
            refresh();
            attroff(COLOR_PAIR(9));
            if(undeed[floor].health == 0) {
                attron(COLOR_PAIR(8));
                mvprintw(undeed[floor].x, undeed[floor].y, ".");
                board[undeed[floor].x][undeed[floor].y] = '.';
                refresh();
                attroff(COLOR_PAIR(8));
            }
            if(damage == 15) {
                undeed[floor].end = 0;
            }
            return 1;
            break;
        case '_':
        case '|':
        case 'O':
        case '<':
        case '+':
            return 0;
            break;
    }
    return 2;
}

void save_borad() {
    FILE* f1;
    f1 = fopen("map1", "w");
    for(int i = 0; i <= 46; i++) {
        fprintf(f1, "%s\n", board1[i]);
    }
    fclose(f1);

    FILE* f2;
    f2 = fopen("map2", "w");
    for(int i = 0; i <= 46; i++) {
        fprintf(f2, "%s\n", board2[i]);
    }
    fclose(f2);

    FILE* f3;
    f3 = fopen("map3", "w");
    for(int i = 0; i <= 46; i++) {
        fprintf(f3, "%s\n", board3[i]);
    }
    fclose(f3);

    FILE* f4;
    f4 = fopen("map4", "w");
    for(int i = 0; i <= 46; i++) {
        fprintf(f4, "%s\n", board4[i]);
    }
    fclose(f4);
    FILE* f5;
    f5 = fopen("map5", "w");
    for(int i = 0; i <= 46; i++) {
        fprintf(f5, "%s\n", board5[i]);
    }
    fclose(f5);

}

void save_flag() {
    FILE* f1;
    f1 = fopen("flag1", "w");
    for(int i = 0; i <= 46; i++) {
        for(int j = 0; j <= 189; j++) {
            if(flag[1][i][j] == 2) {
                flag[1][i][j] = 0;
            }
            fprintf(f1, "%d ", flag[1][i][j]);  
        }
        fprintf(f1, "\n");
    }
    fclose(f1);
    FILE* f2;
    f2 = fopen("flag2", "w");
    for(int i = 0; i <= 46; i++) {
        for(int j = 0; j <= 189; j++) {
            if(flag[2][i][j] == 2) {
                flag[2][i][j] = 0;
            }
            fprintf(f2, "%d ", flag[2][i][j]);
        }
        fprintf(f2, "\n");
    }
    fclose(f2);
    FILE* f3;
    f3 = fopen("flag3", "w");
    for(int i = 0; i <= 46; i++) {
        for(int j = 0; j <= 189; j++) {
            if(flag[3][i][j] == 2) {
                flag[3][i][j] = 0;
            }
            fprintf(f3, "%d ", flag[3][i][j]);
        }
        fprintf(f3, "\n");
    }
    fclose(f3);
    FILE* f4;
    f4 = fopen("flag4", "w");
    for(int i = 0; i <= 46; i++) {
        for(int j = 0; j <= 189; j++) {
            if(flag[4][i][j] == 2) {
                flag[4][i][j] = 0;
            }
            fprintf(f4, "%d ", flag[4][i][j]);
        }
        fprintf(f4, "\n");
    }
    fclose(f4);

}

void save_info() {
    FILE* f;
    f = fopen("info", "w");
    fprintf(f, "%d\n", player.health);
    fprintf(f, "%d\n", player.score);
    fprintf(f, "%d\n", player.gold);
    fprintf(f, "%d\n", player.exp);
    fprintf(f, "%d\n", player.color);
    fprintf(f, "%d\n", player.x);
    fprintf(f, "%d\n", player.y);
    fprintf(f, "%d\n", player.hunger);
    fprintf(f, "%s\n", player.weapon);
    fclose(f);
    FILE* ff;
    ff = fopen("room", "w");
    for(int i = 1; i <= 4; i++) {
        for(int j = 0; j < 6; j++) {
            fprintf(ff, "%d\n", room[i][j].x);
            fprintf(ff, "%d\n", room[i][j].y);
            fprintf(ff, "%d\n", room[i][j].I);
            fprintf(ff, "%d\n", room[i][j].J);
            fprintf(ff, "%d\n", room[i][j].pass);
            fprintf(ff, "%d\n", room[i][j].door.x);
            fprintf(ff, "%d\n", room[i][j].door.y);
        }
    }
    fclose(ff);


}

void save_boss() {
    FILE* f1;
    f1 = fopen("boss", "w");
    for(int i = 1; i <= 4; i++) {
        fprintf(f1, "%d\n", demon[i].x);
        fprintf(f1, "%d\n", demon[i].y);
        fprintf(f1, "%d\n", fire[i].x);
        fprintf(f1, "%d\n", fire[i].y);
        fprintf(f1, "%d\n", giant[i].x);
        fprintf(f1, "%d\n", giant[i].y);
        fprintf(f1, "%d\n", snake[i].x);
        fprintf(f1, "%d\n", snake[i].y);
        fprintf(f1, "%d\n", undeed[i].x);
        fprintf(f1, "%d\n", undeed[i].y);
    }
    fclose(f1);
}

void save_other() {
    FILE* f;
    f = fopen("other", "w");
    fprintf(f, "%d\n", floor);
    fprintf(f, "%d\n", T);
    fprintf(f, "%d\n", reg_food);
    fprintf(f, "%d\n", dagger);
    fprintf(f, "%d\n", wand);
    fprintf(f, "%d\n", arrow);
    fprintf(f, "%d\n", sword);
    fprintf(f, "%d\n", health);
    fprintf(f, "%d\n", damage);
    fprintf(f, "%d\n", speed);
    fprintf(f, "%d\n", h);
    fprintf(f, "%d\n", d);
    fprintf(f, "%d\n", s);
    fprintf(f, "%d\n", hcount);
    fprintf(f, "%d\n", scount);
    fprintf(f, "%d\n", dcount);
    fprintf(f, "%d\n", hidden);
    fprintf(f, "%d\n", check);
    fprintf(f, "%d\n", n_login);
    fclose(f);

}

void make_scoreboard() {
    if(karbar == 1) {
        FILE* f = fopen("scoreboard1", "w");
        fprintf(f, "%s\n", player.name);
        fprintf(f, "%d\n", player.score);
        fprintf(f, "%d\n", player.gold);
        fprintf(f, "%d\n", n_login);
        fprintf(f, "%d\n", player.exp);
        fclose(f);
    }
    else if(karbar == 2) {
        FILE* f = fopen("scoreboard2", "w");
        fprintf(f, "%s\n", player.name);
        fprintf(f, "%d\n", player.score);
        fprintf(f, "%d\n", player.gold);
        fprintf(f, "%d\n", n_login);
        fprintf(f, "%d\n", player.exp);
        fclose(f);
    }
    else if(karbar == 3) {
        FILE* f = fopen("scoreboard3", "w");
        fprintf(f, "%s\n", player.name);
        fprintf(f, "%d\n", player.score);
        fprintf(f, "%d\n", player.gold);
        fprintf(f, "%d\n", n_login);
        fprintf(f, "%d\n", player.exp);
        fclose(f);
    }
}

void quit() {
    clear();
    player.score = player.gold * 10 + player.exp;
    mvprintw(20,83, "press any key to quit");
    refresh();
    if(guest == 0) {
        save_borad();
        save_flag();
        save_info();
        save_boss();
        save_other();
        make_scoreboard();
    }
    char c = getchar();
}