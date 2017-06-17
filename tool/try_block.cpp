#include "public.h"
#include "try_block.h"

void try_block(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "try compound_statement handler_seq");
	new_leaf.clear();
	push_back(new_leaf, TRY);
	compound_statement(tab + 2, new_leaf);
	handler_seq(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void function_try_block(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "try ctor_initializer opt compound_statement handler_seq");
	new_leaf.clear();
	push_back(new_leaf, TRY);
	ctor_initializer(tab + 2, new_leaf);
	compound_statement(tab + 2, new_leaf);
	handler_seq(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void handler_seq(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "handler handler_seq opt");
	new_leaf.clear();
	handler(tab + 2, new_leaf);

	static int rs = 0;
	++rs;
	if(rs >= MAX_DEEP) {
		--rs;
		push_back(leaf, TEMP);
		return;
	}

	handler_seq(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
	--rs;
}

void handler(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "catch ( exception_declaration ) compound_statement");
	new_leaf.clear();
	push_back(new_leaf, CATCH);
	push_back(new_leaf, L_PARENTHESIS);
	exception_declaration(tab + 2, new_leaf);
	push_back(new_leaf, R_PARENTHESIS);
	compound_statement(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void exception_declaration(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "attribute_specifier_seq opt type_specifier_seq declarator");
	new_leaf.clear();
	attribute_specifier_seq(tab + 2, new_leaf);
	type_specifier_seq(tab + 2, new_leaf);
	declarator(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "attribute_specifier_seq opt type_specifier_seq abstract_declarator opt");
	new_leaf.clear();
	attribute_specifier_seq(tab + 2, new_leaf);
	type_specifier_seq(tab + 2, new_leaf);
	abstract_declarator(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "...");
	new_leaf.clear();
	push_back(new_leaf, ELLIPSIS);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void exception_specification(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "dynamic_exception_specification");
	new_leaf.clear();
	dynamic_exception_specification(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "noexcept_specification");
	new_leaf.clear();
	noexcept_specification(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void dynamic_exception_specification(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "throw ( type_id_list opt )");
	new_leaf.clear();
	push_back(new_leaf, THROW);
	push_back(new_leaf, L_PARENTHESIS);
	type_id_list(tab + 2, new_leaf);
	push_back(new_leaf, R_PARENTHESIS);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void type_id_list(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "type_id ... opt");
	new_leaf.clear();
	type_id(tab + 2, new_leaf);
	push_back(new_leaf, ELLIPSIS, true);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "type_id_list , type_id ... opt");
	new_leaf.clear();

	static int rs = 0;
	++rs;
	if(rs >= MAX_DEEP) {
		--rs;
		push_back(leaf, TEMP);
		return;
	}

	type_id_list(tab + 2, new_leaf);
	push_back(new_leaf, COMMA);
	type_id(tab + 2, new_leaf);
	push_back(new_leaf, ELLIPSIS, true);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
	--rs;
}

void noexcept_specification(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "noexcept ( constant_expression )");
	new_leaf.clear();
	push_back(new_leaf, NOEXCEPT);
	push_back(new_leaf, L_PARENTHESIS);
	constant_expression(tab + 2, new_leaf);
	push_back(new_leaf, R_PARENTHESIS);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "noexcept");
	new_leaf.clear();
	push_back(new_leaf, NOEXCEPT);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}


void abstract_declarator(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

void attribute_specifier_seq(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

void compound_statement(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

void constant_expression(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

void ctor_initializer(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

void declarator(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

void type_id(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

void type_specifier_seq(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}
