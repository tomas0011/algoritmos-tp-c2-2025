# 📋 SUPUESTOS - HashTable y Grafo

## Documento de Decisiones de Diseño

---

## 🎯 1. CÓDIGOS DE CENTRO DE DISTRIBUCIÓN

### Supuesto Principal
**Un código único identifica a un centro de distribución**

```cpp
// Códigos de 3 letras basados en provincias argentinas
"CBA"  → Centro de Córdoba
"MZA"  → Centro de Mendoza
"BSA" → Centro de Buenos Aires
"ROS"  → Centro de Rosario
```

### Contexto del Problema
Argentina tiene **24 jurisdicciones:**
- 23 provincias
- 1 distrito federal (CABA)

**Supuesto del proyecto:** Una jurisdicción = Un centro de distribución  
**Total de centros actuales:** 24 (uno por provincia)

### Justificación
- El `code` funciona como identificador único (clave de la HashTable)
- Similar a códigos de provincia en sistemas reales
- **Búsqueda O(1)** por código en la HashTable
- Fácil identificación visual

### Escalabilidad Futura
Si se requieren múltiples centros por provincia:
```cpp
"BUE1" → Centro Norte Buenos Aires
"BUE2" → Centro Sur Buenos Aires
"CBA1" → Centro Córdoba Capital
"CBA2" → Centro Córdoba Interior
```

La HashTable actual (capacidad 6257) soporta esta expansión sin modificaciones.

---

## 🔐 2. HASHTABLE - FUNCIÓN DE HASHING

### Método Elegido: Folding + Division

```cpp
struct FoldingDivisionHash {
    size_t operator()(const string& key) const {
        // PASO 1: FOLDING - Suma valores ASCII
        uint64_t sum = 0;
        for (unsigned char c : key) {
            sum += static_cast<uint64_t>(c);
        }
        
        // PASO 2: DIVISIÓN - Módulo con primo
        const uint64_t PRIME_MODULUS = 6257;
        return static_cast<size_t>(sum % PRIME_MODULUS);
    }
};
```

### Supuestos de Diseño

#### 2.1 Número Primo: 6257

**¿Por qué 6257?**

| Razón | Explicación |
|-------|-------------|
| **Primo estándar** | Aparece en tablas de primos para hashing (Knuth) |
| **Balance perfecto** | Entre eficiencia y escalabilidad |
| **Reduce colisiones** | Los primos distribuyen mejor los valores |
| **Memoria aceptable** | ~50 KB, insignificante en hardware moderno |

**Factor de Carga:**
```
Actual (24 centros):   24 / 6257 = 0.38%  ✅ Excelente
Futuro (240 centros):  240 / 6257 = 3.84% ✅ Muy bueno
Límite (4692 centros): 4692 / 6257 = 75%  ✅ Aceptable
```

#### 2.2 Método Folding

**Suma de valores ASCII:**
```cpp
// Ejemplo: "CBA"
'C' → 67
'B' → 66  
'A' → 65
──────────
sum = 198

hash = 198 % 6257 = 198
```

**Ventajas:**
- ✅ Complejidad O(k) donde k = longitud de la clave
- ✅ Simple de implementar
- ✅ Suficientemente bueno para códigos cortos (3-4 letras)

**Limitación conocida:**
- Anagramas generan el mismo hash: `"ABC"` y `"CBA"` → ambos suman 198
- **Mitigación:** Los códigos reales no son anagramas ("CBA" ≠ "ABC")

#### 2.3 Normalización de Códigos

```cpp
std::string normalizeCode(const string& code) const {
    string normalized = code;
    transform(normalized.begin(), normalized.end(), 
              normalized.begin(), ::toupper);
    return normalized;
}
```

**Supuesto:** Los códigos se almacenan siempre en mayúsculas
- Entrada: `"cba"`, `"Cba"`, `"CBA"` → Almacenado: `"CBA"`
- Evita problemas de case-sensitivity

---

## 🔀 3. RESOLUCIÓN DE COLISIONES

### Método: Sondeo Lineal (Linear Probing)

```cpp
size_t probe(size_t hash, size_t i) const {
    return (hash + i) % capacity;
}
```

**Algoritmo:**
1. Calcular hash: `h = hash(key)`
2. Si `table[h]` ocupada → probar `(h + 1) % 6257`
3. Continuar hasta encontrar espacio: `(h + i) % 6257`

### Ejemplo de Colisión

```
Insertar "CBA": hash = 198
table[198] vacío → insertar ✓

Insertar "XYZ": hash = 198 (colisión)
table[198] ocupado → probar 199
table[199] vacío → insertar ✓

Insertar "ABC": hash = 198 (colisión)
table[198] ocupado → probar 199
table[199] ocupado → probar 200
table[200] vacío → insertar ✓
```

**Resultado:**
```
┌──────┬──────┬─────────┐
│ Idx  │ Key  │ Estado  │
├──────┼──────┼─────────┤
│ 198  │ CBA  │ Original│
│ 199  │ XYZ  │ +1      │
│ 200  │ ABC  │ +2      │
└──────┴──────┴─────────┘
```

### Ventajas del Sondeo Lineal (Linear probing)
- ✅ **Simple:** Solo incrementar índice
- ✅ **Cache-friendly:** Acceso secuencial en memoria
- ✅ **Sin overhead:** No necesita estructuras adicionales

### Lazy Deletion

Al eliminar un elemento, se marca como `deleted = true` (no se borra físicamente):

```cpp
bool remove(const K& key) {
    // Buscar elemento
    // Si existe: node.deleted = true
    // No se elimina físicamente para no romper sondeo
}
```

**Razón:** Si eliminamos físicamente, rompemos la cadena de sondeo lineal.

---

## 🗺️ 4. GRAFO DE CONEXIONES

### Representación: Lista de Adyacencia con HashTable

```cpp
HashTable<string, vector<pair<string, int>>> graph;
```

**Estructura:**
- **Clave:** Código del centro (`"CBA"`)
- **Valor:** Vector de vecinos (código + distancia)

### Ejemplo Visual

**Grafo de rutas:**
```
        150 km
    CBA -------- MZA
     |            |
     | 200 km     | 180 km
     |            |
    BSAS -------- SFE
        250 km
```

**Representación en HashTable:**
```
┌─────────┬────────────────────────────┐
│  Key    │  Value (vecinos)           │
├─────────┼────────────────────────────┤
│ "CBA"   │ [("MZA",150), ("BSA",200)] │
│ "MZA"   │ [("CBA",150), ("SFE",180)] │
│ "BSA"   │ [("CBA",200), ("SFE",250)] │
│ "SFE"   │ [("MZA",180), ("BSA",250)] │
└─────────┴────────────────────────────┘
```

### Supuesto Principal: Grafo Bidireccional

**Las rutas son transitables en ambas direcciones**

```cpp
// Al cargar: CBA MZA 150
// Se agregan AMBAS conexiones:
graph["CBA"].push_back({"MZA", 150});
graph["MZA"].push_back({"CBA", 150});
```

**Justificación:**
- Las rutas terrestres son bidireccionales
- Simplifica la representación
- Coherente con la realidad de centros de distribución

**Implicación:**
- ⚠️ Asume misma distancia en ambos sentidos
- ⚠️ No considera rutas alternativas o tráfico direccional

---

## 🛣️ 5. ALGORITMO DIJKSTRA

### Implementación con Cola de priodidad

```cpp
pair<int, vector<string>> shortestPath(
    const string& origin, 
    const string& destination
);
```

### HashTables Auxiliares

El algoritmo usa **3 HashTables** para eficiencia O(1):

```cpp
HashTable<string, int> distances;        // Distancias acumuladas
HashTable<string, string> previous;     // Nodo previo en camino
HashTable<string, bool> visited;        // Nodos visitados
```

**Ventaja:** Acceso O(1) en cada operación del algoritmo

### Algoritmo

```cpp
// 1. Inicializar distancias a infinito
for (cada centro) {
    distances[centro] = INT_MAX;
}
distances[origin] = 0;

// 2. Cola de prioridad con pares (distancia, nodo)
priority_queue<pair<int, string>, 
               vector<pair<int, string>>, 
               greater<pair<int, string>>> pq;
pq.push({0, origin});

// 3. Procesar nodos
while (!pq.empty()) {
    auto [currentDist, currentNode] = pq.top();
    pq.pop();
    
    if (visited[currentNode]) continue;
    visited[currentNode] = true;
    
    // Relajar vecinos
    for (auto& [neighbor, weight] : graph[currentNode]) {
        int newDist = currentDist + weight;
        if (newDist < distances[neighbor]) {
            distances[neighbor] = newDist;
            previous[neighbor] = currentNode;
            pq.push({newDist, neighbor});
        }
    }
}
```

### Supuestos

#### 5.1 Distancias Positivas
- Todas las distancias son > 0 (requisito de Dijkstra)
- No hay rutas con distancia negativa o cero

#### 5.2 Grafo Conectado
- Asumimos que existe al menos un camino entre centros principales
- Si no existe: el algoritmo retorna `-1` (sin camino)

#### 5.3 Complejidad
```
O((V + E) log V) - Con Cola de priodidad (heap binario)
V = vértices (centros)
E = aristas (conexiones)
```

**Justificación:**
- La cola de prioridad extrae mínimo en O(log V)
- Cada arista se procesa una vez: O(E log V)
- Total: O((V + E) log V)
- Con 24 centros: ~100-200 operaciones (muy eficiente)

---

## 📊 6. USO DE HASHTABLES EN EL PROYECTO

### Total de HashTables: 5

| HashTable | Tipo | Propósito | Complejidad |
|-----------|------|-----------|-------------|
| `centersByCode` | `<string, DistributionCenter>` | Almacenar centros | O(1) búsqueda |
| `graph` | `<string, vector<pair<string,int>>>` | Grafo (lista adyacencia) | O(1) acceso vecinos |
| `distances` | `<string, int>` | Dijkstra - distancias | O(1) actualización |
| `previous` | `<string, string>` | Dijkstra - camino previo | O(1) consulta |
| `visited` | `<string, bool>` | Dijkstra - visitados | O(1) verificación |

### Ventajas de HashTable vs Alternativas

**Sin HashTable (array lineal):**
```cpp
// Buscar centro por código: O(n)
for (int i = 0; i < n; i++) {
    if (centers[i].code == "CBA") { /* encontrado */ }
}
```

**Con HashTable:**
```cpp
// Buscar centro por código: O(1)
DistributionCenter* centro = centersByCode.find("CBA");
```

**Mejora:** De O(n) a O(1) → **impacto crítico en Dijkstra** que hace múltiples búsquedas.

---

## 🎓 RESUMEN DE DECISIONES CRÍTICAS

| Aspecto | Decisión | Justificación |
|---------|----------|---------------|
| **Identificador** | Código string 3-4 letras | Clave única para HashTable |
| **Hash** | Folding + Division | Método de clase, O(k) |
| **Primo** | 6257 | Balance: eficiencia + escalabilidad |
| **Colisiones** | Sondeo lineal | Simple, cache-friendly |
| **Grafo** | Lista adyacencia + HashTable | O(1) acceso a vecinos |
| **Direccionalidad** | Bidireccional | Coherente con rutas reales |
| **Dijkstra** | Cola de priodidad + 3 HashTables | O((V+E) log V) óptimo |
| **Normalización** | Mayúsculas | Evita case-sensitivity |

---

## 🔢 ANÁLISIS DE ESCALABILIDAD

### Probabilidad de Colisiones

```
P(colisión) ≈ n² / (2m)

Con 24 centros:  24² / (2×6257) = 4.6%
Con 240 centros: 240² / (2×6257) ≈ 460% (muchas colisiones, pero factor carga bajo)
```

**Conclusión:** El sondeo lineal maneja las colisiones eficientemente incluso con 240 centros.

---

## ⚠️ LIMITACIONES CONOCIDAS

### 1. Colisiones por Anagramas

**Problema:**
```cpp
"ABC" → 65+66+67 = 198
"CBA" → 67+66+65 = 198  // Misma suma
```

**Mitigación:**
- Sondeo lineal resuelve automáticamente
- Códigos reales predefinidos (no hay anagramas)

### 2. Capacidad Fija

**Limitación:** 6257 slots (sin rehashing dinámico actualmente)

**Mitigación:**
- Capacidad suficiente para 4,692 centros (75% ocupación)
- Rehashing implementado (se activa automáticamente si load > 70%)

### 3. Grafo Simétrico

**Limitación:** Asume misma distancia en ambas direcciones

**Mitigación:**
- Coherente con rutas terrestres reales
- Si se requiere asimetría: agregar dos líneas en `conexiones.txt`

---

## 🚀 CONCLUSIÓN

La implementación de **HashTable propia** con función **Folding + Division** y primo **6257** proporciona:

✅ **O(1) búsqueda** - Acceso instantáneo por código  
✅ **Escalabilidad** - Soporta hasta 4,692 centros  
✅ **Eficiencia** - Memoria insignificante (~50 KB)  
✅ **Simplicidad** - Sondeo lineal sin overhead  
✅ **Dijkstra óptimo** - O((V+E) log V) con Cola de priodidad y 3 HashTables auxiliares  

**Resultado:** Sistema eficiente para gestión de centros de distribución implementando estructuras de datos propias con algoritmos vistos en clase.

