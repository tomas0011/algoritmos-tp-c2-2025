#include "HashTable.h"
#include <iostream>
#include <DistributionCenter.h>

using namespace std;

int main() {
    cout << "\n=== TEST: HashTable con DistributionCenter ===" << endl;
    
    // Crear tabla hash para centros de distribución
    HashTable<string, DistributionCenter> centerTable;
    
    // Insertar centros
    DistributionCenter cba("CBA", "Córdoba", "Córdoba", 5000, 1200, 50);
    DistributionCenter mza("MZA", "Mendoza", "Mendoza", 4500, 1000, 45);
    DistributionCenter bsas("BSAS", "Buenos Aires", "CABA", 10000, 3000, 120);
    
    centerTable.insert("CBA", cba);
    centerTable.insert("MZA", mza);
    centerTable.insert("BSAS", bsas);
    
    cout << "\n✓ Insertados 3 centros" << endl;
    
    // Buscar centro
    cout << "\n--- Buscar 'CBA' ---" << endl;
    DistributionCenter* found = centerTable.find("CBA");
    if (found) {
        cout << "Encontrado: " << found->getCode() << " - " << found->getName() << endl;
    }
    
    // Verificar existencia
    cout << "\n--- Verificar existencia ---" << endl;
    cout << "¿Existe 'MZA'? " << (centerTable.contains("MZA") ? "Sí" : "No") << endl;
    cout << "¿Existe 'ROS'? " << (centerTable.contains("ROS") ? "Sí" : "No") << endl;
    
    // Listar todos
    cout << "\n--- Listar todos los centros ---" << endl;
    auto all = centerTable.getAll();
    for (const auto& pair : all) {
        cout << "  " << pair.first << ": " << pair.second.getName() << endl;
    }
    
    // Eliminar
    cout << "\n--- Eliminar 'MZA' ---" << endl;
    centerTable.remove("MZA");
    cout << "¿Existe 'MZA'? " << (centerTable.contains("MZA") ? "Sí" : "No") << endl;
    
    cout << "\n=== TEST FINALIZADO ===" << endl;
    return 0;
}
