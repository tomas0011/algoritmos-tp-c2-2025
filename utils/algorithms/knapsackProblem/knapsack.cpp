#include <vector>
#include "../../entities/Package.h"

struct ResultadoMochila {
    double precioMaximo;
    std::vector<Package> paquetesSeleccionados;
};

void backtracking(
    const std::vector<Package>& paquetes,
    int indice,
    double pesoActual,
    double precioActual,
    double pesoMaximo,
    std::vector<Package>& solucionActual,
    ResultadoMochila& mejor
);

ResultadoMochila resolverMochila(
    const std::vector<Package>& paquetes,
    double pesoMaximo
);

// ---------------------------------------------------------
// IMPLEMENTACIONES
// ---------------------------------------------------------

void backtracking(
    const std::vector<Package>& paquetes,
    int indice,
    double pesoActual,
    double precioActual,
    double pesoMaximo,
    std::vector<Package>& solucionActual,
    ResultadoMochila& mejor
) {
    if (indice == paquetes.size()) {
        if (precioActual > mejor.precioMaximo) {
            mejor.precioMaximo = precioActual;
            mejor.paquetesSeleccionados = solucionActual;
        }
        return;
    }

    // NO TOMAR
    backtracking(paquetes, indice + 1, pesoActual, precioActual,
                pesoMaximo, solucionActual, mejor);

    // TOMAR
    double nuevoPeso = pesoActual + paquetes[indice].getWeight();
    double nuevoPrecio = precioActual + paquetes[indice].getValue();

    if (nuevoPeso <= pesoMaximo) {
        solucionActual.push_back(paquetes[indice]);
        backtracking(paquetes, indice + 1, nuevoPeso, nuevoPrecio,
                    pesoMaximo, solucionActual, mejor);
        solucionActual.pop_back();
    }
}

ResultadoMochila resolverMochila(
    const std::vector<Package>& paquetes,
    double pesoMaximo
) {
    ResultadoMochila mejor = {0, {}};
    std::vector<Package> actual;

    backtracking(paquetes, 0, 0, 0, pesoMaximo, actual, mejor);

    return mejor;
}
