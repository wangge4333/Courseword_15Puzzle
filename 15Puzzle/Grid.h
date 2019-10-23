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
	

	//void initialize_direct();

	string hash = "";

	int blank_x_pos = 0;
	int blank_y_pos = 0;

public:
	Grid(vector<int> grids_value, int ini_length);
	Grid(int ini_length);
	Grid();

	int get_length() { return length; };
	void set_length(int ini_length) { length = ini_length; };

	void set_value(vector<int> grids_value);
	void set_value(Grid n_grid);

	string get_hash() { return hash; };
	int get_blank_x() { return blank_x_pos; };
	int get_blank_y() { return blank_y_pos; };

	Block* get_blank_one() { return &all_grid[blank_y_pos][blank_x_pos]; };
	int get_one_value(int y, int x) { return all_grid[y][x].get_number(); };

	//Grid operator=(Grid n_grid);

	//Grid(Block* blocks, int length);
	~Grid() {};

	//Others
	void show_grid();
	string get_grid();
	void compute_hash();
	bool if_pt_bottom_right();

	bool if_north_valid() { return blank_y_pos > 0; };
	bool if_south_valid() { return blank_y_pos < length - 1; };
	bool if_west_valid() { return blank_x_pos > 0; };
	bool if_east_valid() { return blank_x_pos < length - 1; };

	void move_north();
	void move_east();
	void move_south();
	void move_west();

	Grid move_north_bfs();
	Grid move_east_bfs();
	Grid move_south_bfs();
	Grid move_west_bfs();

};

