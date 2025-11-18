#include "knapsack.cpp"   // la versión nueva de la mochila
#include "../../entities/Package.h"
#include "../../list/List.h"
#include <iostream>
using namespace std;

int main() {
    Package p1("Laptop", 3.0, 400.0);
    Package p2("Celular", 1.0, 250.0);
    Package p3("Libro", 2.0, 40.0);
    Package p4("Campera", 1.5, 120.0);
    Package p5("Zapatillas", 2.5, 150.0);
    Package p6("Microfono", 1.0, 250.0);
    Package p7("Auriculares", 0.1, 20.0);
    Package p8("Diamante", 1, 2000.0);

    // -----------------------------
    // CAMBIO: usamos List en lugar de vector
    // -----------------------------
    List paquetes;
    paquetes.push(p1);
    paquetes.push(p2);
    paquetes.push(p3);
    paquetes.push(p4);
    paquetes.push(p5);
    paquetes.push(p6);
    paquetes.push(p7);
    paquetes.push(p8);

    double pesoMaximo = 5.0;

    // -----------------------------
    ResultadoMochila r = resolverMochila(paquetes, pesoMaximo);

    cout << "PRECIO MAXIMO: " << r.precioMaximo << endl;
    cout << "PAQUETES SELECCIONADOS:" << endl;

    for (auto& p : r.paquetesSeleccionados) {
        cout << " - " << p.getId()
            << " | peso: " << p.getWeight()
            << " | valor: " << p.getValue()
            << endl;
    }

    return 0;
}