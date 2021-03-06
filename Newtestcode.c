#include "fubar.h"
#include <vector>
#include <iostream>
#include <string>


vector<string> data;
vector<string>digraph;
	vector<int>ifPos;

	int fortemp;
	int fortemp2;
	int fortemp3;
	int fortemp4;
	int fortemp5;
	int temp;
	int temp2;
	int temp3;
	int temp4;
	int ifcounter=0;
	int forcounter=0;
	int forcounter2=0;
	int truelabelcounter;
	int falselabelcounter;
	int lastthing;
	int rememberelse;
	int once =1;
	int number =2;
	int checkstatement;

int node = 0, switchNode = 0, endNode = -1;
	bool isIfBracket = false, isFallthrough = false, isSwitchbracket = false;
	bool notinstatements=true;
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
void justinoutput(){
int start=0;
	cout << '"';
while(data[start] != "{"){
	cout << data[start];
	start++;
}
	cout << '"' << "-> 0" <<  endl;
	int tempstarter =0;
	for (unsigned int i = 5; i < data.size(); i++)
	{
		if (data[i] == "if" || data[i] == "switch")
		{
			notinstatements=false;
			if (data[i] == "if")
			{
				isSwitchbracket = true;
				ifPos.push_back(node);
				isIfBracket = true;
			}

			i += 2;
			string temp = "";

			while (data[i] != ")")
			{
				temp += data[i];
				i++;
			}

			digraph.push_back(to_string(node) + "[label = " +'"'+ temp + '"' +" shape = diamond]");


			//digraph.push_back(data[i]);
			int checknext = i++;
			checknext++;
			checknext++;

			if(data[checknext] != "if"|| data[checknext]!="switch" ){notinstatements=true;}
			else{notinstatements=false;}

			if (isIfBracket)
			{
				digraph.push_back(to_string(ifPos.back()) + "->" + to_string(++node) + "[label = true]");
			}
			else
			{
				if (node != 0)
				{
					digraph.push_back(to_string(node++) + "->" + to_string(node));
				}

				switchNode = node;
			}
		}
		else if (data[i] == "else")
		{
int checknext = i++;
			checknext++;
			checknext++;
			if(data[checknext] != "if"|| data[checknext]!="switch" ){notinstatements=true;}
			else{notinstatements=false;}

			digraph.push_back(to_string(ifPos.back()) + "->" + to_string(++node) + "[label = false]");
			
			isIfBracket = false;
			ifPos.pop_back();

		}
		else
		{
 
			if (data[i] == "}")
			{

				if (isIfBracket && ifPos.size() > 0)
				{
					ifPos.pop_back();
				}
				continue;
			}

			if (data[i] == "{" || data[i] == ";")
			{
				i++;
			}

			string temp = "", code = "";
	
			if (data[i] == "case")
			{
				notinstatements=false;
				i++;
				while (data[i] != ":")
				{
					code += data[i];
					i++;
				}

				if (isFallthrough)
				{
					digraph.push_back(to_string(switchNode) + "->" + to_string(node) + "[label =" + '"'+ code +'"' + "]");
					isFallthrough = false;
				}
				else
				{
					digraph.push_back(to_string(switchNode) + "->" + to_string(++node) + "[label =" + '"'+code+'"' + "]");
				}

				continue;
			}
			else if (data[i] == "default")
			{
				notinstatements=false;
				code = data[i];
				digraph.push_back(to_string(switchNode) + "->" + to_string(endNode) + "[label = " + '"'+ code +'"' + "]");

				while (data[i] != "}")
				{
					i++;
				}

				continue;
			}

//WHERE IT READS THE CODE INSIDE { }, PUT LOOP HERE TO OUTPUT STUFF THATS NOT IF,ELSE,SWITCH,ETC...
			while (data[i] != "if" && data[i] != "else" && data[i] != "switch" && data[i] != "case" && data[i] != "break" && data[i] != "}")
			{
				if (data[i] != ";")
				{
					code += data[i];
				}
				i++;
			}

			temp = data[i];

			if(notinstatements==true){
				//digraph.push_back(to_string(--node) + "->" + to_string(++node));
				//node++;
				int tempnode, nextnode;
				tempnode =node;
				nextnode = tempnode++;
				if(temp=="}" && isSwitchbracket){
					//digraph.push_back(to_string(nextnode)+ "->" + to_string(endNode));
					digraph.push_back(to_string(node) + "[label = " +'"'+ code+'"' + "]");
				}
				else if(temp == "break")
				{

				}
				else{

					digraph.push_back(to_string(nextnode) + "->"+ to_string(tempnode));
					digraph.push_back(to_string(node) + "[label = " +'"'+ code+'"' + "]");
					node++;
				}
				
				
			}
			else /*if (code.size() > 0)*/
			{
				digraph.push_back(to_string(node) + "[label = " +'"'+ code+'"' + "]");

//HERE
				
				/*if(node==0){

					digraph.push_back(to_string(node)+"->"+ digraph.push_back(node++));
					node++;
				}*/

			}

		
			if (temp == "if" || temp == "else" || temp == "switch")
			{
				i--;
			}	
			else if (temp == "case")
			{

				isFallthrough = true;
				digraph.push_back(to_string(--node) + "->" + to_string(++node));
				node++;
				i--;
			}
			else if (temp == "}" && isSwitchbracket)
			{	
				if(isSwitchbracket){
				digraph.push_back(to_string(node) + "->" + to_string(endNode));
				isIfBracket = false;
				}

				continue;
			}
			else
			{
				if(isSwitchbracket)
				{
					isSwitchbracket= false;
				}
				else{
				digraph.push_back(to_string(node) + "->" + to_string(endNode));

				}
			}
		}
	}
	digraph.push_back(to_string(endNode) + "[label = " + '"' +"return 0" +'"' + ",shape=oval]");

	for (unsigned int i = 0; i < digraph.size(); i++)
	{
		cout << digraph[i] << endl;

	}
			cout << "}" << endl;

}









void start(int input){
	cout << data[1] << "->";
	for(int i=input; i < data.size(); i++)
	{
		if(data[i] == "if"){ifcounter++;truelabelcounter++;falselabelcounter++;}
		else if(data[i] =="for"){forcounter++;}
		else{}
	}
}
void output(int input)
{

	for(int i=input; i < data.size(); i++)
	{

		if (data[i] == "if" && ifcounter !=0)
			{
				i++;//skip if
				i++;//skip (
				ifstatement(i);
				while(data[i] != "else"){i++;}
				i++;
				i++;
				elsestatement(i);
				ifcounter--;
			}
	
		else if(data[i]=="for" && forcounter !=0)
			{
				i++;
				i++;
				forstatement(i);
				forcounter--;
			}
		else{}
	}
}
void forstatement(int placement){

	if(once ==1){
	cout << '"';
}	

				fortemp = placement;
				fortemp2= placement;
				fortemp3 = placement;
				fortemp5 = placement;
				lastthing = placement;
				temp3 = placement;
				checkstatement =1;
	while(data[placement] != ")"){
						cout <<  data[placement];
						placement++;
					}
				cout << '"' << endl;
	
				cout << '"';
				while(data[fortemp] != ")"){
						cout << data[fortemp];
						fortemp++;
				}			
				cout << '"' << " [shape = diamond]" << endl;

				cout << '"';

				while(data[fortemp2] != ")"){
						cout << data[fortemp2];
						fortemp2++;
				}
				cout << '"' << ":w" << "->" << '"';
				placement++; // skips )
				placement++; //skips {
				fortemp4 = placement;
				while( data[placement] != "}")
					{
						if(data[placement] == "if")
						{
						outputblock(placement);
					while(data[placement] != "}"){placement++;}
						}
						else if(data[placement] == "for")
						{
						outputblock(placement);
					while(data[placement] != "}"){placement++;}
						}
						else{
						cout << data[placement];
						placement++;}
					}
				cout << '"' << "[label = true]" << endl;
				
				cout << '"';	
				while( data[fortemp4] != "}")
					{
						if(data[fortemp4] == "if")
						{
						outputblock(fortemp4);
					while(data[fortemp4] != "}"){fortemp4++;}
						}
						else if(data[fortemp4] == "for")
						{
						outputblock(fortemp4);
					while(data[fortemp4] != "}"){fortemp4++;}
						}
						else{
						cout << data[fortemp4];
						fortemp4++;}
					}
				
				cout << '"' << ":e->" << '"';
				while(data[fortemp3] != ")"){
						cout << data[fortemp3];
						fortemp3++;
				}			
				cout << '"' << ":s[label=" << '"' << "increment/decrement" << '"' << "]" << endl;
				if(ifcounter ==0){
				if(placement+3 >= data.size()){
				cout << '"';
					while(data[fortemp5] != ")"){
						cout << data[fortemp5];
						fortemp5++;
				}	
				
				cout << '"' << ":e -> " << '"' << "return 0" << '"' << "[label=false]" << endl;
				cout << '"' << "return 0" << '"' << "[shape = oval]" << endl;
				}
				}

}	
void ifstatement(int placement){
				cout << '"';
				temp = placement;
				temp2= placement;

				rememberelse = placement;
				while(data[placement] != ")"){
						cout <<  data[placement];
						placement++;
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
				
				placement++; // skips )
				placement++; //skips {
				//temp4 = placement;
				lastthing = placement;
				cout << '"' << ":w" << "->";
				while( data[placement] != "}")
					{
						if(data[placement] == "if")
						{
						outputblock(placement);
					while(data[placement] != "}"){placement++;}
						}
						else if(data[placement] == "for")
						{
						forcounter2 =1;
						truelabelcounter--;
						forcounter2 =0;
						outputblock(placement);
					while(data[placement] != "}"){placement++;}
						}
						else{
						if(once==1){cout << '"';once--;}
						cout << data[placement];
						placement++;}
					}
					once =1;
				if(truelabelcounter !=0){cout << '"' << "[label = true]" << endl;}
				cout << '"';

if(forcounter2 >0){
				forcounter2=0;
				while( data[lastthing] != ")")
					{
						if(data[lastthing] == "if")
						{
						outputblock(lastthing);
					while(data[lastthing] != ")"){lastthing++;}
						}
						else if(data[lastthing] == "for")
						{
						outputblock(lastthing);
					while(data[lastthing] != ")"){lastthing++;}
						}
						else{
						cout << data[lastthing];
						lastthing++;}
					}
					cout << '"' << ":e -> " << '"' << "pointstogether" << '"' <<"[arrowhead=none][label = false]" << endl;
}
else /*if(forcounter ==1)*/{
while( data[lastthing] != "}")
					{
						if(data[lastthing] == "if")
						{
						outputblock(lastthing);
					while(data[lastthing] != ")"){lastthing++;}
						}
						else if(data[lastthing] == "for")
						{
						outputblock(lastthing);
					while(data[lastthing] != ")"){lastthing++;}
						}
						else{
						cout << data[lastthing];
						lastthing++;}
					}
					cout << '"' << ":s -> " << '"' << "pointstogether" << '"' <<"[arrowhead=none]" << endl;
}		



				
}
void elsestatement(int placement){
				cout << '"';
				lastthing = placement;
				while(data[rememberelse] != ")"){
						cout << data[rememberelse];
						rememberelse++;
				}
				cout << '"' << ":e" << "->" << '"';
				once =0;
				temp3=placement;
				checkstatement =2;
				while( data[placement] != "}")
					{
						if(data[placement] == "if")
						{
						falselabelcounter--;
						outputblock(placement);
					while(data[placement] != "}"){placement++;}
						}
						else if(data[placement] == "for")
						{
						forcounter2 =1;
						falselabelcounter--;
						outputblock(placement);

					while(data[placement] != "}"){placement++;}
						}
						else{

						cout << data[placement];
						placement++;}
					}
				if(falselabelcounter !=0){cout << '"' << "[label = false]" << endl;falselabelcounter--;}

				cout << '"';
if(forcounter2 > 0){
					forcounter2=0;
					while( data[lastthing] != ")")
					{
						number++;
						if(data[lastthing] == "if")
						{
						outputblock(lastthing);
					while(data[lastthing] != "}"){lastthing++;}
						}
						else if(data[lastthing] == "for")
						{
						outputblock(lastthing);
					while(data[lastthing] != "}"){lastthing++;}
						}
						else{
						cout << data[lastthing];
						lastthing++;}
					}
					cout << '"' << ":s -> " << '"' << "pointstogether" << '"' <<"[arrowhead=none]" << endl;
}
else{
while( data[lastthing] != "}")
					{
						number++;
						if(data[lastthing] == "if")
						{
						outputblock(lastthing);
					while(data[lastthing] != "}"){lastthing++;}
						}
						else if(data[lastthing] == "for")
						{
						outputblock(lastthing);
					while(data[lastthing] != "}"){lastthing++;}
						}
						else{
						cout << data[lastthing];
						lastthing++;}
					}
				cout << '"' << ":e -> " << '"' << "pointstogether" << '"' <<"[arrowhead=none][label = false]" << endl;				
}

				cout << "pointstogether[label=" << '"' << '"' << ",fixedsize=false,width=0,height=0,shape=none]" << endl;
				cout << '"' << "pointstogether" << '"' << "->";
				if(placement+number >= data.size()){
				cout << '"' << "return 0" << '"' << "[shape=oval]" << endl;
				}
}


void outputblock(int placement)
{
	if(data[placement] == "if")
		{
			output(placement);
		}
	else if(data[placement] == ";")
		{
			
		}
	else if(data[placement] == "for")
		{
			output(placement);
		}
	else
		{
			cout << data[placement];
		}
}
void finish(){
cout << data[1] << "[shape = none]" << endl;
	cout << "\n}" << endl;
}

