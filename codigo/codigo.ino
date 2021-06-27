
/*    author : ISMAEL RODRIGO SOUSA BRASIL
 *     
 *    data : 18/05/21
 *    
 *    PROJETO : CONTROLADORA DE DISPOSITIVOS DIGITAL 
 *    POR ASSISTENTE VIRTUAL E CONTROLE EMISSOR IR.
 *    
 *    VERSAO: 3.5
 *    
 *    MCU : ESP8266 (ESPRESSIF)
 * 
 */

//------------LIBS AUXILIAR DO ESP8266----------------------//

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
#include <Espalexa.h>
#include <ArduinoOTA.h>

//--------------CONFIG WIFI-------------------------------//

const char* ssid = "Neto"; //nome da rede
const char* password = "030272neto"; //senha da rede

//------------CONFIG DAS SAIDAS DIGITAIS EXTERNAS--------//

#define qtdDISP 10      //QTD DE DISP VISIVEL NO DISPLAY
#define qtdCI 2         //qtd de CI usado
#define qtdSAIDAS  16   //qtd  de pinos OUTPUT DOS CI

//------MAPEAMENTO BUTTONS------------//

#define butt_a 12      // butt +
#define butt_b 13     // butt - 
#define ativador 14  // butt Enter

//----DEFINICOES DOS REGISTRADORES-----//

#define latchPin 2  // st_cp
#define data 3     // data
#define clk 4     // sh_cp

//------------FUNC EXTERNAS------------//

extern void atualiza_EEPROM();
extern void Timer();
extern void tela_ihm();
extern void Atualiza_saidas();
extern bool butt_incrementa();
extern bool butt_decrementa();
extern bool butt_enter() ;
extern void controle_butt();
void modo_pulse();
extern void Envia_register();
extern bool Estado_disp[];
extern bool EstadoAnt_disp[];
byte buffer_disp[((qtdSAIDAS-1)/8)+1];
extern bool termostato_disp[];
extern bool timer_disp[];
extern bool ligamento_disp[];
extern bool modo_disp[];
extern void salvar_dados();
extern void att_display();
//--------------TIMER------------------------//
bool flag_A; 
unsigned long temp_ant;
void Timer();
bool flag_display;
bool teste ;
volatile int aux1,aux2,aux3,aux4,aux5;
volatile byte aux1a;
void timer_x();

//-----------NAVEGACAO----------------------//

byte controle;
int tela;
int sub_tela;
bool flag_reset;

//----------CONFIG DISPLAY------------------//

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  

//-----------FUNC PULSE---------------------//

extern void pin_mode_input();
bool flag_pulse;
byte inf;
bool flag_timer;

//---------FUNC READ_I2C-------------------//

extern void read_i2c();
bool flag_read_i2c;
bool flag_reset2;
bool flag_config;
bool sinal_display;
int tela_config;
byte horas_timer;
bool flag_att_butts;

//-------FUNC ALEXA & VARIAVEIS ----------//

void firstLightChanged(uint8_t brightness);
void secondLightChanged(uint8_t brightness);
void thirdLightChanged(uint8_t brightness);
void fourthLightChanged(uint8_t brightness);
void fifthLightChanged(uint8_t brightness);
void sixLightChanged(uint8_t brightness);
void sevenLightChanged(uint8_t brightness);
void oitoLightChanged(uint8_t brightness);
void noveLightChanged(uint8_t brightness);

String Device_1_Name = "DEVICE1B";
String Device_2_Name = "DEVICE2B";
String Device_3_Name = "DEVICE3B";
String Device_4_Name = "DEVICE4B";
String Device_5_Name = "DEVICE5B";
String Device_6_Name = "DEVICE6B";
String Device_7_Name = "DEVICE7B";
String Device_8_Name = "DEVICE8B";
String Device_9_Name = "DEVICE9B";

Espalexa espalexa;

//**********************************************************************************************//
//====================================VOID SETUP================================================//
//**********************************************************************************************//
void setup() 
{
//-----------BUTT FRONTAL----------------//

pinMode(butt_a,INPUT_PULLUP);
pinMode(butt_b,INPUT_PULLUP);
pinMode(ativador,INPUT_PULLUP);  

//--------ZERA SAIDA DOS ATUADORES-------//  

Envia_register();
    
//-----------WIFI------------------------//  
  
Serial.begin(115200);
wifiMulti.addAP(ssid, password);    
while (wifiMulti.run() != WL_CONNECTED)
{       
 delay(250);
 Serial.print('.');
}
Serial.println("");
Serial.println("CONECTADO AO WIFI");

//-----------OTA-------------------------//
ArduinoOTA.setHostname("myesp8266");
ArduinoOTA.setPassword("12345678");
ArduinoOTA.onStart([](){ startOTA(); });
ArduinoOTA.onEnd([](){ endOTA(); });
ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) { progressOTA(progress,total); });
ArduinoOTA.onError([](ota_error_t error){ errorOTA(error); });
ArduinoOTA.begin();

Serial.println("Ready");
Serial.print("IP address: ");
Serial.println(WiFi.localIP());
  
//--------------CONECTA ALEXA-----------//
    
espalexa.addDevice(Device_1_Name, firstLightChanged); //simplest definition, default state off
espalexa.addDevice(Device_2_Name, secondLightChanged);
espalexa.addDevice(Device_3_Name, thirdLightChanged);
espalexa.addDevice(Device_4_Name, fourthLightChanged);
espalexa.addDevice(Device_5_Name, fifthLightChanged);
espalexa.addDevice(Device_6_Name, sixLightChanged);
espalexa.addDevice(Device_7_Name, sevenLightChanged);
espalexa.addDevice(Device_8_Name, oitoLightChanged);
espalexa.addDevice(Device_9_Name, noveLightChanged);  
espalexa.begin();

//----------CONFIG SAIDAS-------------//

for(byte i=qtdSAIDAS;i<qtdCI*8;i++){
 pin_mode_input(i);
}

for(byte i=0;i<qtdSAIDAS;i++) { 
 EstadoAnt_disp[i]=!Estado_disp[i];
}

//------INICIALIZA DISPLAY----------//    

lcd.init(); 
lcd.backlight();
sinal_display = 1;




}

//**********************************************************************************************//
//====================================FUNCOES OTA===============================================//
//**********************************************************************************************//

void startOTA()
{
   String type; 
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "flash";
    else 
     type = "filesystem";  
     Serial.println("Start updating " + type);    
}
void endOTA()
{
  Serial.println("\nEnd");
}
void progressOTA(unsigned int progress, unsigned int total)
{
  Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
}

void errorOTA(ota_error_t error)
{  
      Serial.printf("Error[%u]: ", error);
      
      if (error == OTA_AUTH_ERROR) 
        Serial.println("Auth Failed");
      else
      if (error == OTA_BEGIN_ERROR)
        Serial.println("Begin Failed");
      else 
      if (error == OTA_CONNECT_ERROR)
        Serial.println("Connect Failed");
      else
      if (error == OTA_RECEIVE_ERROR) 
        Serial.println("Receive Failed");
      else 
      if (error == OTA_END_ERROR)
        Serial.println("End Failed");
}

//**********************************************************************************************//
//====================================VOID LOOP=================================================//
//**********************************************************************************************//
void loop() 
{ 
//----------FUNC OTA-----------//  
ArduinoOTA.handle(); 

//---------ALEXA--------------//
 
espalexa.loop();   

//---------TIMER_X------------//

timer_x();

//-----ATUALIZA ATUADORES-----//

if(flag_read_i2c) 
{
  controle_butt();  
  Atualiza_saidas();  

  flag_read_i2c = 0;
}
//---------ATUALIZA DISPLAY----//

  
if(sinal_display)
{
  tela_ihm();
  sinal_display = 0;  
}




//----------FIM---------------//
}

//**********************************************************************************************//
//====================================FUNCAO TIMER_X============================================//
//**********************************************************************************************//

void timer_x() //executa o codigo a cada 10ms
{
  if ( (unsigned long) (millis() - temp_ant)>=10)
  {
    temp_ant = millis();
    Timer();
  }
}

//**********************************************************************************************//
//==========================================FIM=================================================//
//**********************************************************************************************//
