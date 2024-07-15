#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>

void print_menu()
{
	char decision = 0;
	printf("\n\t<<<~~~~~ Root Calculator ~~~~~>>>\n\n");
	printf("Press 'Enter' to start the program.\n");
	printf("Press 'i' to see further information.\n");
	printf("Press 'e' to exit\n");

	do
	{
		decision = _getch();

		if (decision == 'e')
		{
			exit(0);
		}
		else if (decision == '\r')
		{
			printf("\n\t<<<~~~~~ Root Calculator ~~~~~>>>\n\n\n");
			printf("     k  ___\n");
			printf("y  =  \\/ x\n");
			printf("\n *~~~~~~~~~~~~~~~~~~*\n\n");
		}
		else if (decision == 'i')
		{
			printf("\n\t<<<~~~~~ Root Calculator ~~~~~>>>\n\n\n");
			printf("'x' - Root expression (from |1e-7| to |1e+7|).\n");
			printf("'k' - Root degree. Can't be equal to 0 (from |1e-3| to |1e+3|).\n");
			printf("'e' - Precision. Can be write in exponential, deciminal or natural way (from 1e-9 to 9).\n\n");
			printf("Press 'b' to return to the main menu or 'e' to exit.");

			do
			{
				decision = _getch();

				if (decision == 'e')
				{
					exit(0);
				}

				if (decision == 'b')
				{
					print_menu();
				}
				else
				{
					printf("\nPlease, press 'b' or 'e': ");
					decision = 0;
				}
			} while (decision == 0);
		}
		else
		{
			printf("\nPlease, press 'Enter', 'i' or 'e': ");
			decision = 0;
		}
	} while (decision == 0);
}

void error_message()
{
	printf("\n  _____ ____  ____   ___  ____  \n");
	printf(" | ____|  _ \\|  _ \\ / _ \\|  _ \\ \n");
	printf(" |  _| | |_) | |_) | | | | |_) |\n");
	printf(" | |___|  _ <|  _ <| |_| |  _ < \n");
	printf(" |_____|_| \\_\\_| \\_\\\\___/|_| \\_\\\n");
}

int restart_programm()
{
	printf("\nPress 'Enter' to restart programm\n");
	return (_getch() == '\r') ? 1 : 0;
}

void convert_precision(double *e, int *numbers)
{
	if (*e >= 1)
	{
		*numbers = *e;
		*e = pow(10, -*e);
	}
	else
	{
		*numbers = (int)(-log10(*e));
	}
}

char check_variables(double x, double k, double e)
{
	char error_check = 0;

	if (e <= 0.0)
	{
		error_message();
		printf("\n Precision must be positive! \n");
		error_check = 1;
	}

	if (e > 9 || e < 1.0e-9 && e > 0)
	{
		error_message();
		printf("\n Precision is too small! \n");
		error_check = 1;
	}

	if (fabs(x) > 1.0e7 || fabs(x) < 1.0e-7 && x != 0)
	{
		error_message();
		printf("\n Value of number is too big or too small! \n");
		error_check = 1;
	}

	if (fabs(k) > 1.0e3 || fabs(k) < 1.0e-3 && k != 0)
	{
		error_message();
		printf("\n Value of degree is too big or too small! \n");
		error_check = 1;
	}

	if (k == 0.0)
	{
		error_message();
		printf("\n Degree can not be zero!\n");
		error_check = 1;
	}

	if (x == 0.0 && k < 0.0)
	{
		error_message();
		printf("\n If number is zero, Degree must be greater than zero!\n");
		error_check = 1;
	}

	if (x < 0.0 && ((int)k % 2 == 0))
	{
		error_message();
		printf("\n If number is lower than zero, Degree must be odd!\n");
		error_check = 1;
	}
	return error_check;
}

double get_double()
{
	char check = 0, buf = 0;
	double number;

	do
	{
		if (scanf("%lf%c", &number, &buf) && buf == '\n')
		{
			check = 1;
		}
		else
		{
			error_message();
			printf("\n Entered number is not a float!\n"
				   "\n Please, try again: ");
			while ((buf = getchar()) != '\n' && buf != EOF)
				;
		}
	} while (!check);

	return number;
}

double get_root(double x, double k, double e)
{
	if (x == 0)
	{
		return 0;
	}

	int is_k_positive = (k > 0) ? 1 : 0;
	k = fabs(k);

	double y = 1, yk = 1, delta = 1, k1 = (1. / k);

	while (fabs(delta) > e)
	{
		yk = pow(y, k - 1);
		delta = k1 * (x / yk - y);
		y += delta;

		if (y == 0)
			y = -1.0;
		if (fabs(y) < 1e-9 || isnan(y) || isinf(y))
			return nan("");
	}

	if (is_k_positive == 0)
	{
		return 1 / y;
	}
	else
	{
		return y;
	}
}

void print_answer(double answer, int numbers)
{
	if (!isnan(answer))
	{
		printf("\n *~~~~~~~~~~~~~~~~~~*\n");
		printf("\n  Answer is: "
			   "%.*g\n",
			   (int)log10(fabs(answer)) + 1 + numbers, answer);
		printf("\n *~~~~~~~~~~~~~~~~~~*\n");
	}
	else
	{
		error_message();
		printf("\n Something went wrong! The answer is very small or very big!\n"
			   "\n Please, try again\n");
	}
}

int main()
{
	do
	{
		double x, k, e, answer;
		int numbers;

		print_menu();

		printf("Enter x: ");
		x = get_double();

		printf("Enter k: ");
		k = get_double();

		printf("Enter e: ");
		e = get_double();

		if (!check_variables(x, k, e))
		{
			convert_precision(&e, &numbers);
			answer = get_root(x, k, e);
			print_answer(answer, numbers);
		}

	} while (restart_programm() == 1);

	return 0;
}