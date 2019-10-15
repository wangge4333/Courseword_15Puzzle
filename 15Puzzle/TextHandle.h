#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class TextHandle
{
protected:
	string fileAddress;
	string text_content;
	int number_of_grid;
	void set_grid_number();
	vector<int>* grids = nullptr;

public:
	TextHandle();
	~TextHandle() {};

	//Import matrix from files
	void get_info_from_text();
	int get_grid_number() { return number_of_grid; };
	void split_string();

	//Input matrix manually
	//void check_grid_number();
	bool input_new_grid();
	void write_in_file();

	//Others
	void show_all_grids();
	vector<int>* get_vectors() { return grids; };

};

