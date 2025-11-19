#include "knapsack.h"
#include "entities/package/Package.h"
#include "utils/dataStructures/list/List.h" 

// ---------------------------------------------------------

void backtrackingList(
    Node* nodo,                 // nodo actual
    double pesoActual,
    double precioActual,
    double pesoMaximo,
    List& solucionActual,       
    ResultadoMochila& mejor
) {
    if (nodo == nullptr) {
        // Fin de lista = caso base
        if (precioActual > mejor.precioMaximo) {
            mejor.precioMaximo = precioActual;
            mejor.paquetesSeleccionados = solucionActual;
        }
        return;
    }

    // Obtener el paquete guardado como "any"
    Package paquete = any_cast<Package>(nodo->getData());

    // -------------------------------
    //  NO TOMAR ESTE PAQUETE
    // -------------------------------
    backtrackingList(
        nodo->getNext(),
        pesoActual,
        precioActual,
        pesoMaximo,
        solucionActual,
        mejor
    );

    // -------------------------------
    //  TOMAR ESTE PAQUETE (si entra)
    // -------------------------------
    double nuevoPeso = pesoActual + paquete.getWeight();

    if (nuevoPeso <= pesoMaximo) {
        solucionActual.push(any(paquete));

        backtrackingList(
            nodo->getNext(),
            nuevoPeso,
            precioActual + paquete.getPrice(),
            pesoMaximo,
            solucionActual,
            mejor
        );

        solucionActual.popBack();
    }
}

// ---------------------------------------------------------

ResultadoMochila resolverMochila(
    const List& paquetes,
    double pesoMaximo
) {
    ResultadoMochila mejor;
    mejor.precioMaximo = 0;

    List solucionActual;  // empieza vacía

    backtrackingList(
        paquetes.getHead(),   // empezamos desde el primer nodo
        0,
        0,
        pesoMaximo,
        solucionActual,
        mejor
    );

    return mejor;
}