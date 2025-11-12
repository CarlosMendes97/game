#include "combat.h"
#include <time.h>
#include <stdlib.h>

// Lógica de Combate
int standardDiceRollCombat(Territory* attacker, Territory* defender) {
    // srand(time(NULL)) deve ser chamado em main.c
    int attackerRoll = (rand() % 6) + 1;
    int defenderRoll = (rand() % 6) + 1;
    
    if (attackerRoll > defenderRoll) {
        if (defender->armies > 0) {
            defender->armies--;
            printf("  -> Vitória do Atacante! %s perde 1 exército.\n", defender->name);
            return 1;
        }
    } else {
        if (attacker->armies > 1) { 
            attacker->armies--;
            printf("  -> Vitória do Defensor! %s perde 1 exército.\n", attacker->name);
        }
    }
    return 0;
}

void initiateAttack(Territory* attacker, Territory* defender, CombatStrategy strategy) {
    if (attacker->ownerId == defender->ownerId) {
        printf("Ataque Inválido: Territórios pertencem ao mesmo jogador.\n");
        return;
    }
    
    printf("\n--- ATAQUE INICIADO: %s vs %s ---\n", attacker->name, defender->name);

    while (attacker->armies > 1 && defender->armies > 0) {
        strategy(attacker, defender); 
        
        if (defender->armies == 0) {
            printf(">>> VITÓRIA! %s conquistou %s!\n", attacker->name, defender->name);
            defender->ownerId = attacker->ownerId;
            // O atacante deve mover um exército para o novo território
            defender->armies = 1; 
            attacker->armies--;
            break;
        }
        if (attacker->armies == 1) {
             printf(">>> Ataque encerrado. Exércitos insuficientes.\n");
             break;
        }
    }
}