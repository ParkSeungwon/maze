#include "maze.h"
#include <iostream>
#include <exception>
using namespace std;

int main(int argc, char** argv)
{
	if(argc < 3) {
		cout << "usage : " << argv[0] << " width height" << endl;
		return 0;
	}
	int w = atoi(argv[1]);
	int h = atoi(argv[2]);

//	Char2D c4(c2);
	Maze m(w, h);
	m.build_maze();
	m.show();
	cout << endl;
	m.find_way(1, 0);
	m.show();
	cout << endl;
	if(m(w-2, h-1) == STEP) {
		try {
		int step = m.best_way(1, 0);
		} catch(exception& e) {cout << e.what() << endl;}
		m.shortcut.show(); 
		cout << endl;
		cout << "took " << m.shortest_steps << "steps" << endl;
	}
}

