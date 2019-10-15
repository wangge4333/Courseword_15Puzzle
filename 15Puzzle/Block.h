#pragma once
class Block
{
protected:
	Block* north_block = nullptr;
	Block* south_block = nullptr;
	Block* west_block = nullptr;
	Block* east_block = nullptr;

	int num = 0;								//The value of block, 0 means blank

public:;
	   virtual Block* get_north_block() { return north_block; };
	   virtual Block* get_south_block() { return south_block; };
	   virtual Block* get_west_block() { return west_block; };
	   virtual Block* get_east_block() { return east_block; };

	   virtual void set_north_block(Block* block) { north_block = block; };
	   virtual void set_south_block(Block* block) { south_block = block; };
	   virtual void set_west_block(Block* block) { west_block = block; };
	   virtual void set_east_block(Block* block) { east_block = block; };

	   virtual int get_number() { return num; };
	   virtual void set_number(int new_num) { num = new_num; };


	   Block(int ini_num) :num(ini_num) {};
	   Block() {};
	   ~Block() {};
};

