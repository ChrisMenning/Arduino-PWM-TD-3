// I/0 pin numbers
const int potPin1 = A0;
const int potPin2 = A1;
const int potPin3 = A2;

const int button1Pin = 2;  // pushbutton 1 pin
const int buzzerPin = 9;
const int gateIn = A5;
const int cvIn = A4;
const int syncIn = A3;
const int syncOut =  11;

const int RED_PIN = 4;
const int BLUE_PIN = 5;
const int GREEN_PIN = 6;

const int beatLed = 7;

float dutyHigh = 0.5;
float dutyLow = 1 - dutyHigh;

// Mode stuff
int state = HIGH;      // the current state of the output pin
int reading;           // the current reading from the input pin
int previous = LOW;    // the previous reading from the input pin
int mode = 0; // The operating mode

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long time = 0;         // the last time the output pin was toggled
long debounce = 200;   // the debounce time, increase if the output flickers

long noteTime = 0;

bool isPlaying = false;
int steps = 0;

// Directly map a control voltage to a tone. This is most useful for handling glides.
// OR directly map a potentiometer value to a duty cycle. (int range to float range).
float mapIntRangetoFloatRange(int input, float inMin, float inMax, float outMin, float outMax)
{
    // Map voltage range 200 to 850 to 32 to 260
    float result = (input - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
    return result;
}

void setup() {
  // Note: Analog pins are always input
  Serial.begin(9600); // open the serial port at 9600 bps:
  pinMode(buzzerPin, OUTPUT);
  pinMode(button1Pin, INPUT);

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(beatLed, OUTPUT);
}

float tuning (int potValue)
{
  //Serial.println(potValue);
  return mapIntRangetoFloatRange(potValue, 0, 695, 0.9, 1.2);
}

  
bool TimeIntervalDone(int input)
{
  static const unsigned long REFRESH_INTERVAL = input; // ms
  static unsigned long lastRefreshTime = 0;
  if(millis() - lastRefreshTime >= REFRESH_INTERVAL)
  {
    lastRefreshTime += REFRESH_INTERVAL;
    return 1;
  } 
  return 0;
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

    if (mode > 5)
      mode = 0;
}

void DebugTheMode()
{
  Serial.print("Operation Mode: ");
  Serial.print(mode);
  Serial.println();
}

void loop() {
  getOperationMode();

  if (mode == 0) // VOICE WITH POTENTIOMETER DRIVEN  
  {
    Red();
    DualVoiceSweep();
  }
  else if (mode == 1) // VOICE WITH PWM SWEEPS
  {
    Blue();
    DualVoicePotDrive();
  } else if (mode == 2) // UNVOICED POT-DRIVEN TONE
  {
    // Turn LED GREEN
    Green();
    UnvoicedPotDrive(); 

  } else if (mode == 3) // UNVOICED SWEEP
  {
    // Turn LED Yellow
    Yellow();
    UnvoicedSweep();
  } else if (mode ==4)
  {
    // Turn LED CYAN // PULSE-WOBBLE
    Cyan();
    int pot3Value = analogRead(potPin3);
    steps = getSteps(pot3Value);
    playTone(1000 / steps, buzzerPin);
  }
  else if(mode == 5) // SYNC
  {
    // Turn LED Purple
    Purple();
    Sync();
  }
}

void Sync(){
  int syncInValue = analogRead(syncIn);
  //Serial.println(syncInValue);
  
  if (syncInValue > 100)
  {
      steps = 50;
      playTone(1000 / steps, buzzerPin);
  } 
}

void DualVoicePotDrive()
{
    int pot1Value = analogRead(potPin1);
    int pot2Value = analogRead(potPin2);
    int gateValue = analogRead(gateIn);
    int cvValue = analogRead(cvIn);
  setDutyCycle(pot2Value);
  
    // PLAY
    if (gateValue > 1000)
    {  
      float note = convertCVtoTone(cvValue);

      float tunedNote = note * tuning(pot1Value);
      //Serial.print("Calculated tone: ");
      //Serial.println(note);
      playPulsesFromCV(tunedNote); // Use pot 1 for tuning      
      //tone(buzzerPin, note);
      
      noteTime = micros();
    } else
    {
      noTone(buzzerPin);
    }  
}

void DualVoiceSweep(){ 
  // Sweep
  int gateValue = analogRead(gateIn);
  int cvValue = analogRead(cvIn);
  int pot1Value = analogRead(potPin1);
  int pot2Value = analogRead(potPin2);
    int pot3Value = analogRead(potPin3);

  int SweepMode = SetSweepMode(pot2Value);
  float sweepRate = SetSweepRate(pot3Value);

 // String debugMsg = "";
 // debugMsg = "Gate: ";
 // debugMsg += gateValue;
 // debugMsg += " CV: ";
 // debugMsg += cvValue;
 // debugMsg += " Sync In: ";
 // debugMsg += syncInValue;
 // debugMsg += " Sync Out: ";
 // debugMsg += syncOutValue;
  //Serial.println(gateValue);
  
  DutyCycleSweep(SweepMode, sweepRate);
  if (gateValue > 1000)
  {  
    float note = convertCVtoTone(cvValue);
    playPulsesFromCV(note * tuning(pot1Value));
  } else
  {
    noTone(buzzerPin);
  }  
}

void UnvoicedPotDrive()
{
    int pot3Value = analogRead(potPin3);
  int pot2Value = analogRead(potPin2);

   setDutyCycle(pot3Value);
 
    float rate = mapIntRangetoFloatRange(pot2Value, 0, 698, 0.1, 60);
    playPulsesFromCV(rate);
}

void UnvoicedSweep()
{
  int pot3Value = analogRead(potPin3);
  int pot2Value = analogRead(potPin2);
    int SweepMode = 0;
    float sweepRate = SetSweepRate(pot3Value);
    DutyCycleSweep(SweepMode, sweepRate);

    float rate = mapIntRangetoFloatRange(pot2Value, 0, 698, 0.1, 32);
    playPulsesFromCV(rate);

}

void Blink()
{
  bool shouldBlink = TimeIntervalDone(60);
  if(shouldBlink)
  {
    // go high
  } else
  {
    // go low
  }
}
