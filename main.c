//46*189
//x:1-32 y:1-179
//end game bug
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
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
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
int flor = 1, T = 0, reg_food = 0, z_food = 0, y_food = 0, x_food = 0, M = 0; 
int dagger = 10, wand = 10, arrow = 10, sword = 0, mace = 1;
int health = 0, damage = 0, speed = 0, s = 0, d = 0, h = 0, scount = 0, dcount = 0, hcount = 0;
char c1, c2, c3, c4, c5, c6, c7;
int hidden = 0, check = 0,load = 0, n_login = 0, karbar = 0, init_health = 0, win = 0, lose = 0, guest = 0, song = 0;
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
void input(char, char**, WINDOW*);
void create_map(char***);
void print_map(char**);
int check_room(Room**);
void Doors(char***);
void print_character(int, int, char**, WINDOW*);
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
void generate_password();
void profile();
void play_audio(const char *filename);
void new_game();
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
    init_color(33, 200, 500, 800);
    init_color(COLOR_BLACK, 0, 0, 0);
    init_pair(8, 33, COLOR_BLACK);
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

    boss_init();
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
    else if(guest == 0) {
        karbar = 4;
    }
    color();
    napms(1000);
    clear();
    if(load == 0) {
        new_game();
    }
    init_health = player.health;
    if(flor == 1) {
        print_map(board1); 
    }
    else if(flor == 2) {
        print_map(board2); 
    }
    else if(flor == 3) {
        print_map(board3); 
    }
    else if(flor == 4) {
        print_map(board4); 
    }
    n_login++;
    WINDOW* w1;
    w1 = newwin(3, 20, 1, 1);
    box(w1, 1, 1);
    while(1) {
        mvprintw(0, 0, "\U0000230C");
        mvprintw(0, 65, "\U0000230D");
        mvprintw(3, 0, "\U0000230E");
        mvprintw(3, 65, "\U0000230F");
        enchant_check();
        if(player.hunger <= 0) {
            player.health -= 10;
            player.hunger = 0;
        }
        if(!song && room[1][0].x <= player.x && player.x < room[1][0].x + room[1][0].I && room[1][0].y <= player.y && player.y < room[1][0].y + room[1][0].J) {
            song = 1;
            play_audio("01._theme_from_the_walking_dead.mp3");
        }
        if(!(room[1][0].x <= player.x && player.x < room[1][0].x + room[1][0].I && room[1][0].y <= player.y && player.y < room[1][0].y + room[1][0].J)) {
            song = 0;
            
        }
        mvprintw(0,184, "0:save");
        if(guest) {
            mvprintw(0,184, "0:quit");
        }
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
            mvprintw(23, 86, "press any key to return to the menu");
            refresh();
            getchar();
            clear();
            menu();
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
            if(!guest) {
                FILE* f = fopen("winlose", "w");
                fprintf(f, "%d\n", win);
                fprintf(f, "%d\n", lose);
                fclose(f);
            }
                
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
        switch (flor)
        {
        case 1:
            input(c, board1, w1);
            break;
        case 2:
            input(c, board2, w1);
            break;
        case 3:
            input(c, board3, w1);
            break;
        case 4:
            input(c, board4, w1);
            break;
        case 5:
            input(c, board5, w1);
            break;
        }
        player.exp++;
    }
    endwin();
    return 0;
}
void play_audio(const char *filename) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Mix_OpenAudio Error: %s\n", Mix_GetError());
        SDL_Quit();
        return;
    }

    Mix_Music *music = Mix_LoadMUS(filename);
    if (!music) {
        printf("Mix_LoadMUS Error: %s\n", Mix_GetError());
    } else {
        Mix_PlayMusic(music, -1);
    }
}

void new_game() {
        loading(flor);
        create_map(&board1);
        napms(1000);
        flor++; 
        loading(flor);
        create_map(&board2);
        napms(1000);
        flor++;  
        loading(flor);
        create_map(&board3);
        napms(1000);
        flor++;  
        loading(flor);
        create_map(&board4);
        napms(500);
        flor = 1;
        if(player.health != 300 && player.health != 500 && player.health != 700 && player.health != 900) {
            player.health = 900;
        }
        player.hunger = 200;
        player.gold = 0;
        strcpy(player.weapon, "mace");
        player.score = 0;
        player.exp = 0;
}

void music() {
    mvprintw(0, 80, "please select your music");
    mvprintw(0, 184, "0:back");
    while(1) {
        mvprintw(20, 80, "1.hoghahasan_shamaeizadeh_ghogha");
        mvprintw(22, 80, "2.CARNIVAL");
        mvprintw(24, 80, "3.theme_from_the_walking_dead");
        mvprintw(26, 80, "4.bobby_bass_hoist_the_colours");
        mvprintw(28, 80, "5.Clint Mansell - Lux Aeterna");

        refresh();
        char c = getchar();
        if(c == '1') {
            play_audio("hasan_shamaeizadeh_-_ghogha.mp3");
        }
        else if(c == '2') {
            play_audio("$ - CARNIVAL.mp3");
        }
        else if (c == '3') {
            play_audio("01._theme_from_the_walking_dead.mp3");
        }
        else if (c == '4') {
            play_audio("bobby_bass_hoist_the_colours 128.mp3");
        }
        else if (c == '5') {
            play_audio("Clint Mansell - Lux Aeterna (320).mp3");
        }
        else if(c == '0') {
            break;
        }
        else {
            continue;
        }

    }
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
    init_color(15, 380, 90, 90);
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
        init_pair(10, COLOR_GREEN, COLOR_BLACK);
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
            flag[flor][i][j] = 0;
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
        if(check == NULL) {
            f = fopen(player.name, "w");
            fprintf(f, "username:%s \n",  player.name);
            fclose(f);
            break;
        }
        else if(check != NULL){
            printw("Username has already been taken\nplease enter a new username\n");
        }
    }
    printw("Enter your password:(enter g to generate a random password)\n");
    while(1) {
        scanw(" %s", player.pass);
        if(strcmp(player.pass, "g") == 0) {
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
            printw("your %s\n", p);
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
    if(strcmp(player.name, "mahdi0x06") == 0) {
        karbar = 1;

        FILE* f1 = fopen("scoreboard1", "r");
        char n[40];
        fscanf(f1, "%s", n);
        fscanf(f1, "%d", &player.score);
        fscanf(f1, "%d", &player.gold);
        fscanf(f1, "%d", &n_login);
        fscanf(f1, "%d", &player.exp);
        fclose(f1);
    }
    else if(strcmp(player.name, "mahdi0110") == 0) {
        karbar = 2;
        FILE* f2 = fopen("scoreboard2", "r");
        char n[40];
        fscanf(f2, "%s", n);
        fscanf(f2, "%d", &player.score);
        fscanf(f2, "%d", &player.gold);
        fscanf(f2, "%d", &n_login);
        fscanf(f2, "%d", &player.exp);
        fclose(f2);

    }
    else if(strcmp(player.name, "TAmabani") == 0) {
        karbar = 3;
        FILE* f3 = fopen("scoreboard3", "r");
        char n[40];
        fscanf(f3, "%s", n);
        fscanf(f3, "%d", &player.score);
        fscanf(f3, "%d", &player.gold);
        fscanf(f3, "%d", &n_login);
        fscanf(f3, "%d", &player.exp);
        fclose(f3);
    }
    else {
        karbar = 4;
        FILE* f4 = fopen("scoreboard4", "r");
        char n[40];
        fscanf(f4, "%s", n);
        fscanf(f4, "%d", &player.score);
        fscanf(f4, "%d", &player.gold);
        fscanf(f4, "%d", &n_login);
        fscanf(f4, "%d", &player.exp);
        fclose(f4);
    }
    menu();
}

void profile() {
    char name[80];
    char email[80];
    // FILE* f = fopen("info", "r");
    // fscanf(f, "%d", &player.health);
    // fscanf(f, "%d", &player.score);
    // fscanf(f, "%d", &player.gold);
    // fscanf(f, "%d", &player.exp);
    // fclose(f);
    FILE* f1  = fopen(player.name, "r");
    fgets(name, 70, f1);
    fgets(email, 70, f1);
    fgets(email, 70, f1);
    fgets(email, 70, f1);
    fgets(player.mail, 70, f1);
    fclose(f1);

    while(1) {
        mvprintw(0, 184, "0:back");
        mvprintw(20, 85, "player's name:%s", player.name);
        mvprintw(22, 85, "player's %s", player.mail);
        mvprintw(24, 85, "player's score:%d", player.score);
        mvprintw(26, 85, "player's gold:%d", player.gold);
        mvprintw(28, 85, "player's exp:%d", player.exp);



        refresh();
        char c = getchar();
        if(c == '0') {
            break;
        }
    }
    menu();
}

void menu() {
    if(strcmp(player.name, "mahdi0x06") == 0) {
        karbar = 1;
    }
    else if(strcmp(player.name, "mahdi0110") == 0) {
        karbar = 2;
    }
    else if(strcmp(player.name, "TAmabani") == 0) {
        karbar = 3;
    }
    else if(guest == 0) {
        karbar = 4;
    }
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
            load_game();
            if(n_login != 0) {
                FILE* f = fopen("winlose", "r");
                fscanf(f, "%d", &win);
                fscanf(f, "%d", &lose);
                fclose(f);
            }
            if(win == 1 || lose == 1) {
                mvprintw(0, 77, "you don't have any saved game");
                refresh();
                continue;
            }
            else if(guest == 1) {
                mvprintw(0, 77, "you have logged in as a guest");
                refresh();
                continue;
            }
            clear();
            load = 1;
            loading(1);
            napms(1000);
            loading(2);
            napms(1000);
            loading(3);
            napms(1000);
            loading(4);
            napms(1000);
            
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
            if(guest == 0) {
                clear();
                
                profile();
            }
            else {
                mvprintw(0, 77, "you have logged in as a guest");
                refresh();
                continue;
            }
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
    if(karbar == 1) {
        FILE* f9 = fopen("info1", "r");
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
    }
    else if(karbar == 2) {
        FILE* f9 = fopen("info2", "r");
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
    }
    else if(karbar == 3) {
        FILE* f9 = fopen("info3", "r");
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
    }
    else if(karbar == 4) {
        FILE* f9 = fopen("info4", "r");
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
    }

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
        fscanf(f11, "%d", &demon[i].health);
        fscanf(f11, "%d", &fire[i].health);
        fscanf(f11, "%d", &giant[i].health);
        fscanf(f11, "%d", &snake[i].health);
        fscanf(f11, "%d", &undeed[i].health);
        fscanf(f11, "%d", &demon[i].end);
        fscanf(f11, "%d", &fire[i].end);
        fscanf(f11, "%d", &giant[i].end);
        fscanf(f11, "%d", &snake[i].end);
        fscanf(f11, "%d", &undeed[i].end);
    }
    fclose(f11);

    FILE* f12;
    f12 = fopen("other", "r");
    fscanf(f12, "%d", &flor);
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

    FILE* f1 = fopen("scoreboard1", "r");
    FILE* f2 = fopen("scoreboard2", "r");
    FILE* f3 = fopen("scoreboard3", "r");
    FILE* f4 = fopen("scoreboard4", "r");
    at p[4];
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

    fscanf(f4, "%s", p[3].name);
    fscanf(f4, "%d", &p[3].score);
    fscanf(f4, "%d", &p[3].gold);
    fscanf(f4, "%d", &p[3].n_login);
    fscanf(f4, "%d", &p[3].exp);
    fclose(f4);

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);

    while(1) {
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
            else {
                attron(COLOR_PAIR(1));
            
                mvprintw(2, 0, "1.\U0001F947 %s(goat)                   %d                   %d                   %d                 %d", p[2].name, p[2].score, p[2].gold, p[2].n_login, p[2].exp);
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(2));
            
                mvprintw(4, 0, "2.\U0001F948 %s(legend)                  %d                   %d                   %d                 %d", p[1].name, p[1].score, p[1].gold, p[1].n_login, p[1].exp);
                attroff(COLOR_PAIR(2));
                attron(COLOR_PAIR(4));
            
                mvprintw(6, 0, "3.\U0001F949 %s(champ)                    %d                   %d                   %d                 %d", p[0].name, p[0].score, p[0].gold, p[0].n_login, p[0].exp);   
                attroff(COLOR_PAIR(4));
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
            else {
                attron(COLOR_PAIR(1));
            
                mvprintw(2, 0, "1.\U0001F947 %s(goat)                   %d                   %d                   %d                 %d", p[1].name, p[1].score, p[1].gold, p[1].n_login, p[1].exp);
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(2));
            
                mvprintw(4, 0, "2.\U0001F948 %s(legend)                  %d                   %d                   %d                 %d", p[2].name, p[2].score, p[2].gold, p[2].n_login, p[2].exp);
                attroff(COLOR_PAIR(2));
                attron(COLOR_PAIR(4));
            
                mvprintw(6, 0, "3.\U0001F949 %s(champ)                    %d                   %d                   %d                 %d", p[0].name, p[0].score, p[0].gold, p[0].n_login, p[0].exp);   
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
            else {
                attron(COLOR_PAIR(1));
            
                mvprintw(2, 0, "1.\U0001F947 %s(goat)                   %d                   %d                   %d                 %d", p[2].name, p[2].score, p[2].gold, p[2].n_login, p[2].exp);
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(2));
            
                mvprintw(4, 0, "2.\U0001F948 %s(legend)                  %d                   %d                   %d                 %d", p[0].name, p[0].score, p[0].gold, p[0].n_login, p[0].exp);
                attroff(COLOR_PAIR(2));
                attron(COLOR_PAIR(4));
            
                mvprintw(6, 0, "3.\U0001F949 %s(champ)                    %d                   %d                   %d                 %d", p[1].name, p[1].score, p[1].gold, p[1].n_login, p[1].exp);   
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
            else {
                attron(COLOR_PAIR(1));
            
                mvprintw(2, 0, "1.\U0001F947 %s(goat)                   %d                   %d                   %d                 %d", p[0].name, p[0].score, p[0].gold, p[0].n_login, p[0].exp);
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(2));
            
                mvprintw(4, 0, "2.\U0001F948 %s(legend)                  %d                   %d                   %d                 %d", p[2].name, p[2].score, p[2].gold, p[2].n_login, p[2].exp);
                attroff(COLOR_PAIR(2));
                attron(COLOR_PAIR(4));
            
                mvprintw(6, 0, "3.\U0001F949 %s(champ)                    %d                   %d                   %d                 %d", p[1].name, p[1].score, p[1].gold, p[1].n_login, p[1].exp);   
                attroff(COLOR_PAIR(4));
            }
            refresh();
        }
        else if(p[2].score <= p[1].score && p[1].score <= p[0].score) {
            if(strcmp(player.name, "mahdi0x06") == 0) {
                attron(COLOR_PAIR(1));
            
                mvprintw(2, 0, "\U000027A11.\U0001F947 %s(goat)                  %d                   %d                   %d                 %d", p[0].name, p[0].score, p[0].gold, p[0].n_login, p[0].exp);
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
            else {
                attron(COLOR_PAIR(1));
            
                mvprintw(2, 0, "1.\U0001F947 %s(goat)                   %d                   %d                   %d                 %d", p[0].name, p[0].score, p[0].gold, p[0].n_login, p[0].exp);
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(2));
            
                mvprintw(4, 0, "2.\U0001F948 %s(legend)                  %d                   %d                   %d                 %d", p[1].name, p[1].score, p[1].gold, p[1].n_login, p[1].exp);
                attroff(COLOR_PAIR(2));
                attron(COLOR_PAIR(4));
            
                mvprintw(6, 0, "3.\U0001F949 %s(champ)                    %d                   %d                   %d                 %d", p[2].name, p[2].score, p[2].gold, p[2].n_login, p[2].exp);   
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
            else {
                attron(COLOR_PAIR(1));
            
                mvprintw(2, 0, "1.\U0001F947 %s(goat)                   %d                   %d                   %d                 %d", p[1].name, p[1].score, p[1].gold, p[1].n_login, p[1].exp);
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(2));
            
                mvprintw(4, 0, "2.\U0001F948 %s(legend)                  %d                   %d                   %d                 %d", p[0].name, p[0].score, p[0].gold, p[0].n_login, p[0].exp);
                attroff(COLOR_PAIR(2));
                attron(COLOR_PAIR(4));
            
                mvprintw(6, 0, "3.\U0001F949 %s(champ)                    %d                   %d                   %d                 %d", p[2].name, p[2].score, p[2].gold, p[2].n_login, p[2].exp);   
                attroff(COLOR_PAIR(4));
            }
            refresh();
        }
        attron(COLOR_PAIR(9));
        if(karbar == 4) {
            mvprintw(8, 0, "\U000027A14.%s                                 %d                   %d                   %d                 %d", p[3].name, p[3].score, p[3].gold, p[3].n_login, p[3].exp); 

        }
        else {
            mvprintw(8, 0, "4.%s                                 %d                   %d                   %d                 %d", p[3].name, p[3].score, p[3].gold, p[3].n_login, p[3].exp); 

        }
        refresh();
        attroff(COLOR_PAIR(9));
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
            music();
        }
        else if(n == '0') {
        }
        else {continue;}
        break;
    }
    menu();

}

void create_map(char*** board) {
    if(flor == 4) {
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
        if(flor == 2 && i == 0) {
            room[flor][0].x = room[flor - 1][0].x;
            room[flor][0].y = room[flor - 1][0].y;
            continue;
        }
        else if(flor == 3 && i == 1) {
            room[flor][1].x = room[flor - 1][1].x;
            room[flor][1].y = room[flor - 1][1].y;
            continue;
        }
        else if(flor == 4 && i == 2) {
            room[flor][2].x = room[flor - 1][2].x;
            room[flor][2].y = room[flor - 1][2].y;
            continue;
        }
        room[flor][i].x = rand() % (32) + 6;
        room[flor][i].y = rand() % (157) + 19;
    }
    int x = check_room(room);
    while(x == 0) {
        for(int i = 0; i < 6; i++) {
            if(flor == 2 && i == 0) {
                continue;
            }
            else if(flor == 3 && i == 1) {
                continue;
            }
            else if(flor == 4 && i == 2) {
                continue;
            }
            room[flor][i].x = rand() % (32) + 6;
            room[flor][i].y = rand() % (157) + 19;
        }
        x = check_room(room);
    }
    int nfood = rand() % (4) + 3;
    int nfood1 = rand() % (4) + 3;
    int nfood2 = rand() % (4) + 3;
    int nfood3 = rand() % (4) + 3;
    int ngold = rand() % (4) + 3;
    for(int i = 0; i < 6; i++) {
        room[flor][i].I = rand() % (5) + 5;
        room[flor][i].J = rand() % (7) + 6;
        int x = rand() % (2) + 1;
        int X = rand() % (room[flor][i].I - 2) + room[flor][i].x + 1;
        int Y = rand () % (room[flor][i].J - 2) + room[flor][i].y + 1;
        int food_x = rand() % (room[flor][i].I - 3) + room[flor][i].x;
        int food_x1 = rand() % (room[flor][i].I - 3) + room[flor][i].x;
        int food_x2 = rand() % (room[flor][i].I - 3) + room[flor][i].x;
        int food_x3 = rand() % (room[flor][i].I - 3) + room[flor][i].x;
        int gold_x = rand() % (room[flor][i].I - 3) + room[flor][i].x;
        int door;
        if(flor == 1 && i == 0) {
            IJ[0].x = room[flor][i].I;
            IJ[0].y = room[flor][i].J;
        }
        else if(flor == 2 && i == 1) {
            IJ[1].x = room[flor][i].I;
            IJ[1].y = room[flor][i].J;
        }
        else if(flor == 3 && i == 2) {
            IJ[2].x = room[flor][i].I;
            IJ[2].y = room[flor][i].J;
        }
        if(flor == 2 && i == 0) {
            room[flor][i].I = IJ[0].x;
            room[flor][i].J = IJ[0].y;
        }
        else if(flor == 3 && i == 1) {
            room[flor][i].I = IJ[1].x;
            room[flor][i].J = IJ[1].y;
        }
        else if(flor == 4 && i == 2) {
            room[flor][i].I = IJ[2].x;
            room[flor][i].J = IJ[2].y;
        }
        if(x == 1) {
            door = rand() % (room[flor][i].I) + room[flor][i].x;
        }
        else {
            door = rand () % (room[flor][i].J) + room[flor][i].y;
        }
        while (abs(door - X) < 1 || abs(door - Y) < 1) {
            if(x == 1) {
                door = rand() % (room[flor][i].I) + room[flor][i].x;
            }
            else {
                door = rand () % (room[flor][i].J) + room[flor][i].y;
            }
        }
        if(flor == 1 && i == 1) {
            player.x = X;
            player.y = Y + 1;
            for(int j = room[flor][i].x - 1; j <= room[flor][i].x + room[flor][i].I; j++) {
                for(int q = room[flor][i].y - 1; q <= room[flor][i].y  + room[flor][i].J; q++) {
                    flag[flor][j][q] = 1;
                }
            }
        }

       
        for(int j = room[flor][i].x; j < room[flor][i].x + room[flor][i].I; j++) {
            for(int q = room[flor][i].y; q < room[flor][i].y + room[flor][i].J; q++) {
                if(j == X && q == Y) {
                    (*board)[j][q] = 'O';
                    room[flor][i].c[j][q] = 'O';
                    continue;
                }
                else if(flor == 1 && i == 0 && j == X + 1 && q == Y + 1) {
                    (*board)[j][q] = '<';
                    room[flor][i].c[j][q] = '<';
                    continue;
                }
                else if(flor == 2 && i == 1 && j == X + 1 && q == Y + 1) {
                    (*board)[j][q] = '<';
                    room[flor][i].c[j][q] = '<';
                    continue;
                }
                else if(flor == 3 && i == 2 && j == X + 1 && q == Y + 1) {
                    (*board)[j][q] = '<';
                    room[flor][i].c[j][q] = '<';
                    continue;
                }
                else if(flor == 4 && i == 5 && j == room[flor][i].x + room[flor][i].I - 1 && q == room[flor][i].y + room[flor][i].J - 1) {
                    (*board)[j][q] = '>';
                    room[flor][i].c[j][q] = '>';
                    continue;
                }
                else if(flor == 1 && i == 5 && j == room[flor][i].x + 3 && q == room[flor][i].y + room[flor][i].J) {
                    (*board)[j][q] = '?';
                    room[flor][i].c[j][q] = '?';
                    continue;
                }
                else if(i == 5 && j == room[flor][i].x + room[flor][i].I - 1 && q == room[flor][i].y + 2) {
                    (*board)[j][q] = 'd';
                    room[flor][i].c[j][q] = 'd';
                    continue;
                }
                else if(i == 4 && j == room[flor][i].x + room[flor][i].I - 1 && q == room[flor][i].y + 1) {
                    (*board)[j][q] = 'a';
                    room[flor][i].c[j][q] = 'a';
                    continue;
                }
                else if(i == 3 && j == room[flor][i].x + room[flor][i].I - 1 && q == room[flor][i].y + 3) {
                    (*board)[j][q] = 'm';
                    room[flor][i].c[j][q] = 'm';
                    continue;
                }
                else if(i == 1 && j == room[flor][i].x + room[flor][i].I - 1 && q == room[flor][i].y + 5 && flor != 2 && flor != 3) {
                    (*board)[j][q] = 'e';
                    room[flor][i].c[j][q] = 'e';
                    demon[flor].x = j;
                    demon[flor].y = q;
                    continue;
                }
                else if(i == 2 && j == room[flor][i].x + room[flor][i].I - 1 && q == room[flor][i].y + 4 && flor != 3 && flor != 4) {
                    (*board)[j][q] = 'f';
                    room[flor][i].c[j][q] = 'f';
                    fire[flor].x = j;
                    fire[flor].y = q;
                    continue;
                }
                else if(i == 3 && j == room[flor][i].x + room[flor][i].I - 1 && q == room[flor][i].y + 4) {
                    
                    (*board)[j][q] = 'i';
                    room[flor][i].c[j][q] = 'i';
                    giant[flor].x = j;
                    giant[flor].y = q;
                    continue;
                }
                else if(i == 4 && j == room[flor][i].x + room[flor][i].I - 1 && q == room[flor][i].y + 4) {
                    (*board)[j][q] = 'n';
                    room[flor][i].c[j][q] = 'n';
                    snake[flor].x = j;
                    snake[flor].y = q;
                    continue;
                }
                else if(i == 5 && j == room[flor][i].x + room[flor][i].I - 1 && q == room[flor][i].y + 4) {
                    (*board)[j][q] = 'u';
                    room[flor][i].c[j][q] = 'u';
                    undeed[flor].x = j;
                    undeed[flor].y = q;
                    continue;
                }
                else if(i == 2 && j == room[flor][i].x + room[flor][i].I - 1 && q == room[flor][i].y + 3 && flor == 2) {
                    (*board)[j][q] = 's';
                    room[flor][i].c[j][q] = 's';
                    continue;
                }
                else if(i == 1 && j == room[flor][i].x + room[flor][i].I - 1 && q == room[flor][i].y + 3) {
                    (*board)[j][q] = 'h';
                    room[flor][i].c[j][q] = 'h';
                    continue;
                }
                else if(i == 0 && j == room[flor][i].x + room[flor][i].I - 1 && q == room[flor][i].y + 2 && (flor == 2 || flor == 3 || flor == 4)) {
                    (*board)[j][q] = 'S';
                    room[flor][i].c[j][q] = 'S';
                    continue;
                }
                else if(i == 3 && j == room[flor][i].x + room[flor][i].I - 1 && q == room[flor][i].y + 2 && (flor == 3 || flor == 4)) {
                    (*board)[j][q] = 'D';
                    room[flor][i].c[j][q] = 'D';
                    continue;
                }
                else if(j == X - 1 && q == Y) {
                    (*board)[j][q] = '^';
                    room[flor][i].c[j][q] = '.';
                    refresh();
                    continue;
                }
                else if(j == X - 1 && q == Y + 1 && i == 4) {
                    (*board)[j][q] = '@';
                    room[flor][i].c[j][q] = '@';
                    attron(COLOR_PAIR(8));
                    refresh();
                    continue;
                }
                else if(j == room[flor][i].x + room[flor][i].I - 1 && q == room[flor][i].y + room[flor][i].J - 1 && i == 4) {
                    (*board)[j][q] = '&';
                    room[flor][i].c[j][q] = '&';
                    attron(COLOR_PAIR(8));
                    refresh();
                    continue;
                }
                else if(j == room[flor][i].x && q == room[flor][i].y + room[flor][i].J - 1 && i == 1) {
                    (*board)[j][q] = 'T';
                    room[flor][i].c[j][q] = 'T';
                    attron(COLOR_PAIR(8));
                    refresh();
                    continue;
                }
                (*board)[j][q] = '.';
                room[flor][i].c[j][q] = '.';
                refresh();
            }
        }

        for(int j = room[flor][i].y; j < room[flor][i].y + room[flor][i].J; j++) {
            if(x == 2 && door == j) {
                (*board)[room[flor][i].x - 1][j] = '+';
                room[flor][i].c[room[flor][i].x][j] = '+';
                (*board)[room[flor][i].x + room[flor][i].I][j] = '_';
                room[flor][i].c[room[flor][i].x + room[flor][i].I][j] = '_';
                room[flor][i].door.x = room[flor][i].x - 1;
                room[flor][i].door.y = j;
                continue;
            }
            (*board)[room[flor][i].x - 1][j] = '_';
            room[flor][i].c[room[flor][i].x][j] = '_';
            (*board)[room[flor][i].x + room[flor][i].I][j] = '_';
            room[flor][i].c[room[flor][i].x + room[flor][i].I][j] = '_';
        }
        for(int j = room[flor][i].x; j < room[flor][i].x + room[flor][i].I; j++) {
            if(x == 1 && door == j) {
                (*board)[j][room[flor][i].y - 1] = '+';
                room[flor][i].c[j][room[flor][i].y] = '+';
                (*board)[j][room[flor][i].y + room[flor][i].J] = '|';
                room[flor][i].c[j][room[flor][i].y + room[flor][i].J] = '|';
                room[flor][i].door.x = j;
                room[flor][i].door.y = room[flor][i].y - 1;
                continue;
            }
                (*board)[j][room[flor][i].y - 1] = '|';
                room[flor][i].c[j][room[flor][i].y] = '|';
                (*board)[j][room[flor][i].y + room[flor][i].J] = '|';
                room[flor][i].c[j][room[flor][i].y + room[flor][i].J] = '|';
        }
        if(ngold) {
            if((*board)[gold_x][room[flor][i].y] != 'T' && (*board)[gold_x][room[flor][i].y] != '@' && (*board)[gold_x][room[flor][i].y] != '&' && (*board)[gold_x][room[flor][i].y] != '<') {
                (*board)[gold_x][room[flor][i].y] = 'G';
                ngold--;
            }
        }
        if((*board)[gold_x][room[flor][i].y] != 'T' && (*board)[gold_x][room[flor][i].y] != '@' && (*board)[gold_x][room[flor][i].y] != '&' && (*board)[gold_x][room[flor][i].y] != '<' && flor == 3 && i == 3) {
                (*board)[gold_x][room[flor][i].y] = 'g';
            } 
        if(nfood) {
            if((*board)[food_x][room[flor][i].J + room[flor][i].y - 1] != 'T' && (*board)[food_x][room[flor][i].J + room[flor][i].y - 1] != '@' && (*board)[food_x][room[flor][i].J + room[flor][i].y - 1] != '&' && (*board)[food_x][room[flor][i].y + room[flor][i].J - 1] != '<' && (*board)[food_x][room[flor][i].y + room[flor][i].J - 1] != '+') {
                (*board)[food_x][room[flor][i].J + room[flor][i].y - 1] = 'F';
                nfood--;
            }
        }
        if(nfood1) {
            if((*board)[food_x1][room[flor][i].J + room[flor][i].y - 2] != 'T' && (*board)[food_x1][room[flor][i].J + room[flor][i].y - 2] != '@' && (*board)[food_x1][room[flor][i].J + room[flor][i].y - 2] != '&' && (*board)[food_x1][room[flor][i].y + room[flor][i].J - 2] != '<' && (*board)[food_x1][room[flor][i].y + room[flor][i].J - 2] != '+') {
                (*board)[food_x1][room[flor][i].J + room[flor][i].y - 2] = 'z';
                nfood1--;
            }
        }
        if(nfood2) {
            if((*board)[food_x2][room[flor][i].J + room[flor][i].y - 3] != 'T' && (*board)[food_x2][room[flor][i].J + room[flor][i].y - 3] != '@' && (*board)[food_x2][room[flor][i].J + room[flor][i].y - 3] != '&' && (*board)[food_x2][room[flor][i].y + room[flor][i].J - 3] != '<' && (*board)[food_x2][room[flor][i].y + room[flor][i].J - 3] != '+') {
                (*board)[food_x2][room[flor][i].J + room[flor][i].y - 3] = 'x';
                nfood2--;
            }
        }
        if(nfood3) {
            if((*board)[food_x3][room[flor][i].J + room[flor][i].y - 4] != 'T' && (*board)[food_x3][room[flor][i].J + room[flor][i].y - 4] != '@' && (*board)[food_x3][room[flor][i].J + room[flor][i].y - 4] != '&' && (*board)[food_x3][room[flor][i].y + room[flor][i].J - 4] != '<' && (*board)[food_x2][room[flor][i].y + room[flor][i].J - 4] != '+') {
                (*board)[food_x3][room[flor][i].J + room[flor][i].y - 4] = 'y';
                nfood3--;
            }
        }
    }
    if(flor == 1) {
        (*board)[room[1][5].x + 3][room[1][5].y + room[1][5].J] = '?';
    }

    Doors(board);
}

int check_room(Room** room) {
    for(int i = 0; i < 5; i++) {
        for(int j = i + 1; j < 6; j++) {
            if(abs(room[flor][i].y - room[flor][j].y) <= 23 ) {
                return 0;
            }
        }
    }
    return 1;
}

void print_map(char** board) {
    // clear();
    for(int i = 4; i <= 46; i++) {
        move(i, 0);
        clrtoeol();
    }
    for(int i = 0; i <= 46; i++) {
        for(int j = 0; j <= 189; j++) {
            if(0 <= i && i <= 3 && 0 <= j && j <= 65) {
                //mvprintw(i, j, "#");
                continue;
            }
            if(flag[flor][i][j]) {
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
                    if(flor == 5) {
                        attron(COLOR_PAIR(13));
                        mvprintw(i, j, "_");
                        attroff(COLOR_PAIR(13));     
                    }
                    else if(flor == 1 && (i == room[flor][0].x - 1 || i == room[flor][0].x + room[flor][0].I) && room[flor][0].y <= j && j < room[flor][0].y + room[flor][0].J) {
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
                    if(flor == 5) {
                        attron(COLOR_PAIR(13));
                        mvprintw(i, j, "|");
                        attroff(COLOR_PAIR(13));     
                    }
                    else if(flor == 1 && (j == room[flor][0].y - 1 || j == room[flor][0].y + room[flor][0].J) && room[flor][0].x <= i && i < room[flor][0].x + room[flor][0].I) {
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
        temp.x = room[flor][p].door.x;
        temp.y = room[flor][p].door.y;
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
            while(temp.x < room[flor][p + 1].door.x) {
                if(temp.x == room[flor][p + 1].door.x && temp.y + 1 == room[flor][p + 1].door.y) {
                    break;
                }
                else if(temp.x + 1 == room[flor][p + 1].door.x && temp.y == room[flor][p + 1].door.y) {
                    break;
                }
                else if(temp.x == room[flor][p + 1].door.x && temp.y - 1 == room[flor][p + 1].door.y) {
                    break;
                }
                else if(temp.x - 1 == room[flor][p + 1].door.x && temp.y == room[flor][p + 1].door.y) {
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
            while(temp.x > room[flor][p + 1].door.x) {
                if(temp.x == room[flor][p + 1].door.x && temp.y + 1 == room[flor][p + 1].door.y) {
                    break;
                }
                else if(temp.x + 1 == room[flor][p + 1].door.x && temp.y == room[flor][p + 1].door.y) {
                    break;
                }
                else if(temp.x == room[flor][p + 1].door.x && temp.y - 1 == room[flor][p + 1].door.y) {
                    break;
                }
                else if(temp.x - 1 == room[flor][p + 1].door.x && temp.y == room[flor][p + 1].door.y) {
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
            while(temp.y < room[flor][p + 1].door.y) {
                if(temp.x == room[flor][p + 1].door.x && temp.y + 1 == room[flor][p + 1].door.y) {
                    break;
                }
                else if(temp.x + 1 == room[flor][p + 1].door.x && temp.y == room[flor][p + 1].door.y) {
                    break;
                }
                else if(temp.x == room[flor][p + 1].door.x && temp.y - 1 == room[flor][p + 1].door.y) {
                    break;
                }
                else if(temp.x - 1 == room[flor][p + 1].door.x && temp.y == room[flor][p + 1].door.y) {
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
            while(temp.y > room[flor][p + 1].door.y) {
                if(temp.x == room[flor][p + 1].door.x && temp.y + 1 == room[flor][p + 1].door.y) {
                    break;
                }
                else if(temp.x + 1 == room[flor][p + 1].door.x && temp.y == room[flor][p + 1].door.y) {
                    break;
                }
                else if(temp.x == room[flor][p + 1].door.x && temp.y - 1 == room[flor][p + 1].door.y) {
                    break;
                }
                else if(temp.x - 1 == room[flor][p + 1].door.x && temp.y == room[flor][p + 1].door.y) {
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
            if(temp.x == room[flor][p + 1].door.x && temp.y + 1 == room[flor][p + 1].door.y) {
                move(temp.x, temp.y + 1);
                break;
            }
            else if(temp.x + 1 == room[flor][p + 1].door.x && temp.y == room[flor][p + 1].door.y) {
                move(temp.x + 1, temp.y);
                break;
            }
            else if(temp.x == room[flor][p + 1].door.x && temp.y - 1 == room[flor][p + 1].door.y) {
                move(temp.x, temp.y - 1);
                break;
            }
            else if(temp.x - 1 == room[flor][p + 1].door.x && temp.y == room[flor][p + 1].door.y) {
                move(temp.x - 1, temp.y);
                break;
            }
        }
    }
}

void input(char c, char** board, WINDOW* w1) {
    int x = player.x , y = player.y;
    switch (c) {
        case 'M':
            M++;
            show_map(board, M);
            break;
        case ' ':
            attack(board);
            print_character(x, y, board, w1);
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
            print_character(x, y, board, w1);
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
            print_character(x, y, board, w1);
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
            print_character(x, y, board, w1);
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
            print_character(x, y, board, w1);
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
            print_character(x, y, board, w1);
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
            print_character(x, y, board, w1);
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
            print_character(x, y, board, w1);
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
            print_character(x, y, board, w1);
            break;
        case 'f':
            char c = getchar();
            if(c == 'w') {
                while(board[player.x - 1][player.y] != ' ' && board[player.x - 1][player.y] != '_' && board[player.x - 1][player.y] != '|' && board[player.x - 1][player.y] != 'O' && board[player.x - 1][player.y] != 'e' && board[player.x - 1][player.y] != 'f' && board[player.x - 1][player.y] != 'i' && board[player.x - 1][player.y] != 'n' && board[player.x - 1][player.y] != 'u') {
                    if(board[player.x][player.y] == '+') {
                        check_door(board, player.x, player.y);
                        mvprintw(1, 1, "                                                                           ");
                        mvprintw(1, 1,"new room");
                    }
                    flag[flor][player.x][player.y] = 1;
                    player.x--;
                    player.health--;
                }
            }
            else if(c == 's') {
                while(board[player.x + 1][player.y] != ' ' && board[player.x + 1][player.y] != '_' && board[player.x + 1][player.y] != '|' && board[player.x + 1][player.y] != 'O' && board[player.x + 1][player.y] != 'e' && board[player.x + 1][player.y] != 'f' && board[player.x + 1][player.y] != 'i' && board[player.x + 1][player.y] != 'n' && board[player.x + 1][player.y] != 'u') {
                    if(board[player.x][player.y] == '+') {
                        check_door(board, player.x, player.y);
                        mvprintw(1, 1, "                                                                           ");
                        mvprintw(1, 1,"new room");
                    }
                    flag[flor][player.x][player.y] = 1;
                    player.x++;
                    player.health--;
                }
            }
            else if(c == 'a') {
                while(board[player.x][player.y - 1] != ' ' && board[player.x][player.y - 1] != '_' && board[player.x][player.y - 1] != '|' && board[player.x][player.y - 1] != 'O' && board[player.x][player.y - 1] != 'e' && board[player.x][player.y - 1] != 'f' && board[player.x][player.y - 1] != 'i' && board[player.x][player.y - 1] != 'n' && board[player.x][player.y - 1] != 'u') {
                    if(board[player.x][player.y] == '+') {
                        check_door(board, player.x, player.y);
                        mvprintw(1, 1, "                                                                           ");
                        mvprintw(1, 1,"new room");
                    }
                    flag[flor][player.x][player.y] = 1;
                    player.y--;
                    player.health--;
                }
            }
            else if(c == 'd') {
                while(board[player.x][player.y + 1] != ' ' && board[player.x][player.y + 1] != '_' && board[player.x][player.y + 1] != '|' && board[player.x][player.y + 1] != 'O' && board[player.x][player.y + 1] != 'e' && board[player.x][player.y + 1] != 'f' && board[player.x][player.y + 1] != 'i' && board[player.x][player.y + 1] != 'n' && board[player.x][player.y + 1] != 'u') {
                    if(board[player.x][player.y] == '+') {
                        check_door(board, player.x, player.y);
                        mvprintw(1, 1, "                                                                           ");
                        mvprintw(1, 1,"new room");
                    }
                    flag[flor][player.x][player.y] = 1;
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
            print_character(x, y, board, w1);
            print_map(board);
            break;
        case 'g':
            char cc = getchar();
            if(cc == 'w') {
                while(board[player.x - 1][player.y] != ' ' && board[player.x - 1][player.y] != '_' && board[player.x - 1][player.y] != '|' && board[player.x - 1][player.y] != 'O' && board[player.x - 1][player.y] != 'e' && board[player.x - 1][player.y] != 'f' && board[player.x - 1][player.y] != 'i' && board[player.x - 1][player.y] != 'n' && board[player.x - 1][player.y] != 'u') {
                    if(board[player.x][player.y] == '+') {
                        check_door(board, player.x, player.y);
                        mvprintw(1, 1, "                                                                           ");
                        mvprintw(1, 1,"new room");
                    }
                    flag[flor][player.x][player.y] = 1;
                    player.x--;
                    player.health--;
                }
            }
            else if(cc == 's') {
                while(board[player.x + 1][player.y] != ' ' && board[player.x + 1][player.y] != '_' && board[player.x + 1][player.y] != '|' && board[player.x + 1][player.y] != 'O' && board[player.x + 1][player.y] != 'e' && board[player.x + 1][player.y] != 'f' && board[player.x + 1][player.y] != 'i' && board[player.x + 1][player.y] != 'n' && board[player.x + 1][player.y] != 'u') {
                    if(board[player.x][player.y] == '+') {
                        check_door(board, player.x, player.y);
                        mvprintw(1, 1, "                                                                           ");
                        mvprintw(1, 1,"new room");
                    }
                    flag[flor][player.x][player.y] = 1;
                    player.x++;
                    player.health--;
                }
            }
            else if(cc == 'a') {
                while(board[player.x][player.y - 1] != ' ' && board[player.x][player.y - 1] != '_' && board[player.x][player.y - 1] != '|' && board[player.x][player.y - 1] != 'O' && board[player.x][player.y - 1] != 'e' && board[player.x][player.y - 1] != 'f' && board[player.x][player.y - 1] != 'i' && board[player.x][player.y - 1] != 'n' && board[player.x][player.y - 1] != 'u') {
                    if(board[player.x][player.y] == '+') {
                        check_door(board, player.x, player.y);
                        mvprintw(1, 1, "                                                                           ");
                        mvprintw(1, 1,"new room");
                    }
                    flag[flor][player.x][player.y] = 1;
                    player.y--;
                    player.health--;
                }
            }
            else if(cc == 'd') {
                while(board[player.x][player.y + 1] != ' ' && board[player.x][player.y + 1] != '_' && board[player.x][player.y + 1] != '|' && board[player.x][player.y + 1] != 'O' && board[player.x][player.y + 1] != 'e' && board[player.x][player.y + 1] != 'f' && board[player.x][player.y + 1] != 'i' && board[player.x][player.y + 1] != 'n' && board[player.x][player.y + 1] != 'u') {
                    if(board[player.x][player.y] == '+') {
                        check_door(board, player.x, player.y);
                        mvprintw(1, 1, "                                                                           ");
                        mvprintw(1, 1,"new room");
                    }
                    flag[flor][player.x][player.y] = 1;
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
            print_character(x, y, board, w1);
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
                if(flag[flor][i][j] == 0) {
                    flag[flor][i][j] = 2;
                }
            }
        }
    }
    else {
        for(int i = 0; i <= 46; i++) {
            for(int j = 0; j <= 189; j++) {
                if(flag[flor][i][j] == 2) {
                    flag[flor][i][j] = 0;
                }
            }
        }
    }
    print_map(board);
}

void print_character(int ox, int oy, char** board, WINDOW* w1) {
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
            else if(board[ox][oy] == 'a' || board[ox][oy] == 'A') {
                if(c4 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U000027B3");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'm' || board[ox][oy] == 'M') {
                if(c5 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U00002133");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'd' || board[ox][oy] == 'r') {
                if(c6 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U0001F5E1");
                    refresh();
                    attroff(COLOR_PAIR(9));  
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }            
            win = 1;
            n_login++;
            player.score += player.gold * 10 + player.exp;
            player.score += 150;
            clear();
            attron(COLOR_PAIR(9));
            mvprintw(23, 83, "You Won");
            mvprintw(24, 83, "Your score:%d", player.score);
            mvprintw(25, 83, "press any key to return to the menu");
            refresh();
            attroff(COLOR_PAIR(9));
            getchar();
            clear();
            menu();
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
            else if(board[ox][oy] == 'a' || board[ox][oy] == 'A') {
                if(c4 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U000027B3");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'm' || board[ox][oy] == 'M') {
                if(c5 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U00002133");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'd' || board[ox][oy] == 'r') {
                if(c6 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U0001F5E1");
                    refresh();
                    attroff(COLOR_PAIR(9));  
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }            
            char xx = getchar();
            if(xx == '>') {
                flor++;
                player.x = 20;
                player.y = 90;
                print_map(board5);
                mvprintw(1, 1, "                                                                           ");
                mvprintw(1, 1,"next flor!");
                play_audio("01 Elden Ring.mp3");
                refresh();
            }
            //treasure_room();
            break;
        case '?':
            if(board[ox][oy] == '.') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'a' || board[ox][oy] == 'A') {
                if(c4 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U000027B3");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'm' || board[ox][oy] == 'M') {
                if(c5 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U00002133");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'd' || board[ox][oy] == 'r') {
                if(c6 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U0001F5E1");
                    refresh();
                    attroff(COLOR_PAIR(9));  
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }            
            attron(COLOR_PAIR(16));
            mvprintw(player.x, player.y, "?");
            refresh();
            attroff(COLOR_PAIR(16));
            hidden = 1;
            player.x = room[1][0].door.x;
            player.y = room[1][0].door.y;
            check_door(board, player.x, player.y);
            break;
        case 'h':
            if(board[ox][oy] == '.') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'a' || board[ox][oy] == 'A') {
                if(c4 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U000027B3");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'm' || board[ox][oy] == 'M') {
                if(c5 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U00002133");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'd' || board[ox][oy] == 'r') {
                if(c6 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U0001F5E1");
                    refresh();
                    attroff(COLOR_PAIR(9));  
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            c1 = getchar();
            if(c1 == 'p') {
                board[player.x][player.y] = '.';
                health++;
            }
            break;

        case 'S':
            if(board[ox][oy] == '.') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'a' || board[ox][oy] == 'A') {
                if(c4 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U000027B3");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'm' || board[ox][oy] == 'M') {
                if(c5 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U00002133");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'd' || board[ox][oy] == 'r') {
                if(c6 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U0001F5E1");
                    refresh();
                    attroff(COLOR_PAIR(9));  
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            c2 = getchar();
            if(c2 == 'p') {
                board[player.x][player.y] = '.';
                speed++;
            }
            break;
        case 'D':
            if(board[ox][oy] == '.') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'a' || board[ox][oy] == 'A') {
                if(c4 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U000027B3");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'm' || board[ox][oy] == 'M') {
                if(c5 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U00002133");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'd' || board[ox][oy] == 'r') {
                if(c6 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U0001F5E1");
                    refresh();
                    attroff(COLOR_PAIR(9));  
                }
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
            else if(board[ox][oy] == 'a' || board[ox][oy] == 'A') {
                if(c4 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U000027B3");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'm' || board[ox][oy] == 'M') {
                if(c5 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U00002133");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'd' || board[ox][oy] == 'r') {
                if(c6 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U0001F5E1");
                    refresh();
                    attroff(COLOR_PAIR(9));  
                }
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
            else if(board[ox][oy] == 'a' || board[ox][oy] == 'A') {
                if(c4 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U000027B3");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'm' || board[ox][oy] == 'M') {
                if(c5 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U00002133");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'd' || board[ox][oy] == 'r') {
                if(c6 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U0001F5E1");
                    refresh();
                    attroff(COLOR_PAIR(9));  
                }
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
            else if(board[ox][oy] == 'a' || board[ox][oy] == 'A') {
                if(c4 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U000027B3");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'm' || board[ox][oy] == 'M') {
                if(c5 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U00002133");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'd' || board[ox][oy] == 'r') {
                if(c6 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U0001F5E1");
                    refresh();
                    attroff(COLOR_PAIR(9));  
                }
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
            else if(board[ox][oy] == 'a' || board[ox][oy] == 'A') {
                if(c4 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U000027B3");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'm' || board[ox][oy] == 'M') {
                if(c5 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U00002133");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'd' || board[ox][oy] == 'r') {
                if(c6 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U0001F5E1");
                    refresh();
                    attroff(COLOR_PAIR(9));  
                }
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
            else if(board[ox][oy] == 'a' || board[ox][oy] == 'A') {
                if(c4 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U000027B3");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'm' || board[ox][oy] == 'M') {
                if(c5 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U00002133");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'd' || board[ox][oy] == 'r') {
                if(c6 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U0001F5E1");
                    refresh();
                    attroff(COLOR_PAIR(9));  
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            srand(time(NULL));
            int g = rand() % (41) + 10;
            mvprintw(1, 1, "                                                                           ");
            mvprintw(1, 1, "gold+%d", g);
            player.gold += g;
            board[player.x][player.y] = '.';
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
            else if(board[ox][oy] == 'a' || board[ox][oy] == 'A') {
                if(c4 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U000027B3");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'm' || board[ox][oy] == 'M') {
                if(c5 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U00002133");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'd' || board[ox][oy] == 'r') {
                if(c6 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U0001F5E1");
                    refresh();
                    attroff(COLOR_PAIR(9));  
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            srand(time(NULL));
            int G = rand() % (5) + 1;
            mvprintw(1, 1, "                                                                           ");
            mvprintw(1, 1, "gold+%d", G);
            player.gold += G;
            board[player.x][player.y] = '.';
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
            board[player.x][player.y] = '.';
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
            else if(board[ox][oy] == 'a' || board[ox][oy] == 'A') {
                if(c4 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U000027B3");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'm' || board[ox][oy] == 'M') {
                if(c5 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U00002133");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'd' || board[ox][oy] == 'r') {
                if(c6 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U0001F5E1");
                    refresh();
                    attroff(COLOR_PAIR(9));  
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            if(x_food <= 4) {
                x_food++;
            }
            board[player.x][player.y] = '.';
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
            else if(board[ox][oy] == 'a' || board[ox][oy] == 'A') {
                if(c4 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U000027B3");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'm' || board[ox][oy] == 'M') {
                if(c5 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U00002133");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'd' || board[ox][oy] == 'r') {
                if(c6 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U0001F5E1");
                    refresh();
                    attroff(COLOR_PAIR(9));  
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            if(y_food <= 4) {
                y_food++;
            }
            board[player.x][player.y] = '.';
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
            else if(board[ox][oy] == 'a' || board[ox][oy] == 'A') {
                if(c4 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U000027B3");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'm' || board[ox][oy] == 'M') {
                if(c5 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U00002133");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'd' || board[ox][oy] == 'r') {
                if(c6 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U0001F5E1");
                    refresh();
                    attroff(COLOR_PAIR(9));  
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            if(z_food <= 4) {
                z_food++;
            }
            board[player.x][player.y] = '.';
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
            else if(board[ox][oy] == 'a' || board[ox][oy] == 'A') {
                if(c4 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, "\U00002591");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U000027B3");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'm' || board[ox][oy] == 'M') {
                if(c5 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, "\U00002591");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U00002133");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'd' || board[ox][oy] == 'r') {
                if(c6 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, "\U00002591");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U0001F5E1");
                    refresh();
                    attroff(COLOR_PAIR(9));  
                }
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
            else if(board[ox][oy] == 'O') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, "O");
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
                if(c2 == 'p') {
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
                if(c3 == 'p') {
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
            else if(board[ox][oy] == 'a' || board[ox][oy] == 'A') {
                if(c4 == 'p') {
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
            else if(board[ox][oy] == 'm' || board[ox][oy] == 'M') {
                if(c5 == 'p') {
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
            else if(board[ox][oy] == 'd' || board[ox][oy] == 'r') {
                if(c6 == 'p') {
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
                if(c7 == 'p') {
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
            check_door(board, player.x, player.y);
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
                mvprintw(1, 1, "                                                                           ");
                mvprintw(1, 1,"new room");
                mvprintw(ox, oy, "\U00002591");
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
            else if(board[ox][oy] == 'a' || board[ox][oy] == 'A') {
                if(c4 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U000027B3");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'm' || board[ox][oy] == 'M') {
                if(c5 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U00002133");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'd' || board[ox][oy] == 'r') {
                if(c6 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U0001F5E1");
                    refresh();
                    attroff(COLOR_PAIR(9));  
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            break;
        case '^':
            player.hunger--;
            if(board[ox][oy] == '.' || board[ox][oy] == 'O') {
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
            else if(board[ox][oy] == 'a' || board[ox][oy] == 'A') {
                if(c4 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U000027B3");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'm' || board[ox][oy] == 'M') {
                if(c5 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U00002133");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'd' || board[ox][oy] == 'r') {
                if(c6 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U0001F5E1");
                    refresh();
                    attroff(COLOR_PAIR(9));  
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            mvprintw(1, 1, "                                                                           ");
            mvprintw(1, 1, "TRAP!");
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
             else if(board[ox][oy] == 'a' || board[ox][oy] == 'A') {
                if(c4 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U000027B3");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'm' || board[ox][oy] == 'M') {
                if(c5 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U00002133");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'd' || board[ox][oy] == 'r') {
                if(c6 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U0001F5E1");
                    refresh();
                    attroff(COLOR_PAIR(9));  
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            char x = getchar();
            if(x == '>') {
                flor++;
                clear();
                if(flor == 2) {
                    check_door(board, room[flor][0].door.x, room[flor][0].door.y);
                }
                else if(flor == 3) {
                    check_door(board, room[flor][1].door.x, room[flor][1].door.y);
                    
                }
                else if(flor == 4) {
                    check_door(board, room[flor][2].door.x, room[flor][2].door.y);
                }
                attron(COLOR_PAIR(8));
                if(flor == 2) {
                    print_map(board2);
                }
                else if(flor == 3) {
                    print_map(board3);
                }
                else if(flor == 4) {
                    print_map(board4);
                }
                mvprintw(1, 1, "                                                                           ");
                mvprintw(1, 1,"next flor!");
            }
            break;
        case '&':
            player.hunger--;
            if(board[ox][oy] == '.') {
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, ".");
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));

            }
             else if(board[ox][oy] == 'a' || board[ox][oy] == 'A') {
                if(c4 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U000027B3");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'm' || board[ox][oy] == 'M') {
                if(c5 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U00002133");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'd' || board[ox][oy] == 'r') {
                if(c6 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U0001F5E1");
                    refresh();
                    attroff(COLOR_PAIR(9));  
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            room[flor][4].pass = rand() % (9000) + 1000;
            mvprintw(1, 1, "                                                                           ");
            mvprintw(1, 1, "password:%d", room[flor][4].pass);
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
                if(room[flor][4].pass == 0) {
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
                    if(p == room[flor][4].pass) {
                        print_map(board);
                        mvprintw(1,0, "%d", room[flor][4].pass);
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
                        mvprintw(1,0, "%d", room[flor][4].pass);
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
             else if(board[ox][oy] == 'a' || board[ox][oy] == 'A') {
                if(c4 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U000027B3");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'm' || board[ox][oy] == 'M') {
                if(c5 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U00002133");
                    attroff(COLOR_PAIR(9));
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            else if(board[ox][oy] == 'd' || board[ox][oy] == 'r') {
                if(c6 == 'p') {
                    attron(COLOR_PAIR(8));
                    mvprintw(ox, oy, ".");
                    attroff(COLOR_PAIR(8));
                }
                else {
                    attron(COLOR_PAIR(9));
                    mvaddstr(ox, oy, "\U0001F5E1");
                    refresh();
                    attroff(COLOR_PAIR(9));  
                }
                attron(COLOR_PAIR(10));
                mvprintw(player.x, player.y, "H"); 
                attroff(COLOR_PAIR(10));
                refresh();
            }
            board[player.x][player.y] = '.';
        //     break;
        // attron(COLOR_PAIR(10));
        // mvprintw(player.x, player.y, "H"); 
        // attroff(COLOR_PAIR(10));
    }
    if(flor != 5) {
        if((room[flor][1].x <= player.x && player.x <= room[flor][1].x + room[flor][1].I) && (room[flor][1].y <= player.y && player.y <= room[flor][1].y + room[flor][1].J) && demon[flor].health > 0 && flor != 2 && flor != 3) {
        refresh();
        if(demon[flor].end-- > 0) {
            attron(COLOR_PAIR(8));
            mvprintw(demon[flor].x, demon[flor].y, ".");
            board[demon[flor].x][demon[flor].y] = '.';
            refresh();
            attroff(COLOR_PAIR(8));
            dfs_boss(board, &demon[flor].x, &demon[flor].y, player.x, player.y, 1);
            attron(COLOR_PAIR(17));
            mvprintw(demon[flor].x, demon[flor].y, "D");
            board[demon[flor].x][demon[flor].y] = 'e';
            refresh();
            attroff(COLOR_PAIR(17));
        }
        else {
            if(check_attack(board, 'e')) {
                damage_handle(1);
            }
        }
    }
        else if((room[flor][2].x <= player.x && player.x <= room[flor][2].x + room[flor][2].I) && (room[flor][2].y <= player.y && player.y <= room[flor][2].y + room[flor][2].J) && fire[flor].health > 0 && flor != 3 && flor != 4) {
        if(fire[flor].end-- > 0) {
            attron(COLOR_PAIR(8));
            mvprintw(fire[flor].x, fire[flor].y, ".");
            board[fire[flor].x][fire[flor].y] = '.';
            refresh();
            attroff(COLOR_PAIR(8));
            dfs_boss(board, &fire[flor].x, &fire[flor].y,  player.x, player.y, 2);
            attron(COLOR_PAIR(17));
            mvprintw(fire[flor].x, fire[flor].y, "F");
            board[fire[flor].x][fire[flor].y] = 'f';
            refresh();
            attroff(COLOR_PAIR(17));
        }
        else {
            if(check_attack(board, 'f')) {
                damage_handle(2);
            }
        }
    }
        else if((room[flor][3].x <= player.x && player.x <= room[flor][3].x + room[flor][3].I) && (room[flor][3].y <= player.y && player.y <= room[flor][3].y + room[flor][3].J) && giant[flor].health > 0) {
        if(giant[flor].end-- > 0) {
            attron(COLOR_PAIR(8));
            mvprintw(giant[flor].x, giant[flor].y, ".");
            board[giant[flor].x][giant[flor].y] = '.';
            refresh();
            attroff(COLOR_PAIR(8));
            dfs_boss(board, &giant[flor].x, &giant[flor].y, player.x, player.y, 3);
            attron(COLOR_PAIR(17));
            mvprintw(giant[flor].x, giant[flor].y, "G");
            board[giant[flor].x][giant[flor].y] = 'i';
            refresh();
            attroff(COLOR_PAIR(17));
        }
        else {
            if(check_attack(board, 'i')) {
                damage_handle(3);
            }
        }
    }
        else if((room[flor][4].x <= player.x && player.x <= room[flor][4].x + room[flor][4].I) && (room[flor][4].y <= player.y && player.y <= room[flor][4].y + room[flor][4].J) && snake[flor].health > 0) {
        attron(COLOR_PAIR(8));
        mvprintw(snake[flor].x, snake[flor].y, ".");
        board[snake[flor].x][snake[flor].y] = '.';
        refresh();
        attroff(COLOR_PAIR(8));
        dfs_boss(board, &snake[flor].x, &snake[flor].y, player.x, player.y, 4);
        attron(COLOR_PAIR(17));
        mvprintw(snake[flor].x, snake[flor].y, "S");
        board[snake[flor].x][snake[flor].y] = 'n';
        refresh();
        attroff(COLOR_PAIR(17)); 
    }
        else if((room[flor][5].x <= player.x && player.x <= room[flor][5].x + room[flor][5].I) && (room[flor][5].y <= player.y && player.y <= room[flor][5].y + room[flor][5].J) && undeed[flor].health > 0) {
        if(undeed[flor].end-- > 0) {
            attron(COLOR_PAIR(8));
            mvprintw(undeed[flor].x, undeed[flor].y, ".");
            board[undeed[flor].x][undeed[flor].y] = '.';
            refresh();
            attroff(COLOR_PAIR(8));
            dfs_boss(board, &undeed[flor].x, &undeed[flor].y, player.x, player.y, 5);
            attron(COLOR_PAIR(17));
            mvprintw(undeed[flor].x, undeed[flor].y, "U");
            board[undeed[flor].x][undeed[flor].y] = 'u';
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
    else if(flor == 5) {
        if(demon[flor].end-- > 0) {
            attron(COLOR_PAIR(8));
            mvprintw(demon[flor].x, demon[flor].y, ".");
            board[demon[flor].x][demon[flor].y] = '.';
            refresh();
            attroff(COLOR_PAIR(8));
            dfs_boss(board, &demon[flor].x, &demon[flor].y, player.x, player.y, 1);
            attron(COLOR_PAIR(17));
            mvprintw(demon[flor].x, demon[flor].y, "D");
            board[demon[flor].x][demon[flor].y] = 'e';
            refresh();
            attroff(COLOR_PAIR(17));
        }
        else {
            if(check_attack(board, 'e')) {
                damage_handle(1);
            }
        }
        if(fire[flor].end-- > 0) {
            attron(COLOR_PAIR(8));
            mvprintw(fire[flor].x, fire[flor].y, ".");
            board[fire[flor].x][fire[flor].y] = '.';
            refresh();
            attroff(COLOR_PAIR(8));
            dfs_boss(board, &fire[flor].x, &fire[flor].y,  player.x, player.y, 2);
            attron(COLOR_PAIR(17));
            mvprintw(fire[flor].x, fire[flor].y, "F");
            board[fire[flor].x][fire[flor].y] = 'f';
            refresh();
            attroff(COLOR_PAIR(17));
        }
        else {
            if(check_attack(board, 'f')) {
                damage_handle(2);
            }
        }
        if(giant[flor].end-- > 0) {
            attron(COLOR_PAIR(8));
            mvprintw(giant[flor].x, giant[flor].y, ".");
            board[giant[flor].x][giant[flor].y] = '.';
            refresh();
            attroff(COLOR_PAIR(8));
            dfs_boss(board, &giant[flor].x, &giant[flor].y, player.x, player.y, 3);
            attron(COLOR_PAIR(17));
            mvprintw(giant[flor].x, giant[flor].y, "G");
            board[giant[flor].x][giant[flor].y] = 'i';
            refresh();
            attroff(COLOR_PAIR(17));
        }
        else {
            if(check_attack(board, 'i')) {
                damage_handle(3);
            }
        }
        attron(COLOR_PAIR(8));
        mvprintw(snake[flor].x, snake[flor].y, ".");
        board[snake[flor].x][snake[flor].y] = '.';
        refresh();
        attroff(COLOR_PAIR(8));
        dfs_boss(board, &snake[flor].x, &snake[flor].y, player.x, player.y, 4);
        attron(COLOR_PAIR(17));
        mvprintw(snake[flor].x, snake[flor].y, "S");
        board[snake[flor].x][snake[flor].y] = 'n';
        refresh();
        attroff(COLOR_PAIR(17)); 
        if(undeed[flor].end-- > 0) {
            attron(COLOR_PAIR(8));
            mvprintw(undeed[flor].x, undeed[flor].y, ".");
            board[undeed[flor].x][undeed[flor].y] = '.';
            refresh();
            attroff(COLOR_PAIR(8));
            dfs_boss(board, &undeed[flor].x, &undeed[flor].y, player.x, player.y, 5);
            attron(COLOR_PAIR(17));
            mvprintw(undeed[flor].x, undeed[flor].y, "U");
            board[undeed[flor].x][undeed[flor].y] = 'u';
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
        flag[flor][x - 1][y] = 1;
        attron(COLOR_PAIR(9));
        mvprintw(x - 1, y, "\U00002591");
        attroff(COLOR_PAIR(9));
    }
    else if(board[x - 1][y] == '+') {
        flag[flor][x - 1][y] = 1;
        attron(COLOR_PAIR(8));
        mvprintw(x - 1, y, "+");
        attroff(COLOR_PAIR(8));
    }
    if(board[x + 1][y] == '#') {
        flag[flor][x + 1][y] = 1;
        attron(COLOR_PAIR(9));
        mvprintw(x + 1, y, "\U00002591");
        attroff(COLOR_PAIR(9));
    }
    else if(board[x + 1][y] == '+') {
        flag[flor][x + 1][y] = 1;
        attron(COLOR_PAIR(8));
        mvprintw(x + 1, y, "+");
        attroff(COLOR_PAIR(8));
    }
    if(board[x][y - 1] == '#') {
        flag[flor][x][y - 1] = 1;
        attron(COLOR_PAIR(9));
        mvprintw(x, y - 1, "\U00002591");
        attroff(COLOR_PAIR(9));
    }
    else if(board[x][y - 1] == '+') {
        flag[flor][x][y - 1] = 1;
        attron(COLOR_PAIR(8));
        mvprintw(x, y - 1, "+");
        attroff(COLOR_PAIR(8));
    }
    if(board[x][y + 1] == '#') {
        flag[flor][x][y + 1] = 1;
        attron(COLOR_PAIR(9));
        mvprintw(x, y + 1, "\U00002591");
        attroff(COLOR_PAIR(9));
    } 
    else if(board[x][y + 1] == '+') {
        flag[flor][x][y + 1] = 1;
        attron(COLOR_PAIR(8));
        mvprintw(x, y + 1, "+");
        attroff(COLOR_PAIR(8));
    }
    if(board[x - 2][y] == '#') {
        flag[flor][x - 2][y] = 1;
        attron(COLOR_PAIR(9));
        mvprintw(x - 2, y, "\U00002591");
        attroff(COLOR_PAIR(9));
    }
    else if(board[x - 2][y] == '+') {
        flag[flor][x - 2][y] = 1;
        attron(COLOR_PAIR(8));
        mvprintw(x - 2, y, "+");
        attroff(COLOR_PAIR(8));
    }
    if(board[x + 2][y] == '#') {
        flag[flor][x + 2][y] = 1;
        attron(COLOR_PAIR(9));
        mvprintw(x + 2, y, "\U00002591");
        attroff(COLOR_PAIR(9));
    }
    else if(board[x + 2][y] == '+') {
        flag[flor][x + 2][y] = 1;
        attron(COLOR_PAIR(8));
        mvprintw(x + 2, y, "+");
        attroff(COLOR_PAIR(8));
    }
    if(board[x][y - 2] == '#') {
        flag[flor][x][y - 2] = 1;
        attron(COLOR_PAIR(9));
        mvprintw(x, y - 2, "\U00002591");
        attroff(COLOR_PAIR(9));
    }
    else if(board[x][y - 2] == '+') {
        flag[flor][x][y - 2] = 1;
        attron(COLOR_PAIR(8));
        mvprintw(x, y - 2, "+");
        attroff(COLOR_PAIR(8));
    }
    if(board[x][y + 2] == '#') {
        flag[flor][x][y + 2] = 1;
        attron(COLOR_PAIR(9));
        mvprintw(x, y + 2, "\U00002591");
        attroff(COLOR_PAIR(9));
    } 
    else if(board[x][y + 2] == '+') {
        flag[flor][x][y + 2] = 1;
        attron(COLOR_PAIR(8));
        mvprintw(x, y + 2, "+");
        attroff(COLOR_PAIR(8));
    }
    
    refresh();
}

void check_door(char** board, int x, int y) {
    for(int i = 0; i < 6; i++) {
        if(x == room[flor][i].door.x && y == room[flor][i].door.y) {
            for(int j = room[flor][i].x - 1; j <= room[flor][i].x + room[flor][i].I; j++) {
                for(int q = room[flor][i].y - 1; q <= room[flor][i].y + room[flor][i].J; q++) {
                    flag[flor][j][q] = 1;
                }
            }
        }
    }
    print_map(board);
}

void food_list(char** board) {
    clear();
    mvprintw(15, 73, "hunger:");
    for(int i = 0 ; i < (player.hunger / 10); i++) {
        mvaddstr(15,80 + i,"\U000025A3");
    }
    while(1) {
        mvprintw(17, 60, "Type");
        mvprintw(17, 76, "numbers saved");
        mvprintw(17, 100, "health increase");
        mvprintw(19, 60, "1:regular food");
        mvprintw(21, 60, "2.magical food");
        mvprintw(23, 60, "3.exquisite food");
        mvprintw(19, 82, "%d", reg_food + y_food);//y_food --> expired
        mvprintw(21, 82, "%d", x_food);//x_food --> magical 
        mvprintw(23, 82, "%d", z_food);//z_food --> exquisite
        mvprintw(19, 105, "50");
        mvprintw(21, 105, "50");
        mvprintw(23, 105, "50");
        refresh();
        char n = getchar();
        if(n == '1') {
            if(y_food > 0)  {
                player.health -= 50;
                mvprintw(25, 82, "                                 ");
                mvprintw(25, 82, "you ate expired food");
                y_food--;
                continue;
            }
            if(reg_food <= 0) {
                mvprintw(25, 82, "                                 ");
                mvprintw(25, 82, "Not Enough Food");
                refresh();
                continue;
            }
            player.hunger += 80;
            player.health += 50;
            reg_food--;
        }
        else if(n == '2') {
            if(x_food <= 0) {
                mvprintw(25, 82, "                                 ");
                mvprintw(25, 82, "Not Enough Food");
                refresh();
                continue;
            }
            player.hunger += 80;
            x_food--;
            s = 1;
        } 
        else if(n == '3') {
            if(z_food <= 0) {
                mvprintw(25, 82, "                                 ");
                mvprintw(25, 82, "Not Enough Food");
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

void loading(int flor) {
    clear();
    mvprintw(22, 92, "loading");
    for(int i = 0; i < flor; i++) {
        mvaddstr(23, 93 + i, "\U000025A3");
        refresh();
    }
}

void weapon_list(char** board){
    clear();
    attron(COLOR_PAIR(9));
    mvprintw(17, 60, "name");
    mvprintw(17, 68, "sign");
    mvprintw(17, 76, "numbers saved");
    mvprintw(17, 95, "type");
    mvprintw(17, 105, "damage");
    mvprintw(17, 117, "range");
    mvprintw(19, 60, "1.mace    \U00002692             %d          close       5            -", mace);
    mvprintw(21, 60, "2.dagger  \U0001F5E1             %d          long        12           5", dagger);
    mvprintw(23, 60, "3.wand    \U00002133             %d          long        15           10", wand);
    mvprintw(25, 60, "4.arrow   \U000027B3             %d          long        5            5", arrow);
    mvprintw(27, 60, "5.sword   \U00002694             %d          close       5            -", sword);
    refresh();

    while(1) {
        attron(COLOR_PAIR(13));
        if(strcmp(player.weapon, "mace") == 0) {
            mvaddstr(19, 58, "\U000021FE");
        }
        else if(strcmp(player.weapon, "dagger") == 0) {
            mvaddstr(21, 58, "\U000021FE");
        }
        else if(strcmp(player.weapon, "wand") == 0) {
            mvaddstr(23, 58, "\U000021FE");
        }
        else if(strcmp(player.weapon, "arrow") == 0) {
            mvaddstr(25, 58, "\U000021FE");
        }
        else if(strcmp(player.weapon, "sword") == 0) {
            mvaddstr(27, 58, "\U000021FE");
        }
        refresh();
        attroff(COLOR_PAIR(13));

        char n = getchar();
        if(n == '1') {
            if(strcmp(player.weapon, " ") != 0) {
                mvprintw(29, 60, "                                        ");
                mvprintw(29, 60, "put your current weapon in the bag first");
                refresh();
                napms(2500);
            }
            else {
                strcpy(player.weapon, "mace");
                mvprintw(29, 60, "                                 ");
                mvprintw(29, 60, "your current weapon is now %s", player.weapon);
                refresh();
                napms(2500);
            }
            print_map(board);
            break;
        }
        else if(n == '2') {
            if(strcmp(player.weapon, " ") != 0) {
                mvprintw(29, 60, "                                        ");
                mvprintw(29, 60, "put your current weapon in the bag first");
                refresh();
                napms(2500);
            }
            else if(dagger == 0) {
                mvprintw(29, 60, "                         ");
                mvprintw(29, 60, "you don't have any dagger");
                refresh();
                napms(2500);
            }
            else {
                strcpy(player.weapon, "dagger");
                mvprintw(29, 60, "                                 ");
                mvprintw(29, 60, "your current weapon is now %s", player.weapon);
                refresh();
                napms(2500);
            }
            print_map(board);
            break;
        } 
        else if(n == '3') {
            if(strcmp(player.weapon, " ") != 0) {
                mvprintw(29, 60, "                                        ");
                mvprintw(29, 60, "put your current weapon in the bag first");
                refresh();
                napms(2500);
            }
            else if(wand == 0) {
                mvprintw(29, 60, "                       ");
                mvprintw(29, 60, "you don't have any wand");
                refresh();
                napms(2500);
            }
            else {
                strcpy(player.weapon, "wand");
                mvprintw(29, 60, "                                 ");
                mvprintw(29, 60, "your current weapon is now %s", player.weapon);
                refresh();
                napms(2500);
            }
            print_map(board);
            break;
        }
        else if(n == '4') {
            if(strcmp(player.weapon, " ") != 0) {
                mvprintw(29, 60, "                                        ");
                mvprintw(29, 60, "put your current weapon in the bag first");
                refresh();
                napms(2500);
            }
            else if(arrow == 0) {
                mvprintw(29, 60, "                        ");
                mvprintw(29, 60, "you don't have any arrow");
                refresh();
                napms(2500);
            }
            else {
                strcpy(player.weapon, "arrow");
                mvprintw(29, 60, "                                 ");
                mvprintw(29, 60, "your current weapon is now %s", player.weapon);
                refresh();
                napms(2500);
            }
            print_map(board);
            break;
        }
        else if(n == '5') {
            if(strcmp(player.weapon, " ") != 0) {
                mvprintw(29, 60, "                                        ");
                mvprintw(29, 60, "put your current weapon in the bag first");
                refresh();
                napms(2500);
            }
            else if(sword == 0) {
                mvprintw(29, 60, "                        ");
                mvprintw(29, 60, "you don't have any sword");
                refresh();
                napms(2500);
            }
            else {
                strcpy(player.weapon, "sword");
                mvprintw(29, 60, "                                 ");
                mvprintw(29, 60, "your current weapon is now %s", player.weapon);
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
            refresh();
        }
        else {
            mvprintw(29, 60, "                              ");
            mvprintw(29, 60, "please choose the right number");
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
    mvprintw(17, 81, "name");
    mvprintw(17, 92, "sign");
    mvprintw(17, 99, "numbers saved");
    refresh();
    while(1) {
        mvprintw(19, 81, "1.health    \U00002671            %d ", health);
        mvprintw(21, 81, "2.damage    \U00002622            %d ", damage);
        mvprintw(23, 81, "3.speed     \U0001F6E6            %d ", speed);
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
        demon[i].health = 5, demon[i].damage = 40, demon[i].end = 15, demon[i].x = 0, demon[i].y = 0;
        fire[i].health = 10, fire[i].damage = 60, fire[i].end = 12, fire[i].x = 0, fire[i].y = 0;
        giant[i].health = 15, giant[i].damage = 80, giant[i].end = 10, giant[i].x = 0, giant[i].y = 0;
        snake[i].health = 20, snake[i].damage = 100, snake[i].x = 0, snake[i].y = 0;
        undeed[i].health = 30, undeed[i].damage = 140, undeed[i].end = 8, undeed[i].x = 0, undeed[i].y = 0;
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
            player.health -= demon[flor].damage;
            attron(COLOR_PAIR(9));
            mvprintw(2, 1, "                                                                           ");
            mvprintw(2, 1, "Got hit by demon");
            attroff(COLOR_PAIR(9));
            break;
        case 2:
            player.health -= fire[flor].damage;
            attron(COLOR_PAIR(9));
            mvprintw(2, 1, "                                                                           ");
            mvprintw(2, 1, "Got hit by fire");
            attroff(COLOR_PAIR(9));
            break;
        case 3:
            player.health -= giant[flor].damage;
            attron(COLOR_PAIR(9));
            mvprintw(2, 1, "                                                                           ");
            mvprintw(2, 1, "Got hit by giant");
            attroff(COLOR_PAIR(9));
            break;
        case 4:
            player.health -= snake[flor].damage;
            attron(COLOR_PAIR(9));
            mvprintw(2, 1, "                                                                           ");
            mvprintw(2, 1, "Got hit by snake");
            attroff(COLOR_PAIR(9));
            break;
        case 5:
            player.health -= undeed[flor].damage;
            attron(COLOR_PAIR(9));
            mvprintw(2, 1, "                                                                           ");
            mvprintw(2, 1, "Got hit by undeed");
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
            demon[flor].health -= 10;
            }
            else {
                demon[flor].health -= 5;
            }
            if(demon[flor].health <= 0){demon[flor].health = 0;}
            attron(COLOR_PAIR(9));
            mvprintw(1, 1, "                                                                           ");
            mvprintw(1, 1, "you hit demon, demon's health:%d", demon[flor].health);
            refresh();
            attroff(COLOR_PAIR(9));
            if(demon[flor].health <= 0) {
                player.score += 10;
                attron(COLOR_PAIR(9));
                mvprintw(2, 1, "                                                                           ");
                mvprintw(2, 1, "demon is dead");
                attroff(COLOR_PAIR(9));
                find_boss(board, 'e');
            }
        }
        else if(check_attack(board, 'f')) {
            if(d) {
                fire[flor].health -= 10;
            }
            else {
                fire[flor].health -= 5;
            }
            if(fire[flor].health <= 0){fire[flor].health = 0;}
            attron(COLOR_PAIR(9));
            mvprintw(1, 1, "                                                                           ");
            mvprintw(1, 1, "you hit fire, fire's health:%d", fire[flor].health);
            refresh();
            attroff(COLOR_PAIR(9));
            if(fire[flor].health <= 0) {
                player.score += 20;
                attron(COLOR_PAIR(9));
                mvprintw(2, 1, "                                                                           ");
                mvprintw(2, 1, "fire is dead");
                attroff(COLOR_PAIR(9));
                find_boss(board, 'f');
            }
        }
        else if(check_attack(board, 'i')) {
            if(d) {
                giant[flor].health -= 10;
            }
            else {
                giant[flor].health -= 5;
            }
            if(giant[flor].health <= 0){giant[flor].health = 0;}
            attron(COLOR_PAIR(9));
            mvprintw(1, 1, "                                                                           ");
            mvprintw(1, 1, "you hit giant, giant's health:%d", giant[flor].health);
            refresh();
            attroff(COLOR_PAIR(9));
            if(giant[flor].health <= 0) {
                player.score += 30;
                attron(COLOR_PAIR(9));
                mvprintw(2, 1, "                                                                           ");
                mvprintw(2, 1, "giant is dead");
                attroff(COLOR_PAIR(9));
                find_boss(board, 'i');
            }
        }
        else if(check_attack(board, 'n')) {
            if(d) {
                snake[flor].health -= 10;
            }
            else {
                snake[flor].health -= 5;
            }
            if(snake[flor].health <= 0){snake[flor].health = 0;}
            attron(COLOR_PAIR(9));
            mvprintw(1, 1, "                                                                           ");
            mvprintw(1, 1, "you hit snake, snake's health:%d", snake[flor].health);
            refresh();
            attroff(COLOR_PAIR(9));
            if(snake[flor].health <= 0) {
                player.score += 40;
                attron(COLOR_PAIR(9));
                mvprintw(2, 1, "                                                                           ");
                mvprintw(2, 1, "sanke is dead");
                attroff(COLOR_PAIR(9));
                find_boss(board, 'n');
            }
        }
        else if(check_attack(board, 'u')) {
            if(d) {
                undeed[flor].health -= 10;
            }
            else {
                undeed[flor].health -= 5;
            }
            if(undeed[flor].health <= 0){undeed[flor].health = 0;}
            attron(COLOR_PAIR(9));
            mvprintw(1, 1, "                                                                           ");
            mvprintw(1, 1, "your hit undeed, undeed's health:%d", undeed[flor].health);
            refresh();
            attroff(COLOR_PAIR(9));
            if(undeed[flor].health <= 0) {
                player.score += 50;
                attron(COLOR_PAIR(9));
                mvprintw(2, 1, "                                                                           ");
                mvprintw(2, 1, "undeed is dead");
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
        print_map(board);
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
        print_map(board);
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
        print_map(board);
    }
    
    else if(strcmp(player.weapon, "sword") == 0) {
        if(check_attack(board, 'e')) {
            if(d) {
                demon[flor].health -= 20;
            }
            else {
                demon[flor].health -= 10;
            }
            if(demon[flor].health <= 0){demon[flor].health = 0;}
            attron(COLOR_PAIR(9));
            mvprintw(1, 1, "                                                                           ");
            mvprintw(1, 1, "you hit demon, demon's health:%d", demon[flor].health);
            refresh();
            attroff(COLOR_PAIR(9));
            if(demon[flor].health <= 0) {
                player.score += 10;
                attron(COLOR_PAIR(9));
                mvprintw(2, 1, "                                                                           ");
                mvprintw(2, 1, "demon is dead");
                attroff(COLOR_PAIR(9));
                find_boss(board, 'e');
            }
        }
        else if(check_attack(board, 'f')) {
            if(d) {
                fire[flor].health -= 20;
            }
            else {
                fire[flor].health -= 10;
            }
            if(fire[flor].health <= 0){fire[flor].health = 0;}
            attron(COLOR_PAIR(9));
            mvprintw(1, 1, "                                                                           ");
            mvprintw(1, 1, "you hit fire, fire's health:%d", fire[flor].health);
            refresh();
            attroff(COLOR_PAIR(9));
            if(fire[flor].health <= 0) {
                player.score += 20;
                attron(COLOR_PAIR(9));
                mvprintw(2, 1, "                                                                           ");
                mvprintw(2, 1, "fire is dead");
                attroff(COLOR_PAIR(9));
                find_boss(board, 'f');
            }
        }
        else if(check_attack(board, 'i')) {
            if(d) {
                giant[flor].health -= 20;
            }
            else {
                giant[flor].health -= 10;
            }
            if(giant[flor].health <= 0){giant[flor].health = 0;}
            attron(COLOR_PAIR(9));
            mvprintw(1, 1, "                                                                           ");
            mvprintw(1, 1, "you hit gaint, giant's health:%d", giant[flor].health);
            refresh();
            attroff(COLOR_PAIR(9));
            if(giant[flor].health <= 0) {
                player.score += 30;
                attron(COLOR_PAIR(9));
                mvprintw(2, 1, "                                                                           ");
                mvprintw(2, 1, "giant is dead");
                attroff(COLOR_PAIR(9));
                find_boss(board, 'i');
            }
        }
        else if(check_attack(board, 'n')) {
            if(d) {
                snake[flor].health -= 20;
            }
            else {
                snake[flor].health -= 10;
            }
            if(snake[flor].health <= 0){snake[flor].health = 0;}
            attron(COLOR_PAIR(9));
            mvprintw(1, 1, "                                                                           ");
            mvprintw(1, 1, "you hit snake, snake's health:%d", snake[flor].health);
            refresh();
            attroff(COLOR_PAIR(9));
            if(snake[flor].health <= 0) {
                player.score += 40;
                attron(COLOR_PAIR(9));
                mvprintw(3, 0, "                 ");
                mvprintw(3, 0, "snake is dead");
                attroff(COLOR_PAIR(9));
                find_boss(board, 'n');
            }
        }
        else if(check_attack(board, 'u')) {
            if(d) {
                undeed[flor].health -= 20;
            }
            else {
                undeed[flor].health -= 10;
            }
            if(undeed[flor].health <= 0){undeed[flor].health = 0;}
            attron(COLOR_PAIR(9));
            mvprintw(1, 1, "                                                                           ");
            mvprintw(1, 1, "you hit undeed, undeed's health:%d", undeed[flor].health);
            refresh();
            attroff(COLOR_PAIR(9));
            if(undeed[flor].health <= 0) {
                player.score += 50;
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
                if(damage == 12) {
                    attron(COLOR_PAIR(9));
                    mvprintw((*x), (*y), "\U0001F5E1");
                    refresh();
                    attroff(COLOR_PAIR(9));
                    napms(150);

                }
                else if(damage == 15) {
                    attron(COLOR_PAIR(9));
                    mvprintw((*x), (*y), "\U00002133");
                    refresh();
                    attroff(COLOR_PAIR(9));
                    napms(150);
                }
                else if(damage == 5) {
                    attron(COLOR_PAIR(9));
                    mvprintw((*x), (*y), "\U000027B3");
                    refresh();
                    attroff(COLOR_PAIR(9));
                    napms(150);
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
                if(damage == 12) {
                    attron(COLOR_PAIR(9));
                    mvprintw((*x), (*y), "\U0001F5E1");
                    refresh();
                    attroff(COLOR_PAIR(9));
                    napms(150);
                }
                else if(damage == 15) {
                    attron(COLOR_PAIR(9));
                    mvprintw((*x), (*y), "\U00002133");
                    refresh();
                    attroff(COLOR_PAIR(9));
                    napms(150);
                }
                else if(damage == 5) {
                    attron(COLOR_PAIR(9));
                    mvprintw((*x), (*y), "\U000027B3");
                    refresh();
                    attroff(COLOR_PAIR(9));
                    napms(150);
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
                if(damage == 12) {
                    attron(COLOR_PAIR(9));
                    mvprintw((*x), (*y), "\U0001F5E1");
                    refresh();
                    attroff(COLOR_PAIR(9));
                    napms(150);
                }
                else if(damage == 15) {
                    attron(COLOR_PAIR(9));
                    mvprintw((*x), (*y), "\U00002133");
                    refresh();
                    attroff(COLOR_PAIR(9));
                    napms(150);
                }
                else if(damage == 5) {
                    attron(COLOR_PAIR(9));
                    mvprintw((*x), (*y), "\U000027B3");
                    refresh();
                    attroff(COLOR_PAIR(9));
                    napms(150);
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
                if(damage == 12) {
                    attron(COLOR_PAIR(9));
                    mvprintw((*x), (*y), "\U0001F5E1");
                    refresh();
                    attroff(COLOR_PAIR(9));
                    napms(150);
                }
                else if(damage == 15) {
                    attron(COLOR_PAIR(9));
                    mvprintw((*x), (*y), "\U00002133");
                    refresh();
                    attroff(COLOR_PAIR(9));
                    napms(150);
                }
                else if(damage == 5) {
                    attron(COLOR_PAIR(9));
                    mvprintw((*x), (*y), "\U000027B3");
                    refresh();
                    attroff(COLOR_PAIR(9));
                    napms(150);
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
                if(damage == 12) {
                    attron(COLOR_PAIR(9));
                    mvprintw((*x), (*y), "\U0001F5E1");
                    refresh();
                    attroff(COLOR_PAIR(9));
                    napms(150);
                }
                else if(damage == 15) {
                    attron(COLOR_PAIR(9));
                    mvprintw((*x), (*y), "\U00002133");
                    refresh();
                    attroff(COLOR_PAIR(9));
                    napms(150);
                }
                else if(damage == 5) {
                    attron(COLOR_PAIR(9));
                    mvprintw((*x), (*y), "\U000027B3");
                    refresh();
                    attroff(COLOR_PAIR(9));
                    napms(150);
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
                if(damage == 12) {
                    attron(COLOR_PAIR(9));
                    mvprintw((*x), (*y), "\U0001F5E1");
                    refresh();
                    attroff(COLOR_PAIR(9));
                    napms(150);
                }
                else if(damage == 15) {
                    attron(COLOR_PAIR(9));
                    mvprintw((*x), (*y), "\U00002133");
                    refresh();
                    attroff(COLOR_PAIR(9));
                    napms(150);
                }
                else if(damage == 5) {
                    attron(COLOR_PAIR(9));
                    mvprintw((*x), (*y), "\U000027B3");
                    refresh();
                    attroff(COLOR_PAIR(9));
                    napms(150);
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
                if(damage == 12) {
                    attron(COLOR_PAIR(9));
                    mvprintw((*x), (*y), "\U0001F5E1");
                    refresh();
                    attroff(COLOR_PAIR(9));
                    napms(150);
                }
                else if(damage == 15) {
                    attron(COLOR_PAIR(9));
                    mvprintw((*x), (*y), "\U00002133");
                    refresh();
                    attroff(COLOR_PAIR(9));
                    napms(150);
                }
                else if(damage == 5) {
                    attron(COLOR_PAIR(9));
                    mvprintw((*x), (*y), "\U000027B3");
                    refresh();
                    attroff(COLOR_PAIR(9));
                    napms(150);
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
                if(damage == 12) {
                    attron(COLOR_PAIR(9));
                    mvprintw((*x), (*y), "\U0001F5E1");
                    refresh();
                    attroff(COLOR_PAIR(9));
                    napms(150);
                }
                else if(damage == 15) {
                    attron(COLOR_PAIR(9));
                    mvprintw((*x), (*y), "\U00002133");
                    refresh();
                    attroff(COLOR_PAIR(9));
                    napms(150);
                }
                else if(damage == 5) {
                    attron(COLOR_PAIR(9));
                    mvprintw((*x), (*y), "\U000027B3");
                    refresh();
                    attroff(COLOR_PAIR(9));
                    napms(150);
                }
                break;
        }
    }

    return 0;
}

int find_boss2(char** board, int x, int y, int damage) {
    switch(board[x][y]) {
        case 'e':
            if(d) {
                demon[flor].health -= 2 * damage;
            }
            else {
                demon[flor].health -= damage;
            }
            if(demon[flor].health <= 0){demon[flor].health = 0;}
            attron(COLOR_PAIR(9));
            mvprintw(1, 1, "                                                                           ");
            mvprintw(1, 1, "you hit demon, demon's health:%d", demon[flor].health);
            refresh();
            attroff(COLOR_PAIR(9));
            if(demon[flor].health == 0) {
                player.score += 10;
                attron(COLOR_PAIR(8));
                mvprintw(demon[flor].x, demon[flor].y, ".");
                board[demon[flor].x][demon[flor].y] = '.';
                refresh();
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(9));
                mvprintw(2, 1, "                                                                           ");
                mvprintw(2, 1, "demon is dead");
                attroff(COLOR_PAIR(9));
            }
            if(damage == 15) {
                demon[flor].end = 0;
            }
            return 1;
            break;
        case 'f':
            if(d) {
                fire[flor].health -= 2 * damage;
            }
            else {
                fire[flor].health -= damage;
            }
            if(fire[flor].health <= 0){fire[flor].health = 0;}
            attron(COLOR_PAIR(9));
            mvprintw(1, 1, "                                                                           ");
            mvprintw(1, 1, "you hit fire, fire's health:%d", fire[flor].health);
            refresh();
            attroff(COLOR_PAIR(9));
            if(fire[flor].health == 0) {
                player.score += 20;
                attron(COLOR_PAIR(8));
                mvprintw(fire[flor].x, fire[flor].y, ".");
                board[fire[flor].x][fire[flor].y] = '.';
                refresh();
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(9));
                mvprintw(2, 1, "                                                                           ");
                mvprintw(2, 1, "fire is dead");
                attroff(COLOR_PAIR(9));
            }
            if(damage == 15) {
                fire[flor].end = 0;
            }
            return 1;
            break;
        case 'i':
            if(d) {
                giant[flor].health -= 2 * damage;
            }
            else {
                giant[flor].health -= damage;
            }
            if(giant[flor].health <= 0){giant[flor].health = 0;}
            attron(COLOR_PAIR(9));
            mvprintw(1, 1, "                                                                           ");
            mvprintw(1, 1, "you hit giant, giant's health:%d", giant[flor].health);
            refresh();
            attroff(COLOR_PAIR(9));
            if(giant[flor].health == 0) {
                player.score += 30;
                attron(COLOR_PAIR(8));
                mvprintw(giant[flor].x, giant[flor].y, ".");
                board[giant[flor].x][giant[flor].y] = '.';
                refresh();
                attroff(COLOR_PAIR(8));
                mvprintw(2, 1, "                                                                           ");
                mvprintw(2, 1, "giant is dead");
            }
            if(damage == 15) {
                giant[flor].end = 0;
            }
            return 1;
            break;
        case 'n':
            if(d) {
                snake[flor].health -= 2 * damage;
            }
            else {
                snake[flor].health -= damage;
            }
            if(snake[flor].health <= 0){snake[flor].health = 0;}
            attron(COLOR_PAIR(9));
            mvprintw(1, 1, "                                                                           ");
            mvprintw(1, 1, "you hit snake, snake's health:%d", snake[flor].health);
            refresh();
            attroff(COLOR_PAIR(9));
            if(snake[flor].health == 0) {
                player.score += 40;
                attron(COLOR_PAIR(8));
                mvprintw(snake[flor].x, snake[flor].y, ".");
                board[snake[flor].x][snake[flor].y] = '.';
                refresh();
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(9));
                mvprintw(2, 1, "                                                                           ");
                mvprintw(2, 1, "sanke is dead");
                attroff(COLOR_PAIR(9));
            }
            if(damage == 15) {
                snake[flor].end = 0;
            }
            return 1;
            break;
        case 'u':
            if(d) {
                undeed[flor].health -= 2 * damage;
            }
            else {
                undeed[flor].health -= damage;
            }
            if(undeed[flor].health <= 0){undeed[flor].health = 0;}
            attron(COLOR_PAIR(9));
            mvprintw(1, 1, "                                                                           ");
            mvprintw(1, 1, "you hit undeed, undeed's health:%d", undeed[flor].health);
            refresh();
            attroff(COLOR_PAIR(9));
            if(undeed[flor].health == 0) {
                player.score += 50;
                attron(COLOR_PAIR(8));
                mvprintw(undeed[flor].x, undeed[flor].y, ".");
                board[undeed[flor].x][undeed[flor].y] = '.';
                refresh();
                attroff(COLOR_PAIR(8));
                attron(COLOR_PAIR(9));
                mvprintw(2, 1, "                                                                           ");
                mvprintw(2, 1, "undeed is dead");
                attroff(COLOR_PAIR(9));
            }
            if(damage == 15) {
                undeed[flor].end = 0;
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
    // FILE* f1 = fopen(player.name, "r");
    // fprintf()
    // fclose(f1);
    if(karbar == 1) {
        FILE* f;
        f = fopen("info1", "w");
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

    }
    else if(karbar == 2) {
        FILE* f;
        f = fopen("info2", "w");
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
    }
    else if(karbar == 3) {
        FILE* f;
        f = fopen("info3", "w");
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
    }
    else if(karbar == 4) {
        FILE* f;
        f = fopen("info4", "w");
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
    }
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
        fprintf(f1, "%d\n", demon[i].health);
        fprintf(f1, "%d\n", fire[i].health);
        fprintf(f1, "%d\n", giant[i].health);
        fprintf(f1, "%d\n", snake[i].health);
        fprintf(f1, "%d\n", undeed[i].health);
        fprintf(f1, "%d\n", demon[i].end);
        fprintf(f1, "%d\n", fire[i].end);
        fprintf(f1, "%d\n", giant[i].end);
        fprintf(f1, "%d\n", snake[i].end);
        fprintf(f1, "%d\n", undeed[i].end);

    }
    fclose(f1);
}

void save_other() {
    FILE* f;
    f = fopen("other", "w");
    fprintf(f, "%d\n", flor);
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
    else if(karbar == 4) {
        FILE* f = fopen("scoreboard4", "w");
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
    player.score += player.gold * 10 + player.exp;
    mvprintw(20,83, "press any key to quit");
    mvprintw(22, 83, "your score:%d", player.score);
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