#include "Board.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <cstdlib> 
#include <ctime>   

using namespace std;

Board::Board(int size) : size_(size), grid_(size, vector<int>(size, 0)) {}

//prints the board
void Board::print() const {
	cout << "Score: " << score << endl;
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
vector<int> slideAndCombine(const vector<int>& line, int& score) {
    vector<int> result;
    int prev = 0;
    for (int num : line) {
        if(num == 0)
			continue;
        if(prev == 0){
            prev = num;
        }
		else if(prev == num) {
			int comb = prev * 2;
			result.push_back(comb);
			score += comb;
            prev = 0;
        }
		else{
            result.push_back(prev);
            prev = num;
        }
    }
    if (prev != 0) 
		result.push_back(prev);
    while(result.size() < line.size()) 
		result.push_back(0);
    return result;
}

// Slide all rows left
bool Board::slideLeft() {
    bool moved = false;
    for(int i = 0; i < size_; ++i){
        vector<int> old = grid_[i];
        grid_[i] = slideAndCombine(grid_[i], score);
        if(grid_[i] != old) 
			moved = true;
    }
    return moved;
}


// Slide all rows right
bool Board::slideRight() {
    bool moved = false;
    for(int i = 0; i < size_; ++i){
        vector<int> old = grid_[i];
        vector<int> reversed(old.rbegin(), old.rend());
        reversed = slideAndCombine(reversed, score);
        vector<int> newVar(reversed.rbegin(), reversed.rend());
        grid_[i] = newVar;
        if(grid_[i] != old) 
			moved = true;
    }
    return moved;
}

// Slide all columns up
bool Board::slideUp() {
	bool moved = false;
    for(int j = 0; j < size_; ++j) {
        vector<int> col, old;
        for(int i = 0; i < size_; ++i){
            col.push_back(grid_[i][j]);
            old.push_back(grid_[i][j]);
        }
        col = slideAndCombine(col, score);
        for(int i = 0; i < size_; ++i) 
			grid_[i][j] = col[i];
        if(col != old) 
			moved = true;
    }
    return moved;
}

// Slide all columns down
bool Board::slideDown() {
    bool moved = false;
    for(int j = 0; j < size_; ++j) {
        vector<int> col, old;
        for(int i = size_ - 1; i >= 0; --i) {
            col.push_back(grid_[i][j]);
            old.push_back(grid_[i][j]);
        }
        col = slideAndCombine(col, score);
        for(int i = size_ - 1, k = 0; i >= 0; --i, ++k) 
			grid_[i][j] = col[k];
        vector<int> newVar;
        for(int i = size_ - 1; i >= 0; --i) 
			newVar.push_back(grid_[i][j]);
        if(newVar != old) 
			moved = true;
    }
    return moved;
}


//spawn tile
void Board::spawnTile(int seed) {
    // Seed the random number generator
    srand(seed);

    // Find all empty squares
    vector<pair<int, int>> empty;
    for (int i = 0; i < size_; ++i)
        for (int j = 0; j < size_; ++j)
            if (grid_[i][j] == 0)
                empty.push_back({i, j});
    if (empty.empty()) return; // No empty square, do nothing

    // Pick a random empty square
    int idx = rand() % empty.size();

    // 90% chance for 2, 10% for 4
    int tileValue = 2;
    if (rand() % 10 == 0)
        tileValue = 4;

    auto [row, col] = empty[idx];
    grid_[row][col] = tileValue;
}

int Board::getScore() const {
    return score;
}

bool Board::isGameOver() const {
    Board temp = *this;
    if (temp.slideLeft()) 
		return false;
    temp = *this;
    if (temp.slideRight()) 
		return false;
    temp = *this;
    if (temp.slideUp()) 
		return false;
    temp = *this;
    if (temp.slideDown()) 
		return false;
    return true;
}