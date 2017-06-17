#include "public.h"
#include "template.h"

void template_declaration(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "template < template_parameter_list > declaration");
	new_leaf.clear();
	push_back(new_leaf, TEMPLATE);
	push_back(new_leaf, LESS);
	template_parameter_list(tab + 2, new_leaf);
	push_back(new_leaf, GREATER);
	declaration(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void template_parameter_list(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "template_parameter");
	new_leaf.clear();
	template_parameter(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
/*
 * 这里为里解决递归冲突
 * template_parameter_list->template_parameter_list template_parameter
 * template_parameter_list->template_parameter->type_parameter->template<template_parameter_list>type_parameter_key ... ID
 * 这两个区分不开，单纯限制调用template_parameter_list的词解决不了问题
 * 因此，这里做个折中，让第一个产生式展开一次
	OUTPUT(tab + 1, "template_parameter_list , template_parameter");
	new_leaf.clear();

	static int rs = 0;
	++rs;
	if(rs >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	template_parameter_list(tab + 2, new_leaf);
	push_back(new_leaf, COMMA);
	template_parameter(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);*/
	push_back(leaf, tmp_leaf);
//	--rs;
}

void template_parameter(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "type_parameter");
	new_leaf.clear();
	type_parameter(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "parameter_declaration");
	new_leaf.clear();
	parameter_declaration(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void type_parameter(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	static int rs = 0;
	++rs;
	if(rs >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}
	OUTPUT(tab + 1, "type_parameter_key ... opt ID opt");
	new_leaf.clear();
	type_parameter_key(tab + 2, new_leaf);
	push_back(new_leaf, ELLIPSIS, true);
	push_back(new_leaf, ID, true);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "type_parameter_key ID opt = type_id");
	new_leaf.clear();
	type_parameter_key(tab + 2, new_leaf);
	push_back(new_leaf, ID, true);
	push_back(new_leaf, ASSIGN);
	type_id(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "template < template_parameter_list > type_parameter_key ... opt ID opt");
	new_leaf.clear();
	push_back(new_leaf, TEMPLATE);
	push_back(new_leaf, LESS);
	template_parameter_list(tab + 2, new_leaf);
	push_back(new_leaf, GREATER);
	type_parameter_key(tab + 2, new_leaf);
	push_back(new_leaf, ELLIPSIS, true);
	push_back(new_leaf, ID, true);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "template < template_parameter_list > type_parameter_key ID opt = id_expression");
	new_leaf.clear();
	push_back(new_leaf, TEMPLATE);
	push_back(new_leaf, LESS);
	template_parameter_list(tab + 2, new_leaf);
	push_back(new_leaf, GREATER);
	type_parameter_key(tab + 2, new_leaf);
	push_back(new_leaf, ID, true);
	push_back(new_leaf, ASSIGN);
	id_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
	--rs;
}

void type_parameter_key(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "class");
	new_leaf.clear();
	push_back(new_leaf, CLASS);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "typename");
	new_leaf.clear();
	push_back(new_leaf, TYPENAME);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

static void simple_template_id(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "template_name < template_argument_list opt >");
	new_leaf.clear();
	template_name(tab + 2, new_leaf);
	push_back(new_leaf, LESS);
	template_argument_list(tab + 2, new_leaf);
	push_back(new_leaf, GREATER);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void template_id(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "simple_template_id");
	new_leaf.clear();
	simple_template_id(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "operator_function_id < template_argument_list opt >");
	new_leaf.clear();
	operator_function_id(tab + 2, new_leaf);
	push_back(new_leaf, LESS);
	template_argument_list(tab + 2, new_leaf);
	push_back(new_leaf, GREATER);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "literal_operator_id < template_argument_list opt >");
	new_leaf.clear();
	literal_operator_id(tab + 2, new_leaf);
	push_back(new_leaf, LESS);
	template_argument_list(tab + 2, new_leaf);
	push_back(new_leaf, GREATER);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void template_argument_list(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "template_argument ... opt");
	new_leaf.clear();
	template_argument(tab + 2, new_leaf);
	push_back(new_leaf, ELLIPSIS, true);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "template_argument_list , template_argument ... opt");
	new_leaf.clear();

	static int rs = 0;
	++rs;
	if(rs >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	template_argument_list(tab + 2, new_leaf);
	push_back(new_leaf, COMMA);
	template_argument(tab + 2, new_leaf);
	push_back(new_leaf, ELLIPSIS, true);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
	--rs;
}

void template_argument(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "constant_expression");
	new_leaf.clear();
	constant_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "type_id");
	new_leaf.clear();
	type_id(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "id_expression");
	new_leaf.clear();
	id_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

static void typename_specifier(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "typename nested_name_specifier ID");
	new_leaf.clear();
	push_back(new_leaf, TYPENAME);
	nested_name_specifier(tab + 2, new_leaf);
	push_back(new_leaf, ID);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "typename nested_name_specifier template opt simple_template_id");
	new_leaf.clear();
	push_back(new_leaf, TYPENAME);
	nested_name_specifier(tab + 2, new_leaf);
	push_back(new_leaf, TEMPLATE, true);
	simple_template_id(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void explicit_instantiation(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "extern opt template declaration");
	new_leaf.clear();
	push_back(new_leaf, EXTERN, true);
	push_back(new_leaf, TEMPLATE);
	declaration(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void explicit_specialization(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "template < > declaration");
	new_leaf.clear();
	push_back(new_leaf, TEMPLATE);
	push_back(new_leaf, LESS);
	push_back(new_leaf, GREATER);
	declaration(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void declaration(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}


void parameter_declaration(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

void template_name(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

#ifdef TEMPLATE_MODEL

void nested_name_specifier(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}
void operator_function_id(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

void literal_operator_id(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}
void constant_expression(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

void type_id(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

void id_expression(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

#endif
