#include "Node.h"
#include <iostream>


Node::Node(std::string t, int nn, int ne)
{
    type=t;
    numberofexits=ne;
    nodenumber=nn;
}

Node::~Node()
{

}

void Node::setnumberofexits(int n)
{
    numberofexits=n;
}


void Node::addtunnel()
{

}

void Node::printnode() //prints node info
{
    std::cout << "Nodo: " << nodenumber << " Tipo: " << type << " Number of exits: " << numberofexits << std::endl;
}
