#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// SHA-256 constants
const uint32_t k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b,
    0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
    0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7,
    0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152,
    0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
    0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc,
    0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x913f7e82,
    0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// Right rotate
uint32_t rightRotate(uint32_t value, uint32_t amount) {
    return (value >> amount) | (value << (32 - amount));
}

// SHA-256 hash function
string sha256(const string& input) {
    // Initialize hash values
    uint32_t h[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };

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
        paddedInput.push_back((originalBitLen >> (56 - i * 8)) & 0xFF);
    }

    // Process the message in successive 512-bit chunks
    for (size_t i = 0; i < paddedInput.size(); i += 64) {
        uint32_t w[64] = {0};

        // Break chunk into sixteen 32-bit big-endian words
        for (size_t j = 0; j < 16; ++j) {
            w[j] = (paddedInput[i + j * 4] << 24) |
                   (paddedInput[i + j * 4 + 1] << 16) |
                   (paddedInput[i + j * 4 + 2] << 8) |
                   (paddedInput[i + j * 4 + 3]);
        }

        // Extend the first 16 words into the remaining 48 words
        for (size_t j = 16; j < 64; ++j) {
            uint32_t s0 = rightRotate(w[j - 15], 7) ^ rightRotate(w[j - 15], 18) ^ (w[j - 15] >> 3);
            uint32_t s1 = rightRotate(w[j - 2], 17) ^ rightRotate(w[j - 2], 19) ^ (w[j - 2] >> 10);
            w[j] = w[j - 16] + s0 + w[j - 7] + s1;
        }

        // Initialize working variables to current hash value
        uint32_t a = h[0];
        uint32_t b = h[1];
        uint32_t c = h[2];
        uint32_t d = h[3];
        uint32_t e = h[4];
        uint32_t f = h[5];
        uint32_t g = h[6];
        uint32_t h0 = h[7];

        // Compression function main loop
        for (size_t j = 0; j < 64; ++j) {
            uint32_t S1 = rightRotate(e, 6) ^ rightRotate(e, 11) ^ rightRotate(e, 25);
            uint32_t ch = (e & f) ^ ((~e) & g);
            uint32_t temp1 = h0 + S1 + ch + k[j] + w[j];
            uint32_t S0 = rightRotate(a, 2) ^ rightRotate(a, 13) ^ rightRotate(a, 22);
            uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
            uint32_t temp2 = S0 + maj;

            h0 = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        // Add the compressed chunk to the current hash value
        h[0] += a;
        h[1] += b;
        h[2] += c;
        h[3] += d;
        h[4] += e;
        h[5] += f;
        h[6] += g;
        h[7] += h0;
    }

    // Produce the final hash value (big-endian)
    string hash;
    for (int i = 0; i < 8; ++i) {
        hash += to_string(h[i]);
    }
    return hash;
}

// Main function for testing
int main() {
    string input;
    cout << "Enter a string to hash: ";
    getline(cin, input);
    string hash = sha256(input);
    cout << "SHA-256 Hash: " << hash << endl;
    return 0;
}
