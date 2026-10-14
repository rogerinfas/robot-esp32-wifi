// Robot movil con control por pagina web (WiFi) - version botones
// Placa: ESP32 DEVKIT V1 (en Arduino IDE: "ESP32 Dev Module")
// El ESP32 crea su propia red: "RobotESP32" (sin internet, solo para el carro)
// Conecta tu celular a esa red y abre http://192.168.4.1

#include <WiFi.h>
#include <WebServer.h>
#include "pagina.h"  // la pagina web vive en la otra pestana

// Motores (puente H L298N) con POO simple:
// cada objeto Motor agrupa sus 2 pines y sabe avanzar/retroceder/detenerse.
class Motor {
  private:
    int _in1, _in2;
  public:
    Motor(int in1, int in2) : _in1(in1), _in2(in2) {}
    void iniciar() {
      pinMode(_in1, OUTPUT);
      pinMode(_in2, OUTPUT);
      detener();
    }
    void adelante()  { digitalWrite(_in1, HIGH); digitalWrite(_in2, LOW); }
    void atras()     { digitalWrite(_in1, LOW);  digitalWrite(_in2, HIGH); }
    void detener()   { digitalWrite(_in1, LOW);  digitalWrite(_in2, LOW); }
};

Motor motorIzq(14, 27);  // IN1, IN2 (motor A)
Motor motorDer(2, 4);    // IN3, IN4 (motor B)

WebServer server(80);

void parar()     { motorIzq.detener(); motorDer.detener(); }
void adelante()  { motorIzq.atras();    motorDer.atras(); }  // invertido: F = motores atras
void atras()     { motorIzq.adelante(); motorDer.adelante(); }  // invertido: B = motores adelante
void izquierda() { motorIzq.atras();    motorDer.adelante(); }  // gira sobre su eje
void derecha()   { motorIzq.adelante();  motorDer.atras(); }     // gira sobre su eje
void adelanteIzq() { motorIzq.detener(); motorDer.adelante(); } // curvas suaves
void adelanteDer() { motorIzq.adelante(); motorDer.detener(); }
void atrasIzq()    { motorIzq.detener(); motorDer.atras(); }
void atrasDer()    { motorIzq.atras();    motorDer.detener(); }

void handleRoot() {
  server.send(200, "text/html", PAGINA);
}

void handleMove() {
  String d = server.arg("dir");
  if (d == "F") adelante();
  else if (d == "B") atras();
  else if (d == "L") izquierda();
  else if (d == "R") derecha();
  else if (d == "FL") adelanteIzq();
  else if (d == "FR") adelanteDer();
  else if (d == "BL") atrasIzq();
  else if (d == "BR") atrasDer();
  else parar();
  Serial.println("CMD: " + d);
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);
  motorIzq.iniciar();
  motorDer.iniciar();
  parar();

  WiFi.softAP("RobotESP32");
  Serial.print("Red WiFi lista. IP: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/move", handleMove);
  server.begin();
  Serial.println("Servidor web listo en http://192.168.4.1");
}

void loop() {
  server.handleClient();
}
