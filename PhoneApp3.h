#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <regex>
#include <vector>

using namespace std;

class DateOfBirth {
private:
    int day;
    int month;
    int year;
public:

    void setMonth(int m) {
        if (m > 0 && m <= 12) {
            month = m;
        }
    }
    void setDay(int d) {

        if (d >= 1 || d <= 28)
        {
            day = d;
        }

        if (d == 29) {
            if (month == 2)
            {
                if (!(year % 4) && (year % 100 || !(year % 400)))
                {
                    day = d;
                    return;
                }
            }
            else
            {
                day = d;
            }
        }

        if (d == 30)
        {
            if (month != 2) day = d;
        }

        if (d == 31)
        {
            switch (month)
            {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                day = d;
            default:
                break;
            }
        }

    }
    void setYear(int y) {
        year = abs(y);
    }
    int getDay() const {
        return day;
    }
    int getMonth() const {
        return month;
    }
    int getYear() const {
        return year;
    }

    DateOfBirth(int d, int m, int y)
    {
        day = 1;
        month = 1;
        year = 1970; // 1 Jan 1970 is a common starting time value

        setDay(d);
        setMonth(m);
        setYear(y);
        // in case of invalid value, default value will remain
    }

    DateOfBirth() : day(1), month(1), year(1970) {}
    //void* operator new(size_t size) {
    //    void* p = (void*)malloc(size);
    //    return p;
    //}
    friend void operator <<(ostream& out, DateOfBirth& dob);
};

void operator <<(ostream& out, DateOfBirth& dob) {
    out << dob.day << "." << dob.month << "." << dob.year << endl;
}
class PhoneNumber {
private:
    string number;
public:
    void setNumber(string number) {
        bool allNumber = true;
        for (int i = 0; i < number.length(); i++)
        {
            if (number[i] < 48 || number[i] > 57) // Fix 0 and 9 be out of range
            {
                allNumber = false;
                break;
            }

        }

        // 12 character long phone number is not suitable for all countries

        if (allNumber) this->number = number;
    }
    string getNumber() const {
        return this->number;
    }

    PhoneNumber(string n) : number(n) {};
    PhoneNumber() : number("") {};
    friend void operator <<(ostream& cout, PhoneNumber p);
    void* operator new(size_t size) {
        void* p = (void*)malloc(size);
        return p;
    }
};

void operator <<(ostream& cout, PhoneNumber p) //for beautiful and formatted output
{
    int i = 0;
    cout << "+(";
    for (; i < 3; i++)
    {
        cout << p.number[i];
    }
    cout << ") ";
    for (; i < 5; i++)
    {
        cout << p.number[i];
    }
    cout << "-";
    for (; i < 8; i++)
    {
        cout << p.number[i];
    }
    cout << "-";
    for (; i < 10; i++)
    {
        cout << p.number[i];
    }
    cout << "-";
    for (; i < 12; i++)
    {
        cout << p.number[i];
    }
    cout << endl;
}

class Email {
private:
    string email;
public:
    void set(string email) {

        // Correct way to validate email using regex

        regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

        if (regex_match(email, pattern)) {
            this->email = email;
        }

        // Fix: unwanted modification in case of invalid input
    }
    string getstr() const
    {
        return email;
    }

    Email(string email)
    {
        this->set(email);
    }

    Email() : email("sample@example.com") {} // example.com is non-accessible domain. used for demonstration purposes

    void* operator new(size_t size) {
        void* p = (void*)malloc(size);
        return p;
    }
    friend void operator <<(ostream& out, Email& em);
};


void operator <<(ostream& out, Email& em) {
    out << em.email << endl;
}

class Contact {
private:
    string displayName;
    string address;
    string ID;
    DateOfBirth dateOfBirth;
    vector<PhoneNumber> phoneNums;
    vector<Email> emails;
public:

    Contact() {
    }

    void setDisplayName(string text) {
        displayName = text;
    }
    string getDisplayName() {
        return displayName;
    }

    void setID(string id) {
        ID = id;
    }
    string getID() {
        return ID;
    }
    void setAddress(string living) {
        address = living;
    }
    string getAddress() {
        return address;
    }
    void setDateofBirth(DateOfBirth dob) {
        dateOfBirth = dob;
    }
    DateOfBirth getDateOfBirth()
    {
        return dateOfBirth;
    }
    void addPhoneNum(PhoneNumber phone)
    {
        phoneNums.push_back(phone);
    }
    void setPhoneNumByID(int i, string phon) {
        phoneNums[i].setNumber(phon);
    }
    PhoneNumber getPhoneNumByID(int i) {
        return phoneNums[i];
    }
    int phoneNumbersCount()
    {
        return phoneNums.size();
    }
    void setEmailByID(int i, string mail)
    {
        emails[i].set(mail);
    }
    Email getEmailByID(int i) {
        return emails[i];
    }

    void addEmail(Email em)
    {
        emails.push_back(em);
    }

    int emailsCount()
    {
        return emails.size();
    }

    friend csv::csv_t toCSV(Contact);
    friend Contact toContact(csv::csv_t);

 friend void operator << (ostream& out, Contact& contact);
    void* operator new(size_t size) {
        void* p = (void*)malloc(size);
        return p;
    }
};


void operator <<(ostream& out, Contact& contact) {
    cout << "Name:   " << contact.displayName << endl;

    for (int i = 0; i < contact.phoneNums.size(); i++)
    {
        cout << "Number " << i +1 << ":  " << contact.phoneNums[i];
    }
    for (int i = 0; i < contact.emails.size(); i++)
    {
        cout << "Email " << i +1 << ":  " << contact.emails[i];
    }
    out << "Address:  " << contact.address << endl;
    cout << "Date of birth : " << contact.dateOfBirth;
}