#include <iostream>
#include <ctime>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "Listas.h"
#include "Listas.cpp"

using namespace std;

struct sSillas
{
    bool estado;
    char tipo;
    int id;
    float valor;
};

struct sPelicula
{
    string nombre;
    int hora_inicio;
    int hora_fin;
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

struct sTiquete {
    string cliente;
    string pelicula;
    string sala;
    int dia;
    int mes;
    int anho;
    int hora_inicio;
    int hora_fin;
    float costo;
};

sPelicula obtenerPelicula(Lista<sPelicula>* peliculas, int pos)
{
    Nodo<sPelicula> * aux;
    aux = peliculas->cab;
    int p = 0;
    while(aux != NULL)
    {
        if(pos == p)
        {
            return aux->info;
        }
        aux = aux->sig;
        p++;
    }
}

sSillas obtenerSilla(Lista<sSillas>* sillas, int pos)
{
    Nodo<sSillas> * aux;
    aux = sillas->cab;
    int p = 0;
    while(aux != NULL)
    {
        if(pos == p)
        {
            return aux->info;
        }
        aux = aux->sig;
        p++;
    }
}

void imprimirSillas (Lista<sSillas>* sillas)
{
    Nodo<sSillas>* aux = sillas->cab;
    int pos = 1;
    while(aux!=NULL)
    {
        cout<<"  Numero de Silla: "<<pos<<endl;
        cout<<"\t  id: "<<(aux->info).id<<endl;
        cout<<"\t  Tipo de silla: "<<(aux->info).tipo<<endl;
        cout<<"\t  Estado: "<<(aux->info).estado<<endl;
        cout<<endl;
        pos++;
        aux = aux->sig;
    }
}

void imprimirSillasDisponibles (Lista<sSillas>* sillas)
{
    Nodo<sSillas>* aux = sillas->cab;
    int pos = 1;
    while(aux!=NULL)
    {
        if (!(aux->info).estado)
        {
            cout<<"  Numero de Silla: "<<pos<<endl;
            cout<<"\t  id: "<<(aux->info).id<<endl;
            cout<<"\t  Tipo de silla: "<<(aux->info).tipo<<endl;
            cout<<"\t  Estado: "<<(aux->info).estado<<endl;
            cout<<endl;
        }
        pos++;
        aux = aux->sig;
    }
}

void imprimirPeliculas (Lista<sPelicula>* peliculas)
{
    Nodo<sPelicula>* aux = peliculas->cab;
    int pos = 1;
    while(aux!=NULL)
    {
        cout<<"  Numero de Pelicula: "<<pos<<endl;
        cout<<"\t  Nombre: "<<(aux->info).nombre<<endl;
        cout<<"\t  Fecha: "<<(aux->info).dia<<"/"<<(aux->info).mes<<"/"<<(aux->info).anho<<endl;
        cout<<"\t  Horario: "<<(aux->info).hora_inicio<<" - "<<(aux->info).hora_fin<<endl;
        cout<<endl;
        pos++;
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
    float general, preferencial;
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
    cout<<"Ingrese el costo de las sillas preferenciales: ";
    cin>>preferencial;
    cout<<"Ingrese el costo de las sillas generales: ";
    cin>>general;
    for (int i = 0; i < sala.cant_sillas/2; i++)
    {
        sSillas silla;
        silla.id = tamano(sala.Lista_sillas) + 1;
        silla.tipo = 'P';
        silla.estado = false;
        silla.valor = preferencial;
        insertar(sala.Lista_sillas, silla);
    }
    for (int i = sala.cant_sillas/2; i < sala.cant_sillas; i++)
    {
        sSillas silla;
        silla.id = tamano(sala.Lista_sillas) + 1;
        silla.tipo = 'G';
        silla.estado = false;
        silla.valor = general;
        insertar(sala.Lista_sillas, silla);
    }
    insertar(salas, sala);
    cout<<"Sala agregada con exito"<<endl;
}

void agregarPelicula (Lista<sSalas>* salas, Lista<sPelicula>* peliculas)
{
    int pos;
    string nom;
    sPelicula pelicula;
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
                    cout<<"Ingrese la hora de inicio de la pelicula (Formato militar, Ej: 1100): ";
                    cin>>pelicula.hora_inicio;
                    cout<<"Ingrese la hora de fin de la pelicula (Formato militar, Ej: 1100): ";
                    cin>>pelicula.hora_fin;
                    cout<<"Ingrese el nombre de la imagen de la pelicula: ";
                    cin>>pelicula.nombre_imagen;
                    insertar((aux->info).Lista_peliculas, pelicula);
                    insertar(peliculas, pelicula);
                    cout<<"Pelicula agregada con exito"<<endl;
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
        do
        {
            cout<<"Desea agregar la pelicula a otra sala (S para si, N para no): ";
            cin>>aggr;
            if (aggr == 'S' || aggr == 's')
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
                            insertar((aux->info).Lista_peliculas, pelicula);
                            cout<<"Pelicula agregada con exito"<<endl;
                        }
                        p++;
                        aux = aux->sig;
                    }
                }
                else
                {
                    cout<<"Sala no existe"<<endl;
                }
            }
        }
        while(aggr == 'S' || aggr == 's');
    }
}

void adicionarSillas (Lista<sSalas>* salas)
{
    int pos, cant;
    char categoria;
    if (vacia(salas))
    {
        cout<<"No hay salas en el sistema"<<endl;
    }
    else
    {
        imprimirSalas(salas);
        cout<<"Ingrese el numero de la sala a la cual va agregar sillas: ";
        cin>>pos;
        if (pos <= tamano(salas))
        {
            Nodo<sSalas>* aux = salas->cab;
            int p = 1;
            while(aux!=NULL)
            {
                if (p == pos)
                {
                    cout<<"Cuantas sillas desea agregar: ";
                    cin>>cant;
                    for (int i = 0; i < cant; i++)
                    {
                        sSillas silla;
                        cout<<"Ingrese la categoria de la silla (P: Preferencial, G: General): ";
                        cin>>categoria;
                        if (categoria=='P' || categoria=='p')
                        {
                            silla.tipo = 'P';
                        }
                        else
                        {
                            silla.tipo = 'G';
                        }
                        silla.id = tamano((aux->info).Lista_sillas) + 1;
                        silla.estado = false;
                        insertar((aux->info).Lista_sillas, silla);
                        cout<<"Silla agregada con exito"<<endl;
                    }
                    (aux->info).cant_sillas += cant;
                    (aux->info).sillas_disponibles += cant;
                }
                p++;
                aux = aux->sig;
            }
        }
        else
        {
            cout<<"Sala no existe"<<endl;
        }
    }
}

void eliminarSala (Lista<sSalas>* salas)
{
    int pos;
    if (vacia(salas))
    {
        cout<<"No hay salas en el sistema"<<endl;
    }
    else
    {
        imprimirSalas(salas);
        cout<<"Ingrese el numero de la sala que va a eliminar: ";
        cin>>pos;
        if (pos <= tamano(salas))
        {
            eliminar(salas, pos-1);
        }
        else
        {
            cout<<"Sala no existe"<<endl;
        }
    }
}

void eliminarPelicula(Lista<sSalas>* salas, Lista<sPelicula>* peliculas)
{
    int pos, posP;
    string nombre;
    if (vacia(peliculas))
    {
        cout<<"No hay salas en el sistema"<<endl;
    }
    else
    {
        imprimirPeliculas(peliculas);
        cout<<"Ingrese el nombre de la pelicula que va a eliminar: ";
        cin>>pos;
        if (pos <= tamano(peliculas))
        {
            sPelicula peli = obtenerPelicula(peliculas, pos - 1);
            nombre = peli.nombre;
            Nodo<sSalas>* aux = salas->cab;
            while(aux!=NULL)
            {
                Nodo<sPelicula>* auxP = (aux->info).Lista_peliculas->cab;
                int posS = 1;
                while (auxP != NULL)
                {
                    if ((auxP->info).nombre == nombre)
                    {
                        posP = posS;
                    }
                    posS++;
                    auxP = auxP->sig;
                }
                eliminar((aux->info).Lista_peliculas, posP - 1);
                aux = aux->sig;
            }
            eliminar(peliculas, pos-1);
        }
        else
        {
            cout<<"Pelicula no existe"<<endl;
        }
    }
}

void eliminarSilla(Lista<sSalas>* salas)
{
    int pos;
    int posS;
    if (vacia(salas))
    {
        cout<<"No hay salas en el sistema"<<endl;
    }
    else
    {
        imprimirSalas(salas);
        cout<<"Ingrese el numero de la sala que va a eliminar: ";
        cin>>pos;
        if (pos <= tamano(salas))
        {
            Nodo<sSalas>* aux = salas->cab;
            int p = 1;
            while(aux!=NULL)
            {
                if (pos == p)
                {
                    imprimirSillasDisponibles((aux->info).Lista_sillas);
                    cout<<"Ingrese el numero de la silla que quiere eliminar: ";
                    cin>>posS;
                    if (posS <= tamano((aux->info).Lista_sillas))
                    {
                        eliminar((aux->info).Lista_sillas, posS - 1);
                        (aux->info).cant_sillas--;
                        (aux->info).sillas_disponibles--;
                    }
                    else
                    {
                        cout<<"Silla inexistente"<<endl;
                    }
                }
                p++;
                aux = aux->sig;
            }
        }
        else
        {
            cout<<"Sala no existe"<<endl;
        }
    }
}

void consultaSalasPorPelicula (Lista<sSalas>* salas, Lista<sPelicula>* peliculas)
{
    string nom;
    if (vacia(salas))
    {
        cout<<"No hay salas en el sistema"<<endl;
    }
    else
    {
        imprimirPeliculas(peliculas);
        cout<<"Ingrese el nombre de la pelicula que quiere consultar: ";
        cin>>nom;

        Nodo<sSalas>* aux = salas->cab;
        int p = 1;
        while (aux != NULL)
        {
            Nodo<sPelicula>* auxP = (aux->info).Lista_peliculas->cab;
            while (auxP != NULL)
            {
                if ((auxP->info).nombre == nom)
                {
                    cout<<"Numero: "<<p<<endl;
                    cout<<"Sala: "<<(aux->info).id<<endl;
                    cout<<"Dia: "<<(auxP->info).dia<<"/"<<(auxP->info).mes<<"/"<<(auxP->info).anho<<endl;
                    cout<<"Horario: "<<(auxP->info).hora_inicio<<" - "<<(auxP->info).hora_fin<<endl;
                    cout<<endl;
                }
                auxP = auxP->sig;
            }
            p++;
            aux = aux->sig;
        }
    }
}

void consultarCartelera (Lista<sSalas>* salas)
{
    ofstream myfile;
    myfile.open ("cartelera.html");
    myfile << "<!DOCTYPE html><html><head></head><body>";
    myfile<<"<h1 style=\"text-align: center;\">Consultar cartelera</h1>";
    myfile<<"<table style=\"height: 104px; margin-left: auto; margin-right: auto;\" border=\"2\" width=\"584\"\">";
    myfile<<"<tbody><tr>";
    myfile<<"<td style=\"width: 110px; text-align: center;\">Sala</td>";
    myfile<<"<td style=\"width: 110px; text-align: center;\">Película</td>";
    myfile<<"<td style=\"width: 110px; text-align: center;\">Fecha</td>";
    myfile<<"<td style=\"width: 110px; text-align: center;\">Hora inicio</td>";
    myfile<<"<td style=\"width: 110px; text-align: center;\">Hora fin</td>";
    myfile<<"<td style=\"width: 110px; text-align: center;\">Imagen</td></tr>";

    Nodo<sSalas>* aux = salas->cab;

    while(aux != NULL)
    {
        Nodo<sPelicula>* auxP = (aux->info).Lista_peliculas->cab;
        while(auxP != NULL)
        {
            myfile<<"<tr><td style=\"width: 110px; text-align: center;\">"<<(aux->info).id;
            myfile<<"</td><td style=\"width: 110px; text-align: center;\">"<<(auxP->info).nombre;
            myfile<<"</td><td style=\"width: 110px; text-align: center;\">"<<(auxP->info).dia<<"/"<<(auxP->info).mes<<"/"<<(auxP->info).anho;
            myfile<<"</td><td style=\"width: 110px; text-align: center;\">"<<(auxP->info).hora_inicio;
            myfile<<"</td><td style=\"width: 110px; text-align: center;\">"<<(auxP->info).hora_fin;
            myfile<<"</td><td style=\"width: 110px; text-align: center;\">";
            myfile<<"<img src=\""<<(auxP->info).nombre_imagen<<"\" width=\"80\" height=\"100\"/>";
            myfile<<"</tr>";
            auxP = auxP->sig;
        }
        aux = aux->sig;
    }

    myfile << "</tbody></table></body></html>";
    myfile.close();
}

void ingresoDePersonasPorFecha (Lista<sTiquete>* tiquetes) {
    int dia1 = -1, dia2 = -1, mes1 = -1, mes2 = -1, anho1 = -1, anho2 = -1, cont = 0;

    if (vacia(tiquetes)) {
        cout<<"No se han vendido tiquetes"<<endl;
    }
    else {
        cout<<"Ingrese el dia de la fecha inicial a comparar: ";
        cin>>dia1;
        cout<<"Ingrese el mes de la fecha inicial a comparar: ";
        cin>>mes1;
        cout<<"Ingrese el anho de la fecha inicial a comparar: ";
        cin>>anho1;

        cout<<"Ingrese el dia de la fecha final a comparar: ";
        cin>>dia2;
        cout<<"Ingrese el mes de la fecha final a comparar: ";
        cin>>mes2;
        cout<<"Ingrese el anho de la fecha final a comparar: ";
        cin>>anho2;

        Nodo<sTiquete>* aux = tiquetes->cab;
        while (aux != NULL) {
            if(((aux->info).anho >= anho1) && ((aux->info).anho <= anho2)) {
                if(((aux->info).mes >= mes1) && ((aux->info).mes <= mes2)) {
                    if(((aux->info).dia >= dia1) && ((aux->info).dia <= dia2)) {
                        cont++;
                    }
                }
            }
            aux = aux->sig;
        }

        cout<<"Un total de "<<cont<<" personas, ingresaron al multiplex entre "<<dia1<<"/"<<mes1<<"/"<<anho1<<" y "<<dia2<<"/"<<mes2<<"/"<<anho2<<endl;
    }
}

void tiquetesPorFecha(Lista<sTiquete>* tiquetes) {
    int dia1, dia2, mes1, mes2, anho1, anho2;
    float valor = 0;
    if (vacia(tiquetes)) {
        cout<<"No se han vendido tiquetes"<<endl;
    }
    else {
        cout<<"Ingrese el dia de la fecha inicial a comparar: ";
        cin>>dia1;
        cout<<"Ingrese el mes de la fecha inicial a comparar: ";
        cin>>mes1;
        cout<<"Ingrese el anho de la fecha inicial a comparar: ";
        cin>>anho1;

        cout<<"Ingrese el dia de la fecha final a comparar: ";
        cin>>dia2;
        cout<<"Ingrese el mes de la fecha final a comparar: ";
        cin>>mes2;
        cout<<"Ingrese el anho de la fecha final a comparar: ";
        cin>>anho2;

        Nodo<sTiquete>* aux = tiquetes->cab;
        while (aux != NULL) {
            if(((aux->info).anho >= anho1) && ((aux->info).anho <= anho2)) {
                if(((aux->info).mes >= mes1) && ((aux->info).mes <= mes2)) {
                    if(((aux->info).dia >= dia1) && ((aux->info).dia <= dia2)) {
                        valor += (aux->info).costo;
                    }
                }
            }
            aux = aux->sig;
        }

        cout<<"Un total de $"<<valor<<" se recaudaron entre "<<dia1<<"/"<<mes1<<"/"<<anho1<<" y "<<dia2<<"/"<<mes2<<"/"<<anho2<<endl;
    }
}

void comprarTiquete (Lista<sSalas>* salas, Lista<sTiquete>* tiquetes, Lista<sPelicula>* peliculas) {
    int pos, cant, posS, dia, mes, anho;
    float total = 0;
    string nom, cliente, sala;
    int hora_inicio, hora_fin;
    ofstream myfile;
    sTiquete tiquete;
    if (vacia(salas))
    {
        cout<<"No hay salas en el sistema"<<endl;
    }
    else
    {
        imprimirPeliculas(peliculas);
        cout<<"Ingrese el nombre de la pelicula que quiere consultar: ";
        cin>>nom;

        Nodo<sSalas>* aux = salas->cab;
        int p = 1;
        while (aux != NULL)
        {
            Nodo<sPelicula>* auxP = (aux->info).Lista_peliculas->cab;
            while (auxP != NULL)
            {
                if ((auxP->info).nombre == nom)
                {
                    cout<<"Numero: "<<p<<endl;
                    cout<<"Sala: "<<(aux->info).id<<endl;
                    cout<<"Dia: "<<(auxP->info).dia<<"/"<<(auxP->info).mes<<"/"<<(auxP->info).anho<<endl;
                    cout<<"Horario: "<<(auxP->info).hora_inicio<<" - "<<(auxP->info).hora_fin<<endl;
                    cout<<endl;

                    dia = (auxP->info).dia;
                    mes = (auxP->info).mes;
                    anho = (auxP->info).anho;
                    hora_inicio = dia = (auxP->info).hora_inicio;
                    hora_fin = (auxP->info).hora_fin;
                }
                auxP = auxP->sig;
            }
            p++;
            aux = aux->sig;
        }

        cout<<"Ingrese el numero de Sala en la que quiere ver la pelicula: ";
        cin>>pos;
        aux = salas->cab;
        p = 1;
        while (aux != NULL)
        {
            if (p == pos && tamano((aux->info).Lista_sillas) > 0) {
                imprimirSillasDisponibles((aux->info).Lista_sillas);
                cout<<"Cuantas sillas desea comprar?: ";
                cin>>cant;
                if (cant <= tamano((aux->info).Lista_sillas)) {
                    sala = (aux->info).id;
                    for (int i = 0; i < cant; i++) {
                        sSillas s;
                        cout<<"Ingrese la posicion de la silla "<<i+1<<" a comprar: ";
                        cin>>posS;
                        s = obtenerSilla((aux->info).Lista_sillas, posS - 1);
                        Nodo<sSillas>* auxS = (aux->info).Lista_sillas->cab;
                        int pS = 1;
                        while (auxS != NULL) {
                            if (pS == posS) {
                                (auxS->info).estado = true;
                            }
                            pS++;
                            auxS = auxS->sig;
                        }
                        total += s.valor;
                    }
                    cout<<"Ingrese el nombre del cliente: ";
                    cin>>cliente;

                    string nomArchivo = "Factura" + cliente + ".txt";
                    myfile.open(nomArchivo.c_str());
                    myfile<<"Tu factura"<<endl;
                    myfile<<"Cliente: "<<cliente<<endl;
                    myfile<<"Pelicula: "<<nom<<endl;
                    myfile<<"Sala: "<<sala<<endl;
                    myfile<<"Fecha: "<<dia<<"/"<<mes<<"/"<<anho<<endl;
                    myfile<<"Horario: "<<hora_inicio<<" - "<<hora_fin<<endl;
                    myfile<<"Cantidad de boletas: "<<cant<<endl;
                    myfile<<"Total a pagar: $"<<total;
                    myfile.close();

                    tiquete.cliente = cliente;
                    tiquete.anho = anho;
                    tiquete.costo = total;
                    tiquete.dia = dia;
                    tiquete.hora_fin = hora_fin;
                    tiquete.hora_inicio = hora_inicio;
                    tiquete.mes = mes;
                    tiquete.pelicula = nom;
                    tiquete.sala = sala;
                    insertar(tiquetes, tiquete);
                    cout<<"Venta exitosa"<<endl;

                } else {
                    cout<<"No hay sillas suficientes"<<endl;
                }
            }
            aux = aux->sig;
        }
    }
}

void actualizarPrecios (Lista<sSalas>* salas) {
    float preferencial, general;
    int pos;
    if (vacia(salas))
    {
        cout<<"No hay salas en el sistema"<<endl;
    }
    else
    {
        imprimirSalas(salas);
        cout<<"Ingrese el numero de la sala que va a actualizar: ";
        cin>>pos;
        if (pos <= tamano(salas))
        {
            Nodo<sSalas>* aux = salas->cab;
            int p = 1;
            while(aux != NULL) {
                if (p == pos) {
                    cout<<"Ingrese el nuevo costo para las sillas preferenciales: ";
                    cin>>preferencial;
                    cout<<"Ingrese el nuevo costo para las sillas generales: ";
                    cin>>general;

                    Nodo<sSillas>* auxS = (aux->info).Lista_sillas->cab;
                    while(auxS != NULL) {
                        if ((auxS->info).tipo == 'P') {
                            (auxS->info).valor = preferencial;
                        }
                        else {
                            (auxS->info).valor = general;
                        }
                        auxS = auxS->sig;
                    }
                }
                aux = aux->sig;
            }
        }
        else
        {
            cout<<"Sala no existe"<<endl;
        }
    }
}

int main()
{
    Lista<sSalas>* salas = crearLista<sSalas>();
    Lista<sPelicula>* peliculas = crearLista<sPelicula>();
    Lista<sTiquete>* tiquetes = crearLista<sTiquete>();
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
        cout<<"\t12. Actualizar precios de sillas"<<endl;
        cout<<"\t0. Salir"<<endl;
        cout<<"Que desea hacer?: ";
        cin>>n;
        switch(n)
        {
        case 1:
            adicionarSala(salas);
            break;
        case 2:
            adicionarSillas(salas);
            break;
        case 3:
            agregarPelicula(salas, peliculas);
            break;
        case 4:
            eliminarSala(salas);
            break;
        case 5:
            eliminarSilla(salas);
            break;
        case 6:
            eliminarPelicula(salas, peliculas);
            break;
        case 7:
            comprarTiquete(salas, tiquetes, peliculas);
            break;
        case 8:
            consultarCartelera(salas);
            break;
        case 9:
            consultaSalasPorPelicula(salas, peliculas);
            break;
        case 10:
            ingresoDePersonasPorFecha(tiquetes);
            break;
        case 11:
            tiquetesPorFecha(tiquetes);
            break;
        case 12:
            actualizarPrecios(salas);
            break;
        case 0:
            cout<<"Gracias por utilizar nuestros servicios"<<endl;
            break;
        }

    }
    while(n == 1 || n == 2 || n == 3 || n == 4 || n == 5 || n == 6 || n == 7 || n == 8 || n == 9 || n == 10 || n == 11 || n == 12);
    return 0;
}
