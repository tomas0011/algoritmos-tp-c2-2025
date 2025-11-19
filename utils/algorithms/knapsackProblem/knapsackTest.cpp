#include "knapsack.h"    // la versión nueva de la mochila
#include <iostream>
using namespace std;

int main() {
    Package p1(1, "Laptop", 400.0, 1, 3.0);
    Package p2(2, "Celular", 250.0, 1, 1.0);
    Package p3(3, "Libro", 40.0, 1, 2.0);
    Package p4(4, "Campera", 120.0, 1, 1.5);
    Package p5(5, "Zapatillas", 150.0, 1, 2.5);
    Package p6(6, "Microfono", 250.0, 1, 1.0);
    Package p7(7, "Auriculares", 20.0, 1, 0.1);
    Package p8(8, "Diamante", 2000.0, 10, 1.0);

    // -----------------------------
    // CAMBIO: usamos List en lugar de vector
    // -----------------------------
    List paquetes;
    paquetes.push(any(p1));
    paquetes.push(any(p2));
    paquetes.push(any(p3));
    paquetes.push(any(p4));
    paquetes.push(any(p5));
    paquetes.push(any(p6));
    paquetes.push(any(p7));
    paquetes.push(any(p8));

    double pesoMaximo = 5.0;

    // -----------------------------
    ResultadoMochila r = resolverMochila(paquetes, pesoMaximo);

    cout << "PRECIO MAXIMO: " << r.precioMaximo << endl;
    cout << "PAQUETES SELECCIONADOS:" << endl;

    Node* nodo = r.paquetesSeleccionados.getHead();
        while (nodo != nullptr) {
            Package p = any_cast<Package>(nodo->getData());
            cout << " - ID " << p.getId()
                << " | Nombre: " << p.getName()
                << " | Peso: " << p.getWeight()
                << " | Valor: " << p.getPrice()
                << endl;

            nodo = nodo->getNext();
        }

        cout << "==============================" << endl;

        return 0;
}
