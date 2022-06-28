#include <string>
#include <sstream>

/*
 * https://www.codewars.com/kata/525f50e3b73515a6db000b83/train/cpp
 */

static char int_to_digit(int i);

std::string createPhoneNumber(const int arr[10]) {
    std::stringstream stream;

    stream.put('(');
    stream.put(int_to_digit(arr[0]));
    stream.put(int_to_digit(arr[1]));
    stream.put(int_to_digit(arr[2]));
    stream.put(')');

    stream.put(' ');

    stream.put(int_to_digit(arr[3]));
    stream.put(int_to_digit(arr[4]));
    stream.put(int_to_digit(arr[5]));

    stream.put('-');

    stream.put(int_to_digit(arr[6]));
    stream.put(int_to_digit(arr[7]));
    stream.put(int_to_digit(arr[8]));
    stream.put(int_to_digit(arr[9]));

    return stream.str();
}

static char int_to_digit(int i) {
    return (char) (i + '0');
}
