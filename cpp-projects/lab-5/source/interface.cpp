#include "..\header\interface.hpp"

void Interface::AllocateNumbers() {
    numbers_ = new TIntNumber * [amount_of_binary_numbers_ + amount_of_hex_numbers_];
    for (int i = 0; i < amount_of_binary_numbers_ + amount_of_hex_numbers_; i++) {
        numbers_[i] = nullptr;
    }
}

void Interface::DeallocateNumbers() {
    for (int i = 0; i < amount_of_binary_numbers_ + amount_of_hex_numbers_; i++) {
        delete numbers_[i];
    }
    delete[] numbers_;
}

Interface::Interface() {
    amount_of_binary_numbers_ = EnterNumber("Enter amount of binary numbers: ", "entered number is not an integer");
    amount_of_hex_numbers_ = EnterNumber("Enter amount of hexadecimal numbers: ", "entered number is not an integer");
    AllocateNumbers();
}

Interface::~Interface() {
    DeallocateNumbers();
}

void Interface::Reset() {
    DeallocateNumbers();
    amount_of_binary_numbers_ = EnterNumber("Enter amount of binary numbers: ", "entered number is not an integer");
    amount_of_hex_numbers_ = EnterNumber("Enter amount of hexadecimal numbers: ", "entered number is not an integer");
    AllocateNumbers();
}

int Interface::EnterNumber(const std::string& prompt, const std::string& error) {
    int number;
    while (true) {
        std::cout << prompt;
        std::cin >> number;

        if (IsStreamValid() && number >= 0) {  
            return number;
        }
        else { 
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << colors::red << "Error: " << error << colors::reset << std::endl;
        }
    }
}

void Interface::CreateNumbers() {
    for (int i = 0; i < amount_of_binary_numbers_; i++) {
        EnterBinaryNumber(i);
    }
    for (int i = amount_of_binary_numbers_; i < amount_of_binary_numbers_ + amount_of_hex_numbers_; i++) {
        EnterHexadecimalNumber(i);
    }
}

void Interface::EnterBinaryNumber(int index) {
    std::string number;
    bool error = false;

    do {
        std::cout << "Enter a binary number: ";
        std::cin >> number;
        error = !IsStreamValid() || !IsBinary(number);

        if (error) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << colors::red << "Error: entered number is not binary" << colors::reset << std::endl;
        }
    } while (error);

    numbers_[index] = new TIntNumber2(number);
}

void Interface::EnterHexadecimalNumber(int index) {
    std::string number;
    bool error = false;

    do {
        std::cout << "Enter a hexadecimal number: ";
        std::cin >> number;
        error = !IsStreamValid() || !IsHexadecimal(number);

        if (error) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << colors::red << "Error: entered number is not hexadecimal" << colors::reset << std::endl;
        }
    } while (error);

    for (char& c : number) {
        c = std::toupper(c);
    }
    numbers_[index] = new TIntNumber16(number);
}

void Interface::UpdateNumbers() {
    int choice;
    choice = GetUserChoice("binary numbers");
    UpdateNumbersOfType(choice, 0, amount_of_binary_numbers_);
    choice = GetUserChoice("hexadecimal numbers");
    UpdateNumbersOfType(choice, amount_of_binary_numbers_, amount_of_binary_numbers_ + amount_of_hex_numbers_);
}

void Interface::UpdateNumbersOfType(int choice, int start_index, int end_index) {
    for (int i = start_index; i < end_index; i++) {
        try {
            if (choice == 1) {
                numbers_[i]->Increment();
            }
            else {
                numbers_[i]->Decrement();
            }
        }
        catch (std::invalid_argument& e) {
            std::cerr << colors::red << "Error occured while updating number " << i - start_index + 1 << ": " << e.what() << colors::reset << std::endl;
        }
    }
}

void Interface::PrintNumbers() {
    std::cout << colors::yellow << "Original" << colors::reset << " numbers:" << std::endl;
    PrintNumbersOfType("binary", 0, amount_of_binary_numbers_);
    PrintNumbersOfType("hexadecimal", amount_of_binary_numbers_, amount_of_binary_numbers_ + amount_of_hex_numbers_);
}

void Interface::PrintNumbersOfType(const std::string& type, int start_index, int end_index) {
    std::cout << std::endl;
    std::cout << type << std::endl;
    if (start_index == end_index) {
        std::cout << "No " << type << " numbers" << std::endl;
    }
    else {
        for (int i = start_index; i < end_index; i++) {
            std::cout << numbers_[i]->GetNumber() << std::endl;
        }
    }
}

void Interface::PrintUpdatedNumbers() {
    std::cout << std::endl;
    std::cout << colors::yellow << "Updated" << colors::reset << " numbers:" << std::endl;
    PrintUpdatedNumbersOfType("binary", 0, amount_of_binary_numbers_);
    PrintUpdatedNumbersOfType("hexadecimal", amount_of_binary_numbers_, amount_of_binary_numbers_ + amount_of_hex_numbers_);
}

void Interface::PrintUpdatedNumbersOfType(const std::string& type, int start_index, int end_index) {
    std::cout << std::endl;
    std::cout << type << " -> Decimal:" << std::endl;
    if (end_index == start_index) {
        std::cout << "No " << type << " numbers" << std::endl;
    }
    else {
        for (int i = start_index; i < end_index; i++) {
            std::cout << numbers_[i]->GetNumber() << std::setw(4) << " -> " << colors::yellow;
            std::cout << numbers_[i]->ToDecimal() << colors::reset << std::endl;
        }
    }
}

void Interface::PrintMaxDecimalValue() {
	int max_decimal = 0;
	std::string max_number;

	for (int i = 0; i < amount_of_binary_numbers_ + amount_of_hex_numbers_; i++) {
		int decimal = numbers_[i]->ToDecimal();
		if (decimal > max_decimal) {
			max_decimal = decimal;
			max_number = numbers_[i]->GetNumber();
		}
	}

	std::cout << std::endl;
	std::cout << "Max number is: " << colors::green << max_number << colors::reset << std::endl;
	std::cout << "Or decimal: " << colors::green << max_decimal << colors::reset << std::endl;
}

int Interface::GetUserChoice(const std::string& type) {
    int choice;
    bool error;
    do {
        error = false;
        std::cout << std::endl;
        std::cout << "Choose an option for " << type << ":" << std::endl;
        std::cout << "1. Increment" << std::endl;
        std::cout << "2. Decrement" << std::endl;
        std::cout << "---> Choice: ";
        std::cin >> choice;
        error = (!IsStreamValid() || choice != 1 && choice != 2);

        if (error) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << colors::red << "Error: invalid argument" << colors::reset << std::endl;
        }

    } while (error);

    return choice;
}

bool Interface::AskUserForRestart() {
	char user_choice;
	int attempts = 6; // ����������� ������� �����

	while (attempts != 0) {
		std::cout << std::endl;
		std::cout << "Do you want to restart program? (y/n)" << std::endl;
		std::cin >> user_choice;

		if (user_choice == 'y') {
			Reset();
			return true;
		}
		else if (user_choice == 'n') {
			return false;
		}
		else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cerr << colors::red << "Inaccurate response. Please try again." << colors::reset << std::endl;
            attempts--;
		}
	}
	std::cerr << colors::red << "Error: maximum number of attempts reached. Exiting program." << colors::reset << std::endl;
	return false;
}

bool Interface::IsBinary(const std::string& number) {
    for (char c : number) {
        if (c != '0' && c != '1') {
            return false;
        }
    }
    return true;
}

bool Interface::IsHexadecimal(const std::string& number) {
    const std::string valid_hex_chars = "0123456789ABCDEFabcdef";

    for (char c : number) {
        if (valid_hex_chars.find(c) == std::string::npos) {
            return false;
        }
    }
    return true;
}


bool Interface::IsStreamValid() {
    if (std::cin.fail() || std::cin.peek() != '\n') {
        return false;
    }
    return true;
}