#include <regex>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int main(){

string line;
regex re("([a-zA-Z]+)( *)([0-9]+)(.*)(Deleting interface)(.*)(interface stats: received)=([0-9]+)(.*)(sent)=([0-9]+)(.*)(dropped)=([0-9]+)(.*)(active_time)=([0-9]+)(.*)(secs)");
cout << "Received" << '\t' << "Sent" << '\t' << "Dropped" << '\t'<<'\t' << "Active time" << '\t' << "Date" << endl;
		
while(getline(cin,line))
	{
		for(smatch m; regex_search(line, m, re); line=m.suffix())
			{
				cout << m[8]<<  '\t'<<'\t' << m[11]<<'\t' << m[14] <<  '\t'<<'\t' << m[17]<< '\t'<<'\t' <<m[1]<< " " << m[3] <<  endl;
			}

	}
return 0;
}

