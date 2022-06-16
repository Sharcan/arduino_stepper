#include <Arduino.h>
#include <Stepper.h>
#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig to and enable it
#endif

#define LED 2
BluetoothSerial BT; // Bluetooth Object

// Définit le nombre de pas par rotation:
const int stepsPerRevolution = 4000;
Stepper myStepper = Stepper(stepsPerRevolution, 18, 21, 19, 23);

void setup() {
  Serial.begin(9600); // Initializing serial connection for debugging
  BT.begin("YEAAAHH"); // Name of your Bluetooth Device and in slave mode
  Serial.println("Bluetooth Device is Ready to Pair");
  pinMode (LED, OUTPUT); // Change the LED pin to OUTPUT
  digitalWrite(LED,HIGH);
  delay(1000);
  digitalWrite(LED,LOW);

  myStepper.setSpeed(5);
}

void loop() {
  if (BT.available()) // Check if we receive anything from Bluetooth
  {
    int incoming = BT.read();
    Serial.println(incoming); // Read what we recevive 
    Serial.print("Received: ");
    Serial.println(incoming);
    if (incoming == 51){ // 1 in ASCII
      myStepper.step(50);
    }
    if (incoming == 50){ // 0 in ASCII
      myStepper.step(-50);
    }
  }
  delay(20);
}