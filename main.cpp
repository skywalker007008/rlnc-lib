#include <iostream>

#include "codec.h"

int main() {
    GFType rand;
    char* encode_buf = (char*)malloc(128 * sizeof(char));
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
    rand = RLNC encode(packet, 128, 1, encode_buf);
    std::cout << "Encode Finished\n";
    RLNC print(encode_buf);
    // RLNC decode(encode_buf, 128, 1, decode_buf, rand);
    // std::cout << "Decode Finished\n";
    // RLNC print(decode_buf);
}