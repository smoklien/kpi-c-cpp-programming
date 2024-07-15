#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

void print_header()
{
	printf("\n\t\t\t<~~~ Nonlinear equations calculator ~~~>\n\n\n");
}

void error_message()
{
	printf("\n\n  _____ ____  ____   ___  ____  \n");
	printf(" | ____|  _ \\|  _ \\ / _ \\|  _ \\ \n");
	printf(" |  _| | |_) | |_) | | | | |_) |\n");
	printf(" | |___|  _ <|  _ <| |_| |  _ < \n");
	printf(" |_____|_| \\_\\_| \\_\\\\___/|_| \\_\\ \n");
}

int restart_program()
{
	printf("\nPress 'Enter' to restart program\n");
	return (getch() == '\r') ? 1 : 0;
}

char make_decision(int *choices_made)
{
	if (*choices_made)
	{
		printf("\n --------------------------------------\n\n");
		printf(" Choose method:\n"
			   "\n 1. Interval halving\n 2. Nethon's method");
	}
	else
	{
		printf(" Choose equation:\n"
			   "\n 1. cos(y/x) - 2 * sin(1/x) + 1/x = 0\n 2. sin(ln(x)) - cos(ln(x)) + y * ln(x) = 0");
		*choices_made = +1;
	}

	char decision = 0;

	do
	{
		decision = getch();
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
				printf(" Wrong answer!\n"
					   " Please, try againg: ");
			}

			decision = 2;
		}
	} while (decision == 2);

	return decision;
}

double get_double(int *numbers_entered)
{
	char check = 0, buf = 0;
	double number;

	switch (*numbers_entered)
	{
	case 0:
		printf("\n\n --------------------------------------\n\n");
		printf(" Enter first number "
			   "(a): ");
		break;
	case 1:
		printf(" Enter last number "
			   "(b): ");
		break;
	case 2:
		printf(" Enter constant "
			   "(y): ");
		break;
	case 3:
		printf(" Enter precision "
			   "(0.001, 3, 1e-3): ");
		break;
	}

	do
	{
		if (scanf("%lf%c", &number, &buf) && buf == '\n')
		{
			if (!(isinf(number) || isnan(number)))
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
	} while (!check);

	*numbers_entered = *numbers_entered + 1;

	return number;
}

bool error_check(double a, double b, double *eps)
{
	bool error = false;

	if (*eps < 0.0)
	{
		error_message();
		printf("\n Precision can not be negative! \n");
		error = true;
	}

	if (fabs(*eps) < 1.0e-9 && *eps != 0 || *eps > 9.0)
	{
		error_message();
		printf("\n Precision is too small! \n");
		error = true;
	}
	else if (*eps >= 1)
	{
		*eps = pow(10, -*eps);
	}

	if (a >= b)
	{
		error_message();
		printf("\n Last number of interval should be greater than first! \n");
		error = true;
	}

	if (fabs(a) < 1.0e-7 && a != 0 || fabs(a) > 1e7)
	{
		error_message();
		printf("\n First number is too large or too small! \n");
		error = true;
	}

	if (fabs(b) < 1.0e-7 && b != 0 || fabs(b) > 1e7)
	{
		error_message();
		printf("\n Last number is too large or too small! \n");
		error = true;
	}

	return error;
}

double first_equation(double x, double y)
{
	return (cos(y / x) - 2 * sin(1 / x) + 1 / x);
}

double second_equation(double x, double y)
{
	return (sin(log(x)) - cos(log(x)) + y * log(x));
}

double halving_root(double (*any_equation)(double, double), double l, double h, double y, double eps)
{
	double x = 0.0;

	while (fabs(h - l) > eps)
	{
		x = (l + h) / 2.0;
		((any_equation)(l, y) * (any_equation)(x, y) > 0) ? (l = x) : (h = x);

		if (isnan(x) || isinf(x))
		{
			return nan("");
		}
	}

	return x;
}

double newton_root(double (*any_equation)(double, double), double l, double h, double y, double eps)
{
	double delta, derivative, x = h;
	int max_iter = 100;

	do
	{
		derivative = ((any_equation)(x + eps, y) - (any_equation)(x, y)) / eps;
		delta = (any_equation)(x, y) / derivative;
		x = x - delta;

		if (fabs(derivative) < eps)
		{
			printf("Newton's method is not converging\n");
			return nan("");
		}

		if (isnan(x) || isinf(x))
		{
			return nan("");
		}

		if (--max_iter < 0)
		{
			printf(" Max iterations exceeded\n");
			break;
		}

	} while (fabs(delta) > eps);

	return x;
}

void print_answer(double answer, double eps)
{
	if (!isnan(answer))
	{
		printf("\n\n ------->> The answer is: "
			   "%.*g",
			   (int)(-log10(eps)) + 1, answer);
	}
	else
	{
		error_message();
		printf("\n Something went wrong! Answer could be too large or too small!\n");
	}
}

int main()
{
	double answer;
	double a;
	double b;
	double y;
	double eps;
	char equation;
	char method;

	do
	{
		int choices_made = 0;
		int numbers_entered = 0;
		double (*any_equation[])(double, double) = {first_equation, second_equation};

		print_header();

		equation = make_decision(&choices_made);
		a = get_double(&numbers_entered);
		b = get_double(&numbers_entered);
		y = get_double(&numbers_entered);
		eps = get_double(&numbers_entered);

		if (!error_check(a, b, &eps))
		{
			method = make_decision(&choices_made);

			if (method)
			{
				answer = newton_root((*any_equation[equation]), a, b, y, eps);
			}
			else
			{
				answer = halving_root((*any_equation[equation]), a, b, y, eps);
			}

			print_answer(answer, eps);
		}
	} while (restart_program());

	return 0;
}