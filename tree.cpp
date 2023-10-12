#include<iostream> 
#include<fstream> 
#include <iomanip> 
using namespace std;
int c = 0, z = 1; //нужно для счётчика сложения и умножения 
const int row = 8; typedef struct Node //структура дерева 
{
	int data;
	Node* left, * right;
}tree;
//КОРЕНЬ БИНАРНОГО ДЕРЕВА (ВЕРХУШКА) 
tree* first(int x, tree* p)
{
	p = new tree;
	p->data = x;
	p->left = p->right = NULL;
	return p;
}
//ДОБАВИТЬ ЭЛЕМЕНТ 
tree* add(int x)
{
	tree* p;
	p = new tree;
	p->data = x;
	p->left = p->right = NULL;
	return p;
}
//УДАЛИТЬ ЭЛЕМЕНТ 
tree* Delete(tree* r, int data)
{
	if (r == NULL)
		return r;
	if (data == r->data)
	{
		tree* tmp;
		if (r->right == NULL)
			tmp = r->left;
		else {
			tree* ptr = r->right;
			if (ptr->left == NULL) {
				ptr->left = r->left;
				tmp = ptr;
			}
			else {
				tree* pmin = ptr->left;
				while (pmin->left != NULL) {
					ptr = pmin;
					pmin = ptr->left;
				}
				ptr->left = pmin->right;
				pmin->left = r->left;
				pmin->right = r->right;
				tmp = pmin;
			}
		}
		delete r; return tmp;
	}
	else if (data < r->data)
		r->left = Delete(r->left, data);
	else
		r->right = Delete(r->right, data);
	return r;
}
//РАСПРЕДЕЛЕНИЕ ЭЛЕМЕНТОВ БИНАРНОГО ДЕРЕВА 
void search(int x, tree* p)
{
	if (x < p->data)
	{
		if (p->left != NULL) //пока не встречен NULL вызываем search 
		{
			search(x, p->left);
		}
		else
		{
			p->left = add(x); //в левую ветку добавляем x 
		}
	}
	else
	{
		if (x > p->data)
		{
			if (p->right != NULL) //пока не встречен NULL вызываем search 
			{
				search(x, p->right);
			}
			else
			{
				p->right = add(x); //в правую ветку добавляем x 
			}
		}
	}
}
//ВЫВЕСТИ ЭЛЕМЕНТЫ БИНАРНОГО ДЕРЕВА ИНФИКСНЫМ СПОСОБОМ 
void infix(tree* p)
{
	if (p->left != NULL)
	{
		infix(p->left);
	}
	cout << p->data << " " << endl;
	if (p->right != NULL)
	{
		infix(p->right);
	}
}
void prefix(tree* p) //префиксный способ 
{
	cout << p->data << " " << endl;
	if (p->left != NULL) {
		infix(p->left);
	}
	if (p->right != NULL)
	{
		infix(p->right);
	}
}
void postfix(tree* p) //постфиксный способ 
{
	if (p->left != NULL)
	{
		infix(p->left);
	}
	if (p->right != NULL)
	{
		infix(p->right);
	}
	cout << p->data << " " << endl;
}
//ПОИСК ЭЛЕМЕНТА 
tree* find(tree* r, float d)
{
	if (r == NULL)
	{
		return NULL; // не найден 
	}
	if (r->data == d)
	{
		cout << "Элемент в бинарном дереве найден!" << endl;
		return r; // нашли!!! 
	}
	if (d <= r->data)
	{
		// left 
		if (r->left != NULL)
			return find(r->left, d); // рекурсивный поиск влево 
		else
		{
			cout << "Элемент в бинарном дереве не найден!" << endl;
			return NULL; // не найден 
		}
	}
	else
	{
		//right 
		if (r->right)
			return find(r->right, d);// рекурсивный поиск вправо 
		else
		{
			cout << "Элемент в бинарном дереве не найден!" << endl;
			return NULL; // не найден 
		}
	}
}
//ГРАФИЧЕСКОЕ ПРЕДСТАВЛЕНИЕ ЭЛЕМЕНТОВ БИНАРНОГО ДЕРЕВА 
void postorder(tree* p, int indent)
{
	int count = 0, cop = 0;
	if (p != NULL)
	{
		if (p->right)
		{
			count = count + 1;
			postorder(p->right, indent + 2);
		}
		if (indent)
		{
			cout << setw(indent) << ' ';
		}
		if (p->right)
			cout << ' ' << "/\n" << setw(indent);
		for (int i = 0; i < count; i++)
			cout << ' ';
		cout << p->data << "\n ";
		if (p->left)
		{
			cop = cop + 1;
			cout << setw(indent) << ' ' << "\\\n";
			for (int i = 0; i < count; i++)
				cout << ' ';
			postorder(p->left, indent + 2);
		}
	}
}
int main()
{
	setlocale(LC_ALL, "ru");
	string y, y1, y2, y3, y4, y5;
	int pol, now, del;
	int mas[row];
	for (int i = 0; i < row; i++)
	{
		cout << i + 1 << " элемент = ";
		cin >> mas[i];
	}
	tree* root = NULL;
	root = first(mas[0], root);
	for (int i = 1; i < row; i++)
	{
		search(mas[i], root);
	}
	try
	{
		cout << "Каким способом вы бы хотели представить бинарное дерево?(infix,prefix,postfix) "; cin >> y;
		if (y == "infix")//инфиксный 
		{
			infix(root);
		}if (y == "prefix")//префиксный 
		{
			prefix(root);
		}
		if (y == "postfix")//постфиксный 
		{
			postfix(root);
		}
		if ((y != "infix") && (y != "prefix") && (y != "postfix"))
		{
			throw "Неправильно набран способ представления бинарного дерева";
		}
		if (typeid(string) != typeid(y))
			throw "Ответ должен иметь строковый тип";
		//
		cout << "Хотите ли вы найти элемент бинарного дерева? "; cin >> y1;
		if (y1 == "yes")
		{
			cout << "Элемент, который нужно найти: "; cin >> pol;
			if (typeid(pol) != typeid(int))
				throw "Элемент должен иметь целочисленное значение";
			if (pol < 0)
				throw "Элемент не должен иметь отрицательное значение";
			find(root, pol);
		}
		else if (y1 == "no")
			cout << "Попробуйте другие функции" << endl;
		if (typeid(y1) != typeid(string))
			throw "Ответ должен иметь строковый тип";
		if ((y1 != "yes") && (y1 != "no"))
			throw "Ответ должен быть либо yes, либо no";
		//
		cout << "Хотите ли вы добавить новый элемент в бинарное дерево? "; cin >> y2;
		if (y2 == "yes")
		{
			cout << "Новый элемент, который нужно добавить в бинарное дерево: "; cin >> now;
			if (typeid(now) != typeid(int))
				throw "Элемент должен иметь целочисленное значение";
			if (now < 0)
				throw "Элемент не должен иметь отрицательное значение";
			search(now, root);
			cout << "Способ представления элементов бинарного дерева(infix,prefix,postfix) "; cin >> y3;
			if (y3 == "infix")//инфиксный 
			{
				cout << "Новая последовательность элементов бинарного дерева: " << endl;
				infix(root);
			}
			if (y3 == "prefix")//префиксный 
			{
				cout << "Новая последовательность элементов бинарного дерева: " << endl;
				prefix(root);
			}
			if (y3 == "postfix")//постфиксный 
			{
				cout << "Новая последовательность элементов бинарного дерева: " << endl; postfix(root);
			}
			if ((y3 != "infix") && (y3 != "prefix") && (y3 != "postfix"))
				cout << "Неправильно набран способ представления бинарного дерева" << endl;
			if (typeid(y3) != typeid(string))
				throw "Ответ должен иметь строковый тип";
		}
		else if (y2 == "no")
			cout << "Попробуйте другие функции" << endl;
		if (typeid(y2) != typeid(string))
			throw "Ответ должен иметь строковый тип";
		if ((y2 != "yes") && (y2 != "no"))
			throw "Ответ должен быть либо yes, либо no";
		//
		cout << "Хотите ли вы удалить элемент из бинарного дерева? "; cin >> y4;
		if (y4 == "yes")
		{
			cout << "Элемент, который нужно удалить: "; cin >> del;
			if (typeid(del) != typeid(int))
				throw "Элемент должен иметь целочисленное значение";
			if (del < 0)
				throw "Элемент не должен иметь отрицательное значение";
			Delete(root, del);
			cout << "Способ представления элементов бинарного дерева(infix,prefix,postfix) "; cin >> y5;
			if (y5 == "infix")//инфиксный 
			{
				cout << "Новая последовательность элементов бинарного дерева: " << endl;
				infix(root);
			}
			if (y5 == "prefix")//префиксный 
			{
				cout << "Новая последовательность элементов бинарного дерева: " << endl;
				prefix(root);
			}
			if (y5 == "postfix")//постфиксный 
			{
				cout << "Новая последовательность элементов бинарного дерева: " << endl;
				postfix(root);
			}
			if ((y5 != "infix") && (y5 != "prefix") && (y5 != "postfix"))
				cout << "Неправильно набран способ представления бинарного дерева" << endl;
			if (typeid(y5) != typeid(string))
				throw "Ответ должен иметь строковый тип";
		}
		else if (y4 == "no")
			cout << "Попробуйте другие функции" << endl;
		if (typeid(y4) != typeid(string))
			throw "Ответ должен иметь строковый тип";
		if ((y4 != "yes") && (y4 != "no"))
			throw "Ответ должен быть либо yes, либо no";
		//
		cout << "Графическое представление бинарного дерева " << endl;
		postorder(root, 0);
	}
	catch (...) {
		cout << "Выберите один из перечисленных способов представления бинарного дерева" << endl;
	}
	system("pause");
	return 0;
}
