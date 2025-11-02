# HashTable Implementation

## 📚 What is a HashTable?

A **hash table** stores **key-value** pairs with **O(1)** access.

```
Search without HashTable:  "CBA" → O(n) - loop through array
Search with HashTable:     "CBA" → O(1) - direct access
```

---

## 🧮 Hash Function: Folding + Division

### Implementation

```cpp
struct FoldingDivisionHash {
    size_t operator()(const string& key) const {
        size_t sum = 0;
        for (char c : key) {
            sum += static_cast<size_t>(c);
        }
        return sum % 6257;  // prime number
    }
};
```

### Example: Hash "CBA"

```
Step 1 - Folding:
'C' → 67
'B' → 66  
'A' → 65
────────
sum = 198

Step 2 - Division:
hash = 198 % 6257 = 198

Result: "CBA" stored at index 198
```

**Why 6257?**
- **Prime number** → better distribution
- 24 centers / 6257 = **0.38% load** (excellent)
- Scales up to 4692 centers (75% load)

---

## 🔀 Collision Resolution: Linear Probing

### What is a collision?

Two different keys produce the **same index**.

### Solution: Linear Probing

If position `h` is occupied, try next positions:
```
h, h+1, h+2, h+3, ..., (h+i) % capacity
```

### Visual Example

**Insert centers:**

```
1. insert("CBA", Center_Cordoba)
   hash("CBA") = 198
   table[198] empty → insert ✓

Array:
┌─────┬──────┬──────────────────┐
│ idx │ key  │ value            │
├─────┼──────┼──────────────────┤
│ 197 │ -    │ -                │
│ 198 │ CBA  │ Center_Cordoba   │ ← original hash
│ 199 │ -    │ -                │
│ 200 │ -    │ -                │
└─────┴──────┴──────────────────┘
```

```
2. insert("MZA", Center_Mendoza)
   hash("MZA") = 523
   table[523] empty → insert ✓

Array (index 523):
┌─────┬──────┬──────────────────┐
│ 522 │ -    │ -                │
│ 523 │ MZA  │ Center_Mendoza   │ ← original hash
│ 524 │ -    │ -                │
└─────┴──────┴──────────────────┘
```

```
3. insert("XYZ", Center_X) 
   hash("XYZ") = 198  ← COLLISION with "CBA"!
   table[198] occupied → try next
   table[199] empty → insert ✓

Array:
┌─────┬──────┬──────────────────┐
│ 197 │ -    │ -                │
│ 198 │ CBA  │ Center_Cordoba   │ ← occupied
│ 199 │ XYZ  │ Center_X         │ ← probing +1
│ 200 │ -    │ -                │
└─────┴──────┴──────────────────┘
```

```
4. insert("ABC", Center_A)
   hash("ABC") = 198  ← COLLISION
   table[198] occupied → try 199
   table[199] occupied → try 200
   table[200] empty → insert ✓

Final array:
┌─────┬──────┬──────────────────┐
│ 197 │ -    │ -                │
│ 198 │ CBA  │ Center_Cordoba   │ ← original position
│ 199 │ XYZ  │ Center_X         │ ← collision, probe +1
│ 200 │ ABC  │ Center_A         │ ← collision, probe +2
│ 201 │ -    │ -                │
└─────┴──────┴──────────────────┘
```

---

## ⚡ Time Complexity

| Operation | Average | Worst Case* |
|-----------|---------|-------------|
| `insert(key, value)` | O(1) | O(n) |
| `find(key)` | O(1) | O(n) |
| `remove(key)` | O(1) | O(n) |
| `contains(key)` | O(1) | O(n) |

*Worst case: all keys collide

### Space

```
Memory = capacity × sizeof(HashNode)
       = 6257 × (sizeof(key) + sizeof(value) + 2 bytes)
       ≈ 50 KB
```

---

## 🎯 Usage in Project

### 1. Store Centers by Code

```cpp
HashTable<string, DistributionCenter> centersByCode;

// Insert
centersByCode.insert("CBA", center);

// Find O(1)
DistributionCenter* center = centersByCode.find("CBA");

// Check existence O(1)
if (centersByCode.contains("CBA")) { /* ... */ }
```

### 2. Graph Connections (Adjacency List)

```cpp
HashTable<string, vector<pair<string, int>>> graph;
```

**Representation:**
```
Graph:
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

**Advantage:** Find neighbors in **O(1)**

```cpp
// Find neighbors of "CBA"
auto* neighbors = graph.find("CBA");  // O(1) ✓
// neighbors = [("MZA", 150), ("BSAS", 200)]
```

### 3. Dijkstra with HashTable

```cpp
// Auxiliary structures O(1)
HashTable<string, int> distances;
HashTable<string, string> previous;
HashTable<string, bool> visited;

// Direct access O(1)
distances["CBA"] = 0;
visited["MZA"] = true;
```

---

## 📊 Advantages vs Disadvantages

### ✅ Advantages

- **O(1) search** - Instant access by key
- **Direct codes** - Use `"CBA"` without numeric indices
- **Own implementation** - Course requirement
- **Class methods** - Folding + Division + Linear Probing

### ❌ Limitations

- **Fixed capacity** - 6257 (enough for project)
- **Lazy deletion** - Marks deleted, doesn't remove physically

---

## 🚀 Summary

**How it works:**
1. **Key** (`"CBA"`) → **Hash Function** (Folding+Division) → **Index** (198)
2. If **collision** → Linear probing (198, 199, 200...)
3. **O(1) operations** → `insert`, `find`, `contains`, `remove`

**Usage in project:**
- HashTable 1: Centers by code
- HashTable 2: Graph (adjacency list)
- HashTables 3-5: Dijkstra auxiliary

**Result:** Instant search and access for distribution center management.
