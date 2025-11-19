#ifndef KNAPSACK_H
#define KNAPSACK_H

#include "../../../entities/package/Package.h"
#include "../../../utils/dataStructures/list/List.h"

struct ResultadoMochila {
    double precioMaximo;
    List paquetesSeleccionados;
};

ResultadoMochila resolverMochila(
    const List& paquetes,
    double pesoMaximo
);

#endif // KNAPSACK_H
