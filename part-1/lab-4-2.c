#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>

void print_header() {
	printf("\n\t<<~~~ Number sorting program ~~~>>\n\n\n");
}

void error_message() {
	printf("\n  _____ ____  ____   ___  ____  \n");
	printf(" | ____|  _ \\|  _ \\ / _ \\|  _ \\ \n");
	printf(" |  _| | |_) | |_) | | | | |_) |\n");
	printf(" | |___|  _ <|  _ <| |_| |  _ < \n");
	printf(" |_____|_| \\_\\_| \\_\\\\___/|_| \\_\\\n");
}

char restart_programm() {
	printf("\n\n Press 'Enter' to restart programm\n");
	return (_getch() == '\r') ? 1 : 0;
}

char make_decision(char decision = 0) {
	printf(" Choose order "  "(1 - in ascending, 2 - in descending): ");
	do {
		decision = _getche();

		if (decision == '1') {
			decision = 0;
		}
		else if (decision == '2') {
			decision = 1;
		}
		else {
			if (decision == '\r') {
				printf("\n Please, type something: ");
			}
			else {
				printf(" - Wrong answer!\n"  " Please, try againg: ");
			}
			decision = 2;
		}
	} while (decision == 2);

	_getch();

	return decision;
}
int get_integer() {
	char check = 0;
	char buf = 0;
	int number;

	printf(" Enter amount of numbers "  "(0 - 100): ");

	do {
		if (scanf("%d%c", &number, &buf) && buf == '\n') {
			if (!(number > 100 || number <= 0))	{
				check = 1;
			}
			else {
				error_message();
				printf("\n Entered number is too big or too small!\n"  "\n Please, try again: ");
			}
		}
		else {
			error_message();
			printf("\n Entered number is not an integer!\n"  "\n Please, try again: ");
			while ((buf = getchar()) != '\n' && buf != EOF);
		}
	} while (!check);

	return number;
}
double get_double() {
	char check = 0;
	char buf = 0;
	double number;

	do {
		if (scanf("%lf%c", &number, &buf) && buf == '\n') {
			if (!(isinf(number) || isnan(number) || fabs(number) < 1e-9 && number != 0 || fabs(number) > 1e9)) {
				check = 1;
			}
			else {
				error_message();
				printf("\n Entered number is too big or too small!\n"  "\n Please, try again: ");
			}
		}
		else {
			error_message();
			printf("\n Entered number is not a float!\n"  "\n Please, try again: ");
			while ((buf = getchar()) != '\n' && buf != EOF);
		}
	} while (!check);

	return number;
}

double *innit_array(int array_size) {
	double* array = (double*)malloc(array_size * sizeof(double));

	if (array == NULL) {
		printf("\n Failed to allocate memory\n");
		exit(1);
	}
	
	return array;
}

void fill_array(double *array, int amount){
	for (int i = 0; i < amount; i++){
		printf(" Enter number %d: " , i + 1);
		array[i] = get_double();
	}
}

void sort_array(double* array, int amount){
	for (int i = 0; i < amount - 1; i++){
		for (int j = i + 1; j < amount; j++){
			if (array[i] > array[j]){
				double reverse = array[i];
				array[i] = array[j];
				array[j] = reverse;
			}
		}
	}
}

void print_array(double* array, int amount, int is_backwards){
	printf( "\n  ~~~~~ Sorted array ~~~~~\n\n");

	if (!is_backwards){
		for (int i = 0; i < amount; i++){
			printf(" %d. "  "%.7g\n" , i + 1, array[i]);
		}
	}
	else{
		for (int i = amount - 1; i >= 0; i--){
			printf(" %d. "  "%.7g\n" , amount - i, array[i]);
		}
	}
}

int main(){
	do{
		int amount;
		int is_backwards;
		double *array;

		print_header();

		amount = get_integer();
		is_backwards = make_decision();
		array = innit_array(amount);

		print_header();

		fill_array(array, amount);
		sort_array(array, amount);
		print_array(array, amount, is_backwards);

		free(array);

	} while (restart_programm());

	return 0;
}