#include <iostream>
#include <ctime>
#include "Listas.h"
#include "Listas.cpp"

using namespace std;

struct sSillas
{
    bool estado;
    bool tipo;
    char* id;
};

struct sPelicula
{
    string nombre;
    string hora_inicio;
    string hora_fin;
    int dia;
    int mes;
    int anho;
    string nombre_imagen;
};

struct sSalas
{
    string id;
    int cant_sillas;
    int sillas_disponibles;
    Lista<sPelicula>* Lista_peliculas;
    Lista<sSillas>* Lista_sillas;
};

void imprimirPeliculas (Lista<sPelicula>* peliculas)
{
    Nodo<sPelicula>* aux = peliculas->cab;
    while(aux!=NULL)
    {
        cout<<"\t\tNombre: "<<(aux->info).nombre<<endl;
        cout<<"\t\tFecha: "<<(aux->info).dia<<"/"<<(aux->info).mes<<"/"<<(aux->info).anho<<endl;
        cout<<"\t\tHorario: "<<(aux->info).hora_inicio<<" - "<<(aux->info).hora_fin<<endl;
        cout<<endl;
        aux = aux->sig;
    }
}

void imprimirSalas(Lista<sSalas>* salas)
{
    Nodo<sSalas>* aux = salas->cab;
    int pos = 1;
    while(aux!=NULL)
    {
        cout<<"Numero "<<pos<<endl;
        cout<<"\tSala: "<<(aux->info).id<<endl;
        cout<<"\tCantidad de sillas: "<<(aux->info).cant_sillas<<endl;
        cout<<"\tDisponibles: "<<(aux->info).sillas_disponibles<<endl;
        cout<<"\tPeliculas"<<endl;
        imprimirPeliculas((aux->info).Lista_peliculas);
        cout<<endl;
        pos++;
        aux = aux->sig;
    }
}

bool verificarIdSala (Lista<sSalas>* salas, string id)
{
    Nodo<sSalas>* aux = salas->cab;
    while(aux!=NULL)
    {
        if((aux->info).id == id)
        {
            return true;
        }
        aux = aux->sig;
    }
    return false;
}

bool verificarNombrePelicula (Lista<sPelicula>* peliculas, string nombre)
{
    Nodo<sPelicula>* aux = peliculas->cab;
    while(aux != NULL)
    {
        if((aux->info).nombre == nombre)
        {
            return true;
        }
        aux = aux->sig;
    }
    return false;
}

void adicionarSala (Lista<sSalas>* salas)
{
    string id;
    sSalas sala;
    do
    {
        cout<<"Ingrese el id de la sala: ";
        cin>>id;
    }
    while (verificarIdSala(salas, id));
    sala.id = id;
    cout<<"Ingrese la cantidad de sillas de la sala: ";
    cin>>sala.cant_sillas;
    cout<<"Ingrese la cantidad de sillas disponibles: ";
    cin>>sala.sillas_disponibles;
    sala.Lista_peliculas = crearLista<sPelicula>();
    sala.Lista_sillas = crearLista<sSillas>();
    insertar(salas, sala);
    cout<<"Sala agregada con exito"<<endl;
}

void agregarPelicula (Lista<sSalas>* salas, Lista<sPelicula>* peliculas)
{
    int pos;
    string nom;
    if (vacia(salas))
    {
        cout<<"No hay salas en el sistema"<<endl;
    }
    else
    {
        imprimirSalas(salas);
        cout<<"Ingrese el numero de la sala en la cual va a presentar la pelicula: ";
        cin>>pos;
        if (pos <= tamano(salas))
        {
            Nodo<sSalas>* aux = salas->cab;
            int p = 1;
            while(aux!=NULL)
            {
                if (p == pos)
                {
                    sPelicula pelicula;
                    do
                    {
                        cout<<"Ingrese el nombre de la pelicula: ";
                        cin>>nom;
                    }
                    while (verificarNombrePelicula(peliculas, nom));
                    pelicula.nombre = nom;
                    time_t now = time(0);
                    tm *ltm = localtime(&now);
                    pelicula.dia = ltm->tm_mday;
                    pelicula.mes = 1+ltm->tm_mon;
                    pelicula.anho = 1900+ltm->tm_year;
                    cout<<"La fecha de publicacion de la pelicula es: "<<pelicula.dia<<"/"<<pelicula.mes<<"/"<<pelicula.anho<<endl;
                    cout<<"Ingrese la hora de inicio de la pelicula: ";
                    cin>>pelicula.hora_inicio;
                    cout<<"Ingrese la hora de fin de la pelicula: ";
                    cin>>pelicula.hora_fin;
                    cout<<"Ingrese el nombre de la imagen de la pelicula: ";
                    cin>>pelicula.nombre_imagen;
                    insertar((aux->info).Lista_peliculas, pelicula);
                    insertar(peliculas, pelicula);
                    cout<<"Pelicula agergada con exito"<<endl;
                }
                p++;
                aux = aux->sig;
            }
        }
        else
        {
            cout<<"Sala no existe"<<endl;
        }

        char aggr;
        do {

        } while(aggr == 'S' || aggr == 'N');
    }
}

int main()
{
    Lista<sSalas>* salas = crearLista<sSalas>();
    Lista<sPelicula>* peliculas = crearLista<sPelicula>();
    int n;
    do
    {
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
        switch(n)
        {
        case 1:
            adicionarSala(salas);
            break;
        case 2:
            break;
        case 3:
            agregarPelicula(salas, peliculas);
            imprimirSalas(salas);
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

    }
    while(n == 1 || n == 2 || n == 3 || n == 4 || n == 5 || n == 6 || n == 7 || n == 8 || n == 9 || n == 10 || n == 11);
    return 0;
}
