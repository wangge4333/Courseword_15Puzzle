// 15Puzzle.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Written by Ge Wang, Student ID 190082628
// SolutionFile will be created automaticly at the same folder of the source puzzle file


#include <iostream>
#include "TextHandle.h"
#include "TextHandle9.h"
#include "TextHandle4.h"
#include "TextHandle25.h"
#include "Grid.h"
#include "Block.h"
#include <unordered_map>
#include <queue>
#include <map>
#include <stdlib.h>
#include <sstream>
#include <iomanip>

using namespace std;

//void moveBlock(Grid& grid, int original_direction); has been abandoned
void moveBlockBFS(Grid& grid);
string get_result_str(Grid& grid);
unsigned long long check_continuous_row(unsigned long long partial);				//for 3x3 or 2x2 matrix
unsigned long long compute_continuous(Grid& grid, unsigned long long partial);		//for 4x4 or over matrix
unsigned long long check_continuous_c(Grid& grid, unsigned long long partial);		//only check the current matrix
void bubbleSort(vector<int>& SplitedInt);
string lltos(long long t);

unordered_map<string, Grid> grid_map;
unordered_map<string, Grid> reachedgrid_map;

//work for recursion, has been abandoned
/*vector<int> step;							//1 = north, 2 = west, 3 = south, 4 = east
bool if_step = false;
bool check_step = false;
int repeat_step = 0;*/

int main()
{
	string order = "";
	int cursor = 0;
	TextHandle* text_handle = nullptr;

	while (order[0] != 'E') {
		order = "";
		cout << "Which length of matrices do you want to use? Input E to exit the program. " << endl;
		cout << "Input 2 for 2x2, 3 for 3x3, 4 for 4x4, etc." << endl;
		if (text_handle != nullptr) {
			delete text_handle;
			text_handle = nullptr;
		}

		cin >> cursor;
		switch (cursor)
		{
		case 2:
			text_handle = new TextHandle4();
			break;

		case 3:
			text_handle = new TextHandle9();
			break;

		case 4:
			text_handle = new TextHandle();
			break;

		case 5:
			text_handle = new TextHandle25();
			break;

		default:
			cout << cursor << 'x' << cursor << " matrices is not supported now." << endl;
			continue;
		}

		if (!text_handle->is_file_valid) {
			system("cls");
			cout << "Wrong file format or illegal number in matrix.\nCheck and Input again." << endl;
			continue;
		}
		
		//first level menu end

		Grid* grids = new Grid[text_handle->get_grid_number()];


		for (int i = 0; i < text_handle->get_grid_number(); i++) {
			grids[i].set_length(text_handle->get_length());
			grids[i].set_value(text_handle->get_vectors()[i]);
		}
		system("cls");

		//2nd level menu
		while (order[0] != 'C') {
			cout << "Input Q to create a new matrix. " << endl;
			cout << "Input W to create new matrices randomly." << endl;
			cout << "Input E to show any matrix(es)." << endl;
			cout << "Input R to get the number of continuous row(and partial) matrices." << endl;
			cout << "Input C to cancel. " << endl;
			cin >> order;

			switch (order[0])
			{
			case 'Q':
				[&]() {
					order = "";
					system("cls");
					while (text_handle->input_new_grid() == false) {};
					if (text_handle->get_grid_number() != 0)
						delete[] grids;
					grids = new Grid[text_handle->get_grid_number()];

					for (int i = 0; i < text_handle->get_grid_number(); i++) {
						grids[i].set_value(text_handle->get_vectors()[i]);
					}
					cout << endl;
				}();
				break;

			case 'E':
				[&]() {
					order = "";
					system("cls");
					if (text_handle->get_grid_number() == 0) {
						cout << "No matrices exist!" << endl;
					}
					else
					{
						cout << "Which matrices do you want to print on screen?" << 1 << '~' << text_handle->get_grid_number() << endl;
						cout << "Input 0 to print all matrices." << endl;
						cin >> cursor;
						if (cursor == 0) {
							for (int i = 0; i < text_handle->get_grid_number(); i++)
								grids[i].show_grid();
						}
						else
						{
							cursor--;
							if (cursor >= text_handle->get_grid_number() || cursor < 0)
								cout << "Input wrong! matrices does not exist." << endl;
							else
							{
								grids[cursor].show_grid();
							}
						}
					}
					
					cout << endl;
				}();
				break;

			case 'R':
				[&]() {
					order = "";
					if (text_handle->get_grid_number() == 0)
						cout << "No matrices exist!" << endl;
					else
					{
						cout << "SolutionFile will be created automaticly at the same folder of the source puzzle file. " << endl;
						cout << "Which matrices do you want to compute? " << 1 << '~' << text_handle->get_grid_number() << endl;
						cout << "Input 0 for compute all grids." << endl;
						cin >> cursor;
						cursor--;
						if (cursor >= text_handle->get_grid_number() || cursor < -1)
							cout << "Input wrong! matrices does not exist." << endl;
						else if (cursor == -1) {
							string str_wait_out = "";
							for (int i = 0; i < text_handle->get_grid_number(); i++) {
								str_wait_out += get_result_str(grids[i]);
							}
							system("cls");
							text_handle->write_solution_file(str_wait_out);
							cout << str_wait_out;
						}
						else
						{
							system("cls");
							string str_wait_out = get_result_str(grids[cursor]);
							text_handle->write_solution_file(str_wait_out);
							cout << str_wait_out;
						}
					}
				}();
				break;

			case 'W':
				[&]() {
					order = "";
					system("cls");
					cout << "How many matriceses do you want to create?" << endl;
					cin >> cursor;
					for (int i = 0; i < cursor; i++)
						text_handle->random_create();
					if (text_handle->get_grid_number() != 0)
						delete[] grids;
					grids = new Grid[text_handle->get_grid_number()];

					for (int i = 0; i < text_handle->get_grid_number(); i++) {
						grids[i].set_length(text_handle->get_length());
						grids[i].set_value(text_handle->get_vectors()[i]);
					}
				}();
				break;

			case 'C':
				system("cls");
				break;
			default:
				order = "";
				system("cls");
				cout << "Unknown order, check your input." << endl;
				break;
			}

		}

		
	}

	

	
}

//original_direction  1 = from_north, 2 = from_east, 3 = from_south, 4 = from_west, 0 = start
//this function has been abandoned because of stack overflow
//void moveBlock(Grid& grid, int original_direction) {
//	if (grid.get_blank_one() == nullptr)
//		return;
//	if (grid.is_pt_bottom_right()) {
//		grid.compute_hash();
//		if (grid_map.find(grid.get_hash()) != grid_map.end()) {
//			r_num++;
//
//			if (!if_step)
//				if_step = true;
//			else {
//				if_step = false;
//				check_step = true;
//				repeat_step = 0;
//			}
//				
//			//cout << "Repeat" << endl;
//			//grid.show_grid();
//			
//		}
//		else
//		{
//			num++;
//
//			if_step = false;
//			check_step = false;
//			step.clear();
//
//			//grid.show_grid();
//			grid_map[grid.get_hash()] = grid;
//		}
//
//		cout << "Grid good: " << num << endl;
//		cout << "Grid repeat: " << r_num << endl;
//
//		if (original_direction != 0)
//		{
//			delete &grid;
//			return;
//		}
//	}
//
//	//cout << grid.get_blank_x() << endl;
//	//cout << grid.get_blank_y() << endl;
//	//grid.show_grid();
//
//	//east
//	if (grid.get_blank_x() < grid.get_length() - 1 && original_direction != 4 ) {
//		if (!check_step || step[repeat_step] != 4) {
//			Grid* temp = new Grid();
//			temp->set_value(grid);
//			temp->move_east();
//			if (if_step)
//				step.push_back(4);
//
//			cout << "east" << endl;
//			moveBlock(*temp, 2);
//		}
//	}
//
//	//west
//	if (grid.get_blank_x() > 0 && original_direction != 2) {
//		if (!check_step || step[repeat_step] != 2) {
//			Grid* temp = new Grid();
//			temp->set_value(grid);
//			temp->move_west();
//			if (if_step)
//				step.push_back(2);
//
//			cout << "west" << endl;
//			moveBlock(*temp, 4);
//		}
//		
//	}
//
//	//south
//	if (grid.get_blank_y() < grid.get_length() - 1 && original_direction != 3) {
//		if (!check_step || step[repeat_step] != 3) {
//			Grid* temp = new Grid();
//			temp->set_value(grid);
//			temp->move_south();
//
//			if (if_step)
//				step.push_back(3);
//
//
//			cout << "south" << endl;
//			moveBlock(*temp, 1);
//		}
//		
//	}
//
//	//north
//	if (grid.get_blank_y() > 0 && original_direction != 1) {
//		if (!check_step || step[repeat_step] != 1) {
//			Grid* temp = new Grid();
//			temp->set_value(grid);
//			temp->move_north();
//
//			if (if_step)
//				step.push_back(1);
//
//			cout << "north" << endl;
//			moveBlock(*temp, 3);
//		}
//		
//	}
//}


//get result directly by a certain formula if matrix is or over 4x4
//go through all possible turns if matrix is or under 3x3
void moveBlockBFS(Grid& grid) {
	if (grid.get_length() > 3) {
		return;
	}

	grid_map.clear();
	reachedgrid_map.clear();

	queue<Grid> wait_grid;
	Grid current_grid, next_grid;

	wait_grid.push(grid);
	reachedgrid_map[grid.get_hash()] = grid;
	grid_map[grid.get_hash()] = grid;

	while (!wait_grid.empty()) {

		current_grid = wait_grid.front();


		wait_grid.pop();

		//get north move node
		if (current_grid.if_north_valid()) {
			next_grid = current_grid.move_north_bfs();

			if (reachedgrid_map.find(next_grid.get_hash()) == reachedgrid_map.end()) {

				if (next_grid.is_pt_bottom_right())
				{
					if (grid_map.find(next_grid.get_hash()) != grid_map.end()) {
						
					}
						
					else
					{
						grid_map[next_grid.get_hash()] = next_grid;
						reachedgrid_map[next_grid.get_hash()] = next_grid;
						wait_grid.push(next_grid);
						
					}
				}
				else
				{
					wait_grid.push(next_grid);
					reachedgrid_map[next_grid.get_hash()] = next_grid;

				}
			}
		}

		//get south move node
		if (current_grid.if_south_valid()) {
			next_grid = current_grid.move_south_bfs();
			if (reachedgrid_map.find(next_grid.get_hash()) == reachedgrid_map.end()) {
				
				if (next_grid.is_pt_bottom_right())
				{
					if (grid_map.find(next_grid.get_hash()) != grid_map.end()) {
						
					}
						
					else
					{
						grid_map[next_grid.get_hash()] = next_grid;
						reachedgrid_map[next_grid.get_hash()] = next_grid;
						wait_grid.push(next_grid);
						
					}
				}
				else
				{
					wait_grid.push(next_grid);
					reachedgrid_map[next_grid.get_hash()] = next_grid;

				}
			}
		}

		//get west move node
		if (current_grid.if_west_valid()) {
			next_grid = current_grid.move_west_bfs();
			if (reachedgrid_map.find(next_grid.get_hash()) == reachedgrid_map.end()) {
				
				if (next_grid.is_pt_bottom_right())
				{
					if (grid_map.find(next_grid.get_hash()) != grid_map.end()) {
						 
					}
					else
					{
						grid_map[next_grid.get_hash()] = next_grid;
						reachedgrid_map[next_grid.get_hash()] = next_grid;
						wait_grid.push(next_grid);
						
					}
				}
				else
				{
					wait_grid.push(next_grid);
					reachedgrid_map[next_grid.get_hash()] = next_grid;

				}
			}
			
		}

		//get east move node
		if (current_grid.if_east_valid()) {
			next_grid = current_grid.move_east_bfs();
			if (reachedgrid_map.find(next_grid.get_hash()) == reachedgrid_map.end()) {
				
				if (next_grid.is_pt_bottom_right())
				{
					if (grid_map.find(next_grid.get_hash()) != grid_map.end()) {

					}
					else
					{
						grid_map[next_grid.get_hash()] = next_grid;
						reachedgrid_map[next_grid.get_hash()] = next_grid;
						wait_grid.push(next_grid);
						
					}
				}
				else
				{
					wait_grid.push(next_grid);
					reachedgrid_map[next_grid.get_hash()] = next_grid;

				}
			}
		}
		
		if (grid_map.size() % 90 == 0) {
			system("cls");
			cout << "Computing...";
			if (grid.get_length() == 3)
				cout << "\n Now " << fixed << setprecision(2) << ((float)grid_map.size() / (float)20160) * 100.0 << "%" << endl;
			if(grid.get_length()==2)
				cout << "\n Now " << fixed << setprecision(2) << ((float)grid_map.size() / (float)3) * 100.0 << "%" << endl;
		}
	}
	system("cls");
}

string lltos(long long t)
{
	string result;
	stringstream temp;
	temp << t;
	temp >> result;
	return result;
}

//to get the string which need to output
string get_result_str(Grid& grid) {

	string temp = "";

	if (grid.get_length() < 4) {
		moveBlockBFS(grid);
		temp += grid.get_grid();
		temp = temp + "row = " + lltos(check_continuous_row(grid.get_length()));
		temp = temp + "\ncolumn = " + lltos(check_continuous_row(grid.get_length()));
		temp = temp + "\nreversed row = " + lltos(check_continuous_row(grid.get_length()));
		temp = temp + "\nreversed column = " + lltos(check_continuous_row(grid.get_length())) + '\n';
		temp = temp + " \n(total for row & column, including reverse, in this configuration) ";
		for (int i = 2; i <= grid.get_length(); i++)
			temp = temp + '\n' + lltos(i) + " = " + lltos(check_continuous_c(grid, i));
		temp = temp + " \n(total for row and column, including reverse, for all valid turns)  ";
		for (int i = 2; i <= grid.get_length(); i++)
			temp = temp + '\n' + lltos(i) + " = " + lltos(check_continuous_row(i) * 4);
		temp += "\n\n";
	}
	else
	{
		temp += grid.get_grid();
		temp = temp + "row = " + lltos(compute_continuous(grid, grid.get_length()));
		temp = temp + "\ncolumn = " + lltos(compute_continuous(grid, grid.get_length()));
		temp = temp + "\nreversed row = " + lltos(compute_continuous(grid, grid.get_length()));
		temp = temp + "\nreversed column = " + lltos(compute_continuous(grid, grid.get_length())) + '\n';
		temp = temp + " \n(total for row & column, including reverse, in this configuration) ";
		for (int i = 2; i <= grid.get_length(); i++)
			temp = temp + '\n' + lltos(i) + " = " + lltos(check_continuous_c(grid, i));
		temp = temp + " \n(total for row and column, including reverse, for all valid turns)  ";
		for (int i = 2; i <= grid.get_length(); i++)
			temp = temp + '\n' + lltos(i) + " = " + lltos(compute_continuous(grid, i) * 4);
		temp += "\n\n";
	}
	
	return temp;
}

//only for 3x3 matrix or under 3x3
unsigned long long check_continuous_row(unsigned long long partial) {
	int length = grid_map.begin()->second.get_length();
	unsigned long long sum = 0;
	int finish_rate = 0;

	for (unordered_map<string, Grid>::iterator iter = grid_map.begin(); iter != grid_map.end(); iter++) {
		finish_rate++;
		vector<int> temp_row;
		for (int i = 0; i < length; i++) {
			for (int j = 0; j < length; j++) {
				temp_row.push_back(iter->second.get_one_value(i, j));
			}
			vector<int> buffer;

			for (int j = 0; j < length; j++) {
				buffer.push_back(temp_row[j]);
				if (j == (temp_row.size() - 1) || temp_row[j] != (temp_row[j + 1] - 1)) {
					if (partial <= buffer.size()) {
						sum += buffer.size() - partial + 1;
					}
					buffer.clear();
				}
					
			}
			temp_row.clear();
		}

		if ((finish_rate % 90) == 0) {
			system("cls");
			cout << "Checking...";
			if (length == 3)
				cout << "\n Now " << fixed << setprecision(2) << ((float)finish_rate / (float)grid_map.size()) * 100.0 << "%" << endl;
		}
		

	}

	return sum;

	//this green code is orginal test code, then I found those 4 numbers are always same, so we can only compute 1 number
	/*if (length == 3) {
		for (int i = 0; i < length; i++) {
			if ((grid.get_one_value(i, 2) - 2) == (grid.get_one_value(i, 0)) && (grid.get_one_value(i, 1) - 1) == (grid.get_one_value(i, 0)))
				continuous_row++;
			if ((grid.get_one_value(2, i) - 2) == (grid.get_one_value(0, i)) && (grid.get_one_value(1, i) - 1) == (grid.get_one_value(0, i)))
				continuous_column++;
			if (grid.get_one_value(i, 2) != 0 && (grid.get_one_value(i, 2) + 2) == (grid.get_one_value(i, 0)) && (grid.get_one_value(i, 1) + 1) == (grid.get_one_value(i, 0)))
				reversed_c_row++;
			if (grid.get_one_value(2, i) != 0 && (grid.get_one_value(2, i) + 2) == (grid.get_one_value(0, i)) && (grid.get_one_value(1, i) + 1) == (grid.get_one_value(0, i)))
				reversed_c_column++;
		}
	}*/
	



}

//only for check continuous row/column/reverse row/reverse column in current matrix
unsigned long long check_continuous_c(Grid& grid, unsigned long long partial) {
	vector<int> temp_row;
	vector<int> temp_column;
	long long temp = 0;

	for (int i = 0; i < grid.get_length(); i++) {
		for (int j = 0; j < grid.get_length(); j++) {
			if (grid.get_one_value(i, j) != 0)
				temp_row.push_back(grid.get_one_value(i, j));
			if (grid.get_one_value(j, i) != 0)
				temp_column.push_back(grid.get_one_value(j, i));
		}

		vector<int> buffer_continuous;
		vector<int> buffer_reverse;

		for (int x = 0; x < temp_row.size(); x++) {
			buffer_continuous.push_back(temp_row[x]);
			buffer_reverse.push_back(temp_row[x]);

			if (x == (temp_row.size() - 1) || temp_row[x] != (temp_row[x + 1] - 1)) {
				if (partial <= buffer_continuous.size()) {
					temp = temp + buffer_continuous.size() - partial + 1;
				}
				buffer_continuous.clear();
			}

			if (x == (temp_row.size() - 1) || temp_row[x] != (temp_row[x + 1] + 1)) {
				if (partial <= buffer_reverse.size()) {
					temp = temp + buffer_reverse.size() - partial + 1;
				}
				buffer_reverse.clear();
			}
		}

		buffer_continuous.clear();
		buffer_reverse.clear();

		for (int x = 0; x < temp_column.size(); x++) {
			buffer_continuous.push_back(temp_column[x]);
			buffer_reverse.push_back(temp_column[x]);
			if (x == (temp_column.size() - 1) || temp_column[x] != (temp_column[x + 1] - 1)) {
				if (partial <= buffer_continuous.size()) {
					temp = temp + buffer_continuous.size() - partial + 1;
				}
				buffer_continuous.clear();
			}

			if (x == (temp_column.size() - 1) || temp_column[x] != (temp_column[x + 1] + 1)) {
				if (partial <= buffer_reverse.size()) {
					temp = temp + buffer_reverse.size() - partial + 1;
				}
				buffer_reverse.clear();
			}
		}
		temp_row.clear();
		temp_column.clear();

	}

	return temp;
		
}

//return the number of continuous row/column/reverse row/reverse column in possible turns, these 4 numbers are same
unsigned long long compute_continuous(Grid& grid, unsigned long long partial) {
	//get result directly by a certain formula if matrix is or over 4x4
	if (partial > grid.get_length())
		return 0;

	unsigned long long poss_con_r = 0;			//this is the number of possible continuous row in this matrix, like  in 1,2,3,4,5, there are 1,2,3,4 and 2,3,4,5 for partial 4
	unsigned long long result = 1;
	unsigned long long poss_pos = 0;			//this is the number of possible positions of the continuous row(column) might appear

	poss_pos = ((unsigned long long)grid.get_length() - partial + 1) * ((unsigned long long)grid.get_length() - 1)
		+ ((unsigned long long)grid.get_length() - partial);

	vector<int> sorted_matrix;
	for (int i = 0; i < grid.get_length(); i++) {
		for (int j = 0; j < grid.get_length(); j++)
			sorted_matrix.push_back(grid.get_one_value(i, j));
	}

	sorted_matrix.pop_back();					//delete the 0
	bubbleSort(sorted_matrix);					//sort the vector to find possible continuous row

	vector<int> temp;

	for (int i = 0; i < sorted_matrix.size(); i++) {
		temp.push_back(sorted_matrix[i]);
		if (i == (sorted_matrix.size() - 1) || sorted_matrix[i] != (sorted_matrix[i + 1] - 1)) {
			if (partial <= temp.size()) {
				poss_con_r += (temp.size() - partial + 1);
			}
			temp.clear();
		}
	}


	for (int i = 1; i <= sorted_matrix.size() - partial; i++)
		result *= i;

	result = poss_con_r * result * poss_pos / 2;
	return result;

}

void bubbleSort(vector<int>& SplitedInt) {
	int temp;
	vector<int>::iterator _current;
	for (int i = 0; i < SplitedInt.size(); i++) {
		for (_current = SplitedInt.begin(); _current < SplitedInt.end() - i - 1; _current++) {
			if (*_current > * (_current + 1))
			{
				temp = *(_current + 1);
				*(_current + 1) = *_current;
				*_current = temp;
			}
		}
	}
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
