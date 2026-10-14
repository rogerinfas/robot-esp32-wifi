// Pagina web del carro (segunda pestana en Arduino IDE).
// Para cambiar botones, colores o textos, edita solo este archivo.
#pragma once

const char PAGINA[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html lang='es'><head>
<meta charset='utf-8'><meta name='viewport' content='width=device-width,initial-scale=1,maximum-scale=1,user-scalable=no'>
<title>Robot ESP32 de Roger</title>
<style>
*{box-sizing:border-box;margin:0;padding:0}
:root{--gold:#d4af37;--gold-l:#f5d76e;--bg:#0a0a0a;--card:#141414;--line:#2a2415}
body{font-family:system-ui,-apple-system,Segoe UI,Roboto,sans-serif;background:var(--bg);color:#f5f0dc;min-height:100vh;display:flex;flex-direction:column;align-items:center;padding:12px}
.wrap{width:100%;max-width:430px;display:flex;flex-direction:column;gap:12px}
header{text-align:center;padding:14px 12px;background:linear-gradient(180deg,#1a1503,#141414);border:1px solid var(--gold);border-radius:16px}
header h1{font-size:clamp(20px,5.5vw,26px);color:var(--gold-l);letter-spacing:.5px}
header p{font-size:12px;color:#a99e7a;margin-top:4px}
#estado{display:inline-block;margin-top:8px;font-size:14px;font-weight:800;letter-spacing:1px;color:#0a0a0a;background:var(--gold);border-radius:999px;padding:6px 18px;min-width:120px}
.panel{background:var(--card);border:1px solid var(--line);border-radius:16px;padding:16px 12px}
.grid{display:grid;grid-template-columns:repeat(3,1fr);gap:12px;max-width:330px;margin:0 auto}
button{aspect-ratio:1/1;width:100%;font-size:clamp(28px,8vw,38px);border-radius:16px;border:1px solid var(--gold);background:#1c1a10;color:var(--gold-l);touch-action:none;-webkit-user-select:none;user-select:none;-webkit-tap-highlight-color:transparent;box-shadow:0 4px 0 #6b5a1e;cursor:pointer}
button:active{transform:translateY(3px);box-shadow:0 1px 0 #6b5a1e;background:#2a2410}
.stop{background:linear-gradient(180deg,#3a2f0a,#211c06);color:var(--gold-l);border-color:var(--gold)}
.hint{text-align:center;color:#8a7f5c;font-size:12px;margin-top:10px}
footer{text-align:center;color:#8a7f5c;font-size:12px;padding:10px}
footer b{color:var(--gold-l)}
@media (min-width:500px){.grid{max-width:360px}}
</style></head><body>
<div class='wrap'>
<header>
<h1>Robot ESP32</h1>
<p>RobotESP32 de Roger &middot; 192.168.4.1</p>
<div id='estado'>STOP</div>
</header>
<div class='panel'>
<div class='grid'>
<div></div><button data-d='F'>&#9650;</button><div></div>
<button data-d='L'>&#9664;</button><button class='stop' data-d='S'>&#9632;</button><button data-d='R'>&#9654;</button>
<div></div><button data-d='B'>&#9660;</button><div></div>
</div>
<p class='hint'>Manten presionado para moverte, suelta para parar.</p>
</div>
<footer>Elaborado por <b>Roger Infa</b> y <b>Rodrigo Ojeda</b></footer>
</div>
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
