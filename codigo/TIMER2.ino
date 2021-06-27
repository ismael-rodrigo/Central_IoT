void Timer(){

aux2++;
//aux3++;
aux4++;
aux5++;

if(flag_reset == 1){
if(aux5>400){
//  EEPROM.write(400,0XFF);
 // asm volatile ("  jmp 0");
}
}
else aux5 =  0;


//--------EFEITO PULSE-------------//
if(flag_timer){
  aux3++;
  if(aux3>30){     
      aux3 = 0;  
      flag_timer = 0;   
            
  }   
}
else aux3 = 0;

//-----VARREDURA DOS BUTT (50MS)----//

if(aux2>5)
{       
  flag_read_i2c = 1; 
  aux2=0;
}

//------------------------------------//


aux1++;
  if(aux1>500)
  {
    if(!flag_A)
    {
    flag_config = 0;
    controle = 0;
    tela = 0; 
    flag_A =1 ; 
    sinal_display = 1;   
    }
    else if(flag_A){
      aux1 = 520; 
    }

    
  }





//------FUNC BUTT ENTER SEGURADO-----//


if(!digitalRead(ativador))
{
  aux1a++;
  if(aux1a>200)
  {
   if(tela != 0 ) controle++;
   if(tela == 0 && controle == 0)
   {    
      flag_config = !flag_config;
      tela_config = 0;
   }

    teste = 1;
    aux1a = 0;
    sinal_display = 1;
      
  }
}
  else {
  aux1a = 0;
  }
}
//-----------FIM TIMER---------------//
