#ifndef ASSIGMENT4_CIPHER_H
#define ASSIGMENT4_CIPHER_H

#include <vector>
#include <string>
#include <cstdint>
#include <cstddef>
#include <dlfcn.h>

typedef void* cipher_t;

class Cipher {
    void* handle = nullptr;
    cipher_t* cipherObj = nullptr;

    cipher_t* (*create_caesar)(int) = nullptr;
    cipher_t* (*create_vigenere)(const char*) = nullptr;
    uint8_t* (*encrypt_fn)(cipher_t*, const uint8_t*, size_t, size_t*) = nullptr;
    uint8_t* (*decrypt_fn)(cipher_t*, const uint8_t*, size_t, size_t*) = nullptr;
    void (*destroy_fn)(cipher_t*) = nullptr;
    void (*free_fn)(uint8_t*) = nullptr;

public:
    Cipher(const std::string& libPath, const std::string& cipherType, const std::string& key);
    ~Cipher();

    std::vector<uint8_t> encrypt(const std::vector<uint8_t>& data);
    std::vector<uint8_t> decrypt(const std::vector<uint8_t>& data);
};

#endif //ASSIGMENT4_CIPHER_H