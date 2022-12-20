
#include <iostream>
#include <vector>
#include <string>

struct BinaryNode
{
	//указатели на левый и правый узлы, пока что равны nullptr
	int value;
	BinaryNode* left = nullptr, * right = nullptr;

	//обработка исходной строки
	BinaryNode(std::string& s)   //обработка входящих данных
	{
		value = getValue(s);
		s.erase(0, digits(value));
		if (s[0] == '(') s = unbracket(s); else return;
		if (isDigit(s[0])) left = new BinaryNode(s);
		if (s[0] == ',' && isDigit(s[1])) right = new BinaryNode(s.erase(0, 1));
	}

	void add(int x)  // добавление
	{
		//приводим введенное значение к строке
		std::string s = std::to_string(x);
		//в зависимоти от того, больше ли введенное число или меньше относительно имеющегося узла, добавляем число в правую или левую ветвь
		if (x > value && right)
			right->add(x);
		//если узла не существует, мы его создаем и размещаем в него введеное число 
		if (x > value && !right)
			right = new BinaryNode(s);
		if (x < value && left)
			left->add(x);
		if (x < value && !left)
			left = new BinaryNode(s);
	}

	void remove(int x)   //удаление
	{
		//в зависимости от числа, которое мы хотим удалить, и его расположения в дереве, сначала делаем на его месте nullptr, затем удаляем узел 
		if (x > value && right && right->value == x)
			right = nullptr;
		if (x > value && right && right->value != x)
			right->remove(x);
		if (x < value && left && left->value == x)
			left = nullptr;
		if (x < value && left && left->value != x)
			left->remove(x);
	}

	bool contains(int x)  // поиск
	{
		// вызов функции find
		return find(x);
	}

	//находим элемент
	BinaryNode* find(int x)
	{
		//если введенное значение равно value, возвращаем указатель на текущий объект
		if (x == value)
			return this;
		//если x <> value, снова вызываем функцию
		if (x > value && right)
			return right->find(x);
		if (x < value && left)
			return left->find(x);
		return nullptr;
	}

	//функция возвращения элементов
	void getElements(std::vector<int>& v)
	{
		//добавляем элемент в конец
		v.push_back(value);
		//возвращаем элемент
		if (left)
			left->getElements(v);
		if (right)
			right->getElements(v);
	}

private:
	//проверка на то, если перед нами число или же это скобка
	bool isDigit(char c) { return c >= '0' && c <= '9'; }//возвращаем символ, если он находится в пределах от 0 до 9
	int digits(int n) // Если n = true, то функция выполняет округление значение и возвращает наибольшее целое значение,
		//которое не больше, чем изначальное.
		//иначе возвращается 1
	    //n - само число, которое мы считали, например, 0, 1 и тд
	{	//n - само число, которое мы считали, например, 0, 1 и тд
		if (n)
		{
			n = floor(log10(n) + 1);
			return n;
		}
		else
			return 1;
	}


	int getValue(std::string& s)
	{
		//получаем размерность строки (в нашем случае она равна 16)
		int n = s.size();
		int i = 1;
		while (i < n)
			//если за цифрой не следует другая цифра, выходим из цикла
			if (!isDigit(s[i++]))
				break;

		//возвращаем подстроку, начиная с символа с индексом 0 по i индекс символа строки, переводя числовую строку в целое число
		return std::stoi(s.substr(0, i));
	}

	//функция удаления скобки 
	std::string unbracket(std::string s)
	{
		for (int i = 1, d = 1; i < s.size(); i++, d += (s[i] == '(') - (s[i] == ')'))
			if (!d)
				return s.erase(0, 1).erase(i - 1, 1);
		return s;
	}

};


//реализация бинарного дерева
class BinaryTree
{
	//объявляем корень бинарного дерева
	BinaryNode* root = nullptr;

	//функция заполнения дерева
	void print(const std::string& p, const BinaryNode* n, bool l)
	{
		if (!n) return;
		std::cout << p << (l ? "|--" : "|--") << n->value << "\n";
		print(p + (l ? "|   " : "    "), n->left, true);
		print(p + (l ? "|   " : "    "), n->right, false);
	}
	
public:

	BinaryTree(std::string s = "")
	{
		if (!s.empty()) root = new BinaryNode(s);
	}

	void print() { if (root) print("", root, 0); else std::cout << "|--\n"; };

	void add(int x)
	{
		std::string s = std::to_string(x);
		if (root) root->add(x);
		else root = new BinaryNode(s);
	}

	void remove(int x)
	{
		if (!root) return;

		BinaryNode* n;
		if (root->value == x) n = root;
		else n = root->find(x);

		std::vector<int> branch;
		if (n->left) n->left->getElements(branch);
		if (n->right) n->right->getElements(branch);

		if (root->value == x) root = nullptr;
		else root->remove(x);
		for (int e : branch) add(e);
	}

	bool contains(int x) { return root ? root->contains(x) : false; }
};

int main()
{
	BinaryTree tree;
	//объявляем строку-команду
	std::string command;
	//число х, которое будем вводить в дерево
	int x;
	tree.print();
	//бесконечный цикл
	while (1)
	{
		//вводим команду и число
		std::cin >> command >> x;
		//случай добавления х
		if (command == "a") tree.add(x), tree.print();
		//случай удаления х
		if (command == "r") tree.remove(x), tree.print();
		//случай нахождения х в дереве
		if (command == "c")
			std::cout << x << (tree.contains(x) ? " exists\n" : " not exists\n");
	}
}
