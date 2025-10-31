#include <iostream>
#include <vector>
#include <limits>
#include "../../dataStructures/graph/Graph.h"

//const Graph& g significa “recibo un grafo por referencia, pero no lo voy a modificar”.
void dijkstra(const Graph& g, int origen) {
    int n = g.getSize();
    vector<double> dist(n, numeric_limits<double>::infinity());
    vector<int> previo(n, -1);
    vector<bool> visitado(n, false);

    dist[origen] = 0;

    for (int i = 0; i < n; i++) {
        // encontrar el nodo no visitado con menor distancia
        double minDist = numeric_limits<double>::infinity();
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (!visitado[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }

        if (u == -1) break;
        visitado[u] = true;

        // Reorganizar aristas
        for (const auto& edge : g.getNode(u)->getEdges()) {
            int v = edge.getDestino();
            double peso = edge.getPeso();
            if (dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                previo[v] = u;
            }
        }
    }

    // Mostrar resultados
    cout << "\nDistancias mínimas desde el nodo " << origen << " (" 
         << g.getNode(origen)->dataToString() << "):\n";
    for (int i = 0; i < n; i++) {
        cout << "  -> " << g.getNode(i)->dataToString() << " = ";
        if (dist[i] == numeric_limits<double>::infinity())
            cout << "∞";
        else
            cout << dist[i];
        cout << endl;
    }
}
