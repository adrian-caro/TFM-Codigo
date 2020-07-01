#include "Node.h"
#include <iostream>


//Node::Node(std::string t, int nn, int ne)
//{
//    type=t;
//    numberofexits=ne;
//    nodenumber=nn;
//}
Node::Node()
{

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

void Node::printexits() //Esta se va a utilizar para imprimir los tuneles que tiene un nodo
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

void Node::setexitprop(float hei, float wid, float Hori, float Vori)
{
    ExitProp.push_back({hei,wid,Hori,Vori});
}
