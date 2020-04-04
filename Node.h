#ifndef NODE
#define NODE
#include <string>

class Node{

private: 
        std::string type;
        int nodenumber;
        int numberofexits;
        float position[3];
        //Tunnel *exits[];
public:
    Node(std::string t, int nn, int ne);
    ~Node();
    void setnumberofexits(int n); //Por si luego se quieren cambiar
    void addtunnel();
    void printnode();
};


#endif
