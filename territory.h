#ifndef TERRITORY_H
#define TERRITORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Territory Territory; // Declaração forward

// Definindo um Território com Adjacência Não-Linear
struct Territory {
    char name[50];
    int armies;
    int ownerId;
    
    // Lista de Adjacência: Array dinâmico de ponteiros para vizinhos
    Territory** neighbors;
    int neighborCount;
};

// Protótipos de Funções
Territory* createTerritory(const char* name, int initialArmies, int initialOwnerId);
void addNeighbor(Territory* t1, Territory* t2);

// Demonstração de Passagem por Referência
void updateTerritoryArmies(Territory* t, int newArmies);

void freeTerritory(Territory* t); // Gerenciamento de Memória

#endif // TERRITORY_H
