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
	int grid_length = 4;
	string fileAddress;
	string text_content;
	int number_of_grid;
	void set_grid_number();
	vector<int>* grids = nullptr;

public:
	TextHandle();
	TextHandle(int length);
	virtual ~TextHandle() {};

	//Import matrix from files
	virtual void get_info_from_text();
	virtual int get_grid_number() { return number_of_grid; };
	virtual void split_string();

	//Input matrix manually
	//void check_grid_number();
	virtual bool input_new_grid();
	virtual void write_in_file();

	//Others
	//void show_all_grids();
	vector<int>* get_vectors() { return grids; };
	int get_length() { return grid_length; };

};

