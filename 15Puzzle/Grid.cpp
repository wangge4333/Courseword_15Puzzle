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

Grid::Grid(int ini_length):hash(""),length(ini_length) {

	all_grid = new Block * [length];
	for (int i = 0; i < length; i++) {
		all_grid[i] = new Block[length];
		all_grid[i]->set_number(0);
	}
}

Grid::Grid():hash("") {

	all_grid = new Block * [length];
	for (int i = 0; i < length; i++) {
		all_grid[i] = new Block[length];
		all_grid[i]->set_number(0);
	}

	//initialize_direct();
}

void Grid::set_value(vector<int> grids_value) {
	grids_value.push_back(0);
	if (grids_value.size() == 9)
		length = 3;
	if (grids_value.size() == 16)
		length = 4;
	if (grids_value.size() == 4)
		length = 2;


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

	length = n_grid.get_length();

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

	string temp = "";
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			string tp_str = "";
			int tp_int = all_grid[i][j].get_number();
			tp_str = tp_int;
			if (tp_int < 10)
				tp_str = '0' + tp_str;

			temp = temp + tp_str;
		}
	}
	hash = temp;
}

void Grid::show_grid() {
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++) {
			int temp = all_grid[i][j].get_number();
			if (temp > 9) {
				cout << temp << ' ';
			}
				
			else if (temp > 0 && temp < 10) {
				cout << ' ' << temp << ' ';
			}
				
		}
		cout << endl;
	} 
	//cout << "This grid's hashtag is " << hash << endl;
	cout << endl;
}

string Grid::get_grid() {
	string out_string = "";
	char buffer[10] = "";
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++) {
			int temp = all_grid[i][j].get_number();
			if (temp > 9) {
				_itoa_s(temp, buffer, 10);
				out_string = out_string + buffer + ' ';
			}

			else if (temp > 0 && temp < 10) {
				_itoa_s(temp, buffer, 10);
				out_string = out_string + ' ' + buffer + ' ';
			}

		}
		out_string += '\n';
	}
	out_string += '\n';
	return out_string;
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
