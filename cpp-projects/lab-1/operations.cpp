#include "operations.hpp"

void read_file()
{
	ifstream file;
	string text, file_name;

	file_name = choose_file();
	if (file_name == "")
		return;

	if (open_file(file, file_name))
	{
		cout << setw(30) << GREEN "<" + file_name + ">" RESET << endl
			 << endl;
		if (file.peek() == EOF)
			cout << YELLOW "<File is empty>" RESET << endl;

		while (getline(file, text))
			cout << text << endl;

		file.close();
	}
	else
		error_call(2);
}

void read_file(string file_name)
{
	ifstream file;
	string text;

	if (open_file(file, file_name))
	{
		cout << setw(5) << GREEN "<" + file_name + ">" RESET << endl
			 << endl;
		if (file.eof())
			cout << YELLOW "<File is empty>" RESET << endl;

		while (getline(file, text))
			cout << text << endl;

		file.close();
	}
	else
		error_call(2);
}

void create_file()
{
	string file_name;
	ofstream file;

	file_name = get_file_name();

	if (open_file(file, file_name))
	{
		file.close();
		add_to_list(file_name);
		cout << GREEN "File <" + file_name + "> was created!" RESET << endl
			 << endl;
	}
	else
		error_call(11);
}

void create_file(string file_name)
{
	ofstream file;

	if (open_file(file, file_name))
	{
		file.close();
		add_to_list(file_name);
		cout << GREEN "File <" + file_name + "> was created!" RESET << endl
			 << endl;
	}
	else
		error_call(11);
}

void convert_file()
{
	ifstream inputFile;
	ofstream outputFile, changedFile;
	string odd_lines, even_lines, line, reworked_line, input_file_name, output_file_name;

	const int LIMIT = 1900;
	int line_counter = 0;

	input_file_name = choose_file();
	if (input_file_name == "")
		return;

	cout << endl
		 << "You chose ---> " GREEN << input_file_name << RESET;
	cout << endl
		 << "Now you have to create new file for converted strings." << endl;

	output_file_name = get_file_name();
	create_file(output_file_name);

	if (open_file(inputFile, input_file_name))
	{
		while (getline(inputFile, line))
		{

			if (line_counter % 2)
			{
				reworked_line = edit_even_line(line);
				even_lines += reworked_line + '\n';
			}
			else
			{
				reworked_line = edit_odd_line(line);
				odd_lines += reworked_line + '\n';
			}
			line_counter++;

			if (odd_lines.length() + even_lines.length() > LIMIT)
			{

				cout << endl
					 << YELLOW "File is too big! Stream mode can not handle it!" RESET << endl;

				return;
			}
		}
		inputFile.close();
	}
	else
		error_call(2);

	cout << endl
		 << GREEN "Original file: ";
	read_file(input_file_name);

	if (open_file(changedFile, input_file_name))
	{
		changedFile << odd_lines;
		changedFile.close();
	}
	else
		error_call(2);

	if (open_file(outputFile, output_file_name))
	{
		outputFile << even_lines;
		outputFile.close();
	}
	else
		error_call(2);

	cout << endl
		 << GREEN "Reworked file: ";
	read_file(input_file_name);
	cout << endl
		 << GREEN "New file: ";
	read_file(output_file_name);
}

void write_to_file()
{
	fstream file;
	string text, file_name = "";

	file_name = choose_file();
	if (file_name == "")
		return;

	cout << setw(30) << GREEN "<" + file_name + ">" RESET << endl
		 << endl
		 << endl;
	cout << "Write text " YELLOW "(end with '$'): " RESET << endl;

	getline(cin, text, '$');
	cin.clear();

	if (open_file(file, file_name))
	{
		file << text << endl;
		file.close();
	}
	else
		error_call(2);
}

void delete_file()
{
	ifstream file;
	string file_name;

	file_name = choose_file();
	if (file_name == "")
		return;

	if (!remove((file_name).c_str()))
	{

		cout << endl
			 << GREEN "File was deleted succesfully!" RESET << endl;
		remove_from_list(file_name);
	}
	else
		error_call(3);
}

void p_read_file()
{
	FILE *file;
	char buffer[BUFFER_SIZE];
	char *file_name;
	int line_counter = 0;

	file_name = p_choose_file();
	if (!file_name)
		return;

	if (!fopen_s(&file, file_name, "r"))
	{

		cout << setw(30) << GREEN "<" << file_name << ">" RESET << endl
			 << endl;
		while (fgets(buffer, BUFFER_SIZE, file) != nullptr)
		{
			cout << buffer;
			line_counter++;
		}
		fclose(file);
		if (!line_counter)
			cout << YELLOW "<File is empty>" RESET << endl;
	}
	else
		error_call(2);

	cout << endl
		 << endl;
}

void p_read_file(const char *file_name)
{
	FILE *file;
	char buffer[BUFFER_SIZE];
	int line_counter = 0;

	if (!fopen_s(&file, (file_name), "r"))
	{
		cout << setw(5) << GREEN "<" << file_name << ">" RESET << endl
			 << endl;
		while (fgets(buffer, BUFFER_SIZE, file) != NULL)
		{
			cout << buffer;
			line_counter++;
		}
		fclose(file);
		if (!line_counter)
			cout << YELLOW "<File is empty>" RESET << endl;
	}
	else
		error_call(2);

	cout << endl
		 << endl;
}

void p_create_file()
{
	FILE *file;
	char *file_name;

	file_name = p_get_file_name();

	if (!fopen_s(&file, file_name, "w"))
	{
		fclose(file);
		p_add_to_list(file_name);
		cout << GREEN "File <" << file_name << "> was created!" RESET << endl
			 << endl;
	}
	else
	{
		error_call(11);
		return;
	}
}

void p_create_file(const char *file_name)
{
	FILE *file;

	if (!fopen_s(&file, file_name, "w"))
	{
		fclose(file);
		p_add_to_list(file_name);
		cout << GREEN "File <" << file_name << "> was created!" RESET << endl
			 << endl;
	}
	else
		error_call(11);
}

void p_convert_file()
{
	FILE *outputFile;
	FILE *inputFile;
	size_t text_size = 0;
	size_t size = 0;
	size_t new_text_size = 0;
	char *context = nullptr;
	char *odd_lines = nullptr;
	char *even_lines = nullptr;
	char *line = nullptr;
	char *text = nullptr;
	char *reworked_line = nullptr;
	char *input_file_name = nullptr;
	char *output_file_name = nullptr;

	int line_counter = 0;

	// ������� ����� �����
	input_file_name = p_choose_file();
	if (!input_file_name)
	{
		return;
	}

	// ��������� ����� �����
	if (!fopen_s(&inputFile, input_file_name, "rb"))
	{
		size = get_file_size(inputFile, input_file_name);
		if (!size)
		{
			cout << endl
				 << YELLOW "Your file is empty! Choose another one." RESET << endl;

			return;
		}
		text = new char[size + 1];
		text_size = fread(text, 1, size, inputFile);
		text[size] = '\0';
		fclose(inputFile);
	}
	else
	{
		error_call(2);

		return;
	}

	cout << endl
		 << "You chose ---> " GREEN << input_file_name << RESET;
	cout << endl
		 << "Now you have to create new file for converted strings." << endl;

	output_file_name = p_get_file_name();
	p_create_file(output_file_name);

	// ������������ odd_lines �� even_lines
	odd_lines = new char[size + 1]{0};
	even_lines = new char[size + 1]{0};

	if (!fopen_s(&inputFile, input_file_name, "r"))
	{
		// �������� ����� �� �����
		line = strtok_s(text, "\r\n", &context);
		while (line != nullptr)
		{
			if (line_counter % 2)
			{
				reworked_line = edit_even_line(line);
				even_lines = extend_array(reworked_line, even_lines);
				new_text_size = strlen(reworked_line) + strlen(even_lines) + 3;
				strcat_s(even_lines, new_text_size, reworked_line);
				strcat_s(even_lines, new_text_size, "\r\n");
			}
			else
			{
				reworked_line = edit_odd_line(line);
				odd_lines = extend_array(reworked_line, odd_lines);
				new_text_size = strlen(reworked_line) + strlen(odd_lines) + 3;
				strcat_s(odd_lines, new_text_size, reworked_line);
				strcat_s(odd_lines, new_text_size, "\r\n");
			}
			line_counter++;
			line = strtok_s(nullptr, "\r\n", &context);
			delete[] reworked_line;
		}
		fclose(inputFile);
	}
	else
	{
		delete[] odd_lines;
		delete[] even_lines;
		error_call(2);

		return;
	}

	cout << endl
		 << GREEN "Original file: ";
	read_file(input_file_name);

	// ³������� ����� ��� ����������
	if (!fopen_s(&inputFile, (input_file_name), "w"))
	{
		fputs(odd_lines, inputFile);
		fclose(inputFile);
	}
	else
		error_call(2);

	if (!fopen_s(&outputFile, output_file_name, "w"))
	{
		fputs(even_lines, outputFile);
		fclose(outputFile);
	}
	else
		error_call(2);

	delete[] odd_lines;
	delete[] even_lines;

	cout << endl
		 << GREEN "Reworked file: ";
	p_read_file(input_file_name);
	cout << endl
		 << GREEN "New file: ";
	p_read_file(output_file_name);
}

void p_write_to_file()
{
	FILE *file;
	char *file_name;
	char text[BUFFER_SIZE];
	size_t mark_pos, len;

	file_name = p_choose_file();
	if (!file_name)
		return;

	if (!fopen_s(&file, file_name, "a"))
	{

		cout << setw(30) << GREEN "<" << file_name << ">" RESET << endl
			 << endl
			 << endl;
		cout << "Write text " YELLOW "(end with '$') " RESET << endl;

		do
		{
			fgets(text, BUFFER_SIZE, stdin);
			len = strlen(text);

			// ������ ������ '$'
			mark_pos = strcspn(text, "$");
			if (mark_pos < len)
				text[mark_pos] = '\0';
			fputs(text, file);

		} while (mark_pos == len);
		fclose(file);
	}
	else
		error_call(2);
}

void p_delete_file()
{
	char *file_name;

	file_name = p_choose_file();
	if (!file_name)
		return;

	if (!remove(file_name))
	{

		cout << endl
			 << GREEN "<" << file_name << "> was deleted succesfully!" RESET << endl;
		p_remove_from_list(file_name);
	}
	else
		error_call(3);
}