#include "Grid.h"

Grid::Grid(vector<int> grids_value, int ini_length) {
	length = ini_length;
	all_grid = new Block * [length];
	for (int i = 0; i < length; i++)
		all_grid[i] = new Block[length];

	grids_value.push_back(0);

	set_value(grids_value);

	//initialize_direct();
}

Grid::Grid(int ini_length):hash(0),length(ini_length) {

	all_grid = new Block * [length];
	for (int i = 0; i < length; i++) {
		all_grid[i] = new Block[length];
		all_grid[i]->set_number(0);
	}
}

Grid::Grid():hash(0) {

	length = 3;

	all_grid = new Block * [length];
	for (int i = 0; i < length; i++) {
		all_grid[i] = new Block[length];
		all_grid[i]->set_number(0);
	}

	//initialize_direct();
}

void Grid::set_value(vector<int> grids_value) {
	grids_value.push_back(0);

	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			all_grid[i][j].set_number(grids_value[i * length + j]);
			if (all_grid[i][j].get_number() == 0) {
				blank_y_pos = i;
				blank_x_pos = j;
			}
		}
	}

	compute_hash();

}

void Grid::set_value(Grid n_grid) {

	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			all_grid[i][j].set_number(n_grid.get_one_value(i, j));
			if (all_grid[i][j].get_number() == 0) {
				blank_y_pos = i;
				blank_x_pos = j;
			}
		}
	}

	compute_hash();
}

void Grid::compute_hash() {
	/*long long tempH = 0, tempV = 0;
	long long tl_br = 0, tr_bl = 0;
	for (int i = 0; i < length - 1; i++) {
		tempH = tempH * 100;
		tempV = tempV * 100;
		for (int j = 0; j < length; j++) {
			tempH = tempH + (long long)all_grid[i][j].get_number();
			tempV = tempV + (long long)all_grid[j][i].get_number();
		}
		tl_br += all_grid[i][i].get_number();
		tr_bl += all_grid[i][length - 1 - i].get_number();

	}
	hash = tempH * 10000000000 + tempV * 10000 + tl_br * 100 + tr_bl;*/

	long long temp = 0;
	for (int i = 0; i < length; i++) {

		for (int j = 0; j < length; j++) {
			temp = temp * 100 + (long long)all_grid[i][j].get_number();
		}
	}
	hash = temp;

}

//Grid Grid::operator=(Grid n_grid) {
//	set_value(n_grid);
//
//	return *this;
//}



//void Grid::initialize_direct() {
//	for (int i = 0; i < length; i++) {
//		for (int j = 0; j < length; j++)
//		{
//			if (i > 0)
//				all_grid[i][j].set_north_block(&all_grid[i - 1][j]);
//			if (i < length - 1)
//				all_grid[i][j].set_south_block(&all_grid[i + 1][j]);
//			if (j > 0)
//				all_grid[i][j].set_west_block(&all_grid[i][j - 1]);
//			if (j < length - 1)
//				all_grid[i][j].set_east_block(&all_grid[i][j + 1]);
//		}
//	}
//}

void Grid::show_grid() {
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
			cout << all_grid[i][j].get_number() << ' ';
		cout << endl;
	} 
	cout << "This grid's hashtag is " << hash << endl;
	cout << endl;
}

bool Grid::if_pt_bottom_right() {
	if (blank_x_pos == length - 1 && blank_y_pos == length - 1)
		return true;
	else
		return false;
}

void Grid::move_north() {
	all_grid[blank_y_pos][blank_x_pos].set_number(all_grid[blank_y_pos - 1][blank_x_pos].get_number());
	all_grid[blank_y_pos - 1][blank_x_pos].set_number(0);
	blank_y_pos -= 1;

}

void Grid::move_east() {
	all_grid[blank_y_pos][blank_x_pos].set_number(all_grid[blank_y_pos][blank_x_pos + 1].get_number());
	all_grid[blank_y_pos][blank_x_pos + 1].set_number(0);
	blank_x_pos += 1;
}
void Grid::move_south() {
	all_grid[blank_y_pos][blank_x_pos].set_number(all_grid[blank_y_pos + 1][blank_x_pos].get_number());
	all_grid[blank_y_pos + 1][blank_x_pos].set_number(0);
	blank_y_pos += 1;
}
void Grid::move_west() {
	all_grid[blank_y_pos][blank_x_pos].set_number(all_grid[blank_y_pos][blank_x_pos - 1].get_number());
	all_grid[blank_y_pos][blank_x_pos - 1].set_number(0);
	blank_x_pos -= 1;
}

Grid Grid::move_north_bfs() {
	if (blank_y_pos > 0) {
		Grid* temp = new Grid(length);
		temp->set_value(*this);
		temp->all_grid[blank_y_pos][blank_x_pos].set_number(temp->all_grid[blank_y_pos - 1][blank_x_pos].get_number());
		temp->all_grid[blank_y_pos - 1][blank_x_pos].set_number(0);
		temp->blank_y_pos -= 1;
		temp->compute_hash();

		return *temp;
	}
	return NULL;
}

Grid Grid::move_east_bfs() {
	if (blank_x_pos < length - 1) {
		Grid* temp = new Grid(length);
		temp->set_value(*this);
		temp->all_grid[blank_y_pos][blank_x_pos].set_number(temp->all_grid[blank_y_pos][blank_x_pos + 1].get_number());
		temp->all_grid[blank_y_pos][blank_x_pos + 1].set_number(0);
		temp->blank_x_pos += 1;
		temp->compute_hash();

		return *temp;
	}
	return NULL;
}
Grid Grid::move_south_bfs() {
	if (blank_y_pos < length - 1) {
		Grid* temp = new Grid(length);
		temp->set_value(*this);
		temp->all_grid[blank_y_pos][blank_x_pos].set_number(temp->all_grid[blank_y_pos + 1][blank_x_pos].get_number());
		temp->all_grid[blank_y_pos + 1][blank_x_pos].set_number(0);
		temp->blank_y_pos += 1;
		temp->compute_hash();

		return *temp;
	}
	return NULL;
}
Grid Grid::move_west_bfs() {
	if (blank_x_pos > 0) {
		Grid* temp = new Grid(length);
		temp->set_value(*this);
		temp->all_grid[blank_y_pos][blank_x_pos].set_number(temp->all_grid[blank_y_pos][blank_x_pos - 1].get_number());
		temp->all_grid[blank_y_pos][blank_x_pos - 1].set_number(0);
		temp->blank_x_pos -= 1;
		temp->compute_hash();

		return *temp;
	}
	return NULL;
}
