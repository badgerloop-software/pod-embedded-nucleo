#include "data.h"
#include "packet.h"
#include <stdlib.h>

void BPacket::init(BPacket::Type type, int size) {
    this->type = type;
    this->size = size;
    this->payload = (char *) malloc(this->size * sizeof(char));
    BPacket::attachHeader();
}

void BPacket::attachHeader() {
    this->payload[0] = (char) this->type;
    this->payload[1] = '|';
}

/* Uses big endian! */
void BPacket::formatData(Data *data, char *out) {
    /* TODO, try to avoid that magic number :( */
    for (int i = 0; i < 16; i++) {
        if (i % 2) {
            out[i] = (char) data->boardTelem[i / 2] & 0x00ff;
        } else {
            out[i] = (char) data->boardTelem[i / 2] >> 8;
        }
    }

    for (int i = 0; i < 16; i++) {
        if (i % 2) {
            out[i + 16] = (char) data->pressures[i / 2] & 0x00ff;
        } else {
            out[i + 16] = (char) data->pressures[i / 2] >> 8;
        }
    }
}
