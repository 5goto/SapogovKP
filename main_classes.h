#pragma once
#include <iostream>
#include <string>

using namespace std;


class Delivery
{
	string title;
	string provider_name; 
	int volume; 

public:
	// ������������
	Delivery(string title_, string provider_name_, int volume_) : // ����������������, ��� ������ �� �����
		title{ title_ }, provider_name{ provider_name_ }, volume{ volume_ } {}
	Delivery(int volume_) :
		title{  }, provider_name{ }, volume{ volume_ } {}
	Delivery() : // �� ���������
		title{ }, provider_name{ }, volume{ } {}


	// ���������� ���������� ��������� ��� ��������� ������
	bool operator ==(const Delivery& other)
	{
		return title == other.title && volume == other.volume && provider_name == other.provider_name;
	}
	bool operator !=(const Delivery& other)
	{
		return title != other.title || volume != other.volume || provider_name != other.provider_name;
	}
	bool operator >=(const Delivery& other)
	{
		return volume >= other.volume;
	}
	bool operator <=(const Delivery& other)
	{
		return volume <= other.volume;
	}
	bool operator >(const Delivery& other)
	{
		return volume > other.volume;
	}
	bool operator < (const Delivery& other)
	{
		return volume < other.volume;
	}
	friend ostream& operator << (ostream& out, Delivery& object) // ���������� ��������� ������, ��� �������
	{
		out << object.title << "|" << object.provider_name <<
			"|" << object.volume;
		return out;
	}

	operator int() const // ���������� � ������ ����� ��� ����� ��������� ������
	{
		return volume;
	}

	string get_provider_name() { return provider_name; }
	string get_title() { return title; }
	int get_volume() { return volume; }

	auto get_all_data_string() // ��� �������� � ��������� ������ � ����������� � ����� // � ���������� ���������� �� ������������
	{
		auto provider_str = gcnew System::String(provider_name.c_str());
		auto title_str = gcnew System::String(title.c_str());

		auto result = provider_str + "<|>" + title_str + "<|>"
			+ volume.ToString();

		return result;
	}

	/*System::String^ get_all_date()
	{
		auto str_e = gcnew System::String(employee.c_str());
		return (date.day + 30 * date.mounth + 365 * date.year).ToString() + "(" + str_e + ")";
	}*/
};



class Provider
{
	string provider_name;
	string phone; 
	string category; 

public:
	Provider(string provider_name_, string phone_, string category_) : // ���������������� ����������� ��� ����� �� �����
		provider_name{ provider_name_ }, phone{ phone_ }, category{ category_ } {}
	Provider() : // ����������� �� ���������, ����� ��� ��� �������
		provider_name{  }, phone{  }, category{  } {}

	operator int() const // ���������� ���������� � ������ �����, ���� ����������� - ����� ����� �������� �������� �����
	{
		int counter{ };
		for (auto i = 0; i < provider_name.length(); ++i)
			counter += (int)provider_name[i];
		return counter;
	}

	friend ostream& operator << (ostream& out, Provider& object) // ���������� ��������� ������. ��� ���������� �������
	{
		out << object.provider_name << "|" << object.phone << "|" << object.category;
		return out;
	}
	bool operator ==(const  Provider& other) // ���������� ���������� ���������
	{
		return provider_name == other.provider_name && phone == other.phone
			&& category == other.category;
	}
	bool operator !=(const  Provider& other)
	{
		return provider_name != other.provider_name || phone != other.phone
			|| category != other.category;
	}
	// ������� �������, ���������� �������� ���������� ����� ��� ��������� ������
	string get_provider_name()
	{
		return provider_name;
	}
	string get_phone()
	{
		return phone;
	}
	string get_category()
	{
		return category;
	}

	auto get_all_data_string() // ��� �������� � ��������� ������ � ����������� � ����� // � ���������� ���������� �� ������������
	{
		auto title_str = gcnew System::String(provider_name.c_str());
		auto phone_str = gcnew System::String(phone.c_str());
		auto category_str = gcnew System::String(category.c_str());


		auto result = title_str + "<|>" + phone_str + "<|>"
			+ category_str;

		return result;
	}
};


