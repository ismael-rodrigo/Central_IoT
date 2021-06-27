extern char *disp_name[];


boolean Estado_disp  [qtdSAIDAS];
boolean EstadoAnt_disp  [qtdSAIDAS];
void pin_mode_input();
void read_i2c();  
extern byte buffer_disp[];
byte ANDRESS[] = {0x20,0X21,0X22};
extern bool modo_disp[];

//---------------VOID PIN_MODE_I2C-------------//

void pin_mode_input(uint8_t pino)
{
bitWrite(buffer_disp[pino/8],pino%8,1);  
}

//--------------BOOL READ_PIN_I2C------------//

bool read_i2c(uint8_t pino){ 
  byte lido;
  bool estado; 
  Wire.requestFrom(ANDRESS[pino/8],1);
 if(Wire.available()){    
  lido = Wire.read();
  }
  estado = bitRead(lido,pino%8);
  return estado;  
}


//-------VOID ATUALIZA_SAIDAS_I2C------------//

void Atualiza_saidas()
{
  for(byte i=0;i<sizeof(Estado_disp);i++)  
  {
    if(Estado_disp[i] != EstadoAnt_disp[i])
    {
          
      if(modo_disp[i]==1)
      {   
        inf = i;
        flag_timer = 1;     
        Estado_disp[i] = 0;
        EstadoAnt_disp[i] = Estado_disp[i]; 


       // sinal_display = 1;
       // lcd.clear();          
        //lcd.setCursor(0,0);
       // lcd.println(disp_name[i]);
       // lcd.setCursor(0,1);
       // lcd.println("PULSED");
        
                                  
      }
      else {
        bitWrite(buffer_disp[i/8],i%8,Estado_disp[i]);  
        Envia_register();          
        EstadoAnt_disp[i] = Estado_disp[i];

       // sinal_display = 1;
       // lcd.clear();          
       /// lcd.setCursor(0,0);
       // lcd.println(disp_name[i]);
       // lcd.setCursor(0,1);
        //if(Estado_disp[i])lcd.println("LIGADO");
       // else lcd.println("DESLIGADO");         
  


         
      }
      
    }    
      }
}
//---------------ENVIA VALOR DO BUFFER PARA O I2C-------------------//

 void Envia_register()
{
  
 for(byte t = 0 ; t<=qtdCI-1;t++)
  { 
  Wire.beginTransmission(ANDRESS[t]);
  Wire.write(buffer_disp[t]);
  Wire.endTransmission();
  }
}

//===================================FIM===========================//

    
