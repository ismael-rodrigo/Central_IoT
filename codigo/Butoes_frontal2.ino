extern char *disp_name[];


//***********************************************************//
//=============LER 0 BUTAO INCREMENTADOR=====================//
//***********************************************************//
bool flag_a;  
bool butt_incrementa()
{

  if (digitalRead(butt_a)==0 && flag_a == 0)flag_a = 1;
  if (digitalRead(butt_a)==1 && flag_a==1)
  {
      aux1 = 0;
      flag_A = 0;
    sinal_display  = 1;
    flag_a =0;
    return HIGH;
  }
  else return LOW;
    
}
//***********************************************************//
//=============LER 0 BUTAO DECREMENTADOR=====================//
//***********************************************************//
bool flag_b;  
bool butt_decrementa()
{

  

  if (digitalRead(butt_b)==0 && flag_b == 0)flag_b = 1;
  if (digitalRead(butt_b)==1 && flag_b==1)
  {
          aux1 = 0;
      flag_A = 0;
    sinal_display  = 1;
    flag_b =0;
    return HIGH;
  }
  else return LOW;
  




}

 //***********************************************************//
//================LER 0 BUTAO ENTER==========================//
//***********************************************************//

bool flag_atv;
bool butt_enter(){

  if(!digitalRead(ativador) && flag_atv == 0 )flag_atv =1;

  if(digitalRead(ativador) && flag_atv == 1 )
    {
     aux1 = 0;
     flag_A = 0;
     sinal_display  = 1;
     flag_atv=0;
     if(teste == 0){
      
      return HIGH;
     }
     if(teste==1){
       teste = 0;  
       return LOW;
     }
    }
  else 
  {
    return LOW ;
  } 

}
