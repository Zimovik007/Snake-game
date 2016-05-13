#include <iostream>
#include <cstdio>
#include <cmath>
#include <stdlib.h>
#include <vector>
#include <string>
#include <ncurses.h>

#include "obj.h"
#include "map.h"
#include "point.h"

//CHARACTER

void Character::find_x_y(Map &M)
{
	int Cnt = 0;	
	for (int i = 3; i < M.height() - 3; i++)
		for (int j = 3; j < M.width() - 3; j++)
			if (M.map_elem(j, i) == Char_empty) 
				Cnt++;
	
	int Ran = rand() % Cnt;
	for (int i = 3; i < M.height() - 3; i++)
		for (int j = 3; j < M.width() - 3; j++)
		{
			if (M.map_elem(j, i) == Char_empty) 
				Ran--;
			if (!Ran)
			{
				Pos = Point(j, i);
				return;
			}
		}
}

Point Character::pos()
{
	return Pos;
}

int Character::pos_x()
{
	return Pos.get_x();
}

int Character::pos_y()
{
	return Pos.get_y();
}

int Character::dir()
{
	return Direction;
}

//HEAD

SnakeHead::SnakeHead(Map &M)
{
	M.add_food();
	Point P1, P2;
	find_x_y(M);
	M.create_char(Pos, Char_head);	
	M.add_to_vector(this);	
	Direction = rand() % 4;
	if (Direction == 0){ P1 = Pos.move_down();  }
	if (Direction == 1){ P1 = Pos.move_left();  }
	if (Direction == 2){ P1 = Pos.move_up();    }
	if (Direction == 3){ P1 = Pos.move_right(); }
	new SnakeTail(M, Direction, Pos);
	new SnakeTail(M, Direction, P1);
}

int SnakeHead::move(Map &M, int Dir)
{
	int Res = Direction;
	if (Dir != -1)
	{
		if (Dir == 'w') Direction = 0;
		else
		if (Dir == 'd') Direction = 1;
		else
		if (Dir == 's') Direction = 2;
		else
		if (Dir == 'a') Direction = 3;
	}
	Point Temp;
	if (Direction == 0) Temp = Pos.move_up();
	if (Direction == 1) Temp = Pos.move_right();
	if (Direction == 2) Temp = Pos.move_down();
	if (Direction == 3) Temp = Pos.move_left();
	
	if (M.map_elem(Temp) == '.')
	{
		M.change(Temp, Pos);
		Pos = Temp;
		return Res;
	}		
	
	if (M.map_elem(Temp) == '$')
	{
		M.change(Temp, Pos);
		Pos = Temp;
		M.add_food();
		return Res;
	}
	
	return -5;
}

//TAIL

SnakeTail::SnakeTail(Map &M, int Dir, Point Position)
{
	char temp;
	Pos = Position;
	if (Dir == 0){ Pos = Pos.move_down();  temp = Char_tail_up;    }
	if (Dir == 1){ Pos = Pos.move_left();  temp = Char_tail_right; }
	if (Dir == 2){ Pos = Pos.move_up();    temp = Char_tail_down;  }
	if (Dir == 3){ Pos = Pos.move_right(); temp = Char_tail_left;  }
	Direction = Dir;
	M.create_char(Pos, temp);	
	M.add_to_vector(this);
}

int SnakeTail::move(Map &M, int Dir)
{
	int Res = Direction;
	Direction = Dir;
	Point Temp;
	if (Direction == 0) {Temp = Pos.move_up();    M.create_char(Pos, Char_tail_up);    }
	if (Direction == 1) {Temp = Pos.move_right(); M.create_char(Pos, Char_tail_right); }
	if (Direction == 2) {Temp = Pos.move_down();  M.create_char(Pos, Char_tail_down);  }
	if (Direction == 3) {Temp = Pos.move_left();  M.create_char(Pos, Char_tail_left);  }
	M.change(Temp, Pos);
	Pos = Temp;
	return Res;
}

//FOOD

SnakeFood::SnakeFood(Map &M)
{
	find_x_y(M);
	M.create_char(Pos, Char_food);
}

int SnakeFood::move(Map &M, int Dir)
{
	return 0;
}
