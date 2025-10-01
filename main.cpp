#include "Board.h"
#include <iostream>
#include <random>
#include <vector>

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
    board.print();
	
	
    return 0;
}