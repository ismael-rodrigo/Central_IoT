

//====================ALEXA FUNC===============//

void firstLightChanged(uint8_t brightness)
{

  if (brightness == 255)
    {
     Estado_disp[0] = 1;
    }
  else
  {
    Estado_disp[0] = 0;
  }
}

void secondLightChanged(uint8_t brightness)
{

  if (brightness == 255)
    {
    Estado_disp[1] = 1;
    }
  else
  {
   Estado_disp[1] = 0;
  }
}

void thirdLightChanged(uint8_t brightness)
{

  if (brightness == 255)
    {
    Estado_disp[2] = 1;
    }
  else
  {
   Estado_disp[2] = 0; 
  }
}

void fourthLightChanged(uint8_t brightness)
{

  if (brightness == 255)
    {
     Estado_disp[3] = 1;
    }
  else
  {
    Estado_disp[3] = 0;
  }
}

void fifthLightChanged(uint8_t brightness)
{

  if (brightness == 255)
    {
      Estado_disp[4] = 1;
    }
  else
  {
    Estado_disp[4] = 0;
  }
}
void sixLightChanged(uint8_t brightness)
{
 
  if (brightness == 255)
    {
    Estado_disp[5] = 1;
    }
  else
  {
    Estado_disp[5] = 0;
  }
}
void sevenLightChanged(uint8_t brightness)
{

  if (brightness == 255)
    {
    Estado_disp[6] = 1;
    }
  else
  {
    Estado_disp[6] = 0;
  }
}
void oitoLightChanged(uint8_t brightness)
{

  if (brightness == 255)
    {
//RESERVED
    }
  else
  {
//RESERVED
  }
}
void noveLightChanged(uint8_t brightness)
{
  //Control the device 
  if (brightness == 255)
    {
//RESERVED
    }
  else
  {
//RESERVED
  }
}
