#include "Client.h"
#include <iostream>

Client::Client(int id, const std::string& name)
    : id(id), name(name) {}

void Client::display() const {
    std::cout << "ID: " << id << ", Name: " << name << std::endl;
}

int Client::getId() const { return id; }
const std::string& Client::getName() const { return name; }