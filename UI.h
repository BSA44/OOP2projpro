#pragma once

#include<iostream>
#include<vector>
#include<string>
#include "List.h"
#include "utils.h"
using namespace std;

string invalid = "Invalid choice, please try again";

class UIstate //stores data about menu
{
private:
	vector<string> data;
public:
	string getLoc() //name of the menu state belongs to
	{
		return data[0];
	}

	vector<string> getArgs() //details of state
	{
		return vector<string>(data.begin() + 1, data.end());
	}

	void setLoc(string loc) //set the state of menu state
	{
		data[0] = loc;
	}

	void setArgs(vector<string> args) //set details of state
	{
		data.resize(1);

		for (auto& i : args)
		{
			data.push_back(i);
		}
	}

	UIstate() {};
	UIstate(vector<string> data) : data(data) {};
};

class UIroute //stores info about previous states
{             // essential for navigation through UI ; gear box
private:
	vector<UIstate> route;
public:
	UIstate getPrev() //returns previous state
	{
		if (route.size() > 1)
		{
			return route[route.size() - 2];
		}
		else
		{
			return route[0];
		}
	}

	void setToPrev() //returns previous page
	{
		route.pop_back(); // last book-tuda yee
	}

	void addState(UIstate state)
	{
		route.push_back(state);
	}

	void home() //returns to home state
	{
		route.clear();
		route.push_back(UIstate( { "home" } ));
	}

	vector<UIstate>& getVector() //returns inner vector
	{
		return route;
	}
};

class UI
{
private:
	UIroute route; // was
	UIstate state; // is
	ContactsList List;
	string mode;
	string passwd;
public:

	UIroute& getRoute()
	{
		return route;
	}

	UIstate& getState()
	{
		return state;
	}

	UI* prev()
	{
		if (state.getLoc() != "home")
		{
			state = route.getPrev();
			route.setToPrev();
		}

		return this;
	}

	UI* goToHome()
	{
		route.home();
		state = route.getVector()[0];

		return this; // course coverage
	}

	void start()
	{
		List.init("");
		ReadStatus prstat;
		passwd = readFile("./data/.psw", prstat);

		this->state = UIstate({ "login" });

		while (state.getLoc() != "exit")
		{
			if (state.getLoc() == "home")
			{
				homeMenu();
			}

			if (state.getLoc() == "search")
			{
				if (state.getArgs().size() == 0)
				{
					searchMenu();
				}
				else
				{
					searchMenu(state.getArgs()[0]);
				}
			}

			if (state.getLoc() == "list")
			{
				listContacts();
			}

			if (state.getLoc() == "createContact")
			{
				if (mode == "readonly")
				{
					restrictionFallbackMenu();
					continue;
				}
				createContact();
			}

			if (state.getLoc() == "details")
			{
				details(state.getArgs()[0]);
			}

			if (state.getLoc() == "edit")
			{
				if (mode == "readonly")
				{
					restrictionFallbackMenu();
					continue;
				}
				editContact(state.getArgs()[0]);
			}

			if (state.getLoc() == "login")
			{
				loginMenu();
			}

			if (state.getLoc() == "editPassword")
			{
				if (mode == "readonly")
				{
					restrictionFallbackMenu();
					continue;
				}
				passwordEdit();
			}
		}
	}

	void homeMenu()
	{
		cout << "1. Create contact" << endl;
		cout << "2. Search contact" << endl;
		cout << "3. List of contacts" << endl;
		cout << "4. Change password" << endl;
		cout << "0. Exit" << endl;

		int selection;

		cin >> selection;

		while (!isBetween(0, selection, 4))
		{
			cout << invalid << endl;
			cin >> selection;
		}

		switch (selection)
		{
		case 0:
			this->route.getVector().clear();
			this->state = UIstate({ "login" });
			this->route.addState(this->state);
			break;
		case 1:
			this->state = UIstate({ "createContact" });
			route.addState(this->state);
			break;
		case 2:
			this->state = UIstate({ "search" });
			route.addState(this->state);
			break;
		case 3:
			this->state = UIstate({ "list" });
			route.addState(this->state);
			break;
		case 4:
			this->state = UIstate({ "editPassword" });
			this->route.addState(this->state);
			break;
		default:
			break;
		}

		system("cls");
	}

	void searchMenu(string query = "")
	{
		int pick;

		do {

			vector<string> searchResults;

			if (!query.empty())
			{
				this->state = UIstate({ "search", query });
				this->route.setToPrev();
				this->route.addState(this->state);

				searchResults = List.search(query);
				for (int i = 0; i < searchResults.size(); i++)
				{
					cout << i << ". " << List.getContactByID(searchResults[i]).getDisplayName() << endl;
				}
			}
			else
			{
				cout << "Search [0 to home]: ";
				cin.ignore();
				getline(cin, query);

				this->state = UIstate({ "search", query });
				this->route.setToPrev();
				this->route.addState(this->state);

				searchResults = List.search(query);
				for (int i = 0; i < searchResults.size(); i++)
				{
					cout << i + 1 << ". " << List.getContactByID(searchResults[i]).getDisplayName() << endl;
				}
			}

			cout << "Input 0 to continue search" << endl;
			cout << "Input number of result to get more info" << endl;
			cout << "Input -1 to go home" << endl;
			cin >> pick;
			while (!isBetween(-1, pick, searchResults.size()))
			{
				cout << "Invalid input, try again" << endl;
				cin >> pick;
			}

			switch (pick)
			{
			case -1:
				goToHome();
				break;
			case 0:
				query = "";
				break;
			default:
				this->state = UIstate({ "details", searchResults[pick - 1] });
				this->route.addState(this->state);
				system("cls");
				return;
			}

		} while (pick == 0);

		system("cls");
	}
	void details(string ID)
	{
		Contact target;
		target = List.getContactByID(ID);
		cout << target;
		cout << "1. Edit contact" << endl;
		cout << "2. Delete this contact" << endl;
		cout << "0. Back" << endl;
		cout << "-1. Home" << endl;
		int choice;
		cin >> choice;

		while (!isBetween(-1, choice, 2))
		{
			cout << invalid << endl;
			cin >> choice;
		}

		switch (choice)
		{
		case -1:
			goToHome();
			break;
		case 0:
			prev();
			break;
		case 1:
			this->state = UIstate({ "edit", ID });
			this->route.addState(this->state);
			break;
		case 2:
		{
			if (mode == "readonly")
			{
				cout << "Available only in administrator mode" << endl;
				system("pause");
				break;
			}
			cout << "Do you really wish to delete this contact?\n1 - yes, 0 - no" << endl;
			int choice;
			cin >> choice;

			while (!isBetween(0, choice, 1))
			{
				cout << invalid << endl;
				cin >> choice;
			}

			if (choice == 1)
			{
				List.deleteContact(ID);
				prev();
			}
		}
			break;
		}

		system("cls");
	}
	void listContacts()
	{
		for (int i = 0; i < List.length(); i++)
		{
			cout << i + 1 << ". " << List.getContactByIndex(i).getDisplayName() << endl;
		}

		cout << "Input number of contact to view details" << endl;
		cout << "0. Back" << endl;
		int choice;
		cin >> choice;
		while (!isBetween(0, choice, List.length()))
		{
			cout << invalid << endl;
			cin >> choice;
		}

		switch (choice)
		{
		case 0:
			prev();
			system("cls");
			return;
		default:
			this->state = UIstate({ "details", List.getContactByIndex(choice - 1).getID()});
			this->route.addState(this->state);
			break;
		}

		system("cls");
	}

	void createContact()
	{
		cout << "Input contact name: " << endl;
		string name;
		cin.ignore();
		getline(cin, name);

		bool nameExists = false;
		string existingID;

		for (int i = 0; i < List.length(); i++)
		{
			if (List.getContactByIndex(i).getDisplayName() == name)
			{
				nameExists = true;
				existingID = List.getContactByIndex(i).getID();
			}

			if (nameExists)
			{
				cout << "Contact with such name already exists, do you wish to edit this contact?\n(1 - yes, 0 - no)" << endl;
				int choice;
				cin >> choice;

				while (!isBetween(0, choice, 1))
				{
					cout << invalid << endl;
					cin >> choice;
				}

				switch (choice)
				{
				case 0:
					prev();
					break;
				case 1:
					goToHome();
					this->state = UIstate({ "edit", existingID });
					this->route.addState(this->state);
				default:
					break;
				}
				system("cls");
				return;
			}
		}

		
		string phoneNum;
		phoneNum = validNumber(true);
		// 12 character long phone number is not suitable for all countries

		Contact newContact = Contact();
		newContact.setDisplayName(name);
		newContact.addPhoneNum(PhoneNumber(phoneNum));
		newContact.setAddress("");
		newContact.setDateofBirth(DateOfBirth());
		newContact.addEmail(Email());

		List.createContact(newContact);
		cout << "Contact created successfully" << endl;
		system("pause");
		system("cls");
		goToHome();
	}

	void editContact(string ID)
	{
		int choice;

		do
		{
			system("cls");

			cout << "Select what to edit" << endl;
			cout << "1. Name" << endl;
			cout << "2. Phone number" << endl;
			cout << "3. Email address" << endl;
			cout << "4. Address" << endl;
			cout << "5. Date of Birth" << endl;
			cout << "0. Back" << endl;

			cin >> choice;

			while (!isBetween(0, choice, 5))
			{
				cout << invalid << endl;
				cin >> choice;
			}

			system("cls");

			switch (choice)
			{
			case 0:
				prev();
				break;
			case 1:
			{
				cout << "Enter new name:\n" << endl;
				cin.ignore();
				string newName;
				getline(cin, newName);
				Contact newData{ List.getContactByID(ID) };
				newData.setDisplayName(newName);
				List.updateContact(ID, newData);
				prev();
				break;
			}
			case 2:
			{
				Contact target{ List.getContactByID(ID) };
				for (int i = 0; i < target.phoneNumbersCount(); i++)
				{
					cout << target.getPhoneNumByID(i).getNumber() << " (" << i + 1 << " to edit)" << endl;
				}
				cout << target.phoneNumbersCount() + 1 << " to add new phone number" << endl;
				cout << "0. Back" << endl;

				int choice;
				cin >> choice;

				while (!isBetween(0, choice, target.phoneNumbersCount() + 1))
				{
					cout << invalid << endl;
					cin >> choice;
				}

				if (choice == 0)
				{

				}
				else if (choice == target.phoneNumbersCount() + 1)
				{
					string newNumber;
					do
					{
						newNumber = validNumber();
						if (List.numberExists(newNumber))
						{
							cout << "Such phone number already exists, input another number" << endl;
							continue;
						}

						break;
					} while (true);
					target.addPhoneNum(newNumber);
				}
				else
				{
					string newNumber;
					do
					{
						newNumber = validNumber();
						if (List.numberExists(newNumber)&&(newNumber != target.getPhoneNumByID(choice - 1).getNumber()))
						{
							cout << "Such phone number already exists, input another number" << endl;
							continue;
						}

						break;
					} while (true);
					target.setPhoneNumByID(choice - 1, newNumber);
				}

				List.updateContact(ID, target);
				prev();
			}
				break;
			case 3:
			{
				Contact target{ List.getContactByID(ID) };
				for (int i = 0; i < target.emailsCount(); i++)
				{
					cout << target.getEmailByID(i).getstr() << " (" << i + 1 << " to edit)" << endl;
				}
				cout << target.emailsCount() + 1 << " to add new email address" << endl;
				cout << "0. Back" << endl;

				int choice;
				cin >> choice;

				while (!isBetween(0, choice, target.emailsCount() + 1))
				{
					cout << invalid << endl;
					cin >> choice;
				}

				if (choice == 0)
				{

				}
				else if (choice == (target.emailsCount() + 1))
				{
					string newEmail;

					do
					{
						newEmail = validEmail();

						bool emailExists = false;
						for (int i = 0; i < target.emailsCount(); i++)
						{
							if (newEmail == target.getEmailByID(i).getstr()) emailExists = true;
						}

						if (emailExists)
						{
							cout << "Such email already exists for this contact, please try again" << endl;
							continue;
						}

						break;
					} while (true);

					target.addEmail(Email(newEmail));
				}
				else
				{
					string newEmail;

					do
					{
						newEmail = validEmail();

						bool emailExists = false;
						for (int i = 0; i < target.emailsCount(); i++)
						{
							if ((newEmail == target.getEmailByID(i).getstr()) && (i != choice - 1)) emailExists = true;
						}

						if (emailExists)
						{
							cout << "Such email already exists for this contact, please try again" << endl;
							continue;
						}

						break;
					} while (true);
				}

				List.updateContact(ID, target);
				prev();
			}
				break;
			case 4:
			{
				Contact target{ List.getContactByID(ID) };
				string address;
				cout << "Input address:" << endl;
				cin.ignore();
				getline(cin, address);
				target.setAddress(address);
				List.updateContact(ID, target);
			}
				break;
			case 5:
			{
				int d, m, y;
				Contact target{ List.getContactByID(ID) };
				cout << "Input year:" << endl;
				cin >> y;
				while (y < 0)
				{
					cout << "You must input non-negative value" << endl;
					cin >> y;
				}

				cout << "Input month: " << endl;
				cin >> m;
				while (!isBetween(1, m, 12))
				{
					cout << "Value must be between 1 and 12" << endl;
					cin >> m;
				}

				int dayLimit = 28; // every month is at least 28 days long, so let be this default

				switch (m)
				{
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:
					dayLimit = 31;
					break;
				case 2:
					if (!(y % 400)) dayLimit = 29;
					if (!(y % 4) || (y % 100)) dayLimit = 29;
					break;
				default:
					dayLimit = 30;
					break;
				}

				cout << "Input day:" << endl;
				cin >> d;
				while (!isBetween(1, d, dayLimit))
				{
					cout << "Value must be between 1 and " << dayLimit << endl;
					cin >> d;
				}

				target.setDateofBirth(DateOfBirth(d, m, y));
				List.updateContact(ID, target);
			}
				break;
			default:
				break;
			}
		} while (choice > 0);
	}

	void passwordEdit()
	{
		string old;
		cin.ignore();
		cout << "Input current password:" << endl;
		do
		{
			getline(cin, old);

			if (passwd != old)
			{
				cout << "Incorrect password" << endl;
			}
		} while (passwd != old);

		string newpassword, confirm;
		cout << "Input new password:" << endl;
		getline(cin, newpassword);

		cout << "Confirm new password" << endl;
		getline(cin, confirm);
		while (confirm != newpassword)
		{
			cout << "Passwords do not match, try again" << endl;
			getline(cin, confirm);
		}

		WriteStatus pwstat;
		writeFile("./data/.psw", newpassword, pwstat);

		if (pwstat == WriteStatus::SUCCESS)
		{
			passwd = newpassword;
			cout << "Password changed successfully!" << endl;
			system("pause");
			system("cls");
			goToHome();
			return;
		}

		cout << "Something went wrong, please try again" << endl;
		system("pause");
		system("cls");
		goToHome();
		
	}

	int PasswordSet()
	{
		ReadStatus rstat;
		string passwd = readFile("./shadow", rstat);
		//fstream shadowF("shadow", ios::in);
		//getline(shadowF, passwd);

		if (rstat == ReadStatus::ERROR)
		{
			return 1; //make ui read this. So if passwd (password) is empty - open sign in
		}
		return 0; //if not empty - open log in
	}

	void loginMenu()
	{
		cout << "1. Login as viewer" << endl;
		cout << "2. Login as administrator (requires password)" << endl;
		cout << "0. Exit program" << endl;

		int choice;
		cin >> choice;

		while (!isBetween(0, choice, 2))
		{
			cout << invalid << endl;
			cin >> choice;
		}

		switch (choice)
		{
		case 0:
			this->state = UIstate({ "exit" });
			return;
		case 1:
			this->mode = "readonly";
			goToHome();
			break;
		case 2:
		{
			string input;
			cin.ignore();
			cout << "Input password:" << endl;
			do
			{
				getline(cin, input);

				if (passwd != input)
				{
					cout << "Incorrect password" << endl;
				}
			} while (passwd != input);

			mode = "admin";
			goToHome();
		}
		}
		system("cls");
	}


	void restrictionFallbackMenu()
	{
		cout << "Available only in administrator mode" << endl;
		system("pause");
		system("cls");
		prev();
	}
};