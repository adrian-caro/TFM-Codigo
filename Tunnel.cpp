#include "Tunnel.h"
#include <iostream>

Tunnel::Tunnel()
{

}
//Tunnel::Tunnel(std::string nam, int len, int slo,int hei, int wid, int num)
//{
//    name=nam;
//    length=len;
//    slope=slo;
//    height=hei;
//    width=wid;
//    numberofsegments=num;

//}

Tunnel::~Tunnel()
{

}


void Tunnel::printtunnel() //prints node info
{
    std::cout << "Tunnel:" << name;
    std::cout <<" Length:" << length << " Width:" << width <<" Height:" << height << " Slope:" << slope << " Number of segments:" << numberofsegments << std::endl;
    std::cout << "Ending nodes: ";
    endings[0]->printname();
    std::cout << " and ";
    endings[1]->printname();
    std::cout << std::endl;
}

void Tunnel::setname(std::string n)
{
    name=n;
}

void Tunnel::setlength(float n)
{
    length=n;
}

void Tunnel::setheight(float n)
{
    height=n;
}

void Tunnel::setwidth(float n)
{
    width=n;
}

void Tunnel::setslope(float n)
{
    slope=n;
}

void Tunnel::setnumberofsegments(int n)
{
    numberofsegments=n;
}

void Tunnel::setstartnode(int n,Node *nod)
{
    endings[0]=&nod[n];
}

void Tunnel::setfinalnode(int n,Node *nod)
{
    endings[1]=&nod[n];

    //queda añadir puntero del objecto actual al array de exits del nodo del argumento n de este metodo.
    //Hay tambien  que comprobar que no existe ya en ese array de salidas para no incluirlo dos veces
}
