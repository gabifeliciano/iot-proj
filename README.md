# Descrição
O  projeto EffiLight: Sistema de Iluminação Eficiente visa criar um sistema automatizado e inteligente para controle de iluminação, com o objetivo de otimizar o uso de energia elétrica. O sistema detecta a presença de indivíduos no ambiente e acende a lâmpada automaticamente, garantindo que a iluminação seja acionada apenas quando necessária, o que contribui significativamente para a eficiência energética.

A plataforma central do sistema é a placa ESP8266 (NodeMCU), que se conecta à rede Wi-Fi e se comunica com um broker MQTT, permitindo o monitoramento remoto do status da lâmpada. O sensor PIR (Passive Infrared Sensor) desempenha um papel fundamental, pois detecta a movimentação na área monitorada. Ao identificar a presença de uma pessoa, o sensor aciona o relé, que, por sua vez, liga a lâmpada.

Além disso, o sistema permite o monitoramento remoto do status da lâmpada por meio do protocolo MQTT. O aplicativo IoT MQTT Panel é utilizado para visualizar em tempo real o estado da lâmpada, promovendo uma gestão energética mais inteligente e prática.
