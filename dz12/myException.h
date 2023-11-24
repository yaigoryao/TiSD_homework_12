#pragma once
#include <exception>

namespace PIA {

	template <class T>
	class myException : public std::exception
	{
	protected:
		T data = T{};
	public:
		myException(const char* msg) : std::exception(msg) {};
		myException(const char* msg, T data) : std::exception(msg) { this->data = data; };
		virtual T errData() { return this->data; };
	};
	template <class T>
	class inputException : public myException<T>
	{
	protected:
		T data = T{};
	public:
		inputException(const char* msg) : myException(msg) {};
		inputException(const char* msg, T data) :myException(msg, data) {};
	};

	template <class T>
	class indexException : public myException<T>
	{
	protected:
		T data = T{};
	public:
		indexException(const char* msg) : myException(msg) {};
		indexException(const char* msg, T data) :myException(msg, data) {};
	};

	template <class T>
	class otherException : public myException<T>
	{
	protected:
		T data = T{};
	public:
		otherException(const char* msg) : myException(msg) {};
		otherException(const char* msg, T data) :myException(msg, data) {};
	};

	/*template<class T>
	class inputException : public myExceptionTemplate<T>
	{
	public:
		inputException(const char* msg) : std::exception(msg) {};
		inputException(const char* msg, T data) : std::exception(msg) { this->data = data; };
	};

	template<class T>
	class indexException : public myExceptionTemplate <T>
	{
	public:
		indexException(const char* msg) : std::exception(msg) {};
		indexException(const char* msg, T data) : std::exception(msg) { this->data = data; };
	};

	template<class T>
	class otherException : public myExceptionTemplate<T>
	{
	public:
		otherException(const char* msg) : std::exception(msg) {};
		otherException(const char* msg, T data) : std::exception(msg) { this->data = data; };
	};

	template<class T>
	class sizeException : public myExceptionTemplate<T>
	{
	public:
		sizeException(const char* msg) : std::exception(msg) {};
		sizeException(const char* msg, T data) : std::exception(msg) { this->data = data; };
	};*/

}
