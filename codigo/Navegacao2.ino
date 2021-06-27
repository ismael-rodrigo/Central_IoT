
char *disp_name[] = 
{
"disp1",
"disp2",
"disp3",
"disp4",
"disp5",
"disp6",
"disp7",
"disp8",
"disp9",
"disp10",
"disp11",
"disp12",
"disp13",
"disp14"
};



 bool termostato_disp[qtdSAIDAS];
 bool timer_disp[qtdSAIDAS];
 bool ligamento_disp[qtdSAIDAS];
 bool modo_disp[qtdSAIDAS];




bool flag_apresentacao;
byte temperatura_termostato = 14;
byte umidade_termostato = 20;
byte temp,umid;

bool flag_tst;

void controle_butt()
{

if(controle == 0 && !flag_config)
{

if(butt_incrementa()) tela++;
if(butt_decrementa()) tela--;
if(tela!=0){
if(butt_enter()) Estado_disp[tela-1] = !Estado_disp[tela-1];
}
}
if(tela==0 && !flag_config){
if(butt_enter())controle++;  
}


if(flag_config ){

  
if(butt_decrementa()) tela_config--;
if(butt_incrementa()) tela_config++;


if(tela_config>4)tela_config =0;
if(tela_config<0)tela_config =4;

if(tela_config==0)
{
if(butt_enter())horas_timer+=30;
if(horas_timer>180)horas_timer = 30;


}

if(tela_config == 1){
  
}
if(tela_config == 2){
  
}
if(tela_config == 3){
  
}
if(tela_config == 4){
  
}


}


if(controle ==1 ){

  if(tela==0)
  {
    if(butt_incrementa())temperatura_termostato+=2;
    if(temperatura_termostato>38)temperatura_termostato = 14;
    if(butt_decrementa())umidade_termostato+=20;
    if(umidade_termostato>100)umidade_termostato = 20;
  }
  else{
    if(butt_incrementa())sub_tela++;
    if(butt_decrementa())sub_tela--;
    if(sub_tela>3)sub_tela =0;
    if(sub_tela<0)sub_tela =3;
    
    if(butt_enter())
    {
      if(sub_tela == 0)timer_disp[tela-1]=!timer_disp[tela-1];
      if(sub_tela == 1)termostato_disp[tela-1]=!termostato_disp[tela-1];
      if(sub_tela == 2)ligamento_disp[tela-1]=!ligamento_disp[tela-1];
      if(sub_tela == 3)modo_disp[tela-1]=!modo_disp[tela-1];
    }
  
  }   
  }
}

void tela_ihm(){
lcd.clear();
if(controle>1)controle = 0;
  


if(flag_config){

switch(tela_config){
 
case 0:
lcd.setCursor(0,0);
lcd.print("TEMPORIZADOR"); 
lcd.setCursor(0,1);
lcd.print(horas_timer);
break;
case 1:
lcd.setCursor(0,0);
lcd.print("LIGAMENTO-PROGM"); 
lcd.setCursor(0,1);

break;
case 2:
lcd.setCursor(0,0);
lcd.print("TELA 3");
lcd.setCursor(0,1);
break;
case 3:
lcd.setCursor(0,0);
lcd.print("TELA 4");
lcd.setCursor(0,1);
break;
case 4:
lcd.setCursor(0,0);
lcd.print("TELA 5"); 
lcd.setCursor(0,1);
break;
}






}
if(!flag_config){
  
if(controle == 0)
{
flag_apresentacao = 0;
 
if(tela>qtdDISP)tela = 0;  
if(tela<0)tela = qtdDISP; 


if(tela==0){ 
lcd.setCursor(0,0);
lcd.print("TEMPERATURA:");
lcd.print(temp);
lcd.print(" C");
lcd.setCursor(0,1);
lcd.print("UMIDADE :");
lcd.print(umid);
lcd.print(" %");
}

//==================TELA-DISP==================//
if(tela!=0){
  
lcd.setCursor(0,0);  
lcd.print(disp_name[tela-1]);
lcd.setCursor(0,1);
if(modo_disp[tela-1]==0){
  if(Estado_disp[tela-1])lcd.print("LIGADO");
  else lcd.print("DESLIGADO");
}
else{
   lcd.print("  ON/OFF  ");  
}
}

}   

//============================================//


//---------------SUB-MENU----------------//  
if(controle==1)
{

//------SUB-MENU TEM/UMID -------//
if(tela==0)
{  
lcd.setCursor(0,0);
lcd.print("TEMP LIMIT:");
lcd.print(temperatura_termostato);
lcd.print(" C");

lcd.setCursor(0,1);
lcd.print("UMID LIMIT:");
lcd.print(umidade_termostato);
lcd.print(" %");
}


//------SUB-MENU DISP[X] ----------------------------------//
else if(tela!=0)
{
//------------SUB-MENU-----------//
//----------APRESENTACAO--------//  
if(!flag_apresentacao){
lcd.clear();  
lcd.setCursor(0,0);
lcd.print("CONFIGURACAO");
lcd.setCursor(0,1);
lcd.print(disp_name[tela-1]);
delay(1000);
flag_apresentacao = 1;
sub_tela = 0;
sinal_display = 1;
}
else{

switch(sub_tela)
{
case 0:  
lcd.setCursor(0,0);
lcd.print("TIMER");
lcd.setCursor(0,1);
if(timer_disp[tela-1])lcd.print("ATIVADO");
else lcd.print("DESATIVO");
break;

case 1:
lcd.setCursor(0,0);
lcd.print("TERMOSTATO");
lcd.setCursor(0,1);
if(termostato_disp[tela-1])lcd.print("ON");
else lcd.print("OFF");
break;

case 2:
lcd.setCursor(0,0);
lcd.print("LIGAMENTO-PROGM.");
lcd.setCursor(0,1);
if(ligamento_disp[tela-1])lcd.print("ON");
else lcd.print("OFF");
break;

case 3:
lcd.setCursor(0,0);
lcd.print("MODO-OPERACAO");
lcd.setCursor(0,1);
if(modo_disp[tela-1])lcd.print("PULSE");
else lcd.print("NORMAL");
break;

}
}
}   
}
}
}



  
  
