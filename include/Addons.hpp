#pragma once
#include <string>
#include <iterator>

std::string compare_data(const std::string &str1,const std::string &str2) 
	{
	  if (stod(str1)>stod(str2))
		  return str1;
	  return str2;
	}

size_t get_brocker_account(const std::string &filename) // Íà âõîäå: balance_00001234_20181001.txt // Tested
	{
	   size_t begin = filename.find_first_of('_');
	   size_t end = filename.find_first_of('_',begin+1);
	   --end;
	   return size_t(std::stoll(filename.substr(begin+1,end-begin)));
	}

std::string get_brocker_date(const std::string &filename) // Íà âõîäå: balance_00001234_20181001.txt // Tested
	{
	   size_t begin = filename.find_last_of('_');
	   size_t end = filename.find_first_of('.');
	   ++begin;
	   return filename.substr(begin,end-begin);
	}