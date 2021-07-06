// I/0 pin numbers
const int potPin1 = 0;
const int potPin2 = 1;
const int button1Pin = 2;  // pushbutton 1 pin
const int button2Pin = 3;  // pushbutton 2 pin
const int buzzerPin = 9;
const int gateIn = A2;
const int cvIn = A5;
const int led = 7;

// PWM variables
int steps = 0;
bool rising = true;

float dutyHigh = 0.5;
float dutyLow = 1 - dutyHigh;
float dutyHighCeiling = 0.65;
float dutyHighFloor = 0.35;

// Mode stuff
int state = HIGH;      // the current state of the output pin
int reading;           // the current reading from the input pin
int previous = LOW;    // the previous reading from the input pin
int mode = 0; // The operating mode

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long time = 0;         // the last time the output pin was toggled
long debounce = 200;   // the debounce time, increase if the output flickers

// Expected voltage and note values for converting CV to tones
int C1_volts = 208;
float C1_Hz = 32.7;
int C1Sharp_volts = 226;
float C1Sharp_Hz = 34.65;
int D1_volts = 244;
float D1_Hz = 36.71;
int D1Sharp_volts = 261;
float D1Sharp_Hz = 38.89;
int E1_volts = 278;
float E1_Hz = 41.2;
int F1_volts = 296;
float F1_Hz = 43.65;
int F1Sharp_volts = 313;
float F1Sharp_Hz = 46.25;
int G1_volts = 330;
float G1_Hz = 49;
int G1Sharp_volts = 348;
float G1Sharp_Hz = 51.91;
int A1_volts = 366;
float A1_Hz = 55;
int A1Sharp_volts = 387;
float A1Sharp_Hz = 58.27;
int B1_volts = 401;
float B1_Hz = 61.74;
int C2_volts = 419;
float C2_Hz = 65.41;
int C2Sharp_volts = 436;
float C2Sharp_Hz = 69.3;
int D2_volts = 455;
float D2_Hz = 73.42;
int D2Sharp_volts = 473;
float D2Sharp_Hz = 77.78;
int E2_volts = 491;
float E2_Hz = 82.41;
int F2_volts = 509;
float F2_Hz = 87.31;
int F2Sharp_volts = 526;
float F2Sharp_Hz = 92.5;
int G2_volts = 543;
float G2_Hz = 98;
int G2Sharp_volts = 561;
float G2Sharp_Hz = 103.83;
int A2_volts = 579;
float A2_Hz = 110;
int A2Sharp_volts = 596;
float A2Sharp_Hz = 116.54;
int B2_volts = 614;
float B2_Hz = 123.47;
int C3_volts = 632;
float C3_Hz = 130.81;
int C3Sharp_volts = 649;
float C3Sharp_Hz = 138.59;
int D3_volts = 667;
float D3_Hz = 146.83;
int D3Sharp_volts = 684;
float D3Sharp_Hz = 155.56;
int E3_volts = 702;
float E3_Hz = 164.81;
int F3_volts = 720;
float F3_Hz = 174.61;
int F3Sharp_volts = 737;
float F3Sharp_Hz = 185;
int G3_volts = 755;
float G3_Hz = 196;
int G3Sharp_volts = 772;
float G3Sharp_Hz = 207.65;
int A3_volts = 790;
float A3_Hz = 220;
int A3Sharp_volts = 807;
float A3Sharp_Hz = 233.08;
int B3_volts = 825;
float B3_Hz = 246.94;
int C4_volts = 843;
float C4_Hz = 261.63;

void setup() {
  Serial.begin(9600); // open the serial port at 9600 bps:
  pinMode(buzzerPin, OUTPUT);
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
   // Note: potPin is analog and always input.
}

// Convert a single input voltage into the target tone, or glide up to the next note.
float voltageToNote(int inputVolts, int targetVolts, int nextHigherInputVolts, float targetHz, float nextHigherHz)
{
  int inputLowVariance = targetVolts - 3;
  int inputHighVariance = targetVolts + 3;
  // ex: if 208 > 206 and 208 < 210
  if (inputVolts > inputLowVariance && inputVolts < inputHighVariance)
  {
    return targetHz; // Return 32.7 hz
  } else if (inputVolts >= inputHighVariance - 2 && inputVolts <= nextHigherInputVolts + 2) // if input >= 210 & input <= 220 
  {
    return mapIntRangetoFloatRange(inputVolts, nextHigherInputVolts, inputHighVariance, targetHz, nextHigherHz);   
  } else
  {
    return 0;
  }
}

// Directly map a control voltage to a tone. This is most useful for handling glides.
// OR directly map a potentiometer value to a duty cycle. (int range to float range).
float mapIntRangetoFloatRange(int input, float inMin, float inMax, float outMin, float outMax)
{
    // Map voltage range 200 to 850 to 32 to 260
    float result = (input - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
    return result;
}

// Map all available voltages to notes or glides.
float convertCVtoTone(int input){
    
    // Low C
    // Pass in input, this note's target volts, the next note's target volts,
    // this note's Hz, the next note's Hz.
    float C_1 = voltageToNote(input, C1_volts, C1Sharp_volts, C1_Hz, C1Sharp_Hz);
    if (C_1 != 0)
       return C_1;

    // Low C#
    float C_Sharp_1 = voltageToNote(input, C1Sharp_volts, D1_volts, C1Sharp_Hz, D1_Hz);
    if (C_Sharp_1 != 0)
      return C_Sharp_1;

    // Low D
    float D_1 = voltageToNote(input, D1_volts, D1Sharp_volts, D1_Hz, D1Sharp_Hz);
    if (D_1 != 0)
      return D_1;

    // Low D#
    float D_Sharp_1 = voltageToNote(input, D1Sharp_volts, E1_volts, D1Sharp_Hz, E1_Hz);
    if (D_Sharp_1 != 0)
      return D_Sharp_1;  

    // Low E
    float E_1 = voltageToNote(input, E1_volts, F1_volts, E1_Hz, F1_Hz);
    if (E_1 != 0)
      return E_1;
      
    // Low F
    float F_1 = voltageToNote(input, F1_volts, F1Sharp_volts, F1_Hz, F1Sharp_Hz);
    if (F_1 != 0)
      return F_1;
    
    // Low F#
    float F_Sharp_1 = voltageToNote(input, F1Sharp_volts, E1_volts, F1Sharp_Hz, E1_Hz);
    if (F_Sharp_1 != 0)
      return F_Sharp_1;
    
    // Low G
    float G_1 = voltageToNote(input, G1_volts, G1Sharp_volts, G1_Hz, G1Sharp_Hz);
    if (G_1 != 0)
      return G_1;
      
    // Low G#
    float G_Sharp_1 = voltageToNote(input, G1Sharp_volts, A1_volts, G1Sharp_Hz, A1_Hz);
    if (G_Sharp_1 != 0)
      return G_Sharp_1;
       
    // Low A
    float A_1 = voltageToNote(input, A1_volts, A1Sharp_volts, A1_Hz, A1Sharp_Hz);
    if (A_1 != 0)
      return A_1;

    // Low A#
    float A_Sharp_1 = voltageToNote(input, A1Sharp_volts, B1_volts, A1Sharp_Hz, B1_Hz);
    if (A_Sharp_1 != 0)
      return A_Sharp_1;  
      
    // Low B
    float B_1 = voltageToNote(input, B1_volts, C2_volts, B1_Hz, C2_Hz);
    if (B_1 != 0)
      return B_1;
      
    // Middle C
    float C_2 = voltageToNote(input, C2_volts, C2Sharp_volts, C2_Hz, C2Sharp_Hz);
    if (C_2 != 0)
      return C_2;
       
    // Middle C#
    float C_Sharp_2 = voltageToNote(input, C2Sharp_volts, D2_volts, C2Sharp_Hz, D2_Hz);
    if (C_Sharp_2 != 0)
      return C_Sharp_2;  
      
    // Middle D
    float D_2 = voltageToNote(input, D2_volts, D2Sharp_volts, D2_Hz, D2Sharp_Hz);
    if (D_2 != 0)
      return D_2;
      
    // Middle D#
    float D_Sharp_2 = voltageToNote(input, D2Sharp_volts, E2_volts, D2Sharp_Hz, E2_Hz);
    if (D_Sharp_2 != 0)
      return D_Sharp_2;  
      
    // Middle E
    float E_2 = voltageToNote(input, E2_volts, F2_volts, E2_Hz, F2_Hz);
    if (E_2 != 0)
      return E_2;
       
    // Middle F
    float F_2 = voltageToNote(input, F2_volts, F2Sharp_volts, F2_Hz, F2Sharp_Hz);
    if (F_2 != 0)
      return F_2;
      
    // Middle F#
    float F_Sharp_2 = voltageToNote(input, F2Sharp_volts, G2_volts, F2Sharp_Hz, G2_Hz);
    if (F_Sharp_2 != 0)
      return F_Sharp_2;  
      
    // Middle G
    float G_2 = voltageToNote(input, G2_volts, G2Sharp_volts, G2_Hz, G2Sharp_Hz);
    if (G_2 != 0)
      return G_2;
      
    // Middle G#
    float G_Sharp_2 = voltageToNote(input, G2Sharp_volts, A2_volts, G2Sharp_Hz, A2_Hz);
    if (G_Sharp_2 != 0)
      return G_Sharp_2;  
      
    // Middle A
    float A_2 = voltageToNote(input, A2_volts, A2Sharp_volts, A2_Hz, A2Sharp_Hz);
    if (A_2 != 0)
      return A_2;
      
    // Middle A#
    float A_Sharp_2 = voltageToNote(input, A2Sharp_volts, B2_volts, A2Sharp_Hz, B2_Hz);
    if (A_Sharp_2 != 0)
      return A_Sharp_2;  
      
    // Middle B
    float B_2 = voltageToNote(input, B2_volts, C3_volts, B2_Hz, C3_Hz);
    if (B_2 != 0)
      return B_2;
      
    // High C
    float C_3 = voltageToNote(input, C3_volts, C3Sharp_volts, C3_Hz, C3Sharp_Hz);
    if (C_3 != 0)
      return C_3;
      
    // High C#
    float C_Sharp_3 = voltageToNote(input, C3Sharp_volts, D3_volts, C3Sharp_Hz, D3_Hz);
    if (C_Sharp_3 != 0)
      return C_Sharp_3;  
      
    // High D
    float D_3 = voltageToNote(input, D3_volts, D3Sharp_volts, D3_Hz, D3Sharp_Hz);
    if (D_3 != 0)
      return D_3;
      
    // High D#
    float D_Sharp_3 = voltageToNote(input, D3Sharp_volts, E3_volts, D3Sharp_Hz, E3_Hz);
    if (D_Sharp_3 != 0)
      return D_Sharp_3;
      
    // High E
    float E_3 = voltageToNote(input, E3_volts, F3_volts, E3_Hz, F3_Hz);
    if (E_3 != 0)
      return E_3;

    // High F
    float F_3 = voltageToNote(input, F3_volts, F3Sharp_volts, E3_Hz, F3Sharp_Hz);
    if (F_3 != 0)
      return F_3;
      
    // High F#
    float F_Sharp_3 = voltageToNote(input, F3Sharp_volts, G3_volts, F3Sharp_Hz, G3_Hz);
    if (F_Sharp_3 != 0)
      return F_Sharp_3;  
      
    // High G
    float G_3 = voltageToNote(input, G3_volts, G3Sharp_volts, G3_Hz, G3Sharp_Hz);
    if (G_3 != 0)
      return G_3;
      
    // High G#
    float G_Sharp_3 = voltageToNote(input, G3Sharp_volts, A3_volts, G3Sharp_Hz, A3_Hz);
    if (G_Sharp_3 != 0)
      return G_Sharp_3;

    // High A
    float A_3 = voltageToNote(input, A3_volts, A3Sharp_volts, A3_Hz, A3Sharp_Hz);
    if (A_3 != 0)
      return A_3;
      
    // High A#
    float A_Sharp_3 = voltageToNote(input, A3Sharp_volts, B3_volts, A3Sharp_Hz, B3_Hz);
    if (A_Sharp_3 != 0)
      return A_Sharp_3;
      
    // High B
    float B_3 = voltageToNote(input, B3_volts, C4_volts, B3_Hz, C4_Hz);
    if (B_3 != 0)
      return B_3;
      
    // HIGHEST C 
    float C_4 = voltageToNote(input, C4_volts, C4_volts, C4_Hz, C4_Hz);
    if (C_4 != 0)
      return C_4;
}

void playPulsesFromCV(float inputTone)
{
  // 1,000,000 microseconds in 1 second.
  // Hz is only 1000/s.
  
  float newToneInMicro = (1000000 / inputTone);
  int newMicroInt = round(newToneInMicro);

  playToneMicroseconds(newMicroInt);
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

// Simple high and low for signal generation
void playTone(int input)
{
    digitalWrite(led, HIGH);
    digitalWrite(buzzerPin, HIGH); 
    delay(input * (dutyHigh * 2));
    digitalWrite(led, LOW);
    digitalWrite(buzzerPin, LOW); 
    delay(input * (dutyLow * 2));     
}

void playToneMicroseconds(int input)
{
    digitalWrite(led, HIGH);
    digitalWrite(buzzerPin, HIGH); 
    delayMicroseconds(input * dutyHigh);
    digitalWrite(led, LOW);
    digitalWrite(buzzerPin, LOW); 
    delayMicroseconds(input * dutyLow);
}

// Use Potentiometer to set Duty Cycle
void setDutyCycle(int potInput){
  dutyHigh = mapIntRangetoFloatRange(potInput, 0, 695, dutyHighFloor, dutyHighCeiling);
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
  if (sweepMode == 0) // Sawtooth
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

  if (sweepMode == 1) // Ramp Up
  {
    // Start ramp up
    if (dutyHigh < dutyHighCeiling)
      dutyHigh = dutyHigh + rate;
    if (dutyHigh >= dutyHighCeiling)
      dutyHigh = dutyHighFloor;
  }

  if (sweepMode == 2) // Ramp Down
  {
    // if ramping down, continue ramping down   
    if (dutyHigh > dutyHighFloor)
      dutyHigh = dutyHigh - rate;
    if (dutyHigh <= dutyHighFloor)
      dutyHigh = dutyHighCeiling;
  }
  //Serial.println(dutyHigh);
  dutyLow = 1 - dutyHigh; // Set low part of duty cycle.
}

float SetSweepRate(int potValue)
{
  float newValue = (potValue - 0) * (0.05 - 0.001) / (700 - 0) + 0.001;
  return newValue;
}


// 
int getOperationMode()
{
    reading = digitalRead(button1Pin);

    if (reading == HIGH && previous == LOW && millis() - time > debounce) {
      if (state == HIGH)
        state = LOW;
      else
        state = HIGH;

      // Regardless of high or low, increment mode number.
      mode++;
    time = millis();    
  }

    previous = reading;

    if (mode > 2)
      mode = 0;
}

void DebugTheMode()
{
  Serial.print("Operation Mode: ");
  Serial.print(mode);
  Serial.print(" | Duty High: ");
  Serial.print(dutyHigh);
  Serial.print("Duty Low: ");
  Serial.print(dutyLow);
  Serial.println();
}


void loop() {
  int gateValue = analogRead(gateIn);
  int pot1Value = analogRead(potPin1);
  int pot2Value = analogRead(potPin2);
  int cvValue = analogRead(cvIn);
  
  getOperationMode();
  //DebugTheMode();
  if (mode == 0) // DUAL VOICE WITH POTENTIOMETER DRIVEN PWM
  {
    setDutyCycle(pot2Value);

    // PLAY
    if (gateValue > 1000)
    {  
      float note = convertCVtoTone(cvValue);
      //Serial.println(note);
      //Serial.println(cvValue);
      playPulsesFromCV(note);
    } else
    {
      noTone(buzzerPin);
    }
  }
  else if (mode == 1) // DUAL VOICE WITH PWM SWEEPS
  {
      // Sweep
      int SweepMode = SetSweepMode(pot1Value);
      float sweepRate = SetSweepRate(pot2Value);
      DutyCycleSweep(SweepMode, sweepRate);

    if (gateValue > 1000)
    {  

      float note = convertCVtoTone(cvValue);
      playPulsesFromCV(note);
    } else
    {
      noTone(buzzerPin);
    }
  }
  else if (mode == 2) // PWM filter wobble, short pulses
  {
    setDutyCycle(pot2Value);

    if (gateValue > 1000)
    {
      steps = getSteps(pot1Value);
      playTone(1000 / steps);
    }

  }
}
