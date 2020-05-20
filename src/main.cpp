#include <Arduino.h>
#include <ADC.h>

#define USB Serial

ADC *adc = new ADC();
ADC::Sync_result result1;
ADC::Sync_result result2;

IntervalTimer timer_sampling;
volatile boolean b_newSamples = false;
void sample(void);

void readConfig(void);
void sendConfig(void);
void startSampling(void);
void stopSampling(void);

void setup() {
  USB.begin(9600); // usb is always 12Mbit/s

  /*
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  */

  /*

  */
}

void loop() {

  uint16_t u16_newBytes = USB.available();
  if (u16_newBytes != 0) {
    for (uint16_t u16_nextByte = 0; u16_nextByte < u16_newBytes; u16_nextByte++) {
      // read input
    }
  }

  // this has to be faster than 10us
  if (b_newSamples) { 
    // prepare data bytes
    uint8_t message[10];

    // start byte
    Serial.write(0x00);

    // data
    Serial.write(result1.result_adc0);
    Serial.write(result1.result_adc0>>8);
    Serial.write(result1.result_adc1);
    Serial.write(result1.result_adc1>>8);
    Serial.write(result2.result_adc0);
    Serial.write(result2.result_adc0>>8);
    Serial.write(result2.result_adc1);
    Serial.write(result2.result_adc1>>8);

    // wait for next byte
    b_newSamples = false;
  }
}

void sample(void) {
  //result1 = adc->analogSyncRead(A0, A1);
  //result2 = adc->analogSyncRead(A2, A3);

  b_newSamples = true;
}

void readConfig(void) {
  // setup adcs if analog data has to be read

  // read resolution
  // get byte in answer message

  // adc 0
  adc->adc0->setAveraging(1);
  adc->adc0->setResolution(16);
  adc->adc0->setConversionSpeed(ADC_CONVERSION_SPEED::VERY_HIGH_SPEED);
  adc->adc0->setSamplingSpeed(ADC_SAMPLING_SPEED::VERY_HIGH_SPEED);
  // adc 1
  adc->adc1->setAveraging(1);
  adc->adc1->setResolution(16);
  adc->adc1->setConversionSpeed(ADC_CONVERSION_SPEED::VERY_HIGH_SPEED);
  adc->adc1->setSamplingSpeed(ADC_SAMPLING_SPEED::VERY_HIGH_SPEED);

  // setup analog pins
  if (false) {
    pinMode(A0, INPUT);
  }
  if (false) {
    pinMode(A1, INPUT);
  }
  if (false) {
    pinMode(A2, INPUT);
  }
  if (false) {
    pinMode(A3, INPUT);
  }
  if (false) {
    pinMode(A4, INPUT);
  }
  if (false) {
    pinMode(A5, INPUT);
  }
  if (false) {
    pinMode(A6, INPUT);
  }
  if (false) {
    pinMode(A7, INPUT);
  }
  if (false) {
    pinMode(A8, INPUT);
  }
  if (false) {
    pinMode(A9, INPUT);
  }
  if (false) {
    pinMode(A10, INPUT);
  }
  if (false) {
    pinMode(A11, INPUT);
  }
  if (false) {
    pinMode(A12, INPUT);
  }
  if (false) {
    pinMode(A13, INPUT);
  }



  // setup digital pins
}

void startSampling(void) {
  // call sampling every 10us
  // this is equal to the 100kHz and will, with 10 bytes full of data, saturate the USB connection
  timer_sampling.begin(sample, 10);
}

void stopSampling(void) {
  // stop the sampling
  timer_sampling.end();
}