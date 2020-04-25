#ifndef NODE
#define NODE
#include <string>
#include <vector>
#include "Tunnel.h"


class OOI;
class Tunnel;
class Node{

private: 
        std::string type;
        int nodenumber;
        int numberofexits;
        float position[3];
        Tunnel *exits[10];
        std::vector<OOI*> OOIs;
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
    void addOOI(OOI *ooi);
};


#endif
