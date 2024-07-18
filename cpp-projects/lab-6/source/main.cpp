#include "..\header\interface.hpp"

int main() {
    Interface interface;
    try {
        do {
            interface.SetArraySize();
            interface.SetArrayType();
            interface.CreateArray();
        } while (interface.AskUserForRestart());
    }
    catch (std::bad_alloc) {
        std::cerr << colors::RED << "Error: bad memory allocation." << colors::RESET;
        return 1;
    }
    catch (const std::runtime_error& e) {
        std::cerr << colors::RED << "Runtime error occurred: " << e.what() << colors::RESET << std::endl;
        return 1;
    }
    return 0;
}