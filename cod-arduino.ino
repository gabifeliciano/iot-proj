#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "SEU_SSID";           
const char* password = "SUA_SENHA";     

const char* mqtt_server = "BROKER_IP";   
const char* mqtt_user = "USUARIO_MQTT";  
const char* mqtt_pass = "SENHA_MQTT";    

WiFiClient espClient;
PubSubClient client(espClient);

int relayPin = 2;  

void callback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  if (message == "LIGAR") {
    digitalWrite(relayPin, HIGH);
  }
  else if (message == "DESLIGAR") {
    digitalWrite(relayPin, LOW);
  }
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao Wi-Fi...");
  }
  Serial.println("Conectado ao Wi-Fi!");

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);  
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT...");
    if (client.connect("ESP8266Client", mqtt_user, mqtt_pass)) {
      Serial.println("Conectado ao broker MQTT!");
      client.subscribe("lampada/status");  
    } else {
      Serial.print("Falha ao conectar, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); 

  int pirState = digitalRead(7);  // Pino do sensor PIR
  if (pirState == HIGH) {
    Serial.println("MOVIMENTO DETECTADO!");
    // Envia para o MQTT que o movimento foi detectado
    client.publish("lampada/movimento", "Detectado");
  }
  delay(100);
}

