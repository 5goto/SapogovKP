#pragma once
#include "main_interface.h"
#include "hash_table_class.h"
#include "tree_class.h"
#include "init_mod.h"
#include "main_classes.h"

class Interface // Паттерн фасад для усправления основными сущностями
{
	BTree<Delivery*>* delivery_data_base; 
	SimpleHashTable<Provider*>* provider_data_base; 
	int hash_table_size; // хэш таблица статическая - поэтому указывается размер таблицы
	bool inited; // проверяет инициализированы ли базы данных, для графики

	bool is_it_prime(int n) {
		for (auto i = 2; i <= sqrt(n); i++) {
			if (n % i == 0)
				return false;
		}
		return true;
	}

public:
	Interface() : delivery_data_base{ nullptr }, provider_data_base{ nullptr }, inited{ false } {} 
	~Interface() 
	{
		delete delivery_data_base;
		delete provider_data_base;
	}

	void Init_Data_Bases(int size) // инициализация основных баз данных
	{
		Init_Delivery_Data_Base favorites_base; //  объекты из файла Init from file
		Init_Provider_Data_Base manga_base;   // они  вернут заполненные из файла базы данных
		hash_table_size = size;
		delivery_data_base = favorites_base.Init_Data_Base();  // здесь
		provider_data_base = manga_base.Init_Data_Base(hash_table_size); // и здесь
		inited = true;
	}

	bool is_bases_inited()
	{
		return inited;
	}


	auto find_object_in_tree(string title_, string provider_name_, int volume_)
	{
		Delivery* tmp_struct = new Delivery{ title_, provider_name_, volume_ };
		return delivery_data_base->tree_search(tmp_struct);
	}

	auto find_object_in_table(string provider_name_, string phone_, string category_)
	{
		Provider* tmp_struct = new Provider{ provider_name_, phone_, category_ };
		auto operation_result = provider_data_base->search_index(tmp_struct);
		if (operation_result != -1)
			return true;
		else
			return false;
	}

	int get_string_code(string object) // функция переводит Строку к числовому представлению - считает сумму кодов символов
	{
		int counter{ };
		for (auto i = 0; i < object.length(); ++i)
			counter += (int)object[i];
		return counter;
	}


	auto main_search_task(int volume, string category, int& comprassions) // решение осонвной поисковой задачи, принимает статус и ограничение по возрасту
	{ 
		// здесь мы получаем узел, содержащий все объекты с интересующим нас статусом 
		vector<Provider*> answer; // это вектор, в которыйь ответы
		BTree<Delivery*>::node* good_volume = delivery_data_base->search_wrap(new Delivery{ volume }, comprassions); // (*)
		
			while (good_volume != NULL) // просто последовательно идем по цепочке, как по односвязному списку
			{ 
				Provider* tmp = provider_data_base->search_index(get_string_code(good_volume->num->get_provider_name())); // хэшируем по этому названию, смотрим есть ли такой объект в таблице
				if (tmp != NULL)  // если объект есть т.е. хэширование успешно
				{
					if (tmp->get_category() == category)
						answer.push_back(tmp); 
				}
				good_volume = good_volume->next; // движемся дальше по цепочке пока не пройдем ее всю
				comprassions++;
			}
			return answer;
	}


	auto get_all_tree_for_debug()
	{
		return delivery_data_base;
	}

	auto get_all_tree_for_drawning()
	{
		return delivery_data_base->draw_wrap_return();
	}

	auto get_all_hash_table()
	{
		return provider_data_base;
	}

	auto get_hash_table_size()
	{
		return hash_table_size;
	}

	int insert_element_to_provider_data_base(string provider_name_, string phone_, string category_)
	{
		Provider* tmp_struct = new Provider{ provider_name_, phone_, category_ };
		int op_result = provider_data_base->add_element(tmp_struct);
		return op_result;
	}

	int delete_element_from_provider_data_base(string provider_name_, string phone_, string category_)
	{
		Provider* tmp_struct = new Provider{  provider_name_,  phone_, category_ };
		int op_result = provider_data_base->delete_element(tmp_struct);
		return op_result;
	}

	vector<int>* insert_element_to_Delivery_data_base(string title_, string provider_name_, int volume_)
	{
		Delivery* tmp_struct = new Delivery{ title_, provider_name_, volume_ };
		auto path = delivery_data_base->additem(tmp_struct);
		return path;
	}

	bool delete_element_to_Delivery_data_base(string title_, string provider_name_, int volume_)
	{
		Delivery* tmp_struct = new Delivery{ title_, provider_name_, volume_ };
		auto process_result = delivery_data_base->delete_wrap(tmp_struct);
		return process_result;
	}

	auto find_all_elements_by_num(string name)
	{
		auto elements_found = delivery_data_base->searchOrderTraversWrapper(name);
		return elements_found;
	}
};