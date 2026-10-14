// Pagina web del carro (segunda pestana en Arduino IDE).
// Para cambiar botones, colores o textos, edita solo este archivo.
#pragma once

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
