#ifndef TUNNEL
#define TUNNEL
#include <string>
#include <vector>
#include "Node.h"
using namespace std;
class OOI;
class Segment;
class Node;
class Tunnel{

private:
    std::string name;
    //Node *endings[2];
    std::vector<int> endings;
    int numberofsegments;
    float length;
    vector<Segment*> segments;
    vector<OOI*> OOIs;
public:
    Tunnel();
    ~Tunnel();
    void printtunnel();
    void reverseprinttunnel();
    void setname(std::string n);
    void setnumberofsegments(int n);
    int getnumberofsegments();
    float getlength();
    vector<int> getendings();
    void setstartnode(int n);
    void setfinalnode(int n);
    void addsegment(Segment *seg);
    vector<Segment*> getsegments();
    void addOOI(OOI *ooi);

};


#endif
