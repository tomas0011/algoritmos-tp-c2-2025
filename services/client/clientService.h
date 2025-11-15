#ifndef CLIENT_SERVICE_H
#define CLIENT_SERVICE_H

#include "../../entities/client/Client.h"
#include "../../utils/dataStructures/list/List.h"
#include <iostream>

class ClientService {
private:
    List& clients;

public:
    ClientService(List& clientsList);
    
    // CRUD operations
    void createClient(int id, std::string name);
    Client* getClientById(int id);
    void updateClient(int id, std::string newName);
    void deleteClient(int id);

    // Utility functions
    void displayAllClients();
    int getClientCount();
};

#endif // CLIENT_SERVICE_H