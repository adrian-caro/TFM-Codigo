#include "Segment.h"
#include <iostream>
Segment::Segment()
{

}

void Segment::setlength(float n)
{
    length=n;
}

float Segment::getlength()
{
    return length;
}


void Segment::setheight(float n)
{
    height=n;
}

void Segment::setwidth(float n)
{
    width=n;
}

void Segment::setslope(float n)
{
    slope=n;
}

void Segment::printsegments()
{
    std::cout << "Length:" << length << "\t";
    std::cout << "Height:" << height << "\t";
    std::cout << "Width:" << width << "\t";
    std::cout << "Slope:" << slope;
    std::cout << std::endl;
}
