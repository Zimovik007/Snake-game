#include <iostream>
#include <cstdio>
#include <cmath>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include <ncurses.h>

#include "map.h"
#include "obj.h"
#include "point.h"

Map::Map()
{
	int Size = 0;
	Cnt_food = -1;
	char c;
	FILE* Fin;
	Width = 0;
	//Задача узнать количество строк и столцов
	Fin = fopen("map", "r");
	fscanf(Fin, "%c", &c);
	while ((c != '\n') && (c != feof(Fin)))
	{
		Width++;
		fscanf(Fin, "%c", &c);		
	}
	Size = Width;
	while (!feof(Fin))
	{
		if (c != '\n')
			Size++;
		fscanf(Fin, "%c", &c);
	}
	Height = Size / Width;
	fclose(Fin);
	
	Map_data = new char*[Height];
	for (int i = 0; i < Height; i++)
		Map_data[i] = new char[Width];
	
	//
	Fin = fopen("map", "r");
	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
			fscanf(Fin, "%c", &Map_data[i][j]);
		fscanf(Fin, "%c", &c);
	}	
}

void Map::display()
{
	for (int i = 0; i < Height; i++, printw("\n"))
		for (int j = 0; j < Width; j++)
		{
			if (Map_data[i][j] == Char_food) //Цвет еды
			{
				attron(COLOR_PAIR(1)); 
				addch(Map_data[i][j]); 
				attroff(COLOR_PAIR(1));
			}
			else 
			if (Map_data[i][j] == Char_head) //Цвет головы
			{
				attron(COLOR_PAIR(2)); 
				addch(Map_data[i][j]); 
				attroff(COLOR_PAIR(2));
			}
			else
			if ((Map_data[i][j] == Char_tail_up)
			||  (Map_data[i][j] == Char_tail_down)
			||  (Map_data[i][j] == Char_tail_left)
			||  (Map_data[i][j] == Char_tail_right)) //Цвет хвоста
			{
				attron(A_BOLD); 
				attron(COLOR_PAIR(3)); 
				addch(Map_data[i][j]); 
				attroff(COLOR_PAIR(3)); 
				attroff(A_BOLD);
			}
			else
			if (Map_data[i][j] == Char_wall) //Цвет хвоста
			{
				attron(A_BOLD); 
				addch(Map_data[i][j]); 
				attroff(A_BOLD);
			}
			else
				addch(Map_data[i][j]);
		}	
}

int Map::vec_size()
{
	return Chars.size();
}

void Map::vec_erase(int i)
{
	Chars.erase(Chars.begin() + i);
}

void Map::vec_erase(Point& P)
{
	for (int i = 0; i < Chars.size(); i++)
	{
		if ((Chars[i]->pos_x() == P.get_x()) && (Chars[i]->pos_y() == P.get_y()))
		{
			Chars.erase(Chars.begin() + i);
			break;
		}
	}
}

int Map::cnt_food()
{
	return Cnt_food;
}

void Map::add_food()
{
	Cnt_food++;
	Food = new SnakeFood(*this);
}

void Map::create_char(Point& Pos, char c)
{
	Map_data[Pos.get_y()][Pos.get_x()] = c;
}

Character* Map::select_char(int i)
{
	return Chars[i];
}

void Map::change(Point& P1, Point& P2)
{
	Map_data[P1.get_y()][P1.get_x()] = Map_data[P2.get_y()][P2.get_x()];
	Map_data[P2.get_y()][P2.get_x()] = Char_empty;
}

char Map::map_elem(Point& P)
{
	return Map_data[P.get_y()][P.get_x()];
}

char Map::map_elem(int X, int Y)
{
	return Map_data[Y][X];
}

void Map::add_to_vector(Character* address)
{
	Chars.push_back(address);
}

void Map::push_char_front(Character* C)
{
	Chars.insert(Chars.begin(), C);
}

int Map::height()
{
	return Height;
}

int Map::width()
{
	return Width;
}
