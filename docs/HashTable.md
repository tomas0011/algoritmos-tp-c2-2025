# Implementación de HashTable

## 📚 ¿Qué es una HashTable?

Una **tabla hash** almacena pares **clave-valor** con acceso **O(1)**.

```
Búsqueda sin HashTable:  "CBA" → O(n) - recorrer todo el array
Búsqueda con HashTable:  "CBA" → O(1) - acceso directo
```

---

## 🧮 Función de Hashing: Folding + División

### Implementación

```cpp
struct FoldingDivisionHash {
    size_t operator()(const string& key) const {
        size_t sum = 0;
        for (char c : key) {
            sum += static_cast<size_t>(c);
        }
        return sum % 6257;  // número primo
    }
};
```

### Ejemplo: Hash de "CBA"

```
Paso 1 - Folding:
'C' → 67
'B' → 66  
'A' → 65
────────
sum = 198

Paso 2 - División:
hash = 198 % 6257 = 198

Resultado: "CBA" se guarda en índice 198
```

**¿Por qué 6257?**
- **Número primo** → mejor distribución
- 24 centros / 6257 = **0.38% de carga** (excelente)
- Escala hasta 4692 centros (75% de carga)

---

## 🔀 Resolución de Colisiones: Sondeo Lineal

### ¿Qué es una colisión?

Dos claves diferentes producen el **mismo índice**.

### Solución: Linear Probing (Sondeo Lineal)

Si la posición `h` está ocupada, probar las siguientes:
```
h, h+1, h+2, h+3, ..., (h+i) % capacity
```

### Ejemplo Visual

**Insertar centros:**

```
1. insert("CBA", Centro_Cordoba)
   hash("CBA") = 198
   table[198] vacío → insertar ✓

Array:
┌─────┬──────┬──────────────────┐
│ idx │ key  │ value            │
├─────┼──────┼──────────────────┤
│ 197 │ -    │ -                │
│ 198 │ CBA  │ Centro_Cordoba   │ ← hash original
│ 199 │ -    │ -                │
│ 200 │ -    │ -                │
└─────┴──────┴──────────────────┘
```

```
2. insert("MZA", Centro_Mendoza)
   hash("MZA") = 523
   table[523] vacío → insertar ✓

Array (índice 523):
┌─────┬──────┬──────────────────┐
│ 522 │ -    │ -                │
│ 523 │ MZA  │ Centro_Mendoza   │ ← hash original
│ 524 │ -    │ -                │
└─────┴──────┴──────────────────┘
```

```
3. insert("XYZ", Centro_X) 
   hash("XYZ") = 198  ← ¡COLISIÓN con "CBA"!
   table[198] ocupado → probar siguiente
   table[199] vacío → insertar ✓

Array:
┌─────┬──────┬──────────────────┐
│ 197 │ -    │ -                │
│ 198 │ CBA  │ Centro_Cordoba   │ ← ocupado
│ 199 │ XYZ  │ Centro_X         │ ← sondeo +1
│ 200 │ -    │ -                │
└─────┴──────┴──────────────────┘
```

```
4. insert("ABC", Centro_A)
   hash("ABC") = 198  ← COLISIÓN
   table[198] ocupado → probar 199
   table[199] ocupado → probar 200
   table[200] vacío → insertar ✓

Array final:
┌─────┬──────┬──────────────────┐
│ 197 │ -    │ -                │
│ 198 │ CBA  │ Centro_Cordoba   │ ← posición original
│ 199 │ XYZ  │ Centro_X         │ ← colisión, sondeo +1
│ 200 │ ABC  │ Centro_A         │ ← colisión, sondeo +2
│ 201 │ -    │ -                │
└─────┴──────┴──────────────────┘
```

---

## ⚡ Complejidad Temporal

| Operación | Promedio | Peor Caso* |
|-----------|---------|-------------|
| `insert(key, value)` | O(1) | O(n) |
| `find(key)` | O(1) | O(n) |
| `remove(key)` | O(1) | O(n) |
| `contains(key)` | O(1) | O(n) |

*Peor caso: todas las claves colisionan

### Espacio

```
Memoria = capacity × sizeof(HashNode)
        = 6257 × (sizeof(key) + sizeof(value) + 2 bytes)
        ≈ 50 KB
```

---

## 🎯 Uso en el Proyecto

### 1. Almacenar Centros por Código

```cpp
HashTable<string, DistributionCenter> centersByCode;

// Insertar
centersByCode.insert("CBA", center);

// Buscar O(1)
DistributionCenter* center = centersByCode.find("CBA");

// Verificar existencia O(1)
if (centersByCode.contains("CBA")) { /* ... */ }
```

### 2. Grafo de Conexiones (Lista de Adyacencia)

```cpp
HashTable<string, vector<pair<string, int>>> graph;
```

**Representación:**
```
Grafo:
    CBA --150km-- MZA
     |             |
   200km        180km
     |             |
    BSAS --250km-- SFE

HashTable:
┌───────┬───────────────────────────┐
│ "CBA" │ [("MZA",150),("BSAS",200)]│
│ "MZA" │ [("CBA",150),("SFE",180)] │
│"BSAS" │ [("CBA",200),("SFE",250)] │
│ "SFE" │ [("MZA",180),("BSAS",250)]│
└───────┴───────────────────────────┘
```

**Ventaja:** Buscar vecinos de un nodo es **O(1)**

```cpp
// Buscar vecinos de "CBA"
auto* neighbors = graph.find("CBA");  // O(1) ✓
// neighbors = [("MZA", 150), ("BSAS", 200)]
```

### 3. Dijkstra con HashTable

```cpp
// Estructuras auxiliares O(1)
HashTable<string, int> distances;
HashTable<string, string> previous;
HashTable<string, bool> visited;

// Acceso directo O(1)
distances["CBA"] = 0;
visited["MZA"] = true;
```

---

## 📊 Ventajas vs Desventajas

### ✅ Ventajas

- **Búsqueda O(1)** - Acceso instantáneo por clave
- **Códigos directos** - Usar `"CBA"` sin índices numéricos
- **Implementación propia** - Requisito del curso
- **Métodos de clase** - Folding + División + Sondeo Lineal

### ❌ Limitaciones

- **Capacidad fija** - 6257 (suficiente para el proyecto)
- **Lazy deletion** - Marca como borrado, no elimina físicamente

---

## 🚀 Resumen

**Cómo funciona:**
1. **Clave** (`"CBA"`) → **Función Hash** (Folding+División) → **Índice** (198)
2. Si hay **colisión** → Sondeo lineal (198, 199, 200...)
3. **Operaciones O(1)** → `insert`, `find`, `contains`, `remove`

**Uso en el proyecto:**
- HashTable 1: Centros por código
- HashTable 2: Grafo (lista de adyacencia)
- HashTables 3-5: Auxiliares de Dijkstra

**Resultado:** Búsqueda y acceso instantáneo para gestión de centros de distribución.
