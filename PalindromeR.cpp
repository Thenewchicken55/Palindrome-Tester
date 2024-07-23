// palindromeR.cpp -- recursive palindrome tester
// c. 2015 A. Deeter

#include "PalindromeR.hpp"
#include <string>

namespace  { // anonymous namespace to prevent name collisions. Usually this would be encapsulated in its own file
// returns true if the character is a letter or a number, false otherwise
bool isAlphanumeric(char c)
    {
        std::string alphanumericCharacters = "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        return (alphanumericCharacters.find(c) != std::string::npos);
    }
}

// returns -1 if the string is a palindrome; otherwise returns 1
int PalindromeR::test_string(const std::string &s)
{
    std::string alphanumericString = ""; //contains only alphanumeric characters from string s

    for (int i = 0; i < s.length(); ++i)
    {
        if (isAlphanumeric(s[i]))
            alphanumericString += s[i];
    }

    // base case: string is empty or contains only one character, then it is a palindrome
    if (alphanumericString.length() <= 1)
        return -1;

    // recursive case: string is longer than one character and the first and last characters match
    if (toupper(alphanumericString[0]) == toupper(alphanumericString[alphanumericString.length() - 1]))
    {
        if (PalindromeR::test_string(alphanumericString.substr(1, alphanumericString.length() - 2)) < 0)
            return -1;
    }
    return 1;
}
