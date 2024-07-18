#include "..\header\hex_numbers.hpp"

TIntNumber16::TIntNumber16(const std::string& number) 
    : TIntNumber(number) {}

void TIntNumber16::Increment() {
    int carry = 1;
    for (int i = m_number.size() - 1; i >= 0 && carry; i--) {
        if (m_number[i] >= '0' && m_number[i] < '9') {
            m_number[i]++;
            carry = 0;
        }
        else if (m_number[i] == '9') {
            m_number[i] = 'A';
            carry = 0;
        }
        else if (m_number[i] >= 'A' && m_number[i] < 'F') {
            m_number[i]++;
            carry = 0;
        }
        else if (m_number[i] == 'F') {
            m_number[i] = '0';
            carry = 1;
        }
    }
    if (carry == 1) {
        m_number = '1' + m_number;
    }
}

void TIntNumber16::Decrement() {
    if (m_number == "0") {
        throw std::invalid_argument("Cannot decrement zero");
    }
    int carry = -1;
    for (int i = m_number.size() - 1; i >= 0 && carry; i--) {
        if (m_number[i] > '0' && m_number[i] <= '9') {
            m_number[i]--;
            carry = 0;
        }
        else if (m_number[i] == '0') {
            m_number[i] = 'F';
            carry = 1;
        }
        else if (m_number[i] > 'A' && m_number[i] <= 'F') {
            m_number[i]--;
            carry = 0;
        }
        else if (m_number[i] == 'A') {
            m_number[i] = '9';
            carry = 0;
        }
    }
}

int TIntNumber16::ToDecimal() const {
    int decimal = 0;
    for (char c : m_number) {
        decimal *= 16;
        if (c >= '0' && c <= '9') {
            decimal += (c - '0');
        }
        else if (c >= 'A' && c <= 'F') {
            decimal += (c - 'A' + 10);
        }
    }
    return decimal;
}