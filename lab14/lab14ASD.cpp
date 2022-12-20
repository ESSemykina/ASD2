#include <iostream>
#include <fstream>

int i = 0;
#define N 40
#define n 15 

int Hashf(int a) //хэш функция,нужна для того,чтобы найти число  b,его id
{
	int b = a % N + i;
	return b;
}

void HashTable(int mas[N][N], int a) //функция,в которую задаю массив NxN и число
{


	while (1) //проверка
	{
		int b = Hashf(a);// в b засунули хэш функцию

		if (mas[b][0] == -1) //если в найденном id  ячейке 0 у нас находится -1
		{
			mas[b][0] = a;//то мы записываем туда наше число
			i = 0;//зануляем 
			break;//останавливаем 
		}
		else //если нет,то переходим на следующий id и осуществляем такую же проверку 
			i++;
	}
}



void out(int mas[N][N]) //вывод массива
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (mas[i][j] != -1)
				std::cout << mas[i][j] << " ";
			else
				std::cout << "-";
		}
		std::cout << std::endl;
	}


}



//по определенному id ищем, есть ли в этом id значение или нет
void searchNum(int mas[N][N], int k)//k - id 
{

	for (int i = 0; i < N; i++)
	{
		if (mas[k][i] != -1) //если есть,
			std::cout << mas[k][i] << " ";//то выводится 
		else //если значения нет
			break;//то функция просто останавливается 
	}

}


int main()
{
	std::ifstream in("input.txt");

	int hashtable[N][N];//задаем хэш таблицу
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			hashtable[i][j] = -1;
	}

	int mas[n];//вписываем туда значения 
	for (int i = 0; i < n; i++)
		mas[i] = rand() % 100;
	in >> mas[i];

for (int i = 0; i < n; i++) // и сверяем  
	HashTable(hashtable, mas[i]);


out(hashtable);

}
