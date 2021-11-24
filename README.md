# Encrypt
A encrypt lib with c/cpp

In order to better call and pass, I design them as  functors, by naming anonymous functions.
## Usage of Base64
```cpp
// ASCII to Base64 Code
size_t AtoB(char* ascii,  char*& res)
// Base64 to ASCII Code
size_t BtoA(char* base64, char*& res)
```

## Usage of SHA256
```cpp
sha256result sha256(char* msg, char*& res)
//overload operator<<
//use cout to output
```

## Usage of HMACSHA256
```cpp
//to be comtinue;
```
