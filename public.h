#ifndef _PUBLIC_H_
#define _PUBLIC_H_
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::ifstream;
using std::istringstream;
using std::string;

#define OTHER 2
#define SECOND 1
#define FIRST 0

#define MAX_BUFF 256
#define MAX_DEEP  2

#define COLOR_OUTPUT        switch(i % 8) {\
            case 0:\
                cout << "\e[31m|\e[0m  ";\
                break;\
            case 1:\
                cout << "\e[32m|\e[0m  ";\
                break;\
            case 2:\
                cout << "\e[33m|\e[0m  ";\
                break;\
            case 3:\
                cout << "\e[34m|\e[0m  ";\
                break;\
            case 4:\
                cout << "\e[35m|\e[0m  ";\
                break;\
            case 5:\
                cout << "\e[36m|\e[0m  ";\
                break;\
            case 6:\
                cout << "\e[37m|\e[0m  ";\
                break;\
            default:\
                cout << "|  ";\
                break;\
        }\

#define TAB_FUNCTION(tab) do{\
	for(int i = 0; i <= tab; ++i) \
        COLOR_OUTPUT\
	cout<<endl;\
	for(int i = 0; i < tab; ++i)\
        COLOR_OUTPUT\
	cout << "+- " << __FUNCTION__ << endl;}while(0)

#define OUTPUT_(tab, str) do{\
	for(int i = 0; i <= tab; ++i)\
		cout << "|  ";\
	cout << endl;\
	for(int i = 0; i < tab; ++i)\
		cout << "|  ";\
	cout << "|-> " << str << endl;}while(0)

#define OUTPUT(tab, str) do{\
	for(int i = 0; i <= tab; ++i)\
        COLOR_OUTPUT\
	cout << endl;\
	for(int i = 0; i < tab; ++i)\
        COLOR_OUTPUT\
	cout << "|-> " << str << endl;}while(0)

typedef vector<vector<int> > leaf_t;
typedef map< string, int > str2code_map_t;
typedef vector< string > code2str_vec_t;

typedef enum{
	OPT = 0,
#include "terminal.h"
#include "unterminal.h"
	NR_TERMINAL
}Token_t;

void insert(leaf_t &old_leaf, leaf_t &new_leaf);
void output(leaf_t &code, code2str_vec_t &code2str);
void push_back(leaf_t &old_leaf, leaf_t &new_leaf, bool opt=false);
void push_back(leaf_t &old_leaf, Token_t tk, bool opt=false);
void init_data(const char *f, str2code_map_t &str2code, code2str_vec_t &code2str);

//model

extern void statement(int tab, leaf_t &leaf);
extern void try_block(int tab, leaf_t &leaf);
extern void template_declaration(int tab, leaf_t &leaf);
extern void primary_expression(int tab, leaf_t &leaf);
extern void decl_specifier_seq(int tab, leaf_t &leaf);
#endif
