#include "Node.h"
#include "Tunnel.h"
#include "Graph.h"
#include "Segment.h"

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


int main()
{
    //lee el archivo
    ifstream inputdata;
    inputdata.open("/home/adri/Datos/Git/TFM-Codigo/data.txt");

    //Comprueba que se ha leido correctamente
    if (!inputdata)
    {
        cout << "Error: Can't open the file.\n";
        exit(1);
    }

    //Esto ignora el header del archivo
    string junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;

    string name;
    int var1;
    int var2;

    std::cout << "------Nodes input------" << std::endl;
    std::cout << std::endl;
    //Creo un vector de objetos nodo, que van a ir configurandose según el txt
    Node nodos[10];
    int i=0, N; // N=Number of nodes in the graph
    while (inputdata >> name >> var1 >> var2)
    {
        //Comprueba que no se ha pasado a definir los tuneles
        if (name=="NOMORENODESFLAG")
        {
            // std::cout << "se salio";
            break;

        };


        //Configura el nodo
        nodos[i].settype(name);
        nodos[i].setnodenumber(var1);
        nodos[i].setnumberofexits(var2);
        nodos[i].printnode();

        //cout << name <<" "<< var1 <<" "<< var2  <<" "<< std::endl;
        i++;
    }
    N=i;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;


    //Creo un vector de objetos tunnel, que van a ir configurandose según el txt
    Tunnel tuneles[10];
    vector<Segment> segments(100); //OJO [] es tamaño, () es numero de objetos.



    std::cout << std::endl;
    std::cout << "------Tunnels input------" << std::endl;
    std::cout << std::endl;



    vector<Enlace> enlaces;
    i=0;
    std::string tunnel;
    int start, final, nuseg,segcounter=0;

    //crear tantos objeto sewgmentos como numero de segmento


    float len, wid, hei, slo;
    while (inputdata >> tunnel >> start >> final >> nuseg)
    {


        tuneles[i].setname(tunnel);
        tuneles[i].setstartnode(start,nodos);
        tuneles[i].setfinalnode(final,nodos);
        tuneles[i].setnumberofsegments(nuseg);

        for (int j=0;j<nuseg;j++)
        {

            inputdata>> len >> wid >> hei >> slo;
            segments[segcounter].setlength(len);
            segments[segcounter].setwidth(wid);
            segments[segcounter].setheight(hei);
            segments[segcounter].setslope(slo);
            tuneles[i].addsegment(&segments[segcounter]);
            segcounter++;
        }




        tuneles[i].printtunnel();

        enlaces.push_back({start,final}); //creates links in the node adjacency list
        i++;
    }


//     =
//    {
//        { 0, 1 }, { 1, 2 }, { 2, 0 }, { 2, 1 },
//        { 3, 2 }, { 4, 5 }, { 5, 4 }
//    };

    std::cout << std::endl;
    std::cout << "------Node adjacency list------" << std::endl;
    std::cout << std::endl;

    // construct grafo
    Grafo grafo(enlaces, N);

    // print adjacency list representation of grafo
    grafo.printGraph(grafo, N);
    std::cout << std::endl;
    return 0;
    //nodos[1].printnode();

}
