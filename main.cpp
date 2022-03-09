#include "iostream"
#include "sha256.h"
#include "base64.h"

using namespace std;



int main() {

	char a[] = "abcdef";
	char *b = nullptr;
	cout << sha256(a, b) << endl;
	
	return 0;
}