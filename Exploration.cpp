#include "Exploration.h"
#include <time.h>
#include <iostream>
#include <random>
#include <math.h>

Exploration::Exploration()
{

}
float Exploration::nodecomparison(int realnode, int mapnode, Node *nodos)
{
    //check if both nodes to compare have the same exits
    int salidas=nodos[realnode].getnumberofexits();
    int nexitstocompare=1;
    float Pnodevariation=0;
    std::cout << "Nodes to compare:  real (" << explorationnodes[realnode].getnodenumber() << ") and expected (" << nodos[mapnode].getnodenumber()<< ")" << std::endl;
    if (salidas!=nodos[mapnode].getnumberofexits())
    {
        if (salidas<nodos[mapnode].getnumberofexits())
        {
            nexitstocompare=salidas;
        }
        else
        {
            nexitstocompare=nodos[mapnode].getnumberofexits();
        }
    }
    else
    {
        nexitstocompare=salidas;
    }
    for (int i=0;i<nexitstocompare;i++)
    {
        float dH=   abs((explorationnodes[realnode].getexitprop(i,1)-nodos[mapnode].getexitprop(i,1)))/std::max(explorationnodes[realnode].getexitprop(i,1),nodos[mapnode].getexitprop(i,1));
        float dW=   abs((explorationnodes[realnode].getexitprop(i,2)-nodos[mapnode].getexitprop(i,2)))/std::max(explorationnodes[realnode].getexitprop(i,2),nodos[mapnode].getexitprop(i,2));
        float dHori=abs((explorationnodes[realnode].getexitprop(i,3)-nodos[mapnode].getexitprop(i,3)))/std::max(explorationnodes[realnode].getexitprop(i,3),nodos[mapnode].getexitprop(i,3));
        float dVori=abs((explorationnodes[realnode].getexitprop(i,4)-nodos[mapnode].getexitprop(i,4)))/std::max(explorationnodes[realnode].getexitprop(i,4),nodos[mapnode].getexitprop(i,4));

        float Pi=(1-dH)*(1-dW)*(1-dHori)*(1-dVori);
        Pnodevariation=Pnodevariation+Pi;
    }

    Pnodevariation=Pnodevariation/salidas;
    return Pnodevariation;
}


void Exploration::sensoreadings(int nodenumber, Node *nodos)
{
    explorationnodes[nodenumber].settype(nodos[nodenumber].gettype());
    explorationnodes[nodenumber].setnumberofexits(nodos[nodenumber].getnumberofexits());
    int salidas=nodos[nodenumber].getnumberofexits();
    explorationnodes[nodenumber].setnodenumber(nodos[nodenumber].getnodenumber());



    int con; float he, wi, Hor,  Vor;
    int conn; float hei, wid, Hori,  Vori;


    //Noise parameters

    float Pheightvariation, Pwidthvariation, PHorivariation,PVorivariation;

    random_device rd;
    mt19937 mt(rd());

    uniform_real_distribution<double> dist(-Pheightvariationmax, Pheightvariationmax);
    Pheightvariation = dist(mt);

    uniform_real_distribution<double> dist2(-Pwidthvariationmax, Pwidthvariationmax);
    Pwidthvariation = dist2(mt);

    uniform_real_distribution<double> dist3(-PHorivariationmax, PHorivariationmax);
    PHorivariation = dist3(mt);

    uniform_real_distribution<double> dist4(-PVorivariationmax, PVorivariationmax);
    PVorivariation = dist4(mt);




    //float Pnumberofexitsvariation=0.2;
    //--------------------------------------

    //float nodevariation=0;
    //nodevariation=((float) rand()) / (float) RAND_MAX;



    //Probabilidad de que no detecte una salida
    //    if (nodevariation<Pnumberofexitsvariation)
    //    {
    //        int deletedexit= + ( (int) rand() % ( 5-1) );
    //    }

    //que pasa a la hora de comparar con un nodo con menos salidas.
    for (int i=0;i<salidas;i++)
    {

        //A variation is generated (sensor noise)
        conn=nodos[nodenumber].getexitprop(i,0);
        con=conn;

        hei=nodos[nodenumber].getexitprop(i,1);

        //he = hei*(1+-Pheightvariation + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(Pheightvariation*2))));
        he = hei*(1+Pheightvariation);
        //he=he+(-Pheightvariation + rand() % ( Pheightvariation*2 + 1 ));

        wid=nodos[nodenumber].getexitprop(i,2);
        //srand(time(NULL));
        //wi = wid*(1+-Pwidthvariation + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(Pwidthvariation*2))));
        wi = wid*(1+Pwidthvariation);

        Hori=nodos[nodenumber].getexitprop(i,3);
        //srand(time(NULL));
        //Hor = Hori*(1+-PHorivariation + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(PHorivariation*2))));
        Hor = Hori*(1+PHorivariation);

        Vori=nodos[nodenumber].getexitprop(i,4);
        //srand(time(NULL));
        //Vor = Vori*(1+-PVorivariation + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(PVorivariation*2))));
        Vor = Vori*(1+PVorivariation);
        explorationnodes[nodenumber].setexitprop(con,he,wi,Hor,Vor);
    }



}

void Exploration::explorationalgorithm(Node *nodos, vector<int> solutionpath, Tunnel *tuneles, int numtuneles, vector<Pair> OOIlist)
{

    float uncertainty=1,pastuncertainty;
    //it is assumed that the the robot is in the first node of the solution path firstly.
    int first=-1,checkOOInode;
    //
    int solutionpathindex=0; //indicates the actual solution node where the robot is facing
    int actualnode, pastnode=solutionpath[0];
    actualnode=solutionpath[0];
    std::cout << std::endl;
    std::cout << "------Exploration------" << std::endl;
    std::cout << std::endl;
    std::cout << "Initial node: " << actualnode << std::endl;
    int expectednextnode=solutionpath[1];//There are real and expected nodes due to tunnel mistakes
    int realnextnode=solutionpath[1];
    int chosenexit=0,OOIcomparison;
    float penalization;
    float pnodevariation,OOIdetectionR;

    int error=0;
    sensoreadings(actualnode,nodos);



    random_device rd;
    mt19937 mt(rd());

    uniform_real_distribution<double> dist(0.0, explorationnodes[actualnode].getnumberofexits()-1);
    uniform_real_distribution<double> OOIdetection(0,1);

    //float Pbadtunn=0.15; //probability of choosing a bad tunnel

    while (actualnode!=solutionpath[solutionpath.size()-1]) //Revisar la condicion y los actualnodes
    {

        first++;//Because in the first iteration there must not be any past correction.

        //-------------------- Initial part--------------------------------------------------------------------------

        //The robot get the sensor readings of how many exits he is seing and their properties.
        int salidas;
        salidas=explorationnodes[solutionpath[solutionpathindex]].getnumberofexits();


        //-------------------- Exit selection ------------------------------------------------------------------------
        int exitfound=0;
        //Looks for the correct exit
        for (int i=0;i<salidas;i++)
        {
            if (explorationnodes[actualnode].getexitprop(i,0)==solutionpath[solutionpathindex+1])
            {
                expectednextnode=explorationnodes[actualnode].getexitprop(i,0);
                chosenexit=i;
                exitfound=1;
            }

        }

        if (exitfound==0)
        {
            //Añadir condicion cuando no encuentra la salida que se quiere
            expectednextnode=0;
            std::cout << "Error exit not found " << solutionpath[solutionpath.size()-1] << std::endl;
            error=1;
            break;

            //Ojo CAMBIAR

        }

        realnextnode=expectednextnode;

        if (error==1)
        {
            break;
        }

        //-------------------- Tunnel transition ----------------------------------------------------------------------

        std::cout << "Tunnel transition. "<< std::endl;
        //Bad tunnel probability
        float badtunnel =  static_cast <float> (rand()) /( static_cast <float> (RAND_MAX));

        //float Pnodevariation;

        if (badtunnel<Pbadtunn)
        {


            //chosenexit=chosenexit-1;
            int num;
            num=chosenexit;
            if (explorationnodes[actualnode].getnumberofexits()==2)
            {
                if (chosenexit==1)
                {
                    num=0;
                    std::cout << "***BAD TUNNEL CHOSEN***. "<< std::endl;
                }
                else
                {
                    num=1;
                    std::cout << "***BAD TUNNEL CHOSEN***. "<< std::endl;
                }
            }
            else if (explorationnodes[actualnode].getnumberofexits()==1)
            {
                num=0;
            }
            else
            {
                float temp;
                while (num==chosenexit)
                {


                    temp = dist(mt);
                    num=round(temp);

//                    int lower=0;
//                    int upper=explorationnodes[actualnode].getnumberofexits()-1;
//                    num = (rand() % (upper - lower + 1)) + lower;
                    //std::cout << num << std::endl;

                }
                std::cout << "***BAD TUNNEL CHOSEN***. "<< std::endl;
            }
            chosenexit=num;
            realnextnode=explorationnodes[actualnode].getexitprop(chosenexit,0);

        }

        //Tunnel print
        int a=actualnode;
        int b=realnextnode;
        vector<int> temp;

        for(int j=0;j<numtuneles;j++)
        {
            temp=tuneles[j].getendings();


            if(temp.at(0)==a && temp.at(1)==b)
            {
                //segmentemp=tuneles[j].getsegments();
                std::cout << std::endl;
                tuneles[j].printtunnel();
                std::cout << std::endl;
                //                for (int i=0; i<tuneles[j].getnumberofsegments(); i++)
                //                {
                //                    segmentpath.push_back(segmentemp.at(i));
                //                }
            }


            if(temp.at(0)==b && temp.at(1)==a)
            {
                std::cout << std::endl;
                tuneles[j].reverseprinttunnel();
                std::cout << std::endl;
                //                segmentemp=tuneles[j].getsegments();
                //                for (int i=tuneles[j].getnumberofsegments()-1; i>-1; i--)
                //                {
                //                    segmentpath.push_back(segmentemp.at(i));
                //                }
            }

        }


        //-------------------- Node arrival ----------------------------------------------------------------------
        pastnode=actualnode;
        actualnode=realnextnode;


        if (actualnode==99)
        {
           std::cout << "The robot arrived to an unknown node. " << std::endl;
           std::cout << "No further exploration will be performed this way." << std::endl;
           std::cout << "Going back to the previous node." << std::endl;

           //Tunnel print
           int a=actualnode;
           int b=pastnode;
           vector<int> temp;

           for(int j=0;j<numtuneles;j++)
           {
               temp=tuneles[j].getendings();


               if(temp.at(0)==a && temp.at(1)==b)
               {

                   std::cout << std::endl;
                   tuneles[j].printtunnel();
                   std::cout << std::endl;

               }


               if(temp.at(0)==b && temp.at(1)==a)
               {
                   std::cout << std::endl;
                   tuneles[j].reverseprinttunnel();
                   std::cout << std::endl;

               }

           }


           std::cout << "Previous node (" << pastnode << ") reached correctly."<< std::endl;
           actualnode=pastnode;
           expectednextnode=actualnode;
           solutionpathindex--;
        }
        else {
            std::cout << "Node " << actualnode << " arrived. " << std::endl;
            //The robot get the readings of the new just arrived node (realnextnode)
            sensoreadings(actualnode,nodos); //clona el nodo con variaciones de lectura
        }


        //-------------------- Node check -------------------------------------------------------------------------

        //The robot compare the sensor readings with the expected node
        pnodevariation=nodecomparison(actualnode,expectednextnode,nodos); //ofrece una estimacion de la similitud entre nodos (0-1)
        penalization=0;
        std::cout << "Node check: P = " << pnodevariation << std::endl;


        //The number of real exits are compared with the expected number of exits
        if (explorationnodes[actualnode].getnumberofexits()!=nodos[expectednextnode].getnumberofexits()) //Compara el numero de salidas del nodo actual y el nodo esperado
        {
            std::cout << "Exits number different." << std::endl;
            if (abs(explorationnodes[actualnode].getnumberofexits()-nodos[expectednextnode].getnumberofexits())==1) //Exit difference=1
            {
                //re-Scan of the node
                std::cout << "Re-scaning." << std::endl;
                sensoreadings(actualnode,nodos);
                pnodevariation=nodecomparison(actualnode,expectednextnode,nodos);
                //Re-compare of exits
                if (explorationnodes[actualnode].getnumberofexits()!=nodos[expectednextnode].getnumberofexits())
                {
                    if (abs(explorationnodes[actualnode].getnumberofexits()-nodos[expectednextnode].getnumberofexits())==1) //Exit difference=1
                    {
                        //Penalization
                        penalization=0.2; //penaliza
                        std::cout << "Number of exits different by 1. Penalization." << std::endl;

                    }
                    else //Exit difference>1
                    {
                        //Bad node
                        std::cout << "Number of exits different by more than 1. Bad node." << std::endl;
                        pnodevariation=0;
                    }
                }

            }
            else //Exit difference>1
            {
                //Bad node
                std::cout << "More than 1 exit different. Bad node." << std::endl;
                pnodevariation=0;
            }
        }
        pnodevariation=pnodevariation-penalization;
        pastuncertainty=uncertainty;

        if (pnodevariation<0)
        {
            pnodevariation=0;
        }



        if (pnodevariation>0.9)
        {
            uncertainty=uncertainty+0.2;
            if (uncertainty>1)
            {
                uncertainty=1;
            }
        }
        else if (pnodevariation<0.2)
        {
            //Bad node known, do not change uncertainty
        }
        else
        {
            uncertainty=uncertainty*pnodevariation;
        }


        if (nodos[actualnode].getnumberofOOI()!=0)
        {
            OOIdetectionR = OOIdetection(mt);
            if (OOIdetectionR<OOIdetectionRatio)
            {
                //OOI detected
                OOIcomparison=nodos[actualnode].getOOI_ID(0);
                for (int j=0;j<OOIlist.size()-1;j++)
                {
                    if (OOIlist.at(j).first==OOIcomparison)
                    {
                        std::cout << "OOI ID_" << OOIcomparison << " identifyed." << std::endl;
                        std::cout << "Checking OOI with the database."<<std::endl;
                        checkOOInode=nodos[OOIlist.at(j).second].getnodenumber(); //Node where the robot is.

                        if (actualnode!=checkOOInode)
                        {
                            std::cout << "Expected position wrong. OOI confirmed the real position. "<<std::endl;
                            std::cout << "Actual node: "<< checkOOInode <<std::endl;
                            actualnode=checkOOInode;
                            pastnode=checkOOInode;
                            pnodevariation=1;
                            uncertainty=1;

                        }
                        else
                        {
                            std::cout << "Position confirmed by the OOI."<<std::endl;
                            uncertainty=1;
                        }

                    }
                }
            }

        }

        std::cout << "Position uncertainty = " << uncertainty << std::endl;


        //Results of node comparison
        if (pnodevariation>0.6)
        {
            //Good comparison
            //std::cout << "Tunnel to node " << actualnode << " identified."<< std::endl;
            solutionpathindex++;
            //actualnode=solutionpath[solutionpathindex];
            if (actualnode==solutionpath[solutionpath.size()-1])
            {
                std::cout << std::endl;
                std::cout << "***** End node reached correctly *****" << std::endl;
                std::cout << "Ending program... " << std::endl;
                std::cout << std::endl;
                break;
            }



        }
        else
        {
            //Bad comparison

            //if the actualnode is the first node there is no past node
            if (first!=0)
            {

                std::cout << "Node " << expectednextnode << " missed. Checking for mistakes in previous tunnel choice."<< std::endl;
                int notfound=1;
                for (int i=0;i<explorationnodes[pastnode].getnumberofexits();i++) //gets the number of exits of the past node
                {
                    if (explorationnodes[pastnode].getexitprop(i,0)==expectednextnode) //looks in every exit looking for the correct tunnel
                    {
                        //expectednextnode=explorationnodes[pastnode].getexitprop(i,0);
                        chosenexit=i;
                        std::cout << "Checking the map for detecting tunnel mistakes."<< std::endl;

                        std::cout << "Mistaken tunnel choosed confirmed by map simmilarities."<< std::endl;
                        std::cout << "Trying to return to the previous node ."<< std::endl;
                        uncertainty=pastuncertainty+0.2;
                        if (uncertainty>1)
                        {
                            uncertainty=1;
                        }
                        std::cout << "Choosing the correct tunnel."<< std::endl;
                        //PRINT HERE TUNNEL CHANGE
                        std::cout << "Going back to the previous node."<< std::endl;

                        //Tunnel print
                        int a=actualnode;
                        int b=pastnode;
                        vector<int> temp;

                        for(int j=0;j<numtuneles;j++)
                        {
                            temp=tuneles[j].getendings();


                            if(temp.at(0)==a && temp.at(1)==b)
                            {

                                std::cout << std::endl;
                                tuneles[j].printtunnel();
                                std::cout << std::endl;

                            }


                            if(temp.at(0)==b && temp.at(1)==a)
                            {
                                std::cout << std::endl;
                                tuneles[j].reverseprinttunnel();
                                std::cout << std::endl;

                            }

                        }


                        std::cout << "Previous node (" << pastnode << ") reached correctly."<< std::endl;
                        actualnode=pastnode;
                        notfound=0;
                    }

                }
                if (notfound==1)
                {
                    //Añadir condicion cuando no encuentra la salida que se quiere
                    std::cout << "LOST."<< std::endl;
                    error=1;
                    break;

                    //Ojo CAMBIAR
                    //_______________________________________________________________________________________
                }
            }
        }



    }
}




int Exploration::lost(Node *nodos,int Numnodos,int actualnode)
{
    std::cout << "----- Robot lost -----" << std::endl;
    std::cout << std::endl;
    std::cout << "Looking for the most probable current node according to similarities. " << std::endl;
        //-------------------- Node read ----------------------------------------------------------------------

        //The robot get the readings of the node
        sensoreadings(actualnode,nodos);

        //-------------------- Search node simmilarities ------------------------------------------------------------


        vector<float> lostprobabilities;
        int indexmax=0;
        float valuemax=0;
        float tempcompare;
        //-----------------------------------------
        std::cout.setstate(std::ios_base::failbit);
        //-----------------------------------------

        for (int i=0;i<Numnodos;i++)
        {
            tempcompare=nodecomparison(actualnode,i,nodos);
            lostprobabilities.push_back(tempcompare);
            std::cout << " P = " << tempcompare << std::endl;
            if (lostprobabilities.at(i)>valuemax)
            {
                valuemax=lostprobabilities.at(i);
                indexmax=i;
            }
        }
        //-----------------------------------------
        std::cout.clear();
        //-----------------------------------------

        actualnode=indexmax;

        std::cout << "Node (" << actualnode << ") is the most probable current node." << std::endl;
        std::cout << std::endl;
        return actualnode;

//        //-------------------- Two possibilities ----------------------------------------------------------------------



//        if (valuemax>0.5)//Lost node is a known node
//        {

//            actualnode=indexmax;

//            if (nolink==0) //Means its not the first node discovered in a row.
//            {
//                //Needs to create a link between nodes

//                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//            }
//            fin=1;
//            return actualnode;
//        }
//        else //Lost node is an unknwon node
//        {

//            //-------------------- Register the node ----------------------------------------------------------------------

//            std::cout << "Actual node doesnt match any map node. Registering the node." << std::endl;
//            actualnode=Numnodos;
//            Numnodos++;

//            explorationnodes[actualnode].setnodenumber(actualnode+1); //OJO revisar
//            //Hacer que lea los datos de un fichero pero como si los hubiese obtenido de los sensores

//            //-------------------- Link if needed ----------------------------------------------------------------------

//            if (nolink==0) //Means its not the first node discovered in a row.
//            {
//                //Needs to create a link between nodes


//            }

//            //-------------------- Exit selection ----------------------------------------------------------------------

//            //Hacerlo ir por una salida random
//            int num;
//            int lower=0;
//            int upper=explorationnodes[actualnode].getnumberofexits()-1;
//            num = (rand() % (upper - lower + 1)) + lower;
//            std::cout << num << std::endl;

//            //-------------------- Register the tunnel ----------------------------------------------------------------------

//            //Ir creando tunel segun avanza por la ruta




//            //New node arrived

//            nolink=0;
//        }


//        //Tener en cuenta que pasa si llega a un nodo desconocido ciego.

}

