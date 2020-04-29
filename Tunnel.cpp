#include "Tunnel.h"
#include "Segment.h"

#include <iostream>


Tunnel::Tunnel()
{
    length=0;
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
    //endings[0]->printname();
    std::cout << endings[0];
    std::cout << "-";
    std::cout << endings[1];
    //endings[1]->printname();
    std::cout << "\t";
    std::cout << "Length:";
    std::cout << length;
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

void Tunnel::reverseprinttunnel() //prints node info
{
    cout << "Tunnel:" << name << "\t";
    std::cout << "Ending nodes: ";
    //endings[0]->printname();
    std::cout << endings[1];
    std::cout << "-";
    std::cout << endings[0];
    //endings[1]->printname();
    std::cout << "\t";
    std::cout << "Length:";
    std::cout << length;
    std::cout << "\t";
    std::cout << "Number of segments:" << numberofsegments << std::endl;
    std::cout << std::endl;

    for (int i=numberofsegments-1;i>-1;i--)
    {
        std::cout << "\t\t-Segment " << name << "-" << (i) << "\t";
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


float Tunnel::getlength()
{
    return length;
}


void Tunnel::setstartnode(int n)
//void Tunnel::setstartnode(int n,Node *nod)
{
    endings.push_back(n);
}


void Tunnel::setfinalnode(int n)
//void Tunnel::setfinalnode(int n,Node *nod)
{
    endings.push_back(n);

    //queda añadir puntero del objecto actual al array de exits del nodo del argumento n de este metodo.
    //Hay tambien  que comprobar que no existe ya en ese array de salidas para no incluirlo dos veces
}


void Tunnel::addsegment(Segment *seg)
{
    segments.push_back(seg);

    //Segment lenght is added to the tunnel length.
    //maybe further implementation is needed when deleting segments in order to substract its lenght to tunnel length.
    length=length+seg->getlength();
}

void Tunnel::addOOI(OOI *ooi)
{
    OOIs.push_back(ooi);
}

vector<int> Tunnel::getendings()
{
    return endings;
}

int Tunnel::getnumberofsegments()
{
    return numberofsegments;
}

vector<Segment*> Tunnel::getsegments()
{
    return segments;
}
