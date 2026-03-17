#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void clearBoard(char** board, int size){
    for (int x = 0; x < size; x++)
        for (int y =0; y <size; y++)
        board[x][y] = ' ';
}

void showBoard(char** board, int size){
    for (int x = 0; x < size; x++){
        for (int y =0; y <size; y++){
            cout << board[x][y];
            if (y < size -1 ){
                cout << " | ";
            }
            
        }
        if (x < size - 1){
            cout << "\n";
            for (int i = 0; i < size * 3; i++)
            cout << "-";
            cout << "\n"; 
        }
    }

}

bool setPoint(char** board, int size, unsigned int x, unsigned int y, char player){
    if (x >= (unsigned)size || y >= (unsigned)size) return false;
    if (board[x][y] == ' ') {
        board[x][y] = player;
        return true;
    }
    return false;
}

bool checkWin(char** board, int size, char player){
    for (int i = 0; i < size; i++) {
        bool rowWin = true, colWin = true; // na poczatku zakladamy ze wygral ktos
        for (int j = 0; j < size; j++) {
            if (board[i][j] != player) rowWin = false;
            if (board[j][i] != player) colWin = false;
        }
        if (rowWin || colWin) return true; // jezeli gdzies wszystkie wiersze lub kolumny sa jednego znaku to mamy zwyciesce 
    }
    
    bool przekatna1 = true, przekatna2 = true;
    for (int i = 0; i < size; i++) {
        if (board[i][i] != player) przekatna1 = false;
        if (board[i][size - 1 - i] != player) przekatna2 = false;
    }
    return przekatna1 || przekatna2;
}

char isFinished(char** board, int size){
    for (char player : {'X', 'O'}) {
        if (checkWin(board, size, player)) {
            cout << "Wygrywa: " << player << endl;
            showBoard(board, size);
            return 0;
        }
    }
    bool remis = true;

    for (int x = 0; x < size; x++)
        for (int y = 0; y < size; y++)
            if (board[x][y] == ' ')
            {
                remis = false;
            }

    if (remis){
        cout << "Remis" << endl;
        showBoard(board, size);
        return 0;
    }
    return ' ';
    }

void aiOpponent(char** board, int size){
    int a, b;
    do {
        a = rand() % size;
        b = rand() % size;
    } while (board[a][b]!= ' ');

    board[a][b] = 'O';
    } 
    
 

int main(){
    srand(time(NULL));
    cout << "Wybierz tryb gry (1) gracz na gracza (2) gracz na komputer: ";
    int tryb; cin >> tryb;
    cin.ignore(); 
    int size;
    char** board = nullptr;

    if (tryb == 1){
    cout << "Podaj rozmiar planszy 2-2x2, 3-3x3..."; cin >> size;

    char** board = new char*[size];
        for (int i = 0; i < size; i++){
            board[i] = new char[size];
        }

    clearBoard(board, size);
    char player = 'X';

    while (isFinished(board, size)) {
        int x;
        int y;
        
        do {
            showBoard(board, size);
            cout << "   Kolej na " << player << endl;;
            cout << " Podaj wspolrzedne np. 0 1 ";
            cin >> x >> y; 
        }while(!setPoint(board, size, x, y, player));
        
        if (player == 'X')
            player = 'O';
        else
            player = 'X';
    }
}
    if (tryb == 2){
        cout << "Podaj rozmiar planszy 2-2x2, 3-3x3..."; cin >> size;

        board = new char*[size];
        for (int i = 0; i < size; i++){
            board[i] = new char[size];
        }

    clearBoard(board, size);
    char player = 'X';

    while (isFinished(board, size))
    {
        int x;
        int y;
        if (player == 'X'){
            do {
                showBoard(board, size);
                cout << "   Kolej na " << 'X' << endl;
                cout << " Podaj wspolrzedne np. 0 1 ";
                cin >> x >> y; 
                }while(!setPoint(board, size, x, y, player));
    }
        if (player == 'X')
            player = 'O';

        if (player == 'O'){
            
                aiOpponent(board, size);
            
            player = 'X';
        }

    }
    }
    


    for (int i = 0; i < size; i++){
        delete[] board[i]; 
    }
    delete[] board;
    return 0;

    }
