#ifndef BASE64
#define BASE64
#include <string>
#include <cstring>

char sheet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// ASCII to Base64 Code
std::string AtoB(std::string &ascii){
    char *s = new char[ascii.length() + 16];
    memset(s, 0, sizeof(s));
    memcpy(s, ascii.c_str(), ascii.length());
    char *res = new char[ascii.length()*2];
    int cnt = 0;
    for(int i = 0; i < ascii.length(); i += 3){
        int group = (s[i] << 16) + (s[i+1] << 8) + s[i+2], tcnt = 0;
        char temp[8];
        for(int j = 0; j < 4 ;j++, group>>=6) temp[tcnt++] = group - ((group >> 6) << 6);
        for(; tcnt; ) res[cnt++] = sheet[temp[--tcnt]];
    }
    return std::string(res);
}



// Base64 to ASCII Code
std::string BtoA(std::string &base64){
    char *s = new char[base64.length() + 16];
    memset(s + base64.length(), 0, sizeof(s));
    for(int i = 0; i < base64.length(); i++)s[i] = reverse_sheet(base64[i]);
    char *res = new char[base64.length()*2];
    int cnt = 0;
    for(int i = 0; i < base64.length(); i += 4){
        size_t group = (s[i] << 18) + (s[i+1] << 12) + (s[i+2] << 6) + s[i+3], tcnt = 0;
        char temp[8];
        for(int j = 0; j < 3 ;j++, group>>=8) temp[tcnt++] = group - ((group >> 8) << 8);
        for(; tcnt; ) res[cnt++] = temp[--tcnt];
    }
    return std::string(res);
}



char reverse_sheet(char ch){
    if(ch >= 'A' && ch <= 'Z')
        return ch - 'A';
    else if(ch >= 'a' && ch <= 'z')
        return ch - 'a' + 26;
    else if(ch >= '0' && ch <= '9')
        return ch - '0' + 52;
    else if(ch == '+')
        return 62;
    else
        return 63;
}


#endif