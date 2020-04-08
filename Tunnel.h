#ifndef TUNNEL
#define TUNNEL
#include <string>
#include "Node.h"
class Node;
class Tunnel{

private:
        std::string name;
        int length;
        float slope;
        float height;
        float width;
        Node *endings[2];
        int numberofsegments;
        //Segments *segment[];
public:
    Tunnel(std::string nam, int len, int slo,int hei, int wid, int num);
    ~Tunnel();
    void printtunnel();


};


#endif
