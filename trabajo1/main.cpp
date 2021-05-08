#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include "funciones.cpp"

using namespace std;

/* En esta parte se crean las matrices en el orden estipulado y posteriormente se realiza
el traspaso de estas a un archivo csv cada una de ellas*/
int main(int argc, char** argv){
    agregarAmatriz();
    PasarMatriz(Maximos,2);
    PasarMatriz(Artisticos,3);
    PasarMatriz(Humanismo,4);
    PasarMatriz(Tecnico,5);
    Acsv("maximos",Maximos);
    Acsv("artistico",Artisticos);
    Acsv("humanismo",Humanismo);
    Acsv("tecnicos",Tecnico);
    cout << "<<INTEGRANTES>>" << endl;
    cout << "Felipe González Duarte" << endl << "Fabián Urriola Poisson";
    cout << endl;
    return EXIT_SUCCESS;
}