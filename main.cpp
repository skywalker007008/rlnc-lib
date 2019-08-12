#include <iostream>

#include "test_codec.h"

int main() {
    GFType** rand1;
    GFType** rand2;
    GFType** rand3;
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
    char packet[128] = "This is the test code. "
            "And encode and decode this message to test the result right or not";
    RLNC print(packet);
    rand1 = RLNC encode(packet, 128, encode_buf1);
    std::cout << "Encode1 Finished\n";
    RLNC print(encode_buf1);

    rand2 = gauss_inv(rand1, 4);

    RLNC decode(encode_buf1, 128, decode_buf, rand2, 4);
    std::cout << "Decode Finished\n";
    RLNC print(decode_buf);

    GFType a = gf_add(gf_mul(0x67, 0x5f), gf_mul(0xC6, 0xaa));
    GFType b = gf_add(gf_mul(0x67, 0xf), gf_mul(0xC6, 0x83));
    GFType c = gf_add(gf_mul(0x69, 0x5f), gf_mul(0x73, 0xaa));
    GFType d = gf_add(gf_mul(0x69, 0xf), gf_mul(0x73, 0x83));

    GFType e = gf_div(0xde, 0x1a);
    printf("%x %x %x %x\n", a, b, c, d);
    // printf("%x\n", e);

    // RLNC print_mul();
}