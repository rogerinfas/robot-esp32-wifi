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

**Regla de oro:** programar = solo USB, sin pilas. Probar = USB + pilas.
