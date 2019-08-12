#include <cstdint>

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
        rand_list[i] = (GFType*)malloc(vec_size * sizeof(GFType));
        for (int t = 0; t < vec_size; t++) {
            rand = std::rand() % gFieldSize;
            std::cout << "rand:" << rand << "\n";
            for (int j = 0; j < kPacketSize; j++) {
                buf[i * kPacketSize + j] ^= gf_mul(rand, (uint8_t) packet[t * kPacketSize + j]);
                // printf("%x\n", (uint8_t) buf[i * kPacketSize + j]);
            }
            rand_list[i][t] = rand;
        }
    }
    return rand_list;
}

void RLNC decode(char* packet, int length, char* buf, GFType** rand_list, int vec_size) {
    memset(buf, 0, length * sizeof(char));
    GFType rand;
    for (int i = 0; i < vec_size; i++) {
        for (int t = 0; t < vec_size; t++) {
            rand = rand_list[i][t];
            std::cout << "rand:" << rand << "\n";
            for (int j = 0; j < kPacketSize; j++) {
                buf[i * kPacketSize + j] ^= gf_mul(rand, (uint8_t) packet[t * kPacketSize + j]);
                // printf("%x\n", (uint8_t) buf[i * kPacketSize + j]);
            }
        }
    }
}

