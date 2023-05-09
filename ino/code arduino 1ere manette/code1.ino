// Inclure les bibliothèques nécessaires
#include <Bounce2.h>

// Broches des boutons
#define BUTTON1_PIN 2
#define BUTTON2_PIN 3
#define BUTTON3_PIN 4
#define BUTTON4_PIN 5

// Broches des LEDs
#define LED1_PIN 6
#define LED2_PIN 7
#define LED3_PIN 8
#define LED4_PIN 9

// Temps de rebond des boutons (en ms)
#define DEBOUNCE_TIME 20

// Créer des objets pour les boutons
Bounce button1 = Bounce(BUTTON1_PIN, DEBOUNCE_TIME);
Bounce button2 = Bounce(BUTTON2_PIN, DEBOUNCE_TIME);
Bounce button3 = Bounce(BUTTON3_PIN, DEBOUNCE_TIME);
Bounce button4 = Bounce(BUTTON4_PIN, DEBOUNCE_TIME);

void setup() {
  // Définir les broches des boutons en entrée et activer les résistances de pull-up internes
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(BUTTON3_PIN, INPUT_PULLUP);
  pinMode(BUTTON4_PIN, INPUT_PULLUP);

  // Définir les broches des LEDs en sortie
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);
}

void loop() {
  // Mettre à jour l'état des boutons
  button1.update();
  button2.update();
  button3.update();
  button4.update();

  // Vérifier si le bouton 1 est enfoncé
  if (button1.fell()) {
    digitalWrite(LED1_PIN, HIGH); // Allumer la LED 1
  }
  if (button1.rose()) {
    digitalWrite(LED1_PIN, LOW); // Éteindre la LED 1
  }

  // Vérifier si le bouton 2 est enfoncé
  if (button2.fell()) {
    digitalWrite(LED2_PIN, HIGH); // Allumer la LED 2
  }
  if (button2.rose()) {
    digitalWrite(LED2_PIN, LOW
