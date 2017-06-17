#include <iostream>
using namespace std;

void statement(int tab);
void labeled_statement(int tab);
void expression_statement(int tab);
void compound_statement(int tab);
void statement_seq(int tab);
void selection_statement(int tab);
void condition(int tab);
void iteration_statement(int tab);
void for_init_statement(int tab);
void for_range_declaration(int tab);
void for_range_initializer(int tab);
void jump_statement(int tab);
void declaration_statement(int tab);
void block_declaration(int tab);
void braced_init_list(int tab);
void decl_specifier_seq(int tab);
void declarator(int tab);
void initializer_clause(int tab);
void expression(int tab);
void constant_expression(int tab);
void condition(int tab);
void try_block(int tab);
void simple_declaration(int tab);

#define MAX_DEEP  2
#define TAB_FUNCTION(tab) do{\
	for(int i = 0; i <= tab; ++i) \
		cout << "|  ";\
	cout<<endl;\
	for(int i = 0; i < tab; ++i)\
		cout << "|  ";\
	cout << "+- " << __FUNCTION__ << endl;}while(0)
#define OUTPUT(tab, str) do{\
	for(int i = 0; i <= tab; ++i)\
		cout << "|  ";\
	cout << endl;\
	for(int i = 0; i < tab; ++i)\
		cout << "|  ";\
	cout << "|-> " << str << endl;}while(0)

void statement(int tab)
{
	TAB_FUNCTION(tab);
	static int rs = 0;
	++rs;
	if(rs >= MAX_DEEP) {
		--rs;
		return;
	}

	OUTPUT(tab + 1, "labeled_statement");
	labeled_statement(tab + 2);
	OUTPUT(tab + 1, "expression_statement");
	expression_statement(tab + 2);
	OUTPUT(tab + 1, "compound_statement");
 	compound_statement(tab + 2);
	OUTPUT(tab + 1, "selection_statement");
	selection_statement(tab + 2);
	OUTPUT(tab + 1, "iteration_statement");
 	iteration_statement(tab + 2);
	OUTPUT(tab + 1, "jump_statement");
 	jump_statement(tab + 2);
	OUTPUT(tab + 1, "declaration_statement");
 	declaration_statement(tab + 2);
	OUTPUT(tab + 1, "try_block");
 	try_block(tab + 2);
	--rs;
}

void labeled_statement(int tab)
{
	TAB_FUNCTION(tab);
	OUTPUT(tab + 1, "ID : statement");
	statement(tab + 2);
	OUTPUT(tab + 1, "case constant_expression : statement"); 
	constant_expression(tab + 2); 
	statement(tab + 2);
	OUTPUT(tab + 1, "default : statement"); 
	statement(tab + 2);
}

void expression_statement(int tab)
{
	TAB_FUNCTION(tab);
	OUTPUT(tab + 1, ";");
	OUTPUT(tab + 1, "expression ;");
	expression(tab + 2);
}

void compound_statement(int tab)
{
	TAB_FUNCTION(tab);
	OUTPUT(tab + 1, "{ }");
	OUTPUT(tab + 1, "{ statement_seq }"); 
	statement_seq(tab + 2);
}

void statement_seq(int tab)
{
	TAB_FUNCTION(tab);
	statement(tab + 1);
	//statement_seq statement
}

void selection_statement(int tab)
{
	TAB_FUNCTION(tab);
	OUTPUT(tab + 1, "if ( condition ) statement"); 
	OUTPUT(tab + 1, "if ( condition ) statement else statement"); 
	OUTPUT(tab + 1, "switch ( condition ) statement"); 
	condition(tab + 2); 
	statement(tab + 2);
}

void condition(int tab)
{
	TAB_FUNCTION(tab);

	expression(tab + 1);
	OUTPUT(tab + 1, "decl_specifier_seq declarator = initializer_clause");
	decl_specifier_seq(tab + 2); 
	declarator(tab + 2); 
	initializer_clause(tab + 2);
	OUTPUT(tab + 1, "ecl_specifier_seq declarator braced_init_list");
	decl_specifier_seq(tab + 2); 
	declarator(tab + 2); 
	braced_init_list(tab + 2);
}

void iteration_statement(int tab)
{
	TAB_FUNCTION(tab);
	OUTPUT(tab + 1, "while ( condition ) statement");
	condition(tab + 2); 
	statement(tab + 2);
	OUTPUT(tab + 1, "do statement while ( expression ) ;"); 
	statement(tab + 2); 
	expression(tab + 2); 
	OUTPUT(tab + 1, "for ( for_init_statement condition opt ; expression opt ) statement"); 
	for_init_statement(tab + 2); 
	condition(tab + 2); 
	expression(tab + 2); 
	statement(tab + 2);
	OUTPUT(tab + 1, "for ( for_range_declaration : for_range_initializer ) statement"); 
	for_range_declaration(tab + 2);
	for_range_initializer(tab + 2);
	statement(tab + 2);
}

void for_init_statement(int tab)
{
	TAB_FUNCTION(tab);
	OUTPUT(tab + 1, "expression_statement");
	expression_statement(tab + 1);
	OUTPUT(tab + 1, "simple_declaration");
	simple_declaration(tab + 1);
}

void for_range_declaration(int tab)
{
	TAB_FUNCTION(tab);
	OUTPUT(tab + 1, "decl_specifier_seq declarator");
 	decl_specifier_seq(tab + 2); 
 	declarator(tab + 2);
}

void for_range_initializer(int tab)
{
	TAB_FUNCTION(tab);
	OUTPUT(tab + 1, "expression");
	expression(tab + 1);
	OUTPUT(tab + 1, "braced_init_list");
	braced_init_list(tab + 1);
}

void jump_statement(int tab)
{
	TAB_FUNCTION(tab);
	OUTPUT(tab + 1, "break ;");
	OUTPUT(tab + 1, "continue ;");
	OUTPUT(tab + 1, "return expression ");
	expression(tab + 2); 
	OUTPUT(tab + 1, "return braced_init_list;");
	braced_init_list(tab + 2);
	OUTPUT(tab + 1, "goto ID ;");
}

void declaration_statement(int tab)
{
	TAB_FUNCTION(tab);
	OUTPUT(tab + 1, "block_declaration");
	block_declaration(tab + 1);
}


void block_declaration(int tab)
{
	TAB_FUNCTION(tab);
}

void braced_init_list(int tab)
{
	TAB_FUNCTION(tab);
}

void decl_specifier_seq(int tab)
{
	TAB_FUNCTION(tab);
}

void declarator(int tab)
{
	TAB_FUNCTION(tab);
}

void initializer_clause(int tab)
{
	TAB_FUNCTION(tab);
}

void expression(int tab)
{
	TAB_FUNCTION(tab);
}

void constant_expression(int tab)
{
	TAB_FUNCTION(tab);
}

void try_block(int tab)
{
	TAB_FUNCTION(tab);
}

void simple_declaration(int tab)
{
	TAB_FUNCTION(tab);
}

int main(int argc, char *argv[])
{
	statement(0);
	return 0;
}
