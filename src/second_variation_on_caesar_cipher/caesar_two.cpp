#include <string>
#include <utility>
#include <vector>
#include <cmath>
#include <sstream>

/**
 * https://www.codewars.com/kata/55084d3898b323f0aa000546/train/cpp
 * Version: 0.0.1
 * Changelog:
 *   - fix bug when shift is larger than 1 (not covered by Codewars tests!)
 */
class CaesarTwo {
public:
    static std::vector<std::string> encodeStr(const std::string &cleartext, int shift);

    static std::string decode(std::vector<std::string> &chunks);
};

class Ciphertext;

class Chunks {
private:
    static const int DEFAULT_AMOUNT = 5;

    std::vector<std::string> chunks;

    static std::vector<std::string> create_chunks(unsigned int chunksize, const std::string &text);

    explicit Chunks(std::vector<std::string> chunks) : chunks(std::move(chunks)) {}

public:

    [[nodiscard]] std::vector<std::string> to_vector() const;

    [[nodiscard]] Ciphertext join() const;

    static Chunks from(const std::string &text);

    static Chunks of(const std::vector<std::string> &strings);
};

class Prefix {
private:
    const int _shift;
    const std::string chars;

    Prefix(const int shift, std::string chars) : _shift(shift), chars(std::move(chars)) {}

public:
    static const unsigned int DEFAULT_SIZE = 2;

    [[nodiscard]] std::string to_string() const { return chars; }

    [[nodiscard]] int shift() const { return _shift; }

    static Prefix for_encryption(char first, int shift);

    static Prefix for_decryption(const std::string &ciphertext);
};

class Cleartext;

class Ciphertext {
private:
    const Prefix prefix;
    const std::string payload;
public:
    Ciphertext(Prefix prefix, std::string ciphertext) : prefix(std::move(prefix)), payload(std::move(ciphertext)) {}

    [[nodiscard]] Chunks to_chunks() const;

    [[nodiscard]] Cleartext decrypt() const;

    static Ciphertext from(const std::string &ciphertext);
};

class Cleartext {
private:
    const std::string _value;

    explicit Cleartext(std::string cleartext) : _value(std::move(cleartext)) {}

public:
    [[nodiscard]] Ciphertext encrypt_with(int shift) const;

    [[nodiscard]] std::string cleartext() const { return _value; }

    static Cleartext of(const std::string &cleartext) { return Cleartext(cleartext); }
};

std::vector<std::string> CaesarTwo::encodeStr(const std::string &cleartext, int shift) {
    return Cleartext::of(cleartext)
            .encrypt_with(shift)
            .to_chunks()
            .to_vector();
}

std::string CaesarTwo::decode(std::vector<std::string> &chunks) {
    return Chunks::of(chunks)
            .join()
            .decrypt()
            .cleartext();
}

class Caesars {
private:
    static const unsigned int ALPHABET_SIZE = 26;
public:
    static std::string encrypt(const std::string &cleartext, int shift) {
        std::stringstream encrypted;

        for (char c: cleartext) {
            encrypted << move(c, shift);
        }

        return encrypted.str();
    }

    static std::string decrypt(const std::string &cleartext, int shift) {
        return encrypt(cleartext, -shift);
    }

    static char move(char c, int shift) {
        char offset;

        if (std::islower(c)) {
            offset = 'a';
        } else if (std::isupper(c)) {
            offset = 'A';
        } else {
            return c;
        }

        return (char) ((c - offset + shift + ALPHABET_SIZE) % ALPHABET_SIZE + offset);
    }
};

/* *********************************************************************************************************************
 * Prefix implementation
 ******************************************************************************************************************** */

Prefix Prefix::for_encryption(const char first, const int shift) {
    char second = Caesars::move(first, shift);
    char chars[] = {
            (char) std::tolower(first),
            (char) std::tolower(second),
            '\0'
    };

    return {shift, chars};
}

Prefix Prefix::for_decryption(const std::string &ciphertext) {
    std::string chars = ciphertext.substr(0, DEFAULT_SIZE);
    int shift = chars.at(1) - chars.at(0);

    return {shift, chars};
}

/* *********************************************************************************************************************
 * Ciphertext implementation
 ******************************************************************************************************************** */

Chunks Ciphertext::to_chunks() const {
    std::string joined = this->prefix.to_string().append(this->payload);
    return Chunks::from(joined);
}

Ciphertext Ciphertext::from(const std::string &ciphertext) {
    Prefix prefix = Prefix::for_decryption(ciphertext);
    return {prefix, ciphertext.substr(Prefix::DEFAULT_SIZE)};
}

Cleartext Ciphertext::decrypt() const {
    const std::string &cleartext = Caesars::decrypt(payload, prefix.shift());

    return Cleartext::of(cleartext);
}

/* *********************************************************************************************************************
 * Chunks implementation
 ******************************************************************************************************************** */

std::vector<std::string> Chunks::to_vector() const {
    return chunks;
}

std::vector<std::string> Chunks::create_chunks(unsigned int chunksize, const std::string &text) {
    std::vector<std::string> chunks = {};
    std::string remaining = text;

    while (remaining.length() > 0) {
        std::string chunk = remaining.substr(0, chunksize);
        chunks.push_back(chunk);

        if (remaining.length() <= chunksize) {
            break;
        }

        remaining = remaining.substr(chunksize);
    }

    return chunks;
}

Chunks Chunks::from(const std::string &text) {
    auto chunksSize = (unsigned int) ceil((double) text.length() / (double) DEFAULT_AMOUNT);
    const std::vector<std::string> &chunks = create_chunks(chunksSize, text);

    return Chunks(chunks);
}

Chunks Chunks::of(const std::vector<std::string> &strings) {
    return Chunks(strings);
}

Ciphertext Chunks::join() const {
    std::string joined;

    for (const auto &chunk: this->chunks) {
        joined.append(chunk);
    }

    return Ciphertext::from(joined);
}

/* *********************************************************************************************************************
 * Plaintext implementation
 ******************************************************************************************************************** */

Ciphertext Cleartext::encrypt_with(const int shift) const {
    const std::string &ciphertext = Caesars::encrypt(this->_value, shift);
    const Prefix prefix = Prefix::for_encryption(this->_value.c_str()[0], shift);

    return {prefix, ciphertext};
}
