#include <stdint.h>
#include <fstream>

uint16_t arr_crc16(char *data, int size);
uint16_t file_crc16(char *filename);

uint16_t arr_crc16(char *data, int size) {
    uint16_t polynom = 0x8005;
    uint32_t cregister = 0x00000000;
    
    for (int i = 0; i < size + 2; i++) {
        if (i < size)
            cregister |= static_cast<uint32_t>(data[i]) * 0x100;
        
        for (int j = 0; j < 8; j++) {
            if (cregister & 0x80000000) {
                cregister = (cregister << 1) ^ static_cast<uint32_t>(polynom) * 0x10000;
            }
            else
                cregister <<= 1;
        }
    }
    
    return static_cast<uint16_t>(cregister / 0x10000);
}

uint16_t file_crc16(char *filename) {
    uint16_t polynom = 0x8005;
    uint32_t cregister = 0x00000000;
    
    std::ifstream file(filename, std::ios::binary);
    if (!file)
        return 0x0000;
    
    char ch;
    int i = 0;
    while (i < 2) {
        file.read(&ch, 1);
        if (!file.eof())
            cregister |= static_cast<uint32_t>(ch) * 0x100;
        else
            i++;
        
        for (int j = 0; j < 8; j++) {
            if (cregister & 0x80000000) {
                cregister = (cregister << 1) ^ static_cast<uint32_t>(polynom) * 0x10000;
            }
            else
                cregister <<= 1;
        }
    }
    
    return static_cast<uint16_t>(cregister / 0x10000);
}