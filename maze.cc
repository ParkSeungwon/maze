#include <iostream>
#include <random>
#include <chrono>
#include <future>
#include "maze.h"
using namespace std;

int Maze::shortest_steps = 10000;
unsigned long Maze::wander = 0;
unsigned long Maze::build = 0;
Char2D Maze::shortcut {0, 0};

void func1() {
	this_thread::sleep_for(chrono::seconds(1));
}

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
	build++;
	uniform_real_distribution<> nd(0,10);
	knuth_b e(chrono::system_clock::now().time_since_epoch().count());
	
	for(int y=1; y<height-1; y++) {
		for(int x=1; x<width-1; x++) {
			if(nd(e) > 5) p_char2d[y][x] = ROAD;
			else p_char2d[y][x] = WALL;
		}
	}
	p_char2d[1][1] = ROAD;
	p_char2d[height-2][width-2] = ROAD;
	shortest_steps = 10000;
	step = 0;
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
	wander++;
	this->x = x; this->y = y;
	p_char2d[y][x] = SHORTCUT;
	if(step >= shortest_steps) return step;
	if(width-2 == x && height-1 == y) {
		if(step < shortest_steps) {
			shortest_steps = step;
			shortcut = *this;
		}
		return step;
	}
	auto ft = async(launch::async, bind(&Maze::time_branch, this, x, y-1));
	time_branch(x, y+1);
	time_branch(x+1, y);
	time_branch(x-1, y);
	ft.get();
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

void Maze::time_branch(int x, int y)
{
	if(peep(x, y)) {
		Maze m(*this);
		m.step++;
		m.best_way(x,y);
	}
}

