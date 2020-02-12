#ifndef TEXTVALUE_H
#define TEXTVALUE_H

#include <QString>
#include <string>
#include <sstream>
#include <iomanip>

#include "openssl/sha.h"

using namespace std;

class TextValue
{

public:
    TextValue(QString text);
    TextValue(string text);
    QString GetText();
    void SetText(QString text);
    void SetText(string text);
    QString static base64_encode(const ::std::string &bindata);
    QString static TextToSha256(string text);
    string ToStdString();

private:
    string _textValue;

};

#endif // TEXTVALUE_H
