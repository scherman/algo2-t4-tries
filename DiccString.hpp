#ifndef DICC_STRING_H_
#define DICC_STRING_H_

#include "Conj.hpp"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;


template<typename T>
class DiccString {
        public:
                /**
                CONSTRUCTOR
                * Construye un diccionario vacio.
                **/
                DiccString();

                /**
                CONSTRUCTOR POR COPIA
                * Construye un diccionario por copia.
                **/
                DiccString(const DiccString<T>&);


                /**
                DESTRUCTOR
                **/
                ~DiccString();

                /**
                DEFINIR
                * Recibe una clave con su significado de tipo T y la define.
                * Si ya estaba definida, la reescribe.
                **/
                void Definir(const string& clave, const T& significado);

                /**
                DEFINIDO?
                * Devuelve un bool, que es true si la clave pasada está definida en
                * el diccionario.
                **/
                bool Definido(const string& clave) const;

                /**
                OBTENER
                * Dada una clave, devuelve su significado.
                * PRE: La clave está definida.
                --PRODUCE ALIASING--
				-- Versión modificable y no modificable
                **/
				const T& Obtener(const string& clave) const;
                T& Obtener(const string& clave);

                /**
                OBTENER
                * Dada una clave, la borra del diccionario junto a su significado.
                * PRE: La clave está definida.
                --PRODUCE ALIASING--
                **/
                void Borrar(const string& clave);


                /**
                CLAVES
                * Devuelve las claves del diccionario.
                --NO PRODUCE ALIASING--
                **/
                const Conj<string>& Claves() const;

        private:

                struct Nodo{
                    Nodo** siguientes;
                    T* definicion;
                    Nodo(){
//                        std::cout << "Nodo creado " << this << std::endl;
						siguientes = new Nodo*[256];
                        for (int i = 0; i < 256; ++i){
                            siguientes[i] = NULL;
                        }
                        definicion = NULL;
                    }

                    Nodo(const Nodo &n) {
//                        std::cout << "Nodo creado por copia " << this << std::endl;
                        definicion =  n.definicion == NULL ? NULL : new T(*n.definicion);
                        siguientes = new Nodo*[256];
                        for (int i = 0; i < 256; ++i){
                            siguientes[i] = n.siguientes[i] == NULL ? NULL : new Nodo(*n.siguientes[i]);
                        }
                    }

                    ~Nodo(){
//                        std::cout << "Nodo borrado " << this <<  std::endl;
                        delete definicion;
                        for (int i = 0; i < 256; ++i){
                            delete siguientes[i];
                        }
						delete [] siguientes;
                    }
                };

                //TODO: funciones auxiliares

                Nodo* raiz;
                Conj<string> claves;

                const int cantSiguientes (const Nodo &nodo) const;
};


template <typename T>
DiccString<T>::DiccString()
    : raiz(NULL), claves(){
}


template <typename T>
DiccString<T>::DiccString(const DiccString& d) : claves(d.claves) {
    raiz = d.raiz != NULL ? new Nodo(*d.raiz) : NULL;
}

template <typename T>
DiccString<T>::~DiccString(){
    delete raiz;
}


template <typename T>
void DiccString<T>::Definir(const string& clave, const T& significado){
    if (raiz == NULL) raiz = new Nodo();

    // Recorro la clave hasta que el siguiente es un NULL.
    Nodo* actual = raiz;
    int i = 0;
    while (i < clave.length()) {
        if (actual->siguientes[(int)clave[i]] == NULL) break;
        actual = actual->siguientes[(int)clave[i]];
        ++i;
    }

    // Creo camino que falta
    for (int n=i; n < clave.length(); ++n) {
        // Creo un nodo en la posicion de la letra y sigo
        Nodo* nuevo = new Nodo();
        actual->siguientes[(int)clave[n]] = nuevo;
        actual = nuevo;
    }
    if (actual->definicion != NULL) delete actual->definicion;
    actual->definicion = new T(significado);
    claves.insertar(clave);
}


template <typename T>
bool DiccString<T>::Definido(const string& clave) const{
    return claves.pertenece(clave);
}

template <typename T>
T& DiccString<T>::Obtener(const string& clave) {
    Nodo* actual = raiz;
    for (int i = 0; i < clave.length(); ++i) {
        actual = actual->siguientes[(int)clave[i]];
    }
    return *(actual->definicion);
}


template <typename T>
const T& DiccString<T>::Obtener(const string& clave) const {
    Nodo* actual = raiz;
    for (int i = 0; i < clave.length(); ++i) {
        actual = actual->siguientes[(int)clave[i]];
    }
    return *(actual->definicion);
}


template <typename T>
const Conj<string>& DiccString<T>::Claves() const{
    return claves;
}


template <typename T>
void DiccString<T>::Borrar(const string& clave) {
    if (raiz == NULL) return;

    // Recorro toda la clave. Guardo actual en ultimo si tiene 2+ hijos o si tiene una definicion
    Nodo *actual = raiz, *ultimo = raiz;
    int indiceBifurcacion = 0;
    for(int i = 0; i < clave.length(); ++i) {
        actual = actual->siguientes[(int)clave[i]];
        if ( (cantSiguientes(*actual) > 1) || (actual->definicion != NULL) && (i != clave.length()-1)) {
            ultimo = actual;
            indiceBifurcacion = i;
        }
    }

    // Elimino todos los nodos a partir de ultimo
    if (cantSiguientes(*actual) == 0) {
        // La clave a borrar no es un prefijo de otra clave
        if (ultimo == raiz) {
            if (claves.cardinal() == 1) {
                // Era la unica clave entonces borro el arbol completo
                delete raiz;
                raiz = NULL;
            } else {
                // La raiz contiene una definicion. Dejo la raiz y borro lo demas
                delete raiz->siguientes[(int)clave[0]];
                raiz->siguientes[(int)clave[0]] = NULL;
            }
        } else {
            // Borro a partir de la ultima bifurcacion
            delete ultimo->siguientes[(int)clave[indiceBifurcacion+1]];
            ultimo->siguientes[(int)clave[indiceBifurcacion+1]] = NULL;
        }
    } else {
        // La clave a borrar es prefijo de otra clave. Solo borro la definicion
        delete actual->definicion;
        actual->definicion = NULL;
    }
    claves.remover(clave);
}

template <typename T>
const int DiccString<T>::cantSiguientes(const typename DiccString<T>::Nodo &nodo) const {
    int cantSiguientes = 0;
    for(int i = 0; i < 256; ++i) {
        if (nodo.siguientes[i] != NULL) ++cantSiguientes;
    }
    return cantSiguientes;
}


#endif
