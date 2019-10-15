#include "Grid.h"

Grid::Grid(vector<int> grids_value):blank_one(nullptr) {
	all_grid = new Block * [length];
	for (int i = 0; i < length; i++)
		all_grid[i] = new Block[length];

	grids_value.push_back(0);

	set_value(grids_value);

	initialize_direct();
}

Grid::Grid() :blank_one(nullptr) {
	all_grid = new Block * [length];
	for (int i = 0; i < length; i++) {
		all_grid[i] = new Block[length];
		all_grid[i]->set_number(0);
	}
}

void Grid::set_value(vector<int> grids_value) {
	grids_value.push_back(0);

	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			all_grid[i][j].set_number(grids_value[i * 4 + j]);
			if (all_grid[i][j].get_number() == 0)
				blank_one = &all_grid[i][j];
		}
	}

}

void Grid::initialize_direct() {
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++)
		{
			if (i > 0)
				all_grid[i][j].set_west_block(&all_grid[i - 1][j]);
			if (i < length - 1)
				all_grid[i][j].set_east_block(&all_grid[i + 1][j]);
			if (j > 0)
				all_grid[i][j].set_north_block(&all_grid[i][j - 1]);
			if (j < length - 1)
				all_grid[i][j].set_south_block(&all_grid[i][j + 1]);
		}
	}
}

void Grid::show_grid() {
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
			cout << all_grid[i][j].get_number() << ' ';
		cout << endl;
	}
	cout << endl;
}