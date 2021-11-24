#pragma once
#ifndef BASE64
#define BASE64
#include <string>
#include <cstring>



char reverse_sheet(char ch);

char sheet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
auto AtoB = [](char* ascii, char*& res) -> size_t {
    size_t len = strlen(ascii);
    char* s = new char[len + 16];
    memset(s, 0, sizeof(s));
    memcpy(s, ascii, len);
    res = new char[len * 2];
    size_t cnt = 0;
    for (size_t i = 0; i < len; i += 3) {
        int group = (s[i] << 16) + (s[i + 1] << 8) + s[i + 2], tcnt = 0;
        char temp[8];
        for (size_t j = 0; j < 4; j++, group >>= 6) temp[tcnt++] = group - ((group >> 6) << 6);
        for (; tcnt; ) res[cnt++] = sheet[temp[--tcnt]];
        res[cnt] = '\0';
    }
    return cnt;
};
auto BtoA = [](char* base64, char*& res) -> size_t {
    size_t len = strlen(base64);
    char* s = new char[len + 16];
    memset(s + len, 0, sizeof(s));
    for (size_t i = 0; i < len; i++)s[i] = reverse_sheet(base64[i]);
    res = new char[len * 2];
    size_t cnt = 0;
    for (size_t i = 0; i < len; i += 4) {
        size_t group = (s[i] << 18) + (s[i + 1] << 12) + (s[i + 2] << 6) + s[i + 3], tcnt = 0;
        char temp[8];
        for (size_t j = 0; j < 3; j++, group >>= 8) temp[tcnt++] = group - ((group >> 8) << 8);
        for (; tcnt; ) res[cnt++] = temp[--tcnt];
        res[cnt] = '\0';
    }
    return cnt;
};

char reverse_sheet(char ch) {
    if (ch >= 'A' && ch <= 'Z')
        return ch - 'A';
    else if (ch >= 'a' && ch <= 'z')
        return ch - 'a' + 26;
    else if (ch >= '0' && ch <= '9')
        return ch - '0' + 52;
    else if (ch == '+')
        return 62;
    else
        return 63;
}

#endif