#ifndef TUNNEL
#define TUNNEL
#include <string>
#include <vector>
#include "Node.h"
using namespace std;

class Segment;
class Node;
class Tunnel{

private:
        std::string name;
        Node *endings[2];
        int numberofsegments;
        vector<Segment*> segments;
public:
    Tunnel();
    //Tunnel(std::string nam, int len, int slo,int hei, int wid, int num);
    ~Tunnel();
    void printtunnel();
    void setname(std::string n);
    void setnumberofsegments(int n);
    void setstartnode(int n, Node *nod);
    void setfinalnode(int n, Node *nod);
    void addsegment(Segment *seg);
};


#endif
