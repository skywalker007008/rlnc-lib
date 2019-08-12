#include <cstdint>
#include <iostream>
#include "codec.h"

/*
 * Copyright G410 Studio
 * Author: Skywalker007008, Liu Zihao
 * Github Link: https://github.com/skywalker007008/marvelCoding
 * 
 */

GFType** RLNC encode(char* packet, int length, char* buf) {
    int vec_size = length / kPacketSize;
    memset(buf, 0, length * sizeof(char));
    GFType** rand_list = (GFType**)malloc(vec_size * sizeof(GFType*));
    GFType rand;

    for (int i = 0; i < vec_size; i++) {
        for (int t = 0; t < vec_size; t++) {
            rand = std::rand() % gFieldSize;
            std::cout << "rand:" << rand << "\n";
            for (int j = 0; j < kPacketSize; j++) {
                buf[i * kPacketSize + j] ^= gf_mul(rand, (uint8_t) packet[t * kPacketSize + j]);
                printf("%x\n", (uint8_t) buf[i * kPacketSize + j]);
            }
        }
        rand_list[i] = rand;
    }
    return rand_list;
}

void RLNC decode(char* packet, int length, char* buf, GFType* rand_list, int vec_size) {
    memset(buf, 0, length * sizeof(char));
    GFType rand;
    for (int i = 0; i < vec_size; i++) {
        rand = rand_list[vec_size - i - 1];
        for (int t = 0; t < vec_size; t++) {
            for (int j = 0; j < kPacketSize; j++) {
                buf[i * kPacketSize + j] ^= gf_mul(gf_inv(rand), (uint8_t) packet[t * kPacketSize + j]);
                printf("%x\n", (uint8_t) buf[i * kPacketSize + j]);
            }
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