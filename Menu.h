#pragma once
#ifndef SDDS_MENU_H
#define SDDS_MENU_H
#include <iostream>
#include <string>
#pragma warning(disable : 4996)
using namespace std;
const int MAX_NO_OF_ITEMS = 10;
#define _CRT_SECURE_NO_WARNINGS

namespace sdds
{
	class Menuitem
	{
		char* content = nullptr;
		Menuitem();
		Menuitem(const char* cont);
		ostream& display(ostream& out = cout) const;
		~Menuitem();
		Menuitem(const Menuitem& item) = delete;
		Menuitem& operator=(const Menuitem& item) = delete;
		friend class Menu;
	};


	class Menu
	{
		int count = 0;
		char* title = nullptr;
		Menuitem* menuit[MAX_NO_OF_ITEMS];
		int indentation = 0;
	public:
		Menu();
		Menu(const char* header, int indent = 0);
		Menu(const Menu& menu_obj);
		Menu& operator=(const Menu& menu_ob);
		bool isEmpty() const;
		operator bool() const;
		ostream& display(ostream& out = std::cout) const;
		void add(const char* menuitems);
		Menu& operator<<(const char* menuItem);
		operator int() const;
		int run(std::ostream& out = std::cout, istream& input = std::cin) const;
		void addtitle(const char* title);
		void set();;
		~Menu();
	};
}
#endif // !SDDS_MENU_H
