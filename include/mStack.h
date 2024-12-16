// вектор

#pragma once

#include <iostream>
using namespace std;

template<typename T> 
class mVector
{
protected:
	size_t sz;
	size_t capacity;
	T* pMem;
public:
	mVector(size_t size = 0) : sz(size), capacity(sz * 2 + 2)
	{
		pMem = new T[capacity];
		if (pMem == nullptr)
			throw bad_alloc();
	}
	mVector(T* arr, size_t size) : sz(size), capacity(sz * 2 + 2)
	{
		if (arr == nullptr)
			throw logic_error("mVector requires non - nullptr arg");
		pMem = new T[capacity];
		if (pMem == nullptr)
			throw bad_alloc();
		copy(arr, arr + sz, pMem);
	}
	mVector(const mVector& v) : sz(v.sz), capacity(v.capacity) // это нам зочем
	{
		pMem = new T[capacity];
		if (pMem == nullptr)
			throw bad_alloc();
		copy(v.pMem, v.pMem + sz, pMem);
	}
	mVector(mVector&& v) noexcept // это нам зочем
	{
		sz = 0;
		capacity = 0;
		pMem = nullptr;
		swap(*this, v);
	}
	~mVector()
	{
		delete[] pMem;
		pMem = nullptr;
	}

	// операторы

	mVector& operator=(const mVector& v)
	{
		if (this != &v)
		{
			if (sz != v.sz)
			{
				sz = v.sz;
				capacity = v.capacity;
				delete[] pMem;
				T* p = new T[capacity];
				if (p == nullptr)
					throw bad_alloc();
				pMem = p;
			}
			copy(v.pMem, v.pMem + sz, pMem);
		}
		return (*this);
	}
	mVector& operator=(mVector&& v) noexcept
	{
		sz = 0;
		capacity = 0;
		delete[] pMem;
		pMem = nullptr;
		swap(*this, v);
		return (*this);
	}
	friend void swap(mVector& lhs, mVector& rhs)
	{
		swap(lhs.size, rhs.size);
		swap(lhs.capacity, rhs.capacity);
		swap(lhs.data, rhs.data);
	}
	size_t size() const noexcept { return sz; }
	size_t getcapacity() const noexcept { return capacity; }
	bool isFull() const noexcept { return (sz == capacity); } 
	bool isEmpty() const noexcept { return (sz == 0); } 

	// индексация
	T& operator[](size_t ind)
	{
		return pMem[ind];
	}
	const T& operator[](size_t ind) const
	{
		return pMem[ind];
	}

	// сравнение
	bool operator==(const mVector& v) const noexcept
	{
		if (sz != v.sz)
			return 0;
		else
			for (size_t i = 0; i < sz; i++)
				if (pMem[i] != v.pMem[i])
					return 0;
		return 1;
	}
	bool operator!=(const mVector& v) const noexcept
	{
		return !(*this == v);
	}
	void resize(size_t newsize)
	{
		T* p = new T[newsize * 2 + 2];
		if(p == nullptr)
			throw bad_alloc();
		copy(pMem, pMem + sz, p);
		pMem = p;
		p = nullptr;
		capacity = newsize * 2 + 2; // почему не считаем капасити сразу и не создаем сразу р от капасити
	}
	void push_back(T elem)
	{
		if (isFull())
			resize(sz + 1);
		pMem[sz++] = elem;
	}
	void pop_back()
	{
		if (isEmpty())
			throw logic_error("Vector is empty");
		else sz--;
	}
	void push_front(T elem)
	{
	    insert(elem, 0);
	}
	void pop_front()
	{
		erase(0);
	}
	void insert(T elem, size_t ind)
	{
		if (ind < 0 || ind >= capacity)
			throw out_of_range("Index should be greater than zero and less than vector size");
		if (sz == capacity)
			resize(sz + 1);
		for (size_t i = sz; i > ind; i--)
			pMem[i] = pMem[i - 1];
		pMem[ind] = elem;
		sz++;
	}
	void erase(size_t ind)
	{
		if (ind < 0 || ind >= capacity)
			throw out_of_range("Index should be greater than zero and less than vector size");
		if (sz == 0)
			throw logic_error("Vector is empty");
		for (size_t i = sz; i > ind; i++)
			pMem[i] = pMem[i + 1];
		sz--;
	}
};

// стек
template<typename T>
class mStack : private mVector<T>
{
	using mVector<T>::sz; 
	using mVector<T>::capacity;
	using mVector<T>::pMem;
	using mVector<T>::push_back;
	using mVector<T>::pop_back;
	using mVector<T>::resize;
public:
	using mVector<T>::isFull; 
	using mVector<T>::isEmpty;
	using mVector<T>::size;

	size_t getcapacity() const noexcept { return capacity; }
	mStack() : mVector<T>(0) { };
	void push(T elem)
	{
		push_back(elem);
	}
	void pop()
	{
		pop_back();
	}
	T top()
	{
		if (isEmpty())
			throw logic_error("Stack is empty");
		return pMem[sz - 1];
	}
};
