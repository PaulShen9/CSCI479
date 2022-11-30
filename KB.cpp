#include <iostream>
#include "KB.h"
using namespace std;

EasyMap::EasyMap()
{
	//use a hash map to create build the whole system
	//the size is set to 200 according to the requirment 
	//the first element is the key of the hash table, the key is the conclution in this case
	//the second elment is the value itself, in this case, the second elment is the list of string which can get the conclution
	m_hashMap = new pair<string, list<string>>[200];
	m_hasOther = true;
	count = 0;
}


//called by the tell function
//put the input into the hash table
void EasyMap::insert(pair<string, string> input)
{
	//try to get the data from the input
	string neverOrAlways;
	string data = input.second;

	//if the frist element is equal to " ", which menas there is no data for the key
	//at this case, should just get out of the function
	if (input.first== "")
	{
		cout<<"You provide the wrong input, tell is going wrong"<<endl;
		return;
	}

	//test the first element contains ! or not , for example !A.
	//if thie contains !, than change all the rest part to the reverse type
	//for example, if first element is !A, and second element is !B^C
	//the final result will become the first element is A, the second element is B^!C
	if (isNegation(input.first))
	{
		//use a function called split to sperate the string since we need test each elemnt sperately
		for (string& str : split(data,"^"))
		{
			if (isNegation(str))
			{
				//use erase to erase the !
				//since the string will only have 2elment(!A), start from 0, erase one elment
				str = str.erase(0, 1);
			}
			else
			{
				//if there is no ! in the string, add ! to the string
				str = "!" + str;
			}
		}
		//cout<<"Negation test"<<endl;
	}
	
	//for the second element, if it is " ", which means it will be always true or always false
	//cout <<"data test"<<endl;
	//cout <<"data is "<<data<<endl;
	if(data == ""){
		//cout <<"data test"<<endl;
		if (isNegation(input.first))
		//if the key contains !,which means it will always be the false
		//set its value to never
		{
			data = "never";
		}
		else
		//if it do not contains !, they it will always be true, set the value to always
		{
			data = "always";
			//cout <<"The data is "<<data ;
		}
	}
	//cout << "the input is "<<input.first<<endl;
	//add the data into hash table
	m_hashMap[count].first = input.first;
	m_hashMap[count].second.push_back(data);
	//update the count
	count++;
	//cout <<"First elemtn : "  <<m_hashMap[count-1].first<<endl;

}

//return false if there is no ! in the string
bool isNegation(string str)
{
	//go through the whole string to find the !
	for (string::iterator it = str.begin() ; it != str.end() ; it++)
	{
		if (*it == '!')
		{
			return true;
		}
	}
	//at this point, the string should not sounld !, return false;
	return false;
}

list<string> EasyMap::split(const string& str, const string& delim) 
{
	list<string> res;	
	//if the string is empty, than nothing should be split
	if(str == ""){
		return res;
	}

	char * strs = new char[str.length() + 1]; //if do not +1, will get sege fault  
	strcpy(strs, str.c_str());

	char * d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());

	//use a build function called strtok from string library to split the string
	char *p = strtok(strs, d);
	while (p != NULL) 
	{
		//get the element one by one
		string s = p;   
		//push the element to the list
		res.push_back(s); 
		//git next element
		p = strtok(NULL, d);
	}

	return res;
}

//given the key, find the value for the given key
//return an empty list if not found
list<string> EasyMap::find(string key)
{
	int position =0;
	while(position < count){
		//if found, return the value
		if(m_hashMap[position].first == key){
			return m_hashMap[position].second;
		}
		position++;
	}	
	//means not found
	//return an empty list
	return list<string>();
}

//given the string, go through the hash table to find out the value can lead to the key
//add these value to a list and return the list
int EasyMap::query(string strQuery)
{
	int ret = 1;
	list<string> listValue= find(strQuery);
	//if not emepty, return 0;
	if (listValue.empty())
	{
		//cout <<"empty"<<endl;
		ret = 0;
	}
	//go thorough the list to find out how many elemnts are there
	for (string str: listValue)
	{
		//cout<<"not empty"<<endl;
		int value = RecursiveQuery(split(str , "^"));
		//the reason use * here is because we set the ret to 1, once RecursiveQuery return 0 for once, than the result automatically become 0
		ret  = ret * value;
	}
	//cout <<"The ret is " <<ret <<endl;
	return ret;
}


int  EasyMap::RecursiveQuery(list<string> strQuery)
{
	//set a return value to 1
	//each time the value will times the returnValue from the recurive call
	//if once time the result not found, then the final result will become 0
	
	int returnValue= 1;
	//if the query is empty, then simply return 0 
	if (strQuery.empty())
	{
		return 0;
	}

	for (string condition : strQuery)
	{
		bool bNegation = isNegation(condition);
		if (bNegation)
		{
			//remove the !
			condition = condition.erase(0, 1);
			//if the condition is always, since this is a negation of the case, we need to return a failure, which is 0
			if (condition == "always")
			{
				return 0;
			}
			else if (condition == "never")
			{
				return 1;
			}
			//use backward method, take the condition as key to find out the next condition
			int position = 0;
			while(position < count){
				if(m_hashMap[position].first == condition){
					//if the position is found, then get out of the loop
					break;
				}
				position++;
			}
			
			//for each value(second elment) in this position, use backword channing by recurr call to go through each of the elmeent splited by ^
			for (string str : m_hashMap[position].second)
			{
				//use the same logic before, since this is a negation
				returnValue = returnValue * RecursiveQuery(split(str, "^"));
				if (returnValue == 0)
				{
					returnValue= 1;
				}
				if (returnValue == 1)
				{
					returnValue = 0;
				}
			}
		}
		else
		{
			//not negation, so need to negate
			if (condition == "always")
			{
				return 1;
			}
			else if (condition == "never")
			{
				return 0;
			}
			//reset the position
			int position = 0;
			//use the same method as before
			while(position < count){
				if(m_hashMap[position].first == condition){
					//if the position is found, then get out of the loop
					break;
				}
				position++;
			}
			
			for (string str : m_hashMap[position].second)
			{
				returnValue = returnValue * RecursiveQuery(split(str, "^"));
			}
		}
	}
	return returnValue;
}





bool HF_KB::ASK(string str)
{
	//same idea as before, erase the ! before do the work
	bool negation = isNegation(str);
	if (negation == true)
	{
		str = str.erase(0, 1);
	}
	if (negation == true)
	{
		//if the negation is true, since we already erase the before the secarch
		//we need return the opposite result for the function
		return !m_map.query(str);
	}
	else
	{
		return m_map.query(str);
	}
}
void HF_KB::TELL(string value, string key) 
{
	//used a bulid in function called make_pair to pair the key and value
	m_map.insert(make_pair(key, value));
}