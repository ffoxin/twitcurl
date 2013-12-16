#include <iomanip>
#include <sstream>

#include "urlencode.h"

std::string char2hex(char dec)
{
    std::stringstream hstream;
    hstream << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(dec);

    return hstream.str();
}

std::string urlencode(const std::string& url)
{
    std::string escaped;

    for (const char& ch : url)
    {
        if (('A' <= ch && ch <= 'Z') ||
            ('a' <= ch && ch <= 'z') ||
            ('0' <= ch && ch <= '9') ||
            (ch == '-' || ch == '_' || ch == '.' || ch == '~')
            )
        {
            escaped.append(&ch, 1);
        }
        else
        {
            escaped.append("%");
            escaped.append(char2hex(ch)); //converts char 255 to string "FF"
        }
    }

    return escaped;
}
