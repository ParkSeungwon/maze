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
	Maze m(w, h);
	while(true) {
		m.build_maze();
		//m.show();
		//cout << endl;
		m.find_way(1, 0);
		if(m(w-2, h-1) == STEP) {
			m.show();
			cout << endl;
			m.best_way(1, 0);
			m.shortcut.show(); 
			cout << endl;
			cout << "built maze " << m.build << " times" << endl;
			cout << "took " << m.shortest_steps << " steps" << endl;
			cout << "wandered " << m.wander << " times" << endl;
			break;
		} 
	}
}

