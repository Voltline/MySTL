#pragma once
#include <exception>

class LengthErrorException : public std::exception
{
	const char* what() const throw ()
	{
		return "LengthError";
	}
};

class OutOfRangeException : public std::exception
{
	const char* what() const throw ()
	{
		return "Out of Range Error";
	}
};

class IteratorErrorException : public std::exception
{
	const char* what() const throw ()
	{
		return "IteratorError";
	}
};

class IteratorOutOfRangeException : public std::exception
{
	const char* what() const throw ()
	{
		return "IteratorOutOfRange";
	}
};