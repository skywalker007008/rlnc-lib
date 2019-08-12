#include <iostream>

#include "test_codec.h"

int main() {
    GFType** rand1;
    GFType** rand2;
    GFType** rand3;
    GFType** rand4;
    GFType** standard_coef = (GFType**)malloc(2 * sizeof(GFType*));
    standard_coef[0] = (GFType*)malloc(2 * sizeof(GFType));
    standard_coef[1] = (GFType*)malloc(2 * sizeof(GFType));
    standard_coef[0][0] = 1;
    standard_coef[0][1] = 0;
    standard_coef[1][0] = 0;
    standard_coef[1][1] = 1;
    char* encode_buf1 = (char*)malloc(128 * sizeof(char));
    char* encode_buf2 = (char*)malloc(128 * sizeof(char));
    char* encode_buf3 = (char*)malloc(128 * sizeof(char));
    char* decode_buf = (char*)malloc(128 * sizeof(char));
    std::cout << "Hello, World!" << std::endl;
    gf_init(8, prim_poly[8]);
    if (false) {
        printf("%d %d\n", HIGH_8(48879), LOW_8(48879));
        printf("%d\n", gf_mul(HIGH_8(48879), LOW_8(48879)));
        return 0;
    }
    // gf_print();
    // RLNC print_mul();
    CODEC codec(2);
    char packet[128] = "This is the test code. "
            "And encode and decode this message to test the result right or not";
    RLNC print(packet);
    codec.RecvMessage(packet, standard_coef[0]);
    codec.RecvMessage(packet + RLNC kPacketSize, standard_coef[1]);
    rand1 = codec.encode();
    RLNC print_mat(rand1, 2);
    rand1 = gf_newcoef(rand1, standard_coef, 2, 2);
    RLNC print_mat(rand1, 2);
    codec.get_encode_message(encode_buf1);
    std::cout << "Encode1 Finished\n";
    // RLNC print(encode_buf1);
    // free(&codec);

    CODEC codec2(2);
    codec2.RecvMessage(encode_buf1, rand1[0]);
    codec2.RecvMessage(encode_buf1 + RLNC kPacketSize, rand1[1]);
    rand2 = codec2.encode();
    RLNC print_mat(rand2, 2);
    rand2 = gf_newcoef(rand2, rand1, 2, 2);
    RLNC print_mat(rand2, 2);
    codec2.get_encode_message(encode_buf2);
    std::cout << "Encode2 Finished\n";
    // RLNC print(encode_buf2);
    // free(&codec2);

    CODEC codec3(2);
    codec3.RecvMessage(encode_buf2, rand2[0]);
    codec3.RecvMessage(encode_buf2 + RLNC kPacketSize, rand2[1]);
    if (codec3.LinkMsg()) {
        std::cout << "Link Finished\n";
        codec3.decode();
        codec3.get_decode_message(decode_buf);
        std::cout << "Decode Finished\n";
        RLNC print(decode_buf);
    }

    GFType a = gf_add(gf_mul(0xbd, 0xf1), gf_mul(0x24, 0x6b));
    GFType b = gf_add(gf_mul(0xbd, 0xd3), gf_mul(0x24, 0xc4));
    GFType c = gf_add(gf_mul(0x79, 0xf1), gf_mul(0xa3, 0x6b));
    GFType d = gf_add(gf_mul(0x79, 0xd3), gf_mul(0xa3, 0xc4));

    GFType e = gf_div(0xde, 0x1a);
    printf("%x %x %x %x\n", a, b, c, d);


    // printf("%x\n", e);

    // RLNC print_mul();
    free(encode_buf1);
    free(encode_buf2);
    free(encode_buf3);
}