#include "rviz_visual_tools/headers/Graph.h"

using namespace std;


//Creates a graph
Grafo::Grafo(vector<Enlace> const& enlaces, int N,Node *nodos)
{
    // Resize
    ListaAdyacencia.resize(N);

    // Tunnels are added
    for (auto& enlace : enlaces)
    {
        int nointroducir = 0;

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //checks if the tunnel has been added before in the source node

             //checks
        for (std::vector<Pair>::iterator it = ListaAdyacencia[enlace.nodofuente].begin(); it != ListaAdyacencia[enlace.nodofuente].end(); ++it)
        {
            if (it->first == enlace.nododestino)
            {
                nointroducir = 1;
            }

        }

            //add
        if (nointroducir == 0)
        {
            ListaAdyacencia[enlace.nodofuente].push_back(make_pair(enlace.nododestino,enlace.length));
            nodos[enlace.nodofuente].addnodoconectado(enlace.nododestino);
        }


        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        //Checks that the tunnel doesnt exits already, and if so, it adds too in the final node (Bidirectional).
        nointroducir = 0;
            //checks
        for (std::vector<Pair>::iterator it = ListaAdyacencia[enlace.nododestino].begin(); it != ListaAdyacencia[enlace.nododestino].end(); ++it)
        {
            if (it->first == enlace.nodofuente)
            {
                nointroducir = 1;
            }

        }

            //add
        if (nointroducir == 0)
        {
            ListaAdyacencia[enlace.nododestino].push_back(make_pair(enlace.nodofuente,enlace.length));
            nodos[enlace.nododestino].addnodoconectado(enlace.nodofuente);
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    }
}


void Grafo::printGraph(Grafo const& graf, int N)
{
    for (int i = 0; i < N; i++)
    {
        //Prints current node
        cout << i << " --> ";

        //Prints connected nodes
        for (Pair v : graf.ListaAdyacencia[i])
            cout << "(" << v.first << "," << v.second << ") " ;
        cout << endl;
    }
}

vector<vector<Pair>> Grafo::getlista()
{
    return ListaAdyacencia;
}
