/* Adaptateur USB pour Amstrad GX4000 (Optimisé et Commenté)
 * Basé sur le travail de Mikael Norrgård (DaemonBite)
 *
 * Ce programme est un logiciel libre sous licence GNU GPL v3.
 */

#include "Gamepad.h"

// ATT: 20 chars max.
const char *gp_serial = "Amstrad GX4000 USB";

// Définition des broches Arduino (basé sur le câblage GX4000)
#define PIN_HAUT    A0
#define PIN_BAS     A1
#define PIN_GAUCHE  A2
#define PIN_DROITE  A3
#define PIN_B1      14 // Bouton 1 (Fire 1)
#define PIN_B2      6  // Bouton 2 (Fire 2)

// Mettre en place le gamepad USB
Gamepad_ Gamepad;


// -- MODIFICATION (OPTIMISATION 1 : Mémoire) --
// Le type 'long' (32 bits) a été remplacé par 'uint8_t' (8 bits),
// ce qui est plus efficace et suffisant pour stocker 6 états.
//
// -- Version optimisée (actuelle) :
uint8_t currentState = 0;
uint8_t lastState = 0;
//
// -- Ancienne version (non optimisée) :
// long currentState = 0;
// long lastState = 0;


void setup()
{
  // Initialise les broches en INPUT_PULLUP.
  // Quand un bouton est pressé, il connecte la broche au GND (Masse),
  // et l'Arduino lit un signal "LOW".
  pinMode(PIN_HAUT,   INPUT_PULLUP);
  pinMode(PIN_BAS,    INPUT_PULLUP);
  pinMode(PIN_GAUCHE, INPUT_PULLUP);
  pinMode(PIN_DROITE, INPUT_PULLUP);
  pinMode(PIN_B1,     INPUT_PULLUP);
  pinMode(PIN_B2,     INPUT_PULLUP);
}

void loop()
{
  // Lit l'état de chaque bouton
  // (digitalRead(...) == LOW) est VRAI si le bouton est pressé.
  bool haut   = (digitalRead(PIN_HAUT)   == LOW);
  bool bas    = (digitalRead(PIN_BAS)    == LOW);
  bool gauche = (digitalRead(PIN_GAUCHE) == LOW);
  bool droite = (digitalRead(PIN_DROITE) == LOW);
  bool b1     = (digitalRead(PIN_B1)     == LOW);
  bool b2     = (digitalRead(PIN_B2)     == LOW);
  
  // Stocke l'état actuel dans un seul nombre pour une comparaison facile
  currentState = haut | (bas << 1) | (gauche << 2) | (droite << 3) | (b1 << 4) | (b2 << 5);

  // N'envoie une mise à jour USB que si l'état a changé
  if (currentState != lastState)
  {
    // 1. Mettre à jour les axes (Croix directionnelle)
    int axeX = 0;
    int axeY = 0;

    if (gauche) axeX = -1;
    else if (droite) axeX = 1;

    if (haut) axeY = -1;
    else if (bas) axeY = 1;
    
    Gamepad._GamepadReport.X = axeX;
    Gamepad._GamepadReport.Y = axeY;

    // 2. Mettre à jour les boutons
    uint16_t buttons = 0;
    if (b1) buttons |= (1 << 0); // Bouton 0
    if (b2) buttons |= (1 << 1); // Bouton 1

    Gamepad._GamepadReport.buttons = buttons;
    
    // 3. Envoyer le nouvel état à l'ordinateur
    Gamepad.send();

    // Mémoriser l'état actuel
    lastState = currentState;
  }
  
  // -- MODIFICATION (OPTIMISATION 2 : Latence) --
  // Le 'delay(5);' a été supprimé pour réduire la latence au minimum.
  // La boucle tourne maintenant à la vitesse maximale.
  //
  // -- Version optimisée (actuelle) :
  // (Aucun code, le delay est supprimé)
  //
  // -- Ancienne version (non optimisée, 5ms de latence) :
  // delay(5); 
}