#include "functions.hpp"

bool open_file(ifstream &File, string file_name)
{
	File.open(file_name);
	if (!File.is_open())
		return false;
	return true;
}
bool open_file(ofstream &File, string file_name)
{
	File.open(file_name);
	if (!File.is_open())
		return false;
	return true;
}
bool open_file(fstream &File, string file_name)
{
	File.open(file_name, ios::app);
	if (!File.is_open())
		return false;
	return true;
}

void error_call(int error_code)
{
	const string error_messages[] = {
		"File name cannot be empty.",
		"File with this name already exist.",
		"Cannot open this file.",
		"Cannot delete this file",
		"The list with file names cannot be opened.",
		"Cannot remove file name from list.",
		"Term is not recognised as a command.",
		"Invalid argument passed to strtok_s",
		"The file name contains forbidden characters.",
		"File name is forbidden",
		"File name is too long",
		"Cannot create file",
		"Cannot parse the string",
		"File is too large"};

	if (error_code >= 0 && error_code < sizeof(error_messages) / sizeof(error_messages[0]))
		cerr << endl
			 << RED "Error: " + error_messages[error_code] + RESET << endl;

	else
		cerr << endl
			 << RED "Unexpected error." RESET << endl;
}
bool has_control_chars(const string &str)
{
	for (char c : str)
	{
		if (c < ' ' && c > '\0')
		{
			return true;
		}
	}
	return false;
}
bool is_name_taken(string file_name)
{
	string taken_name;
	ifstream fileList;

	if (open_file(fileList, "file_names.txt"))
	{
		while (getline(fileList, taken_name))
		{
			if (file_name + ".txt" == taken_name || file_name == taken_name)
			{
				fileList.close();
				return true;
			}
		}
	}
	else
	{
		error_call(4);
		exit(1);
	}
	fileList.close();

	return false;
}
bool is_name_forbidden(string file_name)
{
	if (file_name + ".txt" == "file_names.txt" || file_name == "file_names.txt")
		return true;

	return false;
}

string get_file_name(int line)
{
	ifstream fileList("file_names.txt");
	string file_name, temp;
	int number = 0;

	while (getline(fileList, temp))
	{
		if (number == line)
		{
			file_name = temp;
			break;
		}
		number++;
	}

	fileList.close();
	return file_name;
}
string get_file_name()
{
	string file_name;
	ifstream fileList;
	const string forbidden_chars = "\\/:*?\"<>|";
	bool error = true;

	do
	{
		cout << endl
			 << "Enter file name: ";
		getline(cin, file_name, '\n');

		// �������� �� ������� �����
		if (file_name.length() >= MAX_FILENAME_LENGTH)
			error_call(10);

		// �������� �� ������ ���������� ����� �����
		else if (file_name.empty())
			error_call(0);

		// �������� �� ��������� ����� � ����� ������
		else if (is_name_taken(file_name))
			error_call(1);

		// �������� �� ����������� � ���� ����� ����������� �������
		else if (file_name.find_first_of(forbidden_chars) != string::npos || has_control_chars(file_name))
			error_call(8);

		else if (is_name_forbidden(file_name))
			error_call(9);

		else
			error = false;

		cin.clear();
	} while (error);

	// ��������� ���������� .txt �� �����
	if (file_name.rfind(".txt") == file_name.length() - EXT_LENGTH && file_name.length() != 3)
		// ���� ����� ����� ���������� � ����� ����, �� 'rfind(".txt")' �� 'length() - EXT_LENGTH' ��������� 0
		// ��� ������ ������� ������� ��������� �������� 'length() != 3'
		return file_name;
	return file_name + ".txt";
}
int get_files_number()
{
	ifstream File;
	string line;
	int number = 0;

	if (open_file(File, "file_names.txt"))
		while (getline(File, line))
			number++;

	else
	{
		error_call(4);
		exit(1);
	}

	return number;
}

void add_to_list(string name)
{
	fstream fileList;

	if (open_file(fileList, "file_names.txt"))
	{
		fileList << name << endl;
		fileList.close();
	}
	else
	{
		error_call(4);
		exit(1);
	}
}
void remove_from_list(string name)
{

	ifstream old_list;
	ofstream new_list;
	string text, new_text;

	if (open_file(old_list, "file_names.txt"))
	{
		while (getline(old_list, text))
		{
			if (text != name)
			{
				new_text += text + '\n';
			}
		}
	}
	else
	{
		error_call(4);
		exit(1);
	}
	old_list.close();

	if (open_file(new_list, "file_names.txt"))
	{
		new_list << new_text;
	}
	else
	{
		error_call(4);
		exit(1);
	}
	new_list.close();
}
void display_file_names(int line)
{
	ifstream fileList;
	string text, arrow = "     ";
	int number = 0;

	if (open_file(fileList, "file_names.txt"))
	{
		cout << endl
			 << GREEN "All files:" RESET << endl
			 << endl;
		while (getline(fileList, text))
		{
			if (line == number)
				arrow = YELLOW "---> ";

			else
				arrow = "     ";

			number++;
			cout << arrow + text + RESET << endl;
		}
		fileList.close();
	}
	else
	{
		error_call(4);
		exit(1);
	}
	cout << endl
		 << "Press \"Esc\" to return to the menu";
}
string choose_file()
{
	int line = 0;
	int files_number = get_files_number();

	display_file_names(line);
	Sleep(130);

	while (true)
	{
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{ // ��������� �������� �����
			line--;
			if (line < 0)
				line = files_number + line;
			display_file_names(line);
			Sleep(130);
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{ // ��������� �������� ����
			line++;
			if (line >= files_number)
				line = line - files_number;
			display_file_names(line);
			Sleep(130);
		}
		else if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{ // ��������� 'Enter'
			while (getchar() != '\n')
			{
			} // �������� ������ ��������
			return get_file_name(line);
		}
		else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) // ��������� 'Esc'
			return "";
	}
}

char *extend_array(char *arr, char *new_arr)
{
	int control_chars = 3;
	size_t arr_len = strlen(arr);
	size_t new_arr_len = strlen(new_arr);
	size_t new_arr_size = new_arr_len + arr_len + control_chars;
	char *new_arr_extended = new char[new_arr_size]{0};
	strcpy_s(new_arr_extended, new_arr_size, new_arr);
	delete[] new_arr;
	new_arr = new_arr_extended;

	return new_arr;
}
int get_file_size(FILE *File, const char *file_name)
{
	const int MB = 1048576;
	size_t size = 0;

	fseek(File, 0, SEEK_END);
	size = ftell(File);
	fseek(File, 0, SEEK_SET);

	if (size > MB)
	{
		error_call(13);
		return 0;
	}

	return size;
}
bool has_control_chars(const char *str)
{
	for (const char *c = str; *c != '\0'; ++c)
		if (*c < ' ' && *c > '\0' || *c == 127)
			return true;

	return false;
}
bool is_name_taken(const char *file_name)
{
	FILE *fileList;
	char taken_name[MAX_FILENAME_LENGTH + 1];
	char *file_name_with_ext = new char[strlen(file_name) + EXT_LENGTH + 1];

	strcpy_s(file_name_with_ext, strlen(file_name) + EXT_LENGTH + 1, file_name);
	strcat_s(file_name_with_ext, strlen(file_name) + EXT_LENGTH + 1, ".txt");

	if (!fopen_s(&fileList, "file_names.txt", "r"))
	{
		while (fgets(taken_name, MAX_FILENAME_LENGTH + 1, fileList))
		{
			size_t len = strlen(taken_name);
			if (len > 0 && taken_name[len - 1] == '\n')
			{
				taken_name[len - 1] = '\0';
			}
			if (!strcmp(file_name_with_ext, taken_name) || !strcmp(file_name, taken_name))
			{
				fclose(fileList);
				return true;
			}
		}
		fclose(fileList);
		return false;
	}
	else
	{
		error_call(4);
		exit(1);
	}
}
bool is_name_forbidden(const char *file_name)
{
	char *file_name_with_ext = new char[strlen(file_name) + EXT_LENGTH + 1];

	strcpy_s(file_name_with_ext, strlen(file_name) + EXT_LENGTH + 1, file_name);
	strcat_s(file_name_with_ext, strlen(file_name) + EXT_LENGTH + 1, ".txt");

	if (!strcmp(file_name_with_ext, "file_names.txt") || !strcmp(file_name, "file_names.txt"))
		return true;

	return false;
}

char *p_get_file_name(int line)
{

	FILE *fileList;
	char *file_name = nullptr, *context = nullptr;
	char buffer[MAX_FILENAME_LENGTH + 1];
	int number = 0;

	if (!fopen_s(&fileList, "file_names.txt", "r"))
	{
		while (fgets(buffer, MAX_FILENAME_LENGTH + 1, fileList) != NULL)
		{
			if (number == line)
			{

				size_t length = strlen(strtok_s(buffer, "\n", &context));
				;
				file_name = new char[length + 1];
				strncpy_s(file_name, length + 1, buffer, _TRUNCATE);
				file_name[length] = '\0';
				break;
			}
			number++;
		}
		fclose(fileList);
	}
	else
	{
		error_call(4);
		exit(1);
	}

	return file_name;
}
char *p_get_file_name()
{
	const char *FORB_CHARS = "\\/:*?\"<>|";
	char temp[MAX_FILENAME_LENGTH + 1];
	bool error = true;

	do
	{
		cin.clear();
		cout << endl
			 << "Enter file name: ";
		fgets(temp, sizeof(temp), stdin);

		temp[strcspn(temp, "\n")] = '\0';

		// �������� �� ������� �����
		if (strlen(temp) >= MAX_FILENAME_LENGTH)
		{
			while (getchar() != '\n')
			{
			} // �������� ������ ��������
			error_call(10);
		}
		// �������� �� ������ ���������� ����� �����
		else if (strlen(temp) == 0)
			error_call(0);

		// �������� �� ��������� ����� � ����� ������
		else if (is_name_taken(temp))
			error_call(1);

		// �������� �� ���������� �����
		else if (is_name_forbidden(temp))
			error_call(9);

		// �������� �� ����������� � ���� ����� ����������� �������
		else if (strpbrk(temp, FORB_CHARS) != NULL || has_control_chars(temp))
			error_call(8);

		else
			error = false;

	} while (error);

	// ��������� ���������� .txt �� �����
	char *file_name = new char[strlen(temp) + EXT_LENGTH];
	strcpy_s(file_name, strlen(temp) + 1, temp);

	if (strlen(file_name) > EXT_LENGTH && !strcmp(file_name + strlen(file_name) - EXT_LENGTH, ".txt"))
		return file_name;

	strcat_s(file_name, strlen(file_name) + EXT_LENGTH + 1, ".txt");

	return file_name;
}
int p_get_files_number()
{
	FILE *File;
	char file_name[MAX_FILENAME_LENGTH + 1];
	int number = 0;

	if (!fopen_s(&File, "file_names.txt", "r"))
	{
		while (fgets(file_name, sizeof(file_name), File) != NULL)
		{
			number++;
		}
		fclose(File);
	}
	else
	{
		error_call(4);
		exit(1);
	}

	return number;
}
void p_display_file_names(int line)
{

	FILE *fileList;
	char file_name[MAX_FILENAME_LENGTH + 1];
	int number = 0;

	if (!fopen_s(&fileList, "file_names.txt", "r"))
	{
		cout << endl
			 << GREEN "All files:" RESET << endl
			 << endl;
		while (fgets(file_name, sizeof(file_name), fileList) != NULL)
		{
			if (line == number)
				cout << YELLOW "---> ";

			else
				cout << "     ";

			cout << file_name << RESET;
			number++;
		}
		fclose(fileList);
	}
	else
	{
		error_call(4);
		exit(1);
	}
	cout << endl
		 << "Press \"Esc\" to return to the menu";
}
void p_add_to_list(const char *name)
{
	FILE *fileList;

	if (!fopen_s(&fileList, "file_names.txt", "a"))
	{
		fputs(name, fileList);
		fputc('\n', fileList);
		fclose(fileList);
	}
	else
	{
		error_call(4);
		exit(1);
	}
}
void p_remove_from_list(const char *name)
{

	FILE *fileList;
	char text[MAX_FILENAME_LENGTH + 1] = {0};
	char new_text[MAX_FILENAME_LENGTH + 1] = {0};

	if (!fopen_s(&fileList, "file_names.txt", "r"))
	{
		while (fgets(text, MAX_FILENAME_LENGTH + 1, fileList) != NULL)
		{
			text[strcspn(text, "\n")] = '\0';
			if (strcmp(text, name))
			{
				text[strcspn(text, "\0")] = '\n';
				strcat_s(new_text, MAX_FILENAME_LENGTH + 1, text);
			}
		}
		fclose(fileList);
	}
	else
	{
		error_call(4);
		exit(1);
	}
	if (!fopen_s(&fileList, "file_names.txt", "w"))
	{
		fputs(new_text, fileList);
		fclose(fileList);
	}
	else
	{
		error_call(4);
		exit(1);
	}
}
char *p_choose_file()
{
	int line = 0;
	int files_number = p_get_files_number();

	p_display_file_names(line);
	Sleep(130);

	while (true)
	{
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{ // ��������� �������� �����
			line--;
			if (line < 0)
				line = files_number + line;
			p_display_file_names(line);
			Sleep(130);
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{ // ��������� �������� ����
			line++;
			if (line >= files_number)
				line = line - files_number;
			p_display_file_names(line);
			Sleep(130);
		}
		else if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{ // ��������� 'Enter'
			while (getchar() != '\n')
			{
			} // �������� ������ ��������
			return p_get_file_name(line);
		}
		else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) // ��������� 'Esc'
			return nullptr;
	}
}