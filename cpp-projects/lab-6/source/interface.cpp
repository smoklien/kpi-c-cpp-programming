#include "..\header\interface.hpp"

void Interface::CreateArray() {
	if (type_ == "bool") {
		Array<bool>arr(size_);
		ChooseOption(arr);
	}
	else if (type_ == "int") {
		Array<int>arr(size_);
		ChooseOption(arr);
	}
	else if (type_ == "float") {
		Array<float>arr(size_);
		ChooseOption(arr);
	}
	else if (type_ == "double") {
		Array<double>arr(size_);
		ChooseOption(arr);
	}
	else if (type_ == "char") {
		Array<char>arr(size_);
		ChooseOption(arr);
	}
	else if (type_ == "string") {
		Array<std::string>arr(size_);
		ChooseOption(arr);
	}
}

template<typename T>
void Interface::ChooseOption(Array<T>& arr) {
	bool error = false;
	int option;
	do {
		error = false;

		std::cout << "Menu:" << std::endl;
		std::cout << "1. Get array size" << std::endl;
		std::cout << "2. Search element" << std::endl;
		std::cout << "3. Check if array is empty" << std::endl;
		std::cout << "4. Insert element" << std::endl;
		std::cout << "5. Iterate through array" << std::endl;
		std::cout << "0. Exit" << std::endl;
		std::cout << "Enter your choice: ";
		option=GetUserInput();

		if (option < 0 || option > 5 || error == true) {
			std::cout << "Invalid option. Please try again." << std::endl;
			continue;
		}

		if (option == 0) {
			std::cout << "Exiting..." << std::endl;
			break;
		}

		InteractWithArray(arr, option);
	} while (true);
}

template <typename T>
void Interface::InteractWithArray(Array<T>& arr, int option) {
	bool error = false;

	switch (option) {
	case 1: {
		size_t size = arr.GetSize();
		std::cout << "Array size: " << size << std::endl;
		break;
	}
	case 2: {
		T value;
		int index;
		std::cout << "Enter the value to search: ";
		std::cin >> value;
		error = !IsStreamValid();

		if (error == false) {
			if (index=arr.Find(value)) {
				std::cout << "Value found in the array. [" << index << "]" << std::endl;
			}
			else {
				std::cout << "Value not found in the array." << std::endl;
			}
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << colors::RED << "Error: invalid value" << colors::RESET << std::endl;
		}
		break;
	}
	case 3: {
		bool is_empty = arr.IsEmpty();
		if (is_empty) {
			std::cout << "Array is empty." << std::endl;
		}
		else {
			std::cout << "Array is not empty." << std::endl;
		}
		break;
	}
	case 4: {
		try {
			T value;
			size_t position;
			std::cout << "Enter the value to insert: ";
			std::cin >> value;
			error = !IsStreamValid();

			if (error == true) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cerr << colors::RED << "Error: invalid value" << colors::RESET << std::endl;
			}
			else {
				std::cout << "Enter the position to insert: ";
				position = GetUserInput();
				arr.Insert(position - 1, value);
			}
		}
		catch (std::logic_error& e) {
			std::cerr << colors::RED << "Error: " << e.what() << colors::RESET << std::endl;
		}
		break;
	}
	case 5: {
		int element_counter = 0;
		for (typename Array<T>::Iterator it = arr.Begin(); !it.IsEnd(arr.End()); it.Next()) {
			std::cout << "Element [" << colors::YELLOW << ++element_counter << colors::RESET << "]: ";
			std::cout << it.GetValue() << std::endl;
		}
		break;
	}
	default: {
		std::cerr << "Invalid option. Please try again." << std::endl;
		break;
	}
	}
}


void Interface::SetArraySize() {
	std::cout << "Enter size of array: ";
	size_ = GetUserInput();
}

void Interface::SetArrayType() {
	bool error = false;
	do {
		error = false;
		std::cout << "Enter type of array: ";
		std::cin >> type_;

		error = !IsValidDataType() || !IsStreamValid();
		if (error) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << colors::RED << "Error: invalid type of data" << colors::RESET << std::endl;
		}
	} while (error);
}

int Interface::GetUserInput() {
	int user_input;
	while (true) {
		std::cin >> user_input;
		if (IsStreamValid()) {
			break;
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << colors::RED << "Error: Invalid input. Please enter an integer." << colors::RESET << std::endl;
		}
	}
	return user_input;
}

bool Interface::IsStreamValid() {
	return !(std::cin.fail() || std::cin.peek() != '\n');
}

bool Interface::IsValidDataType() {
	std::string data_types[6] = { "bool", "int", "float", "double", "char", "string" };
	for (const std::string& data_type : data_types) {
		if (data_type == type_) {
			return true;
		}
	}
	return false;
}

bool Interface::IsValidSize() {
	return (size_ > 0 && size_ <= 20);
}

bool Interface::AskUserForRestart() {
	char user_choice;
	int attempts = 6;
	bool error = false;

	while (attempts != 0) {
		std::cout << std::endl;
		std::cout << "Do you want to restart program? (y/n)" << std::endl;
		std::cin >> user_choice;
		error = IsStreamValid();

		if (user_choice == 'y') {
			return true;
		}
		else if (user_choice == 'n') {
			return false;
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << colors::RED << "Inaccurate response. Please try again." << colors::RESET<< std::endl;
			attempts--;
			error = true;
		}
	}
	std::cerr << colors::RED << "Error: maximum number of attempts reached. Exiting program." << colors::RESET << std::endl;
	exit(1);
}