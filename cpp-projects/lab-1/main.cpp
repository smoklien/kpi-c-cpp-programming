#include <locale>

#include "operations.hpp"

string console_data_processing(int, char *[]);
void print_menu(string, int);
int choose_option(string);

const int NUM_OPTIONS = 6;
const int DELAY_MS = 130;

int main(int argc, char *argv[])
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	string mode = console_data_processing(argc, argv);

	if (mode == "Stream")
	{
		while (true)
		{
			switch (choose_option(mode))
			{
			case 0:
				read_file();
				break;
			case 1:
				create_file();
				break;
			case 2:
				write_to_file();
				break;
			case 3:
				convert_file();
				break;
			case 4:
				delete_file();
				break;
			case 5:
				return 0;
			}
		}
	}
	else if (mode == "Pointer")
	{
		while (true)
		{
			switch (choose_option(mode))
			{
			case 0:
				p_read_file();
				break;
			case 1:
				p_create_file();
				break;
			case 2:
				p_write_to_file();
				break;
			case 3:
				p_convert_file();
				break;
			case 4:
				p_delete_file();
				break;
			case 5:
				return 0;
			}
		}
	}
	else
		return 1;
}

string console_data_processing(int amount, char *vector[])
{
	if (amount > 2 && !_stricmp(vector[1], "-mode") && !_stricmp(vector[2], "FileStream"))
		return "Stream";

	else if (amount > 2 && !_stricmp(vector[1], "-mode") && !_stricmp(vector[2], "FilePointer"))
		return "Pointer";

	else
	{
		error_call(6);
		cout << "You have to type \"-mode (FileStream/FilePointer)\"" << endl;
		exit(1);
	}
}

void print_menu(string mode, int selected_option)
{
	string items[6] = {
		"Read file", "Create file", "Write to file", "Converting strings", "Delete file", "Exit"};

	cout << endl
		 << endl
		 << YELLOW << setw(50)
		 << "<<~~~~ Text files program (" + mode + " mode) ~~~~>>"
		 << endl
		 << endl
		 << endl
		 << endl;
	for (int i = 0; i < 6; i++)
	{
		if (i == selected_option)
			cout << YELLOW "---> " + items[i] << endl;
		else
			cout << RESET "     " + items[i] << endl;
	}
	cout << RESET << endl;
}

int choose_option(string mode)
{
	int selected_option = 0;

	print_menu(mode, selected_option);
	Sleep(DELAY_MS);

	while (true)
	{
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{ // Натиснута стрілочка вгору
			selected_option--;
			if (selected_option < 0)
				selected_option = NUM_OPTIONS - 1;
			print_menu(mode, selected_option);
			Sleep(DELAY_MS);
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{ // Натиснута стрілочка вниз
			selected_option++;
			if (selected_option > NUM_OPTIONS - 1)
				selected_option = 0;
			print_menu(mode, selected_option);
			Sleep(DELAY_MS);
		}
		else if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{ // Натиснуто 'Enter'
			while (getchar() != '\n')
			{
			} // Очищення буфера введення
			return selected_option;
		}
	}
}