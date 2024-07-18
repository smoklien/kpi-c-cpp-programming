#pragma once

#include <iostream>
#include "..\header\utils.hpp"

class TIntNumber {
protected:
	std::string m_number;
public:
    TIntNumber(const std::string&);
    virtual ~TIntNumber() {}

    virtual void Increment() = 0;
    virtual void Decrement() = 0;

    virtual int ToDecimal() const = 0;

    const std::string& GetNumber();
};