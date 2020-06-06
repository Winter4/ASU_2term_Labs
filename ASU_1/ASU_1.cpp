#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

void read_file(int* A, int *n)
{
	FILE* file;
	char name[11];
	do {
		printf("Введите имя файла для считывания: ");
		scanf("%s", name);

		file = fopen(name, "r");
	} while (file == NULL);
	int i = 0;

	while (!(feof(file))) 
		fscanf(file, "%d", &A[i++]);
	
	fclose(file);
	*n = --i;
}

void print_array(int A[40], int n)
{
	for (int i = 0; i < n; i++)
		printf("%-5d", A[i]);
}

void transform_array(int* A, int n)
{
	for (int i = 2; i < n; i += 3)
		A[i] = A[i - 2] * A[i - 1];
}

int main()
{
	setlocale(LC_ALL, "russian");
	int Array[40], n;

	read_file(&Array[0], &n);
	printf("\nИсходный массив: \n");
	print_array(Array, n);

	transform_array(&Array[0], n);

	printf("\n\nПреобразованный массив: \n");
	print_array(Array, n);

	printf("\n");
	system("pause");
	return 0;
}