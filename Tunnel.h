#ifndef TUNNEL
#define TUNNEL
#include <string>
#include "Node.h"
class Node;
class Tunnel{

private:
        std::string name;
        float length;
        float slope;
        float height;
        float width;
        Node *endings[2];
        int numberofsegments;
        //Segments *segment[];
public:
    Tunnel();
    //Tunnel(std::string nam, int len, int slo,int hei, int wid, int num);
    ~Tunnel();
    void printtunnel();
    void setname(std::string n);
    void setlength(float n);
    void setheight(float n);
    void setwidth(float n);
    void setslope(float n);
    void setnumberofsegments(int n);
    void setstartnode(int n, Node *nod);
    void setfinalnode(int n, Node *nod);
};


#endif
