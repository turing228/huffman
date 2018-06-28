#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <utility>
#include "gtest/gtest.h"

#include "../lib/headers/encode.h"
#include "../lib/headers/decode.h"

#include "../util/headers/file_encoder.h"
#include "../util/headers/file_decoder.h"
#include "../util/file_encoder.cpp"
#include "../util/file_decoder.cpp"

TEST(correctness_small, encode_decode_EMPTY_STRING) {
    encoder e;
    decoder d;

    std::string expected;

    std::string encoded = e.encode(expected);
    std::string decoded = d.decode(encoded);

    EXPECT_EQ(expected, decoded);
}

TEST(correctness_small, encode_decode_A) {
    encoder e;
    decoder d;

    std::string expected("A");

    std::string encoded = e.encode(expected);
    std::string decoded = d.decode(encoded);

    EXPECT_EQ(expected, decoded);
}

TEST(correctness_small, encode_decode_AB) {
    encoder e;
    decoder d;

    std::string expected("AB");

    std::string encoded = e.encode(expected);
    std::string decoded = d.decode(encoded);

    EXPECT_EQ(expected, decoded);
}

TEST(correctness_small, encode_decode_A_Translation) {
    encoder e;
    decoder d;

    std::string expected("A\n");

    std::string encoded = e.encode(expected);
    std::string decoded = d.decode(encoded);

    EXPECT_EQ(expected, decoded);
}

TEST(correctness_small, encode_decode_Translation_A) {
    encoder e;
    decoder d;

    std::string expected("\nA");

    std::string encoded = e.encode(expected);
    std::string decoded = d.decode(encoded);

    EXPECT_EQ(expected, decoded);
}

TEST(correctness_small, encode_decode_ABandTranslation) {
    encoder e;
    decoder d;

    std::string expected("AB\n");

    std::string encoded = e.encode(expected);
    std::string decoded = d.decode(encoded);

    EXPECT_EQ(expected, decoded);
}

TEST(correctness_small, encode_decode_A_Translation_B) {
    encoder e;
    decoder d;

    std::string expected("A\nB");

    std::string encoded = e.encode(expected);
    std::string decoded = d.decode(encoded);

    EXPECT_EQ(expected, decoded);
}

TEST(correctness_small, encode_decode_Translations) {
    encoder e;
    decoder d;

    std::string expected("\n\n\n");

    std::string encoded = e.encode(expected);
    std::string decoded = d.decode(encoded);

    EXPECT_EQ(expected, decoded);
}

TEST(correctness_medium, encode_decode_long1) {
    encoder e;
    decoder d;

    std::string expected("{1Oew|1;");

    std::string encoded = e.encode(expected);
    std::string decoded = d.decode(encoded);

    EXPECT_EQ(expected, decoded);
}

TEST(correctness_medium, encode_decode_long32) {
    encoder e;
    decoder d;

    std::string expected("7PSFSc$joZLwC5G3A~mWXVZ*onXJ1}zQ");

    std::string encoded = e.encode(expected);
    std::string decoded = d.decode(encoded);

    EXPECT_EQ(expected, decoded);
}

TEST(correctness_medium, encode_decode_long64) {
    encoder e;
    decoder d;

    std::string expected("uHaaiv}K2|$h8c8dyJhx%Aw7lskZQ8?jDQ3%vpuAzy*QKAG2vc||MR@DJ4w}9F4b");

    std::string encoded = e.encode(expected);
    std::string decoded = d.decode(encoded);

    EXPECT_EQ(expected, decoded);
}

TEST(correctness_random, encode_decode_short_alphabet) {
    for (size_t n = 0; n < 1000; ++n) {
        encoder e;
        decoder d;

        std::string expected;
        for (size_t i = 0; i < 100; ++i) {
            expected += (char) (65 + rand() % 20);
        }

        std::string encoded = e.encode(expected);
        std::string decoded = d.decode(encoded);

        EXPECT_EQ(expected, decoded);
    }
}

TEST(correctness_random, encode_decode_short) {
    for (size_t n = 0; n < 1000; ++n) {
        encoder e;
        decoder d;

        std::string expected;
        for (size_t i = 0; i < 10; ++i) {
            expected += (char) (rand() % 256);
        }

        std::string encoded = e.encode(expected);
        std::string decoded = d.decode(encoded);

        EXPECT_EQ(expected, decoded);
    }
}

TEST(correctness_random, encode_decode_medium) {
    for (size_t n = 0; n < 500; ++n) {
        encoder e;
        decoder d;

        std::string expected;
        for (size_t i = 0; i < 1000; ++i) {
            expected += (char) (rand() % 256);
        }

        std::string encoded = e.encode(expected);
        std::string decoded = d.decode(encoded);

        EXPECT_EQ(expected, decoded);
    }
}

TEST(correctness_random, encode_decode_large) {
    for (size_t n = 0; n < 300; ++n) {
        encoder e;
        decoder d;

        std::string expected;
        for (size_t i = 0; i < 10000; ++i) {
            expected += (char) (rand() % 256);
        }

        std::string encoded = e.encode(expected);
        std::string decoded = d.decode(encoded);

        EXPECT_EQ(expected, decoded);
    }
}

TEST(correctness_random, encode_decode_gigantic) {
    for (size_t n = 0; n < 10; ++n) {
        encoder e;
        decoder d;

        std::string expected;
        for (size_t i = 0; i < SIZE; ++i) {
            expected += (char) (rand() % 256);
        }

        std::string encoded = e.encode(expected);
        std::string decoded = d.decode(encoded);

        EXPECT_EQ(expected, decoded);
    }
}

TEST(correctness_files, encode_decode_empty) {
    std::string original = "empty";
    std::string encoded = "empty_e";
    std::string decoded = "empty_ed";

    encode(original, encoded);
    decode(encoded, decoded);

    std::ifstream cin(original);
    std::string original_string;
    getline(cin, original_string);

    std::ifstream cin2(decoded);
    std::string decoded_string;
    getline(cin2, decoded_string);

    EXPECT_EQ(original_string, decoded_string);

    remove(encoded.c_str());
    remove(decoded.c_str());
}

TEST(correctness_files, encode_decode_TESTS) {
    std::string original = "TESTS";
    std::string encoded = "TESTS_e";
    std::string decoded = "TESTS_ed";

    encode(original, encoded);
    decode(encoded, decoded);

    std::ifstream cin(original);
    std::string original_string;
    getline(cin, original_string);

    std::ifstream cin2(decoded);
    std::string decoded_string;
    getline(cin2, decoded_string);

    EXPECT_EQ(original_string, decoded_string);

    remove(encoded.c_str());
    remove(decoded.c_str());
}

TEST(correctness_files, encode_decode_8) {
    std::string original = "new_file";
    std::string encoded = "new_file_e";
    std::string decoded = "new_file_ed";

    encode(original, encoded);
    decode(encoded, decoded);

    std::ifstream cin(original);
    std::string original_string;
    getline(cin, original_string);

    std::ifstream cin2(decoded);
    std::string decoded_string;
    getline(cin2, decoded_string);

    EXPECT_EQ(original_string, decoded_string);

    remove(encoded.c_str());
    remove(decoded.c_str());
}

TEST(correctness_files, encode_decode_80) {
    std::string original = "new_file_80";
    std::string encoded = "new_file_80e";
    std::string decoded = "new_file_80ed";

    encode(original, encoded);
    decode(encoded, decoded);

    std::ifstream cin(original);
    std::string original_string;
    getline(cin, original_string);

    std::ifstream cin2(decoded);
    std::string decoded_string;
    getline(cin2, decoded_string);

    EXPECT_EQ(original_string, decoded_string);

    remove(encoded.c_str());
    remove(decoded.c_str());
}