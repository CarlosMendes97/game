#include <stdio.h>
#include <time.h>
#include "territory.h"
#include "combat.h"
#include "mission.h"

// Função auxiliar para liberar a memória de todos os territórios
void cleanupGame(Territory** list, int count) {
    printf("\n--- Limpeza de Memória ---\n");
    for (int i = 0; i < count; i++) {
        printf("Liberando %s...\n", list[i]->name);
        freeTerritory(list[i]);
    }
    // Libera o array de ponteiros em si (se alocado dinamicamente)
    // Neste caso, ele foi alocado estaticamente (stack), então só liberamos as structs.
}


int main() {
    srand(time(NULL)); 
    
    // Alocação dinâmica de 5 territórios
    Territory* t_list[5]; 
    int totalTerritories = 5;

    t_list[0] = createTerritory("Norte", 5, 1);
    t_list[1] = createTerritory("Sul", 2, 2);
    t_list[2] = createTerritory("Leste", 3, 1);
    t_list[3] = createTerritory("Oeste", 1, 2);
    t_list[4] = createTerritory("Central", 4, 1);

    // Conexões (Estrutura Não-Linear: Grafo)
    addNeighbor(t_list[0], t_list[1]); // Norte <-> Sul
    addNeighbor(t_list[0], t_list[2]); // Norte <-> Leste
    addNeighbor(t_list[1], t_list[3]); // Sul <-> Oeste
    addNeighbor(t_list[4], t_list[2]); // Central <-> Leste

    printf("--- Inicialização do Jogo e Demonstração ---\n");
    printf("Território 1: %s (Dono: %d, Exércitos: %d)\n", t_list[0]->name, t_list[0]->ownerId, t_list[0]->armies);
    printf("Vizinhos do Norte: %s e %s\n", t_list[0]->neighbors[0]->name, t_list[0]->neighbors[1]->name);

    // Demonstração de Passagem por Referência
    updateTerritoryArmies(t_list[0], 6);

    // Demonstração da Lógica de Combate e Ponteiros para Funções
    // Jogador 1 (Norte) ataca Jogador 2 (Sul)
    Territory* attacker = t_list[0]; 
    Territory* defender = t_list[1]; 
    
    initiateAttack(attacker, defender, standardDiceRollCombat);
    
    // Demonstração de Missões e Verificação de Vitória
    // Cria a missão usando o ponteiro para a função checkConquerNTerritories
    Mission* p1_mission = createMission("Conquistar 4 territórios.", 4, checkConquerNTerritories);
    
    printf("\n--- Verificação de Condição de Vitória (TAD, Encapsulamento) ---\n");
    printf("Missão do Jogador 1: %s\n", p1_mission->description);
    
    // Passa o array de ponteiros (por referência) para a função de verificação
    if (checkPlayerVictory(p1_mission, t_list, totalTerritories, 1)) {
        printf(">>> Jogador 1 Venceu o Jogo por Missão!\n");
    } else {
        printf(">>> Jogador 1 ainda não cumpriu a missão.\n");
    }
    
    // Liberação da memória
    free(p1_mission);
    cleanupGame(t_list, totalTerritories); 

    return 0;
}