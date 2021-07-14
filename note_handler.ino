// Expected voltage and note values for converting CV to tones
int C1_volts = 208;
float C1_Hz = 33.3;       //32.7;   
int C1Sharp_volts = 226;
float C1Sharp_Hz = 36;    //34.65;
int D1_volts = 244;
float D1_Hz =  38;        //36.71;
int D1Sharp_volts = 261;
float D1Sharp_Hz = 40.5;  //38.89;
int E1_volts = 278;
float E1_Hz = 43.1;       //41.2;
int F1_volts = 296;
float F1_Hz = 45.9;       //43.65;
int F1Sharp_volts = 313;
float F1Sharp_Hz = 48.7;  //46.25;
int G1_volts = 330;
float G1_Hz = 51.7;       //49;
int G1Sharp_volts = 348;
float G1Sharp_Hz = 54.8;  //51.91;
int A1_volts = 366;
float A1_Hz =  58.4;      //55;
int A1Sharp_volts = 387;
float A1Sharp_Hz = 62;    //58.27;
int B1_volts = 401;
float B1_Hz = 65.9;       //61.74;
int C2_volts = 419;
float C2_Hz = 70.1;       //65.41;
int C2Sharp_volts = 436;
float C2Sharp_Hz = 74.7;  //69.3;
int D2_volts = 455;
float D2_Hz = 79.2;       //73.42;
int D2Sharp_volts = 473;
float D2Sharp_Hz =  84.3; //77.78;
int E2_volts = 491;
float E2_Hz =  90;        //82.41;
int F2_volts = 509;
float F2_Hz =  95.9;      //87.31;
int F2Sharp_volts = 526;
float F2Sharp_Hz = 102;   //92.5;
int G2_volts = 543;
float G2_Hz = 108.8;      //98;
int G2Sharp_volts = 561;
float G2Sharp_Hz = 115.3; //103.83;
int A2_volts = 579;
float A2_Hz = 123.8;      //110;
int A2Sharp_volts = 596;
float A2Sharp_Hz = 131.8; //116.54;
int B2_volts = 614;
float B2_Hz =  140.2;     //123.47;
int C3_volts = 632;
float C3_Hz =  149.8;     //130.81;
int C3Sharp_volts = 649;
float C3Sharp_Hz =  160;  //138.59;
int D3_volts = 667;
float D3_Hz = 171;        // 146.83;
int D3Sharp_volts = 684;
float D3Sharp_Hz = 184;   // 155.56;
int E3_volts = 702;
float E3_Hz = 196.2;      // 164.81;
int F3_volts = 720;
float F3_Hz = 210.25;     //174.61;
int F3Sharp_volts = 737;
float F3Sharp_Hz =  225.5;//185;
int G3_volts = 755;
float G3_Hz =  242.1;     //196;
int G3Sharp_volts = 772;
float G3Sharp_Hz =  260;  //207.65;
int A3_volts = 790;
float A3_Hz =  280;       //220;
int A3Sharp_volts = 807;
float A3Sharp_Hz =  301;  //233.08;
int B3_volts = 825;
float B3_Hz = 323.77;     //246.94;
int C4_volts = 843;
float C4_Hz =  350.3;     //261.63;

// Calculate length of single pulse from Hz.
void playPulsesFromCV(float inputTone)
{
  // 1,000,000 microseconds in 1 second. Hz is only 1000/s.
  float newToneInMicro = (1000000 / inputTone );
  playToneMicroseconds(newToneInMicro);
  //Serial.println(inputTone);
  //playTone2(1000 / inputTone, buzzerPin);
}

// Map all available voltages to notes or glides.
float convertCVtoTone(int input){
    int variance = 9;
    if (input > C1_volts - variance && input < C1_volts + variance) // C
      return C1_Hz;  
    else if (input > C1_volts + variance && input < C1Sharp_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, C1_volts + variance, C1Sharp_volts - variance, C1_Hz, C1Sharp_volts);
    else if (input > C1Sharp_volts - variance && input < C1Sharp_volts + variance) // C#
      return C1Sharp_Hz;
    else if (input > C1Sharp_volts + variance && input < D1_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, C1Sharp_volts + variance, D1Sharp_volts - variance, C1Sharp_Hz, D1_volts);
    else if (input > D1_volts - variance && input < D1_volts + variance) // D
      return D1_Hz;
    else if (input > D1_volts + variance && input < D1Sharp_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, D1_volts + variance, D1Sharp_volts - variance, D1_Hz, D1Sharp_volts);
    else if (input > D1Sharp_volts - variance && input < D1Sharp_volts + variance) // D#
      return D1Sharp_Hz;
    else if (input > D1Sharp_volts + variance && input < D1_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, D1Sharp_volts + variance, E1_volts - variance, D1Sharp_Hz, E1_volts);
    else if (input > E1_volts - variance && input < E1_volts + variance)
      return E1_Hz;
    else if (input > E1_volts + variance && input < F1_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, E1_volts + variance, F1_volts - variance, E1_Hz, F1_volts);
    else if (input > F1_volts - variance && input < F1_volts + variance)
      return F1_Hz;
    else if (input > F1_volts + variance && input < F1Sharp_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, F1_volts + variance, F1Sharp_volts - variance, F1_Hz, F1Sharp_volts);
    else if (input > F1Sharp_volts - variance && input < F1Sharp_volts + variance)
      return F1Sharp_Hz;
     else if (input > F1Sharp_volts + variance && input < G1_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, F1Sharp_volts + variance, G1_volts - variance, F1Sharp_Hz, G1_volts);
    else if (input > G1_volts - variance && input < G1_volts + variance)
      return G1_Hz;
    else if (input > G1_volts + variance && input < G1Sharp_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, G1_volts + variance, G1Sharp_volts - variance, G1_Hz, G1Sharp_volts);
    else if (input > G1Sharp_volts - variance && input < G1Sharp_volts + variance)
      return G1Sharp_Hz;
     else if (input > G1Sharp_volts + variance && input < A1_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, G1Sharp_volts + variance, A1_volts - variance, G1Sharp_Hz, A1_volts);  
    else if (input > A1_volts - variance && input < A1_volts + variance)
      return A1_Hz;
    else if (input > A1_volts + variance && input < A1Sharp_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, A1_volts + variance, A1Sharp_volts - variance, A1_Hz, A1Sharp_volts);  
    else if (input > A1Sharp_volts - variance && input < A1Sharp_volts + variance)
      return A1Sharp_Hz;
    else if (input > A1Sharp_volts + variance && input < B1_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, A1Sharp_volts + variance, B1_volts - variance, A1Sharp_Hz, B1_volts);   
    else if (input > B1_volts - variance && input < B1_volts + variance)
      return B1_Hz;  
    else if (input > B1_volts + variance && input < C1_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, B1_volts + variance, C1_volts - variance, B1_Hz, C1_volts);                                         
    else if (input > C2_volts - variance && input < C2_volts + variance)
      return C2_Hz;
    else if (input > C2Sharp_volts - variance && input < C2Sharp_volts + variance) // C#
      return C2Sharp_Hz;
    else if (input > C2Sharp_volts + variance && input < D2_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, C2Sharp_volts + variance, D2Sharp_volts - variance, C2Sharp_Hz, D2_volts);
    else if (input > D2_volts - variance && input < D2_volts + variance) // D
      return D2_Hz;
    else if (input > D2_volts + variance && input < D2Sharp_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, D2_volts + variance, D2Sharp_volts - variance, D2_Hz, D2Sharp_volts);
    else if (input > D2Sharp_volts - variance && input < D2Sharp_volts + variance) // D#
      return D2Sharp_Hz;
    else if (input > D2Sharp_volts + variance && input < D2_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, D2Sharp_volts + variance, E2_volts - variance, D2Sharp_Hz, E2_volts);
    else if (input > E2_volts - variance && input < E2_volts + variance)
      return E2_Hz;
    else if (input > E2_volts + variance && input < F2_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, E2_volts + variance, F2_volts - variance, E2_Hz, F2_volts);
    else if (input > F2_volts - variance && input < F2_volts + variance)
      return F2_Hz;
    else if (input > F2_volts + variance && input < F2Sharp_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, F2_volts + variance, F2Sharp_volts - variance, F2_Hz, F2Sharp_volts);
    else if (input > F2Sharp_volts - variance && input < F2Sharp_volts + variance)
      return F2Sharp_Hz;
     else if (input > F2Sharp_volts + variance && input < G2_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, F2Sharp_volts + variance, G2_volts - variance, F2Sharp_Hz, G2_volts);
    else if (input > G2_volts - variance && input < G2_volts + variance)
      return G2_Hz;
    else if (input > G2_volts + variance && input < G2Sharp_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, G2_volts + variance, G2Sharp_volts - variance, G2_Hz, G2Sharp_volts);
    else if (input > G2Sharp_volts - variance && input < G2Sharp_volts + variance)
      return G2Sharp_Hz;
     else if (input > G2Sharp_volts + variance && input < A2_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, G2Sharp_volts + variance, A2_volts - variance, G2Sharp_Hz, A2_volts);  
    else if (input > A2_volts - variance && input < A2_volts + variance)
      return A2_Hz;
    else if (input > A2_volts + variance && input < A2Sharp_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, A2_volts + variance, A2Sharp_volts - variance, A2_Hz, A2Sharp_volts);  
    else if (input > A2Sharp_volts - variance && input < A2Sharp_volts + variance)
      return A2Sharp_Hz;
    else if (input > A2Sharp_volts + variance && input < B2_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, A2Sharp_volts + variance, B2_volts - variance, A2Sharp_Hz, B2_volts);   
    else if (input > B2_volts - variance && input < B2_volts + variance)
      return B2_Hz;  
    else if (input > B2_volts + variance && input < C2_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, B2_volts + variance, C3_volts - variance, B3_Hz, C3_volts);
    else if (input > C3_volts - variance && input < C3_volts + variance) // C
      return C3_Hz;  
    else if (input > C3Sharp_volts - variance && input < C3Sharp_volts + variance) // C#
      return C3Sharp_Hz;
    else if (input > C3Sharp_volts + variance && input < D3_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, C3Sharp_volts + variance, D3Sharp_volts - variance, C3Sharp_Hz, D3_volts);
    else if (input > D3_volts - variance && input < D3_volts + variance) // D
      return D3_Hz;
    else if (input > D3_volts + variance && input < D3Sharp_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, D3_volts + variance, D3Sharp_volts - variance, D3_Hz, D3Sharp_volts);
    else if (input > D3Sharp_volts - variance && input < D3Sharp_volts + variance) // D#
      return D3Sharp_Hz;
    else if (input > D3Sharp_volts + variance && input < D3_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, D3Sharp_volts + variance, E3_volts - variance, D3Sharp_Hz, E3_volts);
    else if (input > E3_volts - variance && input < E3_volts + variance)
      return E3_Hz;
    else if (input > E3_volts + variance && input < F3_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, E3_volts + variance, F3_volts - variance, E3_Hz, F3_volts);
    else if (input > F3_volts - variance && input < F3_volts + variance)
      return F3_Hz;
    else if (input > F3_volts + variance && input < F3Sharp_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, F3_volts + variance, F3Sharp_volts - variance, F3_Hz, F3Sharp_volts);
    else if (input > F3Sharp_volts - variance && input < F3Sharp_volts + variance)
      return F3Sharp_Hz;
     else if (input > F3Sharp_volts + variance && input < G3_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, F3Sharp_volts + variance, G3_volts - variance, F3Sharp_Hz, G3_volts);
    else if (input > G3_volts - variance && input < G3_volts + variance)
      return G3_Hz;
    else if (input > G3_volts + variance && input < G3Sharp_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, G3_volts + variance, G3Sharp_volts - variance, G3_Hz, G3Sharp_volts);
    else if (input > G3Sharp_volts - variance && input < G3Sharp_volts + variance)
      return G3Sharp_Hz;
    else if (input > G3Sharp_volts + variance && input < A3_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, G3Sharp_volts + variance, A3_volts - variance, G3Sharp_Hz, A3_volts);  
    else if (input > A3_volts - variance && input < A3_volts + variance)
      return A3_Hz;
    else if (input > A3_volts + variance && input < A3Sharp_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, A3_volts + variance, A3Sharp_volts - variance, A3_Hz, A3Sharp_volts);  
    else if (input > A3Sharp_volts - variance && input < A3Sharp_volts + variance)
      return A3Sharp_Hz;
    else if (input > A3Sharp_volts + variance && input < B3_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, A3Sharp_volts + variance, B3_volts - variance, A3Sharp_Hz, B3_volts);   
    else if (input > B3_volts - variance && input < B3_volts + variance)
      return B3_Hz;  
    else if (input > B3_volts + variance && input < C4_volts - variance)  // Glide
      return mapIntRangetoFloatRange(input, B3_volts + variance, C4_volts - variance, B3_Hz, C4_volts);
    else if (input > C4_volts - variance && input < C4_volts + variance) // C
      return C4_Hz;  
        
    else return 0;
}
