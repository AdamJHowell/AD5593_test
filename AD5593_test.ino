#include <Wire.h>

// AD5593 I2C address
#define AD5593_ADDR 0x10 // Change to the actual address if different

// AD5593 registers
#define AD5593_REG_CONFIG 0x00
#define AD5593_REG_ADC_SEQ 0x02
#define AD5593_REG_ADC_READ 0x06


void setup() 
{
  // Start the I2C bus
  Wire.begin( 35, 34 );

  // Start serial communication for debugging
  Serial.begin( 115200 );
  Serial.println( "Beginning setup()..." );

  // Configure the AD5593
  configureAD5593();
  Serial.println( "setup() complete!" );
}


void loop() 
{
  // Read the ADC value from channel 7
  uint16_t adcValue = readADCChannel( 7 );
  
  // Print the ADC value
  Serial.print( "ADC Channel 7 Value: " );
  Serial.println( adcValue );

  // Wait a bit before the next read
  delay( 1000 );
}


void configureAD5593() 
{
  // Set all channels to ADC mode (0xFF)
  Wire.beginTransmission( AD5593_ADDR );
  Wire.write( AD5593_REG_CONFIG );
  Wire.write( 0xFF );  // Set all channels to ADC mode
  Wire.endTransmission();

  // Enable the ADC sequence for channel 7
  Wire.beginTransmission( AD5593_ADDR );
  Wire.write( AD5593_REG_ADC_SEQ );
  Wire.write( 0x80 );  // Enable ADC on channel 7
  Wire.endTransmission();
}


uint16_t readADCChannel( uint8_t channel ) 
{
  uint16_t value = 0;

  // Start ADC conversion on the desired channel
  Wire.beginTransmission( AD5593_ADDR );
  Wire.write( AD5593_REG_ADC_READ );
  Wire.endTransmission();
  
  // Request 2 bytes from the ADC
  Wire.requestFrom( AD5593_ADDR, 2 );
  if ( Wire.available() == 2 ) {
    value = ( Wire.read() << 8 ) | Wire.read();
  }

  return value;
}
