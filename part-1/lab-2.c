#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>

void print_line()
{
	printf("-----------------------------\n");
}

int main()
{
	int error = 0;
	int again = 0;
	float a;
	float b;
	float c;
	char buf;

	do
	{
		print_line();
		printf("Enter three sides of triangle:\n");

		do
		{
			scanf("%f %f %f%c", &a, &b, &c, &buf);

			if (a < b + c && b < a + c && c < a + b && buf == '\n')
			{
				error = 0;
				print_line();
			}
			else
			{
				print_line();
				printf("Such triangle does not exist.\nPlease write another numbers:\n");
				error = 1;
				while (getchar() != '\n'){}
			}
		} while (error == 1);

		float p = (a + b + c) / 2;
		float area = sqrt(p * (p - a) * (p - b) * (p - c));
		float height = 2 * sqrt(p * (p - a) * (p - b) * (p - c));

		printf("The area of triangle is: %.4f\n", area);
		printf("The perimetr of triangle is: %.4f\n\n", p * 2);

		printf("The A height is: %.4f\n", height / a);
		printf("The B height is: %.4f\n", height / b);
		printf("The C height is: %.4f\n\n", height / c);

		printf("The A bisector is: %.4f\n", 2 * sqrt(b * c * p * (p - a)) / (b + c));
		printf("The B bisector is: %.4f\n", 2 * sqrt(a * c * p * (p - b)) / (a + c));
		printf("The C bisector is: %.4f\n\n", 2 * sqrt(b * a * p * (p - c)) / (b + a));

		printf("The A median is: %.4f\n", 0.5 * sqrt(2 * b * b + 2 * c * c - a * a));
		printf("The B median is: %.4f\n", 0.5 * sqrt(2 * a * a + 2 * c * c - b * b));
		printf("The C median is: %.4f\n", 0.5 * sqrt(2 * b * b + 2 * a * a - c * c));

		print_line();

		printf("\nPress 'y' to continue calculating\n");
		char confirm = getch();

		if (confirm == 'y' || confirm == 'Y')
		{
			again = 0;
			a, b, c = 0;
		}
		else
		{
			again = 1;
		}

	} while (again == 0);

	return 0;
}