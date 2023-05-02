#include <EEPROM.h>

#define LAST_STATE_ADDRESS 10
#define LAST_STATE_OPEN 100
#define LAST_STATE_CLOSE 200

#include <AFMotor.h>

AF_DCMotor motor(1);
#define SPEED 200
#define TIEMPO_RECORRIDO 25*1000      // 25s - toma 12s libre y como 15s ya montado. Montado se nota menor velocidad por el esfuerzo.
                                      // A veces tooma de 1-3 segundos empezar a moverse dependiendo que tan dura se ponga la llave al principio.
                                      // Se recomienda utilizar aflojatodo en la llave para que no se atasque.
                                      // El manipulador electrico ya trae protección de sobre corriente. Los 10s que se dejan de seguridad no debe pasar nada.
#define TIEMPO_DE_RIEGO 120000        // 2min. 2*60*1000. No multiplicar aquí. El preprocesador no soporta números grandes, poner el valor exacto.
#define REINICIAR_CICLO 10800000      // 3h. 3*60*60*1000. No multiplicar aquí. El preprocesador no soporta números grandes, poner el valor exacto.
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
