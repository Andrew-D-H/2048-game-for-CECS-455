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

//helper method for the slides
vector<int> slideAndCombine(const vector<int>& line) {
    vector<int> result;
    int prev = 0;
    for (int num : line) {
        if (num == 0) continue;
        if (prev == 0) {
            prev = num;
        } else if (prev == num) {
            result.push_back(prev * 2);
            prev = 0;
        } else {
            result.push_back(prev);
            prev = num;
        }
    }
    if (prev != 0) result.push_back(prev);
    while (result.size() < line.size()) result.push_back(0);
    return result;
}

// Slide all rows left
void Board::slideLeft() {
    for (int i = 0; i < size_; ++i) {
        grid_[i] = slideAndCombine(grid_[i]);
    }
}

// Slide all rows right
void Board::slideRight() {
    for (int i = 0; i < size_; ++i) {
        vector<int> reversed(grid_[i].rbegin(), grid_[i].rend());
        reversed = slideAndCombine(reversed);
        grid_[i] = vector<int>(reversed.rbegin(), reversed.rend());
    }
}

// Slide all columns up
void Board::slideUp() {
    for (int j = 0; j < size_; ++j) {
        vector<int> col;
        for (int i = 0; i < size_; ++i) col.push_back(grid_[i][j]);
        col = slideAndCombine(col);
        for (int i = 0; i < size_; ++i) grid_[i][j] = col[i];
    }
}

// Slide all columns down
void Board::slideDown() {
    for (int j = 0; j < size_; ++j) {
        vector<int> col;
        for (int i = size_ - 1; i >= 0; --i) col.push_back(grid_[i][j]);
        col = slideAndCombine(col);
        for (int i = size_ - 1, k = 0; i >= 0; --i, ++k) grid_[i][j] = col[k];
    }
}