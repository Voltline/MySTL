#pragma once
#include <exception>

class LengthErrorException : public std::exception
{
	const char* what() const throw ()
	{
		return "LengthError";
	}
};

class IteratorErrorException : public std::exception
{
	const char* what() const throw ()
	{
		return "IteratorError";
	}
};