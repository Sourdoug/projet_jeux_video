#include <Bounce2.h>

// Définition des broches des boutons
const int boutonRouge = 2;
const int boutonJaune = 3;
const int boutonBleu = 4;
const int boutonVert = 5;

// Définition des broches des LEDs correspondantes aux boutons
const int ledRouge = 6;
const int ledJaune = 7;
const int ledBleu = 8;
const int ledVert = 9;

// Définition de la broche de la LED témoin
const int ledTemoin = 10;

// Initialisation de l'objet Bounce pour chaque bouton
Bounce boutonRougeBounce = Bounce();
Bounce boutonJauneBounce = Bounce();
Bounce boutonBleuBounce = Bounce();
Bounce boutonVertBounce = Bounce();

// Définition de la vitesse du jeu
const int vitesseJeu = 500;

void setup() {
  // Initialisation des broches de boutons en entrée
  pinMode(boutonRouge, INPUT_PULLUP);
  pinMode(boutonJaune, INPUT_PULLUP);
  pinMode(boutonBleu, INPUT_PULLUP);
  pinMode(boutonVert, INPUT_PULLUP);
  
  // Initialisation des broches de LEDs en sortie
  pinMode(ledRouge, OUTPUT);
  pinMode(ledJaune, OUTPUT);
  pinMode(ledBleu, OUTPUT);
  pinMode(ledVert, OUTPUT);

  // Initialisation de la broche de la LED témoin en sortie
  pinMode(ledTemoin, OUTPUT);
  digitalWrite(ledTemoin, HIGH); // LED témoin allumée au démarrage du système

  // Configuration de l'objet Bounce pour chaque bouton
  boutonRougeBounce.attach(boutonRouge);
  boutonRougeBounce.interval(5);
  boutonJauneBounce.attach(boutonJaune);
  boutonJauneBounce.interval(5);
  boutonBleuBounce.attach(boutonBleu);
  boutonBleuBounce.interval(5);
  boutonVertBounce.attach(boutonVert);
  boutonVertBounce.interval(5);
}

void loop() {
  // Vérification de l'état de chaque bouton
  boutonRougeBounce.update();
  if (boutonRougeBounce.fell()) {
    digitalWrite(ledRouge, HIGH);
    delay(vitesseJeu / 2);
    digitalWrite(ledRouge, LOW);
  }
  boutonJauneBounce.update();
  if (boutonJauneBounce.fell()) {
    digitalWrite(ledJaune, HIGH);
    delay(vitesseJeu / 2);
    digitalWrite(ledJaune, LOW);
  }
  boutonBleuBounce.update();
  if (boutonBleuBounce.fell()) {
    digitalWrite(ledBleu, HIGH);
    delay(vitesseJeu / 2);
    digitalWrite(ledBleu, LOW);
  }
  boutonVertBounce.update();
  if (boutonVertBounce.fell()) {
    digitalWrite(ledVert, HIGH);
    delay(vitesseJeu / 2);
    digitalWrite(ledVert, LOW);
  }

  //
