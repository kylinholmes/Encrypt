#include <iostream>
#include <string>
#include "base64.cpp"

using namespace std;

int main(){
    string a = "Hello World!!";
    string b = AtoB(a);
    cout << b << endl;
    cout << BtoA(b) << endl;
    return 0;
}