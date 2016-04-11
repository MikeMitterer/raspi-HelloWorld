#include <cstdlib>
#include <iostream>

#include <rf24.hpp>

using namespace std;

// CE Pin, CSN Pin, SPI Speed
// Setup for GPIO 22 CE and CE0 CSN with SPI Speed @ 250KBPS
RF24 radio(RPI_V2_GPIO_P1_22, RPI_V2_GPIO_P1_24, RF24_250KBPS);

const Role role = Role::Server;

// Initialisierung der Clients funkt nur wenn
// die Adressen der Pipes in ReadingPipe.hpp definiert sind!
RF24Client client1(radio, pipe1, pipeWrite1);
RF24Client client2(radio, pipe2, pipeWrite2);

int main(int argc, char** argv) {
    // Refer to RF24.h or nRF24L01 DS for settings
    radio.begin();
    setupRadio(radio);
    resetReadingPipes(radio);
    delay(50);

    client1.enableReading();
    client2.enableReading();
    //radio.openReadingPipe(2, pipe2.getAddress());

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

    while (1) {
        // Start listening

        if (radio.available()) {
            MsgToSend dataReceived;

            while (radio.available()) {
                //len = radio.getDynamicPayloadSize();
                const uint16_t len = sizeof(MsgToSend);
                radio.read(&dataReceived, len);
                delay(20);

                printf("(%5i) Recv: size=%i Data=%i pipe=%i\n",
                       dataCounter, len, dataReceived.data, dataReceived.id);

                if (dataReceived.data == 111) {
                    digitalWrite(pin, 1);
                    delay(250);
                    digitalWrite(pin, 0);

                    client1.enableWriting();
                    //radio.openWritingPipe(pipeServer.getAddress());
                    delay(50);

                    radio.stopListening();
                    const bool result = radio.write(&dataReceived,len);
                    radio.startListening();

                    if(result == true) {
                        printf("%i bytes written to client 1!\n",len);
                    } else {
                        printf("Could not write to Client 1\n");
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

    return 0;
}
