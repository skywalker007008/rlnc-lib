/*
 * Copyright G410 Studio
 * Author: Skywalker007008, Liu Zihao
 * Github Link: https://github.com/skywalker007008/marvelCoding
 * 
 */

#ifndef RLNC_CODEC_H
#define RLNC_CODEC_H

#include <malloc.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include "gf.h"

#define RLNC rlnc::

#define ROUND(a,b) ((a) + ((a) % (b)))
#define HIGH_8(a) (((a) >> 8) & 0xFF)
#define LOW_8(a) ((a) & 0xFF)

namespace rlnc {
    /*class Codec {
    public:
        Codec();
        ~Codec();
        void set_message(char* message);

    };*/
    constexpr int kPacketSize = 64;
    /*!
     * Encode a packet into a encode_format
     * @param packet the origin message packet
     * @param length the length of the message packet
     * @param buf the buf to receive the encoded result
     * @return the random coefficient list
     */
    GFType** encode(char* packet, int length, char* buf);

    /*!
     * Decode a packet into a decode_format
     * @param packet the encoded message packet
     * @param length the length of the message packet
     * @param buf the receiver of the decode msg
     * @param rand_list the random coefficient used to encode
     * @param vec_size the size of the msg
     */
    void decode(char* packet, int length, char* buf, GFType** rand_list, int vec_size);
}

#endif //RLNC_CODEC_H
