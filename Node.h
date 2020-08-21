#ifndef NODE
#define NODE
#include <string>
#include <vector>
#include "Tunnel.h"
#include "OOI.h"
using namespace std;

class OOI;
class Tunnel;



class Node{

private: 

    std::string type;
    int nodenumber;
    std::vector<OOI*> OOIs;
    float height;
    float width;
    int numberofexits;
    vector<int> nodosconectados;
    vector<int> coordinates;
    vector<vector<float>> ExitProp;

public:
    Node();
    ~Node();
    void settype(std::string n);
    void setnumberofexits(int n);
    void setnodenumber(int n);
    void addtunnel();
    void printnode();
    void printname();
    void printexits();
    void addOOI(OOI *ooi);
    void setheight(float n);
    void setwidth(float n);
    void setexitprop(int connectednode, float hei, float wid, float Hori, float Vori);
    void addnodoconectado(int n);
    void setcoordinates(int x, int y, int z);
    vector<int> getcoordinates();

    string gettype();
    int getnumberofexits();
    int getnodenumber();
    float getexitprop(int salida, int prop);
    //OOI* getOOI();
    int getnumberofOOI();
    int getOOI_ID(int n);


};


#endif
