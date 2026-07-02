#include "Cipher.h"
#include <stdexcept>
#include <iostream>

Cipher::Cipher(const std::string& libPath, const std::string& cipherType, const std::string& key) {
    handle = dlopen(libPath.c_str(), RTLD_LAZY);
    if (!handle) {
        throw std::runtime_error("Не вдалося завантажити бібліотеку: " + std::string(dlerror()));
    }

    create_caesar = (cipher_t*(*)(int)) dlsym(handle, "cipher_create_caesar");
    create_vigenere = (cipher_t*(*)(const char*)) dlsym(handle, "cipher_create_vigenere");
    encrypt_fn = (uint8_t*(*)(cipher_t*, const uint8_t*, size_t, size_t*)) dlsym(handle, "cipher_encrypt");
    decrypt_fn = (uint8_t*(*)(cipher_t*, const uint8_t*, size_t, size_t*)) dlsym(handle, "cipher_decrypt");
    destroy_fn = (void(*)(cipher_t*)) dlsym(handle, "cipher_destroy");
    free_fn = (void(*)(uint8_t*)) dlsym(handle, "cipher_free");

    if (!create_caesar || !create_vigenere || !encrypt_fn || !decrypt_fn || !destroy_fn || !free_fn) {
        throw std::runtime_error("Failed to load symbols: " + std::string(dlerror()));
    }

    if (cipherType == "caesar") {
        cipherObj = create_caesar(std::stoi(key));
    } else if (cipherType == "vigenere") {
        cipherObj = create_vigenere(key.c_str());
    } else {
        throw std::invalid_argument("Unknown cipher type: " + cipherType);
    }
}

Cipher::~Cipher() {
    if (cipherObj && destroy_fn) {
        destroy_fn(cipherObj);
    }
    if (handle) {
        dlclose(handle);
    }
}

std::vector<uint8_t> Cipher::encrypt(const std::vector<uint8_t>& data) {
    size_t outLength = 0;
    uint8_t* result = encrypt_fn(cipherObj, data.data(), data.size(), &outLength);
    std::vector<uint8_t> output(result, result + outLength);
    free_fn(result);
    return output;
}

std::vector<uint8_t> Cipher::decrypt(const std::vector<uint8_t>& data) {
    size_t outLength = 0;
    uint8_t* result = decrypt_fn(cipherObj, data.data(), data.size(), &outLength);
    std::vector<uint8_t> output(result, result + outLength);
    free_fn(result);
    return output;
}