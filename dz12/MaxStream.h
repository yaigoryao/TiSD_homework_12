#pragma once
#include <iostream>
#include <iomanip>
//#include <C:\Users\Игорь\Desktop\учеба\LabRab\ЛР ВП 2 Сем\1 ЛР\LR1\LR1\myException.h>
//#include "C:\Users\Игорь\Desktop\учеба\LabRab\ЛР ВП 2 Сем\1 ЛР\LR1\LR1\myVector.h"
//#include "C:\Users\Игорь\Desktop\учеба\LabRab\ИУК4-32Б\Типы и структуры данных\lab3\lab3\Exceptions.h"
#include "myVector.h"
#include "myException.h"
#include "Exceptions.h"
#include <fstream>
#include <queue>
#include <algorithm>

bool vectorBool(PIA::myVector<bool> v)
{
	for (int i = 0; i < v.getSize(); i++)
	{
		if (v[i] == false) return false;
	}
	return true;
}

using namespace PIA;
class MaxStream
{
private:
	static const int infinity = 899999;
	int** adjacency = nullptr;
	int dim = 0;
public:
	MaxStream()
	{
		this->adjacency = 0;
		this->dim = 0;
	}

	MaxStream(int dim)
	{
		this->dim = dim;
		if (this->adjacency)
		{
			for (int i = 0; i < dim; i++)
			{
				if (adjacency[i]) delete[] adjacency[i];
			}
		}
		this->adjacency = new int* [dim];
		for (int i = 0; i < dim; i++)
		{
			this->adjacency[i] = new int[dim];
		}
		for (int i = 0; i < dim; i++)
		{
			for (int j = 0; j < dim; j++)
			{
				this->adjacency[i][j] = 0;
			}
		}
	}

	int GetDim() const
	{
		return this->dim;
	}

	int** AdjaencyCopy() const
	{
		int** copy = new int* [this->dim];
		for (int i = 0; i < dim; i++)
		{
			this->adjacency[i] = new int[this->dim];
		}
		for (int i = 0; i < dim; i++)
		{
			for (int j = 0; j < dim; j++)
			{
				copy[i][j] = this->adjacency[i][j];
			}
		}
		return copy;
	}

	void Update(int dim)
	{
		if (dim <= 0) throw new OutOfRangeE("Размерность должна быть больше нуля");
		if (this->adjacency)
		{
			for (int i = 0; i < this->dim; i++)
			{
				if (adjacency[i]) delete[] adjacency[i];
			}
		}
		this->dim = dim;
		this->adjacency = new int* [this->dim];
		for (int i = 0; i < this->dim; i++)
		{
			this->adjacency[i] = new int[this->dim];
		}
		for (int i = 0; i < this->dim; i++)
		{
			for (int j = 0; j < this->dim; j++)
			{
				this->adjacency[i][j] = 0;
			}
		}
	}

	myVector<int> BFS(const MaxStream& gr, int beg, int end)
	{
		myVector<int> queue;
		myVector<bool> visited = myVector<bool>(gr.dim, false);
		myVector<int> dest = myVector<int>(gr.dim, 0);
		myVector<int> path_p = myVector<int>(gr.dim, 0);
		queue.pushFront(beg);
		visited[beg] = true;
		path_p[beg] = -1;
		while (!queue.empty())
		{
			int v = queue.popBack();
			for (int i = 0; i < gr.dim; i++)
			{
				if (gr.adjacency[v][i] != 0 && !visited[i])
				{
					visited[i] = true;
					queue.pushFront(i);
					dest[i] = dest[v] + 1;
					path_p[i] = v;
				}
			}
		}
		myVector<int>path = myVector<int>();
		if (path_p[end] == 0) return path;
		for (int v = end; v != -1; v = path_p[v])
		{
			path.pushBack(v);
		}
		path.reverse();
		return myVector<int>(path);
	}

	void DFS(const MaxStream& gr, myVector<int>& stack, myVector<bool>& visited, int beg, int end, bool& flag)
	{
		visited[beg] = true;
		for (int i = 0; i < gr.dim; i++)
		{
			if (!visited[i] && gr.adjacency[beg][i])
			{
				if (i == end)
				{
					flag = true;
					return;
				}
				else
				{
					stack.pushBack(i);
					DFS(gr, stack, visited, i, end, flag);
					if (flag) return;
					stack.popBack();
				}
			}
		}
	}

	myVector<int> PDFS(const MaxStream& gr, int beg, int end)
	{
		myVector<bool> visited = myVector<bool>(gr.dim, false);
		myVector<int> stack = myVector<int>();
		stack.pushBack(beg);
		bool flag = false;
		DFS(gr, stack, visited, beg, end, flag);
		stack.pushBack(end);
		return stack;//myVector<int>(path);
	}

	void AddVertexAuto(int prevCtr, int* prev)
	{
		int** temp = new int* [this->dim + 1];
		for (int i = 0; i < this->dim + 1; i++)
		{
			temp[i] = new int[this->dim + 1];
		}
		for (int i = 0; i < this->dim; i++)
		{
			for (int j = 0; j < this->dim; j++)
			{
				temp[i][j] = adjacency[i][j];
			}
		}
		this->dim += 1;
		for (int i = 0; i < this->dim; i++)
		{
			temp[i][this->dim - 1] = 0;
		}
		for (int i = 0; i < this->dim; i++)
		{
			temp[this->dim - 1][i] = 0;
		}
		for (int i = 0; i < prevCtr; i++)
		{
			temp[prev[i]][this->dim - 1] = 999999;
		}
		temp[dim - 1][dim - 1] = 0;

		if (this->adjacency)
		{
			for (int i = 0; i < this->dim - 1; i++)
			{
				if (this->adjacency[i]) delete[] this->adjacency[i];
			}
		}
		this->adjacency = temp;
	}

	MaxStream FloydWarshell(int source, int drain)
	{
		try
		{
			MaxStream temp = *this;
			//temp.AddVertexAuto(drainCtr, drains);
			std::cout << "Изначальная сеть: " << std::endl;
			temp.Print();
			int dest = drain;
			myVector<int> path = myVector<int>(1, 0);
			int maxStream = 0;
			int ctr = 1;
			while (!path.empty())
			{
				path.clear();
				//path = BFS(temp, source, dest);////////////////////////////////////////////////////
				//if (path.getSize() <= 1) break;////////////////////////////////////////////////////


				path = PDFS(temp, source, dest);/////////////////////////////////////////////////////
				if (path.getSize() <= 2) break;//////////////////////////////////////////////////////
				
				
				path.popBack();
				path.pushBack(dest);
				int minStr = 99999;
				for (int i = 0; i < path.getSize() - 1; i++)
				{
					int pathcost = temp.adjacency[path[i]][path[i + 1]];
					if (minStr > temp.adjacency[path[i]][path[i + 1]] && temp.adjacency[path[i]][path[i + 1]] != 0)
						minStr = temp.adjacency[path[i]][path[i + 1]];
				}
				maxStream += minStr;
				std::cout << std::endl << "Шаг №" << ctr << std::endl;
				for (int i = 0; i < path.getSize() - 1; i++)
				{
					temp.adjacency[path[i]][path[i + 1]] -= minStr;
					temp.adjacency[path[i + 1]][path[i]] += minStr;
				}
				std::cout << "Исток -> сток: ";
				for (auto& e : path) std::cout << e;
				std::cout << std::endl << "MAX поток через сеть: ";
				std::cout << minStr << std::endl;
				std::cout << "Остаточная сеть: " << std::endl;
				temp.Print();
				ctr++;
			}
			std::cout << "Максимальный поток = " << maxStream << std::endl;
		}
		catch (...)
		{
			throw new BaseE("Ошибка выполнения алгоритма");
			return MaxStream();
		}
	}
	bool Empty()
	{
		if (this->dim == 0) return true;
		else return false;
	}
	void Print() const
	{
		if (!this->adjacency) throw new BaseE("Сеть пуста");
		for (int i = 0; i < dim + 1; i++)
		{
			for (int j = 0; j < dim + 1; j++)
			{
				if (i == 0 && j == 0)
				{
					std::cout << std::setw(7) << std::resetiosflags(std::ios::left) << 'г';
				}
				else if (i == 0 || j == 0)
				{
					std::cout << std::setw(7) << std::resetiosflags(std::ios::left) << (-1 + i + j);//(char)('A' - 1 + i + j);
				}
				else
				{
					if (adjacency[i - 1][j - 1] < infinity)
						std::cout << std::setw(7) << std::resetiosflags(std::ios::left) << adjacency[i - 1][j - 1];
					else
						std::cout << std::setw(7) << std::resetiosflags(std::ios::left) << "\u221E";
				}
			}
			std::cout << std::endl;
		}
	}

	void WriteInFile(const char* path) const
	{
		try
		{
			std::ofstream fout;
			fout.open(path);
			if (!this->adjacency) throw new BaseE("Сеть пуста");
			for (int i = 0; i < dim + 1; i++)
			{
				for (int j = 0; j < dim + 1; j++)
				{
					if (i == 0 && j == 0)
					{
						fout << std::setw(3) << 'г';
					}
					else if (i == 0 || j == 0)
					{
						fout << std::setw(3) << (char)('A' - 1 + i + j);
					}
					else
					{
						fout << std::setw(3) << adjacency[i - 1][j - 1];
					}
				}
				fout << std::endl;
			}
			fout.close();
		}
		catch (std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
			std::cout << "Произошла ошибка записи в файл!" << std::endl;
		}
	}

	void Clear()
	{
		if (this->adjacency)
		{
			for (int i = 0; i < this->dim; i++)
			{
				if (this->adjacency[i]) delete adjacency[i];
			}
		}
		this->dim = 0;
	}

	void ReadFromFile(const char* path)
	{
		try
		{
			this->Clear();
			std::ifstream fin;
			fin.open(path);
			fin >> this->dim;
			this->Update(this->dim);
			for (int i = 0; i < this->dim; i++)
			{
				for (int j = 0; j < this->dim; j++)
				{
					fin >> this->adjacency[i][j];
				}
			}
			fin.close();
		}
		catch (...)
		{
			std::cout << "Произошла ошибка считывания файла" << std::endl;
		}
	}

	MaxStream(const MaxStream& other)
	{
		this->dim = other.dim;
		if (this->adjacency)
		{
			for (int i = 0; i < dim; i++)
			{
				if (adjacency[i]) delete[] adjacency[i];
			}
		}
		if (other.adjacency)
		{
			this->adjacency = new int* [dim];
			for (int i = 0; i < this->dim; i++)
			{
				this->adjacency[i] = new int[dim];
			}
			for (int i = 0; i < dim; i++)
			{
				for (int j = 0; j < dim; j++)
				{
					this->adjacency[i][j] = other.adjacency[i][j];
				}
			}
		}
		else this->adjacency = nullptr;
	}

	MaxStream(MaxStream&& other)
	{
		this->dim = other.dim;
		if (this->adjacency)
		{
			for (int i = 0; i < dim; i++)
			{
				if (adjacency[i]) delete[] adjacency[i];
			}
		}
		if (other.adjacency)
		{
			this->adjacency = new int* [dim];
			for (int i = 0; i < this->dim; i++)
			{
				this->adjacency[i] = new int[dim];
			}
			for (int i = 0; i < dim; i++)
			{
				for (int j = 0; j < dim; j++)
				{
					this->adjacency[i][j] = other.adjacency[i][j];
				}
			}
		}
		else this->adjacency = nullptr;
		other.dim = 0;
		for (int i = 0; i < other.dim; i++)
		{
			delete[] other.adjacency[i];
		}
		other.adjacency = nullptr;
	}
};

