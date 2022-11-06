#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/* #include <curses.h>
#include <ncurses.h> */

using namespace std;

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

char p2_cv [1][4][3] = {
    {{'3','3','#'},{'4','3','#'},{'5','3','#'},{'6','3','#'}}
};
char p2_bb [2][3][3] = {
    {{'5','9','#'},{'6','9','#'},{'7','9','#'}},
    {{'9','0','#'},{'9','1','#'},{'9','2','#'}}
};
char p2_cl [3][2][3] = {
    {{'4','0','#'},{'4','1','#'}},
    {{'6','5','#'},{'6','6','#'}},
    {{'8','7','#'},{'9','7','#'}}
};
char p2_dd [4][1][3] = {
    {{'0','0','#'}},
    {{'0','9','#'}},
    {{'3','6','#'}},
    {{'6','1','#'}}
};

bool p2_fleet_status[10] = {1,1,1,1,1,1,1,1,1,1};

bool victory = false;

void drawMyBoard(char [10][10], bool [10]);
void drawEnemyBoard(char [10][10], bool [10]);

void setMyBoard(char [10][10]);
void setBoard(char [10][10], char [1][4][3], char [2][3][3], char [3][2][3], char [4][1][3]);

void attack(char, char, char [10][10], char [1][4][3], char [2][3][3], char [3][2][3], char [4][1][3], bool [10]);

int main()
{   
    int player = 1, dummy;

    system("clear");
    setMyBoard(p1_board);
    setBoard(p2_board, p2_cv, p2_bb, p2_cl, p2_dd);
    
    while(victory != true){
        system("clear");
        char x='k', y='k';

        if(player%2 != 0){
            player = 1;

            while(!(y >= '0' && y <= '9' && x >= 'a' && x <= 'j')){
                drawEnemyBoard(p2_board, p2_fleet_status);
                cout << "=============================" << endl << endl;
                drawMyBoard(p1_board, p1_fleet_status);
                cout << "<-----Turno del Jugador " << player << "----->" << endl << endl;
                cout << "Fila: "; cin >> y;
                cout << "Columna: "; cin >> x;
            }

            attack(x, y, p2_board, p2_cv, p2_bb, p2_cl, p2_dd, p2_fleet_status);
        }
        else{
            player = 2;
            
            while(!(y >= '0' && y <= '9' && x >= 'a' && x <= 'j')){
                drawEnemyBoard(p1_board, p1_fleet_status);
                cout << "=============================" << endl << endl;
                drawMyBoard(p2_board, p2_fleet_status);
                cout << "<-----Turno del Jugador " << player << "----->" << endl << endl;
                cout << "Fila: "; cin >> y;
                cout << "Columna: "; cin >> x;

                
            }

            attack(x, y, p1_board, p1_cv, p1_bb, p1_cl, p1_dd, p1_fleet_status);
        }
        player++;
    }
    return 0;
}


void drawMyBoard(char board[10][10], bool status[10]){
    char l = 'A';
    
    for(int i=0; i<2; i++){
        for (int j=0; j<12; j++){
            if(j==0){
                if(i==0) cout << "   ";
                else cout << "___";
            }
            else if (j<11){
                if(i==0){
                    cout << l << " ";
                    l++;
                }
                else cout << "__";
            }
            else
                if(i==1) cout << "_";
            
        }
        cout << endl;
    }
    
    for(int i=0; i<10; i++){
        for(int j=0; j<12; j++){
            
            if(j==0){
                cout << i;
                cout << "| ";
            }

            else if(j<11){
                cout << board[i][j-1] << " ";
            }
            
            else cout << "|";
            
        }
        cout << endl;
    }
    for(int i=1; i<25; i++) cout << "_";
    cout << endl << endl;
    cout << "Portavones: " << status[0] << " | Acorazados: " << status[1]+status[2] << endl;
    cout << "Curseros: " << status[3]+status[4]+status[5] << " | Destructores: " << status[6]+status[7]+status[8]+status[9] << endl << endl;
}

void drawEnemyBoard(char board[10][10], bool status[10]){
    char l = 'A';
    
    for(int i=0; i<2; i++){
        for (int j=0; j<12; j++){
            if(j==0){
                if(i==0) cout << "   ";
                else cout << "___";
            }
            else if (j<11){
                if(i==0){
                    cout << l << " ";
                    l++;
                }
                else cout << "__";
            }
            else
                if(i==1) cout << "_";
            
        }
        cout << endl;
    }
    
    for(int i=0; i<10; i++){
        for(int j=0; j<12; j++){
            
            if(j==0){
                cout << i;
                cout << "| ";
            }

            else if(j<11){
                if(board[i][j-1] == '#')
                    cout << " ";
                else cout << board[i][j-1];
                cout << " ";
            }
            
            else cout << "|";
            
        }
        cout << endl;
    }
    for(int i=1; i<25; i++) cout << "_";
    cout << endl << endl;
    cout << "Portavones: " << status[0] << " | Acorazados: " << status[1]+status[2] << endl;
    cout << "Curseros: " << status[3]+status[4]+status[5] << " | Destructores: " << status[6]+status[7]+status[8]+status[9] << endl << endl;
}

void setMyBoard(char board[10][10]){
    int i, j;
    bool ready = false;
    char input;

    for(int b = 0 ; b < 1; b++){            
        for(int c = 0; c < 4; c++){
            i = p1_cv[b][c][0]-48;
            j = p1_cv[b][c][1]-48;
            board[i][j] = p1_cv[b][c][2];
        }
    }

    for(int b = 0 ; b < 2; b++){            
        for(int c = 0; c < 3; c++){
            i = p1_bb[b][c][0]-48;
            j = p1_bb[b][c][1]-48;
            board[i][j] = p1_bb[b][c][2];
        }
    }

    for(int b = 0 ; b < 3; b++){            
        for(int c = 0; c < 2; c++){
            i = p1_cl[b][c][0]-48;
            j = p1_cl[b][c][1]-48;
            board[i][j] = p1_cl[b][c][2];
        }
    }
    
    for(int b = 0 ; b < 2; b++){            
        for(int c = 0; c < 3; c++){
            i = p1_dd[b][c][0]-48;
            j = p1_dd[b][c][1]-48;
            board[i][j] = p1_dd[b][c][2];
        }
    }
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
    
    for(int b = 0 ; b < 2; b++){            
        for(int c = 0; c < 3; c++){
            i = dd[b][c][0]-48;
            j = dd[b][c][1]-48;
            board[i][j] = dd[b][c][2];
        }
    }
}

void attack(char x, char y, char board[10][10], char cv[1][4][3], char bb[2][3][3], char cl[3][2][3], char dd[4][1][3], bool status[10]){
    board[y-48][x-97] = '.';
}
