#include <iostream>
using namespace std;

void clearBoard(char board[3][3]){
    for (int x = 0; x < 3; x++)
        for (int y =0; y <3; y++)
        board[x][y] = ' ';
}

void showBoard(char board[3][3]){
    for (int x = 0; x < 3; x++){
        for (int y =0; y <3; y++){
            
            if (y == 1){
                cout << " | ";
            }
            cout << board[x][y];
            if (y== 1) {
            cout <<"  |  " ;
           }
        }
        if (x < 2){
        cout << "\n---------\n";
        }
    }

}

bool setPoint(char board[3][3], unsigned int x, unsigned int y, char player){
    
    if (board[x][y] == ' '){
        board[x][y] = player;
        return true;
    }
    return false;
}

char isFinished(char board[3][3]){
    char player;
    player = 'X';

    for (int i = 0; i<2; i++)
    {

        if (board[0][0]==player && board[0][1]==player && board[0][2]==player) {
        cout << "Wygrywa: " << player << endl;
            return 0;
        }
        if (board[1][0]==player && board[1][1]==player && board[1][2]==player) {
            cout << "Wygrywa: " << player << endl;
            return 0;
        }
        if (board[2][0]==player && board[2][1]==player && board[2][2]==player) {
            cout << "Wygrywa: " << player << endl;
            return 0;
        }
        if (board[0][0]==player && board[1][0]==player && board[2][0]==player) {
            cout << "Wygrywa: " << player << endl;
            return 0;
        }
        if (board[0][1]==player && board[1][1]==player && board[2][1]==player) {
            cout << "Wygrywa: " << player << endl;
            return 0;
        }
        if (board[0][2]==player && board[1][2]==player && board[2][2]==player) {
            cout << "Wygrywa: " << player << endl;
            return 0;
        }
        if (board[0][0]==player && board[1][1]==player && board[2][2]==player) {
            cout << "Wygrywa: " << player << endl;
            return 0;
        }
        if (board[0][2]==player && board[1][1]==player && board[2][0]==player) {
            cout << "Wygrywa: " << player << endl;
            return 0;
        }
        player ='O';
    }

    bool remis = true;
    for (int x = 0; x < 3; x++) {
        for (int y =0; y <3; y++) {
            if (board[x][y] == ' ')
            {
                remis = false;
            }
        }
    }

    if (remis){
        cout << "Remis" << endl;
        
    }
    return ' ';
}
int main(){
    char board[3][3];
    clearBoard(board);
    char player = 'X';
    while (isFinished(board)) {
        int x;
        int y;
        
        do {
            showBoard(board);
            cout << "   Kolej na " << player << endl;;
            cout << " Podaj wspolrzedne np. 0 1 ";
            cin >> x >> y; 
        }while(!setPoint(board, x, y, player));
        
        if (player == 'X')
            player = 'O';
        else
            player = 'X';
    }

    return 0;

}