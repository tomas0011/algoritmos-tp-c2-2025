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

    void copyFrom(const List& other) {
        if (other.head == nullptr) {
            head = nullptr;
            return;
        }
        head = new Node(other.head->getData());
        Node* currentOther = other.head->getNext();
        Node* currentThis = head;
        while (currentOther != nullptr) {
            currentThis->setNext(new Node(currentOther->getData()));
            currentThis = currentThis->getNext();
            currentOther = currentOther->getNext();
        }
    }

public:
    List() : head(nullptr) {}

    List(const List& other) : head(nullptr) {
        copyFrom(other);
    }

    List& operator=(const List& other) {
        if (this != &other) {
            // Delete existing nodes
            Node* current = head;
            while (current != nullptr) {
                Node* temp = current;
                current = current->getNext();
                delete temp;
            }
            copyFrom(other);
        }
        return *this;
    }

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

    int getSize() const {
        int size = 0;
        Node* current = head;
        while (current != nullptr) {
            size++;
            current = current->getNext();
        }
        return size;
    }

    Node* getHead() const {
        return head;
    }

    Node* getNodeAt(int index) const {
        if (index < 0) return nullptr;
        Node* current = head;
        for (int i = 0; i < index && current != nullptr; i++) {
            current = current->getNext();
        }
        return current;
    }

    List getSublist(int start, int end) const {
        List sublist;
        Node* current = getNodeAt(start);
        for (int i = start; i < end && current != nullptr; i++) {
            sublist.push(current->getData());
            current = current->getNext();
        }
        return sublist;
    }
};

#endif // LIST_H
