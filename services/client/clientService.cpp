#include "clientService.h"
#include <iostream>

ClientService::ClientService(List& clientsList) : clients(clientsList) {}

void ClientService::createClient(int id, const std::string& name) {
    Client newClient(id, name);
    clients.push(newClient);
    std::cout << "Client created successfully." << std::endl;
}

Client* ClientService::getClientById(int id) {
    Node* current = clients.getHead();
    while (current != nullptr) {
        try {
            Client c = std::any_cast<Client>(current->getData());
            if (c.getId() == id) {
                return new Client(c); // return a copy
            }
        } catch (const std::bad_any_cast& e) {
            // skip invalid entries
        }
        current = current->getNext();
    }
    return nullptr;
}

void ClientService::updateClient(int id, const std::string& newName) {
    List newList;
    Node* current = clients.getHead();
    bool found = false;

    while (current != nullptr) {
        try {
            Client c = std::any_cast<Client>(current->getData());
            if (c.getId() == id) {
                Client updatedClient(id, newName);
                newList.push(updatedClient);
                found = true;
            } else {
                newList.push(c);
            }
        } catch (const std::bad_any_cast& e) {
            // skip invalid entries
        }
        current = current->getNext();
    }

    if (found) {
        clients = newList;
        std::cout << "Client updated successfully." << std::endl;
    } else {
        std::cout << "Client with ID " << id << " not found." << std::endl;
    }
}

void ClientService::deleteClient(int id) {
    List newList;
    Node* current = clients.getHead();
    bool found = false;

    while (current != nullptr) {
        try {
            Client c = std::any_cast<Client>(current->getData());
            if (c.getId() != id) {
                newList.push(c);
            } else {
                found = true;
            }
        } catch (const std::bad_any_cast& e) {
            // skip invalid entries
        }
        current = current->getNext();
    }

    if (found) {
        clients = newList;
        std::cout << "Client deleted successfully." << std::endl;
    } else {
        std::cout << "Client with ID " << id << " not found." << std::endl;
    }
}

void ClientService::displayAllClients() {
    std::cout << "All Clients:" << std::endl;
    Node* current = clients.getHead();
    while (current != nullptr) {
        try {
            Client c = std::any_cast<Client>(current->getData());
            c.display();
        } catch (const std::bad_any_cast& e) {
            std::cout << "Error displaying client." << std::endl;
        }
        current = current->getNext();
    }
}

int ClientService::getClientCount() {
    return clients.getSize();
}