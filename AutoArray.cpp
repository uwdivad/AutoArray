#include "AutoArray.h"
#include<iostream>

using namespace std;

template <class T>
AutoArray<T>::AutoArray(){
	size = 2;
	Array = new T[size];
	head = 0;
	tail = 0;
}

template <class T>
AutoArray<T>::AutoArray(AutoArray<T>& copy){
	size = copy.size;
	Array = new T[size];
	head = 0;
	tail = 0;
	for (int i = 0; i < copy._size(); i++)
		push(copy.retrieve(i));
}

template <class T>
AutoArray<T>::~AutoArray(){
	delete[] Array;
	size = 0;
	head = 0;
	tail = 0;
	Array = (T*)0;
}

template <class T>
bool AutoArray<T>::isEmpty(){
	return head == tail;
}

template <class T>
int AutoArray<T>::_size(){
	return (head - tail + size) % size;
}

template <class T>
T AutoArray<T>::retrieve(int i){
	if (i<0)
		return Array[(head + size + i) % size];
	return Array[(tail + i) % size];

}

template <class T>
void AutoArray<T>::insert(int i, T val){
	if (i<0)
		Array[(head + size + i) *size] = val;
	else
		Array[(tail + i) % size] = val;
}

template <class T>
void AutoArray<T>::push(T val){
	make_space(_size() + 1);
	Array[head] = val;
	head = (head + 1) % size;
}

template <class T>
void AutoArray<T>::push_back(T val){
	make_space(_size() + 1);
	tail = (tail + size - 1) % size;
	Array[tail] = val;
}

template <class T>
T AutoArray<T>::pop(){
	if (_size() <= 0)
		return Array[0];
	head = (head + size - 1) % size;
	return Array[head];
}

template <class T>
T AutoArray<T>::pop_back(){
	T val = Array[tail];
	tail = (tail + 1) % size;
	return val;
}

template <class T>
void AutoArray<T>::make_space(int n){
	if (size > n)
		return;
	int Size = size;
	while (Size <= n)
		Size *= 2;
	T *newArray = new T[Size];
	for (int i = 0; i < _size(); i++)
		Array = retrieve(i);
	delete[] Array;
	Array = newArray;
	head = _size();
	tail = 0;
	size = Size;
	return;
}

template <class T>
AutoArray<T> &AutoArray<T>::operator=(AutoArray<T> copy){
	delete[] Array;
	size = copy.size;
	Array = new T[size];
	head = 0;
	tail = 0;
	for (int i = 0; i < copy._size(); i++)
		push(copy.retrieve(i));
}
