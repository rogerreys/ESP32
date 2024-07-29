#include <ESPmDNS.h>
#include <WiFi.h>
#include <WebServer.h>

#define TRIG_PIN 5
#define ECHO_PIN 18
#define LED 16

const char* ssid = "REYES_CLARO";       // Reemplaza con el nombre de tu red WiFi
const char* password = "172540871820";  // Reemplaza con la contraseña de tu red WiFi
const int limit = 20;

WebServer server(80);

void handleApi();
void handleRoot();
long handlehcsr04();

void setup() {
  Serial.begin(115200);
  while(Serial.available()){
    ;
  }
  Serial.println("--- INICIO ----");
  pinMode(TRIG_PIN, OUTPUT);  // Configura el pin TRIG como salida
  pinMode(ECHO_PIN, INPUT);   // Configura el pin ECHO como entrada
  pinMode(LED, OUTPUT);

  // Conexión a la red WiFi
  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi");
  unsigned long startAttemptTime = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    delay(1000);
    Serial.print(".");
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("No se pudo conectar a WiFi");
    return;
  }

  Serial.println("");
  Serial.println("Conectado a la red WiFi");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

  // Configuración de mDNS
  if (!MDNS.begin("esp32")) {  // "esp32" será el nombre de dominio local
    Serial.println("Error configurando mDNS");
    return;
  }
  Serial.println("mDNS configurado. Puedes acceder a la ESP32 usando http://esp32.local");

  // Configuración del servidor web
  server.on("/", handleRoot);
  server.on("/api", handleApi);
  server.begin();
  Serial.println("Servidor iniciado");
}

void loop() {
  server.handleClient();
}

void handleApi() {
  long distance = handlehcsr04();

  // Crea el objeto JSON
  String json = "{\"distance\":";
  json += distance;
  json += "}";

  // Envia la respuesta al cliente
  server.send(200, "application/json", json);
}

void handleRoot() {
  long distance = handlehcsr04();

  // Genera la respuesta HTML
  String html = "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Medicion de Distancia</title></head><body><h1>Distancia Medida</h1><p>Distancia: ";
  html += distance;
  html += " cm</p></body></html>";

  // Envia la respuesta al cliente
  server.send(200, "text/html", html);
  // Serial.print("Distancia: ");
  // Serial.print(distance);
  // Serial.println(" cm");
}

long handlehcsr04() {
  long duration, distance;
  // Limpia el pin TRIG
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Genera un pulso de 5 microsegundos en el pin TRIG
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(TRIG_PIN, LOW);

  // Lee el pin ECHO y calcula la duración del pulso
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calcula la distancia en centímetros
  distance = duration * 0.034 / 2;
  // Enciende el led
  if (distance <= limit) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
  return distance;
}