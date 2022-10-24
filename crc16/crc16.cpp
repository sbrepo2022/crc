#include <iostream>
#include <stdint.h>
#include <fstream>
#include <cstring>

uint16_t arr_crc16(char *data, int size);
uint16_t file_crc16(char *filename);
void print_bin_uint16_t(uint16_t num);

int main() {
    char str[256];
    int action;
    std::cout << "Enter action (0 - text, 1 - file):";
    std::cin >> action;
    
    uint16_t result;
    switch (action) {
        case 0:
            std::cout << "Enter text, that you want to hash by crc16 function: ";
            std::cin >> str;
            
            result = arr_crc16(str, strlen(str));
            break;
            
        case 1:
            std::cout << "Enter name of file, that you want to hash by crc16 function: ";
            std::cin >> str;
            
            result = file_crc16(str);
            break;
    }
    std::cout << "bin: ";
    print_bin_uint16_t(result);
    std::cout << "\n";
    std::cout << "dec: " << result << "\n";
    
    system("pause");
    return 0;
}

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
            
            std::cout << "register #" << j << ":\t";
            print_bin_uint16_t(static_cast<uint16_t>(cregister / 0x10000));
            std::cout << "\n";
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
            
            std::cout << "register #" << j << ":\t";
            print_bin_uint16_t(static_cast<uint16_t>(cregister / 0x10000));
            std::cout << "\n";
        }
    }
    
    return static_cast<uint16_t>(cregister / 0x10000);
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