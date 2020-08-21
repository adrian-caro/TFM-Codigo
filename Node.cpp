#include "Node.h"
#include <iostream>

Node::Node()
{
    nodenumber=0;
    height=0;
    width=0;
    numberofexits=0;
}

Node::~Node()
{

}

void Node::settype(std::string n)
{
    type=n;
}

void Node::setnumberofexits(int n)
{
    numberofexits=n;

}

void Node::setnodenumber(int n)
{
    nodenumber=n;
}


void Node::addtunnel()
{

}

void Node::printnode() //prints node info
{
    std::cout << "Node:" << nodenumber << "\t" << " Name:" << type;
    std::cout << "\t" <<  "Number of exits:" << numberofexits << std::endl;
    std::cout << std::endl;

    for (int i=0;i<numberofexits;i++)
    {

        std::cout << "\t\t-Node Exit " << (i+1) << "\t";
        std::cout << "Height:" << ExitProp[i].at(0) << "\t";
        std::cout << "Width:" << ExitProp[i].at(1) << "\t";
        std::cout << "Hor. orientation:" << ExitProp[i].at(2) << "\t";
        std::cout << "Ver. orientation:" << ExitProp[i].at(3)<< std::endl;


    }std::cout << std::endl;
}

void Node::printexits()
{
    // std::cout << "Exits: " << exits[]->printtunnel() << std::endl;
}

void Node::printname()
{
    std::cout << nodenumber;
}

void Node::addOOI(OOI *ooi)
{
    OOIs.push_back(ooi);
}

void Node::setheight(float n)
{
    height=n;
}

void Node::setwidth(float n)
{
    width=n;
}

void Node::setexitprop(int connectednode, float hei, float wid, float Hori, float Vori)
{
    ExitProp.push_back({connectednode, hei,wid,Hori,Vori});
}

void Node::addnodoconectado(int n)
{
    nodosconectados.push_back(n);
}

float Node::getexitprop(int salida, int prop)
{
    return ExitProp[salida].at(prop);
}

int Node::getnodenumber()
{
    return nodenumber;
}

int Node::getnumberofexits()
{
    return numberofexits;
}

string Node::gettype()
{
    return type;
}

void Node::setcoordinates(int x, int y, int z)
{
    coordinates.push_back(x);
    coordinates.push_back(y);
    coordinates.push_back(z);
}

vector<int> Node::getcoordinates()
{

    return coordinates;
}

int Node::getnumberofOOI()
{
    return OOIs.size();
}

int Node::getOOI_ID(int n)
{
    return OOIs[n]->getID();
}
