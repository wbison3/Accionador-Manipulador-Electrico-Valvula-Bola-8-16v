#include <EEPROM.h>

#define LAST_STATE_ADDRESS 10
#define LAST_STATE_OPEN 100
#define LAST_STATE_CLOSE 200

#include <AFMotor.h>

AF_DCMotor motor(1);
#define SPEED 200
#define TIEMPO_RECORRIDO 25*1000     // 25s - ya bien montado se nota menor velocidad por el esfuerzo
#define TIEMPO_DE_RIEGO 120000     // 2min, do not multiply here, the preprocesor does not support big numbers, set the exact value needed
#define REINICIAR_CICLO 3*60*60*1000   // 3h
#define IDLE_TIME 250

#define STATE_APERTURA 1
#define STATE_RIEGO 2
#define STATE_CERRADO 3
#define STATE_IDLE 4

int state;
unsigned long startTime;
unsigned long delayTime;

void setup() {
  // Setup motor
  motor.setSpeed(SPEED);

  int last_state = EEPROM.read(LAST_STATE_ADDRESS);
  if (LAST_STATE_CLOSE == last_state) {
    // Save state
    EEPROM.write(LAST_STATE_ADDRESS, LAST_STATE_OPEN);

    // Loop state
    state = STATE_APERTURA;

    // Start motor
    motor.run(FORWARD);
  } else {
    // Save state
    EEPROM.write(LAST_STATE_ADDRESS, LAST_STATE_CLOSE);

    // Loop state
    state = STATE_CERRADO;

    // Start motor
    motor.run(BACKWARD);
  }

  startTime = millis();
  delayTime = TIEMPO_RECORRIDO;
}

void loop() {
  switch (state) {
    case STATE_APERTURA:
      if(millis() - startTime > delayTime) {
        // stop motor
        motor.run(RELEASE);

        // Prepare next state
        state = STATE_RIEGO;
        startTime = millis();
        delayTime = TIEMPO_DE_RIEGO;
      }
    break;

    case STATE_RIEGO:
      if(millis() - startTime > delayTime) {
        motor.run(BACKWARD);

        state = STATE_CERRADO;
        startTime = millis();
        delayTime = TIEMPO_RECORRIDO;
      }
      break;

    case STATE_CERRADO:
      if(millis() - startTime > delayTime) {
        // stop motor
        motor.run(RELEASE);

        // Save state
        EEPROM.write(LAST_STATE_ADDRESS, LAST_STATE_CLOSE);

        // Prepare next state
        state = STATE_IDLE;
      }
    break;
  }

  delay(IDLE_TIME);
}
