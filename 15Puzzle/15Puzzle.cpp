// 15Puzzle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "TextHandle.h"
#include "TextHandle9.h"
#include "TextHandle4.h"
#include "Grid.h"
#include "Block.h"
#include <unordered_map>
#include <queue>
#include <map>

using namespace std;

void moveBlock(Grid& grid, int original_direction);
void moveBlockBFS(Grid& grid);
void checkGrid(Grid grid);


int num = 0;
int r_num = 0;

void temp_check(Grid grid, long long temp_hash);

int continuous_row = 0;

unordered_map<long long, Grid> grid_map;
unordered_map<long long, Grid> reachedgrid_map;

vector<int> step;							//1 = north, 2 = west, 3 = south, 4 = east
bool if_step = false;
bool check_step = false;
int repeat_step = 0;

int main()
{
	TextHandle* text_handle = new TextHandle9();
	string order = "";
	int int_order = 0;

	Grid* grids = new Grid[text_handle->get_grid_number()];


	for (int i = 0; i < text_handle->get_grid_number(); i++) {
		grids[i].set_length(text_handle->get_length());                 
;		grids[i].set_value(text_handle->get_vectors()[i]);
	}
		

	while (order != "C")
	{
		cout << "Input I to create a new matrix. Input S to show all matrixes. " << endl;
		cout << "Input O to iterate the matrix." << endl;
		cout << "Input C to cancel the program. " << endl;
		cin >> order;
		if (order[0] == 'I') {
			while (text_handle->input_new_grid() == false) {};
			if(text_handle->get_grid_number()!=0)
				delete[] grids;
			grids = new Grid[text_handle->get_grid_number()];

			for (int i = 0; i < text_handle->get_grid_number(); i++) {
				grids[i].set_value(text_handle->get_vectors()[i]);
			}

			cout << endl;
		}
		if (order[0] == 'S') {
			for (int i = 0; i < text_handle->get_grid_number(); i++)
				grids[i].show_grid();
			cout << endl;
		}
		if (order[0] == 'O') {
			if (text_handle->get_grid_number() == 0)
				cout << "No matrix exist!" << endl;
			else
			{
				cout << "Which matrix you want to iterate? " << 1 << '~' << text_handle->get_grid_number() << endl;
				cin >> int_order;
				int_order--;
				if (int_order >= text_handle->get_grid_number() || int_order < 0)
					cout << "Input wrong! Matrix does not exist." << endl;
				else
				{
					moveBlockBFS(grids[int_order]);
				}
			}
		}

	}
}

//original_direction  1 = from_north, 2 = from_east, 3 = from_south, 4 = from_west, 0 = start
void moveBlock(Grid& grid, int original_direction) {
	if (grid.get_blank_one() == nullptr)
		return;
	if (grid.if_pt_bottom_right()) {
		grid.compute_hash();
		if (grid_map.find(grid.get_hash()) != grid_map.end()) {
			r_num++;

			if (!if_step)
				if_step = true;
			else {
				if_step = false;
				check_step = true;
				repeat_step = 0;
			}
				
			cout << "Repeat" << endl;
			grid.show_grid();
			temp_check(grid, grid.get_hash());
			
		}
		else
		{
			num++;

			if_step = false;
			check_step = false;
			step.clear();

			grid.show_grid();
			grid_map[grid.get_hash()] = grid;
		}

		cout << "Grid good: " << num << endl;
		cout << "Grid repeat: " << r_num << endl;

		if (original_direction != 0)
		{
			delete &grid;
			return;
		}
	}

	//cout << grid.get_blank_x() << endl;
	//cout << grid.get_blank_y() << endl;
	//grid.show_grid();

	//east
	if (grid.get_blank_x() < grid.get_length() - 1 && original_direction != 4 ) {
		if (!check_step || step[repeat_step] != 4) {
			Grid* temp = new Grid();
			temp->set_value(grid);
			temp->move_east();
			if (if_step)
				step.push_back(4);

			cout << "east" << endl;
			moveBlock(*temp, 2);
		}
	}

	//west
	if (grid.get_blank_x() > 0 && original_direction != 2) {
		if (!check_step || step[repeat_step] != 2) {
			Grid* temp = new Grid();
			temp->set_value(grid);
			temp->move_west();
			if (if_step)
				step.push_back(2);

			cout << "west" << endl;
			moveBlock(*temp, 4);
		}
		
	}

	//south
	if (grid.get_blank_y() < grid.get_length() - 1 && original_direction != 3) {
		if (!check_step || step[repeat_step] != 3) {
			Grid* temp = new Grid();
			temp->set_value(grid);
			temp->move_south();

			if (if_step)
				step.push_back(3);


			cout << "south" << endl;
			moveBlock(*temp, 1);
		}
		
	}

	//north
	if (grid.get_blank_y() > 0 && original_direction != 1) {
		if (!check_step || step[repeat_step] != 1) {
			Grid* temp = new Grid();
			temp->set_value(grid);
			temp->move_north();

			if (if_step)
				step.push_back(1);

			cout << "north" << endl;
			moveBlock(*temp, 3);
		}
		
	}
}

void moveBlockBFS(Grid& grid) {
	queue<Grid> wait_grid;
	Grid current_grid, next_grid;

	wait_grid.push(grid);
	reachedgrid_map[grid.get_hash()] = grid;

	while (!wait_grid.empty()) {

		grid_map[grid.get_hash()] = grid;
		current_grid = wait_grid.front();

		//current_grid.show_grid();

		wait_grid.pop();

		//get north move node
		if (current_grid.if_north_valid()) {
			next_grid = current_grid.move_north_bfs();

			if (reachedgrid_map.find(next_grid.get_hash()) == reachedgrid_map.end()) {

				if (next_grid.if_pt_bottom_right())
				{
					if (grid_map.find(next_grid.get_hash()) != grid_map.end()) {
						r_num++;
						cout << "Repeat" << endl;
					}
						
					else
					{
						grid_map[next_grid.get_hash()] = next_grid;
						reachedgrid_map[next_grid.get_hash()] = next_grid;
						next_grid.show_grid();
					}
				}
				else
				{
					wait_grid.push(next_grid);
					reachedgrid_map[next_grid.get_hash()] = next_grid;

					//cout << "In reached map: " << reachedgrid_map.size() << endl;
				}
			}
		}

		//get south move node
		if (current_grid.if_south_valid()) {
			next_grid = current_grid.move_south_bfs();
			if (reachedgrid_map.find(next_grid.get_hash()) == reachedgrid_map.end()) {
				
				if (next_grid.if_pt_bottom_right())
				{
					if (grid_map.find(next_grid.get_hash()) != grid_map.end()) {
						r_num++;
						cout << "Repeat" << endl;
					}
						
					else
					{
						grid_map[next_grid.get_hash()] = next_grid;
						reachedgrid_map[next_grid.get_hash()] = next_grid;
						next_grid.show_grid();
					}
				}
				else
				{
					wait_grid.push(next_grid);
					reachedgrid_map[next_grid.get_hash()] = next_grid;

					//cout << "In reached map: " << reachedgrid_map.size() << endl;
				}
			}
		}

		//get west move node
		if (current_grid.if_west_valid()) {
			next_grid = current_grid.move_west_bfs();
			if (reachedgrid_map.find(next_grid.get_hash()) == reachedgrid_map.end()) {
				
				if (next_grid.if_pt_bottom_right())
				{
					if (grid_map.find(next_grid.get_hash()) != grid_map.end()) {
						r_num++;
						cout << "Repeat" << endl; 
					}
					else
					{
						grid_map[next_grid.get_hash()] = next_grid;
						reachedgrid_map[next_grid.get_hash()] = next_grid;
						next_grid.show_grid();
					}
				}
				else
				{
					wait_grid.push(next_grid);
					reachedgrid_map[next_grid.get_hash()] = next_grid;

					//cout << "In reached map: " << reachedgrid_map.size() << endl;
				}
			}
			
		}

		//get east move node
		if (current_grid.if_east_valid()) {
			next_grid = current_grid.move_east_bfs();
			if (reachedgrid_map.find(next_grid.get_hash()) == reachedgrid_map.end()) {
				
				if (next_grid.if_pt_bottom_right())
				{
					if (grid_map.find(next_grid.get_hash()) != grid_map.end()) {
						r_num++;
						cout << "Repeat" << endl;

					}
					else
					{
						grid_map[next_grid.get_hash()] = next_grid;
						reachedgrid_map[next_grid.get_hash()] = next_grid;
						next_grid.show_grid();
					}
				}
				else
				{
					wait_grid.push(next_grid);
					reachedgrid_map[next_grid.get_hash()] = next_grid;

					//cout << "In reached map: " << reachedgrid_map.size() << endl;
				}
			}
		}

		cout << "Now " << grid_map.size() << "." << endl;

	}

	

	cout << "Reachable " << grid_map.size() <<"."<< endl;
	cout << "Total " << reachedgrid_map.size() << "." << endl;
	cout << "Repeat " << r_num << endl;
	grid_map.clear();
	reachedgrid_map.clear();

}



void checkGrid(Grid grid) {

}

void temp_check(Grid grid,long long temp_hash) {
	Grid temp_grid = grid_map[temp_hash];
	bool flag = true;
	for (int i = 0; i < grid.get_length(); i++)
		for (int j = 0; j < grid.get_length(); j++)
			if (grid.get_one_value(i, j) != temp_grid.get_one_value(i, j))
				flag = false;

	if (flag == false) {
		cout << "Bad" << endl;
		system("pause");
	}
	else
		cout << "good" << endl;
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
