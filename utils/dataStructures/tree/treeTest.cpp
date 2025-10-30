#include "Tree.h"
#include <string>
#include <iostream>
using namespace std;

int main() {
    Tree arbol = Tree(5);

    arbol.getRaiz()->setLeft(new Node(3));
    arbol.getRaiz()->getLeft()->setLeft(new Node(1));
    arbol.getRaiz()->getLeft()->getLeft()->setLeft(new Node(0));
    arbol.getRaiz()->getLeft()->getLeft()->setRight(new Node(2));
    arbol.getRaiz()->getLeft()->setRight(new Node(5));
    arbol.getRaiz()->getLeft()->getRight()->setLeft(new Node(4));
    arbol.getRaiz()->getLeft()->getRight()->setRight(new Node(6));

    arbol.getRaiz()->setRight(new Node(8));
    arbol.getRaiz()->getRight()->setLeft(new Node(7));
    cout << "Contenido del árbol:" << endl;

    arbol.display();

    return 0;
}
