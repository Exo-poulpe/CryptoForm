#include "textvalue.h"

TextValue::TextValue(QString text)
{
    TextValue(text.toStdString());
}

TextValue::TextValue(string text)
{
    this->_textValue = text;
}

QString TextValue::GetText(){
    return QString::fromStdString(this->_textValue);
}
void TextValue::SetText(QString text){
    SetText(text.toStdString());
}
void TextValue::SetText(string text){
    this->_textValue = text;
}
string TextValue::ToStdString(){
    return this->GetText().toStdString();
}

QString TextValue::TextToSha256(string text)
{
    SHA256_CTX context;
    if(!SHA256_Init(&context))
    {

    }

    // Read file and update calculated SHA
    string tmp = text;
    char buf[1024];
    strncpy(buf, tmp.c_str(), sizeof(buf));
    if(!SHA256_Update(&context, buf, strlen(buf)))
    {

    }

    // Get Final SHA
    unsigned char result[SHA256_DIGEST_LENGTH];
    if(!SHA256_Final(result, &context))
    {

    }

    std::stringstream shastr;
    shastr << std::hex << std::setfill('0');
    for (const auto &byte: result)
    {
        shastr << std::setw(2) << (int)byte;
    }
    string value = shastr.str();

    return QString::fromStdString(value);
}

QString TextValue::base64_encode(const ::std::string &bindata)
{
    const char b64_table[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
   using ::std::string;
   using ::std::numeric_limits;

   if (bindata.size() > (numeric_limits<string::size_type>::max() / 4u) * 3u) {
      throw ::std::length_error("Converting too large a string to base64.");
   }

   const ::std::size_t binlen = bindata.size();
   // Use = signs so the end is properly padded.
   string retval((((binlen + 2) / 3) * 4), '=');
   ::std::size_t outpos = 0;
   int bits_collected = 0;
   unsigned int accumulator = 0;
   const string::const_iterator binend = bindata.end();

   for (string::const_iterator i = bindata.begin(); i != binend; ++i) {
      accumulator = (accumulator << 8) | (*i & 0xffu);
      bits_collected += 8;
      while (bits_collected >= 6) {
         bits_collected -= 6;
         retval[outpos++] = b64_table[(accumulator >> bits_collected) & 0x3fu];
      }
   }
   if (bits_collected > 0) { // Any trailing bits that are missing.
      assert(bits_collected < 6);
      accumulator <<= 6 - bits_collected;
      retval[outpos++] = b64_table[accumulator & 0x3fu];
   }
   assert(outpos >= (retval.size() - 2));
   assert(outpos <= retval.size());
   return QString::fromStdString(retval);
}
