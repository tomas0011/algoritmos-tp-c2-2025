#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client {
private:
    int id;
    std::string name;

public:
    Client(int id, const std::string& name);
    void display() const;

    // Getters
    int getId() const;
    const std::string& getName() const;
};

#endif // CLIENT_H