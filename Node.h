#ifndef NODE
#define NODE
#include <string>
#include "Tunnel.h"
class Node{

private: 
        std::string type;
        int nodenumber;
        int numberofexits;
        float position[3];
        Tunnel *exits[];
public:
    Node(std::string t, int nn, int ne);
    ~Node();
    void setnumberofexits(int n); //Por si luego se quieren cambiar
    void addtunnel();
    void printnode();
};


#endif
