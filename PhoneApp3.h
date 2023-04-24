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
};

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
    //friend void operator <<(ostream& cout, PhoneNumber p);
    void* operator new(size_t size) {
        void* p = (void*)malloc(size);
        return p;
    }
};

//void operator <<(ostream& cout, PhoneNumber p) //for beautiful and formatted output
//{
//    int i = 0;
//    cout << "+(";
//    for (; i < 3; i++)
//    {
//        cout << p.number[i];
//    }
//    cout << ") ";
//    for (; i < 5; i++)
//    {
//        cout << p.number[i];
//    }
//    cout << "-";
//    for (; i < 8; i++)
//    {
//        cout << p.number[i];
//    }
//    cout << "-";
//    for (; i < 10; i++)
//    {
//        cout << p.number[i];
//    }
//    cout << "-";
//    for (; i < 12; i++)
//    {
//        cout << p.number[i];
//    }
//    cout << endl;
//}

class Email {
private:
    string email;
public:
    void set(string email) {
        
        // Correct way to validate email using regex

        regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

        if (regex_match(email, pattern)) {
            this->email=email;
        }

        // Fix: unwanted modification in case of invalid input
    }
    //string string() const
    //{
    //    return email;
    //}

    Email(string email)
    {
        this->set(email);
    }

    Email() : email("sample@example.com") {} // example.com is non-accessible domain. used for demonstration purposes

    void* operator new(size_t size) {
        void* p = (void*)malloc(size);
        return p;
    }
};

//class Contact {
//private:
//    string DisplayName;
//    static int count;
//    bool gender; // ???????????????
//    string address;
//    int ID;
//    DateOfBirth d_o_b;
//    PhoneNumber* phoneNums;
//    Email* emails;
//public:
//    Contact() {
//        DisplayName = "Jenna";
//        gender = false;
//        ID = count;
//        address = "CA";
//        phoneNums = new phoneNumber[3]; // Wanna more phone numbers?
//        emails = new Email[3];          // or emails? Go fuck yourself.
//        count++;                        // Every time we create just a new instance of the same contact it will continue increasing !!!
//    }
//  
//    void setDisplayName(string ContactName) {
//        DisplayName = ContactName;
//    }
//    string getDisplayName() {
//        return DisplayName;
//    }
//    void setGender(bool sex) { 
//        gender = sex;
//    }
//    bool getGender() {
//        return gender;
//    }
//    void setID(int id) {
//        ID = id;
//    }
//    int getID() {
//        return ID;
//    }
//    void setAddress(string living) {
//        address = living;
//    }
//    string getAddress() {
//        return address;
//    }
//    void setDateofBirth(DateOfBirth dob) {
//        d_o_b = dob;
//    }
//    void setPhoneNumByID(int i, string phon) {
//        phoneNums[i].setNumber(phon); // ...
//    }
//    phoneNumber getPhoneNumByID(int i) {
//        return phoneNums[i];
//    }
//    void setEmailByID(int i, string emm) {
//        emails[i].setEmail(emm); // ... ?
//    }
//    Email getEmailByID(int i) {
//        return emails[i];
//    }
//   // friend void operator << (ostream& out, Contact& contact);
//    void* operator new(size_t size) {
//        void* p = (void*)malloc(size);
//        return p;
//    }
//};

class Contact {
private:
    static int counter;
    string displayName;
    string address;
    string ID;
    DateOfBirth dateOfBirth;
    vector<PhoneNumber> phoneNums;
    vector<Email> emails;
public:
    
    Contact() {
        counter++;
        this->ID = to_string(counter);
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
    void setEmailByID(int i, string mail)
    {
        emails[i].set(mail);
    }
    Email getEmailByID(int i) {
        return emails[i];
    }
   // friend void operator << (ostream& out, Contact& contact);
    void* operator new(size_t size) {
        void* p = (void*)malloc(size);
        return p;
    }
};


//void operator <<(ostream& out, Contact& contact) {
//    out << "Name       -" << contact.getDisplayName() << endl;

//    out << "Number     -" << contact.getPhoneNumByID() << endl;
//    out << "Gender     -" << contact.getGender() << endl;
//    out << "Email      -" << contact.getEmailByID << endl;
//    out << "Address    -" << contact.getAddress() << endl;
//}