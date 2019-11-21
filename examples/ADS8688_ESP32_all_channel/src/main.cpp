/*  ADS8688 library example
 *   
 *  PIN CONNECTION: 
 *  
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
 */

#include <Arduino.h>
#include <ADS8688.h>

uint8_t NmbOfADC = 2;                   // Number of ADCs in series. This can only be two as of right now (03/09/19)
ADS8688 bank = ADS8688(14);             // Instantiate ADS8688 with PIN 14 as default CS

uint16_t ADCBuffer1[8];                 // Buffer for ADC 1
uint16_t ADCBuffer2[8];                 // Buffer for ADC 2


 std::vector<float> FSR, EMG;

void setup() {
  delay(100);
  Serial.begin(9600);                   // start serial communication
  bank.setChannelSPD(0b11111111);       // bitwise channel selection 
  bank.setDaisyChainsNmb(NmbOfADC);     // Specify number of ADCs in series
  bank.setGlobalRange(R0);              // set range for all channels
  bank.autoRst();                       // reset auto sequence
  }

void loop() {
  bank.noOpDaisy();   // Trigger ADCs to sample analog ports

  Serial.println(" ADC 1  | ADC 2");

  // for (byte i=0;i<8;i++) {
  //   Serial.print(bank.I2V(ADCBuffer1[i],R0)); // print ADC1 Voltage
  //   Serial.print(" V | ");                    // print Volt label
  //   Serial.print(bank.I2V(ADCBuffer2[i],R0)); // print ADC2 Voltage
  //   Serial.println(" V");                     // print Volt label
  // }

  FSR = bank.ReturnADC_FSR();
  EMG = bank.ReturnADC_EMG();

for (size_t i = 0; i < 8; i++)
{
    Serial.print(FSR[i]); // print ADC1 Voltage
    Serial.print(" VFSR | ");
    if(i < 4){                    // print Volt label
      Serial.print(EMG[i]); // print ADC2 Voltage
      Serial.print(" VEMG");      
    }
    Serial.println();
}
  Serial.println("");                    // new line 
  delay(2000);                           // wait for 1000 milliseconds
  }
