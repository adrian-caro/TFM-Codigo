#include "OOI.h"
#include <iostream>

OOI::OOI()
{

}
void OOI::setname(std::string n)
{
    name=n;
}

void OOI::setshape(std::string n)
{
    shape=n;
}

void OOI::setposition_longit(float n)
{
    position_longit=n;
}

void OOI::setposition_deg(float n)
{
    position_deg=n;
}

void OOI::printOOI() //prints node info
{
    std::cout << "OOI:" << name << "\t";
    std::cout << "\tShape:" << shape;
    std::cout << "\tPosition_long:" << position_longit;
    std::cout << "\tPosition_deg:" << position_deg;
    std::cout << std::endl;
}
