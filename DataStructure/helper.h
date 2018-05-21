#pragma once

#include <Windows.h>

// there is some useful function for liner list
template<class T>
void change_lenghth_1_d(T*& a, int old_length, int new_length)
{ // change the linear list size
	if (new_length < 0)
	{
		return;
	}

	// create new temp array that size is new_length
	T* temp = new T[new_length];
	auto const number = old_length > new_length ? old_length : new_length;
	for (auto i = 0; i < number; i++)
	{
		temp[i] = a[i];
	}
	delete[]a;
	a = temp;
}

template <class T>
void make_2d_array(T ** &data, int rows, int columns)
{
	// create pointers for the rows
	data = new T*[rows];

	// get memory for each row
	for (auto i = 0; i < rows; i++)
	{
		data[i] = new T[columns];
	}
}

template <class T>
void delete_2d_array(T ** &data, int rows)
{
	// delete the memory for each row
	for (auto i = 0; i < rows; i++)
	{
		delete[] data[i];
	}
	// delete the row pointers
	delete[] data;
	data = 0;
}

//inline void output_debug(const string& output)
//{
//	OutputDebugStringA(output.c_str());
//}