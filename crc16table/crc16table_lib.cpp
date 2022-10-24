#include <fstream>
#include <stdint.h>

void MakeCRC16Table(uint16_t *crctable);
uint16_t GetCRC16(char *buf, int len, uint16_t *crctable);
uint16_t GetCRC16FromFile(char *filename, uint16_t *crctable);

void MakeCRC16Table(uint16_t *crctable) {
    uint16_t r;
    for(int i=0; i<256; i++){
        r = ((uint16_t)i)<<8;
        for(char j=0; j<8; j++) {
            if(r&(1<<15))
                r=(r<<1)^0x8005;
            else
                r=r<<1;
        }
        crctable[i]=r;
    }
}

uint16_t GetCRC16(char *buf, int len, uint16_t *crctable) {
    uint16_t crc;
    crc = 0xffff;
    while(len--)
    {
        crc = crctable[static_cast<int>(((crc>>8)^*buf++)&0xFF)] ^ (crc<<8);
    }
    crc ^= 0xffff;
    return crc;
}

uint16_t GetCRC16FromFile(char *filename, uint16_t *crctable) {
    uint16_t crc;
    crc = 0xffff;
    
    std::ifstream file(filename, std::ios::binary);
    if (!file)
        return 0x0000;
    
    char ch;
    file.read(&ch, 1);
    while(!file.eof()) {
        crc = crctable[static_cast<int>(((crc>>8)^ch)&0xFF)] ^ (crc<<8);
        file.read(&ch, 1);
    }
    crc ^= 0xffff;
    return crc;
}

