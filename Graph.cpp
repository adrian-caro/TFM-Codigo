#include "Graph.h"

using namespace std;



Grafo::Grafo(vector<Enlace> const& enlaces, int N)
{
    // Redimensiona el vector al numero de elementos de tipo vector<int>
    ListaAdyacencia.resize(N);

    // Añade enlaces al grafo
    for (auto& enlace : enlaces)
    {
        int nointroducir = 0;
        //Comprueba que el enlace a añadir no existe ya por parte del otro
        //std::cout << "myvector contains:";

        //Comprueba antes que no exista ese enlace previamente

        // insert at the end

        nointroducir = 0;
        for (std::vector<int>::iterator it = ListaAdyacencia[enlace.nodofuente].begin(); it != ListaAdyacencia[enlace.nodofuente].end(); ++it)
        {
            if (*it == enlace.nododestino)
            {
                nointroducir = 1;
            }

        }
        if (nointroducir == 0)
        {
            // Uncomment below line for undirected grafo
            ListaAdyacencia[enlace.nodofuente].push_back(enlace.nododestino);
        }

        //Al ser indirecto, se añade tambien este enlace al nodo destino.
        //Primero se ha de comprobar que no existe
        nointroducir = 0;
        for (std::vector<int>::iterator it = ListaAdyacencia[enlace.nododestino].begin(); it != ListaAdyacencia[enlace.nododestino].end(); ++it)
        {
            if (*it == enlace.nodofuente)
            {
                nointroducir = 1;
            }

        }
        if (nointroducir == 0)
        {
            // Uncomment below line for undirected grafo
            ListaAdyacencia[enlace.nododestino].push_back(enlace.nodofuente);
        }


        //prueba
    }
}

void Grafo::printGraph(Grafo const& graf, int N)
{
    for (int i = 0; i < N; i++)
    {
        // Imprime el nodo actual
        cout << i << " --> ";

        //  Imprime los nodos vecinos conectados
        for (int v : graf.ListaAdyacencia[i])
            cout << v << " ";
        cout << endl;
    }
}
