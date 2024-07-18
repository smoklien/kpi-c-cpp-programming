#pragma once

#include "..\header\numbers.hpp"

class TIntNumber16 : public TIntNumber {
public:
    TIntNumber16(const std::string&);

    void Increment() override;
    void Decrement() override;

    int ToDecimal() const override;
};