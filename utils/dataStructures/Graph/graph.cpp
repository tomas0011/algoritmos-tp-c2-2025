#include "Graph.h"

int main() {

    //creo el grafo g
    Graph g;

    //le agrego nodos al grafo
    int a = g.addNode("A");
    int b = g.addNode("B");
    int c = g.addNode("C");


    //le agrego aristas al grafo
    g.addEdge(a, b, 5.0); //de a, hacia b, con peso 5
    g.addEdge(a, c, 2.5); //de a, hacia c, con peso 2.5
    g.addEdge(b, c, 1.0); //de b, hacia c, con peso 1

    g.display();
    return 0;
}