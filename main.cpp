#include <wiringPi.h>
#include <stdio.h>
#include <cstdlib>

int main (void)
{
    int pin = 2;
    printf("*Raspberry Pi wiringPi blink test\n");

    if (wiringPiSetup() == -1) {
        exit (1);
    }

    int counter{0};

    pinMode(pin, OUTPUT);

//    for (;;){
        printf("LED On:\n");
        digitalWrite(pin, 1);
        delay(250);
        printf("LED Off %d\n",counter);
        digitalWrite(pin, 0);
        delay(250);

        counter++;
//    }

    return 0;
}
