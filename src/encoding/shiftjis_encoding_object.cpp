#include "natalie.hpp"

namespace Natalie {

// NATFIXME: actual implementation is wrong for much of this file
std::pair<bool, StringView> ShiftJisEncodingObject::prev_char(const String &string, size_t *index) const {
    if (*index == 0)
        return { true, StringView() };
    (*index)--;
    return { true, StringView(&string, *index, 1) };
}

std::pair<bool, StringView> ShiftJisEncodingObject::next_char(const String &string, size_t *index) const {
    size_t len = string.size();
    if (*index >= len)
        return { true, StringView() };
    size_t i = *index;
    int length = 0;
    unsigned char c = string[i];
    // Check the first byte and determine length.
    // Note that the lead byte can go up to 0xFC per JIS X 2013 extensions
    if ((c >= 0x81 && c <= 0x9F) || (c >= 0xE0 && c <= 0xFC)) {
        // first byte of two byte case, so expect another byte
        if (i + 1 >= len) { // missing 2nd byte, this is bad.
            *index = len;
            return { false, StringView(&string, i) };
        }
        // if we got here, it's a two-byte sequence.
        unsigned char c2 = string[i + 1];
        bool valid_2nd_byte = (c2 >= 0x40 && c2 != 0x7F && c2 <= 0xFC);
        if (valid_2nd_byte) {
            *index += 2;
            return { true, StringView(&string, i, 2) };
        } else {
            *index += 1;
            return { false, StringView(&string, i, 1) };
        }
    } else { // is a single byte char
        // first char above 0x80 but not in half-width katakana must be invalid
        bool valid_1st_byte = (c <= 0x7F || (c >= 0xA1 && c <= 0xDF));
        *index += 1;
        return { valid_1st_byte, StringView(&string, i, 1) };
    }
}

String ShiftJisEncodingObject::escaped_char(unsigned char c) const {
    char buf[5];
    snprintf(buf, 5, "\\x%02llX", (long long)c);
    return String(buf);
}

nat_int_t ShiftJisEncodingObject::to_unicode_codepoint(nat_int_t codepoint) const {
    if (codepoint >= 128)
        return -1;

    return codepoint;
}

nat_int_t ShiftJisEncodingObject::from_unicode_codepoint(nat_int_t codepoint) const {
    if (codepoint >= 128)
        return -1;

    return codepoint;
}

String ShiftJisEncodingObject::encode_codepoint(nat_int_t codepoint) const {
    return String((char)codepoint);
}

nat_int_t ShiftJisEncodingObject::decode_codepoint(StringView &str) const {
    switch (str.size()) {
    case 1:
        return (unsigned char)str[0];
    default:
        return -1;
    }
}

}
