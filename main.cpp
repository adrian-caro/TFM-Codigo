#include "Node.h"
#include "Tunnel.h"
#include "Graph.h"
#include "Segment.h"
#include "Dijkstra.h"
#include "Exploration.h"
#include "OOI.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <random>
#include <math.h>
using namespace std;


//Distances in meters (m).
#define MinHeight 0.5
#define MaxHeight 2

#define Minwidth 0.5
#define Maxwidth 3

#define MinHorizontalOrientation 0
#define MaxHorizontalOrientation 360

#define MinVerticalOrientation 0
#define MaxVerticalOrientation 360

#define MinNumberoftunnels 2
#define MaxNumberoftunnels 4

#define Mintunnelsegments 1
#define Maxtunnelsegments 4

#define Minsegmentlength 1
#define Maxsegmentlength 8

#define Minsegmentwidth 0.5
#define Maxsegmentwidth 1.5

#define Minsegmentheight 0.5
#define Maxsegmentheight 1.5

//Slope in %
#define Minsegmentlope 0
#define Maxsegmentlope 15

#define RandomlocationdistX 10 //Distance between nodes
#define RandomlocationdistY 10\

#define OOIgenerationRatio 0.3 //If the random number is lower than OOIgenerationRatio, then a OOI is generated

#define OOIdetectionRatio 0.9
#define unknownodeRatio 0.1
int main()
{
    char inputmode;

    cout << "Choose a graph input mode: " << std::endl;
    cout << "1. Load graph from file (.txt)." << std::endl;
    cout << "2. Random graph." << std::endl;
    cout << "--------------------" << std::endl;
    cout << "Mode:";

    vector<Pair> OOIlist;
    int OOI_ID=0;
    float unknownodeR;


    do{
        std::cin >> inputmode;

        switch(inputmode)
        {
        case '1':

            break;
        case '2':

            break;
        default:
            std::cout<<"Invalid choice" << std::endl;

        }
    }while(inputmode!='1' &&  inputmode!='2');



    if (inputmode=='2')
    {
        cout<< std::endl;
        std::cout<<"Generating a random graph" << std::endl;
        //Grafo grafito;
        int Numnodos;
        int explorationactualnode;
        cout << "Introduce the number of nodes of the desired graph: ";
        cin >> Numnodos;
        Node nodos[Numnodos+1];
        string name="N",result;
        std::cout << "------Nodes input------" << std::endl;
        random_device rd;
        mt19937 mt(rd());

        OOI OOIs[Numnodos];
        Tunnel tuneles[Numnodos*4];
        vector<Segment> segments(Numnodos*5);
        uniform_real_distribution<double> randomx(-RandomlocationdistX, RandomlocationdistX);
        uniform_real_distribution<double> randomy(-RandomlocationdistY, RandomlocationdistY);
        float x,y,z,OOIratio;
        vector<int> previousnodeposition;

        uniform_real_distribution<double> OOIgeneration(0,1);

        for (int i=0;i<Numnodos;i++)
        {
            result = name + std::to_string(i);

            OOIratio= OOIgeneration(mt);

            if (OOIratio<OOIgenerationRatio) //If the random number is lower than OOIgenerationRatio, then a OOI is generated
            {
                //Create an OOI

                OOIs[OOI_ID].setID(OOI_ID);
                OOIlist.push_back(make_pair(OOI_ID,i));
                nodos[i].addOOI(&OOIs[OOI_ID]);
                //OOIs[OOI_ID].
                OOI_ID++;
            }

            unknownodeR=OOIgeneration(mt);

            if (unknownodeR<=unknownodeRatio)
            {
                //Create unknown node
                nodos[i].settype(result);
                nodos[i].setnodenumber(9999);
                std::cout << "Nodo caca -" << i << std::endl;

            }
            else
            {
                nodos[i].settype(result);
                nodos[i].setnodenumber(i);
            }

            if (i==0)
            {
                x= randomx(mt);
                y= randomy(mt);
                z= 0;
            }
            else
            {
                previousnodeposition=nodos[i-1].getcoordinates();
                x= randomx(mt)+previousnodeposition.at(0);
                y= randomy(mt)+previousnodeposition.at(1);
                z= 0;
            }

            nodos[i].setcoordinates(x,y,z);
        }
        float var7,var3,var4,var5,var6;

        //Node 0 Entrance
        vector<int> coordi;
        coordi=nodos[4].getcoordinates();


        //connected node
        var7=1;
        //height
        uniform_real_distribution<double> dist11(MinHeight, MaxHeight);
        var3= dist11(mt);
        //width
        uniform_real_distribution<double> dist12(Minwidth, Maxwidth);
        var4= dist12(mt);
        //HorizontalOrientation
        uniform_real_distribution<double> dist13(MinHorizontalOrientation, MaxHorizontalOrientation);
        var5= dist13(mt);
        //VerticalOrientation
        uniform_real_distribution<double> dist14(MinVerticalOrientation, MaxVerticalOrientation);
        var6= dist14(mt);

        nodos[0].setexitprop(var7,var3,var4,var5,var6);
        nodos[0].setnumberofexits(1);
        nodos[1].setexitprop(0,var3,var4,var5,var6);
        nodos[1].setnumberofexits(1);
        int numberofexits;
        float tempor;
        int connectingnode,tempnumexits;
        uniform_real_distribution<double> dist(-5, 5);
        uniform_real_distribution<double> tunnn(MinNumberoftunnels, MaxNumberoftunnels);
        uniform_real_distribution<double> tunnseg(Mintunnelsegments, Maxtunnelsegments);

        uniform_real_distribution<double> dist20(Minsegmentlength, Maxsegmentlength);
        uniform_real_distribution<double> dist21(Minsegmentwidth, Maxsegmentwidth);
        uniform_real_distribution<double> dist22(Minsegmentheight, Maxsegmentheight);
        uniform_real_distribution<double> dist23(Minsegmentlope, Maxsegmentlope);


        vector<Enlace> enlaces;

        std::string tunnelname;
        int tunnelnumber=0, segmentnumber;
        int start, final, nuseg,segcounter=0;
        float longitud;
        int numberoftunnels=0;

        tempor = tunnseg(mt);
        nuseg=round(tempor);
        tunnelname=std::to_string(tunnelnumber);
        tuneles[numberoftunnels].setname(tunnelname);
        tuneles[numberoftunnels].setstartnode(0);
        tuneles[numberoftunnels].setfinalnode(1);
        tuneles[numberoftunnels].setnumberofsegments(nuseg);



        //creates as many segments as the tunnel has=
        for (int j=0;j<nuseg;j++)
        {

            segments[segcounter].setlength(dist20(mt));
            segments[segcounter].setwidth(dist21(mt));
            segments[segcounter].setheight(dist22(mt));
            segments[segcounter].setslope(dist23(mt));
            tuneles[numberoftunnels].addsegment(&segments[segcounter]);
            segcounter++;
        }

        longitud=tuneles[numberoftunnels].getlength();
        tuneles[numberoftunnels].printtunnel();

        //creates links in the node adjacency list
        enlaces.push_back({0,1,longitud});

        numberoftunnels++;
        tunnelnumber++;
        segmentnumber++;




        for (int j=1;j<Numnodos;j++)
        {
            tempor = tunnn(mt);
            //numberofexits=round(tempor);
            numberofexits=3;
            segmentnumber=0;

            if (nodos[j].getnodenumber()==9999)
            {
                numberofexits=1;
            }

            for (int i=nodos[j].getnumberofexits();i<numberofexits;i++)
            {


                tempor = dist(mt);
                connectingnode=round(tempor)+j;

                while (nodos[connectingnode].getnumberofexits()>=MaxNumberoftunnels ||nodos[connectingnode].getnodenumber()==9999 || connectingnode==j || connectingnode<=0 || connectingnode>Numnodos-1)
                {
                    tempor = dist(mt);
                    connectingnode=round(tempor)+j;
                }
                //connected node
                var7 = connectingnode;
                //height
                var3 = dist11(mt);
                //width
                var4 = dist12(mt);
                //HorizontalOrientation
                var5 = dist13(mt);
                //VerticalOrientation
                var6 = dist14(mt);

                nodos[j].setexitprop(var7,var3,var4,var5,var6);
                tempnumexits=nodos[j].getnumberofexits();
                nodos[j].setnumberofexits(tempnumexits+1);

                nodos[connectingnode].setexitprop(j,var3,var4,var5,var6);
                tempnumexits=nodos[connectingnode].getnumberofexits();
                nodos[connectingnode].setnumberofexits(tempnumexits+1);

                tunnelname=std::to_string(tunnelnumber);
                tuneles[numberoftunnels].setname(tunnelname);
                tuneles[numberoftunnels].setstartnode(j);
                tuneles[numberoftunnels].setfinalnode(connectingnode);

                tempor = tunnseg(mt);
                nuseg=round(tempor);

                OOIratio= OOIgeneration(mt);
                if (OOIratio<OOIgenerationRatio) //If the random number is lower than OOIgenerationRatio, then a OOI is generated
                {
                    //Create an OOI

                    OOIs[OOI_ID].setID(OOI_ID+Numnodos*2);
                    OOIlist.push_back(make_pair(OOI_ID+Numnodos*2,numberoftunnels));
                    tuneles[numberoftunnels].addOOI(&OOIs[OOI_ID]);
                    //OOIs[OOI_ID].
                    OOI_ID++;
                }

                tuneles[numberoftunnels].setnumberofsegments(nuseg);


                //creates as many segments as the tunnel has
                for (int j=0;j<nuseg;j++)
                {

                    segments[segcounter].setlength(dist20(mt));
                    segments[segcounter].setwidth(dist21(mt));
                    segments[segcounter].setheight(dist22(mt));
                    segments[segcounter].setslope(dist23(mt));
                    tuneles[numberoftunnels].addsegment(&segments[segcounter]);
                    segcounter++;
                }

                longitud=tuneles[numberoftunnels].getlength();
                tuneles[numberoftunnels].printtunnel();

                //creates links in the node adjacency list
                enlaces.push_back({j,connectingnode,longitud});

                numberoftunnels++;
                tunnelnumber++;
                segmentnumber++;
            }

        }

        std::cout << std::endl;
        std::cout << "------Node adjacency list------" << std::endl;
        std::cout << std::endl;
        std::cout << "Node --> (LinkedNode,Distance)" << std::endl;
        std::cout << std::endl;

        //Constructs the graph
        Grafo grafo(enlaces, Numnodos,nodos);

        //Print adjacency list representation of the graph
        grafo.printGraph(grafo, Numnodos);
        std::cout << std::endl;


        std::cout << "Do you want to perform a path search between two nodes? (Y/N)." << std::endl;
        char response;

        int search=2;
        int startnode, goalnode;
        do{
            std::cin>>response;
            switch(response)
            {
            case 'Y':
                search=1;

                break;
            case 'y':
                search=1;

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
            int searchmode;
            std::cout << "Select start mode." << std::endl;
            std::cout << "1. Lost start mode" << std::endl;
            std::cout << "2. Known start node" << std::endl;
            cout << "--------------------" << std::endl;
            cout << "Mode:";

            int lostnode;



            char answer;
            do{
                std::cin>>answer;
                switch(answer)
                {
                case '1':
                    searchmode=1;
                    std::cout << "Set start lost node:" << std::endl;
                    std::cin >> lostnode;
                    std::cout << "Set goal node:" << std::endl;
                    std::cin >> goalnode;
                    break;
                case '2':
                    searchmode=2;
                    std::cout << "Set start node:" << std::endl;
                    std::cin >> startnode;
                    std::cout << "Set goal node:" << std::endl;
                    std::cin >> goalnode;

                default: std::cout<<"Invalid choice" << std::endl;
                    break;
                }
            }while(answer!='1' && answer!='2');


            Exploration exploration1;

            if (searchmode==1)
            {
                startnode=exploration1.lost(nodos,Numnodos,lostnode);
            }



            //Performs the path search betweeen to given nodes (defined at the very first lines of the main().

            Dijkstra search;
            solutionpath=search.algorithm(startnode,goalnode,grafo.getlista());
            int a,b;

                std::cout << std::endl;
            //std::cout << "Solution tunnel and segments sequence:" << std::endl;
                std::cout << std::endl;

            vector<Segment*> segmentpath,segmentemp;
            for(int i=0; i<solutionpath.size()-1;i++){
                a=solutionpath.at(i);
                b=solutionpath.at(i+1);

                //search tunnel between nodes
                vector<int> temp;

                for(int j=0;j<numberoftunnels;j++)
                {
                    temp=tuneles[j].getendings();


                    if(temp.at(0)==a && temp.at(1)==b)
                    {
                        segmentemp=tuneles[j].getsegments();
                        //tuneles[j].printtunnel();
                        for (int i=0; i<tuneles[j].getnumberofsegments(); i++)
                        {
                            segmentpath.push_back(segmentemp.at(i));
                        }
                    }


                    if(temp.at(0)==b && temp.at(1)==a)
                    {
                        //tuneles[j].reverseprinttunnel();
                        segmentemp=tuneles[j].getsegments();
                        for (int i=tuneles[j].getnumberofsegments()-1; i>-1; i--)
                        {
                            segmentpath.push_back(segmentemp.at(i));
                        }
                    }

                }

            }


            std::cout << std::endl;\


            explorationactualnode=exploration1.explorationalgorithm(nodos,solutionpath,tuneles,numberoftunnels,OOIlist);

            while (explorationactualnode!=solutionpath[solutionpath.size()-1])
            {
                solutionpath.clear();
                startnode=explorationactualnode;
                solutionpath=search.algorithm(startnode,goalnode,grafo.getlista());


                explorationactualnode=exploration1.explorationalgorithm(nodos,solutionpath,tuneles,numberoftunnels,OOIlist);
            }




        }







    }
    else if (inputmode=='1')
    {


        //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------








        ifstream inputdata;
        srand(time(NULL));
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


        Node nodos[100];
        int i=0, Numnodos; // N=Number of nodes in the graph

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
        Numnodos=i;
        inputdata >> junkheader1;
        inputdata >> junkheader1;
        inputdata >> junkheader1;
        inputdata >> junkheader1;
        inputdata >> junkheader1;
        inputdata >> junkheader1;
        inputdata >> junkheader1;
        inputdata >> junkheader1;


        Tunnel tuneles[100];
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
        Grafo grafo(enlaces, Numnodos,nodos);

        //Print adjacency list representation of the graph
        grafo.printGraph(grafo, Numnodos);
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

            Dijkstra search;
            solutionpath=search.algorithm(startnode,goalnode,grafo.getlista());
            int a,b;

                std::cout << std::endl;
            //std::cout << "Solution tunnel and segments sequence:" << std::endl;
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
                        //tuneles[j].printtunnel();
                        for (int i=0; i<tuneles[j].getnumberofsegments(); i++)
                        {
                            segmentpath.push_back(segmentemp.at(i));
                        }
                    }


                    if(temp.at(0)==b && temp.at(1)==a)
                    {
                        //tuneles[j].reverseprinttunnel();
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

        exploration1.explorationalgorithm(nodos,solutionpath,tuneles,numtuneles,OOIlist);


        int asd=exploration1.lost(nodos,Numnodos,5);
    }




    return 0;

}
