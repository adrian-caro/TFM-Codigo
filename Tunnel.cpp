#include "Tunnel.h"
#include <iostream>


Tunnel::Tunnel(std::string nam, int len, int slo,int hei, int wid, int num)
{
    name=nam;
    length=len;
    slope=slo;
    height=hei;
    width=wid;
    numberofsegments=num;

}

Tunnel::~Tunnel()
{

}


void Tunnel::printtunnel() //prints node info
{
    std::cout << "Tunnel:" << name;
    std::cout <<" Length:" << length << " Width:" << width <<" Height:" << height << " Slope:" << slope << " Number of segments:" << numberofsegments << std::endl;

}
