#pragma once
#include<vector>
#include<string>
#include<exception>

class MatrixException : public std::exception
{
public:
	MatrixException(std::string s) : err_msg(s) {}
	virtual const char* what() const throw() { return err_msg.c_str(); }

protected:
	std::string err_msg;
};

template <typename T>
class Matrix
{
public:
	Matrix(int w, int h);
	Matrix(std::vector<std::vector<T>> v);
	virtual ~Matrix();
	Matrix<T> operator+(const Matrix<T>& r) const;
	Matrix<T> operator-(const Matrix<T>& r) const;
	
protected:
	T** arr;
	int width, height;

private:
	void alloc();
	void release();
};
