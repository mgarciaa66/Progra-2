// Pines
 int pinPot = A0;
 int ledRojo = 9;
 int ledVerde = 10;
 int ledAzul = 11;

void setup() {
  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAzul, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int valorPot = analogRead(pinPot); // 0 a 1023
  Serial.println(valorPot);          // Mostrar valor en Serial

  // Apagar todos los LEDs primero
  analogWrite(ledRojo, 0);
  analogWrite(ledVerde, 0);
  analogWrite(ledAzul, 0);

  // Si el valor es bajo solo LED rojo
  if (valorPot < 341) {
    int brillo = map(valorPot, 0, 340, 0, 255);
    analogWrite(ledRojo, brillo);
  }
  // Si el valor es medio  LED rojo y verde
  else if (valorPot < 682) {
    int brillo = map(valorPot, 341, 681, 0, 255);
    analogWrite(ledRojo, 255);          // Rojo al máximo
    analogWrite(ledVerde, brillo);      // Verde progresivo
  }
  // Si el valor es alto LED rojo, verde y azul
  else {
    int brillo = map(valorPot, 682, 1023, 0, 255);
    analogWrite(ledRojo, 255);
    analogWrite(ledVerde, 255);
    analogWrite(ledAzul, brillo);
  }

  delay(10);
}