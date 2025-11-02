#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Función Hash: Folding + División 
struct FoldingDivisionHash {
    size_t operator()(const string& key) const {
        size_t sum = 0;
        for (char c : key) {
            sum += static_cast<size_t>(c);
        }
        return sum % 6257;  // número primo elegido
    }
};

// Nodo de la tabla hash
template<typename K, typename V>
struct HashNode {
    K key;
    V value;
    bool occupied;
    bool deleted;
    
    HashNode() : occupied(false), deleted(false) {}
    HashNode(const K& k, const V& v) 
        : key(k), value(v), occupied(true), deleted(false) {}
};

// Tabla hash con sondeo lineal (linear probing)
template<typename K, typename V, typename HashFunc = FoldingDivisionHash>
class HashTable {
private:
    vector<HashNode<K, V>> table;
    size_t count;
    size_t capacity;
    HashFunc hashFunc;
    
    // Sondeo lineal
    size_t probe(size_t hash, size_t i) const {
        return (hash + i) % capacity;
    }

public:
    HashTable(size_t cap = 6257) : count(0), capacity(cap) {
        table.resize(capacity);
    }
    
    // Insertar o actualizar
    void insert(const K& key, const V& value) {
        size_t hash = hashFunc(key);
        
        for (size_t i = 0; i < capacity; i++) {
            size_t index = probe(hash, i);
            
            // Espacio vacío o borrado
            if (!table[index].occupied || table[index].deleted) {
                table[index] = HashNode<K, V>(key, value);
                count++;
                return;
            }
            
            // Actualizar clave existente
            if (table[index].key == key) {
                table[index].value = value;
                return;
            }
        }
    }
    
    // Buscar por clave
    V* find(const K& key) {
        size_t hash = hashFunc(key);
        
        for (size_t i = 0; i < capacity; i++) {
            size_t index = probe(hash, i);
            
            if (!table[index].occupied) {
                return nullptr;
            }
            
            if (table[index].key == key && !table[index].deleted) {
                return &table[index].value;
            }
        }
        
        return nullptr;
    }
    
    // Operador [] para acceso
    V& operator[](const K& key) {
        V* found = find(key);
        if (found) {
            return *found;
        }
        insert(key, V());
        return *find(key);
    }
    
    // Verificar si existe la clave
    bool contains(const K& key) const {
        size_t hash = hashFunc(key);
        
        for (size_t i = 0; i < capacity; i++) {
            size_t index = probe(hash, i);
            
            if (!table[index].occupied) {
                return false;
            }
            
            if (table[index].key == key && !table[index].deleted) {
                return true;
            }
        }
        
        return false;
    }
    
    // Eliminar clave
    bool remove(const K& key) {
        size_t hash = hashFunc(key);
        
        for (size_t i = 0; i < capacity; i++) {
            size_t index = probe(hash, i);
            
            if (!table[index].occupied) {
                return false;
            }
            
            if (table[index].key == key && !table[index].deleted) {
                table[index].deleted = true;
                count--;
                return true;
            }
        }
        
        return false;
    }
    
    // Obtener todos los pares clave-valor
    vector<pair<K, V>> getAll() const {
        vector<pair<K, V>> result;
        for (const auto& node : table) {
            if (node.occupied && !node.deleted) {
                result.push_back({node.key, node.value});
            }
        }
        return result;
    }
    
    // Estadísticas
    size_t getSize() const { return count; }
    size_t getCapacity() const { return capacity; }
    double getLoadFactor() const { 
        return static_cast<double>(count) / capacity; 
    }
};

#endif
