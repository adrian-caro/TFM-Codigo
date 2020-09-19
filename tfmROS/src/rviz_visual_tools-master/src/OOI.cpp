#include "rviz_visual_tools/headers/OOI.h"
#include <iostream>

OOI::OOI()
{
    position_longit=0;
    position_deg=0;
    ID=0;

}
void OOI::setID(int n)
{
    ID=n;
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
    std::cout << "OOI: " << ID << "\t";
    std::cout << "\tPosition_long:" << position_longit;
    std::cout << "\tPosition_deg:" << position_deg;
    std::cout << std::endl;
}

int OOI::getID()
{
    return ID;
}
