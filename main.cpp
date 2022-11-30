#include <iostream>
#include "KB.h"

//this is the main program for the assignment4
//use the sama main program given in the course web page
//add user concept
int main()
{
	//conside these are the base as the KB, user do not need to add these by theirself
	HF_KB myKB;
	string myQuery = "!D";
	myKB.TELL("A^B^C", "D");
	myKB.TELL("AB^E", "F");
	myKB.TELL("", "A");
	myKB.TELL("", "B");
	myKB.TELL("", "C");
	myKB.TELL("", "E");
	myKB.TELL("", "P1");

	string key;
	string value;
	string opinion;
	//ask input from user
	cout <<"Please enter your opinion. Ask for ask for KB. Tell for tell the KB.End for end the program."<<endl;
	cin>>opinion;
	while(opinion != "End"){
		if(opinion == "Ask"){
			cout <<"Please enter the key you want to ask"<<endl;
			cin >> myQuery;
			if (myKB.ASK(myQuery))
				cout << "My knowledge base entails   " << myQuery.c_str()<<endl;
			else
				cout << "My knowledge base does not entail   " << myQuery.c_str()<<endl;
		}
		else{
			cout <<"Please enter the key you want to tell"<<endl;
			cin >> key;
			cout <<"Please enter the value you want to tell"<<endl;
			cin >> value;
			myKB.TELL(value, key);
		}
		//get next command
		cout <<"Please enter the next opinion you want to pick"<<endl;
		cin >>opinion;
	}
	
	//if (myKB.ASK(myQuery))
	//	cout << "My knowledge base entails   " << myQuery.c_str()<<endl;
	//else
	//	cout << "My knowledge base does not entail   " << myQuery.c_str();
	//getchar();
}
