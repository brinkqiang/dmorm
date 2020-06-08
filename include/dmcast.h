
// Copyright (c) 2018 brinkqiang (brink.qiang@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef __DMCAST_H_INCLUDE__
#define __DMCAST_H_INCLUDE__

#include <string>

template <typename T>
inline T lexical_cast(const std::string& strIn)
{
    return std::stoi(strIn);
}

template <typename T>
inline T lexical_cast(const char* strIn)
{
    return std::stoi(strIn);
}

template <typename T>
inline std::string lexical_cast(const T& value)
{
    return std::to_string(value);
}

template <size_t N>
inline std::string lexical_cast(const char(&strIn)[N])
{
    return strIn;
}

template <>
inline std::string lexical_cast(const char* strIn)
{
    return strIn;
}

inline std::string lexical_cast(const std::string& strIn)
{
    return std::move(strIn);
}

template <>
inline bool lexical_cast(const char* strIn)
{
    return std::stoi(strIn);
}

template <>
inline char lexical_cast(const std::string& strIn)
{
    return std::stoi(strIn);
}

template <>
inline int8_t lexical_cast(const std::string& strIn)
{
    return std::stoi(strIn);
}

template <>
inline uint8_t lexical_cast(const std::string& strIn)
{
    return std::stoul(strIn);
}

template <>
inline int16_t lexical_cast(const std::string& strIn)
{
    return std::stoi(strIn);
}

template <>
inline uint16_t lexical_cast(const std::string& strIn)
{
    return std::stoul(strIn);
}

template <>
inline int32_t lexical_cast(const std::string& strIn)
{
    return std::stoi(strIn);
}

template <>
inline uint32_t lexical_cast(const std::string& strIn)
{
    return std::stoul(strIn);
}

template <>
inline int64_t lexical_cast(const std::string& strIn)
{
    return std::stoll(strIn);
}

template <>
inline uint64_t lexical_cast(const std::string& strIn)
{
    return std::stoull(strIn);
}

template <>
inline float lexical_cast(const std::string& strIn)
{
    return std::stof(strIn);
}

template <>
inline double lexical_cast(const std::string& strIn)
{
    return std::stod(strIn);
}

template <>
inline long double lexical_cast(const std::string& strIn)
{
    return std::stold(strIn);
}

#endif // __DMCAST_H_INCLUDE__

