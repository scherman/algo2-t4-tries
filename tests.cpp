#include <iostream>
#include "mini_test.h"

#include "DiccString.hpp"


//Chequea que el diccionario vacio no tenga claves
void test_claves_dicc_vacio() {
	DiccString<int> d;
	ASSERT(d.Claves().cardinal() == 0);
}

void test_constructor_copia() {
    DiccString<int> d;
    DiccString<int> a (d);
    ASSERT(a.Claves().cardinal() == 0);

    d.Definir("",15);
    d.Definir("casa",20);
    d.Definir("casita",25);
    d.Definir("casacha",30);

    DiccString<int> c (d);

    ASSERT(c.Definido(""));
    ASSERT(c.Obtener("") == 15);

    ASSERT(c.Definido("casa"));
    ASSERT(c.Obtener("casa") == 20);

    ASSERT(c.Definido("casita"));
    ASSERT(c.Obtener("casita") == 25);

    ASSERT(c.Definido("casacha"));
    ASSERT(c.Obtener("casacha") == 30);
}

//Chequea el definir y definido
void test_definir_definido() {
	DiccString<int> d;

	d.Definir("hola",42);
	ASSERT( d.Definido("hola") );
	ASSERT( !d.Definido("casona") );
 	ASSERT( !d.Definido("casa") );
    ASSERT( !d.Definido("h") );
    ASSERT( !d.Definido("casonita") );

    d.Definir("h",14);
    ASSERT( d.Definido("hola") );
    ASSERT( d.Definido("h") );
    ASSERT( !d.Definido("casona") );
    ASSERT( !d.Definido("casa") );
    ASSERT( !d.Definido("casonita") );

	d.Definir("casona",13);
	ASSERT( d.Definido("hola") );
    ASSERT( d.Definido("h") );
	ASSERT( d.Definido("casona") );
  	ASSERT( !d.Definido("casa") );
    ASSERT( !d.Definido("casonita") );

  	d.Definir("casa",6);
	ASSERT( d.Definido("hola") );
    ASSERT( d.Definido("h") );
	ASSERT( d.Definido("casona") );
  	ASSERT( d.Definido("casa") );
    ASSERT( !d.Definido("casonita") );

    d.Definir("", 2);
    ASSERT( d.Definido("") );
    ASSERT( d.Definido("hola") );
    ASSERT( d.Definido("h") );
    ASSERT( d.Definido("casona") );
    ASSERT( d.Definido("casa") );
    ASSERT( !d.Definido("casonita") );

    d.Definir("casonita", 250);
    ASSERT( d.Definido("") );
    ASSERT( d.Definido("hola") );
    ASSERT( d.Definido("h") );
    ASSERT( d.Definido("casona") );
    ASSERT( d.Definido("casa") );
    ASSERT( d.Definido("casonita") );

}



//cheque el obtener
void test_obtener() {
    DiccString<int> d;
    d.Definir("",15);
    d.Definir("casa",20);
    d.Definir("casita",25);
    d.Definir("casacha",30);

	ASSERT( d.Obtener("") == 15);
	ASSERT( d.Obtener("casa") == 20);
	ASSERT( d.Obtener("casita") == 25);
	ASSERT( d.Obtener("casacha") == 30);

}

//cheque el borrar
void test_borrar() {
	//Completar este test para:
	//Verificar que al borrar una palabra, esta deja de estar definida en el diccionario
	//Chequear que si dos palabras comparten prefijos y una de ellas se borrar, la otra debe seguir estando definida
	//Analizar que el borrado funciona bien si el diccionario tiene definido una sola palabra y esta se borra.

    DiccString<int> d;
    d.Definir("",15);
    d.Definir("casa",20);
    d.Definir("casita",25);
    d.Definir("casitita", 250);
    d.Definir("casacha",30);

    d.Borrar("casitita");
    ASSERT(d.Definido(""));
    ASSERT(d.Definido("casa"));
    ASSERT(d.Definido("casita"));
    ASSERT(d.Definido("casacha"));
    ASSERT(!d.Definido("casitita"));

    d.Borrar("casita");
    ASSERT(d.Definido(""));
    ASSERT(d.Definido("casa"));
    ASSERT(!d.Definido("casita"));
    ASSERT(d.Definido("casacha"));
    ASSERT(!d.Definido("casitita"));

    d.Borrar("casacha");
    ASSERT(d.Definido(""));
    ASSERT(d.Definido("casa"));
    ASSERT(!d.Definido("casita"));
    ASSERT(!d.Definido("casacha"));
    ASSERT(!d.Definido("casitita"));

    d.Borrar("casa");
	ASSERT(d.Definido(""));
	ASSERT(!d.Definido("casa"));
	ASSERT(!d.Definido("casita"));
	ASSERT(!d.Definido("casacha"));
    ASSERT(!d.Definido("casitita"));

    d.Borrar("");
    ASSERT(!d.Definido(""));
    ASSERT(!d.Definido("casa"));
    ASSERT(!d.Definido("casita"));
    ASSERT(!d.Definido("casacha"));
    ASSERT(!d.Definido("casitita"));


}


void test_joaco() {
    DiccString<int> d;
    d.Definir("casa",15);
    d.Definir("c",12);
    d.Borrar("c");
}

void test_claves() {
    DiccString<int> d;
    d.Definir("",15);
    d.Definir("casa",20);
    d.Definir("casita",25);
    d.Definir("casacha",30);

    ASSERT(d.Claves().pertenece(""));
    ASSERT(d.Claves().pertenece("casa"));
    ASSERT(d.Claves().pertenece("casita"));
    ASSERT(d.Claves().pertenece("casacha"));


    d.Borrar("casa");
    ASSERT(d.Claves().pertenece(""));
    ASSERT(!d.Claves().pertenece("casa"));
    ASSERT(d.Claves().pertenece("casita"));
    ASSERT(d.Claves().pertenece("casacha"));

    d.Borrar("casita");
    ASSERT(d.Claves().pertenece(""));
    ASSERT(!d.Claves().pertenece("casa"));
    ASSERT(!d.Claves().pertenece("casita"));
    ASSERT(d.Claves().pertenece("casacha"));

    d.Borrar("");
    ASSERT(!d.Claves().pertenece(""));
    ASSERT(!d.Claves().pertenece("casa"));
    ASSERT(!d.Claves().pertenece("casita"));
    ASSERT(d.Claves().pertenece("casacha"));

    d.Borrar("casacha");
    ASSERT(!d.Claves().pertenece(""));
    ASSERT(!d.Claves().pertenece("casa"));
    ASSERT(!d.Claves().pertenece("casita"));
    ASSERT(!d.Claves().pertenece("casacha"));
}


int main() {
	RUN_TEST(test_claves_dicc_vacio);
    RUN_TEST(test_constructor_copia);
	RUN_TEST(test_definir_definido);
	RUN_TEST(test_obtener);
	RUN_TEST(test_borrar);
	RUN_TEST(test_claves);
	RUN_TEST(test_joaco);
	//Realizar más test para chequear el funcionamiento del diccionario sobre trie.

	return 0;

}


