#pragma once
#include <vector>

using namespace std;

class Board {
	
	public:
		Board(int size = 4);
		void print() const;
		void setTile(int row, int col, int value);
		int getTile(int row, int col) const;
		void printRandomTiles(int count, int seed);
		bool slideLeft();
		bool slideRight();
		bool slideUp();
		bool slideDown();
		void spawnTile(int seed);
		int getScore() const;
		bool isGameOver() const;

	private:
		int size_;
		vector<vector<int>> grid_;
		int score = 0;
};
