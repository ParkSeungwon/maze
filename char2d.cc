#include "char2d.h"
#include <iostream>
#include <exception>
using namespace std;

Char2D::Char2D(int w, int h)
{
	if(w < 3) w = 3;
	if(h < 3) h = 3;
	width = w; height = h;
	alloc();
}

Char2D::Char2D(const Char2D& c)
{//생성자에서 = 연산자를 쓸 수없다. 무한순환
	width = c.width; height = c.height;
	alloc();
	for(int y=0; y<height; y++) {
		for(int x=0; x<width; x++) p_char2d[y][x] = c.p_char2d[y][x];
	}
}

Char2D::~Char2D()
{
	release();
}

void Char2D::release()
{
	if(p_char2d != nullptr) {
		for(int y=0; y<height; y++) delete [] p_char2d[y];
		delete [] p_char2d;
	}
}

void Char2D::alloc()
{
	p_char2d = new char*[height];
	for(int y=0; y<height; y++) p_char2d[y] = new char[width];
}

char& Char2D::operator()(int x, int y)
{
	if(x < 0 || x >= width) return outofbound;
	if(y < 0 || y >= height) return outofbound;
	return p_char2d[y][x];
}

Char2D Char2D::operator=(const Char2D& c)
{
	if(width != c.width || height != c.height) {
		release();
		width = c.width; height = c.height;
		alloc();
	} 
	for(int y=0; y<height; y++) {
		for(int x=0; x<width; x++) p_char2d[y][x] = c.p_char2d[y][x];
	}
	return *this;
}

void Char2D::show()
{
	for(int y=0; y<height; y++) {
		for(int x=0; x<width; x++) {
			cout << p_char2d[y][x];
		}
		cout << endl;
	}
}


