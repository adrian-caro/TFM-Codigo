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
    //Tunnel(std::string nam, int len, int slo,int hei, int wid, int num);
    ~Tunnel();
    void printtunnel();
    void setname(std::string n);
    void setnumberofsegments(int n);
    float getlength();
    vector<int> getendings();
    void setstartnode(int n);
    void setfinalnode(int n);
    //void setstartnode(int n, Node *nod);
    //void setfinalnode(int n, Node *nod);
    //Node getendings();
    void addsegment(Segment *seg);
    void addOOI(OOI *ooi);

};


#endif
