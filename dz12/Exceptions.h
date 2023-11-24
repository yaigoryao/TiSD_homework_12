#pragma once
#include <exception>
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <chrono>
#include <ctime>

#pragma warning(disable : 4996)
class BaseE : std::exception
{
protected:
	const char* message = "";
public:
	BaseE()
	{
	}
	BaseE(const char* msg)
	{
		try {


			std::ofstream fout;
			fout.open("exception.txt", std::ios_base::app);
			if (fout.is_open()) {
				fout << "\n";
				std::time_t end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
				fout << msg << ' ' << ctime(&end_time);
			}
			fout.close();
		}
		catch (...) {

		}
		message = msg;
	}
	virtual const char* what() const
	{
		return message;
	}
};
class OutOfRangeE : BaseE
{
private:
public:
	OutOfRangeE()
	{
	}
	OutOfRangeE(const char* msg) : BaseE(msg)
	{

	}
	virtual const char* what() const override
	{
		return BaseE(message).what();
	};
};
template <class T>
class TypeErrorE : BaseE
{
private:
	const char* targetType = typeid(T).name();
public:
	TypeErrorE()
	{
		targetType = typeid(T).name();
	}
	TypeErrorE(const char* msg) : BaseE(msg)
	{
		targetType = typeid(T).name();
	}
	const char* GetTargetType() const
	{
		return targetType;
	}
	virtual const char* what() const override
	{
		return BaseE(message).what();
	};
};

class InputErrorE : BaseE
{
private:
public:
	InputErrorE()
	{
	}
	InputErrorE(const char* msg) : BaseE(msg)
	{
	}
	virtual const char* what() const override
	{
		return BaseE(message).what();
	};
};

class NodeE : BaseE
{
private:
public:
	NodeE()
	{
	}
	NodeE(const char* msg) : BaseE(msg)
	{
	}
	virtual const char* what() const override
	{
		return BaseE(message).what();
	};
};