#include <algorithm>
#include <array>
#include <vector>

#include <openssl/evp.h>

#include "base64.h"

/******************************************************************************
public utils
******************************************************************************/
std::string unite_lines(const std::string& text)
{
    std::string result = text;

    const std::array<char, 2> new_lines = { '\r', '\n' };

    size_t last_pos = 0;
    for (const char& ch : new_lines)
    {
        while ((last_pos = result.find(ch, last_pos + 1)) != std::string::npos)
        {
            result.erase(last_pos, 1);
        }
    }

    return result;
}

/******************************************************************************
private utils
******************************************************************************/
std::string base64_string_format(const std::string& text)
{
    std::string result = unite_lines(text);

    size_t max = result.length() / 64;
    max += max / 64;
    for (size_t i = 0; i <= max; ++i)
    {
        result.insert(i + 64 * i, 1, '\n');
    }

    return result;
}

/******************************************************************************
base64
******************************************************************************/
std::string base64_encode(const std::string& text)
{
    EVP_ENCODE_CTX ectx;
    size_t size = text.size() * 2;
    std::vector<unsigned char> out(size);
    int outlen = 0;
    size_t tlen = 0;

    EVP_EncodeInit(&ectx);
    EVP_EncodeUpdate(&ectx, out.data(), &outlen, (const unsigned char*)text.c_str(), text.size());
    tlen += outlen;
    EVP_EncodeFinal(&ectx, out.data() + tlen, &outlen);
    tlen += outlen;

    std::string str((char*)out.data(), tlen);

    return str;
}

std::string base64_decode(const std::string& text)
{
    std::string b64text = base64_string_format(text); // silly, but required

    EVP_ENCODE_CTX ectx;
    size_t size = b64text.size();

    std::vector<unsigned char> out(size);
    int outlen = 0;
    size_t tlen = 0;

    EVP_DecodeInit(&ectx);
    EVP_DecodeUpdate(&ectx, out.data(), &outlen, (const unsigned char*)b64text.c_str(), b64text.size());
    tlen += outlen;
    EVP_DecodeFinal(&ectx, out.data() + tlen, &outlen);
    tlen += outlen;

    std::string data((char*)out.data(), tlen);

    return data;
}
