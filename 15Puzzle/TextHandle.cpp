#include "TextHandle.h"

TextHandle::TextHandle() :text_content(""), number_of_grid(0), fileAddress(""), grid_length(4) {
	get_info_from_text();
	is_file_valid = split_string();
}

TextHandle::TextHandle(int length) : text_content(""), number_of_grid(0), fileAddress(""), grid_length(length) {
	get_info_from_text();
	is_file_valid = split_string();
}

void TextHandle::get_info_from_text() {
	ifstream readFile;
	ostringstream buf;
	char temp;
	readFile.open("");
	
	while (!readFile) {
		cout << "Input the file's address. "<< endl;
		cout << "Use \\\\ rather than \\ to seperate the folders and file's name. " << endl;
		cout << "Or input 1 to create a new file." << endl;
		cin >> fileAddress;
		string temp_order = "";
		if (fileAddress[0] == '1') {
			while (!readFile) {
				cout << "Input the path where the file you want to create. " << endl;
				cout << "Use \\\\ rather than \\ to seperate the folders and file's name. " << endl;
				cout << "Input 2 to cancel. " << endl;
				cin >> fileAddress;
				if (fileAddress[0] == '2')
					break;
				readFile.open(fileAddress);
				if (readFile) {
					cout << "File already exists, do you want to cover it? Y/N" << endl;
					cin >> temp_order;
					readFile.close();
					if (temp_order[0] == 'Y') {
						ofstream createFile(fileAddress);
						if (!createFile) {
							cout << "Failed to create new file! Try it again. " << endl;
						}
						createFile.close();
					}
				}
				else {
					ofstream createFile(fileAddress);
					createFile.close();
				}

				readFile.open(fileAddress);
			}
		}
		else
		{
			readFile.open(fileAddress);
			if (!readFile) {
				cout << "Address wrong, Check it again. " << endl;
				readFile.close();
			}
		}
	}

	while (buf && readFile.get(temp))
	{
		buf.put(temp);
	}

	readFile.close();
	text_content = buf.str();

	set_grid_number();
}

void TextHandle::set_grid_number() {
	string temp = "";
	int end_number = 0;
	for (int i = 0; i < text_content.length(); i++)
	{
		temp += text_content[i];
		end_number++;
		if (text_content[i] == '\n') {
			number_of_grid = atoi(text_content.c_str());
			break;
		}
	}
	text_content.erase(0, end_number);

	

	grids = new vector<int>[number_of_grid];
	
}

bool TextHandle::split_string() {
	if (number_of_grid == 0)
		return true;

	string content_backup = text_content;

	string temp = "";
	int counter = 0, end_number = 0;
	for (int i = 0; i < number_of_grid; i++)
		for (int j = 0; j < content_backup.length() + 1; j++) {
			temp += content_backup[j];
			end_number++;

			if (content_backup[j] == ' ' || content_backup[j] == '\n' || content_backup[j] == '\0')
			{
				if (atoi(temp.c_str()) != 0) {
					grids[i].push_back(atoi(temp.c_str()));
					counter++;
				}
				temp = "";
			}
			if (counter == grid_length * grid_length - 1) {
				content_backup.erase(0, end_number);
				end_number = 0;
				counter = 0;
				break;
			}

		}
	//check lack of matrix or wrong number of num
	for (int i = 0; i < number_of_grid; i++)
		if (grids[i].size() != grid_length * grid_length - 1)
			return false;

	//check repeative number or number exceed the area
	for (int i = 0; i < number_of_grid; i++)
		for (int j = 0; j < grids[i].size() - 1; j++) {
			if (grids[i][j]<1 || grids[i][j]>grid_length * (grid_length + 1))
				return false;
			for (int x = j + 1; x < grids[i].size(); x++)
				if (grids[i][j] == grids[i][x] || grids[i][j] == 0)
					return false;
		}
			

	return true;
}

bool TextHandle::input_new_grid() {
	string new_grid_string = "";
	string temp = "";

	cout << "\nInput a new grid in a correct form, 15 numbers in 1~20, no two of them can be same. " << endl;
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

	for(int i=0;i< grid_length * grid_length - 2;i++)
		for (int j = i + 1; j < grid_length * grid_length - 1; j++)
			if (new_grid[i] == new_grid[j] || new_grid[i] > 20 || new_grid[i] < 0) {
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

void TextHandle::write_in_file() {
	string text = "";
	text += to_string(number_of_grid);
	text += '\n';

	for (int i = 0; i < number_of_grid; i++) {
		for (int j = 0; j < grid_length * grid_length - 1; j++) {
			text += to_string(grids[i][j]);
			if ((j % grid_length) == grid_length - 1)
				text += '\n';
			else
				text += ' ';
		}
		text += "\n\n";
	}
		

	ofstream writeFile;
	writeFile.open(fileAddress);
	writeFile << text;
	writeFile.close();

	cout << "New matrix successfully created." << endl;
}

bool TextHandle::random_create() {
	vector<int> new_grid;
	int counter = 0;

	random_device rd;
	default_random_engine random_num(rd());
	uniform_int_distribution<int> random_num_dis(1, grid_length * (grid_length + 1));

	for (counter = 0; counter < grid_length * grid_length - 1;) {
		int temp = random_num_dis(random_num);
		if (check_if_not_exist(new_grid, temp)) {
			new_grid.push_back(temp);
			counter++;
		}
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

bool TextHandle::check_if_not_exist(vector<int> grid, int wait_checked_num) {
	for (int i = 0; i < grid.size(); i++)
		if (wait_checked_num == grid[i])
			return false;
	return true;
}

void TextHandle::write_solution_file(string solution) {
	ofstream oFile;
	oFile.open(fileAddress + "_Solution", ios::app);
	if (!oFile) {
		ofstream createFile(fileAddress + "_Solution");
		createFile.close();
		oFile.open(fileAddress + "_Solution", ios::app);
	}

	oFile << solution;
	oFile.close();
}