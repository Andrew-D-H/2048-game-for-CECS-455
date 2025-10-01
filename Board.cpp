#include "Board.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <vector>

using namespace std;

Board::Board(int size) : size_(size), grid_(size, vector<int>(size, 0)) {}

//prints the board
void Board::print() const {
    cout << "+------------------------+" << endl;
    for (int i = 0; i < size_; ++i) {
        cout << "|";
        for (int j = 0; j < size_; ++j) {
            if (grid_[i][j] == 0)
                cout << setw(5) << ".";
            else
                cout << setw(5) << grid_[i][j];
        }
        cout << " |" << endl;
    }
    cout << "+------------------------+" << endl;
}

void Board::setTile(int row, int col, int value){
    grid_[row][col] = value;
}

int Board::getTile(int row, int col) const {
    return grid_[row][col];
}

//randomly place tiles with the given seed
void Board::printRandomTiles(int count, int seed) {
    mt19937 rng(seed);
    uniform_int_distribution<int> dist(0, size_ - 1);

    //place 2's while avoiding double placement on the same tile
    int placed = 0;
    while (placed < count) {
        int row = dist(rng);
        int col = dist(rng);
        if (grid_[row][col] == 0) { 
            grid_[row][col] = 2;
            placed++;
        }
    }
}