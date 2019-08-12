/*
 * Copyright G410 Studio
 * Author: Skywalker007008, Liu Zihao
 * Github Link: https://github.com/skywalker007008/marvelCoding
 * 
 */

#include "test_codec.h"

void RLNC print(char* msg) {
    int len = strlen(msg);
    for (int i = 0; i < len / 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%x ", (uint8_t)msg[i * 4 + j]);
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

void RLNC print_mat(GFType** mat, int vec_size) {
    printf("matrix::\n");
    for (int i = 0; i < vec_size; i++) {
        for (int j = 0; j < vec_size; j++) {
            printf("%x ", mat[i][j]);
        }
        printf("\n");
    }
}