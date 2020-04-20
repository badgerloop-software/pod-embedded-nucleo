#ifndef __BLOOP_PACKET_H__
#define __BLOOP_PACKET_H__

#include "mbed.h"
#include "data.h"
#include <stdlib.h>

#define FORMAT_HEADER(x) (x##|)

/* Badgerloop Packet! */
class BPacket {
    private:
        static const int MIN_DATA_PACKET_SIZE = 32;
        const int OFFSET = 2;
        uint16_t size;
        char *data;
        char *payload;
        char header;
        
        enum Type {
            DATA    = 'd',
            CONTROL = 'c'
        };
        
        void init(BPacket::Type type, int size);
        void attachHeader();
        void formatData(Data *data, char *out);

    public:
        
        BPacket::Type type;
        
        enum Command {
            BRAKE,
            UNBRAKE,
            ACK,
            ACKACK
        };
        

        BPacket(Data *data) {
            this->init(DATA, MIN_DATA_PACKET_SIZE + 2);
            char pData[MIN_DATA_PACKET_SIZE];
            formatData(data, pData);
            for (int i = OFFSET; i < this->size; i++) {
                this->payload[i] = pData[i];
            }
        }

        BPacket(BPacket::Command cmd) {
            this->init(CONTROL, 3);
            this->payload[2] = (char) cmd;
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

        void dump() {
            // Print contents of packet
            printf("%s\n\r", this->getPayload());
        }

};

#endif
