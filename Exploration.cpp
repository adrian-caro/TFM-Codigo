#include "Exploration.h"
#include <time.h>

Exploration::Exploration()
{
    dH=0,dC=0,dAlpha=0,dBeta=0;
    P=0;
    K=0;
}

void Exploration::sensoreadings(int nodenumber,Node *nodos)
{
    explorationnodes[nodenumber].settype(nodos[nodenumber].gettype());
    explorationnodes[nodenumber].setnumberofexits(nodos[nodenumber].getnumberofexits());
    int salidas=nodos[nodenumber].getnumberofexits();
    explorationnodes[nodenumber].setnodenumber(nodos[nodenumber].getnodenumber());



    int con; float he, wi, Hor,  Vor;


    //Noise parameters
    //--------------------------------------
    float Pnodevariation=0;
    float Pheightvariation=0.05;
    float Pwidthvariation=0.05;
    float PHorivariation=0.05;
    float PVorivariation=0.05;
    //--------------------------------------


    for (int i=0;i<salidas;i++)
    {
        //A variation is generated (sensor noise)
        con=nodos[nodenumber].getexitprop(i,0);


        he=nodos[nodenumber].getexitprop(i,1);
        srand(time(NULL));
        he = he*(1+-Pheightvariation + (rand()) /( static_cast <float> (RAND_MAX/(Pheightvariation*2))));
        //he=he+(-Pheightvariation + rand() % ( Pheightvariation*2 + 1 ));

        wi=nodos[nodenumber].getexitprop(i,2);
        srand(time(NULL));
        wi = wi*(1+-Pwidthvariation + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(Pwidthvariation*2))));

        Hor=nodos[nodenumber].getexitprop(i,3);
        srand(time(NULL));
        Hor = Hor*(1+-PHorivariation + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(PHorivariation*2))));

        Vor=nodos[nodenumber].getexitprop(i,4);
        srand(time(NULL));
        Vor = Vor*(1+-PVorivariation + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(PVorivariation*2))));

        explorationnodes[nodenumber].setexitprop(con,he,wi,Hor,Vor);
    }

}
//void Exploration::explorationalgorithm(int nodoini,Node *nodos,vector<int> solutionpath)
//{

//    //Opens the sensor readings file
//    ifstream inputdata;
//    inputdata.open("/home/adri/Git/TFM-Codigo/exploration.txt");


//    //Checks the openned file
//    if (!inputdata)
//    {
//        cout << "Error: Can't open the file.\n";
//        exit(1);
//    }

//    //it is assumed that the the robot is in the first node of the solution path firstly.

//    int solutionpathindex=0,actualnode=nodoini,i=0; //indicates the next heading node for the robot



//    while (solutionpathindex<solutionpath.size()) //Revisar la condicion
//    {
//        //The robot get the sensor readings of how many exits he is seing and their properties.
//        //----------------------------------------------------------------------

//        std::cout << std::endl;
//        std::cout << "------Robot sensors input------" << std::endl;
//        std::cout << std::endl;



//        //----------------------------------------------------------------------


//        solutionpathindex++;

//    }
//}
