#include "ini_parser.h"

#include <vector>
#include <string>
#include <string.h>
#include <fstream>
#include <map>
#include <iostream>
#include <algorithm>

namespace qh
{
	typedef std::vector<std::string> stringvector;
	std::string default_sectionName="default";
	
	//delete the space in string head and tail
	std::string restrip(std::string s){
		const std::string space = " ";
		s.erase(s.find_last_not_of(space)+1);
		return s.erase(0,s.find_first_not_of(space));
	}

        //read the file as data block that use to parse
	bool INIParser::Parse(const std::string& ini_file_path){
		std::ifstream infile(ini_file_path.c_str());
		if(!infile) return false;
		std::string data_block = "";
		std::string line;
		while(getline(infile, line)){
			if(line.size()==0) continue;
			else if(line[0] == '[' && data_block.size() == 0){
				data_block += line;
			}else if(line[0] == '[' && data_block.size() != 0){
				//std::cout<<data_block<<std::endl;
				if(!Parse(data_block.c_str(), data_block.size(), "\n", "=")) return false;
				data_block.clear();
				data_block+=line;
			}else if(line[0] != '['){
				data_block += "\n"; 
				data_block += line;
			}
		}//endwhile
		//std::cout<<data_block<<std::endl;
		if(!Parse(data_block.c_str(), data_block.size(), "\n", "=")) return false;
		infile.close();
		return true;
	}

	
	//slice the data block to (key=value),put they into vector
	stringvector Slice(const char* ini_data, size_t ini_data_len, const std::string& line_seperator){
		stringvector slice_data;
		std::string ini_str(ini_data, ini_data_len);
		size_t start_pos = 0;
		size_t index = ini_str.find_first_of(line_seperator, start_pos);
		while(index != std::string::npos && start_pos <= ini_data_len){
			slice_data.push_back(ini_str.substr(start_pos, index-start_pos));
			start_pos = index+1;
			index = ini_str.find_first_of(line_seperator, start_pos);
		}//while
		if(start_pos < ini_data_len) slice_data.push_back(ini_str.substr(start_pos, ini_data_len-start_pos));
		return slice_data;
	}

	//parse the data block
        bool INIParser::Parse(const char* ini_data, size_t ini_data_len, const std::string& line_seperator, const std::string& key_value_seperator){
		std::string key,value,sectionName = default_sectionName;
		std::string ini_str(ini_data, ini_data_len);
		if(ini_str[0] == '['){
			size_t pos=1;
			while(ini_str[pos] != ']'){
				pos++;
			}
			sectionName = ini_str.substr(1, pos-1);
			sectionName = restrip(sectionName);
			ini_str = ini_str.substr(pos+1, ini_data_len-pos-1);
			ini_data_len = ini_data_len-pos-1;
			//sliced_data = Slice(ini_str,ini_data_len-pos-1,line_seperator);
		}
	 	stringvector sliced_data = Slice(ini_str.c_str(), ini_data_len,line_seperator);
		for(size_t i = 0;i != sliced_data.size();++i){
			std::string ini_sub = sliced_data[i];
			size_t sub_len = ini_sub.size();
			size_t index = ini_sub.find_first_of(key_value_seperator);
			if(index != std::string::npos){
				key = ini_sub.substr(0,index);
				key = restrip(key);
				value = ini_sub.substr(index+1, sub_len-index-1);
				value = restrip(value);
			}else{
				key = ini_sub;
				key = restrip(key);
				value = "";
				value = restrip(value);
			}
				result_mp[sectionName][key] = value;
		}//for
		return true;
	}
	
	//get the key's value from the map,with section	
        const std::string& INIParser::Get(const std::string& section, const std::string& key, bool* found){
		std::string sectionName;
		sectionName = restrip(section);
		std::map<std::string, std::string>::iterator beg = result_mp[sectionName].begin();
		for(;beg != result_mp[sectionName].end();++beg){
			if(beg->first == key) return beg->second;
		}
		static std::string emp = "";
		return emp;
	}
	
	//get the key's value from the map
        const std::string& INIParser::Get(const std::string& key, bool* found){
		std::string section = default_sectionName;
		std::map<std::string, std::string>::iterator beg = result_mp[section].begin();
		for(;beg != result_mp[section].end();++beg){
			if(beg->first == key) return beg->second;
		}
		static std::string emp = "";
		return emp; 
	}
}
