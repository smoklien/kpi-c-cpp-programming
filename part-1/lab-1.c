#include <stdio.h>
#include <conio.h>

int roman(int, int, char);

int main() {
	int a;

	printf("Enter Number\n");
	scanf("%d", &a);

	a = roman(a, 1000, 'M');
	a = roman(a, 500, 'D');
	a = roman(a, 100, 'C');
	a = roman(a, 50, 'L');
	a = roman(a, 10, 'X');
	a = roman(a, 5, 'V');
	a = roman(a, 1, 'I');

	return 0;
}

int roman(int i, int j, char c) {
	while (i >= j) {
		putchar(c);
		i = i - j;
	}

	return (i);
}