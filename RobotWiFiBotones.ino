// Robot movil con control por pagina web (WiFi) - version botones
// Placa: ESP32 DEVKIT V1 (en Arduino IDE: "ESP32 Dev Module")
// El ESP32 crea su propia red: "RobotESP32" (sin internet, solo para el carro)
// Conecta tu celular a esa red y abre http://192.168.4.1

#include <WiFi.h>
#include <WebServer.h>

// Motores (puente H L298N)
const int motorA1 = 14;  // IN1
const int motorA2 = 27;  // IN2
const int motorB1 = 2;   // IN3
const int motorB2 = 4;   // IN4

WebServer server(80);

void parar() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}
void adelante() {  // (invertido: el frente del carro es el otro lado)
  digitalWrite(motorA1, HIGH); digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH); digitalWrite(motorB2, LOW);
}
void atras() {
  digitalWrite(motorA1, LOW);  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);  digitalWrite(motorB2, HIGH);
}
void izquierda() {  // gira sobre su eje
  digitalWrite(motorA1, LOW);  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH); digitalWrite(motorB2, LOW);
}
void derecha() {  // gira sobre su eje
  digitalWrite(motorA1, HIGH); digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);  digitalWrite(motorB2, HIGH);
}

const char PAGINA[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html><head>
<meta charset='utf-8'><meta name='viewport' content='width=device-width,initial-scale=1'>
<title>Robot ESP32</title>
<style>
body{font-family:sans-serif;text-align:center;background:#111;color:#eee;margin:0;padding:16px}
h2{margin:8px}
table{margin:10px auto;border-spacing:10px}
button{width:90px;height:90px;font-size:36px;border-radius:16px;border:none;
background:#1e88e5;color:#fff;touch-action:none;-webkit-user-select:none;user-select:none}
button:active{background:#0d47a1}
.stop{background:#e53935}
#estado{font-size:20px;min-height:28px;color:#9ccc65}
</style></head><body>
<h2>Robot ESP32</h2>
<div id='estado'>STOP</div>
<table>
<tr><td></td><td><button data-d='F'>&#9650;</button></td><td></td></tr>
<tr><td><button data-d='L'>&#9664;</button></td>
<td><button class='stop' data-d='S'>&#9632;</button></td>
<td><button data-d='R'>&#9654;</button></td></tr>
<tr><td></td><td><button data-d='B'>&#9660;</button></td><td></td></tr>
</table>
<p>Manten presionado para moverte, suelta para parar.</p>
<script>
const est=document.getElementById('estado');
const nom={F:'ADELANTE',B:'ATRAS',L:'IZQUIERDA',R:'DERECHA',S:'STOP'};
function manda(d){fetch('/move?dir='+d);est.textContent=nom[d];}
document.querySelectorAll('button').forEach(b=>{
 const d=b.dataset.d;
 const ini=e=>{e.preventDefault();manda(d);};
 const fin=e=>{e.preventDefault();if(d!=='S')manda('S');};
 b.addEventListener('touchstart',ini,{passive:false});
 b.addEventListener('touchend',fin);b.addEventListener('touchcancel',fin);
 b.addEventListener('mousedown',ini);b.addEventListener('mouseup',fin);
 b.addEventListener('mouseleave',fin);
});
</script></body></html>
)rawliteral";

void handleRoot() {
  server.send(200, "text/html", PAGINA);
}

void handleMove() {
  String d = server.arg("dir");
  if (d == "F") adelante();
  else if (d == "B") atras();
  else if (d == "L") izquierda();
  else if (d == "R") derecha();
  else parar();
  Serial.println("CMD: " + d);
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
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
