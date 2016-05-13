#pragma once

#include <vector>
#include "map.h"
#include "point.h"

#define Char_head       '@'
#define Char_tail_up    '^'
#define Char_tail_down  'v'
#define Char_tail_left  '<'
#define Char_tail_right '>'
#define Char_food       '$'
#define Char_empty      '.'
#define Char_wall       '#'

class Character
{
public:
	virtual int move(Map &M, int Dir = -1) = 0;
	virtual void find_x_y(Map &M);
	virtual Point pos();	
	virtual int pos_x();
	virtual int pos_y();
	virtual int dir();
protected:
	int Direction;
	Point Pos;
};

class SnakeHead : public Character
{
public:
	SnakeHead(Map &M);
	int move(Map &M, int Dir = -1);
};

class SnakeTail : public Character
{
public:
	SnakeTail(Map &M, int Dir, Point Position);
	int move(Map &M, int Dir = -1);
};

class SnakeFood : public Character
{
public:
	SnakeFood(Map &M);
	int move(Map &M, int Dir = -1);
};
