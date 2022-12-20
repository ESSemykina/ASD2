#include <iostream>
#include <fstream>

#define N 20
#define n 15

int Hashf(int a) //хеш функция для присваивания индекса 
{
	int b = a % N;
	return b;
}

void HashTable(int mas[N][N], int a) //проверяю,есть ли в таком то значения
{
	int b = Hashf(a); //присваиваем б индекс для элемента а
	if (mas[b][0] == 0) //если нет(то есть 0)
	{
		mas[b][0] = a;//то вписываю а
	}
	else
	{
		for (int i = 1; i < N; i++) //если уже есть элемент с таким индексом то выбираем другую строку но сохраняем индекс
		{
			if (mas[b][i] == 0)
			{
				mas[b][i] = a;
				break;
			}
		}
	}
}

void out(int mas[N][N]) //вывод таблицы
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (mas[i][j] != 0)
				std::cout << mas[i][j] << " ";
			else
				std::cout << "|"; //этот вывод добавлен для более наглядного вывода, элементы с одним ключом будут в одной строке 
		}
		std::cout << std::endl;
	}
}

void Write(int mas[N][N]) //записть таблицы в файл
{
	std::ofstream out("output.txt");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (mas[i][j] != 0)
				out << mas[i][j] << " ";
			else
				out << "|"; //этот вывод добавлен для более наглядного вывода, элементы с одним ключом будут в одной строке 
		}
		out << std::endl;
	}
}

int searchKey(int y) //ищем ключ элемента
{
	int a = Hashf(y);// в а засунули хэш функцию
	return a;
}

int main()
{
	std::ifstream in("input.txt");

	int hashtable[N][N];//задаем хэш таблицу
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			hashtable[i][j] = 0;
		}
	}
	int mas[n];//заполняем  массив 
	for (int i = 0; i < n; i++) {
		in >> mas[i];
	}
	for (int i = 0; i < n; i++) {   // и сверяем  
		HashTable(hashtable, mas[i]);
	}
	out(hashtable);
	Write(hashtable);

	return 0;
}

