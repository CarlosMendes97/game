#ifndef COMBAT_H
#define COMBAT_H

#include "territory.h"

// Ponteiro para Função (Tipo Abstrato)
typedef int (*CombatStrategy)(Territory* attacker, Territory* defender);

// Protótipo da função de ataque principal
void initiateAttack(Territory* attacker, Territory* defender, CombatStrategy strategy);

// Protótipo de uma estratégia específica
int standardDiceRollCombat(Territory* attacker, Territory* defender);

#endif // COMBAT_H
