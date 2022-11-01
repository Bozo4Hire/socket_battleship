#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

char p1_board [11][11] = {
    {'o','o','o','o','o','o','o','o','o','o','o'},
    {'|','b','b','b','b','b','b','b','b','b','b'},
    {'|','b','b','b','b','b','b','b','b','b','b'},
    {'|','b','b','b','b','b','b','b','b','b','b'},
    {'|','b','b','b','b','b','b','b','b','b','b'},
    {'|','b','b','b','b','b','b','b','b','b','b'},
    {'|','b','b','b','b','b','b','b','b','b','b'},
    {'|','b','b','b','b','b','b','b','b','b','b'},
    {'|','b','b','b','b','b','b','b','b','b','b'},
    {'|','b','b','b','b','b','b','b','b','b','b'},
    {'|','b','b','b','b','b','b','b','b','b','b'}
};
char p2_board [11][11] = {
    {'o','o','o','o','o','o','o','o','o','o','o'},
    {'|','b','b','b','b','b','b','b','b','b','b'},
    {'|','b','b','b','b','b','b','b','b','b','b'},
    {'|','b','b','b','b','b','b','b','b','b','b'},
    {'|','b','b','b','b','b','b','b','b','b','b'},
    {'|','b','b','b','b','b','b','b','b','b','b'},
    {'|','b','b','b','b','b','b','b','b','b','b'},
    {'|','b','b','b','b','b','b','b','b','b','b'},
    {'|','b','b','b','b','b','b','b','b','b','b'},
    {'|','b','b','b','b','b','b','b','b','b','b'},
    {'|','b','b','b','b','b','b','b','b','b','b'}
};

void drawMyBoard(char [11][11]);

int main()
{   
    drawMyBoard(p2_board);

    return 0;
}


void drawMyBoard(char board[11][11]){
    char l = 'A';
    
    for(int i=0; i<2; i++){
        for (int j=0; j<10; j++){
            
            if(i==0){
                cout << l << " ";
                l++;
            }
            else cout << "--";
            
        }
        cout << endl;
    }
    
    for(int i=1; i<11; i++){
        for(int j=0; j<11; j++){
            
            cout << board[i][j] << " ";
            
            //if else 
            
        }
        cout << endl;
    }
}