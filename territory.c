#include "territory.h"

Territory* createTerritory(const char* name, int initialArmies, int initialOwnerId) {
    Territory* newTerritory = (Territory*)malloc(sizeof(Territory));
    if (newTerritory == NULL) {
        perror("Erro ao alocar memória para o novo território.");
        exit(EXIT_FAILURE);
    }

    strncpy(newTerritory->name, name, 49);
    newTerritory->name[49] = '\0';
    newTerritory->armies = initialArmies;
    newTerritory->ownerId = initialOwnerId;
    
    newTerritory->neighbors = NULL;
    newTerritory->neighborCount = 0;
    
    return newTerritory;
}

void addNeighbor(Territory* t1, Territory* t2) {
    // 1. Adiciona t2 como vizinho de t1
    t1->neighbors = (Territory**)realloc(t1->neighbors, 
                                        (t1->neighborCount + 1) * sizeof(Territory*));
    if (t1->neighbors == NULL) { /* Erro handling */ }
    t1->neighbors[t1->neighborCount] = t2;
    t1->neighborCount++;

    // 2. Adiciona t1 como vizinho de t2
    t2->neighbors = (Territory**)realloc(t2->neighbors, 
                                        (t2->neighborCount + 1) * sizeof(Territory*));
    if (t2->neighbors == NULL) { /* Erro handling */ }
    t2->neighbors[t2->neighborCount] = t1;
    t2->neighborCount++;
}

// **Passagem de Parâmetro por Referência (Ponteiro para a Struct)**
void updateTerritoryArmies(Territory* t, int newArmies) {
    // Modifica o valor original da struct na memória
    t->armies = newArmies; 
    printf("  [REF] Exércitos de %s atualizados para %d\n", t->name, t->armies);
}

void freeTerritory(Territory* t) {
    if (t != NULL) {
        if (t->neighbors != NULL) {
            free(t->neighbors);
        }
        free(t);
    }
}
