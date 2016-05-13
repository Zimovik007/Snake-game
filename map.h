#pragma once

#include <vector>

class Character;
class Point;

class Map
{
private:
	int Height;
	int Width;
	char **Map_data;
	std::vector<Character*> Chars;
	Character* Food;
	int Cnt_food;
public:
	Map();
	int cnt_food();
	void add_food();
	void display();
	void create_char(Point& Pos, char c);
	char map_elem(int X, int Y);
	char map_elem(Point& P);
	void vec_erase(int i);
	void vec_erase(Point& P);
	void change(Point& P1, Point& P2);
	void add_to_vector(Character* address);
	int  vec_size();
	void push_char_front(Character* C);
	Character* select_char(int i);
	int height();
	int width();
};
	
