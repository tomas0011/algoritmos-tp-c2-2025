#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <any>

using namespace std;

class Node {
private:
    any data;
    Node* next;

public:
    Node(any newData, Node* nextNode = nullptr)
        : data(newData), next(nextNode) {}

    any getData() const { return data; }
    Node* getNext() const { return next; }
    void setNext(Node* nextNode) { next = nextNode; }
};

class List {
private:
    Node* head;

public:
    List() : head(nullptr) {}

    ~List() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->getNext();
            delete temp;
        }
    }

    void unshift(any data) {
        Node* newNode = new Node(data, head);
        head = newNode;
    }

    void push(any data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        Node* current = head;
        while (current->getNext() != nullptr)
            current = current->getNext();
        current->setNext(newNode);
    }

    void display() const {
        Node* current = head;
        while (current != nullptr) {
            try {
                if (current->getData().type() == typeid(int))
                    cout << any_cast<int>(current->getData());
                else if (current->getData().type() == typeid(string))
                    cout << any_cast<string>(current->getData());
                else
                    cout << "[obj]";
            } catch (const bad_any_cast& e) {
                cout << "[error]";
            }
            cout << " -> ";
            current = current->getNext();
        }
        cout << "NULL" << endl;
    }

    bool contains(any value) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->getData().type() == value.type()) {
                if (current->getData().type() == typeid(int) &&
                    any_cast<int>(current->getData()) == any_cast<int>(value))
                    return true;
                else if (current->getData().type() == typeid(string) &&
                         any_cast<string>(current->getData()) == any_cast<string>(value))
                    return true;
            }
            current = current->getNext();
        }
        return false;
    }
};

#endif // LIST_H
