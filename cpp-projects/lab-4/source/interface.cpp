#include "..\header\interface.hpp"

Interface::Interface(int number_of_triangles)
{
	number_of_triangles_ = number_of_triangles;
	triangles_ = new Triangle * [number_of_triangles_];

	for (int i = 0; i < number_of_triangles_; i++) {
		triangles_[i] = nullptr;
	}
}

Interface::~Interface() {
	for (int i = 0; i < number_of_triangles_; i++) {
		delete triangles_[i];
	}
	delete[] triangles_;
}
//
// Restart Prog
//
bool Interface::AskUserForRestart() {
	char response;
	bool error;

	do {
		error = false;
		std::cout << std::endl;
		std::cout << "Would you like to restart? (y/n): " << std::endl;
		std::cin >> response;
		error = !IsStreamValid();

		if (error) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << colors::red << "Error: Innacurate answer." << colors::reset << std::endl;
		}
	} while (error == true);

	return response == 'y' || response == 'Y';
}
//
// Print Results
//
void Interface::PrintTrianglesDimensions() {
	for (int i = 0; i < number_of_triangles_; i++) {
		std::cout << "Dimesions of triangle " << colors::yellow << i + 1 << colors::reset << ": ";
		std::cout << triangles_[i]->GetSideA() << ", ";
		std::cout << triangles_[i]->GetSideB() << ", ";
		std::cout << triangles_[i]->GetSideC() << std::endl;
	}
}

void Interface::PrintTrianglesAreas() {
	int max_index = 0;
	float max_area = 0;
	float areas[3]{};

	std::cout << std::endl;
	for (int i = 0; i < number_of_triangles_; i++) {
		areas[i] = triangles_[i]->CalculateAreaHeron();
		std::cout << "Area of triangle " << colors::yellow << i + 1 << colors::reset << ": " << areas[i] << std::endl;

		if (areas[i] > max_area) {
			max_area = areas[i];
			max_index = i;
		}
	}
	if (areas[0] == areas[1] && areas[1] == areas[2]) {
		std::cout << std::endl;
		std::cout << "Areas are equal.";
	}
	else {
		std::cout << std::endl;
		std::cout << "The maximum area is triangle ";
		std::cout << colors::green << max_index + 1 << " (" << max_area << ")" << colors::reset << std::endl;
	}
}
//
// Set new values for triangles
//
void Interface::UpdateTriangles() {
	for (int i = 0; i < number_of_triangles_; i++) {
		DisplayUpdateOptions(i);

		int choice;
		while (true) {
			choice = GetUserInput();
			if (choice >= 1 && choice <= 3) {
				break;
			}
			std::cerr << "Invalid choice. Please, try again." << std::endl;
		}

		Triangle* new_triangle = new Triangle(*triangles_[i]);

		try {

			if (choice == 1) {
				++(*new_triangle);
			}
			else if (choice == 2) {
				--(*new_triangle);
			}
			else {
				std::cout << "Enter the specific amount: ";
				float specific_amount = GetUserInput();
				(*new_triangle) += specific_amount;
			}

			triangles_[i] = new_triangle;
		}
		catch (const std::logic_error& e) {
			delete new_triangle;
			std::cerr << colors::red << "Error: " << e.what() << colors::reset << std::endl;
			i--;
		}
	}
}
//
// Construct triangles
//
void Interface::CreateTriangles() {
	for (int i = 0; i < number_of_triangles_; i++) {
		DisplayCreationOptions(i);

		int choice;
		while (true) {
			choice = GetUserInput();
			if (choice >= 1 && (choice <= 2 || (choice == 3 && i > 0))) {
				break;
			}
			std::cerr << "Invalid choice. Please, try again." << std::endl;
		}

		Triangle* new_triangle = nullptr;

		try {
			if (choice == 1) {
				new_triangle = CreateTriangleWithSides();
			}
			else if (choice == 2) {
				new_triangle = CreateTriangleWithSideAndHeight();
			}
			else if (choice == 3 && i > 0) {
				new_triangle = new Triangle(*triangles_[i - 1]);
			}
			triangles_[i] = new_triangle;
		}
		catch (const std::logic_error& e) {
			delete new_triangle;
			std::cerr << colors::red << "Error: " << e.what() << colors::reset << std::endl;
			i--;  // Redo this iteration
		}
	}
}
//
// Displaying text
//
void Interface::DisplayUpdateOptions(int i) const {
	std::cout << std::endl;
	std::cout << "Triangle " << colors::yellow << i + 1 << colors::reset << ": ";
	std::cout << "How would you like to update this triangle?" << std::endl;
	std::cout << "1. Increment" << std::endl;
	std::cout << "2. Decrement" << std::endl;
	std::cout << "3. Add specific amount" << std::endl;
	std::cout << "---> Choice: ";
}

void Interface::DisplayCreationOptions(int i) const {
	std::cout << std::endl;
	std::cout << "Creating triangle " << colors::yellow << i + 1 << ":" << colors::reset << std::endl;
	std::cout << "How would you like to construct this triangle?" << std::endl;
	std::cout << "1. Three sides" << std::endl;
	std::cout << "2. Side and height (isosceled)" << std::endl;
	if (i != 0) {
		std::cout << "3. Copy previous triangle" << std::endl;
	}
	std::cout << "---> Choice: ";
}
//
// Creating triangles depending on constructor
//
Triangle* Interface::CreateTriangleWithSides() {
	float side_a, side_b, side_c;

	std::cout << std::endl;
	std::cout << "Enter lengths of three sides: ";
	std::cin >> side_a >> side_b >> side_c;

	if (!IsStreamValid()) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		throw std::logic_error("Invalid input.");
	}

	return new Triangle(side_a, side_b, side_c);
}

Triangle* Interface::CreateTriangleWithSideAndHeight() {
	float side, height;

	std::cout << std::endl;
	std::cout << "Enter lengths of side and height: ";
	std::cin >> side >> height;

	if (!IsStreamValid()) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		throw std::logic_error("Invalid input.");
	}

	return new Triangle(side, height);
}
//
// getting a value from user
//
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
			std::cout << colors::red << "Error: Invalid input. Please enter an integer." << colors::reset << std::endl;
		}
	}
	return user_input;
}
//
// Handle input
//
bool Interface::IsStreamValid() {
	return !(std::cin.fail() || std::cin.peek() != '\n');
}