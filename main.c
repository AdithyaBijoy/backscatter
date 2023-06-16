/**
 * Tobias Mages & Wenqing Yan
 * Backscatter PIO
 * 02-March-2023
 */

#include <stdio.h>
#include "math.h"
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "backscatter.pio.h"
#include "packet_generation.h"

#define TX_DURATION 250 // send a packet every 250ms (when changing baud-rate, ensure that the TX delay is larger than the transmission time)
#define RECEIVER 1352 // define the receiver board either 2500 or 1352
#define PIN_TX1 6
#define PIN_TX2 27

int main() {
    PIO pio = pio0;
    uint sm = 0;
    uint offset = pio_add_program(pio, &backscatter_program);
    backscatter_program_init(pio, sm, offset, PIN_TX1); // two antenna setup
    //backscatter_program_init(pio, sm, offset, PIN_TX1); // one antenna setup

    static uint8_t message[buffer_size(PAYLOADSIZE+2, HEADER_LEN)*4] = {0};  // include 10 header bytes
    static uint32_t buffer[buffer_size(PAYLOADSIZE, HEADER_LEN)] = {0}; // initialize the buffer
    static uint8_t seq = 0;
    uint8_t *header_tmplate = packet_hdr_template(RECEIVER);
    // uint8_t tx_payload_buffer[PAYLOADSIZE];

    while (true) {
        /* generate new data */
        // generate_data(tx_payload_buffer, PAYLOADSIZE, true);
        uint8_t tx_payload_buffer[]= {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e};


        /* add header (10 byte) to packet */
        add_header(&message[0], seq, header_tmplate);
        /* add payload to packet */
        memcpy(&message[HEADER_LEN], tx_payload_buffer, PAYLOADSIZE);

        /* casting for 32-bit fifo */
        for (uint8_t i=0; i < buffer_size(PAYLOADSIZE, HEADER_LEN); i++) {
            buffer[i] = ((uint32_t) message[4*i+3]) | (((uint32_t) message[4*i+2]) << 8) | (((uint32_t) message[4*i+1]) << 16) | (((uint32_t)message[4*i]) << 24);
        }
        // the first 24 elements are for the sync word for the sync word 
        int i=0;
        // The sync word passed for the first time
        buffer[i++]=0b11001100110000111100001111001100;
        buffer[i++]=0b11000011001111000011001100110011;
        // The sync word passed for the second time
        buffer[i++]=0b11001100110000111100001111001100;
        buffer[i++]=0b11000011001111000011001100110011;
        // The inverted sync word
        buffer[i++]=0b00110011001111000011110000110011;
        buffer[i++]=0b00111100110000111100110011001100;
        // The payload
        buffer[i++]=0b00000000000000000000000000000000;
        buffer[i++]=0b00000000000000000000000000000000;
        buffer[i++]=0b00000000000000000000000000000000;
        buffer[i++]=0b00000000000000000000000000000000;
        buffer[i++]=0b00000000000000000000000000000000;
        buffer[i++]=0b00000000000000000000000000000000;
        buffer[i++]=0b00000000000000000000000000000000;
        buffer[i++]=0b00000000000000000000000000000000;
        /* put the data to FIFO */
        backscatter_send(pio,sm,buffer,i);
        seq++;
        sleep_ms(TX_DURATION);
    }
}
