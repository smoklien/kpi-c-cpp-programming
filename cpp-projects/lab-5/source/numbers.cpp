#include "..\header\numbers.hpp"

TIntNumber::TIntNumber(const std::string& number) 
    : m_number(number) {}

const std::string& TIntNumber::GetNumber() {
    return m_number;
}