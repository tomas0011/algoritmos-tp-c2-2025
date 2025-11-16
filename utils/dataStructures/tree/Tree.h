#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <any>
#include <sstream>

using namespace std;

class Node {
private:
    any data ;
    Node* left;
    Node* right;

public:
    Node(any newData)
        : data(newData), left(nullptr), right(nullptr) {}

    any getData() const { return data; }

    Node* getLeft() const { return left; }

    Node* getRight() const { return right; }

    void setLeft(Node* leftNode) { left = leftNode; }

    void setRight(Node* rightNode) { right = rightNode; }

    string dataToString() const {
        try {
            if (data.type() == typeid(int)) 
                return to_string(any_cast<int>(data));
            else if (data.type() == typeid(double)) 
                return to_string(any_cast<double>(data));
            else if (data.type() == typeid(string)) 
                return any_cast<string>(data);
            else if (data.type() == typeid(const char*)) 
                return string(any_cast<const char*>(data));
            else
                return "[unknown]";
        } catch (const bad_any_cast&) {
            return "[error]";
        }
    }

    string toString(int depth = 0) const {
        ostringstream oss;

        // sangria según el nivel de profundidad
        for (int i = 0; i < depth; ++i)
            oss << "  ";

        oss << dataToString() << "\n";

        if (left) {
            for (int i = 0; i < depth; ++i) oss << "  ";
            oss << "L: " << left->toString(depth + 1);
        }
        if (right) {
            for (int i = 0; i < depth; ++i) oss << "  ";
            oss << "R: " << right->toString(depth + 1);
        }

        return oss.str();
    }
};

class Tree {
private:
    Node* raiz;
public:
    Tree (any data) {
        this->raiz = new Node(data) ;
    }

    Node* getRaiz() const { return raiz; }

    string toString() const {
        return raiz->toString();
    }

    void display() const {
        cout << "Raiz: " << raiz->toString() << endl;
    }
};

#endif // TREE_H
