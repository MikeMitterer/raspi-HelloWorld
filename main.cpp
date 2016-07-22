#include <cstdlib>
#include <iostream>

//namespace wiring{
//    #include "wiringPi.h"
//}

#include <rf24.hpp>
//#include <errno.h>

using namespace std;

// CE Pin, CSN Pin, SPI Speed
// Setup for GPIO 22 CE and CE0 CSN with SPI Speed @ 250KBPS
RF24 radio(RPI_V2_GPIO_P1_22, RPI_V2_GPIO_P1_24, RF24_250KBPS);

const Role role = Role::Server;

//const int INPUT = BCM2835_GPIO_FSEL_INPT;
uint8_t digitalRead(const uint8_t pin) { return bcm2835_gpio_lev(pin); }

int main(int argc, char** argv) {

    if(!bcm2835_init()) {
        printf("GPIO initialization failed!\n");
        return 1;
    }
    printf("RASPI is up and running\n");

    // Pin 18 / GPIO 24 muss exportiert sein (gpio export 24 in)
    uint8_t gpioButton = 24;
    bcm2835_gpio_fsel(gpioButton, BCM2835_GPIO_FSEL_INPT);
    //pinMode(gpioButton, BCM2835_GPIO_FSEL_INPT);
    //wiring::pinMode(gpioButton, INPUT);

    // Initialisierung der Clients funkt nur wenn
    // die Adressen der Pipes in ReadingPipe.hpp definiert sind!
    RF24Client client1(radio, channel1);
    RF24Client client2(radio, channel2);
//    RF24Client client2(radio, readPipe2, pipeWrite2);

    // Refer to RF24.h or nRF24L01 DS for settings
    radio.begin();
    setupRadio(radio);
    resetReadingPipes(radio);
    delay(50);

    client1.enableReading();
    client2.enableReading();
    //radio.openReadingPipe(channel1.getNumber(), channel1.getInAddress());

    delay(50);

    //radio.openWritingPipe(pipeServer.getAddress());
    delay(50);

    // Pin 27 muss exportiert sein (gpio export 27 out)
    int pin = 27;
    pinMode(pin, OUTPUT);

    //
    // Dump the configuration of the rf unit for debugging
    //
    radio.printDetails();
    printf("Output below : \n");

    radio.startListening();
    delay(50);

    uint16_t dataCounter{};

    int counter = 0;
    uint8_t btnState = 0;
    while (counter < 5) {
        // Start listening

        if (digitalRead(gpioButton) == LOW) {
            delay(50);
            if (digitalRead(gpioButton) == LOW) {
                printf("Button pressed!\n");
                counter++;
            }
        }

        if (radio.available()) {
            MsgToSend dataReceived;

            while (radio.available()) {
                //len = radio.getDynamicPayloadSize();
                const uint16_t len = sizeof(MsgToSend);
                radio.read(&dataReceived, len);
                delay(20);

                printf("(%5i) Recv: size=%i Data=%i pipe=%i\n",
                       dataCounter, len, dataReceived.data, dataReceived.id);

                if (dataReceived.data < 1000) {
                    digitalWrite(pin, 1);
                    delay(250);
                    digitalWrite(pin, 0);

                    uint8_t clientID = 99;
                    if(dataReceived.id == 1) {
                        client1.enableWriting();
                        clientID = 1;
                    } else {
                        client2.enableWriting();
                        clientID = 2;
                    }
                    //radio.openWritingPipe(channel1.getOutAddress());
                    delay(50);

                    radio.stopListening();
                    const bool result = radio.write(&dataReceived,len);
                    radio.startListening();

                    if(result == true) {
                        printf("%i bytes written to client %i!\n",len,clientID);
                    } else {
                        printf("Could not write to Client %i\n",clientID);
                    }

                }

//                // Send back payload to sender
//                radio.stopListening();
//
//                // if pipe is 7, do not send it back
//                radio.write(&dataReceived, len);
//                printf("\t Send: size=%i Data=%i pipe:%i\n", len, dataReceived.data, dataReceived.id);
//                dataReceived.data = 0;
//
//                radio.startListening();

                dataCounter++;
            }

        }

        //delayMicroseconds(20);
        delay(500);
    }

    bcm2835_close();
    return 0;
}
