#include <wiringPi.h>
#include <stdio.h>
#include <cstdlib>

int main (void) {
    // Pin 27 muss exportiert sein (gpio export 27 out)
    int pin = 27;

    printf("*Raspberry Pi wiringPi blink test\n");

    // http://wiringpi.com/reference/setup/
    // wiringPiSetupSys uses Broadcom GPIO pin numbers directly with no re-mapping
    if (wiringPiSetupSys() == -1) {
        exit (1);
    }

    pinMode(pin, OUTPUT);

    for (int counter{0}; counter < 5; counter++){
        printf("LED On:\n");
        digitalWrite(pin, 1);
        delay(250);
        printf("LED Off %d\n",counter);
        digitalWrite(pin, 0);
        delay(250);
    }

    return 0;
}
