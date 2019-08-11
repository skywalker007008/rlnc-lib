#include <cstdint>
#include <iostream>
#include "codec.h"

/*
 * Copyright G410 Studio
 * Author: Skywalker007008, Liu Zihao
 * Github Link: https://github.com/skywalker007008/marvelCoding
 * 
 */

GFType RLNC encode(char* packet, int length, int iter_time, char* buf) {
    // char* buf = (char*)malloc(length * sizeof(char));
    // int windows = ROUND(length, kPacketSize) / kPacketSize;
    // memcpy(buf, packet, length * sizeof(char));
    memset(buf, 0, length * sizeof(char));
    GFType rand = std::rand() % gFieldSize;
    std::cout << "rand:" << rand << "\n";
    for (int i = 0; i < iter_time; i++) {
        for (int j = 0; j < length; j++) {
            printf("%x ", (uint8_t)buf[j]);
            buf[j] = gf_mul(rand, (uint8_t)packet[j]);
            // printf("%d %d\n", HIGH_8(result), LOW_8(result));
            // std::cout << gf_mul(HIGH_8(result), LOW_8(result)) << "\n";
            printf("%x\n", (uint8_t)buf[j]);
        }
    }
    return rand;
}

void RLNC decode(char* packet, int length, int iter_time, char* buf, GFType rand) {
    // memcpy(buf, packet, length * sizeof (char));
    memset(buf, 0, length * sizeof(char));
    for (int i = 0; i < iter_time; i++) {
        for (int j = 0; j < length; j++) {
            printf("%x ", (uint8_t)packet[j]);
            buf[j] = gf_mul(gf_inv(rand), (uint8_t)packet[j]);
            printf("%x\n", (uint8_t)buf[j]);
        }
    }
}

void RLNC print(char* msg) {
    int len = strlen(msg);
    for (int i = 0; i < len / 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%x ", (uint8_t)msg[i * 8 + j]);
        }
        std::cout << "\n";
    }
}

void RLNC print_mul() {
    for (int i = 0; i < gFieldSize; i++) {
        for (int j = 0; j < gFieldSize; j++) {
            printf("%x ", table_mul[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    for (int i = 0; i < gFieldSize; i++) {
        for (int j = 0; j < gFieldSize; j++) {
            printf("%x ", table_div[i][j]);
        }
        printf("\n");
    }

    printf("%x", gf_mul(3,0xE));

}