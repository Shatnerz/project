int sizeOfInt;

void sendVector (int count, int *vector) {
  int i;
  void *ptr = &count;
  void *dptr = &vector[0];
  Serial.write((uint8_t*)ptr, sizeof(int));
  Serial.write((uint8_t*)dptr,count*sizeof(int));
}

int waitVector (int *vector) {
  int count = 0;
  int i, j;
  while (Serial.available() < sizeOfInt);
  for (i = 0; i < sizeOfInt; i++) {
    count += (Serial.read() << (i*8));
  }
  for (j = 0; j < count; j++) {
    vector[j] = 0;
    while (Serial.available() < sizeOfInt);
    for (i = 0; i < sizeOfInt; i++) vector[j] += (Serial.read() << (i*8));  
  }
  return count;
}

void setup() {
  const char *timestamp = __DATE__ ", " __TIME__;
  Serial.begin(115200);
  Serial.print("McGillPhysicsUgrad339"); /* This is a big magic number --- MATLAB waits for this on connect */
  Serial.write(sizeOfInt = sizeof(int)); /* different models of Arduino have different size integers */
  Serial.write(strlen(timestamp));
  Serial.print(timestamp);
  pinMode(13,OUTPUT);
}

void handlePWM(int *cmdVector) 
{
  int pin = cmdVector[1]; /* second number is which pin (3,5,6,9,10,11) */
  int value = cmdVector[2]; /* third number is the value */
  switch (pin) {
  case 3:
  case 5:
  case 6:
  case 9:
  case 10:
  case 11:
    analogWrite(pin,value);
    cmdVector[0] = 0; /* indicate success */
    sendVector(1, cmdVector);
    break;
  default:
    cmdVector[0] = 1; /* indicate failure (bad pin) */
    sendVector(1, cmdVector);
  }
}

void handleADC(int *cmdVector)
{
  int pin = cmdVector[1];
  if ((pin < 0) || (pin > 5)) {
    cmdVector[0] = 1; /* indicate failure (bad pin) */
    sendVector(1, cmdVector);
    return;
  }
  int value = analogRead(pin);
  cmdVector[0] = 0; /* success */
  cmdVector[1] = value;
  sendVector(2,cmdVector);
}

void handleUptime(int *cmdVector)
{
  unsigned long ms = micros(); /* millis() returns number of milliseconds since boot, 32 bit number */
  cmdVector[2] = (ms >> 16); /* upper 16 bits */
  cmdVector[1] = (ms & 0xffff); /* lower 16 bits */
  cmdVector[0] = 0; /* success */
  sendVector(3,cmdVector);
}

int halfPeriod = 500; /* used by blink ... in milliseconds */

void handleBlinking()
{
  unsigned long halfPeriods; /* the number of half-periods since boot up */
  halfPeriods = micros() / halfPeriod;
  if (halfPeriods % 2) { /* if halfPeriods is an odd number, */
    digitalWrite(13,HIGH); /* turn the LED on */
  } else {                /* As the great Brian Kernigan once said, "I can't tell if this is C with comments, or a new language with C as the comments" */
    digitalWrite(13,LOW); /* turn the LED off */
  }
}

void handleBlink(int *cmdVector)
{
  halfPeriod = cmdVector[1] / 2;
  cmdVector[0] = 0;
  cmdVector[1] = 2 * halfPeriod; /* return actual period */
  sendVector(2, cmdVector); /* return success */
}

void loop() {
  int cmdVector[16]; /* this vector will be used for communication */
  int count;
  if (Serial.available()) { /* If MATLAB has sent a command, go get it */
    count = waitVector(cmdVector);
    switch (cmdVector[0]) { /* the first element of vector is the command number */
    case 0: /* Echo ... returns the same vector */
      sendVector(count, cmdVector);
      break;
    case 1: /* PWM */
      handlePWM(cmdVector);
      break;
    case 2: /* get ADC reading, second number is ADC pin */
      handleADC(cmdVector);
      break;
    case 3: /* uptime */
     handleUptime(cmdVector);
     break;
    case 4: /* blink */
      handleBlink(cmdVector);
      break;
    } /* end switch(cmdVector[0]) */
  } /* end if(Serial.available()) */
  
  /* handle the blinking operation */
  handleBlinking();
}
