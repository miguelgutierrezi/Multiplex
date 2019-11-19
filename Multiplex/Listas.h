#ifndef LISTAS_H     
#define LISTAS_H    

template<typename T>
struct Nodo
{    
       T info; //Esta es la informacion de la lista       
       Nodo<T> * sig;
};

template<typename T>
struct Lista
{
       Nodo<T> * cab;
       int tam;
};


template <typename T>
Nodo<T>* crearNodo(T dato);

template<typename T>
void imprimir(Lista<T> *);

template<typename T>
void insertar(Lista<T> *, T); //Este metodo cambia segun el tipo de dato de la informacion de la lista
template<typename T>
bool vacia(Lista<T> *);
template<typename T>
int tamano(Lista<T> *);
template<typename T>
T obtenerDato(Lista<T> *, int);
template<typename T>
bool eliminar(Lista<T> *, int);

template<typename T>
void destruirLista(Lista<T> *);

template<typename T>
Lista<T> *crearLista();
                
#endif    
