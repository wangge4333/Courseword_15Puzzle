#pragma once
#include "Block.h"
#include <vector>
#include <iostream>

using namespace std;

class Grid
{
protected:
	int length = 4;
	Block** all_grid;
	Block* blank_one = nullptr;

	void initialize_direct();

public:
	Grid(vector<int> grids_value);
	Grid();
	void set_value(vector<int> grids_value);

	//Grid(Block* blocks, int length);
	~Grid() {};

	//Others
	void show_grid();

};

