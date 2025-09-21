
int ledPin = 13;

// tiempos (ajusta si quieres)
int tiempoPunto = 100;   // duración del punto
int tiempoRaya  = 500;   // duración de la raya
int separador    = 100;  // pausa entre símbolos (interna a punto/raya)
int finCaracter  = 300;  // pausa entre letras
int espacio      = 700;  // pausa entre palabras

// Diccionario A-Z
const char* morseLetters[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
  "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
  "..-", "...-", ".--", "-..-", "-.--", "--.."
};

// Diccionario 0-9
const char* morseDigits[] = {
  "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."
};

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Listo para enviar Morse. Escribe algo en el Serial o espera el mensaje por defecto.");
}

void loop() {
  String mensajePorDefecto = "El numero 3 y el numero 7 se querian casar pero el 0 dijo alto no permitire que se casen entre primos y ellos le dijeron tu jamas podras dividirnos";
  String texto = mensajePorDefecto;

  // Si hay algo en Serial, lo usamos (hasta newline)
  if (Serial.available()) {
    texto = Serial.readStringUntil('\n');
    texto.trim(); // quitar espacios extra
    if (texto.length() == 0) texto = mensajePorDefecto;
    Serial.print("Enviando desde Serial: ");
    Serial.println(texto);
  } else {
    Serial.println("Enviando mensaje por defecto...");
  }

  enviarMorse(texto);

  Serial.println("----- FIN DEL MENSAJE -----");
  delay(3000); // espera antes de repetir / permitir entrada Serial
}

void enviarMorse(String texto) {
  for (int i = 0; i < texto.length(); i++) {
    char c = toupper(texto[i]);

    if (c >= 'A' && c <= 'Z') {
      const char* codigo = morseLetters[c - 'A'];
      Serial.print(c);
      Serial.print(" -> ");
      Serial.println(codigo);

      // recorrer símbolos del caracter
      for (int j = 0; codigo[j] != '\0'; j++) {
        if (codigo[j] == '.') {
          punto();
        } else if (codigo[j] == '-') {
          raya();
        }
        // separador entre símbolos está dentro de punto() y raya()
      }
      // pausa entre letras
      delay(finCaracter);
    }
    else if (c >= '0' && c <= '9') {
      const char* codigo = morseDigits[c - '0'];
      Serial.print(c);
      Serial.print(" -> ");
      Serial.println(codigo);

      for (int j = 0; codigo[j] != '\0'; j++) {
        if (codigo[j] == '.') {
          punto();
        } else if (codigo[j] == '-') {
          raya();
        }
      }
      delay(finCaracter);
    }
    else if (c == ' ') {
      // espacio entre palabras
      Serial.println("(espacio)");
      delay(espacio);
    }
    else {
      // otros caracteres: los ignoramos (puedes agregar más).
      Serial.print("(ignorado) ");
      Serial.println(c);
    }
  }
}

void punto() {
  digitalWrite(ledPin, HIGH);
  Serial.println("punto");
  delay(tiempoPunto);
  digitalWrite(ledPin, LOW);
  delay(separador); // pausa intra-symbol
}

void raya() {
  digitalWrite(ledPin, HIGH);
  Serial.println("raya");
  delay(tiempoRaya);
  digitalWrite(ledPin, LOW);
  delay(separador); // pausa intra-symbol
}
