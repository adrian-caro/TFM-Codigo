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
    std::cout << "Nodo:" << nodenumber << "\t" << "\t" << "Name:" << type << "\t" <<  "Number of exits:" << numberofexits << std::endl;

}

void Node::printexits() //Esta se va a utilizar para imprimir los tuneles que tiene un nodo
{
    // std::cout << "Exits: " << exits[]->printtunnel() << std::endl;
}

void Node::printname()
{
    std::cout << nodenumber;
}
