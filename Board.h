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
		void slideLeft();
		void slideRight();
		void slideUp();
		void slideDown();

	private:
		int size_;
		vector<vector<int>> grid_;
};