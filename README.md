# Robot ESP32 con control WiFi

Carrito robot con **ESP32 DEVKIT V1** + **puente H L298N** + 2 motores DC,
manejado desde el celular por WiFi (sin internet, sin apps, sin piezas extra).

## Cómo funciona

1. El ESP32 crea su propia red WiFi (`RobotESP32`).
2. Conectas tu celular a esa red y abres `http://192.168.4.1`.
3. Botones con flechas: mantén presionado para moverte, suelta para parar.

## Contenido

| Archivo | Para qué |
|---|---|
| `RobotWiFiBotones/` | Programa del carro (Arduino IDE, 2 pestañas: código + página) |
| `LEEME.txt` | Instructivo paso a paso para **Windows** |
| `LEEME_LINUX.txt` | Instructivo paso a paso para **Linux** (PlatformIO) |
| `COMANDOS.md` | Chuleta de comandos Linux |

## Empieza aquí

- En Windows → lee [`LEEME.txt`](LEEME.txt).
- En Linux → lee [`LEEME_LINUX.txt`](LEEME_LINUX.txt).

## Hardware

- ESP32 DEVKIT V1 (30 pines, chip CP2102)
- Módulo puente H L298N (jumpers ENA, ENB y 5V_EN puestos)
- 2 motores DC + 2 pilas 18650 en serie (7.4V)
- Sin protoboard, sin resistencias

Regla de oro: las pilas son las **últimas en entrar y las primeras en salir**.
