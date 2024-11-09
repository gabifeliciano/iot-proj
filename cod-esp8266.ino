#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Informações da rede Wi-Fi
const char* ssid = "SEU_SSID";           
const char* password = "SUA_SENHA";     

// Informações do Broker MQTT
const char* mqtt_server = "BROKER_IP";   
const char* mqtt_user = "USUARIO_MQTT";  
const char* mqtt_pass = "SENHA_MQTT";    

WiFiClient espClient;
PubSubClient client(espClient);

// Pino do relé (para monitoramento)
int relayPin = 2;  

void callback(char* topic, byte* payload, unsigned int length) {
}

void setup() {
  Serial.begin(115200);

  // Conexão com Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao Wi-Fi...");
  }
  Serial.println("Conectado ao Wi-Fi!");

  // Configuração do MQTT
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  pinMode(relayPin, INPUT);  // Usando o pino para monitorar o status da lâmpada
}

void reconnect() {
  // Reconexão ao broker MQTT se necessário
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

  // Monitoramento do status da lâmpada
  int lampStatus = digitalRead(relayPin);  

  // Envia o status da lâmpada para o MQTT
  if (lampStatus == HIGH) {
    client.publish("lampada/status", "LIGADA");
  } else {
    client.publish("lampada/status", "DESLIGADA");
  }

  delay(1000);  // Publica o status a cada 1 segundo
}
