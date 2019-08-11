#include <iostream>

#include "codec.h"

int main() {
    GFType rand1, rand2, rand3;
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
    rand1 = RLNC encode(packet, 128, 1, encode_buf1);
    std::cout << "Encode1 Finished\n";
    RLNC print(encode_buf1);

    rand2 = RLNC encode(encode_buf1, 128, 1, encode_buf2);
    std::cout << "Encode2 Finished\n";
    RLNC print(encode_buf2);

    rand3 = RLNC encode(encode_buf2, 128, 1, encode_buf3);
    std::cout << "Encode3 Finished\n";
    RLNC print(encode_buf3);

    RLNC decode(encode_buf3, 128, 1, decode_buf, gf_mul(gf_mul(rand1, rand2), rand3));
    std::cout << "Decode Finished\n";
    RLNC print(decode_buf);

    int a = gf_mul(103, 104);
    int c = gf_mul(198, a);
    int b = gf_mul(gf_inv(gf_mul(103, 198)), c);
    printf("%x %x\n", a, b);

    // RLNC print_mul();
}