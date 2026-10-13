// Robot movil con control por pagina web (WiFi) - version botones
// Placa: ESP32 DEVKIT V1 (en Arduino IDE: "ESP32 Dev Module")
// El ESP32 crea su propia red: "RobotESP32" (sin internet, solo para el carro)
// Conecta tu celular a esa red y abre http://192.168.4.1

#include <WiFi.h>
#include <WebServer.h>

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
void adelante()  { motorIzq.adelante(); motorDer.adelante(); }  // frente invertido
void atras()     { motorIzq.atras();    motorDer.atras(); }
void izquierda() { motorIzq.atras();    motorDer.adelante(); }  // gira sobre su eje
void derecha()   { motorIzq.adelante();  motorDer.atras(); }     // gira sobre su eje
void adelanteIzq() { motorIzq.detener(); motorDer.adelante(); } // curvas suaves
void adelanteDer() { motorIzq.adelante(); motorDer.detener(); }
void atrasIzq()    { motorIzq.detener(); motorDer.atras(); }
void atrasDer()    { motorIzq.atras();    motorDer.detener(); }

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
