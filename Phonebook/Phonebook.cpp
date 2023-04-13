#include <iostream>
#include <fstream>
#include <string>
#include"Phonebook.h"
using namespace std;

int main() 
{
    setlocale(0, "");
    Phonebook phonebook;
    phonebook.addContact("Инокентий Кузнецов", "54-55-10", "55-89-47", "+79517778816", "Друг");
    phonebook.addContact("Яна Домикова", "51-88-98", "66-84-12", "+79825563075", "Колега");
    phonebook.addContact("Гоги Рабинович", "77-77-77", "15-14-13", "+77777777777", "Родня");
    phonebook.printAllContacts();

    phonebook.removeContact("Яна Домикова");
    cout << endl;
    phonebook.printAllContacts();
    cout << endl;
    Contact* contact = phonebook.findContact("Гоги Рабинович");
    if (contact != nullptr) 
    {
        cout << "Результат поиска: " << contact->getName() << "\n";
    }
    else
    {
        cout << "Контакт не неайден.\n";
    }

    phonebook.saveToFile("phonebook.txt");

    phonebook.loadFromFile("phonebook.txt");

    phonebook.printAllContacts();

    return 0;
}