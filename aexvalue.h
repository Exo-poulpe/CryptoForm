#ifndef AEXVALUE_H
#define AEXVALUE_H

#include "string"
#include "QString"

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/aes.h>
#include <openssl/sha.h>

#include "textvalue.h"

using namespace std;

class AexValue
{
public:
    AexValue(QString text,QString key,QString iv);
    AexValue(string text,string key,string iv);
    string Aes_128_CBC();
    void SetIv(QString iv);
    void SetKey(QString key);
private:
    string _plainTextValue;
    string _ivValue;
    string _keyValue;
    string _result;
};

#endif // AEXVALUE_H
