#pragma once

#include "..\header\array.hpp"


class Interface {
private:
	int size_;
	std::string type_;

	bool IsValidDataType();
	bool IsValidSize();
	bool IsStreamValid();
	int GetUserInput();

	template <typename T>
	void InteractWithArray(Array<T>&, int);

	template <typename T>
	void ChooseOption(Array<T>&);

public:
	void SetArraySize();
	void SetArrayType();
	void CreateArray();
	bool AskUserForRestart();
};