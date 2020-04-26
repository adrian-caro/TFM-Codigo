#include "Dijkstra.h"
using namespace std;

Dijkstra::Dijkstra(int sta, int goa,vector<vector<Pair>> n)
{
    std::cout << "------Path search required------" << std::endl;
    std::cout << std::endl;
    nodestart=sta;
    nodegoal=goa;
    nodelist=n;
    std::cout << "Finding path from node " << sta << " to node " << goa << "."<< std::endl;

}

void Dijkstra::algorithm()
{
    int solucionado=0; //just a flag for finishing
    int primermuerto=0;

    //Put node start in Open list with
    //vector of vectors [node,heuristic,cost,function (h+c),parent]
    open.push_back({nodestart,0,0,0,-1});



    //while open list isnt empty,do:
    while (!open.empty())
    {
        primermuerto=primermuerto+1;


        //search for the open node with lowest f value
        int small=999999;
        int position=0;
        int c=0;

        for (std::vector<vector<int>>::iterator it = open.begin(); it != open.end(); ++it)
        {

            if (it->at(3) < small)
            {
                small=it->at(3);
                position=c; //contains the index number of the smallest f value vector
            }

            c++;
        }

        //in case that chosen node is solution, finish the execution.
        if (open[position].at(0) == nodegoal)
        {
            std::cout << "Solution found" << std::endl;
            closed.push_back(open[position]);
            solucionado=1;
            break;
        }


        //Sends father node to closed list
        if (primermuerto==1) //first iteration, has no father
        {
            //linea 115
            closed.push_back({nodestart,0,0,0,-1}); //father 0
        }
        else //not first
        {
            closed.push_back(open[position]);
        }

        //saves the index as father
        int fatherindex;
        fatherindex=closed.size()-1;




        int indextoevaluate;
        indextoevaluate=open[position].at(0); //extracts the node number of the lowest function value


        // variables
         int node;
         //int length;
         int alreadyinclose=0;
         int alreadyinopen=0;
         //now all links with other nodes are explored
         for (std::vector<Pair>::iterator it = nodelist[indextoevaluate].begin(); it !=nodelist[indextoevaluate].end(); ++it)
         {
             node=it->first;
             //length=it->second;


             //1.check if this node already exists in closed list

             for (std::vector<vector<int>>::iterator it = closed.begin(); it != closed.end(); ++it)
             {
                 if (it->at(0) == node)
                 {
                     alreadyinclose=1;
                 }
             }



             //2.if is not closed, then proceed

             if (alreadyinclose==0)
             {
                 //2.1 check if it already is in open, and if it is, update its cost.
                 for (std::vector<vector<int>>::iterator it = open.begin(); it != open.end(); ++it)
                 {
                     if (it->at(0) == node)
                     {
                         alreadyinopen=1;
                         //if the cost is lower, it updates it.
                         if (it->at(2) > open[position].at(2)+1)
                         {
                             it->at(2) = open[position].at(2)+1;
                         }
                     }
                 }

                 //2.2 if it isnt in open, then adds it.
                 if (alreadyinopen==0)
                 {
                     open.push_back({node,0,open[position].at(2)+1,open[position].at(2)+1+0,fatherindex});
                     //[node,heuristic,cost,function (h+c),parent]
                 }

             }



             alreadyinclose=0;
             alreadyinopen=0;
         }

        //Deletes selected node from open list
         open.erase(open.begin()+position);

    }


    if (solucionado==0)
    {
        std::cout << "No solution found." << std::endl;
    }

    if (solucionado==1)
    {
        //Now takes part the backtracking of the nodes solution path.

        vector<int> path;

        //int final;
        int i=closed.size()-1;
        //adds node by node tracking its parents
        while (closed[i].at(4)!=-1)
        {
            path.push_back(closed[i].at(0));
            i=closed[i].at(4);
        }

        //add initial node
        path.push_back(nodestart);

        //but.. now temp vector must be flipped.
        std::reverse(path.begin(),path.end());

        std::cout << "Solution node sequence: ";
        for (int j=0; j<path.size(); j++)
        {
            std::cout << path[j] << " ";
        }
    }
        std::cout << std::endl;


}
