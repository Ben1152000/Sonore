
int cMajor[] = {36, 38, 39, 41, 43, 44, 46, 48, 50, 51, 53, 55, 56, 58, 60, 62, 63};
int scale[] = {37, 40, 42, 45, 47, 49, 52, 54, 57, 59, 61, 64, 66, 69, 71, 73, 76};

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);

  Serial.begin(9600);
  pinMode(13, OUTPUT);
  
  tone(13, getFreq(38)); //A3
  delay(30);
  noTone(13);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (readCapacitivePin(2) >= 8) {
    tone(13, getFreq(scale[0])); //A3
    delay(20);
    noTone(13);
    Serial.println(getFreq(36));
  }
  
  else if (readCapacitivePin(3) >= 8) {
    tone(13, getFreq(scale[1])); //B3
    delay(20);
    noTone(13);
    Serial.println(getFreq(38));
  }

  else if (readCapacitivePin(4) >= 8) {
    tone(13, getFreq(scale[2])); //C4
    delay(20);
    noTone(13);
    Serial.println(getFreq(39));
  }

  else if (readCapacitivePin(5) >= 8) {
    tone(13, getFreq(scale[3])); //D4
    delay(20);
    noTone(13);
    Serial.println(getFreq(41));
  }

  else if (readCapacitivePin(6) >= 8) {
    tone(13, getFreq(scale[4])); //E4
    delay(20);
    noTone(13);
    Serial.println(getFreq(43));
  }

  else if (readCapacitivePin(7) >= 8) {
    tone(13, getFreq(scale[5])); //F4
    delay(20);
    noTone(13);
    Serial.println(getFreq(44));
  }
  
  else if (readCapacitivePin(8) >= 8) {
    tone(13, getFreq(scale[6])); //G4
    delay(20);
    noTone(13);
    Serial.println(getFreq(46));
  }
  
  else if (readCapacitivePin(9) >= 8) {
    tone(13, getFreq(scale[7])); //A4
    delay(20);
    noTone(13);
    Serial.println(getFreq(48));
  }

  else if (readCapacitivePin(10) >= 8) {
    tone(13, getFreq(scale[8])); //B4
    delay(20);
    noTone(13);
    Serial.println(getFreq(50));
  }

  else if (readCapacitivePin(11) >= 8) {
    tone(13, getFreq(scale[9])); //C5
    delay(20);
    noTone(13);
    Serial.println(getFreq(51));
  }

  else if (readCapacitivePin(12) >= 8) {
    tone(13, getFreq(scale[10])); //D5
    delay(20);
    noTone(13);
    Serial.println(getFreq(53));
  }

  else if (readCapacitivePin(A0) >= 8) {
    tone(13, getFreq(scale[11])); //E5
    delay(20);
    noTone(13);
    Serial.println(getFreq(54));
  }
  
  else if (readCapacitivePin(A1) >= 8) {
    tone(13, getFreq(scale[12])); //F4
    delay(20);
    noTone(13);
    Serial.println(getFreq(56));
  }

  else if (readCapacitivePin(A2) >= 8) {
    tone(13, getFreq(scale[13])); //G4
    delay(20);
    noTone(13);
    Serial.println(getFreq(58));
  }

  else if (readCapacitivePin(A3) >= 8) {
    tone(13, getFreq(scale[14])); //A5
    delay(20);
    noTone(13);
    Serial.println(getFreq(60));
  }

  else if (readCapacitivePin(A4) >= 8) {
    tone(13, getFreq(scale[15])); //B5
    delay(20);
    noTone(13);
    Serial.println(getFreq(62));
  }

  else if (readCapacitivePin(A5) >= 8) {
    tone(13, getFreq(scale[16])); //C6
    delay(20);
    noTone(13);
    Serial.println(getFreq(63));
  }
}

uint8_t readCapacitivePin(int pinToMeasure) {
  // Variables used to translate from Arduino to AVR pin naming
  volatile uint8_t* port;
  volatile uint8_t* ddr;
  volatile uint8_t* pin;
  // Here we translate the input pin number from
  //  Arduino pin number to the AVR PORT, PIN, DDR,
  //  and which bit of those registers we care about.
  byte bitmask;
  port = portOutputRegister(digitalPinToPort(pinToMeasure));
  ddr = portModeRegister(digitalPinToPort(pinToMeasure));
  bitmask = digitalPinToBitMask(pinToMeasure);
  pin = portInputRegister(digitalPinToPort(pinToMeasure));
  // Discharge the pin first by setting it low and output
  *port &= ~(bitmask);
  *ddr  |= bitmask;
  delay(1);
  uint8_t SREG_old = SREG; //back up the AVR Status Register
  // Prevent the timer IRQ from disturbing our measurement
  noInterrupts();
  // Make the pin an input with the internal pull-up on
  *ddr &= ~(bitmask);
  *port |= bitmask;
  // Now see how long the pin to get pulled up. This manual unrolling of the loop
  // decreases the number of hardware cycles between each read of the pin,
  // thus increasing sensitivity.
  uint8_t cycles = 17;
  if (*pin & bitmask) { cycles =  0;}
  else if (*pin & bitmask) { cycles =  1;}
  else if (*pin & bitmask) { cycles =  2;}
  else if (*pin & bitmask) { cycles =  3;}
  else if (*pin & bitmask) { cycles =  4;}
  else if (*pin & bitmask) { cycles =  5;}
  else if (*pin & bitmask) { cycles =  6;}
  else if (*pin & bitmask) { cycles =  7;}
  else if (*pin & bitmask) { cycles =  8;}
  else if (*pin & bitmask) { cycles =  9;}
  else if (*pin & bitmask) { cycles = 10;}
  else if (*pin & bitmask) { cycles = 11;}
  else if (*pin & bitmask) { cycles = 12;}
  else if (*pin & bitmask) { cycles = 13;}
  else if (*pin & bitmask) { cycles = 14;}
  else if (*pin & bitmask) { cycles = 15;}
  else if (*pin & bitmask) { cycles = 16;}
  // End of timing-critical section; turn interrupts back on if they were on before, or leave them off if they were off before
  SREG = SREG_old;
  *port &= ~(bitmask);
  *ddr  |= bitmask;
  return cycles;
}

double getFreq(int noteNum) { // A0 is note 0
  return int( 55 * pow(2, noteNum/12.0 - 1) );
}

  
