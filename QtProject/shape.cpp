#include "shape.h"

int Shape::count = 0;

Shape::Shape()
{
    count++;
    num = count;
}

Shape::~Shape()
{
    count--;
}
