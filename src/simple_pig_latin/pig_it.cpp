#include <vector>
#include <sstream>

namespace simple_pig_latin {
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
}

std::string pig_word(const std::string &word);

/**
 * https://www.codewars.com/kata/520b9d2ad5c005041100000f/train/cpp
 * @param str the puzzle input
 * @return a string moved the first letter of each word to the end of it, then add "ay" to the end of the word. Leave punctuation marks untouched.
 */
std::string pig_it(const std::string &str) {
    std::stringstream words(str);
    simple_pig_latin::Join joiner = simple_pig_latin::Join(" ");

    std::string word;
    while (words >> word) {
        std::string pigged = pig_word(word);
        joiner.append(pigged);
    }

    return joiner.build();
}

std::string pig_word(const std::string &word) {
    std::string head = word.substr(0, 1);

    if (std::string("!?.,").find(head) != std::string::npos) {
        return word;
    }

    std::string tail = word.substr(1);

    return tail.append(head).append("ay");
}

namespace simple_pig_latin {
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
}
