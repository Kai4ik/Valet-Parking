#include <iostream>
#include <cstring>
#include <iomanip>
#include "string.h"
#include "Menu.h"
using namespace std;

namespace sdds
{
    Menuitem::Menuitem()
    {
        content = nullptr;
    }
    Menuitem::Menuitem(const char* str)
    {
        if (str != nullptr)
        {
            content = new char[strlen(str) + 1];
            strcpy(content, str);
        }
        else
        {
            content = nullptr;
        }
    }
    ostream& Menuitem::display(ostream& os) const
    {
        if (content != nullptr)
        {
            os << content << std::endl;
        }
        return os;
    }
    Menuitem::~Menuitem()
    {
        delete[] content;
        content = nullptr;
    }






    Menu::Menu()
    {
        set();
    }
    Menu::Menu(const char* title, int indent)
    {
        if (title == nullptr)
        {
            set();
        }
        else
        {
            set();
            addtitle(title);
            indentation = indent;
        }
    }

    void Menu::set()
    {
        title = nullptr;
        count = 0;
        indentation = 0;
        for (int i = 0; i < MAX_NO_OF_ITEMS; i++)
        {
            menuit[i] = nullptr;
        }
    }
    Menu::Menu(const Menu& tmp)
    {
        set();
        *this = tmp;
    }
    Menu& Menu::operator=(const Menu& tmpr)
    {
        if (this != &tmpr)
        {
            indentation = tmpr.indentation;
            if (!tmpr.isEmpty())
            {
                addtitle(tmpr.title);
                if (tmpr.count != 0)
                {
                    for (int i = 0; i < count; i++)
                    {
                        delete menuit[i];
                        menuit[i] = nullptr;
                    }
                    for (int i = 0; i < tmpr.count; i++)
                    {
                        add(tmpr.menuit[i]->content);
                    }
                    count = tmpr.count;
                }
            }
            else
            {
                delete[] title;
                for (int i = 0; i < count; i++)
                {
                    delete menuit[i];
                    menuit[i] = nullptr;
                }
                set();
            }
        }
        return *this;
    }

    bool Menu::isEmpty() const
    {
        if (title == nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    Menu::operator bool() const
    {
        if (title != nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    ostream& Menu::display(ostream& os) const
    {
        if (isEmpty())
        {
            os << "Invalid Menu!" << endl;
        }
        else if (count == 0)
        {
            os << setw((4 * indentation) + strlen(title)) << fixed << right << title << endl;
            os << "No Items to display!" << endl;
        }
        else
        {
            os << setw((4 * indentation) + strlen(title)) << fixed << right << title << endl;
            for (int i = 0; i < count; i++)
            {
                os << setw((4 * indentation) + 1) << fixed << right << i + 1 << "- ";
                menuit[i]->display(os);
            }
            os << setw((4 * indentation) + 2) << "> ";
        }
        return os;
    }

    void Menu::addtitle(const char* title_ex)
    {
        if (!isEmpty())
        {
            delete[] title;
        }
        if (title_ex == nullptr)
        {
            title = nullptr;
        }
        else
        {
            title = new char[strlen(title_ex) + 1];
            strcpy(title, title_ex);
        }
    }


    void Menu::add(const char* item)
    {
        if (item != nullptr && count < MAX_NO_OF_ITEMS && title != nullptr)
        {
            menuit[count] = new Menuitem(item);
            count++;
        }
        else
        {
            delete[] title;
            for (int i = 0; i < count; i++)
            {
                delete menuit[i];
                menuit[i] = nullptr;
            }
            set();
        }
    }


    int Menu::run(ostream& os, istream& in) const
    {
        int option = 0;
        bool ch = true;
        this->display();
        if (this->count > 0)
        {
            do
            {
                cin >> option;
                if (cin.fail())
                {
                    cin.clear();
                    cout << "Invalid Integer, try again: ";
                }
                else if (option > count || option <= 0)
                {
                    cout << "Invalid selection, try again: ";
                }
                else
                {
                    ch = false;
                }
                cin.ignore(1000, '\n');
            } while (ch);
        }
        return option;
    }

    Menu::operator int() const
    {
        return run();
    }

    Menu& Menu::operator<<(const char* item)
    {
        add(item);
        return *this;
    }

    Menu::~Menu()
    {
        delete[] title;
        title = nullptr;
        for (int i = 0; i < count; i++)
        {
            delete menuit[i];
            menuit[i] = nullptr;
        }
    }
}