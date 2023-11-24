#pragma once
#include <iostream>
#include "myException.h"
namespace PIA 
{
	template <class T>

	class myVector
	{
	private:
		T* vect = nullptr;
		unsigned int size = 0;
		unsigned int capacity = 2;

		bool addMemory() 
		{
			if (this->size + 1 >= this->capacity)
			{
				this->capacity = 2 * (this->size + 1);
				T* temp = this->vect;
				this->vect = new T[capacity];
				for (int i = 0; i < this->size; i++)
				{
					this->vect[i] = temp[i];
				}
				delete[] temp;
				return true;
			}
			else return false;
		}

	public:

		class mvIterator
		{
			T* current;
		public:
			mvIterator(T* vect) { current = vect; }

			T& operator+ (int n) { return *(current + n); }
			T& operator- (int n) { return *(current - n); }
			T& operator++(int) { return*current++; }
			T& operator--(int) { return*current--; }
			T& operator++() { return*++current; }
			T& operator--() { return*--current; }

			bool operator==(const mvIterator& other) const { return current == other.current; }
			bool operator!=(const mvIterator& other) const { return current != other.current; }

			T& operator*() const { return *current; }
		};

		mvIterator begin() { return mvIterator(vect); }
		mvIterator end() { return  mvIterator(vect+size); }

		myVector()
		{
			this->size = 0;
			this->capacity = 2 * (this->size + 1);
			this->vect = new T[capacity];
		}

		myVector(unsigned size) 
		{
			this->size = size;
			this->capacity = 2 * (this->size + 1);
			this->vect = new T[capacity];
		}

		myVector(unsigned size, int val)
		{
			this->size = size;
			this->capacity = 2 * (this->size + 1);
			this->vect = new T[capacity];
			for (int i = 0; i < size; i++)
			{
				this->vect[i] = val;
			}
		}

		/*void pushBack(T& data)
		{
			addMemory();
			this->vect[this->size] = data;
			this->size++;
		}*/

		void pushBack(T data)
		{
			addMemory();
			this->vect[this->size] = data;
			this->size++;
		}
			
		T popBack()
		{
			if (this->size == 0) throw myException<int>("Вектор не содержит элементов");
			this->size--;
			//return this->vect[this->size-1];
			return this->vect[this->size];
		}

		/*void pushFront(T& data)
		{
			addMemory();
			for (int i = this->size-1; i <= 0; i++) 
			{
				this->vect[i + 1] = this->vect[i];
			}
			this->vect[0] = data;
			this->size++;
		}*/

		/*void pushFront(T data)
		{
			addMemory();
			if (this->size == 0) 
			{
				this->vect[0] = data;
			}
			else
			{
				for (int i = this->size - 1; i <= 0; i++)
				{
					this->vect[i + 1] = this->vect[i];
				}
				this->vect[0] = data;
			}
			this->size++;
		}*/
		void pushFront(T data)
		{
			addMemory();
			if (this->size == 0)
			{
				this->vect[0] = data;
			}
			else
			{
				for (int i = this->size; i > 0; i--)
				{
					this->vect[i] = this->vect[i-1];
				}
				/*for (int i = 0; i<this->size - 1; i++)
				{
					this->vect[this->size - i] = this->vect[this->size - i - 1];
				}*/
				/*for (int i = this->size - 1; i <= 0; i--)
				{
					this->vect[i + 1] = this->vect[i];
				}*/
				this->vect[0] = data;
			}
			this->size++;
		}

		T popFront()
		{
			if (this->size == 0) throw myException<int>("Вектор не содержит элементов");
			T tmp = vect[0];
			for (int i = 0; i < this->size - 1; i++)
			{
				this->vect[i] = this->vect[i + 1];
			}
			this->size--;
			return tmp;
		}

		void remove(unsigned index)
		{
			//if (index > this->size || this->size == 0) return;
			if (index >= this->size) throw myException<int>("Индекс за пределами вектора", index);
			if (this->size == 0) throw myException<int>("Вектор не содержит элементов");
			for (int i = index + 1; i < this->size; i++) 
			{
				this->vect[i - 1] = this->vect[i];
			}
			this->size--;
		}
		
		void insert(T& data, unsigned index)
		{
			if (index >= this->size) throw myException<int>("Индекс за пределами вектора", index);
			addMemory();
			for (int i = this->size - 1; i <= index; i--)
			{
				this->vect[i + 1] = this->vect[i];
			}
			this->vect[index] = data;
			this->size++;
		}

		void insert(T data, unsigned index)
		{
			if (index >= this->size) throw myException<int>("Индекс за пределами вектора", index);
			addMemory();
			for (int i = this->size - 1; i <= index; i--)
			{
				this->vect[i + 1] = this->vect[i];
			}
			this->vect[index] = data;
			this->size++;
		}
		/*myVector()
		{
			vect = nullptr;
			size = 0;
		}

		myVector(unsigned int size)
		{
			this->size = size;
			vect = new T[this->size];
			for (int i = 0; i < this->size; i++)
				vect[i] = {};
		}*/

		//myVector(unsigned int size, const T& value)
		//{
		//	this->size = size;
		//	vect = new T[this->size];
		//	for (int i = 0; i < this->size; i++)
		//		vect[i] = value;
		//}

		//void fill(unsigned int pos, unsigned int range, const T& value)
		//{
		//	if (this->size <= pos) return;
		//	if (this->size <= range) {
		//		for (int i = 0; i < range; i++) {
		//			this->vect[i + pos] = value;
		//		}
		//		return;
		//	}
		//	for (int i = 0; i < range; i++) {
		//		this->vect[i + pos] = value;
		//	}
		//}
		//myVector(T* arr, unsigned int size)
		//{
		//	this->size = size;
		//	vect = new T[this->size];
		//	for (int i = 0; i < this->size; i++) {
		//		vect[i] = arr[i];
		//	}
		//};

		//myVector(T* arr)
		//{
		//	this->size = sizeof(arr) / sizeof(arr[0]);
		//	vect = new T[this->size];
		//	for (int i = 0; i < this->size; i++) {
		//		vect[i] = arr[i];
		//	}
		//}

		/*~myVector()
		{
			if (vect != nullptr) delete[] vect;
		}*/

		unsigned getSize() const { return this->size; }

		unsigned getCapacity() const { return this->capacity; }
		/////////////////////////////////////////
		//void pushFront(T data)
		//{
		//	T* buff = new T[++size];
		//	buff[0] = data;
		//	for (int i = 0; i < size - 1; i++) {
		//		buff[i + 1] = vect[i];
		//	}
		//	delete[] vect;
		//	vect = buff;
		//}

		//void pushBack(T data)
		//{
		//	T* buff = new T[++size];
		//	buff[size - 1] = data;
		//	for (int i = 0; i < size - 1; i++) {
		//		buff[i] = vect[i];
		//	}
		//	delete[] vect;
		//	vect = buff;
		//}

		//void popFront()
		//{
		//	T* buff = new T[--size];
		//	for (int i = 0; i < size; i++) {
		//		buff[i] = vect[i + 1];
		//	}
		//	delete[] vect;
		//	vect = buff;
		//}

		//void popBack()
		//{
		//	T* buff = new T[--size];
		//	for (int i = 0; i < size; i++) {
		//		buff[i] = vect[i];
		//	}
		//	delete[] vect;
		//	vect = buff;
		//}
		////////////////////////////////////////////
		//void insert(T data, unsigned int pos)
		//{
		//	T* buff = new T[++size];
		//	int i = 0, j = 0;
		//	for (i = 0, j = 0; i < size; i++, j++) {
		//		if (i == pos) {
		//			buff[i] = data;
		//			i++;
		//		}
		//		buff[i] = vect[j];
		//	}
		//	delete[] vect;
		//	vect = buff;
		//}
		//////////////////////////////////////////
		void bubbleSort()
		{
			int ctr = this->size;
			while (ctr--) {
				bool swapped = false;
				for (int i = 0; i < ctr; i++) {
					if (vect[i] > vect[i + 1]) {
						std::swap(vect[i], vect[i + 1]);
						swapped = true;
					}
				}
				if (!swapped)
					break;
			}
		}

		void reverseBubbleSort()
		{
			int ctr = this->size;
			bubbleSort();
			for (int i = 0; i < ctr / 2; i++) {
				std::swap(vect[i], vect[ctr - (i + 1)]);
			}
		}
		void clear()
		{
			this->size = 0;
			this->capacity = 2 * (this->size + 1);
			delete[] this->vect;
			this->vect = new T[this->capacity];
		}
		////////
		//void clear()
		//{
		//	delete[] vect;
		//	vect = nullptr;
		//	size = 0;
		//}
		/////////////////////////////
		//void remove(unsigned int pos)
		//{
		//	if (this->size == 0 || this->vect == nullptr) return;
		//	if (pos >= size) return;
		//	T* buff = new T[--size];
		//	unsigned int i = 0, j = 0;
		//	//for (i = 0, j = 0; j < size + 1; i++, j++) {
		//	//	if (j == pos) {
		//	//		i--;
		//	//		continue;
		//	//	}
		//	//	buff[i] = vect[j];
		//	//}
		//	for (i = 0, j = 0; j < size + 1; i++, j++) {
		//		if (j == pos)
		//			j++;
		//		buff[i] = vect[j];
		//	}
		//	delete[] vect;
		//	vect = buff;
		//}
		/////////////////////////////////
		/*void remove(unsigned int pos, unsigned int range)
		{
			if (this->size == 0 || this->vect == nullptr) return;
			if (range >= size) {
				this->size = 0;
				delete[] vect;
				vect = nullptr;
				return;
			}

			this->size -= range;
			T* buff = new T[size];
			unsigned int i = 0, j = 0;
			for (i = 0, j = 0; j < size + range; i++, j++) {
				if (i == pos) {
					for (unsigned int k = 0; k < range; k++) {
						j++;
					}
				}
				buff[i] = vect[j];
			}
			delete[] vect;
			vect = buff;
		}*/

		void reverse()
		{
			for (unsigned int i = 0; i < this->size / 2; i++) {
				std::swap(this->vect[i], this->vect[size - (i + 1)]);
			}
		}

		void print() const
		{
			for (unsigned int i = 0; i < size; i++) {
				std::cout << vect[i] << ' ';
			}
		}

		T& operator[](unsigned index) 
		{ 
			if (index >= this->size) throw myException<int>("Индекс за пределами вектора", index);
			if (this->size == 0) throw myException<int>("Вектор не содержит элементов");
			return vect[index]; 
		}
		const T& operator[](unsigned index) const 
		{ 
			if (index >= this->size) throw myException<int>("Индекс за пределами вектора", index);
			if (this->size == 0) throw myException<int>("Вектор не содержит элементов");
			return vect[index]; 
		}

		//myVector& operator=(std::initializer_list<T> list) 
		//{
		//	this->size = (unsigned int)list.size();
		//	if(this->vect != nullptr) delete[] this->vect;
		//	vect = new T[this->size];
		//	auto it = list.begin();
		//	for (unsigned int i = 0; i < this->size; i++) {
		//		this->vect[i] = *it;
		//		it++;
		//	}
		//	return *this;
		//}

		//myVector& operator=(const myVector& other) 
		//{
		//	this->size = other.size;
		//	this->vect = new T[this->size];
		//	for (int i = 0; i < this->size; i++) {
		//		this->vect[i] = other.vect[i];
		//	}
		//	return *this;
		//}

		/*myVector(myVector&& other) noexcept
		{
			if (this != &other) 
			{
				delete[] this->vect;
				this->vect = other.vect;
				this->size = other.size;
				this->capacity = other.capacity;
				other.vect = nullptr;
				other.size = other.capacity = 0;
			}
		}*/
		//myVector(myVector&& other) //noexcept
		//{
		//	if (this != &other)
		//	{
		//		delete[] this->vect;
		//		this->vect = nullptr;
		//		this->vect = new int[other.size];
		//		for (int i = 0; i < other.size; i++)
		//		{
		//			this->vect[i] = other.vect[i];
		//		}
		//		//this->vect = other.vect;
		//		this->size = other.size;
		//		this->capacity = other.capacity;
		//		delete[] other.vect;
		//		other.vect = nullptr;
		//		other.size = other.capacity = 0;
		//		// other.size = other.capacity = 0;
		//	}
		//}

		~myVector()
		{
			if (this->vect != nullptr)
			{
				delete[] this->vect;
				this->size = 0;
				this->capacity = 0;
				this->vect = nullptr;
			}
		}

		myVector(const myVector& other)
		{
			//if (this != &other)
			//{
			//if (this->vect) 
			//delete[] this->vect;
			this->vect = new T[other.capacity];
			for (int i = 0; i < other.size; i++)
			{
				this->vect[i] = other.vect[i];
			}
			this->size = other.size;
			this->capacity = other.capacity;
			//}
		}

		myVector(myVector&& other) noexcept
		{
			this->vect = other.vect;
			this->size = other.size;
			this->capacity = other.capacity;
			other.size = other.capacity = 0;
			other.vect = nullptr;
		}

		myVector& operator=(const myVector& other)
		{
			if (this != &other)
			{
				if (this->vect) delete[] this->vect;
				this->vect = new T[other.capacity];
				for (int i = 0; i < other.size; i++)
				{
					this->vect[i] = other.vect[i];
				}
				this->size = other.size;
				this->capacity = other.capacity;
			}
			return *this;
		}

		/*myVector& operator=(myVector&& other) noexcept
		{
			if (this != &other)
			{
				delete[] this->vect;
				this->vect = other.vect;
				this->size = other.size;
				this->capacity = other.capacity;
				delete[] other.vect;
				other.vect = nullptr;
				other.size = other.capacity = 0;
			}
			return *this;
		}*/

		bool empty() const {
			return (this->size == 0);//&& this->vect == nullptr);
		}

		void swap(unsigned int pos1, unsigned int pos2) {
			//if (pos1 >= size || pos2 >= size) return;
			if (pos1 >= this->size) throw myException<int>("Индекс за пределами вектора", pos1);
			if (pos2 >= this->size) throw myException<int>("Индекс за пределами вектора", pos2);
			if (this->size == 0) throw myException<int>("Вектор не содержит элементов");
			std::swap(vect[pos1], vect[pos2]);
		}

		//friend std::ostream& operator<< (std::ostream& out, const myVector& vect);

		//void reserve(unsigned int size)
		//{
		//	if (size == 0)
		//	{
		//		this->size = 0;
		//		this->vect = nullptr;
		//	}
		//	else
		//	{
		//		this->size = size;
		//		this->vect = new T[size];
		//		for (int i = 0; i < this->size; i++) {
		//			vect[i] = {};
		//		}
		//	}
		//}
	};

	//template <class T>
	//std::ostream& operator<<(std::ostream& out, myVector<T>& const vect)
	//{
	//	for (int i = 0; i < vect.getSize(); i++) {
	//		out << vect[i] << ' ';
	//	}
	//	return out;
	//}
}

