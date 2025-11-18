#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <vector>
#include "../../../entities/package/Package.h"
#include "../../../utils/dataStructures/list/List.h"

struct ResultadoMochila {
    double precioMaximo;
    std::vector<Package> paquetesSeleccionados;
};

ResultadoMochila resolverMochila(
    const List& paquetes,
    double pesoMaximo
);

#endif // KNAPSACK_H
