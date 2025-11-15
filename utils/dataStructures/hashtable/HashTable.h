#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <any>
#include <string>
#include <sstream>
#include <vector>
#include "../list/List.h"

using namespace std;

// =======================================================
// Clase HashEntry (Entrada de la tabla hash)
// =======================================================
class HashEntry {
private:
    string key;
    any value;
    bool occupied;  // indica si la celda está ocupada
    bool deleted;   // indica si la celda fue eliminada (para linear probing)

public:
    HashEntry() : key(""), value(nullptr), occupied(false), deleted(false) {}
    
    HashEntry(string k, any v) 
        : key(k), value(v), occupied(true), deleted(false) {}

    string getKey() const { return key; }
    any getValue() const { return value; }
    bool isOccupied() const { return occupied; }
    bool isDeleted() const { return deleted; }

    void setValue(any v) { value = v; }
    void setOccupied(bool occ) { occupied = occ; }
    void setDeleted(bool del) { deleted = del; }
    void setKey(string k) { key = k; }

    string valueToString() const {
        if (!occupied) return "[empty]";
        if (deleted) return "[deleted]";
        
        try {
            if (value.type() == typeid(int))
                return to_string(any_cast<int>(value));
            else if (value.type() == typeid(double))
                return to_string(any_cast<double>(value));
            else if (value.type() == typeid(string))
                return any_cast<string>(value);
            else if (value.type() == typeid(const char*))
                return string(any_cast<const char*>(value));
            else
                return "[object]";
        } catch (const bad_any_cast&) {
            return "[error]";
        }
    }

    string toString() const {
        if (!occupied) return "[empty]";
        if (deleted) return "[deleted]";
        return "(" + key + ": " + valueToString() + ")";
    }
};

// =======================================================
// Clase HashTable
// =======================================================
class HashTable {
private:
    vector<HashEntry> table;
    int capacity;
    int size;           // número de elementos actualmente en la tabla
    int numDeleted;     // número de elementos marcados como eliminados

    // Función hash: Division + Folding
    int hashFunction(const string& key) const {
        // Folding: dividir la clave en partes y sumarlas
        int sum = 0;
        int foldSize = 4; // tamaño de cada "fold" (grupo de caracteres)
        
        for (size_t i = 0; i < key.length(); i += foldSize) {
            string fold = key.substr(i, foldSize);
            int foldValue = 0;
            
            // Convertir cada carácter a su valor ASCII y combinarlo
            for (char c : fold) {
                foldValue = foldValue * 256 + static_cast<int>(c);
            }
            sum += foldValue;
        }
        
        // Division: aplicar módulo con el tamaño de la tabla
        return abs(sum) % capacity;
    }

    // Linear Probing: buscar la siguiente posición disponible
    int findSlot(const string& key, bool forInsertion = true) const {
        int index = hashFunction(key);
        int originalIndex = index;
        int firstDeletedIndex = -1;
        
        do {
            // Si encontramos la clave exacta
            if (table[index].isOccupied() && !table[index].isDeleted() 
                && table[index].getKey() == key) {
                return index;
            }
            
            // Para inserción: guardar el primer slot eliminado encontrado
            if (forInsertion && firstDeletedIndex == -1 
                && table[index].isDeleted()) {
                firstDeletedIndex = index;
            }
            
            // Si encontramos un slot vacío (nunca ocupado)
            if (!table[index].isOccupied()) {
                // Para inserción, preferir reutilizar un slot eliminado
                if (forInsertion && firstDeletedIndex != -1) {
                    return firstDeletedIndex;
                }
                return index;
            }
            
            // Linear probing: avanzar a la siguiente posición
            index = (index + 1) % capacity;
            
        } while (index != originalIndex);
        
        // Si recorrimos toda la tabla
        if (forInsertion && firstDeletedIndex != -1) {
            return firstDeletedIndex;
        }
        
        return -1; // Tabla llena o clave no encontrada
    }

    // Verificar si necesitamos redimensionar
    bool needsResize() const {
        double loadFactor = static_cast<double>(size + numDeleted) / capacity;
        return loadFactor > 0.7; // Factor de carga del 70%
    }

    // Redimensionar la tabla
    void resize() {
        int oldCapacity = capacity;
        vector<HashEntry> oldTable = table;
        
        // Duplicar la capacidad
        capacity = capacity * 2;
        table.clear();
        table.resize(capacity);
        size = 0;
        numDeleted = 0;
        
        // Reinsertar todos los elementos no eliminados
        for (int i = 0; i < oldCapacity; i++) {
            if (oldTable[i].isOccupied() && !oldTable[i].isDeleted()) {
                insert(oldTable[i].getKey(), oldTable[i].getValue());
            }
        }
    }

public:
    // Constructor
    HashTable(int initialCapacity = 11) 
        : capacity(initialCapacity), size(0), numDeleted(0) {
        table.resize(capacity);
    }

    // Insertar o actualizar un par clave-valor
    bool insert(const string& key, any value) {
        if (needsResize()) {
            resize();
        }
        
        int index = findSlot(key, true);
        
        if (index == -1) {
            cerr << "Error: HashTable está llena" << endl;
            return false;
        }
        
        // Si la clave ya existe, actualizar el valor
        if (table[index].isOccupied() && !table[index].isDeleted() 
            && table[index].getKey() == key) {
            table[index].setValue(value);
            return true;
        }
        
        // Insertar nuevo elemento
        if (table[index].isDeleted()) {
            numDeleted--;
        }
        
        table[index] = HashEntry(key, value);
        size++;
        return true;
    }

    // Buscar un valor por clave
    any search(const string& key) const {
        int index = findSlot(key, false);
        
        if (index != -1 && table[index].isOccupied() 
            && !table[index].isDeleted() 
            && table[index].getKey() == key) {
            return table[index].getValue();
        }
        
        return any(); // Retornar any vacío si no se encuentra
    }

    // Verificar si una clave existe
    bool contains(const string& key) const {
        int index = findSlot(key, false);
        return (index != -1 && table[index].isOccupied() 
                && !table[index].isDeleted() 
                && table[index].getKey() == key);
    }

    // Eliminar un elemento por clave (eliminación lógica)
    bool remove(const string& key) {
        int index = findSlot(key, false);
        
        if (index != -1 && table[index].isOccupied() 
            && !table[index].isDeleted() 
            && table[index].getKey() == key) {
            table[index].setDeleted(true);
            size--;
            numDeleted++;
            return true;
        }
        
        return false;
    }

    // Obtener el tamaño actual (elementos activos)
    int getSize() const {
        return size;
    }

    // Obtener la capacidad de la tabla
    int getCapacity() const {
        return capacity;
    }

    // Obtener el factor de carga
    double getLoadFactor() const {
        return static_cast<double>(size) / capacity;
    }

    // Obtener todas las claves
    List getKeys() const {
        List keys;
        for (int i = 0; i < capacity; i++) {
            if (table[i].isOccupied() && !table[i].isDeleted()) {
                keys.push(table[i].getKey());
            }
        }
        return keys;
    }

    // Limpiar la tabla
    void clear() {
        table.clear();
        table.resize(capacity);
        size = 0;
        numDeleted = 0;
    }

    // Mostrar la tabla completa (para debugging)
    void display() const {
        cout << "=== HashTable ===" << endl;
        cout << "Capacity: " << capacity << endl;
        cout << "Size: " << size << endl;
        cout << "Load Factor: " << getLoadFactor() << endl;
        cout << "Deleted: " << numDeleted << endl;
        cout << "\nTable contents:" << endl;
        
        for (int i = 0; i < capacity; i++) {
            cout << "[" << i << "] ";
            if (table[i].isOccupied()) {
                cout << table[i].toString();
            } else {
                cout << "[empty]";
            }
            cout << endl;
        }
        cout << "=================" << endl;
    }

    // Mostrar solo los elementos activos
    void displayActive() const {
        cout << "=== Active Elements ===" << endl;
        cout << "Size: " << size << endl;
        
        for (int i = 0; i < capacity; i++) {
            if (table[i].isOccupied() && !table[i].isDeleted()) {
                cout << "[" << i << "] " << table[i].toString() << endl;
            }
        }
        cout << "======================" << endl;
    }

    // Convertir a string
    string toString() const {
        ostringstream oss;
        oss << "HashTable(size=" << size << ", capacity=" << capacity << ")";
        return oss.str();
    }

    // Obtener estadísticas de colisiones
    void displayStatistics() const {
        int emptySlots = 0;
        int occupiedSlots = 0;
        int deletedSlots = 0;
        
        for (int i = 0; i < capacity; i++) {
            if (!table[i].isOccupied()) {
                emptySlots++;
            } else if (table[i].isDeleted()) {
                deletedSlots++;
            } else {
                occupiedSlots++;
            }
        }
        
        cout << "=== HashTable Statistics ===" << endl;
        cout << "Capacidad total: " << capacity << endl;
        cout << "Espacios ocupados: " << occupiedSlots << endl;
        cout << "Espacios eliminados: " << deletedSlots << endl;
        cout << "Espacios vacios: " << emptySlots << endl;
        cout << "Factor de carga: " << getLoadFactor() * 100 << "%" << endl;
        cout << "===========================" << endl;
    }
};

#endif // HASHTABLE_H
