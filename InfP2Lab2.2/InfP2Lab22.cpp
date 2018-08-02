// InfP2Lab2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int maxGrades = 5;
int minGrades = 2;
int lowGrade = 0;
int topGrade = 99;

struct FIO
{
	char* firstName;
	char* lastName;
};

struct Students
{
	FIO fio;
	int numGrades;
	int* grades;
	int midGrade;
};

struct List
{
	Students* student;
	int count;
};

List createList();
Students createDefaultStudent(char* fName, char* lName);
Students createStudent();
void countMidGrade(List list);
void addStudent(List* list, Students student);
void showStudent(Students student);
void showList(List list);
void deleteStudent(Students student);
void removeStudent(List* list);
void sortLastName(List list);
void searchLName(List list);
void menu(List list);
void outMenu();

void main()
{
	outMenu();
	List list = createList();
	addStudent(&list, createDefaultStudent("Ivan", "Petrov"));
	addStudent(&list, createDefaultStudent("Sergey", "Bodrov"));
	addStudent(&list, createDefaultStudent("Aleksandr", "Kravchenko"));
	addStudent(&list, createDefaultStudent("Maria", "Serova"));
	addStudent(&list, createDefaultStudent("Vika", "Agapova"));
	menu(list);
}



List createList()
{
	return { NULL, 0 };
}

void countMidGrade(List list)
{
	int number;
	printf("Enter number of student to count Average grade: ");
	scanf("%d", &number);
	if (number<0 || number> list.count)
	{
		printf("---No any notes---\n");
		return;
	}
	int sum = 0;
	int i;
	for (i = 0; i < list.student[number - 1].numGrades; i++)
	{
		sum += list.student[number - 1].grades[i];
	}
	sum = sum / i;
	printf("Average grade of sudent %s %s: %d\n", list.student[number - 1].fio.lastName, list.student[number - 1].fio.firstName, sum);
}

Students createDefaultStudent(char* fName, char* lName)
{
	Students student;
	student.fio.firstName = (char*)malloc(strlen(fName) + 1);
	strcpy(student.fio.firstName, fName);

	student.fio.lastName = (char*)malloc(strlen(lName) + 1);
	strcpy(student.fio.lastName, lName);

	student.numGrades = maxGrades;
	student.grades = (int*)malloc(student.numGrades * sizeof(int));

	for (int i = 0; i < student.numGrades; i++)
	{
		student.grades[i] = rand() % 100;
	}

	return student;
}

Students createStudent()
{
	Students student;
	char fName[100];
	char lName[100];
	do 
	{
		printf("Input firstname(10 symbols): ");
		scanf("%s", &fName);
	} while (strlen(fName) > 10);
	do
	{
		printf("Input lastname(10 symbols): ");
		scanf("%s", &lName);
	} while (strlen(lName) > 10);
	student.fio.firstName = (char*)malloc(strlen(fName) + 1);
	strcpy(student.fio.firstName, fName);

	student.fio.lastName = (char*)malloc(strlen(lName) + 1);
	strcpy(student.fio.lastName, lName);

	do
	{
		printf("Input quantity of grades(min 2, max 5): ");
		scanf("%d", &student.numGrades);
	} while (student.numGrades < minGrades || student.numGrades>maxGrades);
	student.grades = (int*)malloc(student.numGrades * sizeof(int));

	for (int i = 0; i < student.numGrades; i++)
	{
		do
		{
			printf("Input grade %d(0-99): ", (i + 1));
			scanf("%d", &student.grades[i]);
		} while (student.grades[i] < lowGrade || student.grades[i]>topGrade);
	}
	printf("---Student Created---\n");

	return student;
}

void addStudent(List* list, Students student)
{
	list->student = (Students*)realloc(list->student, (list->count + 1) * sizeof(student));
	list->student[list->count] = student;
	list->count++;
}

void showStudent(Students student)
{
	printf("|%10s %10s|", student.fio.lastName, student.fio.firstName);
	printf("%2d |", student.numGrades);
	printf(" ");
	for (int i = 0; i < student.numGrades; i++)
	{
		printf("%2d ", student.grades[i]);
	}
	int table = maxGrades - student.numGrades;
	for (int i = student.numGrades; i < maxGrades; i++)
	{
		printf("** ");
	}
	printf("|\n");
	printf("-----------------------------------------------\n");
}

void showList(List list)
{
	printf("|No|         FIO         |All|     Grades     |\n");
	printf("-----------------------------------------------\n");
	for (int i = 0; i < list.count; i++)
	{
		printf("|%2d", i + 1);
		showStudent(list.student[i]);
	}
}

void deleteStudent(Students student)
{
	free(student.fio.firstName);
	free(student.fio.lastName);
}

void removeStudent(List* list)
{
	int number;
	printf("Input number of student to Delete: ");
	scanf("%d", &number);
	number -= 1;
	if (number<0 || number> list->count)
	{
		printf("---No any notes---\n");
		return;
	}
	printf("---Deleted note %s %s---\n", list->student[number].fio.firstName, list->student[number].fio.lastName);
	deleteStudent(list->student[number]);
	if (number == list->count - 1)
	{
		list->count--;
	}
	else
	{

		for (int i = number; i < list->count - 1; i++)
		{

			list->student[i] = list->student[i + 1];

		}
		list->count--;
	}
}

void sortLastName(List list)
{
	Students* sortSt = list.student;
	int n = list.count;
	for (int i = 0; i < list.count - 1; i++)
	{
		for (int j = (list.count - 1); j > i; j--)
		{
			int n = strcmp(list.student[j - 1].fio.lastName, list.student[j].fio.lastName);
			if (n > 0)
			{
				Students temp = sortSt[j-1];
				sortSt[j-1] = sortSt[j];
				sortSt[j] = temp;
			}
		}
	}
	printf("---Sorted---\n");
}

void searchLName(List list)
{
	char search[10];
	printf("Input lastname for search: ");
	scanf("%s", &search);
	for (int i = 0; i < list.count; i++)
	{
		char* match = strstr(list.student[i].fio.lastName, search);
		if (match != NULL)
		{
			printf("%d. ", i + 1);
			showStudent(list.student[i]);
		}
	}
}

void outMenu()
{
	printf("Select an action\n");
	printf("| 1 | Show list      |\n");
	printf("----------------------\n");
	printf("| 2 | Add a note     |\n");
	printf("----------------------\n");
	printf("| 3 | Delete note    |\n");
	printf("----------------------\n");
	printf("| 4 | Sort lastname  |\n");
	printf("----------------------\n");
	printf("| 5 | Search         |\n");
	printf("----------------------\n");
	printf("| 6 | Average grade  |\n");
	printf("----------------------\n");
	printf("| 0 | Exit           |\n");
	printf("----------------------\n");
}

void menu(List list)
{
	while (true)
	{
		int key = _getch();
		switch (key)
		{
		case 0x31:
			showList(list);
			break;
		case 0x32:
			addStudent(&list, createStudent());
			break;
		case 0x33:
			removeStudent(&list);
			break;
		case 0x34:
			sortLastName(list);
			break;
		case 0x35:
			searchLName(list);
			break;
		case 0x36:
			countMidGrade(list);
			break;
		case 0x30:
			exit(0);
			break;
		}
	}
}