#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <random>

using namespace std;


//This is a class to handle and manage the orginal data of 4x4 matrices
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

	//check the file is valid
	bool is_file_valid = false;

	//Import matrix from files
	virtual void get_info_from_text();
	virtual int get_grid_number() { return number_of_grid; };
	virtual bool split_string();

	//Input matrix manually
	virtual bool input_new_grid();

	//File IO
	virtual void write_solution_file(string solution);
	virtual void write_in_file();

	//Randomly create matrix
	virtual bool random_create();
	virtual bool check_if_not_exist(vector<int> grid, int wait_checked_num);

	//Others
	//void show_all_grids();
	vector<int>* get_vectors() { return grids; };
	int get_length() { return grid_length; };

};

