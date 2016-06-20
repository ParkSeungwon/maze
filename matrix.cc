#include<iostream>
#include"matrix.h"
using namespace std;

template <typename T>
Matrix<T>::Matrix(int w, int h)
{
	width = w;
	height = h;
	alloc();
}

template <typename T>
Matrix<T>::Matrix(vector<vector<T>> v)
{
	height = v.size();
	width = v[0].size();
	alloc();
	for(int y=0; y<height; y++) {
		for(int x=0; x<width; x++) {
			arr[y][x] = v[y][x];
		}
	}
}

template <typename T>
void Matrix<T>::alloc()
{
	arr = new T*[height];
	for(int i=0; i<height; i++) arr[i] = new T[width];
}

template <typename T>
void Matrix<T>::release() 
{
	for(int i=0; i<height; i++) delete [] arr[i];
	delete arr;
}

template <typename T>
Matrix<T>::~Matrix() {
	release();
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& r) const
{
	if(width != r.width || height != r.height) throw MatrixException("w, h does not match");
	Matrix<T> m;
	for(int y=0; y<height; y++) {
		for(int x=0; x<width; x++) {
			m[y][x] = arr[y][x] + r.arr[y][x];
		}
	}
	return m;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& r) const
{
	if(width != r.width || height != r.height) throw MatrixException("w, h does not match");
	Matrix<T> m;
	for(int y=0; y<height; y++) {
		for(int x=0; x<width; x++) {
			m[y][x] = arr[y][x] - r.arr[y][x];
		}
	}
	return m;
}



