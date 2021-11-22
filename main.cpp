#include "base64.h"
#include "iostream"
#include "sha256.h"
using namespace std;


void base64test() {
	char a[] = "Hello World!";
	char* b = nullptr;
	char* c = nullptr;
	size_t blen = AtoB(a, b);
	size_t clen = BtoA(b, c);

	printf("%s\n%d\n", b, blen);
	printf("%s\n%d\n", c, clen);
}

int main() {
	base64test();
	return 0;
}