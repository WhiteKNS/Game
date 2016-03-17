
#include "stdafx.h"

#include "DataBase.h"

DataBase::DataBase()
{

}

const int DataBase::GetTarget()
{
	return save.at(0);
}


const int DataBase::GetSpeed()
{
	return save.at(1);
}


const int DataBase::GetTime()
{
	return save.at(2);
}

int DataBase::SaveToGame(const std::string current_str) 
{
	int start = 0;
	int number = 0;
	for (unsigned int i = 0; i < current_str.length(); ++i) 
	{
		if (current_str.at(i) == '=') 
		{
			std::string final_str = "";
			for (unsigned int j = i + 1; j < current_str.length(); j++) //parsing the string
			{
				final_str += current_str.at(j);
			}
			number = atoi(final_str.c_str()); //get number from the file and store it to the vector
			break;
		}
	}

	return number;
}

void DataBase::InitField()
{
	std::fstream fin;
	fin.open("input.txt");
	std::string current_str = "";
	if (!fin.is_open())
	{
		Render::PrintString(10, 100, std::string("can't open file: "), 1.0f, BottomAlign);
	}
	else
	{
		int i = 0;
		while (!fin.eof())
		{
			std::getline(fin, current_str, '\n');//get string from the file
			if (current_str.empty()) { break; }
			save.push_back(SaveToGame(current_str));
			i++;
		}
	}
	fin.close();
}
