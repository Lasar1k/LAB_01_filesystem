#include "BrokerSearcher.hpp"
#include "Addons.hpp"
#include <iostream>
#include <iomanip>

void BrokerSearcher::print() 
	{
	     std::cout<<std::left<<std::setw(12)<<"____________"  <<"_"<<std::setw(11)<<"___________"<<"_"<<std::setw(9)<<"_________"<<"_"<<std::setw(12)<<"____________"<<"_\n"
			      <<std::setw(12)<<""             <<"|"<<std::setw(11)<<""         <<"|"<<std::setw(9)<<""       <<"|"<<std::setw(12)<<""          <<"|\n"
				  <<std::setw(12)<<"   broker"     <<"|"<<std::setw(11)<<"  account" <<"|"<<std::setw(9)<<"  files" <<"|"<<std::setw(12)<<"  lastdate" <<"|\n"
			      <<std::setw(12)<<"____________"  <<"|"<<std::setw(11)<<"___________"<<"|"<<std::setw(9)<<"_________"<<"|"<<std::setw(12)<<"____________"<<"|\n";
		for (auto index = database.begin();index!=database.end();++index) 
			{
				std::cout<<std::left<<std::setw(12)<<""                  <<"|"<<std::setw(11)<<""                   <<"|"<<std::setw(9)<<""                 <<"|"<<std::setw(12)<<""          <<"|\n"
					<<std::setw(12)<<index->second.broker<<"|"<<std::setw(11)<<index->second.account<<"|"<<std::setw(9)<<index->second.files<<"|"<<std::setw(12)<<index->second.lastdate<<"|\n";
			}
		 std::cout<<std::left<<std::setw(12)<<"____________"  <<"|"<<std::setw(10)<<"___________"<<"|"<<std::setw(8)<<"_________"<<"|"<<std::setw(12)<<"____________"<<"|\n";
	}

void BrokerSearcher::print_all_finance_files() 
	{
	    std::cout<<"All finance files:\n\n";
		for (auto index = NeededFiles.begin();index!=NeededFiles.end();++index) 
			{
				std::cout<<*index<<"\n";
			}
		std::cout<<"\n";
	}

void BrokerSearcher::search(const boost::filesystem::path &path) 
	{
          for (const boost::filesystem::directory_entry &EntryDir : boost::filesystem::directory_iterator{path}) 
			{
				 boost::filesystem::path canon_view = boost::filesystem::canonical(EntryDir);				

				if (boost::filesystem::is_directory(canon_view)) 
					{
						NestedDirs.push(canon_view.stem().string());

						search(canon_view);
					} 
				else if (boost::filesystem::is_regular_file(canon_view)) 
					{
					   found_regular_file(canon_view);
					}
			}

		if (!NestedDirs.empty()) 
			{
				NestedDirs.pop();
			}
	}

void BrokerSearcher::found_regular_file(const boost::filesystem::path &path) 
	{
	    BrokerData temp;
        std::string name_of_file = path.filename().string();
		boost::smatch result;
		/* Ìû äîëæíû èçáåãàòü ôàéëîâ, êîòîðûå íå ñîäåðæàò .old è èìÿ äðóãîãî ôîðìàòà*/
		if (name_of_file.find(".old") != std::string::npos || !boost::regex_match(name_of_file, result, ExampleOfBA)) 
			{
				return;
			}
		NeededFiles.push_back(NestedDirs.top() + " " + path.filename().string());
		
		// Çàíîñèì äàííûå â áóôôåðíóþ èíôîðìàöèþ î áðîêåðå
		temp.broker = NestedDirs.top();
		temp.account = get_brocker_account(path.filename().string());
		temp.lastdate = get_brocker_date(path.filename().string());
		temp.files = 0;

		// Åñëè â áàçå óæå ñóùåñòâóåò àêêàóíò ó òîãî æå áðîêåðà, òî
		auto account = database.find(temp.account);
		if ((account != database.end()) && (account->second.broker == temp.broker)) 
			{
			   if (std::stoll(account->second.lastdate)<std::stoll(temp.lastdate)) 
				   {
                      account->second.lastdate = temp.lastdate;
				   }
			   ++account->second.files;
			} 
	    else 
			{
                database.insert(std::make_pair(temp.account,temp));
			}
	}