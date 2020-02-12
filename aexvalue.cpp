#include "aexvalue.h"

AexValue::AexValue(QString text,QString key,QString iv = "0123456789012345")
{
    AexValue(text.toStdString(),key.toStdString(),iv.toStdString());
}

AexValue::AexValue(string text,string key,string iv = "0123456789012345")
{
    this->_plainTextValue = text;
    this->_keyValue = key;
    this->_ivValue = iv;
}


string AexValue::Aes_128_CBC()
{
    unsigned char *plaintext = (unsigned char *)this->_plainTextValue.c_str();
    int plaintext_len =  strlen((char *)plaintext);
    unsigned char *key = (unsigned char *)this->_keyValue.c_str();
    unsigned char *iv = (unsigned char *)this->_ivValue.c_str();
    unsigned char ciphertext[1024];

    EVP_CIPHER_CTX *ctx;

    int len;

    int ciphertext_len;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
    {
        return string("");
    }

    /*
     * Initialise the encryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
    {
        return string("");
    }

    /*
     * Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_EncryptUpdate can be called multiple times if necessary
     */
    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    {

    }

    ciphertext_len = len;

    /*
     * Finalise the encryption. Further ciphertext bytes may be written at
     * this stage.
     */
    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
    {
        return string("");
    }
    ciphertext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);


    this->_result = string(reinterpret_cast<char*>(ciphertext));
    return _result;
}
