#pragma once
#ifndef SHA256
#define SHA256


const uint32_t  Const_H[8] = {
	0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};
const uint32_t  Const_K[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

inline uint32_t ror(uint32_t val, size_t bit) {
	return (val >> bit) | (val << (32 - bit));
}

inline bool isBigEndian() {
	uint32_t tmp = 0xabcdeeff;
	char* check = (char*)&tmp;
	return (uint32_t)(*check) != 0xff;
}

template<typename T>
inline T ToBigEndian(T val) {
	if (!isBigEndian())
		return val;
	char* res = (char*)&val;
	uint32_t size = sizeof(T);
	for (uint32_t i = 0; i < size / 2; i++)
		std::swap(res[i], res[size - 1 - i]);
	return val;
}
// useless but define
template<typename T>
inline T ToLittleEndian(T val) {
	if (isBigEndian())
		return val;
	char* res = (char*)&val;
	uint32_t size = sizeof(T);
	for (uint32_t i = 0; i < size / 2; i++)
		std::swap(res[i], res[size - 1 - i]);
	return val;
}





size_t PreProcess(char *msg, char* &res) {
	
	// calc extra bit and byte that will append to the msg
	uint64_t len		=	strlen(msg);
	uint64_t extra_bit	=	(512 + 448 - ((512 + (len * 8 + 1)) % 512)) % 512;
	uint64_t extra_byte	=	(extra_bit + 1) / 8;
	uint64_t reslen		=	len + extra_byte + 8;
	
	// allocate enough memory and set zero
	res = new char[reslen + 8];
	memset(res, 0, reslen);
	// copy msg to res 
	memcpy(res, msg, strlen(msg));

	uint64_t* plen;
	// set b`1000 0000` at the end of msg
	plen = (uint64_t*)(res + len);
	memset(res + len, -1, 8);
	(*plen)	&= (uint64_t)0x80;
	
	// set length of msg at the end of res, in Bid Endian
	plen = (uint64_t*)(res + extra_byte + len);
	memset(res + len + extra_byte, -1, 8);
	(*plen)	&= ToBigEndian((uint64_t)len * 8);
	return len + extra_byte + 8;
}

uint32_t* MainLoop(char*& res, uint64_t len) {

	uint32_t* H = new uint32_t[9];
	memcpy(H, Const_H, 8);
	H[8] = 0;
	// split total into => 64Byte a chunk
	// chunk num = len / 64;
	for (uint64_t i = 0; i < len; i += 64) {
		uint32_t* chunk = (uint32_t*)(res + i);
		uint32_t w[64], cnt = 0;
		memset(w, 0, sizeof(w));

		// w in Big Endian
		for (uint32_t j = 0; j < 16; j++)
			w[cnt++] = ToBigEndian((*(chunk + j)));

		// define variable
		uint64_t s0, s1, ch, t1, t2, maj;
		uint32_t A2H[8];
		memcpy(A2H, H, 8);

		// handle W msg chunk
		for (uint32_t j = 16; j < 64; j++) {
			s0 = ror(w[j - 15], 7) ^ ror(w[j - 15], 18) ^ (w[j - 15] >> 3);
			s1 = ror(w[j - 2], 17) ^ ror(w[j - 2], 19) ^ (w[j - 2] >> 10);
			w[j] = w[j - 16] + s0 + w[j - 7] + s1;
		}


		// apply sha256 func to update a, b, c, ..., h
		for (uint32_t j = 0; j < 64; j++) {
			s1 = ror(A2H[4], 6) ^ ror(A2H[4], 11) ^ ror(A2H[4], 25);
			ch = (A2H[4] & A2H[5]) ^ ((~A2H[4]) & A2H[6]);
			t1 = A2H[7] + s1 + ch + Const_K[j] + w[j];

			s0 = ror(A2H[0], 2) ^ ror(A2H[0], 13) ^ ror(A2H[0], 22);
			maj = (A2H[0] & A2H[1]) ^ (A2H[0] & A2H[2]) ^ (A2H[1] & A2H[2]);
			t2 = s0 + maj;

			for (uint32_t k = 7; k >= 1; k--)
				std::swap(A2H[k], A2H[k - 1]);
			A2H[4] += t1;
			A2H[0] = t1 + t2;
		}

		// update A2H to H
		for (uint32_t j = 0; j < 8; j++)
			H[j] += A2H[j];
	}
	for (uint32_t i = 0; i < 8; i++) 
		H[i] = ToBigEndian(H[i]);
	
	return H;
}
#include <ostream>
struct sha256result {
	char* ptr;
	sha256result(char* res) :ptr(res) {};
	friend std::ostream& operator<< (std::ostream& os, const sha256result& res) {
		for (int i = 0; i < 32; i++) 
			os << std::hex << ((uint32_t)(*(res.ptr + i)) & 0xff);
		return os;
	}
};

auto sha256 = [](char* msg, char* &res)-> sha256result {
	size_t length = PreProcess(msg, res);
	res = (char*)MainLoop(res, length);
	return sha256result(res);
};

#endif
