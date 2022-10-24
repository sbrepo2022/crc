#include <iostream>
#include <fstream>
#include <stdint.h>
#include <cstring>

void MakeCRC16Table(uint16_t *crctable);
uint16_t GetCRC16(char *buf, int len, uint16_t *crctable);
uint16_t GetCRC16FromFile(char *filename, uint16_t *crctable);

void print_bin_uint16_t(uint16_t num);

int main() {
    uint16_t crctable[256];
    MakeCRC16Table(crctable);
    
    char str[256];
    int action;
    std::cout << "Enter action (0 - text, 1 - file):";
    std::cin >> action;
    
    uint16_t result;
    switch (action) {
        case 0:
            std::cout << "Enter text, that you want to hash by crc16 function: ";
            std::cin >> str;
            
            result = GetCRC16(str, strlen(str), crctable);
            break;
            
        case 1:
            std::cout << "Enter name of file, that you want to hash by crc16 function: ";
            std::cin >> str;
            
            result = GetCRC16FromFile(str, crctable);
            break;
    }
    std::cout << "bin: ";
    print_bin_uint16_t(result);
    std::cout << "\n";
    std::cout << "dec: " << result << "\n";
    
    system("pause");
    return 0;
}

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


void print_bin_uint16_t(uint16_t num) {
    int i = 16;
    int c = 32768;
    while (i--) {
        (num & c) ? std::cout << 1 : std::cout << 0;
        if (!(i % 4))
            std::cout << " ";
        c /= 2;
    }
}

