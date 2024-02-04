#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>

int day, date, month, year;
int buf;
char n = 0;
bool wrong_num_check, restart_prog, leap_year;

void big_line() {
	printf("----------------------\n");
}

int main() {
	do {
		big_line();
		printf("Enter your date: (dd.mm.year)\n\n");

		do {
			scanf("%d.%d.%d", &day, &month, &year);
			if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1 || year > 9999) {
				system("cls");
				big_line();
				printf("Wrong date!\nPlease enter correctly: (dd.mm.year)\n\n");
				day, month, year = 0;
				wrong_num_check = true;
				while (getchar() != '\n') {}
			}
			else{
				wrong_num_check = false;
			}
		} while (wrong_num_check == true);


		if ((year % 100 != 0 && year % 4 == 0) || (year % 100 == 0 && year % 400 == 0)) {
			leap_year = true;
		}
		else{
			leap_year = false;
		}
		if (month <= 2 && leap_year == true){
			n = 1;
		}
		else if (month <= 2 && leap_year == false) {
			n = 2;
		}
		else {
			n = 0;
		}

		date = ((int(365.25 * year) + int(30.56 * month) + day + n) % 7);

		big_line();

		switch (date) {
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

		big_line();
		printf("\nDo you want more?\n(press 'Y' for continue)\n");
		char confirm = _getch();

		if (confirm != 'Y' && confirm != 'y'){
			restart_prog = false;
			return 0;
		}
		else {
			restart_prog = true;
			day, year, month, date, leap_year = 0;
		}

	} while (restart_prog == true);

	return 0;
}