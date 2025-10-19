# Jerry-s-Daycare-Management-System

A robust C project demonstrating **generic data-structure engineering** (Linked List, Hash Table, MultiValue Hash Table) applied to a real use case: managing *Jerry* entities, their identifiers, planets, and physical attributes. The project emphasizes **clean architecture, memory safety, and clear separation of concerns**, and includes a CLI program that loads data from a configuration file and provides an interactive menu for managing the system.

---

## Table of Contents

1. [Overview](#overview)  
2. [Key Highlights](#key-highlights)  
3. [Architecture](#architecture)  
4. [Data Structures](#data-structures)  
   - [Linked List (Doubly-Linked)](#linked-list-doubly-linked)  
   - [KeyValuePair](#keyvaluepair)  
   - [Hash Table (Chaining)](#hash-table-chaining)  
   - [MultiValue Hash Table](#multivalue-hash-table)  
5. [Jerry Domain Model](#jerry-domain-model)  
6. [Memory Management & Error Handling](#memory-management--error-handling)  
7. [Build & Run](#build--run)  
8. [Example Workflow](#example-workflow)  
9. [Project Structure](#project-structure)  
10. [Complexity Notes](#complexity-notes)  
11. [Testing Notes](#testing-notes)  
12. [Notes & Assumptions](#notes--assumptions)  
13. [License](#license)

---

## Overview

This repository contains a modular implementation of **generic containers** in C and a domain application named **Jerry-boree** (CLI) that uses them. The system loads data (planets, Jerrys, and their attributes) from a configuration text file, builds in-memory indexes, and provides menu operations for adding/removing Jerrys and attributes, querying by ID/attribute, and printing system state.

The data-structure layer is intentionally generic and reusable, with user-supplied function pointers for **copy**, **destroy**, **compare**, **print**, and **hash** operations.

---

## Key Highlights

- **Professional-grade generics** in C using function pointers for type-agnostic containers.  
- **Doubly-linked list** chosen to simplify safe deletions in O(1) given a node pointer.  
- **Hash table with chaining**: array of buckets, each bucket is a linked list of `KeyValuePair` elements.  
- **MultiValue hash table**: maps a key to a *linked list* of values, enabling many-to-one relationships (e.g., attribute → multiple Jerrys).  
- **Deliberate memory strategy**: deep vs. shallow copies selected per structure to prevent ownership bugs and leaks.  
- **Clear destruction order** ensuring *no memory leaks* and consistent teardown on errors.  
- **Robust CLI**: interactive menu with graceful handling of invalid input and memory errors (`memoryProblem`) with full cleanup.

---

## Architecture

**Layers**:  
- **Containers Layer** – `LinkedList`, `KeyValuePair`, `HashTable`, `MultiValueHashTable` (generic, reusable).  
- **Domain Layer** – *Jerry* model, *Planet* model, attribute handling.  
- **Application Layer (CLI)** – `JerryBoree` main program: file loading, indexing, and interactive menu.

**High-level data flow**:  
1. Parse configuration file → create planets and Jerrys.  
2. Build indexes:  
   - `list<Jerry*>` – linear traversal & lifecycle control.  
   - `hash<id:string, Jerry*>` – quick lookup by Jerry ID.  
   - `multihash<attribute:string, list<Jerry*>>` – group Jerrys by physical attributes.  
3. Expose menu actions: add/remove Jerrys and attributes, print, search, cleanup.

---

## Data Structures

### Linked List (Doubly-Linked)

- Implemented with an internal `Node` (private to `.c`): `{ data, prev, next }`.  
- **Why doubly-linked?** Simplifies `deleteNode` by adjusting both neighbor pointers in O(1).  
- Deletion handles all cases: empty list, single element, multi-element list.

**Generic behavior via user functions** (when used in domain):  
- **Copy**: shallow copy for `Jerry*` pointers.  
- **Destroy**: destroys a `Jerry` instance when the list owns it.  
- **Compare**: either `Jerry vs Jerry` or `Jerry vs char*` (ID-based equality).  
- **Print**: delegated to the `Jerry` printer.

### KeyValuePair

- Encapsulates a key and a value with user-supplied operations.  
- **Insertion** uses the user **copy** routine to store key/value.  
- **Destruction**: destroys `key`, then `value`, then the pair itself, using the respective user **destroy** functions.  
- Enables flexible ownership: deep/shallow per use case.

### Hash Table (Chaining)

- Array size provided at creation.  
- Each bucket is a **LinkedList** of `KeyValuePair`.  
- On **insert**: compute index using user-provided `hash(key)` (here: based on ASCII of `char*`), then append pair to the bucket list (create bucket list lazily if needed).  
- On **destroy**: iterate buckets; if a list exists, destroy the list; finally free bucket array and table.

### MultiValue Hash Table

- Extends hash table semantics: each key maps to a **LinkedList of values**.  
- On **add**:  
  - If key exists, append value to the existing values list.  
  - If not, create a new values list, insert the value, and store it as the hash value.  
- On **remove (key,value)**:  
  - If key exists, find and remove the specific value from the values list.  
  - If values list becomes empty, remove the key from the table.  
- **Key management**: key is **deep-copied** (e.g., attribute name) to ensure removing a `Jerry` does not accidentally free the key string that may be shared elsewhere.  
- **Destroy**: use a value-destroyer that matches the value's type (here: linked list of `Jerry*`).

---

## Jerry Domain Model

- **LinkedList<Jerry*>** – primary ownership and lifecycle of `Jerry` objects.  
- **HashTable<char*, Jerry*>** – ID → Jerry*, shallow copies for pointers; value free is a no-op (ownership held by the list).  
- **MultiValueHashTable<char*, LinkedList<Jerry*>>** – attribute name → list of Jerrys with that attribute. Deep copy/free for keys.

**Menu operations** include:  
- Add/Delete a single Jerry (updates all three structures).  
- Add/Remove an attribute from a specific Jerry (updates multihash accordingly).  
- Display a Jerry or print collections.  
- Safety checks: validate inputs; on memory issues → emit `memoryProblem` and perform total cleanup.

**File loading**:  
- Build a temporary list of physical attributes encountered while parsing; once the multihash deep-copies each attribute name, the temporary list is freed to avoid leaks.

---

## Memory Management & Error Handling

- **Ownership rules** are explicit:  
  - The *LinkedList* that stores `Jerry*` owns and ultimately frees each `Jerry`.  
  - The *HashTable* stores pointers to `Jerry` with shallow copy; its value-destroyer is a no-op.  
  - The *MultiValueHashTable* deep-copies attribute **keys**; value destroyers align with the stored value type.  
- **Destruction order matters**: multihash → hashtable → linked list of Jerrys (actual `Jerry` free happens here).  
- **Error paths**: if parsing fails or allocation fails, specialized teardown functions clean partially built structures (e.g., planet cleanup on file errors).

---

## Build & Run

### Prerequisites
- Standard C toolchain (`gcc`, `make`).

### Compilation
From the repository root:
```
make
```

This compiles all `.c` sources and links the **JerryBoree** executable.

### Running
```
./JerryBoree <number_of_planets> <configuration_file_path>
```
- `<number_of_planets>` – integer used to initialize the planets list.
- `<configuration_file_path>` – path to a text file describing planets, Jerrys, and attributes.

**Example**
```
./JerryBoree 4 configuration_file.txt
```

### Cleaning
```
make clean
```

---

## Example Workflow

1. Load initial data from the configuration file.  
2. Add a new Jerry (updates list, hash by ID, and multihash by attributes).  
3. Attach or remove attributes from an existing Jerry.  
4. Remove a Jerry: delete from multihash, from ID hash, and finally from the owning linked list.  
5. Exit: global destroy in the correct order to ensure no leaks.

---

## Project Structure

```
/src
  linked_list.c / .h
  key_value_pair.c / .h
  hash_table.c / .h
  multi_hash_table.c / .h
  jerry.c / .h
  planet.c / .h
  main.c            (JerryBoree CLI)
/include            (public headers)
Makefile
README.md
configuration_file.txt (example)
```

> Note: File names may vary depending on your course template; keep public APIs in `include/` and implementations in `src/` for clarity.

---

## Complexity Notes

- Linked List ops: insert/delete/search by value ~ O(n); delete with node pointer ~ O(1).  
- Hash Table: average O(1) insert/lookup with chaining; O(n) worst-case per bucket.  
- MultiValue Hash: same as Hash Table for key ops; per-key value list ops depend on list length.

---

## Testing Notes

- Validate **insertion/deletion** edge cases: empty list, single element, head/tail removal.  
- Verify **hash collisions** by crafting keys with same hash index; ensure chaining works.  
- Check **multihash** remove(key,value) behavior and removal of empty per-key lists.  
- Run with sanitizers/valgrind to verify **no memory leaks** and correct ownership.

---

## Notes & Assumptions

- The hash function for `char*` keys uses ASCII-based calculation per the assignment spec.  
- Keys in **MultiValue Hash** are deep-copied to decouple their lifecycle from `Jerry` entities.  
- The `HashTable` values are pointers owned elsewhere; their destroyers are no-ops.

---

## License

This project is provided for educational purposes. You may choose any OSI-approved license that matches your needs (e.g., MIT). Add a `LICENSE` file if you plan to distribute.
