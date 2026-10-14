# Chuleta de comandos Linux — Robot ESP32

Terminal, desde cualquier carpeta. Cambia `NOMBRE` por tu carpeta de
proyecto y `/dev/ttyUSB0` por tu puerto si fuera distinto
(por ejemplo `/dev/ttyACM0`).

## ¿Está conectado el ESP32?

```bash
ls /dev/ttyUSB* /dev/ttyACM*
lsusb | grep -i -E "cp210|ch340|silicon|1a86|10c4"
pio device list
```

## ¿Tengo permiso del puerto?

```bash
groups          # debe salir uucp (Arch) o dialout (Debian/Ubuntu)
```

Si falta, agrégate y **cierra sesión**:

```bash
# Arch / EndeavourOS / Manjaro
sudo usermod -aG uucp $USER
# Debian / Ubuntu / Mint
sudo usermod -aG dialout $USER
```

## Crear proyecto nuevo (ESP32 DEVKIT)

```bash
pio project init --board esp32dev --project-dir NOMBRE
```

## Compilar (sin subir)

```bash
pio run --project-dir NOMBRE
```

## Subir al ESP32 (compila + graba en la flash)

```bash
pio run -t upload --project-dir NOMBRE
```

> Si el primer intento falla (`Failed to connect`, `stub`), reintenta:
> en algunas placas el segundo intento entra.

## Subir + abrir monitor serial

```bash
pio run -t upload -t monitor --project-dir NOMBRE
```

## Ver mensajes del ESP32 (monitor serial a 115200)

```bash
pio device monitor --baud 115200
```

Salir con `Ctrl+C`. Alternativa con Python (lee 8 segundos):

```bash
python3 -c "import serial,time
s=serial.Serial('/dev/ttyUSB0',115200,timeout=1)
t0=time.time()
while time.time()-t0 < 8:
    l=s.readline().decode('utf-8','replace').strip()
    if l: print(l)"
```

## Borrar compilación y recompilar limpio

```bash
pio run -t clean --project-dir NOMBRE
```

## Ver datos de la placa conectada

```bash
pio device list --serial
pio --version
```

## Instalación rápida (referencia)

```bash
# Arch / EndeavourOS / Manjaro
sudo pacman -S --needed platformio-core platformio-core-udev
# Debian / Ubuntu / Mint
sudo apt install python3-pip && pip3 install --user platformio
```

---

## Apagar bien / cambiar de modo (USB, pilas, VIN)

El carro no tiene botón: se apaga sacando las pilas.

**REGLA DE ORO:**
- Pilas = últimas en entrar, primeras en salir.
- **NUNCA USB + cable VIN juntos** (quema el regulador).
  O lo alimentas por USB, o por VIN, nunca los dos.

**1. Modo PC / programar (solo USB):**
Para subir código desde el PC.
1. Saca las pilas.
2. Quita el cable 5V→VIN del ESP32 (si lo tiene).
3. Conecta el USB al PC.
4. Sube: `pio run -t upload --project-dir esp32-robot-wifi`

**2. Modo prueba (USB + pilas, con PC al lado):**
Para probar motores con el PC conectado.
1. USB conectado, SIN pilas al inicio.
2. Sin cable VIN puesto.
3. Mete las pilas.
4. Prueba en `http://192.168.4.1`.
5. Para parar/apagar: saca las pilas primero, luego el USB.

**3. Modo autónomo (solo pilas, sin PC ni powerbank):**
Para usarlo en la calle. El L298N alimenta al ESP32.
1. Desconecta el USB (sin USB).
2. Pon el cable: tornillo **5V del L298N** → pin **VIN** del ESP32.
   (GND común ya queda: negro pilas + GND L298N + GND ESP32).
3. Mete las pilas → enciende solo, sale `RobotESP32`.
4. Para apagar: saca las pilas.

**Volver de autónomo a PC:**
1. Saca las pilas.
2. Quita el cable 5V→VIN.
3. Recién ahí conecta el USB al PC.

**Regla de oro:** programar = solo USB, sin pilas, sin VIN. Probar = USB + pilas, sin VIN. Calle = solo pilas + VIN, sin USB.
