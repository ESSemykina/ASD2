#include <fstream>

int main()
{
	std::ifstream in, in1, in2;
	std::ofstream out, out1, out2;

	int a, b, size = 0, countA, countB, count;
	bool flag = true, Afull, Bfull;
	//открываем файлы
	in.open("input.txt");
	out.open("output.txt");
	//считаем кол-во чисел и добавляем их в файл output
	while (in >> a)
	{
		out << a << " ";
		size++;
	}
	in.close();
	out.close();
	//сортировка
	//partSize *= 2 тк мы будем разбивать последовательность на 2 файла
	for (int partSize = 1; partSize < size; partSize *= 2)
	{
		in.open("output.txt");
		out1.open("A.txt");
		out2.open("B.txt");
		count = 0;
		//добавляем по 1 числу сначала в A потом в В
		//потом  по 2 пары чисел потом по 4 пары
		while (in >> a)
		{

			count++;
			//добавляем число в А
			if (flag) out1 << a << " ";
			//добавляем число в В
			else out2 << a << " ";
			//когда распределили все числа по файлам А и В 
			if (count == partSize)
			{
				count = 0;
				flag = !flag;
			}
		}
		//закрываем файл
		in.close();
		out1.close();
		out2.close();
		//очищаем файл
		remove("output.txt");
		//открываем
		in1.open("A.txt");
		in2.open("B.txt");
		out.open("output.txt");
		//проверяем остались ли числа в том же файле ,в котором и были
		if (in1 >> a)
			Afull = true;
		else Afull = false;
		if (in2 >> b)
			Bfull = true;
		else Bfull = false;
		//основная сортировка
		for (int i = 0; i < size; i += 2 * partSize)
		{
			countA = 0; countB = 0;
			//сравниваем по 1 числу из файла А и В
			//потом  по 2 пары чисел потом по 4 пары (partSize *= 2)
			while (countA < partSize && Afull && countB < partSize && Bfull)
				//если а < b добавляем в А и  считаем сколько там чисел
				if (a < b)
				{
					out << a << " ";
					if (in1 >> a) Afull = true;
					else Afull = false;
					countA++;
				}
			//добавляем в В и считаем сколько там чисел 
				else
				{
					out << b << " ";
					if (in2 >> b) Bfull = true;
					else Bfull = false;
					countB++;
				}
			//если остались числа в А
			while (countA < partSize && Afull)
			{
				out << a << " ";
				if (in1 >> a) Afull = true;
				else Afull = false;
				countA++;
			}
			//если остались числа в В
			while (countB < partSize && Bfull)
			{
				out << b << " ";
				if (in2 >> b) Bfull = true;
				else Bfull = false;
				countB++;
			}

		}
		//закрываем файлы и очищаем их
		in1.close();
		in2.close();
		out.close();
		remove("A.txt");
		remove("B.txt");
	}
	return 0;
}