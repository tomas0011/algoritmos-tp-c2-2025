#include "../../../entities/Package.h"
#include "../../../list/List.h"   // donde tengas tu List

struct ResultadoMochila {
    double precioMaximo;
    std::vector<Package> paquetesSeleccionados;
};

// ---------------------------------------------------------

void backtrackingList(
    Node* nodo,                         // nodo actual de la lista
    double pesoActual,
    double precioActual,
    double pesoMaximo,
    std::vector<Package>& solucionActual,
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
        solucionActual.push_back(paquete);

        backtrackingList(
            nodo->getNext(),
            nuevoPeso,
            precioActual + paquete.getValue(),
            pesoMaximo,
            solucionActual,
            mejor
        );

        solucionActual.pop_back();
    }
}

// ---------------------------------------------------------

ResultadoMochila resolverMochila(
    const List& paquetes,
    double pesoMaximo
) {
    ResultadoMochila mejor = {0, {}};
    std::vector<Package> actual;

    backtrackingList(
        paquetes.getHead(),   // empezamos desde el primer nodo
        0,
        0,
        pesoMaximo,
        actual,
        mejor
    );

    return mejor;
}