// PWM variables
bool rising = true;

int pulseCounter = 0;

float dutyHighCeiling = 0.99;
float dutyHighFloor = 0.001;

  void playToneMicroseconds(float input)
  {
    if (input > 0 && isPlaying == false)
    {
      isPlaying = true;
        digitalWrite(buzzerPin, HIGH);
        digitalWrite(beatLed, HIGH); 
        delayMicroseconds((input * dutyHigh));
        digitalWrite(buzzerPin, LOW);
        digitalWrite(beatLed, LOW); 
        delayMicroseconds((input * dutyLow));
      isPlaying = false;
    }
  }

    // Simple high and low for signal generation
void playTone2(int input, int outputPin)
{
  if (input > 0 && isPlaying == false)
    {
      isPlaying = true;
    digitalWrite(beatLed, HIGH);
    digitalWrite(outputPin, HIGH); 
    delay(input * dutyHigh);
    digitalWrite(beatLed, LOW);
    digitalWrite(outputPin, LOW); 
    delay(input * dutyLow);   
    isPlaying = false;
    }  
}

  // Simple high and low for signal generation
void playTone(int input, int outputPin)
{
    digitalWrite(beatLed, HIGH);
    digitalWrite(outputPin, HIGH); 
    delay(input * (dutyHigh * 2));
    digitalWrite(beatLed, LOW);
    digitalWrite(outputPin, LOW); 
    delay(input * (dutyLow * 2));     
}
  
  // Use Potentiometer to set Duty Cycle
  void setDutyCycle(int potInput)
  {
    dutyHigh = mapIntRangetoFloatRange(potInput, 0, 699, dutyHighFloor, dutyHighCeiling);
    dutyLow = 1 - dutyHigh;
  }
  
  int SetSweepMode(int potValue)
  {
    if (potValue > 0 && potValue <= 233)
      return 0;
    else if (potValue > 233 && potValue <= 466)
      return 1;
    else if (potValue > 466 && potValue <= 700)
      return 2;
  }

  // When not using potentiometer to control Duty Cycle, sweep them.
  void DutyCycleSweep(int sweepMode, float rate)
  {
    if (dutyHigh == 0)
    {
      dutyHigh == 0.01;  
    }
    if (sweepMode == 0) // Triangle
    {
      // Start ramp up 
      if (dutyHigh <= dutyHighFloor)
        rising = true;
      if (rising == true)
        dutyHigh = dutyHigh + rate;
      if (dutyHigh >= dutyHighCeiling)
        rising = false;
      if (rising == false)
          dutyHigh = dutyHigh - rate; 
    }
  
    else if (sweepMode == 1) // Ramp Up
    {
      // Start ramp up
      if (dutyHigh < dutyHighCeiling)
        dutyHigh = dutyHigh + rate;
      if (dutyHigh >= dutyHighCeiling)
        dutyHigh = dutyHighFloor;
    }
  
    else if (sweepMode == 2) // Ramp Down
    {
      // if ramping down, continue ramping down   
      if (dutyHigh > dutyHighFloor)
        dutyHigh = dutyHigh - rate;
      if (dutyHigh <= dutyHighFloor)
        dutyHigh = dutyHighCeiling;
    }
    dutyLow = 1 - dutyHigh; // Set low part of duty cycle.
  }

  float SetSweepRate(int potValue)
  {
    float newValue = (potValue - 0) * (dutyHighCeiling - dutyHighFloor) / (700 - 0) + dutyHighFloor;
    return newValue;
  }

  // PWM pulse steps - For wobble mode
int getSteps(int inputValue)
{
  if (inputValue > 0 && inputValue < 50)
  {
    return 1;  
  } else if (inputValue >=51 && inputValue < 100)
  {
    return 2;
  } else if (inputValue >=101 && inputValue < 200)
  {
    return 3;
  } else if (inputValue >=201 && inputValue < 300)
  {
    return 4;
  }
  else if (inputValue >=301 && inputValue < 400)
  {
    return 8;
  }  
  else if (inputValue >=401 && inputValue < 500)
  {
    return 16;
  }
  else if (inputValue >=501 && inputValue < 700)
  {
    return 32;
  }
  else if (inputValue >=700)
  {
    return 64; 
  }
}
