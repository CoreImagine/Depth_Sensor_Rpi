#include "test.h"
#include<stdio.h>
#include<stdlib.h>
extern "C" int add(int a, int b)
{
	return add(a,b);
}

extern "C" int sub(int a, int b)
{
	return sub(a,b);
}
