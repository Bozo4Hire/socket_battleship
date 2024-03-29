#include <iostream>
#include <string.h>
#include <unistd.h>
#include <curses.h>
#include <ncurses.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include <arpa/inet.h>

#define PORT 8080
#define _OPEN_SYS_SOCK_IPV6

using namespace std;


// i = y = fila 
// j = x = columna

char p1_board [10][10] = {
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
};

char p1_cv [1][4][3] = {
    {{'3','3','#'},{'4','3','#'},{'5','3','#'},{'6','3','#'}}
};
char p1_bb [2][3][3] = {
    {{'5','9','#'},{'6','9','#'},{'7','9','#'}},
    {{'9','0','#'},{'9','1','#'},{'9','2','#'}}
};
char p1_cl [3][2][3] = {
    {{'4','0','#'},{'4','1','#'}},
    {{'6','5','#'},{'6','6','#'}},
    {{'8','7','#'},{'9','7','#'}}
};
char p1_dd [4][1][3] = {
    {{'1','2','#'}},
    {{'2','9','#'}},
    {{'3','6','#'}},
    {{'6','1','#'}}
};

bool p1_fleet_status[10] = {1,1,1,1,1,1,1,1,1,1};

char p2_board [10][10] = {
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
};

char p2_cv [1][4][3];
char p2_bb [2][3][3];
char p2_cl [3][2][3];
char p2_dd [4][1][3];
bool p2_fleet_status [10] = {1,1,1,1,1,1,1,1,1,1};

void drawMyBoard(char [10][10], bool [10]);
void drawEnemyBoard(char [10][10], bool [10]);
void setBoard(char [10][10], char [1][4][3], char [2][3][3], char [3][2][3], char [4][1][3]);
int attack(char, char, char [10][10], char [1][4][3], char [2][3][3], char [3][2][3], char [4][1][3], bool [10]);
bool checkwin(int, char [10][10], char [10][10], bool [10], bool [10], bool [10]);

int main()
{   
    system("clear");
    printf("B A T T L E S H I P\nwaiting for player 2\n");
    sleep(1);

    // Game variables init:
    int player = 1, dummy, atk_error;
    bool victory = 0;

    // Sockety vars init.
    int server_fd, sock, valread;
    struct sockaddr_in address;
    int opt = 1, loop = 1; 
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((sock = accept(server_fd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    for(int b = 0 ; b < 1; b++){            
        for(int c = 0; c < 4; c++){
            for(int d = 0; d < 3; d++){
                char aux = p1_cv[b][c][d];
                char *msg = &aux;
                send(sock, msg, strlen(msg), 0);
                char buffer[1] = {0};
                valread = read(sock, buffer, 1);
                p2_cv[b][c][d] = buffer[0];
            }
        }
    }
    for(int b = 0 ; b < 2; b++){            
        for(int c = 0; c < 3; c++){
            for(int d = 0; d < 3; d++){
                char aux = p1_bb[b][c][d];
                char *msg = &aux;
                send(sock, msg, strlen(msg), 0);
                char buffer[1] = {0};
                valread = read(sock, buffer, 1);
                p2_bb[b][c][d] = buffer[0];
            }
        }
    } 
    for(int b = 0 ; b < 3; b++){            
        for(int c = 0; c < 2; c++){
            for(int d = 0; d < 3; d++){
                char aux = p1_cl[b][c][d];
                char *msg = &aux;
                send(sock, msg, strlen(msg), 0);
                char buffer[1] = {0};
                valread = read(sock, buffer, 1);
                p2_cl[b][c][d] = buffer[0];
            }
        }
    } 
    for(int b = 0 ; b < 4; b++){            
        for(int c = 0; c < 1; c++){
            for(int d = 0; d < 3; d++){
                char aux = p1_dd[b][c][d];
                char *msg = &aux;
                send(sock, msg, strlen(msg), 0);
                char buffer[1] = {0};
                valread = read(sock, buffer, 1);
                p2_dd[b][c][d] = buffer[0];
            }
        }
    } 

    setBoard(p1_board, p1_cv, p1_bb, p1_cl, p1_dd);
    setBoard(p2_board, p2_cv, p2_bb, p2_cl, p2_dd);

    initscr();
    while(victory != true){
        char x='k', y='k';

        if(player%2 != 0){
            player = 1;

            do{
                atk_error = 0;

                clear();
                drawEnemyBoard(p2_board, p2_fleet_status);
                printw("=============================\n\n");
                drawMyBoard(p1_board, p1_fleet_status);

                printw("<-----Turno del Jugador %i----->\n\n", player);
                printw("Fila: "); refresh();
                y = getch();
                printw("\nColumna: "); refresh();
                x = getch();
                sleep(0.5);

                atk_error = attack(x, y, p2_board, p2_cv, p2_bb, p2_cl, p2_dd, p2_fleet_status);

            }while(!(atk_error==0));

            char aux[2] = {y,x};
            char *msg = aux;
            send(sock, msg, strlen(msg), 0);

            victory = checkwin(player, p1_board, p2_board, p2_fleet_status, p1_fleet_status, p2_fleet_status);
        }
        else{
            player = 2;
            
            clear();
            drawEnemyBoard(p2_board, p2_fleet_status);
            printw("=============================\n\n");
            drawMyBoard(p1_board, p1_fleet_status);

            printw("<-----Turno del Jugador %i----->\n\n", player);
            printw("Esperando al Jugador %i ...\n", player);
            refresh();

            char buffer[2] = {0};
            valread = read(sock, buffer, 2);
            y = buffer[0];
            x = buffer[1];

            attack(x, y, p1_board, p1_cv, p1_bb, p1_cl, p1_dd, p1_fleet_status);

            victory = checkwin(player, p1_board, p2_board, p1_fleet_status, p1_fleet_status, p2_fleet_status);
        }

        player++;
    }
    getch();
    endwin();
    return 0;
}

void drawMyBoard(char board[10][10], bool status[10]){
    char l = 'A';
    
    for(int i=0; i<2; i++){
        for (int j=0; j<12; j++){
            if(j==0){
                if(i==0) printw("   ");
                else printw("___");
            }
            else if (j<11){
                if(i==0){
                    printw ("%c ", l);
                    l++;
                }
                else printw("__");
            }
            else
                if(i==1) printw("_");
            
        }
        printw("\n");
    }
    
    for(int i=0; i<10; i++){
        for(int j=0; j<12; j++){
            
            if(j==0)
                printw("%i| ", i);

            else if(j<11)
                printw("%c ", board[i][j-1]);
            
            else 
                printw("|");
            
        }
        printw ("\n");
    }
    for(int i=1; i<25; i++) printw("_");
    printw("\n\n");
    printw("Portaviones: %i | Acorazados: %i\n", status[0], status[1]+status[2]);
    printw("Cruseros: %i | Destructores: %i\n\n", status[3]+status[4]+status[5], status[6]+status[7]+status[8]+status[9]);
}

void drawEnemyBoard(char board[10][10], bool status[10]){
    char l = 'A';
    
    for(int i=0; i<2; i++){
        for (int j=0; j<12; j++){
            if(j==0){
                if(i==0) printw("   ");
                else printw("___");
            }
            else if (j<11){
                if(i==0){
                    printw("%c ", l);
                    l++;
                }
                else printw("__");
            }
            else
                if(i==1) printw("_");
            
        }
        printw("\n");
    }
    
    for(int i=0; i<10; i++){
        for(int j=0; j<12; j++){
            
            if(j==0)
                printw("%i| ", i);

            else if(j<11){
                if(board[i][j-1] == '#')
                    printw(" ");
                else printw("%c", board[i][j-1]);
                printw(" ");
            }
            
            else printw("|");
            
        }
        printw("\n");
    }
    for(int i=1; i<25; i++) printw("_");
    printw("\n\n");
    printw("Portaviones: %i | Acorazados: %i\n", status[0], status[1]+status[2]);
    printw("Cruseros: %i | Destructores: %i\n\n", status[3]+status[4]+status[5], status[6]+status[7]+status[8]+status[9]);
}

void setBoard(char board[10][10], char cv[1][4][3], char bb[2][3][3], char cl[3][2][3], char dd[4][1][3])
{
    int i, j;
    for(int b = 0 ; b < 1; b++){            
        for(int c = 0; c < 4; c++){
            i = cv[b][c][0]-48;
            j = cv[b][c][1]-48;
            board[i][j] = cv[b][c][2];  
        }
    }

    for(int b = 0 ; b < 2; b++){            
        for(int c = 0; c < 3; c++){
            i = bb[b][c][0]-48;
            j = bb[b][c][1]-48;
            board[i][j] = bb[b][c][2];
        }
    }

    for(int b = 0 ; b < 3; b++){            
        for(int c = 0; c < 2; c++){
            i = cl[b][c][0]-48;
            j = cl[b][c][1]-48;
            board[i][j] = cl[b][c][2];
        }
    }
    
    for(int b = 0 ; b < 4; b++){            
        for(int c = 0; c < 1; c++){
            i = dd[b][c][0]-48;
            j = dd[b][c][1]-48;
            board[i][j] = dd[b][c][2];
        }
    }
}

int attack(char x, char y, char board[10][10], char cv[1][4][3], char bb[2][3][3], char cl[3][2][3], char dd[4][1][3], bool status[10]){
    if(y >= '0' && y <= '9' && x >= 'a' && x <= 'j'){
        x += -49;
        char i, j;
        int status_c = 0, hit_c;
        bool hit = 0;

        // i = y = fila 
        // j = x = columna

        if(board[y-48][x-48]==' '){
            board[y-48][x-48] = '.';
            return 0;
        }
        else if(board[y-48][x-48] == '#'){

            for(int b = 0 ; b < 1; b++){
                hit_c = 0;
                for(int d = 0; d<3; d++){    
                    for(int c = 0; c < 4; c++){

                        if (d == 0 && cv[b][c][2] == 'X')
                            break;  

                        i = cv[b][c][0]-48;
                        j = cv[b][c][1]-48;

                        if(d == 0 && x == cv[b][c][1] && y == cv[b][c][0]){
                            hit = 1;
                            board[y-48][x-48] = '@';
                            cv[b][c][2] = '@';
                            break;
                        }
                        if(d == 1 && cv[b][c][2] == '@') 
                            hit_c++;

                        if(d == 2){
                            board[i][j] = 'X';
                            cv[b][c][2] = 'X';
                        }

                    }

                    if(hit == 0)                break;
                    if(d == 1 && hit_c == 4)    status[status_c] = 0;
                    if(d == 1 && hit_c != 4)    break;
                }
                status_c++;
            }

            for(int b = 0 ; b < 2; b++){  
                hit_c = 0;
                for(int d = 0; d<3; d++){  
                    for(int c = 0; c < 3; c++){

                        if (d == 0 && bb[b][c][2] == 'X')
                            break;  

                        i = bb[b][c][0]-48;
                        j = bb[b][c][1]-48;

                        if(d == 0 && x == bb[b][c][1] && y == bb[b][c][0]){
                            hit = 1;
                            board[y-48][x-48] = '@';
                            bb[b][c][2] = '@';
                            break;
                        }
                        if(d == 1 && bb[b][c][2] == '@') 
                            hit_c++;

                        if(d == 2){
                            board[i][j] = 'X';
                            bb[b][c][2] = 'X';
                        }

                    }

                    if(hit == 0)                break;
                    if(d == 1 && hit_c == 3)    status[status_c] = 0;
                    if(d == 1 && hit_c != 3)    break;
                }
                status_c++;               
            }

            for(int b = 0 ; b < 3; b++){
                hit_c = 0;
                for(int d = 0; d<3; d++){              
                    for(int c = 0; c < 2; c++){
            
                        if (d == 0 && cl[b][c][2] == 'X')
                            break;  

                        i = cl[b][c][0]-48;
                        j = cl[b][c][1]-48;

                        if(d == 0 && x == cl[b][c][1] && y == cl[b][c][0]){
                            hit = 1;
                            board[y-48][x-48] = '@';
                            cl[b][c][2] = '@';
                            break;
                        }
                        if(d == 1 && cl[b][c][2] == '@') 
                            hit_c++;

                        if(d == 2){
                            board[i][j] = 'X';
                            cl[b][c][2] = 'X';
                        }

                    }

                    if(hit == 0)                break;
                    if(d == 1 && hit_c == 2)    status[status_c] = 0;
                    if(d == 1 && hit_c != 2)    break;
                }
                status_c++; 
            }
            
            for(int b = 0 ; b < 4; b++){  
                hit_c = 0;
                for(int d = 0; d<3; d++){  
                    for(int c = 0; c < 1; c++){

                        if (d == 0 && dd[b][c][2] == 'X')
                            break;  

                        i = dd[b][c][0]-48;
                        j = dd[b][c][1]-48;

                        if(d == 0 && x == dd[b][c][1] && y == dd[b][c][0]){
                            hit = 1;
                            board[y-48][x-48] = '@';
                            dd[b][c][2] = '@';
                            break;
                        }
                        if(d == 1 && dd[b][c][2] == '@') 
                            hit_c++;

                        if(d == 2){
                            board[i][j] = 'X';
                            dd[b][c][2] = 'X';
                        }

                    }

                    if(hit == 0)                break;
                    if(d == 1 && hit_c == 1)    status[status_c] = 0;
                    if(d == 1 && hit_c != 1)    break;
                }
                status_c++; 
            }
            return 0;
        }
    }
    return -1;    
}

bool checkwin(int pnum, char myBoard[10][10], char enBoard[10][10], bool curStatus[10], bool myStatus[10], bool enStatus[10]){
    int status_sum=0, aux;
    
    for(int i = 0; i < 10; i++){
        status_sum += int(curStatus[i]);
    }

    if(status_sum < 1){
        clear();
        drawMyBoard(enBoard, enStatus);
        printw("========Jugador %i Gana=======\n\n", pnum);
        drawMyBoard(myBoard, myStatus);
        refresh();
        return 1;
    }
    else
        return 0;
}