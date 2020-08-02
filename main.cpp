#include "Node.h"
#include "Tunnel.h"
#include "Graph.h"
#include "Segment.h"
#include "Dijkstra.h"
#include "Exploration.h"

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


int main()
{
    ifstream inputdata;

    //definitions
    int startnode, goalnode;
    inputdata.open("/home/adri/Git/TFM-Codigo/data.txt");


    //Checks the openned file
    if (!inputdata)
    {
        cout << "Error: Can't open the file.\n";
        exit(1);
    }


    //Jumps header data
    string junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;

    string name;
    int var1,var2, var7;
    float var3, var5, var6, var4;

    std::cout << "------Nodes input------" << std::endl;
    std::cout << std::endl;


    Node nodos[10];
    int i=0, N; // N=Number of nodes in the graph

    while (inputdata >> name >> var1 >> var2)
    {
        //Check for the end of node definition
        if (name=="NoMoreNodesFLAG")
        {
            break;
        };

        //Configures the node
        nodos[i].settype(name);
        nodos[i].setnodenumber(var1);
        nodos[i].setnumberofexits(var2);

        for (int j=0;j<var2;j++)
        {
            inputdata >> var7 >> var3 >> var4 >> var5 >> var6;

            nodos[i].setexitprop(var7,var3,var4,var5,var6);
        }

        nodos[i].printnode();

        i++;
    }


    //Jumps header data
    N=i;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;
    inputdata >> junkheader1;


    Tunnel tuneles[10];
    vector<Segment> segments(30);



    std::cout << std::endl;
    std::cout << "------Tunnels input------" << std::endl;
    std::cout << std::endl;



    vector<Enlace> enlaces;
    i=0;
    std::string tunnel;
    int start, final, nuseg,segcounter=0;


    float len, wid, hei, slo,longitud;
    while (inputdata >> tunnel >> start >> final >> nuseg)
    {
        tuneles[i].setname(tunnel);
        tuneles[i].setstartnode(start);
        tuneles[i].setfinalnode(final);
        tuneles[i].setnumberofsegments(nuseg);

        //creates as many segments as the tunnel has
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

        longitud=tuneles[i].getlength();
        tuneles[i].printtunnel();

        //creates links in the node adjacency list
        enlaces.push_back({start,final,longitud});
        i++;
    }

    int numtuneles=i;

    std::cout << std::endl;
    std::cout << "------Node adjacency list------" << std::endl;
    std::cout << std::endl;
    std::cout << "Node --> (LinkedNode,Distance)" << std::endl;
    std::cout << std::endl;

    //Constructs the graph
    Grafo grafo(enlaces, N,nodos);

    //Print adjacency list representation of the graph
    grafo.printGraph(grafo, N);
    std::cout << std::endl;

    std::cout << "Do you want to perform a path search between two nodes? (Y/N)." << std::endl;
    char response;

    int search=2;

    do{
        std::cin>>response;
        switch(response)
        {
        case 'Y':
            search=1;
            std::cout << "Set start node:" << std::endl;
            std::cin >> startnode;
            std::cout << "Set goal node:" << std::endl;
            std::cin >> goalnode;
            break;
        case 'y':
            search=1;
            std::cout << "Set start node:" << std::endl;
            std::cin >> startnode;
            std::cout << "Set goal node:" << std::endl;
            std::cin >> goalnode;
            break;
        case 'N':   search=0;
            break;
        case 'n':   search=0;
            break;
        default: std::cout<<"Invalid choice" << std::endl;
            break;
        }
    }while(search!=0 && search!=1);


    vector<int> solutionpath;
    if (search==1)
    {
        //Performs the path search betweeen to given nodes (defined at the very first lines of the main().

        Dijkstra search(startnode,goalnode,grafo.getlista());
        solutionpath=search.algorithm();
        int a,b;

            std::cout << std::endl;
        std::cout << "Solution tunnel and segments sequence:" << std::endl;
            std::cout << std::endl;

        vector<Segment*> segmentpath,segmentemp;
        for(int i=0; i<solutionpath.size()-1;i++){
            a=solutionpath.at(i);
            b=solutionpath.at(i+1);

            //search tunnel between nodes
            vector<int> temp;

            for(int j=0;j<numtuneles;j++)
            {
                temp=tuneles[j].getendings();


                if(temp.at(0)==a && temp.at(1)==b)
                {
                    segmentemp=tuneles[j].getsegments();
                    tuneles[j].printtunnel();
                    for (int i=0; i<tuneles[j].getnumberofsegments(); i++)
                    {
                        segmentpath.push_back(segmentemp.at(i));
                    }
                }


                if(temp.at(0)==b && temp.at(1)==a)
                {
                    tuneles[j].reverseprinttunnel();
                    segmentemp=tuneles[j].getsegments();
                    for (int i=tuneles[j].getnumberofsegments()-1; i>-1; i--)
                    {
                        segmentpath.push_back(segmentemp.at(i));
                    }
                }

            }

        }

            //ADD REVERSE PRINT TUNNEL SECTION

    }


    std::cout << std::endl;\
    Exploration exploration1;

    //exploration1.sensoreadings(1,nodos);
    //float Pnodevariation=exploration1.nodecomparison(1,1,nodos);

    exploration1.explorationalgorithm(nodos,solutionpath);

    return 0;
}
