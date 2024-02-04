#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

void print_header() {
	printf( "\n\t\t\t<~~~ System of linear equations ~~~>\n\n\n");
}

int ask_user_for_restart(){
	printf("\nPress 'Enter' to restart program\n");
	return (_getch() == '\r') ? 1 : 0;
}

int get_integer(){
	printf(" Enter size of SLE"  " (1 - 100): ");

	char check = 0, buf = 0;
	int number;

	do{
		if (scanf("%d%c", &number, &buf) && buf == '\n'){
			if (!(number > 100 || number <= 0)) {
				check = 1;
			}
			else {
				printf(" Entered number is too big or too small!\n"  "\n Please, try again: ");
			}
		}
		else{
			printf("\n Entered number is not an integer!\n"  "\n Please, try again: ");
			while ((buf = getchar()) != '\n' && buf != EOF);
		}
	} while (!check);

	return number;
}

double get_double() {
	char check = 0, buf = 0;
	double number;

	do {
		if (scanf("%lf%c", &number, &buf) && buf == '\n') {
			if (!(fabs(number) < 1e-6 && number != 0 || fabs(number) > 1e6)) {
				check = 1;
			}
			else{
				printf("\n Entered number is too big or too small!\n"  "\n Please, try again: ");
			}
		}
		else {
			printf("\n Entered number is not a float!\n"  "\n Please, try again: ");
			while ((buf = getchar()) != '\n' && buf != EOF);
		}
	} while (!check);

	return number;
}

double** innit_array(int array_size){
	double** array = (double**)malloc(array_size * sizeof(double*));
	if (array == NULL) {
		printf("Failed to allocate memory\n");
		exit(1);
	}
	for (int i = 0; i < array_size; i++) {
		array[i] = (double*)malloc(array_size * sizeof(double));
		if (array[i] == NULL) {
			printf("Failed to allocate memory\n");
			for (int j = 0; j < i; j++) {
				free(array[j]);
			}
			free(array);
			exit(1);
		}
	}
	return array;
}

void fill_sle(double** a, double* b, int size) {
	for (int i = 0; i < size; i++) {
		printf("\n");

		for (int j = 0; j < size + 1; j++) {
			if (j == size) {
				printf( "\n Enter constant"  " %d: ", i + 1);
				b[i] = get_double();
			}
			else {
				printf( " Enter coefficient"  " %d-%d: ", i + 1, j + 1);
				a[i][j] = get_double();
			}
		}
	}
}

void print_sle(double** a, double* b, int size) {
	print_header();
	printf("\n Your SLE:\n\n");

	double eps = 1e-6;		//��������

	for (int i = 0; i < size; i++) {
		if (size == 1) {
			printf("\n  %gx  =  %g", a[0][0], b[0]);
			break;
		}
		else if (i == 0){
			printf("\n\t / ");		
		}
		else if (i < size - 1)	{
			printf("\n\t|  ");
		}
		else{
			printf("\n\t \\ ");
		}

		for (int j = 0; j < size + 1; j++) {
			if (j == size) {
				printf("="  "%5g" , b[i]);

				if (i == 0){
					printf(" \\");
				}
				else if (i < size - 1){
					printf("  |");
				}
				else{
					printf(" /");
				}
			}
			else {
				if (a[i][j] < 0){
					printf("-");
				}
				else if (j > 0){
					printf("+");
				}
				printf("%5g * x%-5d", fabs(a[i][j]), j + 1);
			}
		}
	}
}

int check_result(double **a, double *b, int size) {
	for (int i = 0; i < size; i++){
		double sum = 0;

		for (int j = 0; j < size; j++) {
			if (j != i){
				sum += a[i][j];
			}
		}
		if (fabs(a[i][i]) <= fabs(sum)) {
			printf( "\n\n\n Sorry, but we can not calculate these numbers!\n"  "\n Error in line %d\n" , i + 1);
			return 1;
		}
	}
	return 0;
}

void print_result(double **a, double *b, int size) {
	printf("\n\n\n Results:\n\n");

	double delta = 1;
	double eps = 1e-6;
	double *xp = (double*)malloc(size * sizeof(double));
	double *x = (double*)malloc(size * sizeof(double));

	if (xp == NULL) {
		printf("Failed to allocate memory\n");
		exit(1);
	}

	if (x == NULL) {
		printf("Failed to allocate memory\n");
		exit(1);
	}

	for (int i = 0; i < size; i++)	{
		xp[i] = b[i] / a[i][i];
	}

	while (fabs(delta) > eps) {
		delta = 0;

		for (int i = 0; i < size; i++){
			double sum = 0;

			for (int j = 0; j < size; j++) {
				if (j != i) {
					sum += a[i][j] * xp[j];
				}
			}
			x[i] = (b[i] - sum) / a[i][i];

			if (fabs(x[i] - xp[i]) > delta) {
				delta = fabs(x[i] - xp[i]);
			}

			xp[i] = x[i];
		}
	}

	for (int i = 0; i < size; i++) {
		printf( "  x%d = %g\n" , i + 1, x[i]);
	}
}

int main() {
	do {
		print_header();

		int	size = get_integer();
		double** coefficients = innit_array(size);
		double* constants = (double*)malloc(size * sizeof(double*));
		if (constants == NULL) {
			printf("Failed to allocate memory\n");
			return 1;
		}

		fill_sle(coefficients, constants, size);
		print_sle(coefficients, constants, size);
		if (!check_result(coefficients, constants, size)) {
			print_result(coefficients, constants, size);
		}

		for (int i = 0; i < size; i++) {
			free(coefficients[i]);
		}
		free(coefficients);
		free(constants);

	} while (ask_user_for_restart() == 1);

	return 0;
}