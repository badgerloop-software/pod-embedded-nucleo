#ifndef __BLOOP_PACKET_H__
#define __BLOOP_PACKET_H__

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
    public:
        enum Type {
            DATA    = 'd',
            CONTROL = 'c'
        };
        
        BPacket::Type type;
        
        enum Command {
            BRAKE,
            UNBRAKE,
            ACK,
            ACKACK
        };

        BPacket(BPacket::Type type, uint16_t size, char *data) {
            this->type = type;
            this->size = size;
            this->payload = (char *) malloc(size * sizeof(char) + OFFSET);   // Add space for the header!
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

        /* Ensure we follow big endian! */
        static int formatData(uint16_t *voltAndCurrent, uint16_t *pressures, 
                char *out, int size) {
            if (size < MIN_DATA_PACKET_SIZE) {
                for (int i = 0; i < size; i++) {
                    out[i] = 1;  // Indicates an error
                }
                return -1;
            }
            /* TODO, try to avoid that magic number :( */
            for (int i = 0; i < 16; i++) {
                if (i % 2) {
                    out[i] = (char) voltAndCurrent[i] & 0x00ff;
                } else {
                    out[i] = (char) voltAndCurrent[i] >> 8;
                }
            }

            for (int i = 0; i < 16; i++) {
                if (i % 2) {
                    out[i + 16] = (char) pressures[i] & 0x00ff;
                } else {
                    out[i + 16] = (char) pressures[i] >> 8;
                }
            }

            return 32;
        }
};

#endif
