#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

struct term {
	int rusLang;
	int math;
	int coding;
	int phyl;
};


struct student {
	char surname[10];
	char name[10];
	char country[10];
	char faculty[7];
	char group[7];
	term terms[2];
};

void print_struct(student studs[20], int n)
{
	printf("№    Фамилия  Имя     Страна  Факультет  Группа  Сем. 1  Рус. яз.  Мат.  Пр.  Фил.  Сем. 2  Рус. яз.  Мат.  Пр.  Фил. \n");
	for (int i = 0; i < n; i++) {
		printf("%-3d  %-8s %-7s %-7s %-10s %-6s  %12d %7d %5d %5d %14d %6d %5d %5d \n", 
			i + 1, 
			studs[i].surname, 
			studs[i].name, 
			studs[i].country,
			studs[i].faculty, 
			studs[i].group, 
			studs[i].terms[0].rusLang, 
			studs[i].terms[0].math, 
			studs[i].terms[0].coding,
			studs[i].terms[0].phyl, 
			studs[i].terms[1].rusLang, 
			studs[i].terms[1].math, 
			studs[i].terms[1].coding, 
			studs[i].terms[1].phyl);
	}
}

void read_file(student* studs, int* n)
{
	FILE* file;

	do {
		printf("\n Введите имя файла для считывания: ");
		char name[10];
		scanf("%s", &name);

		file = fopen(name, "r");
	} while (file == NULL);

	while (!(feof(file)) && *n < 20) { // 20 - размер массива
		fscanf(file, "%s%s%s%s%s%d%d%d%d%d%d%d%d", &studs[*n].surname, &studs[*n].name, &studs[*n].country, &studs[*n].faculty,
			&studs[*n].group, &studs[*n].terms[0].rusLang, &studs[*n].terms[0].math, &studs[*n].terms[0].coding, &studs[*n].terms[0].phyl,
			&studs[*n].terms[1].rusLang, &studs[*n].terms[1].math, &studs[*n].terms[1].coding, &studs[*n].terms[1].phyl);
		(*n)++;
	}

	fclose(file);
	print_struct(studs, *n);
}

//struct term {
//	int rusLang;
//	int math;
//	int coding;
//	int phyl;
//};

student add_struct()
{
	student newStudent = {};

	printf("\n");

	do {
		printf("Фамилия: ");
		scanf("%s", &newStudent.surname);
	} while (!(strlen(newStudent.surname) > 0));

	do {
		printf("Имя: ");
		scanf("%s", &newStudent.name);
	} while (!(strlen(newStudent.name) > 0));

	do {
		printf("Страна: ");
		scanf("%s", &newStudent.country);
	} while (!(strlen(newStudent.country) > 0));

	do {
		printf("Факультет: ");
		scanf("%s", &newStudent.faculty);
	} while (!(strlen(newStudent.faculty) > 0));

	do {
		printf("Группа: ");
		scanf("%s", &newStudent.group);
	} while (!(strlen(newStudent.group) > 0));

	// ___________________________________________________________________________

	do {
		printf("Сем. 1  Русский яз.: ");
		scanf("%d", &newStudent.terms[0].rusLang);
	} while (!(newStudent.terms[0].rusLang > 0 && newStudent.terms[0].rusLang <= 5));

	do {
		printf("Сем. 1  Математика: ");
		scanf("%d", &newStudent.terms[0].math);
	} while (!(newStudent.terms[0].math > 0 && newStudent.terms[0].math <= 5));

	do {
		printf("Сем. 1  Програм.: ");
		scanf("%d", &newStudent.terms[0].coding);
	} while (!(newStudent.terms[0].coding > 0 && newStudent.terms[0].coding <= 5));

	do {
		printf("Сем. 1  Философия: ");
		scanf("%d", &newStudent.terms[0].phyl);
	} while (!(newStudent.terms[0].phyl > 0 && newStudent.terms[0].phyl <= 5));

	// __________________________________________

	do {
		printf("Сем. 2  Русский яз.: ");
		scanf("%d", &newStudent.terms[1].rusLang);
	} while (!(newStudent.terms[1].rusLang > 0 && newStudent.terms[1].rusLang <= 5));

	do {
		printf("Сем. 2  Математика: ");
		scanf("%d", &newStudent.terms[1].math);
	} while (!(newStudent.terms[1].math > 0 && newStudent.terms[1].math <= 5));

	do {
		printf("Сем. 2  Програм.: ");
		scanf("%d", &newStudent.terms[1].coding);
	} while (!(newStudent.terms[1].coding > 0 && newStudent.terms[1].coding <= 5));

	do {
		printf("Сем. 2  Философия: ");
		scanf("%d", &newStudent.terms[1].phyl);
	} while (!(newStudent.terms[1].phyl > 0 && newStudent.terms[1].phyl <= 5));

	return newStudent;
}

void edit_struct(student* studs, int n)
{
	printf("\n Какую запись редактировать: ");
	int str;
	scanf("%d", &str);

	do {
		printf("Сем. 2  Русский яз.: ");
		scanf("%d", &studs[str - 1].terms[1].rusLang);
	} while (!(studs[str - 1].terms[1].rusLang > 0 && studs[str - 1].terms[1].rusLang <= 5));

	do {
		printf("Сем. 2  Математика: ");
		scanf("%d", &studs[str - 1].terms[1].math);
	} while (!(studs[str - 1].terms[1].math > 0 && studs[str - 1].terms[1].math <= 5));

	do {
		printf("Сем. 2  Програм.: ");
		scanf("%d", &studs[str - 1].terms[1].coding);
	} while (!(studs[str - 1].terms[1].coding > 0 && studs[str - 1].terms[1].coding <= 5));

	do {
		printf("Сем. 2  Философия: ");
		scanf("%d", &studs[str - 1].terms[1].phyl);
	} while (!(studs[str - 1].terms[1].phyl > 0 && studs[str - 1].terms[1].phyl <= 5));

	print_struct(studs, n);
}

void save_structs(student studs[20], int n)
{
	FILE* file;

	do {
		printf("\n Введите имя файла для сохранения: ");
		char name[10];
		scanf("%s", &name);

		file = fopen(name, "w");
	} while (file == NULL);

	for (int i = 0; i < n; i++)
		fprintf (file, "%-3d  %-8s %-4s %-7s %-10s %-6s  %12d %7d %5d %5d %14d %6d %5d %5d \n", 
			i + 1,
			studs[i].surname,
			studs[i].name,
			studs[i].country,
			studs[i].faculty,
			studs[i].group,
			studs[i].terms[0].rusLang,
			studs[i].terms[0].math,
			studs[i].terms[0].coding,
			studs[i].terms[0].phyl,
			studs[i].terms[1].rusLang,
			studs[i].terms[1].math,
			studs[i].terms[1].coding,
			studs[i].terms[1].phyl);
	fclose(file);
}

int main()
{
	setlocale(LC_ALL, "russian");

	student students[20] = {};
	int n = 0;

	do {
		printf("\n 1 - Считать данные из файла \n 2 - Редактировать оценки за 2й семестр \n 3 - Добавить студента \n 4 - Сохранить данные \n 0 - Выход \n");
		int ch;
		scanf("%d", &ch);

		switch (ch) {

		case 1:
			read_file(&students[0], &n);
			break;
		case 2:
			edit_struct(&students[0], n);
			break;
		case 3:
			if (n < 19) {
				students[n++] = add_struct();
				print_struct(students, n);
			}
			else
				printf("\nСлишком много записей.");
			break;
		case 4:
			save_structs(students, n);
			break;
		case 0:
			return 0;
			break;
		}
	} while (true);
}

// Сведения о студентах-иностранцах: фамилия, имя, страна, факультет, группа, оценки по предметам за два семестра обучения . 
// Составить списки студентов-иностранцев по факультетам и по странам.
