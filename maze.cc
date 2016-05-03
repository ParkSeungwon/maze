#include <iostream>
#include <random>
#include <chrono>
#include "maze.h"
using namespace std;

int Maze::shortest_steps = 10000;
Char2D Maze::shortcut {0, 0};

Maze::Maze(int w, int h) : Char2D(w, h)
{
	outer_wall();
	step = 0;
}

Maze::Maze(const Maze& m) : Char2D(m)
{
	step = m.step;
	x = m.x; y = m.y;
}

void Maze::build_maze()
{
	uniform_real_distribution<> nd(0,10);
	knuth_b e(chrono::system_clock::now().time_since_epoch().count());
	
	for(int y=1; y<height-1; y++) {
		for(int x=1; x<width-1; x++) {
			if(nd(e) > 4) p_char2d[y][x] = ROAD;
			else p_char2d[y][x] = WALL;
		}
	}
	p_char2d[1][1] = ROAD;
	p_char2d[height-2][width-2] = ROAD;
	shortest_steps = 10000;
}

void Maze::outer_wall()
{
	for(int x=0; x<width; x++) {
		p_char2d[0][x] = WALL;
		p_char2d[height-1][x] = WALL;
	}
	for(int y=0; y<height; y++) {
		p_char2d[y][0] = WALL;
		p_char2d[y][width-1] = WALL;
	}
	p_char2d[0][1] = ROAD;
	p_char2d[height-1][width-2] = ROAD;
}

void Maze::find_way(int x, int y) {
	p_char2d[y][x] = STEP;
	if((*this)(x, y-1) == ROAD) find_way(x, y-1);
	if((*this)(x, y+1) == ROAD) find_way(x, y+1);
	if((*this)(x-1, y) == ROAD) find_way(x-1, y);
	if((*this)(x+1, y) == ROAD) find_way(x+1, y);
}

int Maze::best_way(int x, int y)
{
	this->x = x; this->y = y;
	cout << '(' << x << ',' << y << ',' << step << ')' << endl;
	p_char2d[y][x] = SHORTCUT;
	show();
	if(step >= shortest_steps) return step;
	if(width-2 == x && height-1 == y) {
		if(step == width + height - 4) {
			show();
			cout << "took2 " << step << "steps" << endl;
			exit(0);
		}
		if(step < shortest_steps) {
			shortest_steps = step;
			shortcut = *this;
		}
		return step;
	}
	if(peep(x, y-1)) {
		Maze m(*this);
		m.step++;
		m.best_way(x, y-1);
	}
	if(peep(x, y+1)) {
		Maze m(*this);
		m.step++;
		m.best_way(x, y+1);
	}
	if(peep(x-1, y)) {
		Maze m(*this);
		m.step++;
		m.best_way(x-1, y);
	}
	if(peep(x+1, y)) {
		Maze m(*this);
		m.step++;
		m.best_way(x+1, y);
	}
}

bool Maze::peep(int x, int y)
{
	int a = x - this->x;
	int b = y - this->y;
	if((*this)(x, y) == STEP &&
		(a == -1 || (*this)(x+1, y) != SHORTCUT) &&
		(a == 1  || (*this)(x-1, y) != SHORTCUT) &&
		(b == -1 || (*this)(x, y+1) != SHORTCUT) &&
		(b == 1  || (*this)(x, y-1) != SHORTCUT))
	{
		return true;
	} else return false;
}


