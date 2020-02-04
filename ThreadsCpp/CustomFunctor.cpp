#include "CustomFunctor.h"
#include <iostream>
#include <sstream>

// CustomFunctor
CustomFunctor::CustomFunctor()
{
}

void CustomFunctor::operator()()
{
	std::cout << "CustomFunctor" << std::endl;
}

// CustomFunctorParam
CustomFunctorParam::CustomFunctorParam()
{
}

void CustomFunctorParam::operator()(int* _arr, int _length)
{
	std::ostringstream oss;
	for (size_t i = 0; i < _length; i++)
	{
		oss << _arr[i] << "\n";
	}
	std::cout << oss.str();
}
