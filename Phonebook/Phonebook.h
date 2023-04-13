#pragma once

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Contact {
public:
    // ������������
    Contact() : m_name(nullptr) {}
    Contact(const string& name, const string& homePhone, const string& workPhone,
        const string& mobilePhone, const string& additionalInfo) :
        m_homePhone(homePhone), m_workPhone(workPhone), m_mobilePhone(mobilePhone),
        m_additionalInfo(additionalInfo) {
        m_name = new string(name);
    }

    // ����������
    ~Contact() { delete m_name; }

    // �������-�����
    string getName() const { return *m_name; }
    string getHomePhone() const { return m_homePhone; }
    string getWorkPhone() const { return m_workPhone; }
    string getMobilePhone() const { return m_mobilePhone; }
    string getAdditionalInfo() const { return m_additionalInfo; }

private:
    // ����������-�����
    string* m_name;
    string m_homePhone;
    string m_workPhone;
    string m_mobilePhone;
    string m_additionalInfo;
};

class Phonebook {
public:
    // �����������
    Phonebook() : m_contacts(nullptr), m_size(0), m_capacity(0) {}

    // ����������
    ~Phonebook()
    {
        for (int i = 0; i < m_size; i++)
        {
            delete m_contacts[i];
        }
        delete[] m_contacts;
    }

    // �������-�����
    void addContact(const string& name, const string& homePhone, const string& workPhone,
        const string& mobilePhone, const string& additionalInfo)
    {
        if (m_size == m_capacity)
        {
            expandCapacity();
        }
        m_contacts[m_size++] = new Contact(name, homePhone, workPhone, mobilePhone, additionalInfo);
    }

    void removeContact(const string& name)
    {
        for (int i = 0; i < m_size; i++)
        {
            if (m_contacts[i]->getName() == name)
            {
                delete m_contacts[i];
                for (int j = i; j < m_size - 1; j++)
                {
                    m_contacts[j] = m_contacts[j + 1];
                }
                m_size--;
                return;
            }
        }
    }

    Contact* findContact(const string& name) const
    {
        for (int i = 0; i < m_size; i++)
        {
            if (m_contacts[i]->getName() == name)
            {
                return m_contacts[i];
            }
        }
        return nullptr;
    }

    void printAllContacts() const
    {
        cout << "��������:\n";
        for (int i = 0; i < m_size; i++)
        {
            cout << "���: " << m_contacts[i]->getName() << "\n"
                << "�������� �������: " << m_contacts[i]->getHomePhone() << "\n"
                << "������� �������: " << m_contacts[i]->getWorkPhone() << "\n"
                << "��������� �������: " << m_contacts[i]->getMobilePhone() << "\n"
                << "�������������� ����������: " << m_contacts[i]->getAdditionalInfo() << "\n";
        }
    }

    void saveToFile(const string& filename) const
    {
        ofstream outfile(filename);
        if (outfile.is_open())
        {
            for (int i = 0; i < m_size; i++)
            {
                outfile << m_contacts[i]->getName() << "\n"
                    << m_contacts[i]->getHomePhone() << "\n"
                    << m_contacts[i]->getWorkPhone() << "\n"
                    << m_contacts[i]->getMobilePhone() << "\n"
                    << m_contacts[i]->getAdditionalInfo() << "\n";
            }
            outfile.close();
        }
        else
        {
            cout << "���� �� ��������!\n";
        }
    }

    void loadFromFile(const string& filename)
    {
        ifstream infile(filename);
        if (infile.is_open())
        {
            string name, homePhone, workPhone, mobilePhone, additionalInfo;
            while (getline(infile, name))
            {
                getline(infile, homePhone);
                getline(infile, workPhone);
                getline(infile, mobilePhone);
                getline(infile, additionalInfo);
                addContact(name, homePhone, workPhone, mobilePhone, additionalInfo);
            }
            infile.close();
        }
        else
        {
            cout << "���� �� ��������!\n";
        }
    }
private:
    // ����������-�����
    Contact** m_contacts;
    int m_size;
    int m_capacity;
    // �������-�����
    void expandCapacity()
    {
        int newCapacity = m_capacity + 10;
        Contact** newContacts = new Contact * [newCapacity];
        for (int i = 0; i < m_size; i++)
        {
            newContacts[i] = m_contacts[i];
        }
        delete[] m_contacts;
        m_contacts = newContacts;
        m_capacity = newCapacity;
    }
};
