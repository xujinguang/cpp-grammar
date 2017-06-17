#include "public.h"
#include "stm.h"

void statement(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	static int rs = 0;
	++rs;
	if(rs >= MAX_DEEP) {
		--rs;
		push_back(leaf, TEMP);
		return;
	}

	leaf_t tmp_leaf;
	leaf_t new_leaf;
	leaf_t::iterator it = new_leaf.begin();
	OUTPUT(tab + 1, "labeled_statement");
	new_leaf.clear();
	labeled_statement(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "expression_statement");
	new_leaf.clear();
	expression_statement(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "compound_statement");
	new_leaf.clear();
 	compound_statement(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "selection_statement");
	new_leaf.clear();
	selection_statement(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "iteration_statement");
	new_leaf.clear();
 	iteration_statement(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "jump_statement");
	new_leaf.clear();
 	jump_statement(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "declaration_statement");
	new_leaf.clear();
 	declaration_statement(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "try_block");
	new_leaf.clear();
 	try_block(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	push_back(leaf, tmp_leaf);
	--rs;
}

void labeled_statement(int tab, leaf_t &leaf)
{
	leaf_t tmp_leaf;
	leaf_t new_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "ID : statement");
	push_back(new_leaf, ID);
	push_back(new_leaf, COLON);
	statement(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "case constant_expression : statement"); 
	new_leaf.clear();
	push_back(new_leaf, CASE);
	constant_expression(tab + 2, new_leaf); 
	push_back(new_leaf, COLON);
	statement(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "default : statement"); 
	new_leaf.clear();
	push_back(new_leaf, DEFAULT);
	push_back(new_leaf, COLON);
	statement(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	push_back(leaf, tmp_leaf);
}

void expression_statement(int tab, leaf_t &leaf)
{
	leaf_t tmp_leaf;
	leaf_t new_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, ";");
	push_back(new_leaf, SEMICOLON);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "expression ;");
	new_leaf.clear();
	expression(tab + 2, new_leaf);
	push_back(new_leaf, SEMICOLON);
	insert(tmp_leaf, new_leaf);

	push_back(leaf, tmp_leaf);
}

void compound_statement(int tab, leaf_t &leaf)
{
	leaf_t tmp_leaf;
	leaf_t new_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "{ }");
	push_back(new_leaf, L_BRACE);
	push_back(new_leaf, R_BRACE);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "{ statement_seq }"); 
	new_leaf.clear();
	push_back(new_leaf, L_BRACE);
	statement_seq(tab + 2, new_leaf);
	push_back(new_leaf, R_BRACE);
	insert(tmp_leaf, new_leaf);

	push_back(leaf, tmp_leaf);
}

void statement_seq(int tab, leaf_t &leaf)
{
	leaf_t tmp_leaf;
	leaf_t new_leaf;
	TAB_FUNCTION(tab);

	statement(tab + 2, new_leaf);
	push_back(leaf, new_leaf);
	//statement_seq statement
	push_back(leaf, tmp_leaf);
}

void selection_statement(int tab, leaf_t &leaf)
{
	leaf_t tmp_leaf;
	leaf_t new_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "if ( condition ) statement"); 
	OUTPUT(tab + 1, "if ( condition ) statement else statement"); 
	push_back(new_leaf, IF);
	push_back(new_leaf, L_PARENTHESIS);
	condition(tab + 2, new_leaf); 
	push_back(new_leaf, R_PARENTHESIS);
	statement(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "switch ( condition ) statement"); 
	new_leaf.clear();
	push_back(new_leaf, SWITCH);
	push_back(new_leaf, L_PARENTHESIS);
	condition(tab + 2, new_leaf); 
	push_back(new_leaf, R_PARENTHESIS);
	statement(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	push_back(leaf, tmp_leaf);
}

void condition(int tab, leaf_t &leaf)
{
	leaf_t tmp_leaf;
	leaf_t new_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "expression");
	expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "decl_specifier_seq declarator = initializer_clause");
	new_leaf.clear();
	decl_specifier_seq(tab + 2, new_leaf); 
	declarator(tab + 2, new_leaf); 
	push_back(new_leaf, ASSIGN);
	initializer_clause(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "ecl_specifier_seq declarator braced_init_list");
	new_leaf.clear();
	decl_specifier_seq(tab + 2, new_leaf); 
	declarator(tab + 2, new_leaf); 
	braced_init_list(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	push_back(leaf, tmp_leaf);
}

void iteration_statement(int tab, leaf_t &leaf)
{
	leaf_t tmp_leaf;
	leaf_t new_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "while ( condition ) statement");
	push_back(new_leaf, WHILE);
	push_back(new_leaf, L_PARENTHESIS);
	condition(tab + 2, new_leaf); 
	push_back(new_leaf, R_PARENTHESIS);
	statement(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "do statement while ( expression ) ;"); 
	new_leaf.clear();
	push_back(new_leaf, DO);
	statement(tab + 2, new_leaf); 
	push_back(new_leaf, WHILE);
	push_back(new_leaf, L_PARENTHESIS);
	expression(tab + 2, new_leaf); 
	push_back(new_leaf, R_PARENTHESIS);
	push_back(new_leaf, SEMICOLON);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "for ( for_init_statement condition opt ; expression opt ) statement"); 
	new_leaf.clear();
	push_back(new_leaf, FOR);
	push_back(new_leaf, L_PARENTHESIS);
	for_init_statement(tab + 2, new_leaf); 
	condition(tab + 2, new_leaf); 
	push_back(new_leaf, SEMICOLON);
	expression(tab + 2, new_leaf); 
	push_back(new_leaf, R_PARENTHESIS);
	statement(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "for ( for_range_declaration : for_range_initializer ) statement"); 
	new_leaf.clear();
	push_back(new_leaf, FOR);
	push_back(new_leaf, L_PARENTHESIS);
	for_range_declaration(tab + 2, new_leaf);
	push_back(new_leaf, COLON);
	for_range_initializer(tab + 2, new_leaf);
	push_back(new_leaf, R_PARENTHESIS);
	statement(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	push_back(leaf, tmp_leaf);
}

void for_init_statement(int tab, leaf_t &leaf)
{
	leaf_t tmp_leaf;
	leaf_t new_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "expression_statement");
	expression_statement(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "simple_declaration");
	new_leaf.clear();
	simple_declaration(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	push_back(leaf, tmp_leaf);
}

void for_range_declaration(int tab, leaf_t &leaf)
{
	leaf_t new_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "decl_specifier_seq declarator");
 	decl_specifier_seq(tab + 2, new_leaf); 
 	declarator(tab + 2, new_leaf);

	push_back(leaf, new_leaf);
}

void for_range_initializer(int tab, leaf_t &leaf)
{
	leaf_t tmp_leaf;
	leaf_t new_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "expression");
	expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "braced_init_list");
	new_leaf.clear();
	braced_init_list(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	push_back(leaf, tmp_leaf);
}

void jump_statement(int tab, leaf_t &leaf)
{
	leaf_t tmp_leaf;
	leaf_t new_leaf;
	TAB_FUNCTION(tab);
	OUTPUT(tab + 1, "break ;");
	push_back(new_leaf, BREAK);
	push_back(new_leaf, SEMICOLON);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "continue ;");
	new_leaf.clear();
	push_back(new_leaf, CONTINUE);
	push_back(new_leaf, SEMICOLON);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "return expression ");
	new_leaf.clear();
	push_back(new_leaf, RETURN);
	expression(tab + 2, new_leaf); 
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "return braced_init_list;");
	new_leaf.clear();
	push_back(new_leaf, RETURN);
	braced_init_list(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "goto ID ;");
	new_leaf.clear();
	push_back(new_leaf, GOTO);
	push_back(new_leaf, ID);
	push_back(new_leaf, SEMICOLON);
	insert(tmp_leaf, new_leaf);

	push_back(leaf, tmp_leaf);
}

void declaration_statement(int tab, leaf_t &leaf)
{
	leaf_t new_leaf;
	TAB_FUNCTION(tab);
	OUTPUT(tab + 1, "block_declaration");
	block_declaration(tab + 2, new_leaf);
	push_back(leaf, new_leaf);
}


void block_declaration(int tab, leaf_t &leaf)
{
	leaf_t tmp_leaf;
	leaf_t new_leaf;
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

void braced_init_list(int tab, leaf_t &leaf)
{
	leaf_t tmp_leaf;
	leaf_t new_leaf;
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}


void declarator(int tab, leaf_t &leaf)
{
	leaf_t tmp_leaf;
	leaf_t new_leaf;
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

void initializer_clause(int tab, leaf_t &leaf)
{
	leaf_t tmp_leaf;
	leaf_t new_leaf;
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}
#ifdef STM_MODEL
void decl_specifier_seq(int tab, leaf_t &leaf)
{
	leaf_t tmp_leaf;
	leaf_t new_leaf;
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}
void expression(int tab, leaf_t &leaf)
{
	leaf_t tmp_leaf;
	leaf_t new_leaf;
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

void constant_expression(int tab, leaf_t &leaf)
{
	leaf_t tmp_leaf;
	leaf_t new_leaf;
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

void try_block(int tab, leaf_t &leaf)
{
	leaf_t tmp_leaf;
	leaf_t new_leaf;
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}
#endif

void simple_declaration(int tab, leaf_t &leaf)
{
	leaf_t tmp_leaf;
	leaf_t new_leaf;
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

