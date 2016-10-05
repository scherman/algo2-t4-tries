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
						siguientes = new Nodo*[256];
                        for (int i = 0; i < 256; i++){
                            siguientes[i] = NULL;
                        }
                        definicion = NULL;
                    }
                    ~Nodo(){
                        delete definicion;
						delete [] siguientes;
                    }
                };

                //TODO: funciones auxiliares

                Nodo* raiz;
                Conj<string> claves;
};


template <typename T>
DiccString<T>::DiccString()
    : raiz(NULL), claves(){
}


template <typename T>
DiccString<T>::DiccString(const DiccString& d) {

}

template <typename T>
DiccString<T>::~DiccString(){

}


template <typename T>
void DiccString<T>::Definir(const string& clave, const T& significado){
    if (raiz == NULL) raiz = new Nodo();

    // Recorro hasta que se bifurca
    Nodo* actual = raiz;
    bool bifurco = false;
    int i = 0;
    while (i < clave.length() && !bifurco) {
        if (actual->siguientes[(int)clave[i]] == NULL) {
            actual->siguientes[(int)clave[i]] = new Nodo();
            bifurco = true;
        }
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
    actual->definicion = new T(significado);
    claves.insertar(clave);
}


template <typename T>
bool DiccString<T>::Definido(const string& clave) const{

}

template <typename T>
T& DiccString<T>::Obtener(const string& clave) {

}


template <typename T>
const T& DiccString<T>::Obtener(const string& clave) const {

}


template <typename T>
const Conj<string>& DiccString<T>::Claves() const{
    return claves;
}


template <typename T>
void DiccString<T>::Borrar(const string& clave) {

}


#endif
