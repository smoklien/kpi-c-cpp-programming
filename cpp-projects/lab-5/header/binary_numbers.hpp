#pragma once

#include "..\header\numbers.hpp"

class TIntNumber2 : public TIntNumber {
public:
    TIntNumber2(const std::string&);

    void Increment() override;
    void Decrement() override;

    int ToDecimal() const override;
};