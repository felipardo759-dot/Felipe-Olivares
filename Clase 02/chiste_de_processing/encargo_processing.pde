// https://gptonline.ai/
// Processing (Java mode) - "7+3" rebota, "0 ÷" persigue pero nunca lo alcanza

PVector pos73, vel73;
PVector pos0;
float velocidad0 = 2.0;    // velocidad del perseguidor (más lento)
float velocidad73 = 4.0;   // velocidad del "7+3" (más rápido)
float distanciaMinima = 70; // separación mínima que nunca se debe romper

PFont fontBig, fontSmall;
String s73 = "7+3";
String s0  = "0 ÷"; // Si tu IDE da problemas con '÷', cámbialo por "0 /"

void setup() {
  size(900, 600);
  smooth();
  // crear fuentes (evita problemas de codificación/medida)
  fontBig = createFont("Arial", 48, true);
  fontSmall = createFont("Arial", 20, true);
  textAlign(CENTER, CENTER);

  pos73 = new PVector(width*0.4, height*0.5);
  vel73 = PVector.random2D();
  vel73.mult(velocidad73);

  pos0 = new PVector(width*0.8, height*0.5);
}

void draw() {
  background(245);

  // Medidas del texto grande (para rebotar sin salirse)
  textFont(fontBig);
  float halfW73 = textWidth(s73)/2.0;
  float halfH73 = (textAscent() + textDescent()) / 2.0;

  // --- mover "7+3" con rebote (considerando tamaño del texto) ---
  pos73.add(vel73);
  if (pos73.x - halfW73 < 0) {
    pos73.x = halfW73;
    vel73.x *= -1;
  } else if (pos73.x + halfW73 > width) {
    pos73.x = width - halfW73;
    vel73.x *= -1;
  }
  if (pos73.y - halfH73 < 0) {
    pos73.y = halfH73;
    vel73.y *= -1;
  } else if (pos73.y + halfH73 > height) {
    pos73.y = height - halfH73;
    vel73.y *= -1;
  }

  // --- persecución controlada: nunca acercarse menos que distanciaMinima ---
  PVector dir = PVector.sub(pos73, pos0);
  float d = dir.mag();
  if (d > 0.0001) {
    dir.normalize();
    PVector step = PVector.mult(dir, velocidad0);
    // si el paso haría que nos quedemos más cerca que distanciaMinima,
    // limitar el paso para quedar exactamente en la cota mínima
    if (d - step.mag() < distanciaMinima) {
      float allowed = max(0, d - distanciaMinima);
      if (allowed > 0.0001) {
        step.normalize();
        step.mult(allowed);
        pos0.add(step);
      }
      // si allowed == 0 entonces no nos movemos (ya estamos en la cota mínima)
    } else {
      pos0.add(step);
    }
  }

  // --- dibujar "7+3" y su frase ---
  textFont(fontBig);
  fill(0, 100, 255);
  text(s73, pos73.x, pos73.y);
  textFont(fontSmall);
  fill(0);
  text("¡Tú jamás podrás dividirnos!!", pos73.x, pos73.y + 40);

  // --- dibujar "0 ÷" y su frase ---
  textFont(fontBig);
  // color visual cuando se acerca
  if (d < distanciaMinima + 40) fill(255, 80, 80);
  else fill(200, 30, 30);
  text(s0, pos0.x, pos0.y);
  textFont(fontSmall);
  fill(0);
  text("¡No permitiré que se casen entre primos!!", pos0.x, pos0.y + 40);
}
