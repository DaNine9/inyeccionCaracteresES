#define KEY_LEFT_CTRL   0x01
#define KEY_LEFT_SHIFT  0x02
#define KEY_LEFT_ALT    0x04
#define KEY_LEFT_GUI    0x08
#define KEY_RIGHT_CTRL  0x10
#define KEY_RIGHT_SHIFT 0x20
#define KEY_RIGHT_ALT   0x40
#define KEY_RIGHT_GUI   0x80
#define KEY_ENTER       0x28
#define KEY_SPC         0x2C
#define KEY_NONE        0x37

uint8_t buf[8] = { 0 }; 

void setup();
void loop();

//escribir una string -> typeString("hola españa")
void typeString(const char *str);

//presionar enter
void ENTER();

//presionar control + key -> CTRL(e)
void CTRL(char *c);

//presionar una tecla con un modificador -> pressKeyWithModifier(a, KEY_LEFT_CTRL)
void pressKeyWithModifier(uint8_t key, uint8_t modifier);

void setup() {
  Serial.begin(9600);
  delay(100);

  //ESCRIBIR AQUI EL CODIGO

  CTRL("t");
  delay("200");
  typeString("Hola españa");


  
}

void loop() {
}

void typeString(const char *str) {
    while (*str) {
        char c = *str;

        // Handle lowercase letters
        if (c >= 'a' && c <= 'z') {
            buf[2] = c - 'a' + 4;  // Map a-z to HID codes (4-29)
            Serial.write(buf, 8);   // Send keypress
            buf[2] = 0;             // Release key
            Serial.write(buf, 8);   // Release key
        }
        // Handle uppercase letters
        else if (c >= 'A' && c <= 'Z') {
            buf[0] = KEY_LEFT_SHIFT;  // Set shift for uppercase
            buf[2] = c - 'A' + 4;     // Map A-Z to HID codes
            Serial.write(buf, 8);      // Send keypress
            buf[0] = 0;                // Release shift
            buf[2] = 0;                // Release key
            Serial.write(buf, 8);      // Release key
        }
        // Handle numbers (0-9) with individual cases
        else if (c >= '0' && c <= '9') {
            switch (c) {
                case '0':
                    buf[2] = 0x27;  // Key code for '0'
                    break;
                case '1':
                    buf[2] = 0x1E;  // Key code for '1'
                    break;
                case '2':
                    buf[2] = 0x1F;  // Key code for '2'
                    break;
                case '3':
                    buf[2] = 0x20;  // Key code for '3'
                    break;
                case '4':
                    buf[2] = 0x21;  // Key code for '4'
                    break;
                case '5':
                    buf[2] = 0x22;  // Key code for '5'
                    break;
                case '6':
                    buf[2] = 0x23;  // Key code for '6'
                    break;
                case '7':
                    buf[2] = 0x24;  // Key code for '7'
                    break;
                case '8':
                    buf[2] = 0x25;  // Key code for '8'
                    break;
                case '9':
                    buf[2] = 0x26;  // Key code for '9'
                    break;
            }
            Serial.write(buf, 8);      // Send keypress
            buf[2] = 0;                // Release key
            Serial.write(buf, 8);      // Release key
        }
        // Handle special characters
        else {
            switch (c) {
                case '/':
                    pressKeyWithModifier(0x24, KEY_LEFT_SHIFT);  // Shift + 7 = /
                    break;
                case ':':
                    pressKeyWithModifier(0x37, KEY_LEFT_SHIFT);  // Shift + . = :
                    break;
                case '(':
                    pressKeyWithModifier(0x25, KEY_LEFT_SHIFT);  // Shift + 8 = (
                    break;
                case ')':
                    pressKeyWithModifier(0x26, KEY_LEFT_SHIFT);  // Shift + 9 = )
                    break;
                case '=':
                    pressKeyWithModifier(0x27, KEY_LEFT_SHIFT);  // Shift + 0 = =
                    break;
                case '{':
                    pressKeyWithModifier(0x34, KEY_RIGHT_ALT);   // AltGr + ' = {
                    break;
                case '}':
                    pressKeyWithModifier(0x27, KEY_RIGHT_ALT);   // AltGr + ç = }
                    break;
                case '#':
                    pressKeyWithModifier(0x20, KEY_RIGHT_ALT);   // AltGr + 3 = #
                    break;
                case '"':
                    pressKeyWithModifier(0x1F, KEY_LEFT_SHIFT);   // Shift + 2 = "
                    break;
                case ';':
                    pressKeyWithModifier(0x36, KEY_LEFT_SHIFT);  // Shift + , = ;
                    break;
                case '_':
                    pressKeyWithModifier(0x38, KEY_LEFT_SHIFT);  // Shift + , = ;
                    break;
                case '.':
                    buf[2] = 0x37;  // Direct mapping for . (period) key
                    Serial.write(buf, 8);   // Send keypress
                    buf[2] = 0;             // Release key
                    Serial.write(buf, 8);   // Release key
                    break;
                case ' ':
                    buf[2] = KEY_SPC;   // Spacebar
                    Serial.write(buf, 8);   // Send keypress
                    buf[2] = 0;             // Release key
                    Serial.write(buf, 8);   // Release key
                    break;
                case '\'':
                    buf[2] = 0x28;  // Direct mapping for ' key
                    Serial.write(buf, 8);   // Send keypress
                    buf[2] = 0;             // Release key
                    Serial.write(buf, 8);   // Release key
                    break;
                case ',':
                    buf[2] = 0x36;  // Direct mapping for , key
                    Serial.write(buf, 8);   // Send keypress
                    buf[2] = 0;             // Release key
                    Serial.write(buf, 8);   // Release key
                    break;
                case '-':
                    buf[2] = 0x38;  // Direct mapping for - key
                    Serial.write(buf, 8);   // Send keypress
                    buf[2] = 0;             // Release key
                    Serial.write(buf, 8);   // Release key

                case 'ñ':
                    buf[2] = 0x33;  // HID code for ñ key (Spanish layout)
                    Serial.write(buf, 8);
                    buf[2] = 0;
                    Serial.write(buf, 8);
                    break;

                case 'Ñ':
                    pressKeyWithModifier(0x33, KEY_LEFT_SHIFT);
                    break;
                    
                default:
                    buf[2] = KEY_NONE; // Default to no key pressed
                    break;
            }
        }
        str++; // Move to the next character
    }
}





void pressKeyWithModifier(uint8_t key, uint8_t modifier) {
  buf[0] = modifier; // Set the modifier
  buf[2] = key;      // Set the key
  Serial.write(buf, 8); // Send keypress
  buf[0] = 0;          // Release modifier
  buf[2] = 0;          // Release key
  Serial.write(buf, 8); // Release key
}

void CTRL(char *c) {
  buf[0] = KEY_LEFT_CTRL;  // Set Ctrl
  if (c[0] >= 'a' && c[0] <= 'z') {
    buf[2] = c[0] - 'a' + 4;  // Map a-z to HID codes
  } else if (c[0] >= 'A' && c[0] <= 'Z') {
    buf[0] = KEY_LEFT_SHIFT;  // Set shift for uppercase
    buf[2] = c[0] - 'A' + 4;  // Map A-Z to HID codes
  }

  Serial.write(buf, 8);       // Send keypress
  buf[0] = 0;  // Release modifier keys
  buf[2] = 0;  // Release key
  Serial.write(buf, 8);       // Release key
}

void ENTER() {
  buf[2] = KEY_ENTER;  // Enter key

  Serial.write(buf, 8);       // Send keypress
  buf[0] = 0;  // Release modifier keys
  buf[2] = 0;  // Release key
  Serial.write(buf, 8);       // Release key
}

