#include "..\header\binary_numbers.hpp"

TIntNumber2::TIntNumber2(const std::string& number) 
    : TIntNumber(number) {}

void TIntNumber2::Increment() {
    int carry = 1;
    for (int i = m_number.size() - 1; i >= 0 && carry; i--) {
        if (m_number[i] == '0') {
            m_number[i] = '1';
            carry = 0;
        }
        else if (m_number[i] == '1') {
            m_number[i] = '0';
            carry = 1;
        }
    }
    if (carry == 1) {
        m_number = '1' + m_number;
    }
}

void TIntNumber2::Decrement() {
    if (m_number == "0") {
        throw std::invalid_argument("Cannot decrement zero");
    }
    int carry = -1;
    for (int i = m_number.size() - 1; i >= 0 && carry; i--) {
        if (m_number[i] == '1') {
            m_number[i] = '0';
            carry = 0;
        }
        else if (m_number[i] == '0') {
            m_number[i] = '1';
            carry = 1;
        }
    }
    while (m_number.size() > 1 && m_number[0] == '0') {
        m_number = m_number.substr(1);
    }
}

int TIntNumber2::ToDecimal() const {
    int decimal = 0;
    for (char c : m_number) {
        decimal *= 2;
        if (c == '1') {
            decimal += 1;
        }
    }
    return decimal;
}