#pragma once
#include "TextHandle.h"

//This is a class to handle and manage the orginal data of 3x3 matrices
class TextHandle9 :
	public TextHandle
{
public:
	bool input_new_grid();
	bool random_create();
	TextHandle9();

};

