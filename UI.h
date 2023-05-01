#pragma once

#include<vector>
#include<string>

using namespace std;

class UIstate
{
private:
	vector<string> data;
public:
	string getLoc()
	{
		return data[0];
	}

	vector<string> getArgs()
	{
		return vector<string>(data.begin() + 1, data.end());
	}

	void setLoc(string loc)
	{
		data[0] = loc;
	}

	void setArgs(vector<string> args)
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

class UIroute
{
private:
	vector<UIstate> route;
public:
	UIstate getPrev()
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

	void setPrev()
	{
		route.pop_back();
	}

	void home()
	{
		route.clear();
		route.push_back(UIstate( { "home" } ));
	}

	vector<UIstate>& getVector()
	{
		return route;
	}
};

class UI
{
private:
	UIroute route;
	UIstate state;
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
			route.setPrev();
		}

		return this;
	}

	UI* home()
	{
		route.home();
		state = route.getVector()[0];

		return this;
	}

	void start()
	{
		home();

		while (state.getLoc() != "exit")
		{
			 // here actual UI logic goes
		}
	}
};