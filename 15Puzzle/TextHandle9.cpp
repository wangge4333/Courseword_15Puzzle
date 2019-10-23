#include "TextHandle9.h"

TextHandle9::TextHandle9():TextHandle(3) {
	
}

bool TextHandle9::input_new_grid() {
	string new_grid_string = "";
	string temp = "";

	cout << "\nInput a new grid in a correct form, 8 numbers in 1~10, none two of them can be same. " << endl;
	cout << "Use ',' to divide every number. " << endl;

	for (int i = 0; i < grid_length; i++) {
		cout << "now input the row " << i + 1 << ". " << endl;
		cin >> temp;
		new_grid_string += temp;
		new_grid_string += '\n';
		temp = "";
	}

	temp = "";
	vector<int> new_grid;
	int counter = 0;

	for (int i = 0; i < new_grid_string.length() + 1; i++) {
		temp += new_grid_string[i];

		if (new_grid_string[i] == ' ' || new_grid_string[i] == '\n' || new_grid_string[i] == '\0' || new_grid_string[i] == ',')
		{
			if (atoi(temp.c_str()) != 0) {
				new_grid.push_back(atoi(temp.c_str()));
				counter++;
			}
			temp = "";
		}
		if (counter == grid_length * grid_length - 1) {
			break;
		}
	}

	if (counter < grid_length * grid_length - 1) {
		cout << "Illegal grid form, input again. " << endl;
		return false;
	}

	for (int i = 0; i < grid_length * grid_length - 2; i++)
		for (int j = i + 1; j < grid_length * grid_length - 1; j++)
			if (new_grid[i] == new_grid[j] || new_grid[i] > 12 || new_grid[i] < 0) {
				cout << "You can't input 2 same number in a matrix, or any number not in legal area. " << endl;
				return false;
			}


	if (number_of_grid != 0) {
		vector<int>* temp_grids = new vector<int>[number_of_grid];
		for (int i = 0; i < number_of_grid; i++) {
			temp_grids[i] = grids[i];
		}

		number_of_grid++;
		delete[] grids;

		grids = new vector<int>[number_of_grid];
		for (int i = 0; i < number_of_grid - 1; i++) {
			grids[i] = temp_grids[i];
		}
		grids[number_of_grid - 1] = new_grid;
	}
	else
	{
		number_of_grid++;
		grids = new vector<int>[number_of_grid];
		grids[0] = new_grid;
	}

	write_in_file();
	return true;
}