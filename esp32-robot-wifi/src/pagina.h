// Pagina web del carro (segunda pestana en Arduino IDE).
// Para cambiar botones, colores o textos, edita solo este archivo.
#pragma once

const char PAGINA[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html><head>
<meta charset='utf-8'><meta name='viewport' content='width=device-width,initial-scale=1'>
<title>Robot ESP32 de Roger</title>
<style>
*{box-sizing:border-box}
body{font-family:system-ui,-apple-system,Segoe UI,Roboto,sans-serif;text-align:center;background:linear-gradient(160deg,#0f172a,#1e293b);color:#e2e8f0;margin:0;padding:20px;min-height:100vh;display:flex;flex-direction:column;align-items:center}
.card{background:#1e293b;border:1px solid #334155;border-radius:20px;padding:20px 24px;max-width:420px;width:100%;box-shadow:0 10px 30px rgba(0,0,0,.4)}
h2{margin:6px 0 2px;font-size:26px;letter-spacing:.5px}
.sub{color:#94a3b8;font-size:14px;margin-bottom:12px}
#estado{display:inline-block;font-size:18px;font-weight:700;min-height:30px;color:#052e16;background:#86efac;border-radius:999px;padding:4px 18px;margin:8px 0 12px}
table{margin:12px auto;border-spacing:12px}
button{width:92px;height:92px;font-size:38px;border-radius:20px;border:1px solid #1d4ed8;background:linear-gradient(180deg,#3b82f6,#1d4ed8);color:#fff;touch-action:none;-webkit-user-select:none;user-select:none;box-shadow:0 6px 0 #1e3a8a;cursor:pointer}
button:active{transform:translateY(4px);box-shadow:0 2px 0 #1e3a8a;background:#1d4ed8}
.stop{background:linear-gradient(180deg,#ef4444,#b91c1c);border-color:#7f1d1d;box-shadow:0 6px 0 #7f1d1d}
.stop:active{background:#b91c1c;box-shadow:0 2px 0 #7f1d1d}
.hint{color:#94a3b8;font-size:13px;margin:10px 0 0}
footer{margin-top:16px;color:#64748b;font-size:13px}
footer b{color:#cbd5e1}
</style></head><body>
<div class='card'>
<h2>Robot ESP32</h2>
<div class='sub'>RobotESP32 de Roger &middot; http://192.168.4.1</div>
<div id='estado'>STOP</div>
<table>
<tr><td></td><td><button data-d='F'>&#9650;</button></td><td></td></tr>
<tr><td><button data-d='L'>&#9664;</button></td>
<td><button class='stop' data-d='S'>&#9632;</button></td>
<td><button data-d='R'>&#9654;</button></td></tr>
<tr><td></td><td><button data-d='B'>&#9660;</button></td><td></td></tr>
</table>
<p class='hint'>Manten presionado para moverte, suelta para parar.</p>
</div>
<footer>Elaborado por <b>Roger Infa</b> y <b>Rodrigo Ojeda</b></footer>
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
