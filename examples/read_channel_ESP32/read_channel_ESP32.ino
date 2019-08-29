/*  ADS8688 library example
 *   
 *  PIN CONNECTION: 
 *  REFSEL: GND (enable internal 4.096V reference)
 *  RST/PD: +5V/+3.3V
 *  AVDD:   +5V/+3.3V
 *  DVDD:   +5V/+3.3V
 *  REFIO:  NC
 *  ALARM:  NC
 *  DAISY:  NC
 * 
 *  ESP32
 *  DAC1:   pin A1
 *  CS:     pin 14
 *  MOSI:   pin MO
 *  MISO:   pin MI
 *  SCK:    pin SCK
 * 
 * This code will increase the voltage on DAC1 from 0 - 3.3 Volt.
 * Connect the ADC channel 0 on ADS8688 to DAC1 (A1) on the ESP32
 */

#include <Arduino.h>
#include <ADS8688.h>

uint16_t val;
float adc_voltage;
ADS8688 bank = ADS8688(14);         // Instantiate ADS8688 with PIN 14 as default CS

void setup() {
  Serial.begin(9600);               // start serial communication
  bank.setChannelSPD(0b00000001);   // enable channel 0, power-down the others
  bank.setChannelRange(0,R1);       // set all channel range to +- 1.25*Vref
  bank.autoRst();                   // reset auto sequence  
  }

void loop() {

  for (size_t i = 0; i < 255; i++)
  {
    // Set DAC voltage 
    dacWrite(DAC1, i);
    Serial.print("DAC voltage: ");
    Serial.print((float)i/255. * 3.3);
    // Read ADC voltage 
    Serial.print("  ADC voltage: ");
    val = bank.noOp();       // trigger sampling
    adc_voltage = bank.I2V(val,R1);
    Serial.print(adc_voltage);
    Serial.print("  Difference: ");
    delay(2);
    Serial.println(((float)i/255. * 3.3) - adc_voltage,5);
    delay(4);
    
  }
  delay(2000);

  }
