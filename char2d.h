#pragma once
#define WALL '#'
#define ROAD ' '
#define STEP '.'
#define SHORTCUT '>'
#define OUTOFBOUND 'B'

class Char2D
{
public:
	Char2D(int w, int h);
	Char2D(const Char2D& c);
	~Char2D();
	char& operator()(int x, int y);
	Char2D operator=(const Char2D& c);
	void show();

protected:
	char** p_char2d = nullptr;
	int width, height;
	void release();
	void alloc();

private:
	char outofbound = 'B';
};
