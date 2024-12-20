#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// MD5 Constants
const uint32_t s[64] = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

const uint32_t K[64] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

// Left rotate
uint32_t leftRotate(uint32_t x, uint32_t c) {
    return (x << c) | (x >> (32 - c));
}

// MD5 Hash function
string md5(const string& input) {
    // Initialize variables
    uint32_t a0 = 0x67452301;
    uint32_t b0 = 0xefcdab89;
    uint32_t c0 = 0x98badcfe;
    uint32_t d0 = 0x10325476;

    // Preprocessing
    size_t originalByteLen = input.size();
    size_t originalBitLen = originalByteLen * 8;

    // Padding the input
    vector<uint8_t> paddedInput;
    for (unsigned char c : input) {
        paddedInput.push_back(c);
    }

    paddedInput.push_back(0x80); // Append a single '1' bit

    while ((paddedInput.size() * 8) % 512 != 448) {
        paddedInput.push_back(0x00); // Append '0' bits
    }

    // Append the original length in bits
    for (int i = 0; i < 8; ++i) {
        paddedInput.push_back((originalBitLen >> (8 * i)) & 0xFF);
    }

    // Process the message in successive 512-bit chunks
    for (size_t i = 0; i < paddedInput.size(); i += 64) {
        uint32_t M[16];
        for (size_t j = 0; j < 16; ++j) {
            M[j] = (paddedInput[i + j * 4]) |
                   (paddedInput[i + j * 4 + 1] << 8) |
                   (paddedInput[i + j * 4 + 2] << 16) |
                   (paddedInput[i + j * 4 + 3] << 24);
        }

        uint32_t A = a0, B = b0, C = c0, D = d0;

        // Main loop
        for (size_t j = 0; j < 64; ++j) {
            uint32_t F, g;
            if (j < 16) {
                F = (B & C) | (~B & D);
                g = j;
            } else if (j < 32) {
                F = (D & B) | (~D & C);
                g = (5 * j + 1) % 16;
            } else if (j < 48) {
                F = B ^ C ^ D;
                g = (3 * j + 5) % 16;
            } else {
                F = C ^ (B | ~D);
                g = (7 * j) % 16;
            }

            uint32_t temp = D;
            D = C;
            C = B;
            B = B + leftRotate(A + F + K[j] + M[g], s[j]);
            A = temp;
        }

        a0 += A;
        b0 += B;
        c0 += C;
        d0 += D;
    }

    // Produce the final hash value
    stringstream hash;
    hash << hex << setfill('0') << setw(8) << a0
         << setw(8) << b0
         << setw(8) << c0
         << setw(8) << d0;

    return hash.str();
}

// Main function for testing
int main() {
    string input;
    cout << "Enter a string to hash: ";
    getline(cin, input);
    string hash = md5(input);
    cout << "MD5 Hash: " << hash << endl;
    return 0;
}
