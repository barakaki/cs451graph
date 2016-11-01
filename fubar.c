#include "fubar.h"
#include <vector>

vector<string> data;
	int temp;
	int temp2;
	int rememberelse;

int store(string s)
{
	int n = data.size();
	data.push_back(s);
	return n;
}
string lookup(int n)
{
	return data[n];
}
void start(){
	cout << data[1] << "->";
}
void output(int input)
{

	for(int i=input; i < data.size(); i++)
	{

		if (data[i] == "if")
			{
				i++;//skip if
				i++;//skip (
				cout << '"';
				temp = i;
				temp2= i;
				rememberelse = i;
				while(data[i] != ")"){
						cout <<  data[i];
						i++;
					}
				cout << '"' << endl;

				cout << '"';
				while(data[temp] != ")"){
						cout << data[temp];
						temp++;
				}			
				cout << '"' << " [shape = diamond]" << endl;

				cout << '"';				
				while(data[temp2] != ")"){
						cout << data[temp2];
						temp2++;
				}
				cout << '"' << ":w" << "->";
				i++; // skips )
				i++; //skips {
				while( data[i] != "}")
					{
						outputblock(i);
						i++;
					}
				cout << '"' << "[label = true]" << endl;
			}
	
		else if(data[i] == "else")
			{
				i++; //skips else
				i++; //skips {
				cout << '"';
				while(data[rememberelse] != ")"){
						cout << data[rememberelse];
						rememberelse++;
				}
				cout << '"' << ":e" << "->";
				while( data[i] != "}")
					{
						outputblock(i);
						i++;
					}
				cout << '"' << "[label = false]" << endl;
			}
		else 
			{
				
			}
	}
}
void outputblock(int placement)
{
	if(data[placement] == "if")
		{
			output(placement);
			while(data[placement] != ")")
				{
					placement++;
				}
		}
	else if(data[placement] == ";")
		{
			
		}
	else
		{
			cout << '"' << data[placement];
		}
}
void finish(){
cout << data[1] << "[shape = none]" << endl;
	cout << "\n}" << endl;
}

