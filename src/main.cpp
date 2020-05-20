#include <Arduino.h>
#include <ADC.h>


ADC *adc = new ADC();
ADC::Sync_result result1;
ADC::Sync_result result2;
IntervalTimer timer_measurement;
volatile boolean b_newSamples = false;
void sample(void);

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600); // usb is always 12Mbit/s

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

  timer_measurement.begin(sample, 10);

}

void loop() {
  if (b_newSamples) { 
    digitalWriteFast(LED_BUILTIN, HIGH);
    Serial.write(0x00);
    Serial.write(result1.result_adc0);
    Serial.write(result1.result_adc0>>8);
    Serial.write(result1.result_adc1);
    Serial.write(result1.result_adc1>>8);
    Serial.write(result2.result_adc0);
    Serial.write(result2.result_adc0>>8);
    Serial.write(result2.result_adc1);
    Serial.write(result2.result_adc1>>8);
    b_newSamples = false;
    digitalWriteFast(LED_BUILTIN, LOW);
  }
}

void sample(void) {
  result1 = adc->analogSyncRead(A0, A1);
  result2 = adc->analogSyncRead(A2, A3);

  b_newSamples = true;
}