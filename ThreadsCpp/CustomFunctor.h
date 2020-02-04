#pragma once
class CustomFunctor
{
public:
	CustomFunctor();
	void operator()();
};

class CustomFunctorParam
{
public:
	CustomFunctorParam();
	void operator()(int* _arr, int _length);
};