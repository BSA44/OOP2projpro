#include <iostream>
#include <string>
#include <cstdlib>
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
        else {
            cout << "Invalid month" << endl;
            month = 1;
        }
    }
    void setDay(int d) {
        if (month == 2 && (d > 0 && d <= 29))
        {
            day = d;
        }
        else
        {
            cout << "Invalid day" << endl;
            day = 1;

        }
        if (d > 0 && d <= 31) {
            day = d;
        }
        else {
            cout << "Invalid day" << endl;
            day = 1;
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
    //void* operator new(size_t size) {
    //    void* p = (void*)malloc(size);
    //    return p;
    //}
};

class phoneNumber {
private:
    string number;
public:
    void setNumber(string number) {
        bool AllNumber = true;
        for (int i = 0; i < 12; i++)
        {
            if ((int)number[i] <= 48 || (int)number[i] >= 57)
            {
                AllNumber = false;
                break;
            }

        }

        if (number.length() == 12 && AllNumber) {
            this->number =number;
        }
        else {
            cout << "Invalid number" << endl;
            this->number = "998*********";
        }
    }
    string getNumber()  {
        return this->number;
    }
    void* operator new(size_t size) {
        void* p = (void*)malloc(size);
        return p;
    }
};

class Email {
private:
    string email;
public:
    void setEmail(string email) {
        if (email.find('@') != string::npos) {
            this->email=email;
        }
        else
        {
            cout << "Invalid email" << endl;
            this->email = "proverka@inha.uz";
        }
    }
    string getEmails()
    {
        return email;
    }
    void* operator new(size_t size) {
        void* p = (void*)malloc(size);
        return p;
    }
};

class Contact {
private:
    string DisplayName;
    static int count;
    bool gender;
    string address;
    int ID;
    DateOfBirth d_o_b;
    phoneNumber* phoneNums;
    Email* emails;
public:
    Contact() {
        DisplayName = "Jenna";
        gender = false;
        ID = count;
        address = "CA";
        phoneNums = new phoneNumber[3];
        emails = new Email[3];
        count++;
    }
  
    void setDisplayName(string ContactName) {
        DisplayName = ContactName;
    }
    string getDisplayName() {
        return DisplayName;
    }
    void setGender(bool sex) { 
        gender = sex;
    }
    bool getGender() {
        return gender;
    }
    void setID(int id) {
        ID = id;
    }
    int getID() {
        return ID;
    }
    void setAddress(string living) {
        address = living;
    }
    string getAddress() {
        return address;
    }
    void setDateofBirth(DateOfBirth dob) {
        d_o_b = dob;
    }
    void setPhoneNumByID(int i, string phon) {
        phoneNums[i].setNumber(phon);
    }
    phoneNumber getPhoneNumByID(int i) {
        return phoneNums[i];
    }
    void setEmailByID(int i, string emm) {
        emails[i].setEmail(emm);
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