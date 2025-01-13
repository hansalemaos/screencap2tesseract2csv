#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <any>
#include <array>
#include <bitset>
#include <cctype>
#include <chrono>
#include <cmath>
#include <compare>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <deque>
// #include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <filesystem>
#include <fstream>
#include <functional>
// #include <getopt.h>
#include <initializer_list>
#include <iosfwd>
#include <iostream>
// #include <linux/input.h>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <ostream>
#include <queue>
#include <random>
#include <ranges>
#include <set>
#include <sstream>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <string_view>
// #include <sys/inotify.h>
// #include <sys/ioctl.h>
// #include <sys/poll.h>
#include <typeinfo>
#include <unistd.h>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>

#define MAX_32BIT_INT 2147483647
#define ADJUST_INDICES(start, end, len)                                                                                \
    if (end > len)                                                                                                     \
        end = len;                                                                                                     \
    else if (end < 0)                                                                                                  \
    {                                                                                                                  \
        end += len;                                                                                                    \
        if (end < 0)                                                                                                   \
            end = 0;                                                                                                   \
    }                                                                                                                  \
    if (start < 0)                                                                                                     \
    {                                                                                                                  \
        start += len;                                                                                                  \
        if (start < 0)                                                                                                 \
            start = 0;                                                                                                 \
    }

namespace arghelpers
{
static constexpr int64_t MAX_64BIT_INT = 9223372036854775807;
static constexpr double MAX_64BIT_INT_AS_DOUBLE = 9223372036854775807.0;
static constexpr std::string_view nan_string = "NotANumber";
static constexpr std::string_view integer_numbers_string_view = "0123456789";
static constexpr std::string_view float_numbers_string_view = "0123456789.";
static constexpr std::string_view hex_upper_letters_string_view = "0123456789ABCDEF";
static constexpr std::string_view hex_lower_letters_string_view = "0123456789abcdef";
static constexpr std::string_view prefix_0b = "0b";
static constexpr std::string_view prefix_01 = "01";
static constexpr std::string_view prefix_0x = "0x";
static constexpr std::string_view number_0 = "0";
static constexpr char integer_numbers[] = "0123456789";
static constexpr char float_numbers[] = "0123456789.";
static constexpr char hex_upper_letters[] = "0123456789ABCDEF";
static constexpr unsigned int FNV_PRIME = 16777619u;
static constexpr std::string_view bool1 = "True";
static constexpr std::string_view bool2 = "False";
static constexpr std::string_view bool3 = "true";
static constexpr std::string_view bool4 = "false";
static constexpr std::string_view bool5 = "0";
static constexpr std::string_view bool6 = "1";
static constexpr std::string_view bool7 = "TRUE";
static constexpr std::string_view bool8 = "FALSE";
static constexpr std::string_view emptystringview = "";
static constexpr std::string_view zero1 = "0";
static constexpr std::string_view zero2 = "0.0";
static constexpr std::string_view zero3 = ".0";
static constexpr std::string_view zero4 = "-0";
static constexpr std::string_view zero5 = "-0.0";
static constexpr std::string_view zero6 = "+0.0";
constexpr std::array<uint8_t, 256> array_ascii_replace_non_alphanumeric = {
    32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,
    32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,
    32,  32,  32,  32,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  32,  32,  32,  32,  32,  32,  32,  65,
    66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86,  87,
    88,  89,  90,  32,  32,  32,  32,  32,  32,  97,  98,  99,  100, 101, 102, 103, 104, 105, 106, 107, 108, 109,
    110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 32,  32,  32,  32,  32,  32,  32,  32,  32,
    32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,
    32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,
    32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,
    32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,
    32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,
    32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32};

constexpr std::array<uint8_t, 256> array_ascii_replace_non_printable = {
    32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,
    32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,
    44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,
    66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86,  87,
    88,  89,  90,  91,  92,  93,  94,  95,  96,  97,  98,  99,  100, 101, 102, 103, 104, 105, 106, 107, 108, 109,
    110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 32,  32,  32,  32,  32,
    32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,
    32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,
    32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,
    32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,
    32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,
    32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32};
constexpr std::array<uint8_t, 256> array_ascii_replace_non_numeric = {
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 0-15
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 16-31
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 32-47
    48, 49, 50, 51, 52, 53, 54, 55, 56, 57,                         // 48-57 (digits '0'-'9')
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 58-73
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 74-89
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 90-105
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 106-121
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 122-137
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 138-153
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 154-169
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 170-185
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 186-201
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 202-217
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 218-233
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32  // 234-255
};
constexpr std::array<uint8_t, 256> array_ascii_replace_non_numeric_float = {
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 0-15
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 16-31
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 46, 32, // 32-47
    48, 49, 50, 51, 52, 53, 54, 55, 56, 57,                         // 48-57 (digits '0'-'9')
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 58-73
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 74-89
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 90-105
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 106-121
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 122-137
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 138-153
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 154-169
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 170-185
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 186-201
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 202-217
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 218-233
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32  // 234-255
};

constexpr std::array<uint8_t, 256> array_ascii_replace_non_numeric_float_with_comma = {
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 0-15
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 16-31
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 44, 32, 46, 32, // 32-47
    48, 49, 50, 51, 52, 53, 54, 55, 56, 57,                         // 48-57 (digits '0'-'9')
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 58-73
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 74-89
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 90-105
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 106-121
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 122-137
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 138-153
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 154-169
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 170-185
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 186-201
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 202-217
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 218-233
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32  // 234-255
};

static constexpr bool to_bool(const std::string_view s)
{

    if (s == bool1 || s == bool3 || s == bool6 || s == bool7)
    {
        return true;
    }
    return false;
}
static bool is_int_number(const std::string_view s)
{

    if (s.size() == 0)
    {
        return false;
    };
    if ((s.size() > 1) && ((s[0] == '-') || (s[0] == '+')) && ((s[1] != '-') && (s[1] != '+')))
    {
        return is_int_number(s.substr(1, s.size() - 1));
    }
    for (const char &i : s)
    {
        bool isnumber = false;
        for (const char &j : integer_numbers)
        {
            if (i == j)
            {
                isnumber = true;
                break;
            }
        }
        if (!isnumber)
        {
            return false;
        }
    }
    return true;
}
static bool is_float_number(const std::string_view s)
{
    if (s.size() == 0)
    {
        return false;
    };
    if ((s.size() > 1) && ((s[0] == '-') || (s[0] == '+')) && ((s[1] != '-') && (s[1] != '+')))
    {
        return is_float_number(s.substr(1, s.size() - 1));
    }
    size_t dotcounter = 0;
    for (const char &i : s)
    {
        bool isnumber = false;
        for (const char &j : float_numbers)
        {
            if (i == j)
            {
                if (i == '.')
                {
                    dotcounter += 1;
                    if (dotcounter > 1)
                    {
                        return false;
                    }
                }
                isnumber = true;
                break;
            }
        }
        if (!isnumber)
        {
            return false;
        }
    }
    return true;
}
static std::variant<double, int64_t> to_float_or_int(std::string_view s)
{
    std::variant<double, int64_t> returnvalue{};
    std::string tmpstring = std::string(s);
    if (is_int_number(s))
    {
        returnvalue = std::stoll(tmpstring);
    }
    else if (is_float_number(s))
    {
        returnvalue = std::stod(tmpstring);
    }
    return returnvalue;
}
bool check_if_string_is_valid_float_zero(const std::string_view str)
{

    if (is_float_number(str))
    {
        if (atof(str.data()) == 0)
        {
            return true;
        }
    }
    size_t strlen = str.size();
    if ((strlen > 1) && (str[0] == '+') && (is_float_number(str.substr(1, strlen - 1))))
    {
        return ((atof(&str.data()[1])) == 0);
    }
    if ((strlen > 1) && (str[0] == '-') && (is_float_number(str.substr(1, strlen - 1))))
    {
        return ((atof(&str.data()[1])) == 0);
    }
    return false;
}

bool check_if_string_is_valid_int_zero(const std::string_view str)
{

    if ((str == zero1) || (str == zero2) || (str == zero3) || (str == zero4) || (str == zero5) || (str == zero6))
    {
        return true;
    }

    size_t strlen = str.size();

    if (strlen == 0)
    {
        return false;
    }
    if ((strlen > 1) && (str[0] == '+') && (is_float_number(str.substr(1, strlen - 1))))
    {
        return (int(atof(&str.data()[1])) == 0);
    }
    if ((strlen > 1) && (str[0] == '-') && (is_float_number(str.substr(1, strlen - 1))))
    {
        return ((atof(&str.data()[1])) == 0);
    }
    if (is_int_number(str))
    {
        return (int(atof(str.data())) == 0);
    }

    if ((str[0] != '0') && (str[0] != '.'))
    {
        return false;
    }
    if ((str[0] == '.') && (strlen == 1))
    {
        return false;
    }

    if (str[0] == '.')
    {
        return is_int_number(str.substr(1, strlen - 1));
    }
    if ((str[0] == '0') && (strlen == 1))
    {
        return true;
    }
    if (is_float_number(str))
    {
        double tempdouble = atof(str.data());
        return (tempdouble < 1) && (tempdouble >= 0);
    }
    return false;
}
int64_t convert_to_int_at_any_cost(const std::string_view _sv, int64_t nan_value)
{
    std::variant<double, int64_t> tmpvalue = to_float_or_int(_sv);
    int64_t tmpnumber;
    try
    {
        tmpnumber = std::get<int64_t>(tmpvalue);
    }
    catch (...)
    {
        try
        {
            tmpnumber = (int64_t)(std::get<double>(tmpvalue));
        }
        catch (...)
        {
            // do nothing
        }
    }

    if (tmpnumber != 0)
    {
        return tmpnumber;
    }
    if ((tmpnumber == 0) && (check_if_string_is_valid_int_zero(_sv)))
    {
        return 0;
    }

    return nan_value;
}
double convert_to_double_at_any_cost(const std::string_view _sv, double nan_value)
{
    std::variant<double, int64_t> tmpvalue = to_float_or_int(_sv);
    double tmpnumber;
    try
    {
        tmpnumber = std::get<double>(tmpvalue);
    }
    catch (...)
    {
        try
        {
            tmpnumber = (double)(std::get<int64_t>(tmpvalue));
        }
        catch (...)
        {
            // do nothing
        }
    }
    if (tmpnumber != 0)
    {
        return tmpnumber;
    }
    if ((tmpnumber == 0) && (check_if_string_is_valid_float_zero(_sv)))
    {
        return 0;
    }

    return nan_value;
}
static constexpr bool is_hex_notation_upper_with_0x(const std::string_view input)
{
    return input.compare(0, 2, prefix_0x) == 0 && input.size() > 2 &&
           (input.find_first_not_of(hex_upper_letters_string_view, 2) == std::string_view::npos);
}
static constexpr bool is_hex_notation_upper_without_0x(const std::string_view input)
{
    return input.size() > 0 && (input.find_first_not_of(hex_upper_letters_string_view, 2) == std::string_view::npos);
}
static constexpr bool is_hex_notation_lower_with_0x(const std::string_view input)
{
    return input.compare(0, 2, prefix_0x) == 0 && input.size() > 2 &&
           (input.find_first_not_of(hex_lower_letters_string_view, 2) == std::string_view::npos);
}
static constexpr bool is_hex_notation_lower_without_0x(const std::string_view input)
{
    return input.size() > 0 && (input.find_first_not_of(hex_lower_letters_string_view, 2) == std::string_view::npos);
}
static std::string normalize_whitespaces(const std::string_view &invecj)
{
    std::string outvecj;
    outvecj.reserve(invecj.size());
    int last_whitespace_counter = 1;
    for (size_t i = 0; i < invecj.size(); i++)
    {
        if ((last_whitespace_counter == 0) && ((invecj[i] == ' ') || (invecj[i] == '\t') || (invecj[i] == '\n') ||
                                               (invecj[i] == '\r') || (invecj[i] == '\v') || (invecj[i] == '\f')))
        {
            outvecj += ' ';
            last_whitespace_counter += 1;
            continue;
        }
        else if ((last_whitespace_counter != 0) && ((invecj[i] == ' ') || (invecj[i] == '\t') || (invecj[i] == '\n') ||
                                                    (invecj[i] == '\r') || (invecj[i] == '\v') || (invecj[i] == '\f')))
        {
            last_whitespace_counter += 1;
            continue;
        }
        last_whitespace_counter = 0;
        outvecj += invecj[i];
    }
    if ((!outvecj.empty()) && (outvecj.back() == ' '))
    {
        outvecj.resize(outvecj.size() - 1);
    }

    return outvecj;
}
std::string remove_whitespaces(const std::string_view invecj)
{
    std::string outvecj;
    outvecj.reserve(invecj.size());
    for (size_t i = 0; i < invecj.size(); i++)
    {
        if ((invecj[i] == ' ') || (invecj[i] == '\t') || (invecj[i] == '\n') || (invecj[i] == '\r') ||
            (invecj[i] == '\v') || (invecj[i] == '\f'))
        {
            continue;
        }
        outvecj += invecj[i];
    }

    return outvecj;
}
std::string replace_fu(const std::string_view s, int op)
{
    std::string outv;
    outv.reserve(s.size());
    auto siterstart = s.begin();
    auto siterend = s.end();
    if (op == 0)
    {
        while (siterstart != siterend)
        {
            outv += (array_ascii_replace_non_alphanumeric[*siterstart++]);
        }
    }
    else if (op == 1)
    {
        while (siterstart != siterend)
        {
            outv += (array_ascii_replace_non_printable[*siterstart++]);
        }
    }
    else if (op == 2)
    {
        while (siterstart != siterend)
        {
            outv += (array_ascii_replace_non_numeric[*siterstart++]);
        }
    }
    else if (op == 3)
    {
        while (siterstart != siterend)
        {
            outv += (array_ascii_replace_non_numeric_float[*siterstart++]);
        }
    }
    else if (op == 4)
    {
        while (siterstart != siterend)
        {
            outv += (array_ascii_replace_non_numeric_float_with_comma[*siterstart++]);
        }
    }
    return outv;
}

std::string replace_non_alphanumeric_with_spaces(std::string_view _sv)
{
    return replace_fu(_sv, 0);
}
std::string replace_non_printable_with_spaces(std::string_view _sv)
{
    return replace_fu(_sv, 1);
}
std::string replace_non_decimal_with_spaces(std::string_view _sv)
{
    return replace_fu(_sv, 2);
}
std::string replace_non_float_with_spaces(std::string_view _sv)
{
    return replace_fu(_sv, 3);
}
std::string replace_non_float_with_spaces_and_comma(std::string_view _sv)
{
    return replace_fu(_sv, 4);
}
std::vector<std::pair<std::string, std::string>> parse_args_to_string_vector(int argc, char *argv[])
{
    std::vector<std::pair<std::string, std::string>> args;
    args.reserve(argc);
    for (size_t i{0}; i < argc; i++)
    {
        if (i == 0)
        {
            args.emplace_back(std::make_pair("__FILE__", std::string(argv[i])));
        }
        else
        {
            std::string tmpstring{argv[i]};
            size_t idxequal{tmpstring.find('=')};
            if (idxequal != std::string::npos && idxequal > 2)
            {
                args.emplace_back(std::make_pair(tmpstring.substr(2, idxequal - 2), tmpstring.substr(idxequal + 1)));
            }
            // args.push_back(std::make_pair(std::string(argv[i]), std::string(argv[i + 1])));
        }
    }
    return args;
}
static bool compare2strings(const std::string_view s1, const std::string_view s2)
{
    if (s1.size() != s2.size())
    {
        return false;
    }
    auto it1 = s1.begin();
    auto it2 = s2.begin();
    while (it1 != s1.end())
    {
        if (*it1 != *it2)
        {
            return false;
        }
        it1++;
        it2++;
    }
    return true;
}
static bool compare2strings(const char *s1, const std::string_view s2)
{
    const std::string_view s1view{s1};
    return compare2strings(s1view, s2);
}
static bool compare2strings(const char *s1, const char *s2)
{
    const std::string_view s1view{s1};
    const std::string_view s2view{s2};
    return compare2strings(s1view, s2view);
}
static bool compare2strings(const std::string_view s1, const char *s2)
{
    const std::string_view s2view{s2};
    return compare2strings(s1, s2view);
}

static std::vector<int64_t> parse_ints_to_vector(const std::string_view s, char delim = ',',
                                                 int64_t nan_value = MAX_64BIT_INT)
{
    std::vector<int64_t> result;
    result.reserve(s.size() / 4);
    auto strs = s | std::views::split(delim);
    for (const auto &ref : strs)
    {
        std::string_view sv{ref.begin(), ref.end()};
        result.emplace_back(convert_to_int_at_any_cost(sv, nan_value));
    }

    return result;
}
static std::vector<double> parse_doubles_to_vector(const std::string_view s, char delim = ',',
                                                   int64_t nan_value = MAX_64BIT_INT_AS_DOUBLE)
{
    std::vector<double> result;
    result.reserve(s.size() / 4);
    auto strs = s | std::views::split(delim);
    for (const auto &ref : strs)
    {
        std::string_view sv{ref.begin(), ref.end()};
        result.emplace_back(convert_to_double_at_any_cost(sv, nan_value));
    }
    return result;
}
static std::vector<std::pair<int64_t, int64_t>> parse_int_pairs_to_vector(const std::string_view s,
                                                                          int64_t nan_value = MAX_64BIT_INT)
{
    std::string s2{replace_non_float_with_spaces_and_comma(s)};
    std::string s3{normalize_whitespaces(s2)};
    std::vector<std::pair<int64_t, int64_t>> result;
    result.reserve(s.size() / 4);
    auto strs = s3 | std::views::split(' ');
    for (const auto &ref : strs)
    {
        std::string_view sv{ref.begin(), ref.end()};
        auto floatsnumbers = sv | std::views::split(',');
        size_t numbercounter = 0;
        int64_t firstvalueint = nan_value, secondvalueint = nan_value;
        for (const auto &ref2 : floatsnumbers)
        {
            std::string_view first_sv{ref2.begin(), ref2.end()};
            double firstvalue = convert_to_double_at_any_cost(first_sv, (double)nan_value);
            if (numbercounter == 0)
            {
                firstvalueint = (int64_t)firstvalue;
            }
            else if (numbercounter == 1)
            {
                secondvalueint = (int64_t)firstvalue;
            }
            numbercounter++;
        }
        result.emplace_back(std::make_pair(firstvalueint, secondvalueint));
    }
    return result;
}

static std::vector<std::pair<double, double>> parse_double_pairs_to_vector(const std::string_view s,
                                                                           double nan_value = MAX_64BIT_INT_AS_DOUBLE)
{
    std::string s2{replace_non_float_with_spaces_and_comma(s)};
    std::string s3{normalize_whitespaces(s2)};
    std::vector<std::pair<double, double>> result;
    result.reserve(s.size() / 4);
    auto strs = s3 | std::views::split(' ');
    for (const auto &ref : strs)
    {
        std::string_view sv{ref.begin(), ref.end()};
        auto floatsnumbers = sv | std::views::split(',');
        size_t numbercounter = 0;
        double firstvalueint = nan_value, secondvalueint = nan_value;
        for (const auto &ref2 : floatsnumbers)
        {
            std::string_view first_sv{ref2.begin(), ref2.end()};
            double firstvalue = convert_to_double_at_any_cost(first_sv, nan_value);
            if (numbercounter == 0)
            {
                firstvalueint = firstvalue;
            }
            else if (numbercounter == 1)
            {
                secondvalueint = firstvalue;
            }
            numbercounter++;
        }
        result.emplace_back(std::make_pair(firstvalueint, secondvalueint));
    }
    return result;
}
} // namespace arghelpers

static constexpr std::pair<bool, bool> check_if_start_parsing(const std::string_view l, bool do_first_check,
                                                              bool do_second_check)
{
    std::pair<bool, bool> result{};
    size_t s = l.size();
    // If you find "<body>" at the end of the line, set result.first = true
    if ((do_first_check) && (s >= 6) && (l[s - 1] == '>') && (l[s - 2] == 'y') && (l[s - 3] == 'd') &&
        (l[s - 4] == 'o') && (l[s - 5] == 'b') && (l[s - 6] == '<'))
    {
        result.first = true;
    }
    // If you find "</body>" at the end of the line, set result.second = true
    if ((do_second_check) && (s >= 7) && (l[s - 1] == '>') && (l[s - 2] == 'y') && (l[s - 3] == 'd') &&
        (l[s - 4] == 'o') && (l[s - 5] == 'b') && (l[s - 6] == '/') && (l[s - 7] == '<'))
    {
        result.second = true;
    }
    return result;
}

static void constexpr find_all_indices__and_replace_with_char(std::string &haystack, const std::string_view needle,
                                                              char c = ' ')
{
    std::vector<size_t> indices;
    size_t offset = 0;
    size_t newoffset = 0;
    size_t maxlen = haystack.size();
    for (;;)
    {
        newoffset = haystack.substr(offset, maxlen).find(needle);
        if (newoffset == std::string::npos)
            break;
        offset += newoffset;
        indices.push_back(offset);
        maxlen = haystack.size() - offset - needle.size();
        offset += needle.size();
    }
    for (auto i : indices)
    {
        for (size_t j = 0; j < needle.size(); j++)
        {
            haystack[i + j] = c;
        }
    }
}

typedef struct line_result
{
    std::string text;
    std::string title;
    std::string id;
    std::string lang;
    std::string clazz;
    std::string tag;
    std::string bbox;
    std::string baseline;
    std::string poly;
    std::string x_bboxes;
    std::string x_font;
    std::string x_fsize;
    std::string x_size;
    std::string x_ascenders;
    std::string x_descenders;
    std::string x_wconf;
    std::string x_confs;
    std::string x_mpconf;
    std::string line_conf;
    std::string char_conf;
    std::string ppageno;
    std::string block_num;
    std::string par_num;
    std::string line_num;
    std::string word_num;
    std::string image;
    std::string scan_res;
    std::string rotate;
    std::string x_line_bboxes;
    std::string x_line_confs;
    std::string x_text;
    int64_t line_index;
    std::vector<int64_t> children;
    std::vector<int64_t> parents;
    int64_t aa_start_x;
    int64_t aa_start_y;
    int64_t aa_end_x;
    int64_t aa_end_y;
    int64_t aa_center_x;
    int64_t aa_center_y;
    int64_t aa_width;
    int64_t aa_height;
    int64_t aa_area;
    double_t aa_w_h_relation;

} line_result;

std::string static vector_to_string(std::vector<int64_t> &vec)
{
    if (vec.empty())
    {
        return "()";
    }
    std::string result;
    result.reserve(vec.size() * 3 + 2);
    result += '(';
    for (const auto &str : vec)
    {
        result += std::to_string(str) + ',';
    }
    result += ')';
    return result;
}
static constexpr bool isspace_or_empty(const std::string_view str)
{
    if (str.size() == 0)
    {
        return true;
    }
    for (size_t i{}; i < str.size(); i++)
    {
        if (!::isspace(str[i]))
        {
            return false;
        }
    }
    return true;
}
static constexpr std::string_view delim_csv{"\",\""};
static constexpr std::string_view csv_header{
    "\"text\",\"title\",\"id\",\"lang\",\"clazz\",\"tag\",\"bbox\",\"baseline\",\"poly\",\"x_bboxes\",\"x_font\",\"x_"
    "fsize\",\"x_size\",\"x_ascenders\",\"x_descenders\",\"x_wconf\",\"x_confs\",\"x_mpconf\",\"line_conf\",\"char_"
    "conf\",\"ppageno\",\"block_num\",\"par_num\",\"line_num\",\"word_num\",\"image\",\"scan_res\",\"rotate\",\"x_line_"
    "bboxes\",\"x_line_confs\",\"x_text\",\"line_index\",\"children\",\"parents\",\"aa_start_x\",\"aa_start_y\",\"aa_"
    "end_x\",\"aa_end_y\",\"aa_center_x\",\"aa_center_y\",\"aa_width\",\"aa_height\",\"aa_area\",\"aa_w_h_"
    "relation\"\n"};

static std::string dump_struct_vector_as_csv(std::vector<line_result> &v)
{
    std::string outputstring;
    outputstring.reserve(v.size() * 256);
    outputstring.append(csv_header);
    for (line_result &it : v)
    {
        if (isspace_or_empty(it.id) && isspace_or_empty(it.title))
        {
            continue;
        }
        outputstring += '"';
        outputstring.append((it.text));
        outputstring.append(delim_csv);
        outputstring.append((it.title));
        outputstring.append(delim_csv);
        outputstring.append((it.id));
        outputstring.append(delim_csv);
        outputstring.append((it.lang));
        outputstring.append(delim_csv);
        outputstring.append((it.clazz));
        outputstring.append(delim_csv);
        outputstring.append((it.tag));
        outputstring.append(delim_csv);
        outputstring.append((it.bbox));
        outputstring.append(delim_csv);
        outputstring.append((it.baseline));
        outputstring.append(delim_csv);
        outputstring.append((it.poly));
        outputstring.append(delim_csv);
        outputstring.append((it.x_bboxes));
        outputstring.append(delim_csv);
        outputstring.append((it.x_font));
        outputstring.append(delim_csv);
        outputstring.append((it.x_fsize));
        outputstring.append(delim_csv);
        outputstring.append((it.x_size));
        outputstring.append(delim_csv);
        outputstring.append((it.x_ascenders));
        outputstring.append(delim_csv);
        outputstring.append((it.x_descenders));
        outputstring.append(delim_csv);
        outputstring.append((it.x_wconf));
        outputstring.append(delim_csv);
        outputstring.append((it.x_confs));
        outputstring.append(delim_csv);
        outputstring.append((it.x_mpconf));
        outputstring.append(delim_csv);
        outputstring.append((it.line_conf));
        outputstring.append(delim_csv);
        outputstring.append((it.char_conf));
        outputstring.append(delim_csv);
        outputstring.append((it.ppageno));
        outputstring.append(delim_csv);
        outputstring.append((it.block_num));
        outputstring.append(delim_csv);
        outputstring.append((it.par_num));
        outputstring.append(delim_csv);
        outputstring.append((it.line_num));
        outputstring.append(delim_csv);
        outputstring.append((it.word_num));
        outputstring.append(delim_csv);
        outputstring.append((it.image));
        outputstring.append(delim_csv);
        outputstring.append((it.scan_res));
        outputstring.append(delim_csv);
        outputstring.append((it.rotate));
        outputstring.append(delim_csv);
        outputstring.append((it.x_line_bboxes));
        outputstring.append(delim_csv);
        outputstring.append((it.x_line_confs));
        outputstring.append(delim_csv);
        outputstring.append((it.x_text));
        outputstring.append(delim_csv);
        outputstring.append(std::to_string(it.line_index));
        outputstring.append(delim_csv);
        outputstring.append(vector_to_string(it.children));
        outputstring.append(delim_csv);
        outputstring.append(vector_to_string(it.parents));
        outputstring.append(delim_csv);
        outputstring.append(std::to_string(it.aa_start_x));
        outputstring.append(delim_csv);
        outputstring.append(std::to_string(it.aa_start_y));
        outputstring.append(delim_csv);
        outputstring.append(std::to_string(it.aa_end_x));
        outputstring.append(delim_csv);
        outputstring.append(std::to_string(it.aa_end_y));
        outputstring.append(delim_csv);
        outputstring.append(std::to_string(it.aa_center_x));
        outputstring.append(delim_csv);
        outputstring.append(std::to_string(it.aa_center_y));
        outputstring.append(delim_csv);
        outputstring.append(std::to_string(it.aa_width));
        outputstring.append(delim_csv);
        outputstring.append(std::to_string(it.aa_height));
        outputstring.append(delim_csv);
        outputstring.append(std::to_string(it.aa_area));
        outputstring.append(delim_csv);
        outputstring.append(std::to_string(it.aa_w_h_relation));
        outputstring.append(delim_csv);
        outputstring += '"';
        outputstring += '\n';
    }
    return outputstring;
}
constexpr static bool is_digit(char c)
{
    return c <= '9' && c >= '0';
}

constexpr static int64_t satoll_impl(const char *str, int64_t value = 0)
{
    return *str ? is_digit(*str) ? satoll_impl(str + 1, (*str - '0') + value * 10) : 0 : value;
}

int64_t static constexpr myatoll(const std::string &str)
{
    return satoll_impl(str.c_str());
}

void static constexpr calculate_bounds(line_result &mystruct, std::array<std::string, 4> &resultcoords)
{
    int64_t aa_start_x_real = myatoll(resultcoords[0]);
    int64_t aa_start_y_real = myatoll(resultcoords[1]);
    int64_t aa_end_x_real = myatoll(resultcoords[2]);
    int64_t aa_end_y_real = myatoll(resultcoords[3]);
    mystruct.aa_start_x = aa_start_x_real;
    mystruct.aa_start_y = aa_start_y_real;
    mystruct.aa_end_x = aa_end_x_real;
    mystruct.aa_end_y = aa_end_y_real;
    mystruct.aa_center_x = (mystruct.aa_end_x + mystruct.aa_start_x) / 2;
    mystruct.aa_center_y = (mystruct.aa_end_y + mystruct.aa_start_y) / 2;
    mystruct.aa_width = (mystruct.aa_end_x - mystruct.aa_start_x);
    mystruct.aa_height = (mystruct.aa_end_y - mystruct.aa_start_y);
    mystruct.aa_area = mystruct.aa_width * mystruct.aa_height;
    if (!mystruct.aa_height)
    {
        return;
    }
    mystruct.aa_w_h_relation = (double_t)(mystruct.aa_width) / (double_t)(mystruct.aa_height);
}
void static constexpr ltrim_space(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch); }));
}

void static constexpr rtrim_space(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
}

void static constexpr rtrim_space_and_semicolon(std::string &s)
{
    s.erase(
        std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return (!std::isspace(ch) && ch != ';'); }).base(),
        s.end());
}
void static constexpr rtrim_space_and_quotes(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         [](unsigned char ch) { return (!std::isspace(ch) && ch != '"' && ch != '\''); })
                .base(),
            s.end());
}
static constexpr std::string_view sv_bbox{"bbox"};
static constexpr std::string_view sv_baseline{"baseline"};
static constexpr std::string_view sv_poly{"poly"};
static constexpr std::string_view sv_x_bboxes{"x_bboxes"};
static constexpr std::string_view sv_x_font{"x_font"};
static constexpr std::string_view sv_x_fsize{"x_fsize"};
static constexpr std::string_view sv_x_size{"x_size"};
static constexpr std::string_view sv_x_ascenders{"x_ascenders"};
static constexpr std::string_view sv_x_descenders{"x_descenders"};
static constexpr std::string_view sv_x_wconf{"x_wconf"};
static constexpr std::string_view sv_x_confs{"x_confs"};
static constexpr std::string_view sv_x_mpconf{"x_mpconf"};
static constexpr std::string_view sv_line_conf{"line_conf"};
static constexpr std::string_view sv_char_conf{"char_conf"};
static constexpr std::string_view sv_ppageno{"ppageno"};
static constexpr std::string_view sv_block_num{"block_num"};
static constexpr std::string_view sv_par_num{"par_num"};
static constexpr std::string_view sv_line_num{"line_num"};
static constexpr std::string_view sv_word_num{"word_num"};
static constexpr std::string_view sv_image{"image"};
static constexpr std::string_view sv_scan_res{"scan_res"};
static constexpr std::string_view sv_rotate{"rotate"};
static constexpr std::string_view sv_x_line_bboxes{"x_line_bboxes"};
static constexpr std::string_view sv_x_line_confs{"x_line_confs"};
static constexpr std::string_view sv_x_text{"x_text"};
static constexpr std::string_view sv_class{"class"};
static constexpr std::string_view sv_id{"id"};
static constexpr std::string_view sv_lang{"lang"};

static int constexpr find(const std::string_view str, const std::string_view sub, int start = 0,
                          int end = MAX_32BIT_INT)
{
    ADJUST_INDICES(start, end, (int)str.size());
    std::string::size_type result = str.substr(0, end).find(sub, start);
    if (result == std::string::npos || (result + sub.size() > (std::string::size_type)end))
    {
        return -1;
    }
    return (int)result;
}

static std::string replace(const std::string_view str, const std::string_view oldstr, const std::string_view newstr,
                           int count)
{
    int sofar{};
    int cursor{};
    std::string s{str};
    std::string::size_type oldlen{oldstr.size()};
    std::string::size_type newlen{newstr.size()};
    cursor = find(s, oldstr, cursor);
    while (cursor != -1 && cursor <= (int)s.size())
    {
        if (count > -1 && sofar >= count)
        {
            break;
        }
        s.replace(cursor, oldlen, newstr);
        cursor += (int)newlen;
        if (oldlen != 0)
        {
            cursor = find(s, oldstr, cursor);
        }
        else
        {
            ++cursor;
        }
        ++sofar;
    }
    return s;
}

static constexpr bool startswith(const std::string_view haystack, const std::string_view needle)
{
    if (haystack.size() < needle.size())
    {
        return false;
    }
    for (size_t i = 0; i < needle.size(); i++)
    {
        if (haystack[i] != needle[i])
        {
            return false;
        }
    }
    return true;
}

std::string static get_string_ready(const std::string_view ref, size_t indexstart)
{
    std::string tmpsubstr{ref.substr(indexstart)};
    find_all_indices__and_replace_with_char(tmpsubstr, "'", ' ');
    ltrim_space(tmpsubstr);
    rtrim_space(tmpsubstr);
    return tmpsubstr;
}

static constexpr std::array<char, 10> all_numbers_as_chars{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

static constexpr void set_bounds_array_to_0(std::array<std::string, 4> &boundsarray)
{

    for (int i = 0; i < 4; i++)
    {
        boundsarray[i].clear();
        boundsarray[i] += '0';
    }
}
static void constexpr parse_my_coords(const std::string_view s, std::array<std::string, 4> &resultstringarray)
{

    resultstringarray[0].clear();
    resultstringarray[1].clear();
    resultstringarray[2].clear();
    resultstringarray[3].clear();
    size_t current_idx{};
    for (size_t i = 0; i < s.size(); i++)
    {
        if (s[i] == ' ')
        {
            current_idx++;
        }
        else
        {
            resultstringarray[current_idx] += s[i];
        }
    }
}
bool static constexpr is_rect_in_rect(const std::array<int64_t, 4> &rect1, const std::array<int64_t, 4> &rect2)
{

    return (rect1[0] >= rect2[0] && rect1[1] >= rect2[1] && rect1[2] <= rect2[2] && rect1[3] <= rect2[3]);
}

int static convert_screencap_c(const char *cmd, const char *filename2, int width, int height, int max_color_value)
{
    FILE *f{popen(cmd, "r")};
    if (!f)
    {
        std::cerr << "Error opening pipe" << std::endl;
        return 1;
    }
    FILE *f2{fopen(filename2, "wb")};

    if (!f2)
    {
        std::cerr << "Error opening file" << std::endl;
        fclose(f);
        return 1;
    }
    size_t size_my_buffer{(size_t)width * height * 4 + 17};
    fprintf(f2, "P6\n%d %d\n%d\n", width, height, max_color_value);
    char *buffer{new char[size_my_buffer]};
    if (!buffer)
    {
        std::cerr << "Error allocating buffer" << std::endl;
        fclose(f);
        fclose(f2);
        return 1;
    }
    fread(buffer, size_my_buffer, 1, f);
    for (size_t j{}; j < size_my_buffer - 1; j++)
    {
        if (((j + 1) % 4 == 0) || (j < 16))
        {
            continue;
        }
        fputc(buffer[j], f2);
    }
    pclose(f);
    fclose(f2);
    delete[] buffer;
    return 0;
}

typedef struct parsed_args
{

    std::string this_file;
    std::string path_screencap;
    std::string path_outpic;
    std::string path_outpic_filtered;
    std::string path_outhorc;
    std::string path_exe_tesseract;
    std::string path_exe_imagemagick;
    std::string tesseract_args;
    std::string imagemagick_args;
    std::string cmd_delete_outpic;
    std::string cmd_delete_outpic_filtered;
    std::string cmd_delete_outhorc;
    std::string tessdata;
    int32_t delete_outpic;
    int32_t delete_outpic_filtered;
    int32_t delete_outhorc;
    int32_t width;
    int32_t height;
    bool _this_file;
    bool _path_screencap;
    bool _path_outpic;
    bool _path_outpic_filtered;
    bool _path_outhorc;
    bool _path_exe_tesseract;
    bool _path_exe_imagemagick;
    bool _tesseract_args;
    bool _imagemagick_args;
    bool _delete_outpic;
    bool _delete_outpic_filtered;
    bool _delete_outhorc;
    bool _width;
    bool _height;
    bool _tessdata;

} p_args;

static constexpr std::string_view On_IRed{"\033[0;101m"}; // Red
static constexpr std::string_view Color_Off{"\033[0m"};   // Text Reset
static constexpr std::string_view IYellow{"\033[0;93m"};  // Yellow
static constexpr std::string_view explanation_on_how_to_use_this_app{
    "Mandatory arguments: \n"
    "--width\n"
    "\tDescription: screen width\n"
    "--height\n"
    "\tDescription: screen height\n"
    "--tessdata\n"
    "\tDescription: folder with tessdata\n\n\n"
    "Optional arguments:\n"
    "--path_screencap\n"
    "\tDefault:     screencap\n"
    "\tDescription: Android screencap path\n"
    "--path_outpic\n"
    "\tDefault:     /sdcard/tesseractwithimagemagick.ppm\n"
    "\tDescription: Save path for screencap result as ppm file\n"
    "--path_outpic_filtered\n"
    "\tDefault:     /sdcard/tesseractwithimagemagickfiltered.ppm\n"
    "\tDescription: Save path for ImageMagick filtered screencap result as ppm file\n"
    "--path_outhorc\n"
    "\tDefault:     /sdcard/tesseractwithimagemagick\n"
    "\tDescription: Save path for tesseract result, without extension\n"
    "--path_exe_tesseract\n"
    "\tDefault:     /data/data/com.termux/files/usr/bin/tesseract\n"
    "\tDescription: tesseract path\n"
    "--path_exe_imagemagick\n"
    "\tDefault:     /data/data/com.termux/files/usr/bin/magick\n"
    "\tDescription: ImageMagick path\n"
    "--tesseract_args\n"
    "\tDefault:     \n"
    "\tDescription: aditional tesseract arguments, e.g. --tesseract_args=\"-l por+eng --oem 3\"\n"
    "--imagemagick_args\n"
    "\tDefault:     \n"
    "\tDescription: aditional ImageMagick arguments, e.g. --imagemagick_args=\"-colorspace LinearGray -normalize "
    "-auto-level -alpha "
    "deactivate  -adaptive-blur 1 -adaptive-sharpen 1 -trim -fuzz 60 -antialias -auto-gamma -auto-level "
    "-black-point-compensation -normalize -enhance -white-balance -antialias -black-threshold 4 -mean-shift 1x5+17%\"\n"
    "--delete_outpic\n"
    "\tDefault:     0\n"
    "\tDescription: Whether to delete screencap result or not\n"
    "--delete_outpic_filtered\n"
    "\tDefault:     0\n"
    "\tDescription: Whether to delete ImageMagick filtered screencap result or not\n"
    "--delete_outhorc\n"
    "\tDefault:     0\n"
    "\tDescription: Whether to delete tesseract result or not\n"};
void static throw_error(const std::string &msg, int exit_code)
{
    std::cerr << On_IRed << msg << Color_Off << '\n';
    std::cerr << IYellow << explanation_on_how_to_use_this_app << Color_Off << '\n';
    exit(exit_code);
}

void static check_if_not_bad_value(const auto v, const auto bad_value, const std::string &error_message)
{
    if (v == bad_value)
    {
        throw_error(error_message, 1);
    }
}

auto static parse_args(int argc, char *argv[])
{
    parsed_args myargs{};
    auto parsed_args_vec{arghelpers::parse_args_to_string_vector(argc, argv)};
    for (auto const &[key, value] : parsed_args_vec)
    {

        if (arghelpers::compare2strings(key, "__FILE__"))
        {
            myargs.this_file = value;
        }
        else if (arghelpers::compare2strings(key, "path_screencap"))
        {
            myargs.path_screencap = value;
            myargs._path_screencap = true;
        }
        else if (arghelpers::compare2strings(key, "path_outpic"))
        {
            myargs.path_outpic = value;
            myargs._path_outpic = true;
        }
        else if (arghelpers::compare2strings(key, "path_outpic_filtered"))
        {
            myargs.path_outpic_filtered = value;
            myargs._path_outpic_filtered = true;
        }
        else if (arghelpers::compare2strings(key, "path_outhorc"))
        {
            myargs.path_outhorc = value;
            myargs._path_outhorc = true;
        }
        else if (arghelpers::compare2strings(key, "path_exe_tesseract"))
        {
            myargs.path_exe_tesseract = value;
            myargs._path_exe_tesseract = true;
        }
        else if (arghelpers::compare2strings(key, "path_exe_imagemagick"))
        {
            myargs.path_exe_imagemagick = value;
            myargs._path_exe_imagemagick = true;
        }
        else if (arghelpers::compare2strings(key, "tesseract_args"))
        {
            std::string tmpstring{value};
            rtrim_space_and_quotes(tmpstring);
            myargs.tesseract_args = " " + tmpstring + " ";
            myargs._tesseract_args = true;
        }
        else if (arghelpers::compare2strings(key, "imagemagick_args"))
        {
            std::string tmpstring{value};
            rtrim_space_and_quotes(tmpstring);
            myargs.imagemagick_args = " " + tmpstring + " ";
            myargs._imagemagick_args = true;
        }
        else if (arghelpers::compare2strings(key, "tessdata"))
        {
            myargs.tessdata = value;
            myargs._tessdata = true;
        }

        else if (arghelpers::compare2strings(key, "width"))
        {
            auto width{arghelpers::convert_to_int_at_any_cost(value, arghelpers::MAX_64BIT_INT)};
            check_if_not_bad_value(width, arghelpers::MAX_64BIT_INT, "Invalid width");
            myargs.width = (int32_t)(width);
            myargs._width = true;
        }
        else if (arghelpers::compare2strings(key, "height"))
        {
            auto height{arghelpers::convert_to_int_at_any_cost(value, arghelpers::MAX_64BIT_INT)};
            check_if_not_bad_value(height, arghelpers::MAX_64BIT_INT, "Invalid height");
            myargs.height = (int32_t)(height);
            myargs._height = true;
        }
        else if (arghelpers::compare2strings(key, "delete_outpic"))
        {
            auto delete_outpic{arghelpers::convert_to_int_at_any_cost(value, arghelpers::MAX_64BIT_INT)};
            check_if_not_bad_value(delete_outpic, arghelpers::MAX_64BIT_INT, "Invalid delete_outpic");
            if (delete_outpic >= 1)
            {
                myargs.delete_outpic = 1;
            }
            myargs._delete_outpic = true;
        }
        else if (arghelpers::compare2strings(key, "delete_outpic_filtered"))
        {
            auto delete_outpic_filtered{arghelpers::convert_to_int_at_any_cost(value, arghelpers::MAX_64BIT_INT)};
            check_if_not_bad_value(delete_outpic_filtered, arghelpers::MAX_64BIT_INT, "Invalid delete_outpic_filtered");
            if (delete_outpic_filtered >= 1)
            {
                myargs.delete_outpic_filtered = 1;
            }
            myargs._delete_outpic_filtered = true;
        }
        else if (arghelpers::compare2strings(key, "delete_outhorc"))
        {
            auto delete_outhorc{arghelpers::convert_to_int_at_any_cost(value, arghelpers::MAX_64BIT_INT)};
            check_if_not_bad_value(delete_outhorc, arghelpers::MAX_64BIT_INT, "Invalid delete_outhorc");
            if (delete_outhorc >= 1)
            {
                myargs.delete_outhorc = 1;
            }
            myargs._delete_outhorc = true;
        }
    }
    if (!myargs._width)
    {
        throw_error("Missing width", EXIT_FAILURE);
    }
    if (!myargs._height)
    {
        throw_error("Missing height", EXIT_FAILURE);
    }
    if (!myargs._tessdata)
    {
        throw_error("Missing tessdata folder", EXIT_FAILURE);
    }

    if (!myargs._path_screencap)
    {
        myargs.path_screencap = "screencap";
    }
    if (!myargs._path_outpic)
    {
        myargs.path_outpic = "/sdcard/tesseractwithimagemagick.ppm";
    }
    if (!myargs._path_outpic_filtered)
    {
        myargs.path_outpic_filtered = "/sdcard/tesseractwithimagemagickfiltered.ppm";
    }
    if (!myargs._path_outhorc)
    {
        myargs.path_outhorc = "/sdcard/tesseractwithimagemagick";
    }
    if (!myargs._path_exe_tesseract)
    {
        myargs.path_exe_tesseract = "/data/data/com.termux/files/usr/bin/tesseract";
    }
    if (!myargs._path_exe_imagemagick)
    {
        myargs.path_exe_imagemagick = "/data/data/com.termux/files/usr/bin/magick";
    }
    if (!myargs._tesseract_args)
    {
        myargs.tesseract_args = "";
    }
    if (!myargs._imagemagick_args)
    {
        myargs.imagemagick_args = "";
    }
    if (!myargs._delete_outpic)
    {
        myargs.delete_outpic = 0;
    }
    if (!myargs._delete_outpic_filtered)
    {
        myargs.delete_outpic_filtered = 0;
    }
    if (!myargs._delete_outhorc)
    {
        myargs.delete_outhorc = 0;
    }
    if (myargs.delete_outpic)
    {
        myargs.cmd_delete_outpic = "rm -f " + myargs.path_outpic;
    }
    if (myargs.delete_outpic_filtered)
    {
        myargs.cmd_delete_outpic_filtered = "rm -f " + myargs.path_outpic_filtered;
    }
    if (myargs.delete_outhorc)
    {
        myargs.cmd_delete_outhorc = "rm -f " + myargs.path_outhorc;
    }
    return myargs;
}

void static cleanup(parsed_args &myargs)
{
    if (myargs.delete_outpic)
    {
        system(myargs.cmd_delete_outpic.c_str());
    }
    if (myargs.delete_outpic_filtered)
    {
        system(myargs.cmd_delete_outpic_filtered.c_str());
    }
    if (myargs.delete_outhorc)
    {
        system(myargs.cmd_delete_outhorc.c_str());
    }
}
static constexpr std::string_view thread_limiter{
    "export OMP_THREAD_LIMIT=1;export MAGICK_THREAD_LIMIT=1;export KMP_ALL_THREADS=1;export "
    "KMP_TEAMS_THREAD_LIMIT=1;export OMP_THREAD_LIMIT=1;export KMP_DEVICE_THREAD_LIMIT=1;"};
static constexpr std::string_view important_tesser_args{"-c tessedit_create_hocr=1 -c hocr_font_info=1"};

std::string static construct_tesser_act_cmd(const parsed_args &myargs)
{
    std::string tesseract_cmd;
    tesseract_cmd.reserve(256);
    tesseract_cmd.append(thread_limiter);
    tesseract_cmd.append("export TESSDATA_PREFIX=");
    tesseract_cmd.append(myargs.tessdata);
    tesseract_cmd += ';';
    tesseract_cmd.append(myargs.path_exe_tesseract + " ");
    if (myargs._imagemagick_args)
    {
        tesseract_cmd.append(myargs.path_outpic_filtered);
    }
    else
    {
        tesseract_cmd.append(myargs.path_outpic);
    }
    tesseract_cmd.append(" " + myargs.path_outhorc + myargs.tesseract_args);

    tesseract_cmd.append(important_tesser_args);
    tesseract_cmd.append(" 2>/dev/null");
    return tesseract_cmd;
}

int main(int argc, char *argv[])
{
    parsed_args myargs{parse_args(argc, argv)};

    convert_screencap_c(myargs.path_screencap.c_str(), myargs.path_outpic.c_str(), myargs.width, myargs.height, 255);
    std::string tesseract_cmd{construct_tesser_act_cmd(myargs)};
    std::string imagemagick_cmd{thread_limiter};
    std::cerr << tesseract_cmd << std::endl;
    if (myargs._imagemagick_args)
    {
        imagemagick_cmd.append(myargs.path_exe_imagemagick);
        imagemagick_cmd += ' ';
        imagemagick_cmd.append(myargs.path_outpic);
        imagemagick_cmd += ' ';
        imagemagick_cmd.append(myargs.imagemagick_args);
        imagemagick_cmd += ' ';
        imagemagick_cmd.append(myargs.path_outpic_filtered);
        imagemagick_cmd += ' ';
        std::cerr << imagemagick_cmd << std::endl;
        system(imagemagick_cmd.c_str());
    }
    system(tesseract_cmd.c_str());
    std::string my_file{myargs.path_outhorc + ".hocr"};
    std::ifstream ifs(my_file);
    if (!ifs.is_open())
    {
        std::cerr << "Error opening file: " << my_file << '\n';
        cleanup(myargs);
        return EXIT_FAILURE;
    }

    std::string dumpstringgetline;
    dumpstringgetline.reserve(8192);
    std::vector<std::string> resultvec;
    resultvec.reserve(2048);

    bool startparsing{false};
    std::pair<bool, bool> parsingchecker{};
    bool do_first_check{true};
    bool do_second_check{false};

    size_t index_counter = 0;

    while (std::getline(ifs, dumpstringgetline))
    {

        if (!dumpstringgetline.empty() && dumpstringgetline.back() == '\n')
        {
            dumpstringgetline.pop_back();
        }
        if (!dumpstringgetline.empty() && dumpstringgetline.back() == '\r')
        {
            dumpstringgetline.pop_back();
        }
        if (isspace_or_empty(dumpstringgetline))
        {
            continue;
        }
        // Check for <body> or </body>
        parsingchecker = check_if_start_parsing(dumpstringgetline, do_first_check, do_second_check);
        if (parsingchecker.first)
        {
            startparsing = true;
            do_first_check = false;
            do_second_check = true;
        }
        else if (parsingchecker.second)
        {
            startparsing = false;
            do_first_check = false;
            do_second_check = false;
            if (!resultvec.empty())
            {
                // remove line containing "</body>"
                resultvec.pop_back();
            }
        }

        // If inside <body>...</body>, store line + find tags
        if (startparsing)
        {
            resultvec.emplace_back(dumpstringgetline);
        }
    }
    ifs.close();

    static constexpr std::array<std::string_view, 9> split_attributes{
        "</div>", "<div>", "<div ", "</p>", "<p>", "<p ", "</span>", "<span>", "<span ",
    };
    static constexpr std::array<std::string_view, 5> new_line_at{" class='", " id='", " lang='", " title='", " text='"};
    static constexpr std::string_view sv_class_eq{"class='"};
    static constexpr std::string_view sv_id_eq{"id='"};
    static constexpr std::string_view sv_lang_eq{"lang='"};
    static constexpr std::string_view sv_title_eq{"title='"};
    static constexpr std::string_view sv_text_eq{"text='"};
    static constexpr std::string_view sv_semicol_and_space{"; "};
    std::array<std::string, 4> boundsarray{};
    boundsarray[0].reserve(6);
    boundsarray[1].reserve(6);
    boundsarray[2].reserve(6);
    boundsarray[3].reserve(6);
    std::vector<line_result> line_resultvec;
    line_resultvec.resize(resultvec.size());
    for (size_t i{}; i < resultvec.size(); i++)
    {
        for (const std::string_view sv : split_attributes)
        {
            find_all_indices__and_replace_with_char(resultvec[i], sv);
        }
        find_all_indices__and_replace_with_char(resultvec[i], "\"", '\'');
        resultvec[i] = replace(resultvec[i], ">", " text='", -1);
        for (const std::string_view sv : new_line_at)
        {
            for (;;)
            {
                size_t index_of_str{resultvec[i].find(sv)};
                if (index_of_str != std::string::npos)
                {
                    resultvec[i][index_of_str] = '\n';
                }
                else
                {
                    break;
                }
            }
        }
        auto strs{resultvec[i] | std::views::split('\n')};
        for (const auto &refr : strs)
        {
            std::string_view ref{refr.begin(), refr.end()};
            size_t index_check{ref.find(sv_class_eq)};
            if (index_check != std::string_view::npos)
            {
                line_resultvec[i].clazz = get_string_ready(ref, index_check + sv_class_eq.size());
                continue;
            }
            index_check = ref.find(sv_id_eq);
            if (index_check != std::string_view::npos)
            {
                line_resultvec[i].id = get_string_ready(ref, index_check + sv_id_eq.size());
                continue;
            }

            index_check = ref.find(sv_lang_eq);
            if (index_check != std::string_view::npos)
            {
                line_resultvec[i].lang = get_string_ready(ref, index_check + sv_lang_eq.size());
                continue;
            }

            index_check = ref.find(sv_title_eq);
            if (index_check != std::string_view::npos)
            {
                line_resultvec[i].title = get_string_ready(ref, index_check + sv_title_eq.size());
                find_all_indices__and_replace_with_char(line_resultvec[i].title, sv_semicol_and_space, '\n');
                auto strssub{line_resultvec[i].title | std::views::split('\n')};
                std::string newtmpstring;
                for (const auto &refrsub : strssub)
                {
                    std::string_view refsub{refrsub.begin(), refrsub.end()};
                    if (!isspace_or_empty(refsub))
                    {
                        newtmpstring.append(refsub);
                        newtmpstring.append("|");
                        if (startswith(refsub, sv_bbox))
                        {
                            line_resultvec[i].bbox = get_string_ready(refsub, sv_bbox.size() + 1);
                            parse_my_coords(line_resultvec[i].bbox, boundsarray);
                            calculate_bounds(line_resultvec[i], boundsarray);
                            continue;
                        }
                        if (startswith(refsub, sv_baseline))
                        {
                            line_resultvec[i].baseline = get_string_ready(refsub, sv_baseline.size() + 1);
                            continue;
                        }
                        if (startswith(refsub, sv_poly))
                        {
                            line_resultvec[i].poly = get_string_ready(refsub, sv_poly.size() + 1);
                            continue;
                        }
                        if (startswith(refsub, sv_x_bboxes))
                        {
                            line_resultvec[i].x_bboxes = get_string_ready(refsub, sv_x_bboxes.size() + 1);
                            continue;
                        }
                        if (startswith(refsub, sv_x_font))
                        {
                            line_resultvec[i].x_font = get_string_ready(refsub, sv_x_font.size() + 1);
                            continue;
                        }
                        if (startswith(refsub, sv_x_fsize))
                        {
                            line_resultvec[i].x_fsize = get_string_ready(refsub, sv_x_fsize.size() + 1);
                            continue;
                        }
                        if (startswith(refsub, sv_x_size))
                        {
                            line_resultvec[i].x_size = get_string_ready(refsub, sv_x_size.size() + 1);
                            continue;
                        }
                        if (startswith(refsub, sv_x_ascenders))
                        {
                            line_resultvec[i].x_ascenders = get_string_ready(refsub, sv_x_ascenders.size() + 1);
                            continue;
                        }
                        if (startswith(refsub, sv_x_descenders))
                        {
                            line_resultvec[i].x_descenders = get_string_ready(refsub, sv_x_descenders.size() + 1);
                            continue;
                        }
                        if (startswith(refsub, sv_x_wconf))
                        {
                            line_resultvec[i].x_wconf = get_string_ready(refsub, sv_x_wconf.size() + 1);
                            continue;
                        }
                        if (startswith(refsub, sv_x_confs))
                        {
                            line_resultvec[i].x_confs = get_string_ready(refsub, sv_x_confs.size() + 1);
                            continue;
                        }
                        if (startswith(refsub, sv_x_mpconf))
                        {
                            line_resultvec[i].x_mpconf = get_string_ready(refsub, sv_x_mpconf.size() + 1);
                            continue;
                        }
                        if (startswith(refsub, sv_line_conf))
                        {
                            line_resultvec[i].line_conf = get_string_ready(refsub, sv_line_conf.size() + 1);
                            continue;
                        }
                        if (startswith(refsub, sv_char_conf))
                        {
                            line_resultvec[i].char_conf = get_string_ready(refsub, sv_char_conf.size() + 1);
                            continue;
                        }
                        if (startswith(refsub, sv_ppageno))
                        {
                            line_resultvec[i].ppageno = get_string_ready(refsub, sv_ppageno.size() + 1);
                            continue;
                        }
                        if (startswith(refsub, sv_block_num))
                        {
                            line_resultvec[i].block_num = get_string_ready(refsub, sv_block_num.size() + 1);
                            continue;
                        }
                        if (startswith(refsub, sv_par_num))
                        {
                            line_resultvec[i].par_num = get_string_ready(refsub, sv_par_num.size() + 1);
                            continue;
                        }
                        if (startswith(refsub, sv_line_num))
                        {
                            line_resultvec[i].line_num = get_string_ready(refsub, sv_line_num.size() + 1);
                            continue;
                        }
                        if (startswith(refsub, sv_word_num))
                        {
                            line_resultvec[i].word_num = get_string_ready(refsub, sv_word_num.size() + 1);
                            continue;
                        }
                        if (startswith(refsub, sv_image))
                        {
                            line_resultvec[i].image = get_string_ready(refsub, sv_image.size() + 1);
                            continue;
                        }
                        if (startswith(refsub, sv_scan_res))
                        {
                            line_resultvec[i].scan_res = get_string_ready(refsub, sv_scan_res.size() + 1);
                            continue;
                        }
                        if (startswith(refsub, sv_rotate))
                        {
                            line_resultvec[i].rotate = get_string_ready(refsub, sv_rotate.size() + 1);
                            continue;
                        }
                        if (startswith(refsub, sv_x_line_bboxes))
                        {
                            line_resultvec[i].x_line_bboxes = get_string_ready(refsub, sv_x_line_bboxes.size() + 1);
                            continue;
                        }
                        if (startswith(refsub, sv_x_line_confs))
                        {
                            line_resultvec[i].x_line_confs = get_string_ready(refsub, sv_x_line_confs.size() + 1);
                            continue;
                        }
                        if (startswith(refsub, sv_x_text))
                        {
                            line_resultvec[i].x_text = get_string_ready(refsub, sv_x_text.size() + 1);
                            continue;
                        }
                    }
                }
                if (!newtmpstring.empty())
                {
                    newtmpstring.pop_back();
                }
                line_resultvec[i].title.clear();
                line_resultvec[i].title.append(newtmpstring);
                line_resultvec[i].line_index = i;
                continue;
            }

            index_check = ref.find(sv_text_eq);
            if (index_check != std::string_view::npos)
            {
                line_resultvec[i].text = get_string_ready(ref, index_check + sv_text_eq.size());
                continue;
            }
        }
    }
    std::array<int64_t, 4> rect1{0, 0, 0, 0};
    std::array<int64_t, 4> rect2{0, 0, 0, 0};
    for (size_t i{}; i < line_resultvec.size(); i++)
    {

        if ((isspace_or_empty(line_resultvec[i].id)) && (isspace_or_empty(line_resultvec[i].title)))
        {
            continue;
        }
        rect1[0] = line_resultvec[i].aa_start_x;
        rect1[1] = line_resultvec[i].aa_start_y;
        rect1[2] = line_resultvec[i].aa_end_x;
        rect1[3] = line_resultvec[i].aa_end_y;
        for (size_t j{}; j < line_resultvec.size(); j++)
        {
            if (j == i)
            {
                continue;
            }
            if (isspace_or_empty(line_resultvec[j].id) && (isspace_or_empty(line_resultvec[j].title)))
            {
                continue;
            }
            rect2[0] = line_resultvec[j].aa_start_x;
            rect2[1] = line_resultvec[j].aa_start_y;
            rect2[2] = line_resultvec[j].aa_end_x;
            rect2[3] = line_resultvec[j].aa_end_y;
            if (is_rect_in_rect(rect1, rect2))
            {
                line_resultvec[i].parents.emplace_back(line_resultvec[j].line_index);
                line_resultvec[j].children.emplace_back(line_resultvec[i].line_index);
            }
        }
    }
    std::cout << dump_struct_vector_as_csv(line_resultvec);
    return EXIT_SUCCESS;
}
