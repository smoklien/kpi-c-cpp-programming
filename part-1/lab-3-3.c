#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>

#define PI 3.14159265

void print_header()
{
	printf("\n\t<<<~~~~~ Cubic Equation Calculator ~~~~~>>>\n\n");
}

void print_menu()
{
	char decision = 0;
	printf("\n   <<<~~~~~ Cubic Equation Calculator ~~~~~>>>\n\n\n\n");
	printf("\n Press "
		   "'Enter'"
		   " to start the program.\n Press "
		   "'i'"
		   " to see further information.\n Press "
		   "'e'"
		   " to exit");

	do
	{
		decision = getch();

		if (decision == 'e')
		{
			exit(0);
		}
		else if (decision == '\r')
		{
			print_header();
			printf("   3    2             \n");
			printf("  x + ax + bx + c = 0 \n");
			printf("\n *~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n\n");
		}
		else if (decision == 'i')
		{
			print_header();
			printf("  a, b, c"
				   " - Coefficients.\n");
			printf("           2          3         \n");
			printf("          a         2a    ab    \n");
			printf("  p = b - -- ,  q = --- - -- + c"
				   " - Variable substitutions.\n");
			printf("           3        27     3    \n");
			printf("       3    2\n");
			printf("      p    q \n");
			printf("  d = -- + --"
				   " - Discriminant.\n");
			printf("      27    4\n\n");
			printf("Press "
				   "'b'"
				   " to return to the main menu or "
				   "'e'"
				   " to exit.");

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
					printf("\n Please, press 'b' or 'e': ");
					decision = 0;
				}
			} while (decision == 0);
		}
		else
		{
			printf("\n Please, press 'Enter', 'i' or 'e': ");
			decision = 0;
		}
	} while (decision == 0);
}

void error_message()
{
	printf("  _____ ____  ____   ___  ____  \n");
	printf(" | ____|  _ \\|  _ \\ / _ \\|  _ \\ \n");
	printf(" |  _| | |_) | |_) | | | | |_) |\n");
	printf(" | |___|  _ <|  _ <| |_| |  _ < \n");
	printf(" |_____|_| \\_\\_| \\_\\\\___/|_| \\_\\ \n");
}

int restart_programm()
{
	printf("\n Press 'Enter' to restart programm\n");
	return (_getch() == '\r') ? 1 : 0;
}

int check_value(double value)
{
	return (isinf(value) || isnan(value)) ? 0 : 1;
}

int is_zero(double value)
{
	return (fabs(value) > 1e-10f || value == 0) ? 0 : 1;
}

double get_double()
{
	char check = 0, buf = 0;
	double number;

	do
	{
		if (scanf("%lf%c", &number, &buf) && buf == '\n')
		{
			if (check_value(number) && !is_zero(number))
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
			printf("\n Entered number is not a float!\n"
				   "\n Please, try again: ");
			while ((buf = getchar()) != '\n' && buf != EOF)
				;
		}
	} while (check == 0);

	return number;
}

void positive_discriminant(double p, double q, double d, double a)
{
	double y = -q / 2 + sqrt(d);
	double u = (y >= 0) ? (pow(y, 1 / 3.)) : (pow(fabs(y), 1 / 3.) * -1);
	double v = -p / (3 * u);

	if (check_value(y) && check_value(u) && check_value(v))
	{
		double y1 = u + v;
		double y2_real = -(u + v) / 2;
		double y2_im = sqrt(3) * (u - v) / 2;

		double x1 = y1 - a / 3;
		double x2_real = y2_real - a / 3;

		printf(" y = %g\n u = %g\n v = %g\n\n", y, u, v);
		printf(" y1 = %g\n y2 = ", y1);

		if (!is_zero(y2_real))
			printf("%g ", y2_real);
		if (!is_zero(y2_im))
			printf("+ i * %g", y2_im);
		if (!(y2_real || y2_im))
			printf("0");

		printf("\n y3 = ");

		if (!is_zero(y2_im))
			printf("%g ", y2_real);
		if (!is_zero(y2_im))
			printf("- i * %g", y2_im);
		if (!(y2_real || y2_im))
			printf("0");

		printf("\n\n *~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n\n");
		printf(" x1 = %g\n x2 = ", x1);

		if (!is_zero(x2_real))
			printf("%g ", x2_real);
		if (!is_zero(y2_im))
			printf("+ i * %g", y2_im);
		if (!(x2_real || y2_im))
			printf("0");

		printf("\n x3 = ");

		if (!is_zero(x2_real))
			printf("%g ", x2_real);
		if (!is_zero(y2_im))
			printf("- i * %g", y2_im);
		if (!(x2_real || y2_im))
			printf("0");

		printf("\n");
	}
	else
	{
		error_message();
		printf("\n Calculations can be wrong (v = 0) !\n");
	}
}

void zero_discriminant(double p, double q, double d, double a)
{
	double y1 = 3 * q / p;
	double y2 = -3 * q / (2 * p);

	if (check_value(y1) && check_value(y2))
	{
		double x1 = y1 - a / 3;
		double x2 = y2 - a / 3;

		printf(" y1 = %g\n y2 = %g\n y3 = %g\n", y1, y2, y2);
		printf("\n *~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n\n");
		printf(" x1 = %g\n x2 = %g\n x3 = %g\n", x1, x2, x2);
	}
	else
	{
		error_message();
		printf("\n Calculations can be wrong (p = 0) !\n");
	}
}

void negative_discriminant(double p, double q, double d, double a)
{
	double r = -pow(p, 3) / 27;
	double fi = 0;
	r = sqrt(r);
	fi = acos(-q / (2 * r));

	if (check_value(r) && check_value(fi))
	{
		double r_root = (r > 0) ? (pow(r, 1 / 3.)) : (pow(fabs(r), 1 / 3.) * -1);
		double y1 = 2 * fabs(r_root) * cos(fi / 3);
		double y2 = 2 * fabs(r_root) * cos((fi + 2 * PI) / 3);
		double y3 = 2 * fabs(r_root) * cos((fi + 4 * PI) / 3);

		printf(" r = %g\n fi = %g\n\n", r, fi);

		if (check_value(y1) && check_value(y2) && check_value(y3))
		{
			double x1 = y1 - a / 3;
			double x2 = y2 - a / 3;
			double x3 = y3 - a / 3;

			printf(" y1 = %g\n y2 = %g\n y3 = %g\n", y1, y2, y3);
			printf("\n *~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n\n");
			printf(" Approximate result (d < 0) !\n\n");
			printf(" x1 = %g\n x2 = %g\n x3 = %g\n", x1, x2, x3);
		}
	}
	else
	{
		error_message();
		printf("\n Calculations can be wrong (r <= 0) !\n\n");
	}
}

void solve_cubic_equation(double a, double b, double c)
{
	double p = b - (a * a / 3);
	double q = 2 * pow(a, 3) / 27 - a * b / 3 + c;
	double d = pow(p, 3) / 27 + q * q / 4;

	if (check_value(p) && check_value(q) && check_value(d))
	{
		printf("  x^3 + (%g)x^2 + (%g)x + (%g) = 0 \n", a, b, c);
		printf("\n *~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n\n");
		printf(" p = %g\n q = %g\n d = %g\n\n", p, q, d);

		if (d > 0)
			positive_discriminant(p, q, d, a);
		else if (d == 0)
			zero_discriminant(p, q, d, a);
		else
			negative_discriminant(p, q, d, a);
	}
	else
	{
		error_message();
		printf("\n Answer is too small or too big!\n");
	}

	printf("\n *~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n\n");
}

int main()
{
	do
	{
		double a, b, c;

		print_menu();

		printf(" Enter "
			   "a: ");
		a = get_double();

		printf(" Enter "
			   "b: ");
		b = get_double();

		printf(" Enter "
			   "c: ");
		c = get_double();

		print_header();
		solve_cubic_equation(a, b, c);

	} while (restart_programm());

	return 0;
}