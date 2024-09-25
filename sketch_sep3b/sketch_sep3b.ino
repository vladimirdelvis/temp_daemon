#include <LiquidCrystal_I2C.h>

static unsigned long time = 0;
static unsigned long step = 0;
static char curr_temp[8];
static const char loading_chars[4] = { 45, 0, 124, 47 };
static const char custom_char[8] = { 0, 16, 8, 4, 2, 1, 0, 0 };
static const char waiting[] = "BAGLANTIBEKLENIYOR";
static LiquidCrystal_I2C lcd(0x27, 16, 2);

static void wait_msg(int char_delay = 150, int row_delay = 250) {
  lcd.setCursor(4, 0);
  for (unsigned int i = 0; i < 8; i++) {
    lcd.print(waiting[i]);
    delay(char_delay);
  }
  delay(row_delay);
  lcd.setCursor(3, 1);
  for (unsigned int i = 8; i < 18; i++) {
    lcd.print(waiting[i]);
    delay(char_delay);
  }
}

inline static void animate() {
  lcd.setCursor(1, 0);
  lcd.print(loading_chars[(step % 4)]);
  lcd.setCursor(14, 0);
  lcd.print(loading_chars[(step % 4)]);
  lcd.setCursor(1, 1);
  lcd.print(loading_chars[(step % 4)]);
  lcd.setCursor(14, 1);
  lcd.print(loading_chars[(step++ % 4)]);
}

static void prepare() {
  lcd.clear();
  lcd.print("CPU SICAKLIK:");
  lcd.setCursor(0, 1);
  lcd.print("GPU SICAKLIK:");
}

void setup() {
  Serial.begin(9600);
  lcd.backlight();
  lcd.init();
  lcd.createChar(0, custom_char);
  delay(600);

  if (Serial.available() >= 8) {
    prepare();
    time = millis();
    return;
  }
  step = 0;
  wait_msg(200,250);
  delay(400);
  while (1) {
    if (Serial.available() >= 8) {
      prepare();
      time = millis();
      return;
    }
    animate();
    delay(450);
  }
}

// SERIAL ILETISIM BASLAYINCA ARDUINO RESETLENIR VE RESETLENME SURESINCE GONDERILEN VERILER ILETILMEZ!
/* I2C LQCDisplay UNDEFINED FONKSIYONLAR
void printLeft();
void printRight();
void shiftIncrement();
void shiftDecrement();
*/

void loop() {
  if (Serial.available() >= 8) {
    memset(curr_temp, 0, 8);
    if (Serial.readBytes(curr_temp, 8) == 8) {
      time = millis();
      lcd.setCursor(13, 0);
      lcd.print(curr_temp);
      lcd.setCursor(13, 1);
      lcd.print(curr_temp + 4);
    }
  }
  else if(millis() - time >= 2000){
    lcd.clear();
    step = 0;
    wait_msg(0,0);
    delay(400);
    while(1){
      if(Serial.available() >= 8){
        prepare();
        return;
      }
      animate();
      delay(450);
    }
  }
}
