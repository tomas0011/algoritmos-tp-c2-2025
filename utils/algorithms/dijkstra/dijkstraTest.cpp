#include "../../dataStructures/Graph/Graph.h"
#include "dijkstra.cpp"

int main() {
    Graph g;
    int a = g.addNode(string("A"));
    int b = g.addNode(string("B"));
    int c = g.addNode(string("C"));
    int d = g.addNode(string("D"));
    int e = g.addNode(string("E"));
    int f = g.addNode(string("F"));

    g.addEdge(a, b, 4.0);
    g.addEdge(a, c, 2.0);
    g.addEdge(b, c, 1.0);
    g.addEdge(b, d, 5.0);
    g.addEdge(c, d, 8.0);
    g.addEdge(c, e, 10.0);
    g.addEdge(d, e, 2.0);
    g.addEdge(e, d, 2.0);
    g.addEdge(b, f, 12);
    g.addEdge(c, f, 13);

    g.display();

    dijkstra(g, a);

    return 0;
}