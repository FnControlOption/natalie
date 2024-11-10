#include "natalie.hpp"

namespace Natalie {

static const long WINDOWS1253[] = {
    0x20AC, 0x81, 0x201A, 0x192, 0x201E, 0x2026, 0x2020, 0x2021, 0x88, 0x2030,
    0x8A, 0x2039, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x2018, 0x2019, 0x201C,
    0x201D, 0x2022, 0x2013, 0x2014, 0x98, 0x2122, 0x9A, 0x203A, 0x9C, 0x9D,
    0x9E, 0x9F, 0xA0, 0x385, 0x386, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7,
    0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0x2015, 0xB0, 0xB1,
    0xB2, 0xB3, 0x384, 0xB5, 0xB6, 0xB7, 0x388, 0x389, 0x38A, 0xBB,
    0x38C, 0xBD, 0x38E, 0x38F, 0x390, 0x391, 0x392, 0x393, 0x394, 0x395,
    0x396, 0x397, 0x398, 0x399, 0x39A, 0x39B, 0x39C, 0x39D, 0x39E, 0x39F,
    0x3A0, 0x3A1, 0xD2, 0x3A3, 0x3A4, 0x3A5, 0x3A6, 0x3A7, 0x3A8, 0x3A9,
    0x3AA, 0x3AB, 0x3AC, 0x3AD, 0x3AE, 0x3AF, 0x3B0, 0x3B1, 0x3B2, 0x3B3,
    0x3B4, 0x3B5, 0x3B6, 0x3B7, 0x3B8, 0x3B9, 0x3BA, 0x3BB, 0x3BC, 0x3BD,
    0x3BE, 0x3BF, 0x3C0, 0x3C1, 0x3C2, 0x3C3, 0x3C4, 0x3C5, 0x3C6, 0x3C7,
    0x3C8, 0x3C9, 0x3CA, 0x3CB, 0x3CC, 0x3CD, 0x3CE, 0xFF

};

Windows1253EncodingObject::Windows1253EncodingObject()
    : SingleByteEncodingObject { Encoding::Windows_1253, { "Windows-1253", "CP1253" }, WINDOWS1253 } { }

}
