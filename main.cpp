#include <stdlib.h>
#include <vector>
#include <ncurses.h>
#include <ctime>
#include <unistd.h>

#include "map.h"
#include "obj.h"

Map Snake_map;

int next_move(int D)
{
	int Before_cnt = Snake_map.cnt_food();	
	int Dir = Snake_map.select_char(0)->move(Snake_map, D);
	if (Dir == -5) return 0;
	for(int i = 1; i < Snake_map.vec_size(); i++)
		Dir = Snake_map.select_char(i)->move(Snake_map, Dir);		
	if (Snake_map.cnt_food() > Before_cnt)
		new SnakeTail(Snake_map, Snake_map.select_char(Snake_map.vec_size() - 1)->dir(), 
								 Snake_map.select_char(Snake_map.vec_size() - 1)->pos());
	return 1;
}

void init_ncurses()
{
	initscr();
	start_color();
	keypad(stdscr, TRUE);
	noecho();
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
}

int main()
{
	int q;
	srand(time(0));	
	init_ncurses();
	
	new SnakeHead(Snake_map);
	
	erase();
	Snake_map.display();
	q = getch();
	
	int Game_over = 1;
	while (Game_over)
	{
		q = -1;
		erase();
		Snake_map.display();
		printw("%d\n", Snake_map.cnt_food());
		halfdelay(1);
		q = getch();
		Game_over = next_move(q);
		usleep(40000);
	}
	erase();
	printw("YOU LOOSE!\nYour score: %d\n\n\nPlease ENTER!\n", Snake_map.cnt_food());
	nocbreak();
	getch();
	endwin();
	return 0;
}
