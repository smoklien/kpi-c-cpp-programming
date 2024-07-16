#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

void error_message()
{
	printf("\n  _____ ____  ____   ___  ____  \n");
	printf(" | ____|  _ \\|  _ \\ / _ \\|  _ \\ \n");
	printf(" |  _| | |_) | |_) | | | | |_) |\n");
	printf(" | |___|  _ <|  _ <| |_| |  _ < \n");
	printf(" |_____|_| \\_\\_| \\_\\\\___/|_| \\_\\ \n");
}

char restart_program()
{
	printf("\n\n\n Press 'Enter' to restart the program");
	return (getch() == '\r') ? 1 : 0;
}

int get_integer()
{
	char check = 0, buf = 0;
	int number;

	do
	{
		if (scanf("%d%c", &number, &buf) && buf == '\n')
		{
			if (!(number > 100 || number <= 0))
			{
				check = 1;
			}
			else
			{
				error_message();
				printf("\n Entered number is too big or too small!\n"
					   "\n Please, try again: ");
			}
		}
		else
		{
			error_message();
			printf("\n Entered number is not an integer!\n"
				   "\n Please, try again: ");
			while ((buf = getchar()) != '\n' && buf != EOF)
				;
		}
	} while (!check);

	return number;
}

char get_random_character()
{
	int random = rand() % 52;

	if (random >= 26)
	{
		random = 'a' + random - 26;
	}
	else
	{
		random = 'A' + random;
	}

	return random;

	// return (random >= 26) ? 'a' + random - 26 : 'A' + random;
}

char make_decision()
{
	char decision = 0;
	do
	{
		decision = getche();
		if (decision == '1')
		{
			decision = 0;
		}
		else if (decision == '2')
		{
			decision = 1;
		}
		else
		{
			if (decision == '\r')
			{
				printf("\n Please, type something: ");
			}
			else
			{
				printf(" - Wrong answer!\n"
					   " Please, try againg: ");
			}
			decision = 2;
		}
	} while (decision == 2);

	return decision;
}

char **innit_array(int str_amount, int str_length)
{
	char **array = (char **)malloc(str_amount * sizeof(char *));

	if (array == NULL)
	{
		printf("Failed to allocate memory!");
		exit(1);
	}

	for (int i = 0; i < str_amount; i++)
	{
		array[i] = (char *)malloc(str_length + 1);

		if (array[i] == NULL)
		{
			printf("Failed to allocate memory!");
			for (int j = 0; j < i; j++)
				free(array[j]);
			free(array);
			exit(1);
		}
	}
	return array;
}

void fill_array(char **array, int str_amount, int str_length, char is_random)
{
	if (is_random)
	{
		for (int i = 0; i < str_amount; i++)
		{
			for (int j = 0; j < str_length; j++)
				array[i][j] = get_random_character();
			array[i][str_length] = 0;
		}
	}
	else
	{
		printf("\n\n");

		for (int i = 0; i < str_amount; i++)
		{
			char check = 0;

			printf(" Enter string %d: ", i + 1);
			while (!check)
			{
				for (int j = 0; j <= str_length; j++)
				{
					char string = getchar();

					if (string == '\n')
					{
						if (!j)
						{
							printf("\n You have not entered any character yet!\n"
								   "\n Please, enter string %d: ",
								   i + 1);
							break;
						}

						check = 1;
						for (int k = j; k <= str_length; k++)
							array[i][k] = 0;
						break;
					}
					else
					{
						array[i][j] = string;
						if (j == str_length)
						{
							error_message();
							printf("\n You have entered too many characters!\n"
								   "\n Please, try againg: ");
							while ((string = getchar()) != '\n' && string != EOF)
								;
						}
					}
				}
			}
		}
	}
}

void sort_array(char **array, int str_amount, int str_lenth)
{
	for (int i = 0; i < str_amount - 1; i++)
	{
		for (int j = 0; j < str_amount - i - 1; j++)
		{
			for (int k = 0; k < str_lenth; k++)
			{
				if (array[j][k] > array[j + 1][k])
				{
					char *swap = array[j];
					array[j] = array[j + 1];
					array[j + 1] = swap;
				}
				if (array[j][k] < array[j + 1][k])
				{
					break;
				}
			}
		}
	}
}

void print_array(char **array, int str_amount, int str_length, char is_backwards, char *is_answer)
{
	if (!is_backwards || !*is_answer)
	{
		for (int i = 0; i < str_amount; i++)
		{
			printf("\n %d. ", i + 1);

			for (int j = 0; j < str_length; j++)
			{
				if (!*is_answer)
					printf("%c", array[i][j]);
				else
					printf("%c", array[i][j]);
			}
		}
	}
	else
	{
		for (int i = str_amount - 1; i >= 0; i--)
		{
			printf("\n %d. ", str_amount - i);

			for (int j = 0; j < str_length; j++)
			{
				printf("%c", array[i][j]);
			}
		}
	}

	*is_answer = 1;
}

int main()
{
	srand(time(0));

	do
	{
		int str_amount;
		int str_length;
		char order;
		char is_random;
		char is_answer = 0;

		printf("\n\t~~~ Array sorting progrgam ~~~\n\n");

		printf(" Enter amount of strings you want to sort "
			   "(1 - 100): ");
		str_amount = get_integer();

		printf(" Enter the length of strings "
			   "(1 - 100): ");
		str_length = get_integer();

		printf(" Do you want to type strings? "
			   " 1 - YES, 2 - NO (generate random): ");
		is_random = make_decision();

		printf("\n Choose sort order"
			   " 1 - (A to z), 2 - (z to A): ");
		order = make_decision();

		char **strings = innit_array(str_amount, str_length);
		fill_array(strings, str_amount, str_length, is_random);

		printf("\n\t*~~~~~~~~~ Generated strings ~~~~~~~~~*\n");
		print_array(strings, str_amount, str_length, order, &is_answer);

		printf("\n\n\t*~~~~~~~~~ Sorted strings ~~~~~~~~~*\n");
		sort_array(strings, str_amount, str_length);
		print_array(strings, str_amount, str_length, order, &is_answer);

		for (int i = 0; i < str_amount; i++)
		{
			free(strings[i]);
		}
		free(strings);

	} while (restart_program());

	return 0;
}