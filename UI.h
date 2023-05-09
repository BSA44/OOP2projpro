#pragma once

#include<iostream>
#include<vector>
#include<string>
#include "List.h"
#include "utils.h"
using namespace std;

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
		goToHome();

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
				createContact();
			}

			if (state.getLoc() == "details")
			{
				details(state.getArgs()[0]);
			}

			if (state.getLoc() == "edit")
			{
				editContact(state.getArgs()[0]);
			}
		}
	}

	void homeMenu()
	{
		List.init("");

		cout << "1. Create contact" << endl;
		cout << "2. Search contact" << endl;
		cout << "3. List of contacts" << endl;
		cout << "0. Exit" << endl;

		int selection;

		cin >> selection;

		while (!isBetween(0, selection, 3))
		{
			cout << "Invalid choice, please try again" << endl;
			cin >> selection;
		}

		switch (selection)
		{
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
		case 0:
			this->state = UIstate({ "exit" }); break;
		default:
			break;
		}
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
				return;
			}

		} while (pick == 0);
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
			cout << "Invalid choice, please try again" << endl;
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
			cout << "Do you really wish to delete this contact?\n1 - yes, 0 - no" << endl;
			int choice;
			cin >> choice;

			while (!isBetween(0, choice, 1))
			{
				cout << "Invalid choice, please try again" << endl;
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
	}
	void listContacts()
	{
		for (int i = 0; i < List.getVector().size(); i++)
		{
			cout << i + 1 << ". " << List.getVector()[i].getDisplayName() << endl;
		}

		cout << "Input number of contact to view details" << endl;
		cout << "0. Back" << endl;
		int choice;
		cin >> choice;

		while (!isBetween(0, choice, List.getVector().size()))
		{
			cout << "Invalid choice, please try again" << endl;
			cin >> choice;
		}

		switch (choice)
		{
		case 0:
			prev();
			break;
		default:
			this->state = UIstate({ "details", List.getVector()[choice - 1].getID() });
			this->route.addState(this->state);
			break;
		}
	}

	void createContact()
	{
		cout << "Input contact name: " << endl;
		string name;
		cin.ignore();
		getline(cin, name);

		bool nameExists = false;
		string existingID;

		for (int i = 0; i < List.getVector().size(); i++)
		{
			if (List.getVector()[i].getDisplayName() == name)
			{
				nameExists = true;
				existingID = List.getVector()[i].getID();
			}

			if (nameExists)
			{
				cout << "Contact with such name already exists, do you wish to edit this contact?\n(1 - yes, 0 - no) " << endl;
				int choice;
				cin >> choice;

				while (!isBetween(0, choice, 1))
				{
					cout << "Invalid choice, please try again" << endl;
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

				return;
			}
		}

		cout << "Input phone number: " << endl;
		string phoneNum;
		cin.ignore();
		getline(cin, phoneNum);

		Contact newContact = Contact();
		newContact.setDisplayName(name);
		newContact.addPhoneNum(PhoneNumber(phoneNum));
		newContact.setAddress("");
		newContact.setDateofBirth(DateOfBirth());
		newContact.addEmail(Email());

		List.createContact(newContact);

		goToHome();
	}

	void editContact(string ID)
	{
	}
};