#pragma once

#include <iomanip>
#include <limits>
#include "..\header\binary_numbers.hpp"
#include "..\header\hex_numbers.hpp"

class Interface
{
private:
	TIntNumber **numbers_;
	int amount_of_binary_numbers_;
	int amount_of_hex_numbers_;

	void AllocateNumbers();
	void DeallocateNumbers();
	void Reset();

	void EnterBinaryNumber(int);
	void EnterHexadecimalNumber(int);
	void UpdateNumbersOfType(int, int, int);
	void PrintNumbersOfType(const std::string &, int, int);
	void PrintUpdatedNumbersOfType(const std::string &, int, int);

	int EnterNumber(const std::string &, const std::string &);
	int GetUserChoice(const std::string &);
	bool IsStreamValid();
	bool IsBinary(const std::string &);
	bool IsHexadecimal(const std::string &);

public:
	Interface();
	~Interface();

	void CreateNumbers();
	void UpdateNumbers();
	void PrintNumbers();
	void PrintUpdatedNumbers();
	void PrintMaxDecimalValue();
	bool AskUserForRestart();
};