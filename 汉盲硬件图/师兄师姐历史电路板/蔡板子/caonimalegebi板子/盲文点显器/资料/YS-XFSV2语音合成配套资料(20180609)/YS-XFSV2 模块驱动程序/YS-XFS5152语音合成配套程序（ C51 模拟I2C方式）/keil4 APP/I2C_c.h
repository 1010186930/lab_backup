
#ifndef __I2C_c__
#define __I2C_c__


void I2C_Start();
void I2C_Stop();
void Ack();
void NoAck();
bit Test_Ack();
void SendData(uint8_t buffer);
uint8_t I2CSendData(uint8_t s[],uint8_t n);

#endif