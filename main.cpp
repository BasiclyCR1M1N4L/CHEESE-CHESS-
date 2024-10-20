#include <iostream>
#include <string>
#include  "chess.h"

using namespace std;

int main() {
    Board b;
    string s;
    bool newGame = true;
    cout <<  "Enter any key to start a new game" << endl;
    cin >> s;
    while (newGame){
        b.setBoard();
        while(b.playGame());
        cout << "Enter y to play again"  <<  endl;
        if(s!="y"){
            newGame = false;
        }
    }
} 
