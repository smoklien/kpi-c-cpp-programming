#include "text.hpp"

void replace_letter(string &word, char last)
{
    for (int i = 0; i < last; i++)
    {
        if (word[i] == word[last])
        {
            word[i] = '.';
        }
    }
}
void replace_letter(char *word, char last)
{
    for (int i = 0; i < last; i++)
    {
        if (word[i] == word[last])
        {
            word[i] = '.';
        }
    }
}

void delete_word(string &word, char last)
{
    for (int i = 0; i < word.length(); i++)
    {
        if (word[i] == last || word[i] == (char)tolower(last))
        {
            word = "";
            return;
        }
    }
}
char *delete_word(char *word, char last)
{
    for (int i = 0; i < strlen(word); i++)
    {
        if (word[i] == last || word[i] == (char)tolower(last))
        {
            return (char *)"";
        }
    }
    return word;
}

string edit_even_line(string line)
{

    istringstream iss(line);
    string word, new_line;
    bool is_word_first = true;

    while (iss >> word)
    {

        // ������ ���� ����������
        char mark = word.find_first_of(MARKS);

        if (mark != string::npos)
        {
            replace_letter(word, mark - 1);
        }
        else
        {
            replace_letter(word, word.length() - 1);
        }
        if (!is_word_first)
        {
            new_line += " ";
        }
        new_line += word;

        is_word_first = false;
    }
    return new_line;
}

char *edit_even_line(char *line)
{

    char *context = nullptr;
    char *word = strtok_s(line, " ", &context);
    size_t new_line_size = strlen(word) + 2;
    size_t word_len;
    size_t new_line_len;
    size_t new_line_size_required;
    char *new_line = new char[new_line_size]{0};
    bool is_word_first = true;

    while (word != nullptr)
    {
        word_len = strlen(word);
        new_line_len = strlen(new_line);
        new_line_size_required = new_line_len + word_len + 2;

        if (new_line_size_required > new_line_size)
        {
            new_line = extend_array(word, new_line);
            new_line_size = new_line_size_required;
        }

        // ������ ���� ����������
        char *mark = nullptr;
        for (int i = 0; i < word_len; i++)
        {
            if (strchr(MARKS, word[i]) != nullptr)
            {
                mark = word + i;
                break;
            }
        }

        // �������� �� ��������� ��������� �������� ����� �� ������
        if (mark != nullptr)
        {
            replace_letter(word, mark - word - 1);
        }
        else
        {
            replace_letter(word, word_len - 1);
        }

        // �������� ������ ����� � ����� ����� �� ������ �����, ���� ���� �� �����
        if (!is_word_first)
        {
            strcat_s(new_line, new_line_size, " ");
        }
        strcat_s(new_line, new_line_size, word);

        // ���������� �� ���������� �����
        word = strtok_s(nullptr, " ", &context);
        is_word_first = false;
    }

    delete[] word;

    return new_line;
}

string edit_odd_line(string line)
{

    istringstream iss(line);
    string word, new_line;
    char last_char;
    bool is_word_first = true;

    while (iss >> word)
    {
        // ������ ���� ����������
        char mark = word.find_first_of(MARKS);

        if (is_word_first)
        {
            if (mark != string::npos)
            {
                last_char = word[mark - 1];
            }
            else
            {
                last_char = word[word.length() - 1];
            }
        }
        else
        {
            delete_word(word, last_char);
            new_line += " ";
        }
        new_line += word;
        is_word_first = false;
    }
    return new_line;
}
char *edit_odd_line(char *line)
{

    char *context = nullptr;
    char *word = strtok_s(line, " ", &context);
    size_t new_line_size = strlen(word) + 2;
    size_t word_len;
    size_t new_line_len;
    size_t new_line_size_required;
    char *new_line = new char[new_line_size]{0};
    char last_char = 0;
    bool is_word_first = true;

    while (word != nullptr)
    {
        word_len = strlen(word);
        new_line_len = strlen(new_line);
        new_line_size_required = new_line_len + word_len + 2;
        if (new_line_size_required > new_line_size)
        {
            new_line = extend_array(word, new_line);
            new_line_size = new_line_size_required;
        }

        // ������ ���� ����������
        char *mark = nullptr;
        for (int i = 0; i < word_len; i++)
        {
            if (strchr(MARKS, word[i]) != nullptr)
            {
                mark = word + i;
                break;
            }
        }

        // ��������� ������� ����� ������� �����
        if (is_word_first)
        {
            if (mark != nullptr)
                last_char = word[strlen(mark) - 1];
            else
                last_char = word[strlen(word) - 1];
        }
        else
        {
            // ���������, ���� ������ ������� ����� ������� �����
            word = delete_word(word, last_char);
            strcat_s(new_line, new_line_size, " ");
        }
        strcat_s(new_line, new_line_size, word);

        // ���������� �� ���������� �����
        word = strtok_s(nullptr, " ", &context);
        is_word_first = false;
        // char
    }
    // memory leak (char *) char * line | delete [] | delete
    return new_line;
}