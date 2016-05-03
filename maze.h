#pragma once
#include "char2d.h"
#define WALL '#'
#define ROAD ' '
#define STEP '.'
#define SHORTCUT '>'
#define OUTOFBOUND 'B'

class Maze : public Char2D
{
public:
	Maze(int w, int h);
	Maze(const Maze& m);
	int best_way(int x, int y);
	void find_way(int x, int y);

	void build_maze();
	static Char2D shortcut;
	static int shortest_steps;

protected:
	int step;	

private:
	void outer_wall();
	bool peep(int x, int y);
	int x, y;

};
