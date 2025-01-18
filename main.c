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
typedef struct {
    int x, y;
} pos;
pos doors[6];
typedef struct {
    char name[100], pass[100], mail[100];
    int points, golds, exp, health, color, x, y, hunger;
} att;
att player;
typedef struct {
    int x, y;
    char c[100][100];
    int pass;
} Room;
Room* room;
char message[100];
int floor = 1, T = 0, reg_food = 0; 
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
int check_room(Room*);
void Doors(pos*, char***);
void print_character(int, int, char**, char**);
void save_borad();
void create_board(char***);
void food_list(char**);
int main() {
    setlocale(LC_CTYPE, "");
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
    init_pair(11, COLOR_RED, COLOR_BLACK);
    //init_color(19, 500, 0, 700);
    init_color(15, 240, 90, 90);
    init_pair(14, 15, COLOR_BLACK);
    init_pair(8, COLOR_GREEN, COLOR_BLACK);
    init_pair(10, COLOR_BLUE, COLOR_BLACK);
    init_pair(9, COLOR_WHITE, COLOR_BLACK);
    init_pair(12, 1, COLOR_BLACK);
    init_pair(13, COLOR_YELLOW, COLOR_BLACK);
    attron(COLOR_PAIR(8));
    //initialize();
    char** board1;
    char** board2;
    char** board3;
    char** board4;
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
    room = malloc(6 * sizeof(Room));
    room[4].pass = 0;
    create_map(&board1);
    floor++; 
    create_map(&board2);  
    create_map(&board3); 
    create_map(&board4); 
    floor = 1;
    print_map(board1); 
    save_borad(board1);
    player.health = 900;
    player.hunger = 200;
    while(1) {
        mvprintw(0,184, "0:quit");
        refresh();
        char c;
        mvprintw(46, 0, "HP:");
        if(100 <= player.health) {
            mvprintw(46, 3, "%d", player.health);
        }
        else if(10 <= player.health && player.health <= 99) {
            mvprintw(46, 3, " %d", player.health);
        }
        else {
            mvprintw(46, 3, "  %d", player.health);
        }
        //napms(5000);
        //message[0] = '\0';
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
        default:
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
        room[i].x = rand() % (32) + 2;
        room[i].y = rand() % (158) + 16;
    }
    int x = check_room(room);
    while(x == 0) {
        for(int i = 0; i < 6; i++) {
            room[i].x = rand() % (32) + 2;
            room[i].y = rand() % (158) + 16;
        }
        x = check_room(room);
    }
    srand(time(NULL));
    int nfood = rand() % (6) + 1;
    for(int i = 0; i < 6; i++) {
        int I = rand() % (8) + 4;
        int J = rand() % (7) + 4;
        int x = rand() % (2) + 1;
        int X = rand() % (I - 2) + room[i].x + 1;
        int Y = rand () % (J - 2) + room[i].y + 1;
        int food_x = rand() % (I - 2) + room[i].x + 1;
        int door;
        if(x == 1) {
            door = rand() % (I) + room[i].x;
        }
        else {
            door = rand () % (J) + room[i].y;
        }
        while (abs(door - X) < 1 || abs(door - Y) < 1) {
            if(x == 1) {
                door = rand() % (I) + room[i].x;
            }
            else {
                door = rand () % (J) + room[i].y;
            }
        }
        if(floor == 1) {
            player.x = X + 1 ;
            player.y = Y - 1;
            mvprintw(player.x, player.y, "H"); 
            refresh();
        }
        for(int j = room[i].x; j < room[i].x + I; j++) {
            for(int q = room[i].y; q < room[i].y + J; q++) {
                if(j == X && q == Y) {
                    (*board)[j][q] = 'O';
                    room[i].c[j][q] = 'O';
                    continue;
                }
                else if(j == X - 1 && q == Y) {
                    (*board)[j][q] = '^';
                    room[i].c[j][q] = '.';
                    refresh();
                    continue;
                }
                else if(j == X - 1 && q == Y + 1 && i == 0) {
                    attron(COLOR_PAIR(8));
                    (*board)[j][q] = '<';
                    room[i].c[j][q] = '<';
                    refresh();
                    continue;
                }
                else if(j == X - 1 && q == Y + 1 && i == 4) {
                    (*board)[j][q] = '@';
                    room[i].c[j][q] = '@';
                    attron(COLOR_PAIR(8));
                    refresh();
                    continue;
                }
                else if(j == room[i].x + I - 1 && q == room[i].y + J - 1 && i == 4) {
                    (*board)[j][q] = '&';
                    room[i].c[j][q] = '&';
                    attron(COLOR_PAIR(8));
                    refresh();
                    continue;
                }
                else if(j == room[i].x && q == room[i].y + J - 1 && i == 1) {
                    (*board)[j][q] = 'T';
                    room[i].c[j][q] = 'T';
                    attron(COLOR_PAIR(8));
                    refresh();
                    continue;
                }
                (*board)[j][q] = '.';
                room[i].c[j][q] = '.';
                refresh();
            }
        }
        if(nfood) {
            if((*board)[food_x][J + room[i].y - 1] != 'T' && (*board)[food_x][J + room[i].y - 1] != '@' && (*board)[food_x][J + room[i].y - 1] != '&') {
            (*board)[food_x][J + room[i].y - 1] = 'F';
            nfood--;
            }
        }
        for(int j = room[i].y; j < room[i].y + J; j++) {
            if(x == 2 && door == j) {
                (*board)[room[i].x - 1][j] = '+';
                room[i].c[room[i].x][j] = '+';
                (*board)[room[i].x + I][j] = '_';
                room[i].c[room[i].x + I][j] = '_';
                doors[i].x = room[i].x - 1;
                doors[i].y = j;
                continue;
            }
            (*board)[room[i].x - 1][j] = '_';
            room[i].c[room[i].x][j] = '_';
            (*board)[room[i].x + I][j] = '_';
            room[i].c[room[i].x + I][j] = '_';
            refresh();
        }
        for(int j = room[i].x; j < room[i].x + I; j++) {
            if(x == 1 && door == j) {
                (*board)[j][room[i].y - 1] = '+';
                room[i].c[j][room[i].y] = '+';
                (*board)[j][room[i].y + J] = '|';
                room[i].c[j][room[i].y + J] = '|';
                doors[i].x = j;
                doors[i].y = room[i].y - 1;
                continue;
            }
                (*board)[j][room[i].y - 1] = '|';
                room[i].c[j][room[i].y] = '|';
                (*board)[j][room[i].y + J] = '|';
                room[i].c[j][room[i].y + J] = '|';
                refresh();
        }
    }
    Doors(doors, board);
}
int check_room(Room* room) {
    for(int i = 0; i < 5; i++) {
        for(int j = i + 1; j < 6; j++) {
            refresh();
            if(abs(room[i].y - room[j].y) <= 22 ) {
                return 0;
            }
        }
    }
    return 1;
}
void print_map(char** board) {
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
            else {
                attron(COLOR_PAIR(8));
                mvprintw(i, j, "%c", board[i][j]);
                refresh();
                attroff(COLOR_PAIR(8));
            }
        }
    }

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
        case 'E':
            food_list(board);
            break;
        case 'w': 
            player.x--;
            print_character(x, y, board, next_board);
            break;
        case 's':
            player.x++;
            print_character(x, y, board, next_board);
            break;
        case 'a':
            player.y--;
            print_character(x, y, board, next_board);
            break;
        case 'd':
            player.y++;
            print_character(x, y, board, next_board);
            break;
        case 'e':
            player.x--;
            player.y++;
            print_character(x, y, board, next_board);
            break;
        case 'q':
            player.x--;
            player.y--;
            print_character(x, y, board, next_board);
            break;
        case 'z':
            player.x++;
            player.y--;
            print_character(x, y, board, next_board);
            break;
        case 'x':
            player.x++;
            player.y++;
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
    }
}
void print_character(int ox, int oy, char** board, char** next_board) {
    switch (board[player.x][player.y]) {
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
            break;
        case 'O': 
            player.x = ox;
            player.y = oy;
            break;
        case '_': 
            player.x = ox;
            player.y = oy;
            break;
        case '|': 
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
            else if(board[ox][oy] == ' ') {
                attron(COLOR_PAIR(9));
                strcpy(message, "You entered a new room!");
                mvprintw(0,0,"%s", message);
                attroff(COLOR_PAIR(9));
                attron(COLOR_PAIR(8));
                mvprintw(ox, oy, " ");
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
            mvprintw(0, 0, "TRAP!");
            player.health -= 30;
            break;
        case '<': 
            player.hunger--;
            floor++;
            clear();
            strcpy(message, "You entered the next floor!");
            attron(COLOR_PAIR(9));
            mvprintw(0,0,"%s", message);
            attroff(COLOR_PAIR(9));
            attron(COLOR_PAIR(8));
            print_map(next_board);
            mvprintw(player.x, player.y, "<");
            board[player.x][player.y] = '<';
            break;
        case '&':
            player.hunger--;
            attron(COLOR_PAIR(8));
            mvprintw(ox, oy, ".");
            attroff(COLOR_PAIR(8));
            attron(COLOR_PAIR(10));
            mvprintw(player.x, player.y, "H"); 
            attroff(COLOR_PAIR(10));
            room[4].pass = rand() % (9000) + 1000;
            mvprintw(1,0, "%d", room[4].pass);
            //halfdelay(30);
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
                if(room[4].pass == 0) {
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
                    if(p == room[4].pass) {
                        print_map(board);
                        mvprintw(1,0, "%d", room[4].pass);
                        attron(COLOR_PAIR(8));
                        mvprintw(player.x, player.y, "@");
                        attroff(COLOR_PAIR(8));
                        player.x = ox;
                        player.y = oy;
                    }
                    else {
                        check++;
                        print_map(board);
                        mvprintw(1,0, "%d", room[4].pass);
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
            attron(COLOR_PAIR(8));
            mvprintw(ox, oy, ".");
            attroff(COLOR_PAIR(8));
            attron(COLOR_PAIR(10));
            mvprintw(player.x, player.y, "H"); 
            attroff(COLOR_PAIR(10));
            break;
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
            player.hunger++;
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
void quit() {
    clear();
    mvprintw(20,83, "press any key to quit");
    refresh();
    char c = getchar();
}