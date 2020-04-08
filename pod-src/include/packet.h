#ifndef __BLOOP_PACKET_H__
#define __BLOOP_PACKET_H__

#include "mbed.h"
#include "stdint.h"

#define FORMAT_HEADER(x) (x##|)

/* Badgerloop Packet! */
class BPacket {
    private:
        const int OFFSET = 2;
        BPacket::Type type;
        uint16_t size;
        char *data;
        char *payload;
        char header;
    public:
        enum Type {
            DATA    = 'd',
            CONTROL = 'c'
        };
        
        BPacket(BPacket::Type type, uint16_t size, char *data) {
            this->type = type;
            this->size = size;
            this->payload = malloc(size + OFFSET);   // Add space for the header!
            this->payload[0] = (char) this->type;
            this->payload[1] = '|';
            for (int i = OFFSET; i < (size + OFFSET - 1); i++) 
                this->payload[i] = data[i];
        }

        ~BPacket() {
            free(this->payload);
        }
        
        char *getPayload() {
            return payload;
        }

        BPacket::Type getType() {
            return type;
        }

        uint16_t getSize() {
            return size;
        }

        void dump(RawSerial *pc) {
            // Print contents of packet
            pc->printf("%s\n\r", this->getPayload());
        }
};

#endif
