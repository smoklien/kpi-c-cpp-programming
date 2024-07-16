#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>

int day;
int date;
int month;
int year;
char n = 0;
char error;
char restart_program;
char is_year_leap;

void print_line()
{
	printf("----------------------\n");
}

int main()
{
	do
	{
		print_line();
		printf("Enter your date: (dd.mm.year)\n\n");

		do
		{
			scanf("%d.%d.%d", &day, &month, &year);
			if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1 || year > 9999)
			{
				print_line();
				printf("Wrong date!\nPlease enter correctly: (dd.mm.year)\n\n");
				day, month, year = 0;
				error = 1;
				while (getchar() != '\n'){}
			}
			else
			{
				error = 0;
			}
		} while (error == 1);

		if ((year % 100 != 0 && year % 4 == 0) || (year % 100 == 0 && year % 400 == 0))
		{
			is_year_leap = 1;
		}
		else
		{
			is_year_leap = 0;
		}

		if (month <= 2 && is_year_leap == 1)
		{
			n = 1;
		}
		else if (month <= 2 && is_year_leap == 0)
		{
			n = 2;
		}
		else
		{
			n = 0;
		}

		date = ((int)(365.25 * year) + (int)(30.56 * month) + day + n) % 7;

		print_line();

		switch (date)
		{
		case 0:
			printf("Monday\n");
			break;
		case 1:
			printf("Tuesday\n");
			break;
		case 2:
			printf("Wednesday\n");
			break;
		case 3:
			printf("Thursday\n");
			break;
		case 4:
			printf("Friday\n");
			break;
		case 5:
			printf("Saturday\n");
			break;
		case 6:
			printf("Sunday\n");
			break;
		}

		print_line();
		printf("\nDo you want more?\n(press 'Y' for continue)\n");
		char confirm = getch();

		if (confirm != 'Y' && confirm != 'y')
		{
			restart_program = 0;
			return 0;
		}
		else
		{
			restart_program = 1;
			day, year, month, date, is_year_leap = 0;
		}

	} while (restart_program == 1);

	return 0;
}