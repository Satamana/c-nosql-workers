#include<iostream>
#include<conio.h>
#include<iomanip>
#include<windows.h>
using namespace std;
struct coop
{
	char sname[15];
	short age;
};
void get(char *&str)
{
	str = NULL;
	int n = 0;
	char ch;
	while ((ch = getchar()) != '\n')
	{
		str = (char*)realloc(str, ++n);
		str[n - 1] = ch;
	}
	str = (char*)realloc(str, ++n);
	str[n - 1] = 0;
}
void writef(coop *tmp, int n, char *path)
{
	FILE *from = fopen(path, "wb");
	if (from)
	{
		fwrite(&n, sizeof(n), 1, from);
		fwrite(tmp, sizeof(tmp[0]), n, from);
		fclose(from);
	}
	else cout << "Ошибка открытия " << path << endl;
}
void readf(coop *&tmp, int &n, char *path)
{
	FILE *from = fopen(path, "rb");
	if (from)
	{
		fread(&n, sizeof(n), 1, from);
		tmp = (coop*)malloc(n * sizeof(coop));
		fread(tmp, sizeof(tmp[0]), n, from);
		fclose(from);
	}
	else cout << "Ошибка открытия " << path << endl;
}
coop insert()
{
	coop tmp;
	cout << "Введите фамилию: ";
	cin >> tmp.sname;
	cout << "Введите возраст: ";
	cin >> tmp.age;
	cin.ignore();
	return tmp;
}
void addbase(coop *&tmp, int &n)
{
	tmp = (coop*)realloc(tmp, (n + 1) * sizeof(coop));
	tmp[n++] = insert();
}
void edit(coop *&tmp, int n, char *sname)
{
	int f = 0;
	for (int i = 0; i < n; i++)
	{
		if (stricmp(tmp[i].sname, sname) == 0)
		{
			f = 1;
			tmp[i] = insert();
			cout << "Операция успешно выполнена\n";
		}
	}
	if (f == 0) cout << "Не найдено\n";
}
void show(coop tmp)
{
	cout << setw(15) << tmp.sname
		<< setw(5) << tmp.age << "\n";
}
void showbase(coop *tmp, int n)
{
	for (int i = 0; i < n; i++) show(tmp[i]);
}
void findage(coop *tmp, int n, int age)
{
	int f = 0;
	for (int i = 0; i < n; i++)
	{
		if (tmp[i].age == age)
		{
			f = 1;
			show(tmp[i]);
		}
	}
	if (f == 0) cout << "Не найдено\n";
}
void wfindage(coop *tmp, int n, int age, FILE *to)
{
	fprintf(to, "%s", "Фамилия:\t\tВозраст:\n");
	for (int i = 0; i < n; i++)
	{
		if (tmp[i].age == age) fprintf(to, "%s\t\t%i\n", tmp[i].sname, tmp[i].age);
	}
}
void findch(coop *tmp, int n, char ch)
{
	int f = 0;
	for (int i = 0; i < n; i++)
	{
		if (tmp[i].sname[0] == ch)
		{
			f = 1;
			show(tmp[i]);
		}
	}
	if (f == 0) cout << "Не найдено\n";
}
void wfindch(coop *tmp, int n, char ch, FILE *to)
{
	fprintf(to, "%s", "Фамилия:\t\tВозраст:\n");
	for (int i = 0; i < n; i++)
	{
		if (tmp[i].sname[0] == ch) fprintf(to, "%s\t\t%i\n", tmp[i].sname, tmp[i].age);
	}
}
void findsname(coop *tmp, int n, char *sname)
{
	int f = 0;
	for (int i = 0; i < n; i++)
	{
		if (stricmp(tmp[i].sname, sname) == 0)
		{
			f = 1;
			show(tmp[i]);
		}
	}
	if (f == 0) cout << "Не найдено\n";
}
coop *remove(coop *&tmp, int &n, char *sname)
{
	int f = 0;
	for (int i = 0; i < n; i++)
	{
		while (i < n&&strstr(tmp[i].sname, sname) != 0)
		{
			f = 1;
			for (int j = i; j < n - 1; j++) tmp[j] = tmp[j + 1];
			tmp = (coop*)realloc(tmp, (n - 1) * sizeof(coop));
			n--;
		}
	}
	cout << ((f == 1) ? "Операция успешно выполнена\n" : "Не найдено\n");
	return tmp;
}
void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char ch;
	int n = 0;
	coop *base = NULL;
	readf(base, n, "data.txt");
	do
	{
		system("cls");
		cout << "Меню:\n";
		cout << "1 - Добавить сотрудника\n";
		cout << "2 - Редактировать данные сотрудника\n";
		cout << "3 - Вывод списка сотрудников\n";
		cout << "4 - Вывод сотрудников указанного возраста\n";
		cout << "5 - Вывод сотрудников, фамилия которых начинается на указанную букву\n";
		cout << "6 - Поиск сотрудника по фамилии\n";
		cout << "7 - Удалить сотрудника\n";
		cout << "8 - Сохранить изменения\n";
		cout << "esc Выход\n";
		ch = getch();
		switch (ch)
		{
		case '1': system("cls");
			addbase(base, n);
			cout << "Операция успешно выполнена\n";
			Sleep(1000);
			break;
		case '2': system("cls");
			if (n != 0)
			{
				cout << "Введите фамилию: ";
				char *sname;
				get(sname);
				edit(base, n, sname);
			}
			else cout << "Список сотрудников пуст\n";
			Sleep(1000);
			break;
		case '3': system("cls");
			if (n != 0)
			{
				showbase(base, n);
				system("pause");
			}
			else
			{
				cout << "Список сотрудников пуст\n";
				Sleep(1000);
			}
			break;
		case '4': system("cls");
			if (n != 0)
			{
				cout << "Введите возраст: ";
				int age;
				cin >> age;
				findage(base, n, age);
				cout << "Записать результат в файл? (0-нет, 1-да): ";
				bool write;
				cin >> write;
				cin.ignore();
				if (write == 1)
				{
					cout << "Введите имя файла: ";
					char *name;
					get(name);
					FILE *to = fopen(name, "w");
					if (to)
					{
						wfindage(base, n, age, to);
						fclose(to);
						cout << "Операция успешно выполнена\n";
						
					}
					else cout << "Ошибка в открытии " << name << endl;
					Sleep(1000);
				}
				else Sleep(1000);
			}
			else
			{
				cout << "Список сотрудников пуст\n";
				Sleep(1000);
			}
			break;
		case '5': system("cls");
			if (n != 0)
			{
				cout << "Введите букву: ";
				char ch;
				cin >> ch;
				findch(base, n, ch);
				cout << "Записать результат в файл? (0-нет, 1-да): ";
				bool write;
				cin >> write;
				cin.ignore();
				if (write == 1)
				{
					cout << "Введите имя файла: ";
					char *name;
					get(name);
					FILE *to = fopen(name, "w");
					if (to)
					{
						wfindch(base, n, ch, to);
						fclose(to);
						cout << "Операция успешно выполнена\n";

					}
					else cout << "Ошибка в открытии " << name << endl;
					Sleep(1000);
				}
				else Sleep(1000);
			}
			else
			{
				cout << "Список сотрудников пуст\n";
				Sleep(1000);
			}
			break;
		case '6': system("cls");
			if (n != 0)
			{
				cout << "Введите фамилию: ";
				char *sname;
				get(sname);
				findsname(base, n, sname);
				system("pause");
			}
			else
			{
				cout << "Список сотрудников пуст\n";
				Sleep(1000);
			}
			break;
		case '7': system("cls");
			if (n != 0)
			{
				cout << "Введите фамилию: ";
				char *sname;
				get(sname);
				remove(base, n, sname);
			}
			else cout << "Список сотрудников пуст\n";
			Sleep(1000);
			break;
		case '8': system("cls");
			writef(base, n, "data.txt");
			cout << "Операция успешно выполнена\n";
			Sleep(1000);
		}
	} while (ch != 27);
	writef(base, n, "data.txt");
	free(base);
}