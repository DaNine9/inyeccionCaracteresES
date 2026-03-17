# inyeccionCaracteresES
Un sketch que permite la inyección de caracteres en dispositivos de teclado español usando Arduino UNO
Para poder enviar teclas a través del arduino, hay que reflashear su firmware con el script de DuckDuino (Lacerda53) - https://github.com/Lacerda53/duckduino

**USAR CON CUIDADO**

# funciones
**Escribir una string:**
  - typeString("Hola Mundo!!!");
<br>

**presionar enter:**
  - ENTER();
<br>

**presionar control + tecla**
- CTRL("c");
<br>

**presionar una tecla con un modificador**
- pressKeyWithModifier("w", KEY_LEFT_CTRL);
