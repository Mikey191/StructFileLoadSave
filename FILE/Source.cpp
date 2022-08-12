#include <iostream>
#include <io.h>
#include <stdio.h>
#include <fstream>
using namespace std;

struct people
{
	char name[255];
	int year;
	char city[255];
};

void loaddata_bin(people* arr, int& size)
{
	FILE* file;
	const char* filename = "FirstFile.txt";
	struct _finddata_t myfileinfo;
	intptr_t done = _findfirst(filename, &myfileinfo);
	if (done == -1)
	{
		fopen_s(&file, filename, "wb");
		fclose(file);
	}
	fopen_s(&file, filename, "rb");
	while (!feof(file))
	{
		fread(&arr[size], sizeof(people), 1, file);
		size++;
	}
	fclose(file);
	size--;
}

void savedata_bin(people* arr, int& size)
{
	FILE* file;
	const char* filename = "FirstFile.txt";
	fopen_s(&file, filename, "wb");
	fwrite(&arr[0], sizeof(people), size, file);
	fclose(file);
}

people add()
{
	people temp;
	cout << "\tEnter info:" << endl;
	cout << "Enter Name: ";
	cin >> temp.name;
	cout << "Enter City: ";
	cin >> temp.city;
	cout << "Enter Year: ";
	cin >> temp.year;
	return temp;
}

void addPeople(people* arr, int& size)
{
	arr[size] = add();
	size++;
}

void deletePeopleName(people* arr, int& size)
{
	people temp;
	int k = -1;
	cout << "Enter Name people for delete: ";
	cin >> temp.name;
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(arr[i].name, temp.name) == 0)
		{
			k = i;
		}
	}
	if (k >= 0)
	{
		for (size_t i = k; i < size - 1; i++)
		{
			arr[i] = arr[i + 1];
		}size--;
	}
}

void showAllPeople(people* arr, int& size)
{
	cout << "\tList people" << endl;
	for (size_t i = 0; i < size; i++)
	{
		cout << "Name : " << arr[i].name << "\t";
		cout << "Year : " << arr[i].year<< "\t";
		cout << "City : " << arr[i].city << "\t";
		cout << endl;
	}
	system("pause");
}


int main()
{
	people arr[1000];
	int size = 0;
	int k;
	loaddata_bin(arr, size);
	do
	{
		//MENU
		system("CLS");
		cout << "\tMENU:" << endl;
		cout << "1 - Show all people;" << endl;
		cout << "2 - Add people;" << endl;
		cout << "3 - Delete people;" << endl;
		cout << "0 - Exit;" << endl;
		cout << "Your choise: ";
		cin >> k;
		switch (k)
		{
		case 1: 
			showAllPeople(arr, size);
			break;
		case 2: 
			addPeople(arr, size);
			break;
		case 3: 
			deletePeopleName(arr, size);
			break;
		}
	} while (k != 0);

	savedata_bin(arr, size);



	return 0;
}