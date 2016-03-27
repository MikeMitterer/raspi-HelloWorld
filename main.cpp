#include <cstdlib>
#include <iostream>
#include <RF24/RF24.h>

using namespace std;

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

// CE Pin, CSN Pin, SPI Speed
// Setup for GPIO 22 CE and CE0 CSN with SPI Speed @ 250KBPS
RF24 radio(RPI_V2_GPIO_P1_22, 0, RF24_250KBPS);


int main(int argc, char** argv)
{
    uint8_t len;

    // Refer to RF24.h or nRF24L01 DS for settings
    radio.begin();
    //radio.enableDynamicPayloads();
    //radio.setPALevel(RF24_PA_MAX);
    radio.setRetries(15,15);
    radio.setDataRate(RF24_250KBPS);
    radio.setPayloadSize(8);
    //radio.setAutoAck(1);
    radio.setChannel(13);
    //radio.setCRCLength(RF24_CRC_16);

    // Open 6 pipes for readings ( 5 plus pipe0, also can be used for reading )
    radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1,pipes[1]);

    //
    // Start listening
    //
    radio.startListening();

    //
    // Dump the configuration of the rf unit for debugging
    //
    radio.printDetails();

    printf("Output below : \n");
    delay(1);

    while(1)
    {
        char receivePayload[32];
        uint8_t pipe = 1;

        // Start listening
        radio.startListening();

        while ( radio.available(&pipe) )
        {
            len = radio.getDynamicPayloadSize();
            radio.read( receivePayload, len );

            // Display it on screen
            printf("Recv: size=%i payload=%s pipe=%i",len,receivePayload,pipe);

            // Send back payload to sender
            radio.stopListening();

            // if pipe is 7, do not send it back
            if ( pipe != 7 )
            {
                radio.write(receivePayload,len);
                receivePayload[len]=0;
                printf("\t Send: size=%i payload=%s pipe:%i\n",len,receivePayload,pipe);
            }
            else
            {
                printf("\n");
            }

            pipe++;

            // reset pipe to 0
            if ( pipe > 1 )
                pipe = 0;
        }

        delayMicroseconds(20);
    }

    return 0;
}
