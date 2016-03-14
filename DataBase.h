#pragma once


class DataBase
{
public:

	DataBase();
	void InitField();
	const int GetTarget();
	const int GetSpeed();
	const int GetTime();

private:

	std::vector<int> save;

	int SaveToGame(const std::string current_str);

};