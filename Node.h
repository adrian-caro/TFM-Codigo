#ifndef NODE
#define NODE
#include <string>
#include <vector>
#include "Tunnel.h"
using namespace std;

class OOI;
class Tunnel;



class Node{

private: 

        std::string type;
        int nodenumber;

        //float position[3];
        //Tunnel *exits[10];
        std::vector<OOI*> OOIs;
        float height;
        float width;

        int numberofexits;
        vector<int> nodosconectados;
        vector<vector<float>> ExitProp;
        // float Horientation; //Horizontal orientation. From north, cloclwise.
        // float Vorientation; //Vertical orientation. From horizontal, going up.
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
    void setheight(float n);
    void setwidth(float n);
    void setexitprop(float hei, float wid, float Hori, float Vori);
    void addnodoconectado(int n);
};


#endif
