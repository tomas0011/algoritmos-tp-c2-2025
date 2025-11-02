#include "List.h"
#include "../../algorithms/sort/mergeSort.cpp"
#include <string>
#include <iostream>
using namespace std;

// Test: cd utils/dataStructures/list && g++ listTest.cpp -o listTest && ./listTest

// Definimos la clase Persona fuera de main
struct Persona {
    string nombre;
    int edad;
};

int main() {
    List lista;

    // Enteros
    lista.push(42);
    lista.unshift(10);
    lista.unshift(string("Aca empiezo"));

    // Strings
    lista.push(string("Hola"));
    lista.push(string("Mundo"));

    // Objetos
    Persona p1{"Laura", 30};
    Persona p2{"Tomás", 25};
    lista.push(p1);
    lista.push(p2);

    cout << "Contenido de la lista:" << endl;
    lista.display();

    cout << "\n¿Contiene a Laura? "
          << (lista.contains(p1) ? "Sí ✅" : "No ❌") << endl;

    return 0;
}
