// Pines
 int ledVerde = 9;
 int ledRojo = 10;
 int botonInicio = 2;
 int botonDetener = 3;

// Estados
bool cronometroActivo = false;
unsigned long tiempoInicio = 0;
unsigned long tiempoActual = 0;
unsigned long tiempoAnteriorImpreso = 0;

// Parpadeo del LED verde
unsigned long anteriorParpadeo = 0;
bool estadoLedVerde = false;
unsigned long intervaloParpadeo = 1000; // 1000 ms

void setup() {
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(botonInicio, INPUT_PULLUP);
  pinMode(botonDetener, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // Leer botón de INICIO
  if (digitalRead(botonInicio) == LOW) {
    if (!cronometroActivo) {
      cronometroActivo = true;
      tiempoInicio = millis();
      tiempoAnteriorImpreso = 0; // reiniciar impresión
      anteriorParpadeo = 0;      // reiniciar parpadeo
      delay(200); // anti-rebote
    }
  }

  // Leer botón de DETENER
  if (digitalRead(botonDetener) == LOW) {
    if (cronometroActivo) {
      cronometroActivo = false;
      digitalWrite(ledVerde, LOW); // apagar verde inmediatamente
      digitalWrite(ledRojo, HIGH); // encender rojo inmediatamente
      delay(200); // anti-rebote
    }
  }

  if (cronometroActivo) {
    digitalWrite(ledRojo, LOW); // apagar rojo

    // Parpadeo controlado por millis()
    unsigned long ahora = millis();
    if (ahora - anteriorParpadeo >= intervaloParpadeo) {
      anteriorParpadeo = ahora;
      estadoLedVerde = !estadoLedVerde;
      digitalWrite(ledVerde, estadoLedVerde);
    }

    // Mostrar tiempo cada segundo
    tiempoActual = millis() - tiempoInicio;
    if (millis() - tiempoAnteriorImpreso >= 1000) {
      tiempoAnteriorImpreso = millis();

      unsigned long segundosTotales = tiempoActual / 1000;
      int horas = segundosTotales / 3600;
      int minutos = (segundosTotales % 3600) / 60;
      int segundos = segundosTotales % 60;

      // Imprimir como HH:MM:SS
      if (horas < 10) Serial.print("0");
      Serial.print(horas); Serial.print(":");

      if (minutos < 10) Serial.print("0");
      Serial.print(minutos); Serial.print(":");

      if (segundos < 10) Serial.print("0");
      Serial.println(segundos);
    }

  } else {
    // Si está detenido, el LED verde está apagado
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledRojo, HIGH);
  }
}