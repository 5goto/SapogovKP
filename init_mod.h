#pragma once
#include "main_classes.h"
#include "hash_table_class.h"
#include "tree_class.h"
#include <fstream>
#include <tuple>

using namespace std;

template<typename T>
class Init_From_File
{
protected:

    inline vector<string> str_split_by_one_space(string str)// Делит строку на посдстроки по пробелу
    {
        vector<string> result;
        while (str.find(" ") != -1)
        {
            result.push_back(str.substr(0, str.find(" ") + 1));
            str = str.erase(0, str.find(" ") + 1);
        }
        if (!str.empty())
        {
            result.push_back(str);
        }
        return result;
    }
};


class Init_Delivery_Data_Base : Init_From_File<Delivery*>
{
    string data_base_name;

public:
    Init_Delivery_Data_Base(string data_base_n = "delivery.txt") : data_base_name{ data_base_n } {}
    BTree<Delivery*>* Init_Data_Base()
    {
        string tmp; // для временного хранения строки
        vector<string> splitted_line; // вектор полей структуры
        BTree<Delivery*>* data_base = new BTree<Delivery*>;
        ifstream file_for_input(data_base_name);


        while (getline(file_for_input, tmp))
        {
            splitted_line = str_split_by_one_space(tmp);

            Delivery* tmp_struct = new Delivery{ splitted_line[0], splitted_line[1], stoi(splitted_line[2]) }; // инициализация полей структуры
            data_base->additem(tmp_struct);
        }
        file_for_input.close();
        return data_base;
    }
};

class Init_Provider_Data_Base : Init_From_File<Provider*>
{
    string data_base_name;
    int size_of_base;

    bool is_it_prime(int n) {
        for (auto i = 2; i <= sqrt(n); i++) {
            if (n % i == 0)
                return false;
        }
        return true;
    }
    int culculate_base_size(string data_base = "provider.txt")
    {
        ifstream file_for_input("provider.txt");
        string tmp;
        int counter{};
        while (getline(file_for_input, tmp))
            counter++;
        file_for_input.close();
        while (!is_it_prime(counter))
            counter++;
        return counter;
    }

    int culculate_base_size(int size)
    {
        while (!is_it_prime(size))
            size++;
        return size;
    }

public:

    Init_Provider_Data_Base(string data_base = "provider.txt") : data_base_name{ data_base }, size_of_base{} {}
    SimpleHashTable<Provider*>* Init_Data_Base(int& t_size)
    {

        //size_of_base = culculate_base_size();
        size_of_base = culculate_base_size(t_size);
        t_size = size_of_base;
        string tmp; // для временного хранения строки
        vector<string> splitted_line; // вектор полей структуры
        SimpleHashTable<Provider*>* data_base = new SimpleHashTable<Provider*>{ size_of_base };
        ifstream file_for_input("provider.txt");

        while (getline(file_for_input, tmp))
        {
            splitted_line = str_split_by_one_space(tmp);

            Provider* tmp_struct = new Provider{ splitted_line[0], splitted_line[1],
               splitted_line[2] }; // инициализация полей структуры
            data_base->add_element(tmp_struct);
        }
        file_for_input.close();
        return data_base;
    }
};