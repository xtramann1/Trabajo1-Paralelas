#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

/* Inicialmente se declara una matriz principal con 6 columnas para guardar los datos 
correspondientes para crear los archivos csv finales, en la primera y segunda columna 
va identificado el alumno, en la 3 el promedio máximo del alumno,en la 4 el promedio artístico, 
en la 5 el humanista y la sexta el técnico.*/
string Matriz[15000][6];

//Igualmente se declaran matrices para guardar los mejores 100 promedios de cada clasificación
string Maximos[100][3];
string Artisticos[100][3];
string Humanismo[100][3];
string Tecnico[100][3];

/*En la siguiente función se comienza a agregar a la matriz princial (Matriz)
a los alumnos con sus promedios correspondientes a cada clasificación, 
al colocar cada estudiante se verificara con un cero, en otras palabras, 
si su indicador es cero no se agregará nuevamente ninguna matriz ni archivo.

Para la creación de la clasificación de los promedios de los alumnos se seleccionará
las columnas (1,2,3) (1,2,4), (1,2,5) y (1,2,6) según corresponda,
siendo asi cada matriz con 3 columnas*/

void agregarAmatriz(){
    ifstream infile("estudiantes.csv");
    string line ="";
    string dato = "";
    //Variables para determinar los promedios
    float sumaMaximos = 0;
    float sumaArtisticos = 0;
    float sumaHumanistas = 0;
    float sumaTecnicos = 0;
    float conversion = 0;
    int i = 0;
    // Se busca los datos correspondientes a los alumnos para calcular los promedios
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
        /*Se guardan los datos obtenidos en la matriz principal, ordenados según 
        el archivo "estudiantes.cvs"*/
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

// Método de ordenamiento mergesort
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

//Función para traspasar los datos ordenados por promedios de mayor a menor
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

/*Transforma los datos correspondientes a una matriz con los mejores 100 promedios
de ciertos alumnos a un archivo csv*/
void Acsv(string ArchivoCSV, string matriz[][3]){
    ofstream archivo;
    archivo.open("al/"+ArchivoCSV+".csv", ios::out | ios::app);
    for(int i=0; i<100; i++){
        archivo<<matriz[i][0]<<"; "<<matriz[i][1]<<"; "<<matriz[i][2]<<endl;
    }
}
