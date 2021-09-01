#ifndef SHA256
#define SHA256
#include <cstdio>
#include <cstring>
#include <cstdlib>


#define HMAC_SHA256_DIGEST_SIZE 32
#define I_PAD 0x36
#define O_PAD 0x5C
#define B 64
#define L (SHA256_DIGEST_SIZE)
#define K (SHA256_DIGEST_SIZE * 2)

void hmac_sha256 (
char out[HMAC_SHA256_DIGEST_SIZE],
const char* data, size_t data_len,
const char* key, size_t key_len){


}

#endif