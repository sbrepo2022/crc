#include <iostream>

unsigned char arr_crc8(unsigned char *data, int size);
void print_bin_char(unsigned char num);
void print_bin_short(unsigned short num);

int main() {
    unsigned char arr[2] = {0x96, 0x4b};
    print_bin_char(arr_crc8(arr, 2));
    system("pause");
    return 0;
}

unsigned char arr_crc8(unsigned char *data, int size) {
    unsigned char polynom = 0xd5;
    unsigned short cregister = 0x0000;
    
    for (unsigned int i = 0; i < size; i++) {
        cregister |= static_cast<unsigned short>(data[i]);
        
        for (unsigned short j = 0; j < 8; j++) {
            if (cregister & 0x8000) {
                cregister ^= static_cast<unsigned short>(polynom) * 0x100;
            }
            cregister <<= 1;
        }
    }
    return static_cast<unsigned char>(cregister / 0x100);
}

void print_bin_char(unsigned char num) {
    int i = 8;
    int c = 128;
    while (i--) {
        (num & c) ? std::cout << 1 : std::cout << 0;
        c /= 2;
    }
}

void print_bin_short(unsigned short num) {
    int i = 16;
    int c = 32768;
    while (i--) {
        (num & c) ? std::cout << 1 : std::cout << 0;
        c /= 2;
    }
}