#include <cstdint>

#include "codec.h"
#include "test_codec.h"

/*
 * Copyright G410 Studio
 * Author: Skywalker007008, Liu Zihao
 * Github Link: https://github.com/skywalker007008/marvelCoding
 * 
 */
CODEC::Codec(int vec_size) :
        _vec_size(vec_size), _recv_num(0), _is_enough(false), _is_full(false) {
    _coef_mat = (GFType**)malloc(_vec_size * sizeof(GFType*));
    _cache_coef_mat = (GFType**)malloc(kMaxBufSize * sizeof(GFType*));
    _raw_msg = (char*)malloc(_vec_size * kPacketSize * sizeof(char*));
    _encode_msg = (char*)malloc(_vec_size * kPacketSize * sizeof(char*));
    _decode_msg = (char*)malloc(_vec_size * kPacketSize * sizeof(char*));
    _cache_msg = (char*)malloc(kMaxBufSize * kPacketSize * sizeof(char*));
    for (int i = 0; i < vec_size; i++) {
        _coef_mat[i] = (GFType*)malloc(vec_size * sizeof(GFType));
        _cache_coef_mat[i] = (GFType*)malloc(vec_size * sizeof(GFType));
    }
    for (int i = vec_size; i < kMaxBufSize; i++) {
        _cache_coef_mat[i] = (GFType*)malloc(vec_size * sizeof(GFType));
    }
}

CODEC::~Codec() {
    free(_raw_msg);
    free(_encode_msg);
    free(_decode_msg);
    free(_cache_msg);
    for (int i = 0; i < _vec_size; i++) {
        free(_coef_mat[i]);
        free(_cache_coef_mat[i]);
    }
    for (int i = _vec_size; i < kMaxBufSize; i++) {
        free(_cache_coef_mat[i]);
    }
    free(_coef_mat);
    free(_cache_coef_mat);
}

void CODEC::RecvMessage(char* msg, GFType* coef) {
    // TODO: Recv the msg and add the coef to the cache
    memcpy((_cache_msg + _recv_num * kPacketSize), msg, kPacketSize * sizeof(char));
    memcpy(_cache_coef_mat[_recv_num], coef, _vec_size * sizeof(GFType));
    _recv_num++;
    if (_recv_num == kMaxBufSize) {
        _is_full = true;
    }
}

bool CODEC::LinkMsg() {
    // TODO: Reform the msg with previous _vec_size rows is full-trace
    GFType** orig_mat = (GFType**)malloc(_recv_num * sizeof(GFType*));
    // TODO: Copy the cache_mat
    for (int i = 0; i < _recv_num; i++) {
        orig_mat[i] = (GFType*) malloc(_vec_size * sizeof(GFType));
        memcpy(orig_mat[i], _cache_coef_mat[i], _vec_size * sizeof(GFType));
    }
    // TODO: Turn it into a lower-triangle-matrix
    GFType temp;
    GFType shift_temp;
    char* msg_temp = (char*) malloc(kPacketSize * sizeof(char));
    for (int i = 0; i < _vec_size; i++) {
        // TODO: Turn the [i][i] into 1(change both orig and dest)
        temp = orig_mat[i][i];
        // if [i][i] == 0, needs shift
        if (temp == 0) {
            // TODO: Find a row j while [j][i] != 0
            for (int j = i; j < _recv_num; i++) {
                if (orig_mat[j][i] != 0) {
                    // TODO: Shift the 2 lines
                    for (int k = 0; k < _vec_size; k++) {
                        shift_temp = orig_mat[i][k];
                        orig_mat[i][k] = orig_mat[j][k];
                        orig_mat[j][k] = shift_temp;
                        shift_temp = _cache_coef_mat[i][k];
                        _cache_coef_mat[i][k] = _cache_coef_mat[j][k];
                        _cache_coef_mat[j][k] = shift_temp;
                    }
                    memcpy(msg_temp, (_cache_msg + i * kPacketSize), kPacketSize * sizeof(char));
                    memcpy((_cache_msg + i * kPacketSize), (_cache_msg + j * kPacketSize), kPacketSize * sizeof(char));
                    memcpy((_cache_msg + j * kPacketSize), msg_temp, kPacketSize * sizeof(char));
                    break;
                }
                // TODO: if not found, return false
                if (j == _recv_num - 1) {
                    _recv_num--;
                    return false;
                }
            }
            temp = orig_mat[i][i];
        }
        for (int j = 0; j < _vec_size; j++) {
            orig_mat[i][j] = gf_div(orig_mat[i][j], temp);
        }
        // TODO: Turn the column[i] into 1,0,0,0......
        for (int t = i + 1; t < _recv_num; t++) {
            temp = orig_mat[t][i];
            for (int j = 0; j < _vec_size; j++) {
                orig_mat[t][j] = gf_sub(orig_mat[t][j], gf_mul(temp, orig_mat[i][j]));
            }
        }
    }
    // TODO: Copy the cache into the place
    for (int i = 0; i < _vec_size; i++) {
        memcpy(_coef_mat[i], _cache_coef_mat[i], _vec_size * sizeof(GFType));
    }
    memcpy(_raw_msg, _cache_msg, _vec_size * kPacketSize * sizeof(char));
    _is_enough = true;
    return true;
}

void CODEC::get_encode_message(char* buf) {
    memcpy(buf, _encode_msg, _recv_num * kPacketSize * sizeof(char));
}

void CODEC::get_decode_message(char* buf) {
    memcpy(buf, _decode_msg, _vec_size * kPacketSize * sizeof(char));
}

GFType** CODEC::encode() {
    GFType** rand_list = (GFType**)malloc(_vec_size * sizeof(GFType*));
    GFType rand;
    memcpy(_raw_msg, _cache_msg, _recv_num * kPacketSize * sizeof(char));
    for (int i = 0; i < _recv_num; i++) {
        rand_list[i] = (GFType*)malloc(_recv_num * sizeof(GFType));
        for (int t = 0; t < _recv_num; t++) {
            rand = std::rand() % gFieldSize;
            for (int j = 0; j < kPacketSize; j++) {
                _encode_msg[i * kPacketSize + j] ^=
                        gf_mul(rand, (uint8_t) _raw_msg[t * kPacketSize + j]);
            }
            rand_list[i][t] = rand;
        }
    }
    return rand_list;
}

void CODEC::decode() {
    GFType** inv_mat = gauss_inv(_coef_mat, 2);
    GFType rand;
    for (int i = 0; i < _vec_size; i++) {
        for (int t = 0; t < _vec_size; t++) {
            rand = inv_mat[i][t];
            for (int j = 0; j < kPacketSize; j++) {
                _decode_msg[i * kPacketSize + j] ^=
                        gf_mul(rand, (uint8_t) _raw_msg[t * kPacketSize + j]);
            }
        }
    }
}

