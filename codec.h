/*
 * Copyright G410 Studio
 * Author: Skywalker007008, Liu Zihao
 * Github Link: https://github.com/skywalker007008/marvelCoding
 * 
 */

#ifndef RLNC_CODEC_H
#define RLNC_CODEC_H

#include <malloc.h>
#include <cstring>
#include <cstdlib>
#include "gf.h"

#define RLNC rlnc::

#define ROUND(a,b) ((a) + ((a) % (b)))
#define HIGH_8(a) (((a) >> 8) & 0xFF)
#define LOW_8(a) ((a) & 0xFF)

namespace rlnc {
    constexpr int kPacketSize = 64;
    /*!
     * Encode a packet into a encode_format
     * @param packet the origin message packet
     * @param length the length of the message packet
     * @param iter_time the time of the encode_iter_time
     * @param buf the buf to receive the encoded result
     * @return the random coefficient
     */
    GFType encode(char* packet, int length, int iter_time, char* buf);

    /*!
     * Decode a packet into a decode_format
     * @param packet the encoded message packet
     * @param length the length of the message packet
     * @param iter_time the time of the encode_iter_time
     * @param buf the receiver of the decode msg
     * @param rand the random coefficient used to encode
     */
    void decode(char* packet, int length, int iter_time, char* buf, GFType rand);

    /*!
     * test_print
     * @param msg msg to print
     */
    void print(char* msg);

    void print_mul();
}

#endif //RLNC_CODEC_H
