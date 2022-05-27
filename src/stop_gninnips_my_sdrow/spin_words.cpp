#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <algorithm>

class Join {
private:
    std::string delimiter;
    std::vector<std::string> strings;

    Join();

public:
    explicit Join(std::string delimiter);

    void append(const std::string &str);

    std::string build();
};

/**
 * https://www.codewars.com/kata/5264d2b162488dc400000001/train/cpp
 * @param str a string of one or more words
 * @return the same string, but with all five or more letter words reversed (Just like the name of this Kata)
 */
std::string spinWords(const std::string &str) {
    std::stringstream words(str);
    Join joiner = Join(" ");

    std::string word;
    while (words >> word) {
        if (word.length() >= 5) {
            reverse(word.begin(), word.end());
        }

        joiner.append(word);
    }

    return joiner.build();
}

Join::Join() {
    this->delimiter = "";
}

Join::Join(std::string delimiter) {
    this->delimiter = std::move(delimiter);
}

void Join::append(const std::string &str) {
    this->strings.push_back(str);
}

std::string Join::build() {
    std::string joined;

    size_t ultimo = strings.size() - 1;
    size_t index = 0;

    for (; index < ultimo; index++) {
        joined.append(this->strings[index]);
        joined.append(this->delimiter);
    }

    joined.append(this->strings[index]);

    return joined;
}
