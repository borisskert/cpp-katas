#include <unordered_map>
#include <vector>
#include <string>
#include <cmath>

typedef std::unordered_map<std::string, double> stringdblmap;

/**
 * https://www.codewars.com/kata/5536a85b6ed4ee5a78000035/train/cpp
 */
class Tour {
public:
    static int
    tour(
            std::vector<std::string> &arrFriends,
            std::vector<std::vector<std::string>> &ftwns,
            stringdblmap &h
    );
};

std::unordered_map<std::string, std::string>
toMap(const std::vector<std::vector<std::string>> &twoDimArray) {
    std::unordered_map<std::string, std::string> map;

    for (const std::vector<std::string> &array: twoDimArray) {
        const std::string key = array[0];
        const std::string value = array[1];

        map.insert(std::pair(key, value));
    }

    return map;
}

template<typename T>
std::vector<T> valuesBy(const std::unordered_map<std::string, T> &map, const std::vector<std::string> &keys) {
    std::vector<T> values;

    for (const auto &key: keys) {
        auto found = map.find(key);

        if (found != map.end()) {
            const std::string &actualKey = found->first;
            const T &value = map.at(actualKey);
            values.push_back(value);
        }
    }

    return values;
}

double oppositeLeg(const double a, const double c) {
    return sqrt(c * c - a * a);
}

double granniesDistance(const std::vector<double> &distances) {
    double distance = distances[0];

    for (unsigned int index = 1; index < distances.size(); index++) {
        const double a = distances[index - 1];
        const double c = distances[index];

        distance += oppositeLeg(a, c);
    }

    return distance + distances[distances.size() - 1];
}

int Tour::tour(std::vector<std::string> &arrFriends, std::vector<std::vector<std::string>> &ftwns, stringdblmap &h) {
    const std::unordered_map<std::string, std::string> friendTowns = toMap(ftwns);
    const std::vector<std::string> &towns = valuesBy(friendTowns, arrFriends);
    const std::vector<double> &distances = valuesBy(h, towns);

    return (int)floor(granniesDistance(distances));
}
