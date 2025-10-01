#include "Board.h"
#include <iostream>
#include <random>
#include <vector>
#include <cctype>

using namespace std;

int main(int argc, char* argv[]){
	
	//seed for random number generator
    int seed;
	
	//if a command line is provided, use the number provided as a seed
    if(argc > 1){
        seed = static_cast<int>(stoul(argv[1]));
        cout << "Using seed: " << seed << endl;
    } 
	
	//default to randomly generated seed
	else{
        seed = random_device{}();
        cout << "Using random seed: " << seed << endl;
    }

	// print a board with randomly placed 2s
    Board board(4);
    board.printRandomTiles(2, seed);
	
	//game loop activates
    while(true){
        board.print();
        cout << "Use w/a/s/d to slide (up/left/down/right), q to quit: ";
        char move;
        cin >> move;
		move = tolower(move);
        if (move == 'q') break;
        if (move == 'a') board.slideLeft();
        else if (move == 'd') board.slideRight();
        else if (move == 'w') board.slideUp();
        else if (move == 's') board.slideDown();
        else cout << "Invalid input!\n";
    }
    cout << "Game over!\n";	
	
    return 0;
}