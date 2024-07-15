#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>

#define PI 3.1415926535

void print_header()
{
	printf("\n\n\t\t<<~~~  Trigonometric table  ~~~>>\n\n\n");
}

void error_message()
{
	printf("\n  _____ ____  ____   ___  ____  \n");
	printf(" | ____|  _ \\|  _ \\ / _ \\|  _ \\ \n");
	printf(" |  _| | |_) | |_) | | | | |_) |\n");
	printf(" | |___|  _ <|  _ <| |_| |  _ < \n");
	printf(" |_____|_| \\_\\_| \\_\\\\___/|_| \\_\\ \n");
}

int restart_programm()
{
	printf("\n Press 'enter' to restart programm\n");
	return (getch() == '\r') ? 1 : 0;
}

int is_zero(double value)
{
	return (isnan(value) || (fabs(value) < 1e-9f && value != 0)) ? 1 : 0;
}

char check_variables(double x1, double x2, double dx, double e)
{
	char error = 0;

	if (e >= 1 && floor(e) != e)
	{
		error_message();
		printf("\n Wrong value of precision! If you entered precision greater than one it must be an integer! \n");
		error = 1;
	}

	if (e < 0.0)
	{
		error_message();
		printf("\n Precision can not be negative! \n");
		error = 1;
	}

	if (e > 8 || e < 1.0e-8)
	{
		error_message();
		printf("\n Precision is too small! \n");
		error = 1;
	}

	if (fabs(x1) > 1.0e3 || fabs(x1) < 1.0e-3 && x1 != 0)
	{
		error_message();
		printf("\n Value of first number is too big or too small! \n");
		error = 1;
	}

	if (fabs(x2) > 1.0e3 || fabs(x2) < 1.0e-3 && x2 != 0)
	{
		error_message();
		printf("\n Value of second number is too big or too small! \n");
		error = 1;
	}

	if (fabs(dx) > 1.0e2 || fabs(dx) < 1.0e-2 && dx != 0)
	{
		error_message();
		printf("\n Value of step is too small or too big! \n");
		error = 1;
	}

	if (dx == 0.0)
	{
		error_message();
		printf("\n Step can not be zero!\n");
		error = 1;
	}

	if (x1 > x2 && dx > 0.0)
	{
		error_message();
		printf("\n If first number is greater than second, Step must be negative!\n");
		error = 1;
	}

	if (x1 < x2 && dx < 0.0)
	{
		error_message();
		printf("\n If first number is lower than second, Step must be positive!\n");
		error = 1;
	}

	return error;
}

char choose_table()
{
	char decision = 0;

	printf("\n Choose trigonometric function (1 - sine; 2 - cosine): ");

	while (1)
	{
		decision = getch();

		if (decision == '1' || decision == '2')
		{
			printf("%c\n", decision);
			return decision - '1';
		}
		else
		{
			printf("\nInvalid input. Please, try again: ");
		}
	}
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

void print_sine_table(double x1, double x2, double dx, double e)
{
	int limit = (floor)((x2 - x1) / dx + 1);
	double x1_degree = x1;

	while (x1_degree > 360)
	{
		x1_degree -= 360;
	}
	while (x1_degree < -360)
	{
		x1_degree += 360;
	}

	for (int i = 0; i < limit; i++)
	{
		double x = x1_degree * PI / 180;
		double delta = x;
		double sinx = delta;
		int n = 1;

		while (fabs(delta) > e)
		{
			n = n + 2;
			delta = -delta * x * x / (n * (n - 1));
			sinx = sinx + delta;
		}

		if (is_zero(sinx) || is_zero(sin(x)))
		{
			printf(" | %-8.5g | %-12.5g| %-12.5g| %-12.5g | \n", x1, 0.0, 0.0, sin(x) - sinx);
		}
		else
		{
			printf(" | %-8.5g | %-12.10g| %-12.10g| %-12.10g | \n", x1, sin(x), sinx, sin(x) - sinx);
		}

		x1_degree += dx;
		x1 += dx;
	}
}

void print_cosine_table(double x1, double x2, double dx, double e)
{
	int limit = (floor)((x2 - x1) / dx + 1);
	double x1_degree = x1;

	while (x1_degree > 360)
	{
		x1_degree -= 360;
	}
	while (x1_degree < -360)
	{
		x1_degree += 360;
	}

	for (int i = 0; i < limit; i++)
	{
		double x = x1_degree * PI / 180;
		double delta = 1;
		double cosx = 1;
		int n = 1;

		while (fabs(delta) > e)
		{
			delta = -delta * x * x / (2 * n * (2 * n - 1));
			cosx = cosx + delta;
			n += 1;
		}

		if (is_zero(cosx) || is_zero(cos(x)))
		{
			printf(" | %-8.5g | %-12.5g| %-12.5g| %-12.5g | \n", x1, 0.0, 0.0, cos(x) - cosx);
		}
		else
		{
			printf(" | %-8.5g | %-12.5g| %-12.5g| %-12.5g | \n", x1, cos(x), cosx, cos(x) - cosx);
		}

		x1_degree += dx;
		x1 += dx;
	}
}

int main()
{
	double x1;
	double x2;
	double e;
	double dx;

	do
	{
		print_header();

		printf("Enter first number (x1): ");
		x1 = get_double();

		printf("Enter last number (x2): ");
		x2 = get_double();

		printf("Enter precision (0.001, 3, 1e-3): ");
		e = get_double();

		printf("Enter step (from 0.01 to 100): ");
		dx = get_double();

		if (e >= 1)
		{
			e = pow(10, -e);
		}

		if (!check_variables(x1, x2, dx, e))
		{
			if (!choose_table())
			{
				print_header();
				printf("  ~~ Rad ~~  ~~ Library ~~  ~~ Taylor ~~   ~~ Delta ~~\n");
				printf("      x           sin           sin          sin-Tsin\n\n");
				print_sine_table(x1, x2, dx, e);
			}
			else
			{
				print_header();
				printf("  ~~ Rad ~~  ~~ Library ~~  ~~ Taylor ~~   ~~ Delta ~~\n");
				printf("      x           cos           cos          cos-Tcos\n\n");
				print_cosine_table(x1, x2, dx, e);
			}
		}
	} while (restart_programm());

	return 0;
}