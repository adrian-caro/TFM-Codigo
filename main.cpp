#include "Node.h"
#include "Tunnel.h"

#include <iostream>
#include <fstream>
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

    //Creo un vector de objetos nodo, que van a ir configurandose según el txt
    Node nodos[10];
    int i=0;
    while (inputdata >> name >> var1 >> var2)
    {
        //Comprueba que no se ha pasado a definir los tuneles
        if (name=="%")
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

    //inputdata >> junkheader1;
    //inputdata >> junkheader1;
    //inputdata >> junkheader1;
    //inputdata >> junkheader1;
    //inputdata >> junkheader1;
    //inputdata >> junkheader1;


    //Creo un vector de objetos tunnel, que van a ir configurandose según el txt
    Tunnel tuneles[10];



    i=0;
    std::string tunnel;
    int start, final, nuseg;
    float len, wid, hei, slo;
    while (inputdata >> tunnel >> start >> final >> len >> wid >> hei >> slo >> nuseg)
    {
        //Comprueba que no se ha pasado a definir otra cosa
        if (tunnel=="%")
        {
            std::cout << "se salio";
            break;
        };

        tuneles[i].setname(tunnel);
        tuneles[i].setstartnode(start,nodos);
        tuneles[i].setfinalnode(final,nodos);

        tuneles[i].setlength(len);
        tuneles[i].setwidth(wid);
        tuneles[i].setheight(hei);
        tuneles[i].setslope(slo);
        tuneles[i].setnumberofsegments(nuseg);
        tuneles[i].printtunnel();



        //cout << name <<" "<< var1 <<" "<< var2  <<" "<< std::endl;
        i++;
    }
    //int nodostotales=i;
//    //Imprime los nodos
//    for (i=1; i<nodostotales ;i++)
//    {
//        nodos[i].printnode();
//    }
    //Node nodo1("tipasdasdasdo",1,3);
    //Tunnel tunel1("Tunelito", 1000, 1, 2, 2, 1);


    //nodo1.printnode();
    //tunel1.printtunnel();
    return 0;
    //nodos[1].printnode();

}
