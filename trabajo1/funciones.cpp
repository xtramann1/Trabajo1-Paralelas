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
string Maximos[100][3];
string Artisticos[100][3];
string Humanismo[100][3];
string Tecnico[100][3];

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
void merge(int columna, int inicio, int mitad, int final){
    int i,j,k;
    int elementosIzq = mitad - inicio + 1;
    int elementosDer = final - mitad;

    string MI[elementosIzq][6];
    string MD[elementosDer][6];

    for(int i = 0; i < elementosIzq; i++){
        MI[i][0] = Matriz[inicio+i][0];
        MI[i][1] = Matriz[inicio+i][1];
        MI[i][2] = Matriz[inicio+i][2];
        MI[i][3] = Matriz[inicio+i][3];
        MI[i][4] = Matriz[inicio+i][4];
        MI[i][5] = Matriz[inicio+i][5];
    }
    for(int j = 0; j < elementosDer; j++){
        MD[j][0] = Matriz[mitad + 1 + j][0];
        MD[j][1] = Matriz[mitad + 1 + j][1];
        MD[j][2] = Matriz[mitad + 1 + j][2];
        MD[j][3] = Matriz[mitad + 1 + j][3];
        MD[j][4] = Matriz[mitad + 1 + j][4];
        MD[j][5] = Matriz[mitad + 1 + j][5];
    }

    i = 0;
    j = 0;
    k = inicio;

    while(i < elementosIzq && j < elementosDer){
        if(MI[i][columna] <= MD[j][columna]){
            Matriz[k][0] = MI[i][0];
            Matriz[k][1] = MI[i][1];
            Matriz[k][2] = MI[i][2];
            Matriz[k][3] = MI[i][3];
            Matriz[k][4] = MI[i][4];
            Matriz[k][5] = MI[i][5];
            i++;
        }else{
            Matriz[k][0] = MD[j][0];
            Matriz[k][1] = MD[j][1];
            Matriz[k][2] = MD[j][2];
            Matriz[k][3] = MD[j][3];
            Matriz[k][4] = MD[j][4];
            Matriz[k][5] = MD[j][5];
            j++;
        }
        k++;
    }

    while(j < elementosDer){
        Matriz[k][0] = MD[j][0];
        Matriz[k][1] = MD[j][1];
        Matriz[k][2] = MD[j][2];
        Matriz[k][3] = MD[j][3];
        Matriz[k][4] = MD[j][4];
        Matriz[k][5] = MD[j][5];
        j++;
        k++;
    }

    while(i < elementosIzq){
        Matriz[k][0] = MI[i][0];
        Matriz[k][1] = MI[i][1];
        Matriz[k][2] = MI[i][2];
        Matriz[k][3] = MI[i][3];
        Matriz[k][4] = MI[i][4];
        Matriz[k][5] = MI[i][5];
        i++;
        k++;
    }
}

void mergesort(int columna, int InicioIzq, int FinalDer){
    if(InicioIzq < FinalDer){
        int FinalIzq = InicioIzq + ((FinalDer-InicioIzq)/2);
        mergesort(columna, InicioIzq, FinalIzq);
        mergesort(columna, FinalIzq+1, FinalDer);
        merge(columna, InicioIzq, FinalIzq, FinalDer);
    }
}

void PasarMatriz(string matriz[][3], int columna){
    mergesort(columna,0,14999);
    int a=0,b=0;
    while(a<100){
        if(Matriz[14999-b][0] == "0"){
            b++;
        }
        else{
            matriz[a][0] = Matriz[14999-b][0];
            matriz[a][1] = Matriz[14999-b][1];
            matriz[a][2] = Matriz[14999-b][columna];
            Matriz[14999-b][0] = "0";
            a++;
        }
    }
}

void Acsv(string ArchivoCSV, string matriz[][3]){
    ofstream archivo;
    archivo.open("al/"+ArchivoCSV+".csv", ios::out | ios::app);
    for(int i=0; i<100; i++){
        archivo<<matriz[i][0]<<"; "<<matriz[i][1]<<"; "<<matriz[i][2]<<endl;
    }
}
