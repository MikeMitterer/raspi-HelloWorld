#include <cstdlib>
#include <iostream>
//#include <wiringPi.h>
#include <RF24/RF24.h>

using namespace std;

// Radio pipe addresses for the 2 nodes to communicate.
// Pipes 1-5 should share the first 32 bits.
// Only the least significant byte should be unique.
// You drop the 0x and LL.
// As stated the 0x indicates the value is a hex value and LL means type Long Long
const uint64_t pipes[3] = {0xF0F0F0F0E1LL,
                           0xF0F0F0F0D2LL,
                           0xF0F0F0F0F3LL
};

// CE Pin, CSN Pin, SPI Speed
// Setup for GPIO 22 CE and CE0 CSN with SPI Speed @ 250KBPS
RF24 radio(RPI_V2_GPIO_P1_22, RPI_V2_GPIO_P1_24, RF24_250KBPS);

// 0 - write to pipe 0, read from pipe 1
// 1 - write to pipe 1, read from pipe 0
const int role = 0;

struct MsgToSend {
    uint16_t id;
    uint16_t data;
};

int main(int argc, char** argv) {
    // Refer to RF24.h or nRF24L01 DS for settings
    radio.begin();
    //radio.enableDynamicPayloads();
    radio.setPALevel(RF24_PA_HIGH);
    radio.setRetries(15, 15);
    radio.setDataRate(RF24_250KBPS);
    radio.setPayloadSize(sizeof(MsgToSend));
    radio.setAutoAck(1);
    radio.setChannel(13);
    //radio.setCRCLength(RF24_CRC_16);

    if (role == 0) {
        radio.openWritingPipe(pipes[0]);
        radio.openReadingPipe(1, pipes[1]);
    }
    else {
        radio.openWritingPipe(pipes[1]);
        radio.openReadingPipe(1, pipes[0]);
    }
    delay(50);

    //
    // Start listening
    //
    radio.startListening();

    delay(50);

    //
    // Dump the configuration of the rf unit for debugging
    //
    radio.printDetails();

    printf("Output below : \n");

    // Pin 27 muss exportiert sein (gpio export 27 out)
    int pin = 27;

    // http://wiringpi.com/reference/setup/
    // wiringPiSetupSys uses Broadcom GPIO pin numbers directly with no re-mapping
//    if (wiringPiSetupSys() == -1) {
//        exit (1);
//    }
    pinMode(pin, OUTPUT);
//
    delay(50);

    radio.startListening();
    uint16_t dataCounter{};

    while (1) {
        // Start listening

        if (radio.available()) {
            MsgToSend dataReceived;

            while (radio.available()) {
                //len = radio.getDynamicPayloadSize();
                const uint16_t len = sizeof(MsgToSend);
                radio.read(&dataReceived, len);
                delay(20);

                printf("(%5i) Recv: size=%i Data=%i pipe=%i",dataCounter, len, dataReceived.data, dataReceived.id);

                if (dataReceived.data == 111) {
                    digitalWrite(pin, 1);
                    delay(250);
                    digitalWrite(pin, 0);
                }

                // Send back payload to sender
                radio.stopListening();

                // if pipe is 7, do not send it back
                radio.write(&dataReceived, len);
                printf("\t Send: size=%i Data=%i pipe:%i\n", len, dataReceived.data, dataReceived.id);
                dataReceived.data = 0;

                radio.startListening();

                dataCounter++;
            }

        }

        //delayMicroseconds(20);
        delay(500);
    }

    return 0;
}
