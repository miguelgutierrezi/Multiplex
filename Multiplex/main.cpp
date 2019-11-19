#include <iostream>
#include "Listas.h"

using namespace std;

struct sSillas
{
    bool estado;
    bool tipo;
    char* id;
};

struct sHorario
{
    int fecha_inicio;
    int fecha_fin;
};

struct sPelicula
{
    string nombre;
    sHorario tiempo;
    string nombre_imagen;
};

struct sSalas
{
    string id;
    int cant_sillas;
    int sillas_disponibles;
    Lista<sPelicula>*Lista_peliculas;
    Lista<sSillas>* Lista_sillas;
};

void adicionarSala (Lista<sSalas> salas, int &cant_salas) {

}

int main()
{

    int n;
    do {
        cout<<"Bienvenido al Multiplex"<<endl;
        cout<<"\t1. Agregar sala"<<endl;
        cout<<"\t2. Agregar sillas"<<endl;
        cout<<"\t3. Agregar pelicula"<<endl;
        cout<<"\t4. Eliminar sala"<<endl;
        cout<<"\t5. Eliminar sillas"<<endl;
        cout<<"\t6. Eliminar pelicula"<<endl;
        cout<<"\t7. Comprar tiquete"<<endl;
        cout<<"\t8. Consultar cartelera"<<endl;
        cout<<"\t9. Consultar salas por pelicula"<<endl;
        cout<<"\t10. Consultar ingreso de personas por fecha"<<endl;
        cout<<"\t11. Consultar venta de tiquetes por fecha"<<endl;
        cout<<"\t0. Salir"<<endl;
        cout<<"Que desea hacer?: ";
        cin>>n;
        switch(n) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            break;
        case 0:
            cout<<"Gracias por utilizar nuestros servicios"<<endl;
            break;
        }

    } while(n == 1 || n == 2 || n == 3 || n == 4 || n == 5 || n == 6 || n == 7 || n == 8 || n == 9 || n == 10 || n == 11);
    return 0;
}
