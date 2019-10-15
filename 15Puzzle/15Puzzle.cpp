// 15Puzzle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "TextHandle.h"
#include "Grid.h"
#include "Block.h"

using namespace std;

int main()
{
	TextHandle* text_handle = new TextHandle();
	string order = "";

	Grid* grids = new Grid[text_handle->get_grid_number()];
	for (int i = 0; i < text_handle->get_grid_number(); i++) {
		grids[i].set_value(text_handle->get_vectors()[i]);
	}
		

	while (order != "C")
	{
		cout << "Input I to create a new matrix. Input S to show all matrixes. " << endl;
		cout << "Input C to cancel the program. " << endl;
		cin >> order;
		if (order[0] == 'I') {
			while (text_handle->input_new_grid() == false) {};

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
