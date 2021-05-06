#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

/* se hace una matriz con 6 columnas, en la primera y segunda 
va identificado el alumno, en la 3 el promedio maximo del alumno,
en la 4 el promedio artistico, en la 5 el humanista y la sexta el
tecnico, para crear los archivos se seleccionara las columnas (1,2,3)
(1,2,4), (1,2,5) y (1,2,6) siendo asi cada archivo con 3 columnas   
*/

/*
cuando se crea un archivo, al colocar cada estudiante en cada uno,
se verificara con un cero, entonces si su indicador es cero no 
se agregara a mas archivos ya que ya fue guardado.
*/

string Matriz[15000][6];

void agregarAmatriz(){
    ifstream infile("estudiantes.csv");
    string line ="";
    string dato = "";
    float sumaMaximos = 0;
    float sumaArtisticos = 0;
    float sumaHumanistas = 0;
    float sumaTecnicos = 0;
    float conversion = 0;
    int i = 0;
    while(i<15000){
        for(int j=0;j<10;j++){
            if(j == 9){
                getline(infile,line,'\n');
            }
            else{
                getline(infile,line,';');
            }
            if(j != 0 && j != 1){
                line.replace(line.find('"'),1,"");
                istringstream(line) >> (conversion);
                sumaMaximos = sumaMaximos + conversion;
                if(j == 2 || j == 6){
                    sumaHumanistas = sumaHumanistas + conversion;
                }
                else{
                    if(j == 8 || j == 9){
                        sumaArtisticos = sumaArtisticos + conversion;
                    }
                    else{
                        if(j == 4 || j == 5 || j == 7){
                            sumaTecnicos = sumaTecnicos + conversion;
                        }
                    }
                }
            }
            else{
                Matriz[i][j] = line;
            }
        }
        dato = to_string(sumaMaximos/8);
        Matriz[i][2] = dato;
        dato = to_string(sumaArtisticos/2);
        Matriz[i][3] = dato;
        dato = to_string(sumaHumanistas/2);
        Matriz[i][4] = dato;
        dato = to_string(sumaTecnicos/3);
        Matriz[i][5] = dato;
        sumaTecnicos = 0;
        sumaHumanistas = 0;
        sumaArtisticos = 0;
        sumaMaximos = 0;
        i++;
    }
}

void imprimir(){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 6; j++){
            cout<<" "<<Matriz[i][j];
        }
        cout<<endl;
    }
}

// Agregar un int para seleccionar la columna a agregar
void merge(int columna, int InicioIzq, int FinalIzq, int FinalDer){
    int a, b, c, tamanoDer, tamanoIzq;
    tamanoIzq = FinalIzq - InicioIzq + 1;
    tamanoDer = FinalDer - FinalIzq;
    string MatrizIzq[tamanoIzq][6];
    string MatrizDer[tamanoDer][6];
    for(a = 0; a < tamanoIzq; a++){
        MatrizIzq[a][columna] = Matriz[InicioIzq+a][columna];
    }
    for(b = 0; b < tamanoDer; b++){
        MatrizDer[b][columna] = Matriz[FinalIzq+1+b][columna];
    }
    a = 0;
    b = 0;
    c = InicioIzq;
    while(a<tamanoIzq && b<tamanoDer){
        if(MatrizIzq[a][columna] <= MatrizDer[b][columna]){
            Matriz[c][columna] = MatrizIzq[a][columna];
            a++;
        }
        else{
            Matriz[c][columna] = MatrizDer[b][columna];
            b++;
        }
        c++;
    }
    while(a<tamanoIzq){
        Matriz[c][columna] = MatrizDer[a][columna];
        a++;
        c++;
    }
    while(b<tamanoDer){
        Matriz[c][columna] = MatrizDer[b][columna];
        b++;
        c++;
    }
}

void mergesort(int columna, int InicioIzq, int FinalDer){
    int FinalIzq;
    if(InicioIzq < FinalDer){
        FinalIzq = InicioIzq+(FinalDer+InicioIzq)/2;
        mergesort(columna, InicioIzq, FinalIzq);
        mergesort(columna, FinalIzq+1, FinalDer);
        merge(columna, InicioIzq, FinalIzq, FinalDer);
    }
}
