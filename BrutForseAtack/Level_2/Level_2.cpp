#include <string>
#include "forse.h"
#include <vector>
#include <thread>
#include <fstream>
#include <ctime>
#include <thread>
#include <chrono>
#include <exception>
#include <iostream>
#include "openssl/evp.h"
#include <openssl/aes.h>
#include "openssl/sha.h"
#include "passwordGenerator.h"

unsigned char key[EVP_MAX_KEY_LENGTH];
unsigned char iv[EVP_MAX_IV_LENGTH];

void ReadFile(const std::string& filePath, std::vector<unsigned char>& buf)
{
    std::basic_fstream<unsigned char> fileStream(filePath, std::ios::binary | std::fstream::in);
    if (!fileStream.is_open())
    {
        //throw std::runtime_error("Can not open file " + filePath);
    }
    buf.clear();
    buf.insert(buf.begin(), std::istreambuf_iterator<unsigned char>(fileStream), std::istreambuf_iterator<unsigned char>());

    fileStream.close();
}

void WriteFile(const std::string& filePath, const std::vector<unsigned char>& buf)
{
    std::basic_ofstream<unsigned char> fileStream(filePath, std::ios::binary);
    fileStream.write(&buf[0], buf.size());
    fileStream.close();
    std::cout << "   its good ";
    abort;
}

void PasswordToKey(const std::string& password)
{
    OpenSSL_add_all_digests();
    const EVP_MD* dgst = EVP_get_digestbyname("md5");
    if (!dgst)
    {
        //throw std::runtime_error("no such digest");
    }

    const unsigned char* salt = NULL;
    if (!EVP_BytesToKey(EVP_aes_128_cbc(), EVP_md5(), salt,
        reinterpret_cast<const unsigned char*>(&password[0]),
        password.size(), 1, key, iv))
    {
        //throw std::runtime_error("EVP_BytesToKey failed");
    }
}

bool  DecryptAes(const std::vector<unsigned char>& plainText, std::vector<unsigned char>& chipherText)
{
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
    {
        //throw std::runtime_error("EncryptInit error");
    }

    std::vector<unsigned char> chipherTextBuf(plainText.size() + AES_BLOCK_SIZE);
    int chipherTextSize = 0;
    if (!EVP_DecryptUpdate(ctx, &chipherTextBuf[0], &chipherTextSize, &plainText[0], plainText.size())) {
        EVP_CIPHER_CTX_free(ctx);
        //throw std::runtime_error("Encrypt error");
    }

    int lastPartLen = 0;
    if (!EVP_DecryptFinal_ex(ctx, &chipherTextBuf[0] + chipherTextSize, &lastPartLen)) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    chipherTextSize += lastPartLen;
    chipherTextBuf.erase(chipherTextBuf.begin() + chipherTextSize, chipherTextBuf.end());
    chipherText.swap(chipherTextBuf);
    EVP_CIPHER_CTX_free(ctx);
    return true;
}

void CalculateHash(const std::vector<unsigned char>& data, std::vector<unsigned char>& hash)
{
    std::vector<unsigned char> hashTmp(SHA256_DIGEST_LENGTH);
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, &data[0], data.size());
    SHA256_Final(&hashTmp[0], &sha256);
    hash.swap(hashTmp);
    //hash.clear();
}

 void TimeCounter(passwordGenerator& first)
 {
     int i = 1;
     int allPasvord = CHAR_COUNT* CHAR_COUNT* CHAR_COUNT* CHAR_COUNT;
     
    while(i) {
     
     std::this_thread::sleep_for(std::chrono::milliseconds(1000));
     std::cout << "time = " << (i) << std::endl;
     //std::cout << "Count Genereate Password" << generatedPasswords << std::endl;
     i++;
    }
     

 }
 
 bool DecryptPassWord(std::vector<unsigned char> chipherText, std::vector<unsigned char> hash)
 {
     std::vector<unsigned char> plainText;
     bool a= DecryptAes(chipherText, plainText);
     if (a) {
         
         std::vector<unsigned char> hash2; //(plainText.begin(), plainText.end())
         CalculateHash(plainText, hash2);
         if (hash2 == hash) {
             WriteFile("D:\\Антон\\proj\\Level_1\\CodeBase_HomeTasks-master\\BruteForce\\plain_text_brutforseYEEES", plainText);
             return 1;
         }
         return 0;
     }
     else {
     return 0;
     
     }
 }
 
 void PasswordCheck(
     const std::vector<std::string>& packet,
     const std::vector<unsigned char>& chipherText,
     const std::vector<unsigned char>& hash,
     int const numbThreads) {

     if (numbThreads==1) {
         for (int i = 0; i < packet.size(); i++) {
             PasswordToKey(packet[i]);
             //std::cout << packet[i] << std::endl;
             bool write = DecryptPassWord(chipherText, hash);
         }
     }
     /*
         for (int i = (packet.size() / 2); i < packet.size(); i++) {
             PasswordToKey(packet[i]);
             //std::cout << packet[i] << std::endl;
             bool write = DecryptPassWord(chipherText, hash);
         }
     */
     }
 
int main()
{
     std::vector<unsigned char> chipherText;
     ReadFile("D:\\Антон\\proj\\Level_1\\CodeBase_HomeTasks-master\\BruteForce\\chipher_text_brute_force", chipherText);
     std::vector<unsigned char> hash(chipherText.begin() + chipherText.size() - SHA256_DIGEST_LENGTH, chipherText.end());
     chipherText.resize(chipherText.size() - SHA256_DIGEST_LENGTH);
     passwordGenerator first;
     std::thread TimeGeneratedPassword(TimeCounter,std::ref(first));
     int sizePacket = 500001;
     int amountThreads = 2;
     std::vector<std::string> startOfReport = {"0000"};
     first.SetPacket(sizePacket, startOfReport[0]);
     std::vector<std::string> packet = {};
     packet.reserve (sizePacket + 1);
     packet = first.GetPacket();
     std::thread PassCheck1 (PasswordCheck, std::ref(packet), std::ref(chipherText), std::ref(hash),1);
 //    std::thread PassCheck2(PasswordCheck, std::ref(packet), std::ref(chipherText), std::ref(hash), 2);
      std::thread circle1([&]() {
         first.SetPacket(sizePacket, packet[sizePacket-1]);
         packet = first.GetPacket();
         }); //second circle
     circle1.join();
     PassCheck1.join();
    // PassCheck2.join();
     std::thread PassCheck10(PasswordCheck, std::ref(packet), std::ref(chipherText), std::ref(hash), 1);
    // std::thread PassCheck20(PasswordCheck, std::ref(packet), std::ref(chipherText), std::ref(hash), 2);
     PassCheck10.join();
     //PassCheck20.join();
     TimeGeneratedPassword.join();
     std::cout << "its all right" << std::endl;

}




