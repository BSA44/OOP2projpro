#pragma once

#include"csv.h"
#include"PhoneApp3.h"
#include<string>

csv::csv_t toCSV(Contact contact)
{
	csv::csv_t result = { {} };
	result.resize(6);

	result[0].resize(1);
	result[0][0] = contact.getID();

	result[1].resize(1);
	result[1][0] = contact.getDisplayName();

	result[2].resize(1);
	result[2][0] = contact.getAddress();


	for (int i = 0; i < contact.phoneNumbersCount(); i++)
	{
		result[3].push_back(contact.getPhoneNumByID(i).getNumber());
	}


	for (int i = 0; i < contact.emailsCount(); i++)
	{
		result[4].push_back(contact.getEmailByID(i).getstr());
	}


	result[5].resize(3);
	result[5][0] = to_string(contact.getDateOfBirth().getDay());
	result[5][1] = to_string(contact.getDateOfBirth().getMonth());
	result[5][2] = to_string(contact.getDateOfBirth().getYear());

	return result;
}

Contact toContact(csv::csv_t csvdata)
{
	Contact result;
	result.setID(csvdata[0][0]);
	result.setDisplayName(csvdata[1][0]);
	result.setAddress(csvdata[2][0]);

	for (auto& i : csvdata[3])
	{
		result.phoneNums.push_back(PhoneNumber(i));
	}

	for (auto& i : csvdata[4])
	{
		result.emails.push_back(Email(i));
	}

	result.setDateofBirth(
		DateOfBirth(
			std::stoi(csvdata[5][0]),
			std::stoi(csvdata[5][1]),
			std::stoi(csvdata[5][2])
		)
	);

	return result;
}
