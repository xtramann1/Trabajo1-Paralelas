#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include "funciones.cpp"

using namespace std;

int main(int argc, char** argv){
    agregarAmatriz();
    mergesort(3,0,14999);
    imprimir();
    return EXIT_SUCCESS;
}