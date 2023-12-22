//ESSE PROJETO UTILIZA 1 ARDUINO MEGA,1 DISPLAY TFT 7735 160X128,1 DISPLAY LCD 20X4, 2 ALAVANCAS ON OFF,1 PUSHBUTTON,1 RELÉ 5v E CARTAO SD 2GB (qualquer um até 4GB)
// FOI UTILIZADO EXEMPLOS DE GERAR IMAGEM NO DISPLAY TFT


#include <SPI.h>
#include <SD.h>
#include <TFT.h>
#include <LiquidCrystal.h>
#define sd_cs  6
#define lcd_cs 10
#define dc     9
#define rst    8
int estadoA = 0;
int estadoB = 0;
int ultimoestadoA = 0;
int ultimoestadoB = 0;
const int botaoA = 3; // Pino do botão ou alavanca A
const int botaoB = 4; // Pino do botão ou alavanca B
const int botaoSelect = 2; // Pino do botão Select
const int rele = 5; // Pino do relé
int estadobotaoselect = 0;
int ultimoestadobotaoselect = 0;
int portaselecionada = 0;
bool PortaNotExecutada = false;
bool PortaandExecutada = false;
bool PortanandExecutada = false;
bool PortaorExecutada = false;
bool PortaxorExecutada = false;
bool PortanorExecutada = false;
bool PortaxnorExecutada = false;

LiquidCrystal lcd(12, 11 , 42, 40, 38, 36); // Pinos do LCD
TFT TFTscreen = TFT(lcd_cs, dc, rst);

// variavel que representa oque é pra desenhar
PImage logo;


void setup() {

  lcd.begin(20, 4); // Inicializa o LCD
  lcd.setCursor(0, 1);
  lcd.print("V Feira de ciencias"); // escreve no LCD
  delay(3000);
  lcd.clear();

  //Serial.begin(9600);
  
  pinMode(botaoA, INPUT_PULLUP); // Botão A com pull-up interno
  pinMode(botaoB, INPUT_PULLUP); // Botão B com pull-up interno
  pinMode(botaoSelect, INPUT_PULLUP); // Botão Select com pull-up interno
  pinMode(rele, OUTPUT);

  digitalWrite(rele, LOW); // Saída para o relé
  lcd.setCursor(1, 0);
  lcd.print("Simulador de");
  lcd.setCursor(1, 1);
  lcd.print("Portas Logicas");
  lcd.setCursor(1, 2);
  lcd.print("Eletronica Digital");
  delay(3000);
  lcd.clear(); // Limpa o LCD

  
  TFTscreen.begin();
  TFTscreen.background(255, 255, 255);
  TFTscreen.stroke(0, 0, 255);
  TFTscreen.println();
  TFTscreen.println(F("Arduino TFT Bitmap Example"));
  TFTscreen.stroke(0, 0, 0);
  TFTscreen.println(F("Open serial monitor"));
  TFTscreen.println(F("to run the sketch"));

  
  while (!Serial) {
   
  }

 
  TFTscreen.background(255, 255, 255);

  
  Serial.print(F("Initializing SD card..."));
  if (!SD.begin(sd_cs)) {
    Serial.println(F("failed!"));
    return;
  }
  Serial.println(F("OK!"));

  
  TFTscreen.begin();
  TFTscreen.background(255, 255, 255);


  //-----------------------------------------------------------------------------------
}

void loop() {
  // posiçao da imagem no st7735
  //int x = random(TFTscreen.width() - logo.width());
  //int y = random(TFTscreen.height() - logo.height());


  estadoA = digitalRead(botaoA);
  estadoB = digitalRead(botaoB);
  estadobotaoselect = digitalRead(botaoSelect);

  // Verifica se o botão Select foi acionado
  if (ultimoestadobotaoselect != ultimoestadobotaoselect) {
    delay(50); // delay entre ciclos dos nomes das portas logicas
    if (ultimoestadobotaoselect == LOW) {
      portaselecionada = (portaselecionada + 1) % 7; // Cicla entre as 7 portas lógicas
      lcd.clear();
    }

  }

  //da uma atualizada no display
  lcd.setCursor (5, 0);
  lcd.print ("");
  lcd.setCursor(5, 0);
  int output = 0;

  switch (portaselecionada) {
    case 0:
    lcd.print("Porta: NOT ");
        output = !estadoA; // RELÉ ACIONA SE FOR 0 NA ALAVANCA A
      
      if (PortaNotExecutada == false) {
       
        logo = TFTscreen.loadImage("not.bmp");
        if (!logo.isValid()) {
          Serial.println(F("error while loading not.bmp"));
        }
        // don't do anything if the image wasn't loaded correctly.
        if (logo.isValid() == false) {
          return;
        }

        Serial.println(F("drawing image"));

        // get a random location where to draw the image.
        // To avoid the image to be draw outside the screen,
        // take into account the image size.


        // draw the image to the screen
        TFTscreen.image(logo, 0, 0);
        lcd.print("");
  
        PortaNotExecutada = true;
      }

      break;

    case 1:
    lcd.print("Porta: AND");
      output = estadoA && estadoB; // RELÉ ACIONA SE FOR 1 1 NAS ALAVANCAS
    if (PortaandExecutada == false) {
      
      logo = TFTscreen.loadImage("and.bmp");
      if (!logo.isValid()) {
        Serial.println(F("error while loading and.bmp"));
      }
      // don't do anything if the image wasn't loaded correctly.
      if (logo.isValid() == false) {
        return;
      }

      Serial.println(F("drawing image"));

      // get a random location where to draw the image.
      // To avoid the image to be draw outside the screen,
      // take into account the image size.


      // draw the image to the screen
      TFTscreen.image(logo, 0, 0);
      PortaandExecutada = true;
    }
      break;
      lcd.print("");
    case 2:
    lcd.print("Porta: NAND");
      output = !estadoA && !estadoB || !estadoA && estadoB || estadoA && !estadoB ; // RELÉ ACIONA SE FOR  0 0 OU 0 1 OU 1 0 NAS ALAVANCAS
    if (PortanandExecutada == false) {
      
      logo = TFTscreen.loadImage("nand.bmp");
      if (!logo.isValid()) {
        Serial.println(F("error while loading nand.bmp"));
      }
      // don't do anything if the image wasn't loaded correctly.
      if (logo.isValid() == false) {
        return;
      }

      Serial.println(F("drawing image"));

      // get a random location where to draw the image.
      // To avoid the image to be draw outside the screen,
      // take into account the image size.

      // draw the image to the screen
      TFTscreen.image(logo, 0, 0);
      PortanandExecutada = true;
    }
      break;
      lcd.print("");
    case 3:
    lcd.print("Porta: OR");
      output = estadoA && estadoB || !estadoA && estadoB ||estadoA && !estadoB ; // RELÉ ACIONA SE FOR  1 1 OU 0 1 OU 1 0 NAS ALAVANCAS
    if (PortaorExecutada == false) {
      
      logo = TFTscreen.loadImage("or.bmp");
      if (!logo.isValid()) {
        Serial.println(F("error while loading or.bmp"));
      }
      // don't do anything if the image wasn't loaded correctly.
      if (logo.isValid() == false) {
        return;
      }

      Serial.println(F("drawing image"));

      // get a random location where to draw the image.
      // To avoid the image to be draw outside the screen,
      // take into account the image size.

      // draw the image to the screen
      TFTscreen.image(logo, 0, 0);
      PortaorExecutada = true;
    }
      break;
      lcd.print("");
    case 4:
    lcd.print("Porta: NOR");
      output = !estadoA && !estadoB; // RELÉ ACIONA SE FOR 1 1 NAS ALAVANCAS
     if (PortanorExecutada == false) {
      
      logo = TFTscreen.loadImage("nor.bmp");
      if (!logo.isValid()) {
        Serial.println(F("error while loading nor.bmp"));
      }
      // don't do anything if the image wasn't loaded correctly.
      if (logo.isValid() == false) {
        return;
      }

      Serial.println(F("drawing image"));

      // get a random location where to draw the image.
      // To avoid the image to be draw outside the screen,
      // take into account the image size.


      // draw the image to the screen
      TFTscreen.image(logo, 0, 0);
       PortanorExecutada = true;
     }
      break;
      lcd.print("");
    case 5:
      lcd.print("Porta: XOR");
      output = !estadoA && estadoB || estadoA && !estadoB; // RELÉ ACIONA SE FOR 1 0 OU 0 1 NAS ALAVANCAS
     if (PortaxorExecutada == false) {
    
      logo = TFTscreen.loadImage("xor.bmp");
      if (!logo.isValid()) {
        Serial.println(F("error while loading xor.bmp"));
      }
      // don't do anything if the image wasn't loaded correctly.
      if (logo.isValid() == false) {
        return;
      }

      Serial.println(F("drawing image"));

      // get a random location where to draw the image.
      // To avoid the image to be draw outside the screen,
      // take into account the image size.


      // draw the image to the screen
      TFTscreen.image(logo, 0, 0);
      PortaxorExecutada = true;
     }
      break;
      lcd.print("");
    case 6:
     lcd.print("Porta: XNOR");
      output = estadoA && estadoB || !estadoA && !estadoB; // RELÉ ACIONA SE FOR  1 1 OU 0 0 NAS ALAVANCAS
     if (PortaxnorExecutada == false) {
     
      logo = TFTscreen.loadImage("xnor.bmp");
      if (!logo.isValid()) {
        Serial.println(F("error while loading xnor.bmp"));
      }
      // don't do anything if the image wasn't loaded correctly.
      if (logo.isValid() == false) {
        return;
      }

      Serial.println(F("drawing image"));

      // get a random location where to draw the image.
      // To avoid the image to be draw outside the screen,
      // take into account the image size.


      // draw the image to the screen
      TFTscreen.image(logo, 0, 0);
      PortaxnorExecutada = true;
     }
     
      break;
      lcd.print("");
  }


  if (portaselecionada == 6) {
    PortaNotExecutada = false;
    PortaandExecutada = false;
    PortanandExecutada = false;
    PortaorExecutada = false;
    PortaxorExecutada = false;
    PortanorExecutada = false;
    PortaxnorExecutada = true;
  }
  else if (portaselecionada == 0) {
    PortaxnorExecutada = false;
  
  }

  // Atualiza o status de saída no LCD 20x4
  lcd.setCursor(9, 1);
  lcd.clear(); // Limpa o espaço anterior
  lcd.setCursor(5, 2);
  lcd.clear();
  lcd.print( "Output: ");
  lcd.print(output);

  // Acende ou apaga o LED com base na saída
  digitalWrite(rele, output);

  ultimoestadoA = estadoA;
  ultimoestadoB = estadoB;
  ultimoestadobotaoselect = estadobotaoselect;

}
