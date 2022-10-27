#pragma once
#include <iostream>
#include <string>
#include <exception>
#include <type_traits>
#include <vector>
#include "main_classes.h"

using namespace std;


//  объекты с одинаковым статусом хранятся в одном узле
// каждый узел дерева как бы представляет собой голову односвзяного списка
template<typename T>
class BTree
{

public:struct node // узел дерева
{
    node* left; 
    node* right;
    node* parent;
    node* next; 
    T num; // поля с данными
    node(T n, node* l = 0, node* r = 0, node* p = 0, node* ne = 0) :num(n), left(l), right(r), parent(p), next(ne)
    {

    }
};
private: 

    node* root; // корень дерева


    void insert(node* z, vector<int>* path) 
    {                    
        node* y = NULL;
        node* x = root;
        while (x != NULL)
        {
            path->push_back((int)(*x->num));
            y = x;
            if ((int)(*z->num) < (int)(*x->num))
                x = x->left;
            else if ((int)(*z->num) > (int)(*x->num))
                x = x->right;
            else // если ключи нового объекта и текущего равны -  вставляем его в нашу цепочку этого узла
            {
                node* tmp = x;
                while (tmp->next != NULL)
                    tmp = tmp->next;
                tmp->next = z;
                return;
            }
        }
        z->parent = y;
        if (y == NULL)
            root = z;
        else if ((int)(*z->num) < (int)(*y->num))
            y->left = z;
        else if ((int)(*z->num) > (int)(*y->num))
            y->right = z;
        else //спустились вниз дерева и ключи совпали
        {
            node* tmp = y;
            while (tmp->next != NULL)
                tmp = tmp->next;
            tmp->next = z;
        }
    }

    //void draw(node* p, int level = 3) { //отрисовка дерева, опрокинутого на бок, объеты в одной цепочке выводятся друг за другом
    //    if (p != NULL) {
    //        draw(p->right, level + 3);
    //        for (int i = 0; i < level; i++) {
    //            cout << " ";
    //        }
    //        if (p != NULL)
    //        {
    //            node* tmp = p;
    //            while (tmp != NULL)
    //            {
    //                cout << *tmp->num << "<>";
    //                tmp = tmp->next;
    //            }
    //            cout << endl;
    //        }
    //        draw(p->left, level + 3);
    //    }
    //}

    void transplant(node* u, node* v) // вспомогательный метод для функции удаления 
    {
        if (u->parent == NULL)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else u->parent->right = v;
        if (v != NULL)
            v->parent = u->parent;
    }

    node* three_minimum(node* x) 
    {
        while (x->left != NULL)
            x = x->left;
        return x;
    }
public:
    BTree() {// конструктор
        root = NULL;
    }

    vector<int>* additem(T n) { // обертка для добавления элемента
        vector<int>* path{ new vector<int> };
        node* new_node = new node(n);
        insert(new_node, path);
        return path;
    }


    void draw_wrap() // обертка для отрисовки
    {
        node* head = root;
        draw(head);
    }


    private: void draw(node* p, System::Collections::Generic::LinkedList<System::String^>^ res, int level = 3) {
        if (p != NULL) {
            draw(p->right, res, level + 4);
            System::String^ space = "";
            for (int i = 0; i < level; i++) {
                space += " ";
            }
            if (p != NULL)
            {
               node* tmp = p;
               while (tmp != NULL)
               {
                   space += tmp->num->get_all_data_string() + " <-> ";
                   tmp = tmp->next;
               }
               cout << endl;
            }
            res->AddLast(space);
            draw(p->left, res, level + 4);
        }
    }

    public: auto draw_wrap_return()
    {
        node* head = root;
        auto items{ gcnew System::Collections::Generic::LinkedList<System::String^> };
        draw(head, items);
        return items;
    }

private: void delete_from_three(node* z)
{
    if (z->left == NULL)
        transplant(z, z->right);
    else if (z->right == NULL)
        transplant(z, z->left);
    else
    {
        node* y = three_minimum(z->right);
        if (y->parent != z)
        {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
    }
}

private: node* search(T data, node* x, int& comprassions) // поиск нужного узла в дереве
{
    while (x != NULL && ((int)(*data) != (int)(*x->num)))
    {
        comprassions++;
        if ((int)(*data) < (int)(*x->num))
            x = x->left;
        else x = x->right;
    }
    return x;
}

private: node* search(T data, node* x) // поиск нужного узла в дереве
{
    while (x != NULL && ((int)(*data) != (int)(*x->num)))
    {
        if ((int)(*data) < (int)(*x->num))
            x = x->left;
        else x = x->right;
    }
    return x;
}

public: node* search_wrap(T data, int& comprassions) // обертка для фыункции поиска
{
    node* x = root;
    return search(data, x, comprassions);
}

public: node* search_wrap(T data) // обертка для фыункции поиска
{
    node* x = root;
    return search(data, x);
}

public: bool delete_wrap(T data) //  оберка удаления
{
    // поиск удаляемого элемента в дереве - если его нет - то ничего не происходит
    // если элемент существует, то 
    node* to_delete = search_wrap(data); // ищем цепочку с таким же статусом как в data
    if (to_delete != NULL) // если цепочка существует
    {
        if (to_delete->next == NULL && *to_delete->num == *data) // если цепочка состоит из одного элемента и он совпадает с искомым для удаления
        {
            delete_from_three(to_delete);  // удаляем его
            return true;
        }
        else 
            if (to_delete->next != NULL) // если цепочка состоит из > 1 элементов
        {
            if (*to_delete->num == *data)  // если искомый элемент стоит первым в цепочке
            {
                node* tmp = to_delete;
                if (tmp->parent != NULL) // если у цепочки существует родитель (не является корнем)
                {
                    tmp->next->parent = tmp->parent; // перепривязываем узел
                    if (tmp->parent->right == tmp)
                        tmp->parent->right = tmp->next;
                    else
                        tmp->parent->left = tmp->next;
                }
                else
                    root = tmp->next;
                if (tmp->left != NULL) // если существует левый потомок
                {
                    tmp->next->left = tmp->left;  // перепривязываем узел на следующий
                    tmp->left->parent = tmp->next;
                }
                if (tmp->right != NULL) // если существует правый потомок
                {
                    tmp->next->right = tmp->right;  // перепривязываем узел на следующий
                    tmp->right->parent = tmp->next;
                }
                delete tmp; // наконец удаляем искомый узел
                return true;
            }
            else // если искомый узел не первый, но возможно он есть в цепочке узла
            {
                node* tmp = to_delete;
                while (tmp != NULL) // ищем элемент в цепочке простым перебором узлов
                {
                    if (*tmp->next->num == *data)
                        break;
                    else
                        tmp = tmp->next;
                }
                if (tmp != NULL) // если элемент не равен NULL -> удаляемый элемент найден и является следующим за tmp
                {
                    node* second_tmp = tmp->next; // удаляем этот элемент как из простого односвязного списка
                    tmp->next = second_tmp->next;
                    delete second_tmp;
                    return true;
                }
                else
                    return false;
            }
        }
        else
            return false;
    }
    else
        return false;
}

public:auto delete_all_same_objects_from_tree(T object) // удаление всех одинаковых объектов - понадобится позже
{
    int counter{};
    while (delete_wrap(object))
    {
        counter++;
    }
    return counter;
}


private: void searchOrderTravers(node* head, string name, vector<T>* res) // прямой обход (1)
{
    if (head != NULL)
    {
        node* tmp = head;
        while (tmp != NULL)
        {
            if (tmp->num->get_provider_name() == name)
                res->push_back(tmp->num);
            tmp = tmp->next;
        }
        searchOrderTravers(head->left, name, res);
        searchOrderTravers(head->right, name, res);
    }
}

public:  auto searchOrderTraversWrapper(string name)
{
    node* head = root;
    vector<T>* result{ new vector<T> };
    searchOrderTravers(head, name, result);
    return result;
}

      private:void sortOrderTravers(node* head, vector<T>* res) // обход с выводом в отсортированном порядке (Центрированный)
      {
          if (head != NULL)
          {
              sortOrderTravers(head->left, res);
              node* tmp = head;
              while (tmp != NULL)
              {
                  res->push_back(tmp->num);
                  tmp = tmp->next;
              }
              sortOrderTravers(head->right, res);
          }
      }

    public: auto tree_search(T object)
	{
		node* head = root;
		if (head != NULL)
		{
			while (head != nullptr)
			{
                if (head->num->get_volume() == object->get_volume())
                {
                    node* tmp = head;
                    while (tmp != nullptr)
                    {
                        if (*tmp->num == *object)
                            return true;
                        else
                            tmp = tmp->next;
                    }
                    return false;
                }
				else if (*head->num < *object)
					head = head->right;
				else
					head = head->left;
			}
		}
		else
			return false;
	}

     public: vector<T>*& get_all_items()
      {
          node* head = root;
          vector<T>* items{ new vector<T> };
          sortOrderTravers(head, items);
          return items;
      }
};