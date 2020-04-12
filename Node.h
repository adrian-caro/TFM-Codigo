#ifndef NODE
#define NODE
#include <string>
#include "Tunnel.h"
class Tunnel;
class Node{

private: 
        std::string type;
        int nodenumber;
        int numberofexits;
        float position[3];
        Tunnel *exits[10];
public:
    Node();
        //Node(std::string t, int nn, int ne);
    ~Node();
    void settype(std::string n);
    void setnumberofexits(int n); //Por si luego se quieren cambiar
    void setnodenumber(int n);
    void addtunnel();
    void printnode();
    void printname();
    void printexits();
};


#endif
