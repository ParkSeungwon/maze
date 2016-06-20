#pragma once
#include "char2d.h"

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
	static unsigned long wander, build;

protected:
	int step;	

private:
	void outer_wall();
	bool peep(int x, int y);
	void time_branch(int x, int y);
	int x, y;

};
