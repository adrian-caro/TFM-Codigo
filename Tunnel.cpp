#include "Tunnel.h"
#include "Segment.h"

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
    cout << "Tunnel:" << name << "\t";
    std::cout << "Ending nodes: ";
    endings[0]->printname();
    std::cout << "-";
    endings[1]->printname();
    std::cout << "\t";
    std::cout << "Number of segments:" << numberofsegments << std::endl;
    std::cout << std::endl;

    for (int i=0;i<numberofsegments;i++)
    {
        std::cout << "\t\t-Segment " << name << "-" << (i+1) << "\t";
        segments[i]->printsegments();
        //std::cout << std::endl;
    }
    std::cout << std::endl;std::cout << std::endl;
}

void Tunnel::setname(std::string n)
{
    name=n;
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


void Tunnel::addsegment(Segment *seg)
{
    segments.push_back(seg);
}

