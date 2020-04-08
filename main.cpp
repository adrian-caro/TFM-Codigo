#include "Node.h"
#include "Tunnel.h"
using namespace std;
#include <iostream>

int main()
{

    Node nodo1("tipasdasdasdo",1,3);
    Tunnel tunel1("Tunelito", 1000, 1, 2, 2, 1);


    nodo1.printnode();
    tunel1.printtunnel();
    return 0;
    //prueba
}
