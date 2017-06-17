#include "public.h"

void output(leaf_t &code, code2str_vec_t &code2str)
{
	leaf_t::iterator row = code.begin();
	for(; row != code.end(); ++row) {
		for(vector<int>::iterator col = (*row).begin(); col != (*row).end(); ++col)
			if(*col)
				cout << code2str[*col] << " ";
		cout << endl;
	}
}

#if 0
#define INSERT(old_leaf, new_leaf) 	old_leaf.insert(old_leaf.end(), new_leaf.begin(), new_leaf.end())
#else
void insert(leaf_t &old_leaf, leaf_t &new_leaf)
{
	old_leaf.insert(old_leaf.end(), new_leaf.begin(), new_leaf.end());	
}
#endif

void push_back(leaf_t &old_leaf, leaf_t &new_leaf, bool opt)
{
	//cout << "push_back leaf" << endl;
	int old_size;
	int dump_size;

	if(opt)
		dump_size = new_leaf.size();
	else
		dump_size = new_leaf.size() - 1;

	old_size = old_leaf.size();

	leaf_t tmp;
	for(int i = 0; i < dump_size; ++i) {
		leaf_t::iterator it = old_leaf.begin();
		for(int j = 0; j < old_size; ++j, ++it)
			tmp.push_back(*it);
	}

	leaf_t::iterator it = tmp.begin();
	for(; it != tmp.end(); ++it)
		old_leaf.push_back(*it);

	leaf_t::iterator outer_it = new_leaf.begin();
	leaf_t::iterator inner_it = old_leaf.begin();
	for(; outer_it != new_leaf.end(); ++outer_it) {
		if(old_size) {
			for(int i = 0; i < old_size; ++i, ++inner_it)
				inner_it->insert(inner_it->end(), outer_it->begin(), outer_it->end()); 
		} else {
			vector<int> tmp;
			tmp.insert(tmp.end(), outer_it->begin(), outer_it->end());
			old_leaf.push_back(tmp);
		}

	}
	//output_code(old_leaf);
//	cout << dump_size << endl;
}

//void push_back(leaf_t &old_leaf, int token, bool opt)
void push_back(leaf_t &old_leaf, Token_t tk, bool opt)
{
	//cout << "push_back token" << endl;
	int old_size;
	int token = tk;
	old_size = old_leaf.size();
	if(old_size) {
		leaf_t::iterator it;
		leaf_t tmp;
		if(opt) {
			it = old_leaf.begin();
			for(int i = 0; i < old_size; ++i, ++it) {
				tmp.push_back(*it);
			}
			for(it = tmp.begin(); it != tmp.end(); ++it)
				old_leaf.push_back(*it);
		}

		it = old_leaf.begin();
		for(int i = 0; i < old_size; ++i, ++it)
			(*it).push_back(token);
	} else {
		if(opt) {
			vector<int> tmp;
			tmp.push_back(0);
			old_leaf.push_back(tmp);
		}
		vector<int> tmp;
		tmp.push_back(token);
		old_leaf.push_back(tmp);
	}
//	output_code(old_leaf);
}

void init_data(const char *f, str2code_map_t &str2code, code2str_vec_t &code2str)
{
	ifstream fin(f);	
	if(!fin.is_open()) {
		cout << "Error：cant open file!" << endl;
		exit(-1);
	}

	int code = 0;
	char buff[MAX_BUFF];
	string first, second;

	while(fin.getline(buff, MAX_BUFF)){
		istringstream iss(buff);
		iss >> first >> second;
		str2code[first] = code;
		code2str.push_back(first);
		++code;
	} 
}

