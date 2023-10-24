#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define ADC_CHANNEL1 0 // Channel 1번
#define ADC_CHANNEL2 1 // Channel 2번
#define SPI_SPEED 1000000 // 1Mhz
#define CS 1

int readADC(int channel){ // 지정된 SPI 채널에서 ADC 값을 읽습니다.
    unsigned char buffer[3]; // SPI 통신을 위한 버퍼 준비
    int adc = 0; // ADC 값을 반환하는 

    buffer[0] = 1; // 채널에 따른 시작 바이트 설정
    buffer[1] = (0b10+channel)<<6 | 1<<5;
    buffer[2] = 0;

    //printf("Send   : %x %x %x\n",buffer[0],buffer[1],buffer[2]);
    digitalWrite(CS, LOW); // CS/SHDN bit을 0으로 만들어야 값을 얻을 수 있다.
    wiringPiSPIDataRW(0, buffer, 3); // SPI 장치와 데이터 교환
    digitalWrite(CS, HIGH); // CS/SHDN bit : CHANNEL 바뀔 때 1로 setting
    //printf("Recieve: %x %x %x\n",buffer[0],buffer[1],buffer[2]);
    adc = ((buffer[1] & 0x0F) << 8) + buffer[2]; // 데이터 교환 후 ADC 값 버퍼 추출, 반환
    return adc;
}

int main(void){
    if(wiringPiSetup() == -1){ // wiringPiSetup을 사용해서 초기화
        printf("Failed to setup WiringPi\n");
        return 1;
    }

    if(wiringPiSPISetup(0, SPI_SPEED) == -1){ // wiringPiSPISetup 사용, SPI 채널 설정
        printf("Failed to setup wiringPiSPISetup\n");
        return 1;
    }
    pinMode(CS, OUTPUT);

    while(1){
        //int adcValue1 = readADC(ADC_CHANNEL1);
        //printf("ADC value 1 = %d\n", adcValue1);
        int adcValue2 = readADC(ADC_CHANNEL2); 
        printf("ADC value 2 = %d\n", adcValue2);
        delay(1000);
    }

    return 0;
}