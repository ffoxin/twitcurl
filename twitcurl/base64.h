#ifndef BASE64_H
#define BASE64_H

#include <string>

std::string base64_encode(const std::string& text);
std::string base64_decode(const std::string& text);

#endif // BASE64_H
