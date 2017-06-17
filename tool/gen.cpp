#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <sstream>
#include <fstream>
#include <cstring>

using std::cout;
using std::endl;
using std::string;
using std::map;
using std::vector;
using std::set;
using std::ifstream;
using std::istringstream;
using std::pair;

typedef map< string, int > Str2CodeMap;
typedef vector< string > Code2StrVec;

#define MAX_BUFF 256
#define MAX_FUNC_BUFF 8192 

void initData(const char *f, Str2CodeMap &str2code, Code2StrVec &code2str)
{
	ifstream fin(f);	
	if(!fin.is_open()) {
		cout << "Error: cant open file!" << endl;
		exit(-1);
	}

	int code = 0;
	char buff[MAX_BUFF];
	string first, second;

	while(fin.getline(buff, MAX_BUFF)){
		istringstream iss(buff);
		iss >> first >> second;
		str2code[first] = code;
		code2str.push_back(second);
		++code;
	} 
}

char toupper(char c)  
{  
    if ((c >= 'a') && (c <= 'z'))  
        return c + ('A' - 'a');  
    return c;  
} 

#if 0
#define DEBUG(output) cout << "Debug: " << output << endl
#else
#define DEBUG(output) 
#endif

int getCode(Str2CodeMap &str2code, string &str);
void outputData(Str2CodeMap & str2code, Code2StrVec &code2str)
{
	Str2CodeMap::iterator it = str2code.begin();
	for(; it != str2code.end(); ++it)
		cout << it->first << " : " << it->second << endl;

	cout << "code2string" << endl;
	for(int i = 0; i < code2str.size(); ++i)
		cout << i << " : " << code2str[i] << endl; 

	for(int i = 0; i < code2str.size(); ++i)
		if(i != getCode(str2code, code2str[i])) 
			cout << "error:" << code2str[i] << endl;

}

int getCode(Str2CodeMap &str2code, string &str)
{
	Str2CodeMap::iterator mit;
	mit = str2code.find(str);
	if(mit != str2code.end())
		return mit->second;
	else
		return -1;
}

void genDeclar(char *file)
{
	ifstream fin(file);	
	if(!fin.is_open()) {
		cout << "Error：cant open file!" << endl;
		exit(-1);
	}

	string function;
	char buff[256];
	int len;

	while(fin.getline(buff, 256)){
		len = strlen(buff);
		if(buff[len - 1] == ':' &&  buff[len - 2] == ' ') {
			istringstream iss(buff);
			iss >> function;
			cout << "void " << function << "(int tab, leaf_t &leaf);\n";
			memset(buff, 0, 256);
		}
	}
	fin.close();
}

void genCode(char *file, Str2CodeMap &str2code, Code2StrVec &code2str)
{
	ifstream fin(file);	
	if(!fin.is_open()) {
		cout << "cant open file!" << endl;
		exit(-1);
	}

	int code = 0;
	char buff[MAX_BUFF];
	bool flag;
	string function;
	int no = -1;
	set<string> def_function, undef_function;
	bool is_loop = false;

	cout << "#include \"public.h\"\n";
	cout << "#include \"";
	while(*file != '.') {
		cout << *file;
		++file;
	}
	cout << ".h\"\n\n";

	pair<set<string>::iterator, bool> ret;
	while(fin.getline(buff, MAX_BUFF)){
		DEBUG(buff);
		string  first, second;
		int len = strlen(buff);

		if(buff[0] == '#')
			continue;
		if(buff[len - 1] == ':' &&  buff[len - 2] == ' ') {
			if(no != -1) {
				cout << "\tpush_back(leaf, tmp_leaf);\n";
				if(is_loop)
					cout << "\t--rs;\n";
				cout << "}\n" << endl;
			}
			istringstream iss(buff);
			iss >> function;
			ret = def_function.insert(function);
			cout << "void " << function <<"(int tab, leaf_t &leaf)\n{\n"
				"\tleaf_t new_leaf, tmp_leaf;\n"
				"\tTAB_FUNCTION(tab);\n";
			is_loop = false;
			continue;
		} 

		cout << "\n\tOUTPUT(tab + 1, \"" << buff << "\");\n";
		cout << "\tnew_leaf.clear();\n";

		istringstream iss(buff);
		int first_code, second_code;
		flag = iss >> first; 

		bool rs_flag = false;

		while(flag) {
			flag = iss >> second;
			DEBUG(first);
			DEBUG(second);
			first_code = getCode(str2code, first);	
			if(first == function) {
				is_loop = true;
				cout << "\n\tstatic int rs = 0;\n";
				cout << "\t++rs;\n";
				cout << "\tif(rs >= MAX_DEEP) {\n";
				//cout << "\t\t--rs;\n";
				//cout << "\t\tpush_back(leaf, TEMP);\n";
				cout << "\t\treturn;\n";
				cout << "\t}\n\n";
			}
			if(flag) {
				second_code = getCode(str2code, second);
				if(first_code > 0 && first_code <= str2code.size()) {//terminal
					if(second_code == 0) { //opt
						cout <<"\tpush_back(new_leaf, " << code2str[first_code] << ", true);\n";
						flag = iss >> first;
					} else {//not opt
						cout <<"\tpush_back(new_leaf, " << code2str[first_code] << ");\n";
						first = second;
					}
				} else {//non-terminal
					cout << "\t" << first << "(tab + 2, new_leaf);\n";
					undef_function.insert(first);

					if(second_code == 0) {//opt
						flag = iss >> first;
					} else {
						first = second;
					}
				}
			} else {
				if(first_code > 0 && first_code <= str2code.size()) {//terminal
					cout <<"\tpush_back(new_leaf, " << code2str[first_code] << ");\n";
				} else {//non-terminal
					cout << "\t" << first << "(tab + 2, new_leaf);\n";
					undef_function.insert(first);
				}
			}
		}

		cout << "\tinsert(tmp_leaf, new_leaf);\n";
		no++;
	}

	cout << "\tpush_back(leaf, tmp_leaf);\n";
	if(is_loop)
		cout << "\t--rs;\n";
	cout << "}\n" << endl;

	set<string>::iterator it, ot;
	for(ot = def_function.begin(); ot != def_function.end(); ++ot) {
		it = undef_function.find(*ot);
		if(undef_function.end() != it) {
			undef_function.erase(*it);
		}
	}
	for(it = undef_function.begin(); it != undef_function.end(); ++it) {
		cout << "\nvoid " << *it << "(int tab, leaf_t &leaf)\n";
		cout << "{\n";
		cout << "\tTAB_FUNCTION(tab);\n";
		//cout << "\tpush_back(leaf, TEMP);\n";
		cout << "\tpush_back(leaf, ";
        for(int i = 0; i < (*it).size(); ++i)
            cout<< toupper((*it)[i]);
        cout << ");\n";
		cout << "}\n";
	}
	fin.close();
}

int main(int argc, char *argv[])
{
	if(argc != 2) {
		cout << "Usage: ./XXX  grammar.txt" << endl;
		return 0;
	}

	Str2CodeMap str2code;
	Code2StrVec code2str;

//	initData(argv[1], str2code, code2str);
	initData("terminal.h", str2code, code2str);
//	outputData(str2code, code2str);
#if 1
	genCode(argv[1], str2code, code2str);
#else
	genDeclar(argv[2]);
#endif
//
	return 0;
}

