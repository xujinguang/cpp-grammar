#include "public.h"
#include "expression.h"

void primary_expression(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "literal");
	new_leaf.clear();
	push_back(new_leaf, LITERAL);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "this");
	new_leaf.clear();
	push_back(new_leaf, THIS);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "( expression )");
	new_leaf.clear();
	push_back(new_leaf, L_PARENTHESIS);
	expression(tab + 2, new_leaf);
	push_back(new_leaf, R_PARENTHESIS);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "id_expression");
	new_leaf.clear();
	id_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "lambda_expression");
	new_leaf.clear();
	lambda_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "fold_expression");
	new_leaf.clear();
	fold_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void id_expression(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "unqualified_id");
	new_leaf.clear();
	unqualified_id(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "qualified_id");
	new_leaf.clear();
	qualified_id(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void unqualified_id(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "ID");
	new_leaf.clear();
	push_back(new_leaf, ID);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "operator_function_id");
	new_leaf.clear();
	operator_function_id(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "conversion_function_id");
	new_leaf.clear();
	conversion_function_id(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "literal_operator_id");
	new_leaf.clear();
	literal_operator_id(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "~ class_name");
	new_leaf.clear();
	push_back(new_leaf, INVERT);
	class_name(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "~ decltype_specifier");
	new_leaf.clear();
	push_back(new_leaf, INVERT);
	decltype_specifier(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "template_id");
	new_leaf.clear();
	template_id(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void qualified_id(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "nested_name_specifier template opt unqualified_id");
	new_leaf.clear();
	nested_name_specifier(tab + 2, new_leaf, OTHER);
	push_back(new_leaf, TEMPLATE, true);
	unqualified_id(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void nested_name_specifier(int tab, leaf_t &leaf, int source)
{
	static int rs[3] = {0};
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "::");
	new_leaf.clear();
	push_back(new_leaf, D_COLON);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "type_name ::");
	new_leaf.clear();
	type_name(tab + 2, new_leaf);
	push_back(new_leaf, D_COLON);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "namespace_name ::");
	new_leaf.clear();
	namespace_name(tab + 2, new_leaf);
	push_back(new_leaf, D_COLON);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "decltype_specifier ::");
	new_leaf.clear();
	decltype_specifier(tab + 2, new_leaf);
	push_back(new_leaf, D_COLON);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "nested_name_specifier ID ::");
	new_leaf.clear();

	++rs[source];
	if(rs[source] >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	nested_name_specifier(tab + 2, new_leaf, FIRST);
	push_back(new_leaf, ID);
	push_back(new_leaf, D_COLON);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "nested_name_specifier template opt simple_template_id ::");
	new_leaf.clear();

	++rs[source];
	if(rs[source] >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	nested_name_specifier(tab + 2, new_leaf, SECOND);
	push_back(new_leaf, TEMPLATE, true);
	simple_template_id(tab + 2, new_leaf);
	push_back(new_leaf, D_COLON);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
	--rs[source];
}

void lambda_expression(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "lambda_introducer lambda_declarator opt compound_statement");
	new_leaf.clear();
	lambda_introducer(tab + 2, new_leaf);
	lambda_declarator(tab + 2, new_leaf);
	compound_statement(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void lambda_introducer(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "[ lambda_capture opt ]");
	new_leaf.clear();
	push_back(new_leaf, L_BRACKET);
	lambda_capture(tab + 2, new_leaf);
	push_back(new_leaf, R_BRACKET);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void lambda_capture(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "capture_default");
	new_leaf.clear();
	capture_default(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "capture_list");
	new_leaf.clear();
	capture_list(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "capture_default , capture_list");
	new_leaf.clear();
	capture_default(tab + 2, new_leaf);
	push_back(new_leaf, COMMA);
	capture_list(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void capture_default(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "&=");
	new_leaf.clear();
	push_back(new_leaf, C_AND);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void capture_list(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "capture ... opt");
	new_leaf.clear();
	capture(tab + 2, new_leaf);
	push_back(new_leaf, ELLIPSIS, true);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "capture_list , capture ... opt");
	new_leaf.clear();

	static int rs = 0;
	++rs;
	if(rs >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	capture_list(tab + 2, new_leaf);
	push_back(new_leaf, COMMA);
	capture(tab + 2, new_leaf);
	push_back(new_leaf, ELLIPSIS, true);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
	--rs;
}

void capture(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "simple_capture");
	new_leaf.clear();
	simple_capture(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "init_capture");
	new_leaf.clear();
	init_capture(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void simple_capture(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "ID");
	new_leaf.clear();
	push_back(new_leaf, ID);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "& ID");
	new_leaf.clear();
	push_back(new_leaf, AND);
	push_back(new_leaf, ID);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "this");
	new_leaf.clear();
	push_back(new_leaf, THIS);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void init_capture(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "ID initializer");
	new_leaf.clear();
	push_back(new_leaf, ID);
	initializer(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "& ID initializer");
	new_leaf.clear();
	push_back(new_leaf, AND);
	push_back(new_leaf, ID);
	initializer(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void lambda_declarator(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "( parameter_declaration_clause ) mutable opt");
	new_leaf.clear();
	push_back(new_leaf, L_PARENTHESIS);
	parameter_declaration_clause(tab + 2, new_leaf);
	push_back(new_leaf, R_PARENTHESIS);
	push_back(new_leaf, MUTABLE, true);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "exception_specification opt attribute_specifier_seq opt trailing_return_type opt");
	new_leaf.clear();
	exception_specification(tab + 2, new_leaf);
	attribute_specifier_seq(tab + 2, new_leaf);
	trailing_return_type(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void fold_expression(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "( cast_expression fold_operator ... )");
	new_leaf.clear();
	push_back(new_leaf, L_PARENTHESIS);
	cast_expression(tab + 2, new_leaf);
	fold_operator(tab + 2, new_leaf);
	push_back(new_leaf, ELLIPSIS);
	push_back(new_leaf, R_PARENTHESIS);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "( ... fold_operator cast_expression )");
	new_leaf.clear();
	push_back(new_leaf, L_PARENTHESIS);
	push_back(new_leaf, ELLIPSIS);
	fold_operator(tab + 2, new_leaf);
	cast_expression(tab + 2, new_leaf);
	push_back(new_leaf, R_PARENTHESIS);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "( cast_expression fold_operator ... fold_operator cast_expression )");
	new_leaf.clear();
	push_back(new_leaf, L_PARENTHESIS);
	cast_expression(tab + 2, new_leaf);
	fold_operator(tab + 2, new_leaf);
	push_back(new_leaf, ELLIPSIS);
	fold_operator(tab + 2, new_leaf);
	cast_expression(tab + 2, new_leaf);
	push_back(new_leaf, R_PARENTHESIS);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void fold_operator(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "+");
	new_leaf.clear();
	push_back(new_leaf, ADD);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "-");
	new_leaf.clear();
	push_back(new_leaf, MINUS);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "*");
	new_leaf.clear();
	push_back(new_leaf, ASTERISK);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "/");
	new_leaf.clear();
	push_back(new_leaf, DIV);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "%");
	new_leaf.clear();
	push_back(new_leaf, MOD);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "^");
	new_leaf.clear();
	push_back(new_leaf, XOR);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "&");
	new_leaf.clear();
	push_back(new_leaf, AND);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "|");
	new_leaf.clear();
	push_back(new_leaf, OR);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "<<");
	new_leaf.clear();
	push_back(new_leaf, LSHIFT);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, ">>");
	new_leaf.clear();
	push_back(new_leaf, RSHIFT);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "+=");
	new_leaf.clear();
	push_back(new_leaf, C_ADD);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "-=");
	new_leaf.clear();
	push_back(new_leaf, C_MINUS);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "*=");
	new_leaf.clear();
	push_back(new_leaf, C_MUL);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "/=");
	new_leaf.clear();
	push_back(new_leaf, C_DIV);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "%=");
	new_leaf.clear();
	push_back(new_leaf, C_MOD);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "^=");
	new_leaf.clear();
	push_back(new_leaf, C_XOR);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "&=");
	new_leaf.clear();
	push_back(new_leaf, C_AND);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "|=");
	new_leaf.clear();
	push_back(new_leaf, C_OR);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "<<=");
	new_leaf.clear();
	push_back(new_leaf, C_LSHIFT);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, ">>=");
	new_leaf.clear();
	push_back(new_leaf, C_RSHIFT);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "=");
	new_leaf.clear();
	push_back(new_leaf, ASSIGN);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "==");
	new_leaf.clear();
	push_back(new_leaf, EQUAL);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "!=");
	new_leaf.clear();
	push_back(new_leaf, NOT_EQUAL);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "<");
	new_leaf.clear();
	push_back(new_leaf, LESS);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, ">");
	new_leaf.clear();
	push_back(new_leaf, GREATER);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "<=");
	new_leaf.clear();
	push_back(new_leaf, LESS_EQUAL);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, ">=");
	new_leaf.clear();
	push_back(new_leaf, GREATER_EQUAL);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "&&");
	new_leaf.clear();
	push_back(new_leaf, LAND);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "||");
	new_leaf.clear();
	push_back(new_leaf, LOR);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, ",");
	new_leaf.clear();
	push_back(new_leaf, COMMA);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, ".*");
	new_leaf.clear();
	push_back(new_leaf, DOT_ASTERISK);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "->*");
	new_leaf.clear();
	push_back(new_leaf, ARROW_ASTERISK);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void postfix_expression(int tab, leaf_t &leaf, int source)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "primary_expression");
	new_leaf.clear();
	primary_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "simple_type_specifier ( expression_list opt )");
	new_leaf.clear();
	simple_type_specifier(tab + 2, new_leaf);
	push_back(new_leaf, L_PARENTHESIS);
	expression_list(tab + 2, new_leaf);
	push_back(new_leaf, R_PARENTHESIS);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "typename_specifier ( expression_list opt )");
	new_leaf.clear();
	typename_specifier(tab + 2, new_leaf);
	push_back(new_leaf, L_PARENTHESIS);
	expression_list(tab + 2, new_leaf);
	push_back(new_leaf, R_PARENTHESIS);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "simple_type_specifier braced_init_list");
	new_leaf.clear();
	simple_type_specifier(tab + 2, new_leaf);
	braced_init_list(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "typename_specifier braced_init_list");
	new_leaf.clear();
	typename_specifier(tab + 2, new_leaf);
	braced_init_list(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "dynamic_cast < type_id > ( expression )");
	new_leaf.clear();
	push_back(new_leaf, DYNAMIC_CAST);
	push_back(new_leaf, LESS);
	type_id(tab + 2, new_leaf);
	push_back(new_leaf, GREATER);
	push_back(new_leaf, L_PARENTHESIS);
	expression(tab + 2, new_leaf);
	push_back(new_leaf, R_PARENTHESIS);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "static_cast < type_id > ( expression )");
	new_leaf.clear();
	push_back(new_leaf, STATIC_CAST);
	push_back(new_leaf, LESS);
	type_id(tab + 2, new_leaf);
	push_back(new_leaf, GREATER);
	push_back(new_leaf, L_PARENTHESIS);
	expression(tab + 2, new_leaf);
	push_back(new_leaf, R_PARENTHESIS);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "reinterpret_cast < type_id > ( expression )");
	new_leaf.clear();
	push_back(new_leaf, REINTERPRET_CAST);
	push_back(new_leaf, LESS);
	type_id(tab + 2, new_leaf);
	push_back(new_leaf, GREATER);
	push_back(new_leaf, L_PARENTHESIS);
	expression(tab + 2, new_leaf);
	push_back(new_leaf, R_PARENTHESIS);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "const_cast < type_id > ( expression )");
	new_leaf.clear();
	push_back(new_leaf, CONST_CAST);
	push_back(new_leaf, LESS);
	type_id(tab + 2, new_leaf);
	push_back(new_leaf, GREATER);
	push_back(new_leaf, L_PARENTHESIS);
	expression(tab + 2, new_leaf);
	push_back(new_leaf, R_PARENTHESIS);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "typeid ( expression )");
	new_leaf.clear();
	push_back(new_leaf, TYPEID);
	push_back(new_leaf, L_PARENTHESIS);
	expression(tab + 2, new_leaf);
	push_back(new_leaf, R_PARENTHESIS);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "typeid ( type_id )");
	new_leaf.clear();
	push_back(new_leaf, TYPEID);
	push_back(new_leaf, L_PARENTHESIS);
	type_id(tab + 2, new_leaf);
	push_back(new_leaf, R_PARENTHESIS);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "postfix_expression [ expression ]");
	new_leaf.clear();

	static int rs[16] = {0};
	++rs[source];
	if(rs[source] >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	postfix_expression(tab + 2, new_leaf, 0);
	push_back(new_leaf, L_BRACKET);
	expression(tab + 2, new_leaf);
	push_back(new_leaf, R_BRACKET);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "postfix_expression [ braced_init_list ]");
	new_leaf.clear();

	++rs[source];
	if(rs[source] >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	postfix_expression(tab + 2, new_leaf, 1);
	push_back(new_leaf, L_BRACKET);
	braced_init_list(tab + 2, new_leaf);
	push_back(new_leaf, R_BRACKET);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "postfix_expression ( expression_list opt )");
	new_leaf.clear();

	++rs[source];
	if(rs[source] >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	postfix_expression(tab + 2, new_leaf, 2);
	push_back(new_leaf, L_PARENTHESIS);
	expression_list(tab + 2, new_leaf);
	push_back(new_leaf, R_PARENTHESIS);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "postfix_expression . template opt id_expression");
	new_leaf.clear();

	++rs[source];
	if(rs[source] >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	postfix_expression(tab + 2, new_leaf, 3);
	push_back(new_leaf, DOT);
	push_back(new_leaf, TEMPLATE, true);
	id_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "postfix_expression -> template opt id_expression");
	new_leaf.clear();

	++rs[source];
	if(rs[source] >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	postfix_expression(tab + 2, new_leaf, 4);
	push_back(new_leaf, ARROW);
	push_back(new_leaf, TEMPLATE, true);
	id_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "postfix_expression . pseudo_destructor_name");
	new_leaf.clear();

	++rs[source];
	if(rs[source] >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	postfix_expression(tab + 2, new_leaf, 5);
	push_back(new_leaf, DOT);
	pseudo_destructor_name(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "postfix_expression -> pseudo_destructor_name");
	new_leaf.clear();

	++rs[source];
	if(rs[source] >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	postfix_expression(tab + 2, new_leaf, 6);
	push_back(new_leaf, ARROW);
	pseudo_destructor_name(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "postfix_expression ++");
	new_leaf.clear();

	++rs[source];
	if(rs[source] >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	postfix_expression(tab + 2, new_leaf, 7);
	push_back(new_leaf, INC);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "postfix_expression -- ");
	new_leaf.clear();

	++rs[source];
	if(rs[source] >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}
	
	postfix_expression(tab + 2, new_leaf, 8);
	push_back(new_leaf, DEC);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
	--rs[source];
}

void expression_list(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "initializer_list");
	new_leaf.clear();
	initializer_list(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void pseudo_destructor_name(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "nested_name_specifier opt type_name :: ~ type_name");
	new_leaf.clear();
	nested_name_specifier(tab + 2, new_leaf, OTHER);
	type_name(tab + 2, new_leaf);
	push_back(new_leaf, D_COLON);
	push_back(new_leaf, INVERT);
	type_name(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "nested_name_specifier template simple_template_id :: ~ type_name");
	new_leaf.clear();
	nested_name_specifier(tab + 2, new_leaf, OTHER);
	push_back(new_leaf, TEMPLATE);
	simple_template_id(tab + 2, new_leaf);
	push_back(new_leaf, D_COLON);
	push_back(new_leaf, INVERT);
	type_name(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "~ type_name");
	new_leaf.clear();
	push_back(new_leaf, INVERT);
	type_name(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "~ decltype_specifier");
	new_leaf.clear();
	push_back(new_leaf, INVERT);
	decltype_specifier(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void unary_expression(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "postfix_expression");
	new_leaf.clear();
	postfix_expression(tab + 2, new_leaf, 10);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "++ cast_expression");
	new_leaf.clear();
	push_back(new_leaf, INC);
	cast_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "-- cast_expression");
	new_leaf.clear();
	push_back(new_leaf, DEC);
	cast_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "unary_operator cast_expression");
	new_leaf.clear();
	unary_operator(tab + 2, new_leaf);
	cast_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "sizeof ( type_id )");
	new_leaf.clear();
	push_back(new_leaf, SIZEOF);
	push_back(new_leaf, L_PARENTHESIS);
	type_id(tab + 2, new_leaf);
	push_back(new_leaf, R_PARENTHESIS);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "sizeof ... ( ID )");
	new_leaf.clear();
	push_back(new_leaf, SIZEOF);
	push_back(new_leaf, ELLIPSIS);
	push_back(new_leaf, L_PARENTHESIS);
	push_back(new_leaf, ID);
	push_back(new_leaf, R_PARENTHESIS);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "alignof ( type_id )");
	new_leaf.clear();
	push_back(new_leaf, ALIGNOF);
	push_back(new_leaf, L_PARENTHESIS);
	type_id(tab + 2, new_leaf);
	push_back(new_leaf, R_PARENTHESIS);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "noexcept_expression");
	new_leaf.clear();
	noexcept_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "new_expression");
	new_leaf.clear();
	new_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "delete_expression");
	new_leaf.clear();
	delete_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "sizeof unary_expression");
	new_leaf.clear();
	push_back(new_leaf, SIZEOF);

	static int rs = 0;
	++rs;
	if(rs >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	unary_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
	--rs;
}

void unary_operator(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "*");
	new_leaf.clear();
	push_back(new_leaf, ASTERISK);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "&");
	new_leaf.clear();
	push_back(new_leaf, AND);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "+");
	new_leaf.clear();
	push_back(new_leaf, ADD);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "-");
	new_leaf.clear();
	push_back(new_leaf, MINUS);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "!");
	new_leaf.clear();
	push_back(new_leaf, NOT);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "~");
	new_leaf.clear();
	push_back(new_leaf, INVERT);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void new_expression(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, ":: opt new new_placement opt new_type_id new_initializer opt");
	new_leaf.clear();
	push_back(new_leaf, D_COLON, true);
	push_back(new_leaf, NEW);
	new_placement(tab + 2, new_leaf);
	new_type_id(tab + 2, new_leaf);
	new_initializer(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, ":: opt new new_placement opt ( type_id ) new_initializer opt");
	new_leaf.clear();
	push_back(new_leaf, D_COLON, true);
	push_back(new_leaf, NEW);
	new_placement(tab + 2, new_leaf);
	push_back(new_leaf, L_PARENTHESIS);
	type_id(tab + 2, new_leaf);
	push_back(new_leaf, R_PARENTHESIS);
	new_initializer(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void new_placement(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "( expression_list )");
	new_leaf.clear();
	push_back(new_leaf, L_PARENTHESIS);
	expression_list(tab + 2, new_leaf);
	push_back(new_leaf, R_PARENTHESIS);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void new_type_id(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "type_specifier_seq");
	new_leaf.clear();
	type_specifier_seq(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "type_specifier_seq new_declarator");
	new_leaf.clear();
	type_specifier_seq(tab + 2, new_leaf);
	new_declarator(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void new_declarator(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "ptr_operator new_declarator opt");
	new_leaf.clear();
	ptr_operator(tab + 2, new_leaf);

	static int rs = 0;
	++rs;
	if(rs >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	new_declarator(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "noptr_new_declarator");
	new_leaf.clear();
	noptr_new_declarator(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
	--rs;
}

void noptr_new_declarator(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "[ expression ] attribute_specifier_seq opt");
	new_leaf.clear();
	push_back(new_leaf, L_BRACKET);
	expression(tab + 2, new_leaf);
	push_back(new_leaf, R_BRACKET);
	attribute_specifier_seq(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "noptr_new_declarator [ constant_expression ] attribute_specifier_seq opt");
	new_leaf.clear();

	static int rs = 0;
	++rs;
	if(rs >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	noptr_new_declarator(tab + 2, new_leaf);
	push_back(new_leaf, L_BRACKET);
	constant_expression(tab + 2, new_leaf);
	push_back(new_leaf, R_BRACKET);
	attribute_specifier_seq(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
	--rs;
}

void new_initializer(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "( expression_list opt )");
	new_leaf.clear();
	push_back(new_leaf, L_PARENTHESIS);
	expression_list(tab + 2, new_leaf);
	push_back(new_leaf, R_PARENTHESIS);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "braced_init_list");
	new_leaf.clear();
	braced_init_list(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void delete_expression(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, ":: opt delete cast_expression");
	new_leaf.clear();
	push_back(new_leaf, D_COLON, true);
	push_back(new_leaf, DELETE);
	cast_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, ":: opt delete [ ] cast_expression");
	new_leaf.clear();
	push_back(new_leaf, D_COLON, true);
	push_back(new_leaf, DELETE);
	push_back(new_leaf, L_BRACKET);
	push_back(new_leaf, R_BRACKET);
	cast_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void noexcept_expression(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "noexcept ( expression )");
	new_leaf.clear();
	push_back(new_leaf, NOEXCEPT);
	push_back(new_leaf, L_PARENTHESIS);
	expression(tab + 2, new_leaf);
	push_back(new_leaf, R_PARENTHESIS);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void cast_expression(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "unary_expression");
	new_leaf.clear();
	unary_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "( type_id ) cast_expression");
	new_leaf.clear();
	push_back(new_leaf, L_PARENTHESIS);
	type_id(tab + 2, new_leaf);
	push_back(new_leaf, R_PARENTHESIS);

	static int rs = 0;
	++rs;
	if(rs >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	cast_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
	--rs;
}

void pm_expression(int tab, leaf_t &leaf, int source)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "cast_expression");
	new_leaf.clear();
	cast_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "pm_expression .* cast_expression");
	new_leaf.clear();

	static int rs[4] = {0};
	++rs[source];
	if(rs[source] >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	pm_expression(tab + 2, new_leaf, 1);
	push_back(new_leaf, DOT_ASTERISK);
	cast_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "pm_expression ->* cast_expression");
	new_leaf.clear();

	++rs[source];
	if(rs[source] >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	pm_expression(tab + 2, new_leaf, 2);
	push_back(new_leaf, ARROW_ASTERISK);
	cast_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
	--rs[source];
}

void multiplicative_expression(int tab, leaf_t &leaf, int source)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "pm_expression");
	new_leaf.clear();
	pm_expression(tab + 2, new_leaf, 0);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "multiplicative_expression * pm_expression");
	new_leaf.clear();

	static int rs[8] = {0};
	++rs[source];
	if(rs[source] >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	multiplicative_expression(tab + 2, new_leaf, 1);
	push_back(new_leaf, ASTERISK);
	pm_expression(tab + 2, new_leaf, 0);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "multiplicative_expression / pm_expression");
	new_leaf.clear();

	++rs[source];
	if(rs[source] >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	multiplicative_expression(tab + 2, new_leaf, 2);
	push_back(new_leaf, DIV);
	pm_expression(tab + 2, new_leaf, 0);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "multiplicative_expression % pm_expression");
	new_leaf.clear();

	++rs[source];
	if(rs[source] >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	multiplicative_expression(tab + 2, new_leaf, 3);
	push_back(new_leaf, MOD);
	pm_expression(tab + 2, new_leaf, 0);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
	--rs[source];
}

void additive_expression(int tab, leaf_t &leaf, int source)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "multiplicative_expression");
	new_leaf.clear();
	multiplicative_expression(tab + 2, new_leaf, 0);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "additive_expression + multiplicative_expression");
	new_leaf.clear();

	static int rs[4] = {0};
	++rs[source];
	if(rs[source] >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	additive_expression(tab + 2, new_leaf, 1);
	push_back(new_leaf, ADD);
	multiplicative_expression(tab + 2, new_leaf, 0);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "additive_expression - multiplicative_expression");
	new_leaf.clear();

	++rs[source];
	if(rs[source] >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	additive_expression(tab + 2, new_leaf, 2);
	push_back(new_leaf, MINUS);
	multiplicative_expression(tab + 2, new_leaf, 0);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
	--rs[source];
}

void shift_expression(int tab, leaf_t &leaf, int source)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "additive_expression");
	new_leaf.clear();
	additive_expression(tab + 2, new_leaf, 0);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "shift_expression << additive_expression");
	new_leaf.clear();

	static int rs[4] = {0};

	++rs[source];
	if(rs[source] >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	shift_expression(tab + 2, new_leaf, 1);
	push_back(new_leaf, LSHIFT);
	additive_expression(tab + 2, new_leaf, 0);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "shift_expression >> additive_expression");
	new_leaf.clear();

	++rs[source];
	if(rs[source] >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	shift_expression(tab + 2, new_leaf, 2);
	push_back(new_leaf, RSHIFT);
	additive_expression(tab + 2, new_leaf, 0);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
	--rs[source];
}

void relational_expression(int tab, leaf_t &leaf, int source)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "shift_expression");
	new_leaf.clear();
	shift_expression(tab + 2, new_leaf, 0);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "relational_expression < shift_expression");
	new_leaf.clear();

	static int rs[8] = {0};
	++rs[source];
	if(rs[source] >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	relational_expression(tab + 2, new_leaf, 1);
	push_back(new_leaf, LESS);
	shift_expression(tab + 2, new_leaf, 0);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "relational_expression > shift_expression");
	new_leaf.clear();

	++rs[source];
	if(rs[source] >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	relational_expression(tab + 2, new_leaf, 2);
	push_back(new_leaf, GREATER);
	shift_expression(tab + 2, new_leaf, 0);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "relational_expression <= shift_expression");
	new_leaf.clear();

	++rs[source];
	if(rs[source] >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	relational_expression(tab + 2, new_leaf, 3);
	push_back(new_leaf, LESS_EQUAL);
	shift_expression(tab + 2, new_leaf, 0);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "relational_expression >= shift_expression");
	new_leaf.clear();

	++rs[source];
	if(rs[source] >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	relational_expression(tab + 2, new_leaf, 4);
	push_back(new_leaf, GREATER_EQUAL);
	shift_expression(tab + 2, new_leaf, 0);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
	--rs[source];
}

void equality_expression(int tab, leaf_t &leaf, int source)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "relational_expression");
	new_leaf.clear();
	relational_expression(tab + 2, new_leaf, 0);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "equality_expression == relational_expression");
	new_leaf.clear();

	static int rs[4] = {0};
	++rs[source];
	if(rs[source] >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	equality_expression(tab + 2, new_leaf, 1);
	push_back(new_leaf, EQUAL);
	relational_expression(tab + 2, new_leaf, 0);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "equality_expression != relational_expression");
	new_leaf.clear();

	++rs[source];
	if(rs[source] >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	equality_expression(tab + 2, new_leaf, 2);
	push_back(new_leaf, NOT_EQUAL);
	relational_expression(tab + 2, new_leaf, 0);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
	--rs[source];
}

void and_expression(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "equality_expression");
	new_leaf.clear();
	equality_expression(tab + 2, new_leaf, 0);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "and_expression & equality_expression");
	new_leaf.clear();

	static int rs = 0;
	++rs;
	if(rs >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	and_expression(tab + 2, new_leaf);
	push_back(new_leaf, AND);
	equality_expression(tab + 2, new_leaf, 0);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
	--rs;
}

void exclusive_or_expression(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "and_expression");
	new_leaf.clear();
	and_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "exclusive_or_expression ^ and_expression");
	new_leaf.clear();

	static int rs = 0;
	++rs;
	if(rs >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	exclusive_or_expression(tab + 2, new_leaf);
	push_back(new_leaf, XOR);
	and_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
	--rs;
}

void inclusive_or_expression(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "exclusive_or_expression");
	new_leaf.clear();
	exclusive_or_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "inclusive_or_expression | exclusive_or_expression");
	new_leaf.clear();

	static int rs = 0;
	++rs;
	if(rs >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	inclusive_or_expression(tab + 2, new_leaf);
	push_back(new_leaf, OR);
	exclusive_or_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
	--rs;
}

void logical_and_expression(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "inclusive_or_expression");
	new_leaf.clear();
	inclusive_or_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "logical_and_expression && inclusive_or_expression");
	new_leaf.clear();

	static int rs = 0;
	++rs;
	if(rs >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	logical_and_expression(tab + 2, new_leaf);
	push_back(new_leaf, LAND);
	inclusive_or_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
	--rs;
}

void logical_or_expression(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "logical_and_expression");
	new_leaf.clear();
	logical_and_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "logical_or_expression || logical_and_expression");
	new_leaf.clear();

	static int rs = 0;
	++rs;
	if(rs >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	logical_or_expression(tab + 2, new_leaf);
	push_back(new_leaf, LOR);
	logical_and_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
	--rs;
}

void conditional_expression(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "logical_or_expression");
	new_leaf.clear();
	logical_or_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "logical_or_expression ? expression : assignment_expression");
	new_leaf.clear();
	logical_or_expression(tab + 2, new_leaf);
	push_back(new_leaf, QUESTION);
	expression(tab + 2, new_leaf);
	push_back(new_leaf, COLON);
	assignment_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void throw_expression(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "throw assignment_expression opt");
	new_leaf.clear();
	push_back(new_leaf, THROW);
	assignment_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void assignment_expression(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "conditional_expression");
	new_leaf.clear();
	conditional_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "logical_or_expression assignment_operator initializer_clause");
	new_leaf.clear();
	logical_or_expression(tab + 2, new_leaf);
	assignment_operator(tab + 2, new_leaf);
	initializer_clause(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "throw_expression");
	new_leaf.clear();
	throw_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void assignment_operator(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "=");
	new_leaf.clear();
	push_back(new_leaf, ASSIGN);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "*=");
	new_leaf.clear();
	push_back(new_leaf, C_MUL);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "/=");
	new_leaf.clear();
	push_back(new_leaf, C_DIV);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "%=");
	new_leaf.clear();
	push_back(new_leaf, C_MOD);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "+=");
	new_leaf.clear();
	push_back(new_leaf, C_ADD);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "-=");
	new_leaf.clear();
	push_back(new_leaf, C_MINUS);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, ">>=");
	new_leaf.clear();
	push_back(new_leaf, C_RSHIFT);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "<<=");
	new_leaf.clear();
	push_back(new_leaf, C_LSHIFT);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "&=");
	new_leaf.clear();
	push_back(new_leaf, C_AND);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "^=");
	new_leaf.clear();
	push_back(new_leaf, C_XOR);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "|=");
	new_leaf.clear();
	push_back(new_leaf, C_OR);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

static void expression(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "assignment_expression");
	new_leaf.clear();
	assignment_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "expression , assignment_expression");
	new_leaf.clear();

	static int rs = 0;
	++rs;
	if(rs >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	expression(tab + 2, new_leaf);
	push_back(new_leaf, COMMA);
	assignment_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
	--rs;
}

static void constant_expression(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "conditional_expression");
	new_leaf.clear();
	conditional_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}




void conversion_function_id(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}


void initializer(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

void initializer_list(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

void literal_operator_id(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}


void operator_function_id(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

void parameter_declaration_clause(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

void ptr_operator(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

void trailing_return_type(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

static void simple_template_id(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

#ifdef EXPRESSION_MODEL
void decltype_specifier(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}
void simple_type_specifier(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

void type_name(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

void class_name(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}
void namespace_name(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}


void template_id(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

void typename_specifier(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

void exception_specification(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

void compound_statement(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

void type_id(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

void initializer_clause(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

void braced_init_list(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

void attribute_specifier_seq(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

void type_specifier_seq(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TEMP);
}

#endif
