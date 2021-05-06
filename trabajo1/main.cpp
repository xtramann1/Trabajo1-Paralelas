#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include "funciones.cpp"

using namespace std;

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
    return EXIT_SUCCESS;
}