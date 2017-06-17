#include "public.h"
#include "decl_specifier_seq.h"

void decl_specifier(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "storage_class_specifier");
	new_leaf.clear();
	storage_class_specifier(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "type_specifier");
	new_leaf.clear();
	type_specifier(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "function_specifier");
	new_leaf.clear();
	function_specifier(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "friend");
	new_leaf.clear();
	push_back(new_leaf, FRIEND);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "typedef");
	new_leaf.clear();
	push_back(new_leaf, TYPEDEF);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "constexpr");
	new_leaf.clear();
	push_back(new_leaf, CONSTEXPR);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void decl_specifier_seq(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "decl_specifier attribute_specifier_seq opt");
	new_leaf.clear();
	decl_specifier(tab + 2, new_leaf);
	attribute_specifier_seq(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "decl_specifier decl_specifier_seq");
	new_leaf.clear();
	decl_specifier(tab + 2, new_leaf);

	static int rs = 0;
	++rs;
	if(rs >= MAX_DEEP) {
		//push_back(leaf, TEMP);
		return;
	}

	decl_specifier_seq(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
	--rs;
}

void storage_class_specifier(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "register");
	new_leaf.clear();
	push_back(new_leaf, REGISTER);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "static");
	new_leaf.clear();
	push_back(new_leaf, STATIC);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "thread_local");
	new_leaf.clear();
	push_back(new_leaf, THREAD_LOCAL);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "extern");
	new_leaf.clear();
	push_back(new_leaf, EXTERN);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "mutable");
	new_leaf.clear();
	push_back(new_leaf, MUTABLE);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void function_specifier(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "inline");
	new_leaf.clear();
	push_back(new_leaf, INLINE);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "virtual");
	new_leaf.clear();
	push_back(new_leaf, VIRTUAL);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "explicit");
	new_leaf.clear();
	push_back(new_leaf, EXPLICIT);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void type_specifier(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "trailing_type_specifier");
	new_leaf.clear();
	trailing_type_specifier(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "class_specifier");
	new_leaf.clear();
	class_specifier(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "enum_specifier");
	new_leaf.clear();
	enum_specifier(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void trailing_type_specifier(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "simple_type_specifier");
	new_leaf.clear();
	simple_type_specifier(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "elaborated_type_specifier");
	new_leaf.clear();
	elaborated_type_specifier(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "typename_specifier");
	new_leaf.clear();
	typename_specifier(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "cv_qualifier");
	new_leaf.clear();
	cv_qualifier(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void cv_qualifier(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "const");
	new_leaf.clear();
	push_back(new_leaf, CONST);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "volatile");
	new_leaf.clear();
	push_back(new_leaf, VOLATILE);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void type_specifier_seq(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TYPE_SPECIFIER_SEQ);
    return;
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "type_specifier attribute_specifier_seq opt");
	new_leaf.clear();
	type_specifier(tab + 2, new_leaf);
	attribute_specifier_seq(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "type_specifier type_specifier_seq");
	new_leaf.clear();
	type_specifier(tab + 2, new_leaf);

	static int rs = 0;
	++rs;
	if(rs >= MAX_DEEP) {
		push_back(leaf, TEMP);
		return;
	}

	type_specifier_seq(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
	--rs;
}

void trailing_type_specifier_seq(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "trailing_type_specifier attribute_specifier_seq opt");
	new_leaf.clear();
	trailing_type_specifier(tab + 2, new_leaf);
	attribute_specifier_seq(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "trailing_type_specifier trailing_type_specifier_seq");
	new_leaf.clear();
	trailing_type_specifier(tab + 2, new_leaf);

	static int rs = 0;
	++rs;
	if(rs >= MAX_DEEP) {
		//push_back(leaf, TEMP);
		return;
	}

	trailing_type_specifier_seq(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
	--rs;
}

void simple_type_specifier(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "nested_name_specifier opt type_name");
	new_leaf.clear();
	nested_name_specifier(tab + 2, new_leaf);
	type_name(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "nested_name_specifier template simple_template_id");
	new_leaf.clear();
	nested_name_specifier(tab + 2, new_leaf);
	push_back(new_leaf, TEMPLATE);
	simple_template_id(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "char");
	new_leaf.clear();
	push_back(new_leaf, CHAR);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "char16_t");
	new_leaf.clear();
	push_back(new_leaf, CHAR16_T);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "char32_t");
	new_leaf.clear();
	push_back(new_leaf, CHAR32_T);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "wchar_t");
	new_leaf.clear();
	push_back(new_leaf, WCHAR_T);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "bool");
	new_leaf.clear();
	push_back(new_leaf, BOOL);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "short");
	new_leaf.clear();
	push_back(new_leaf, SHORT);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "int");
	new_leaf.clear();
	push_back(new_leaf, INT);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "long");
	new_leaf.clear();
	push_back(new_leaf, LONG);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "signed");
	new_leaf.clear();
	push_back(new_leaf, SIGNED);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "unsigned");
	new_leaf.clear();
	push_back(new_leaf, UNSIGNED);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "float");
	new_leaf.clear();
	push_back(new_leaf, FLOAT);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "double");
	new_leaf.clear();
	push_back(new_leaf, DOUBLE);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "void");
	new_leaf.clear();
	push_back(new_leaf, VOID);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "auto");
	new_leaf.clear();
	push_back(new_leaf, AUTO);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "decltype_specifier");
	new_leaf.clear();
	decltype_specifier(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void type_name(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "class_name");
	new_leaf.clear();
	class_name(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "enum_name");
	new_leaf.clear();
	enum_name(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "typedef_name");
	new_leaf.clear();
	typedef_name(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "simple_template_id");
	new_leaf.clear();
	simple_template_id(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void class_name(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "ID");
	new_leaf.clear();
	push_back(new_leaf, ID);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void enum_name(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "ID");
	new_leaf.clear();
	push_back(new_leaf, ID);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void typedef_name(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "ID");
	new_leaf.clear();
	push_back(new_leaf, ID);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void decltype_specifier(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "decltype ( expression )");
	new_leaf.clear();
	push_back(new_leaf, DECLTYPE);
	push_back(new_leaf, L_PARENTHESIS);
	expression(tab + 2, new_leaf);
	push_back(new_leaf, R_PARENTHESIS);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "decltype ( auto )");
	new_leaf.clear();
	push_back(new_leaf, DECLTYPE);
	push_back(new_leaf, L_PARENTHESIS);
	push_back(new_leaf, AUTO);
	push_back(new_leaf, R_PARENTHESIS);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void elaborated_type_specifier(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "class_key attribute_specifier_seq opt nested_name_specifier opt ID");
	new_leaf.clear();
	class_key(tab + 2, new_leaf);
	attribute_specifier_seq(tab + 2, new_leaf);
	nested_name_specifier(tab + 2, new_leaf);
	push_back(new_leaf, ID);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "class_key simple_template_id");
	new_leaf.clear();
	class_key(tab + 2, new_leaf);
	simple_template_id(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "class_key nested_name_specifier template opt simple_template_id");
	new_leaf.clear();
	class_key(tab + 2, new_leaf);
	nested_name_specifier(tab + 2, new_leaf);
	push_back(new_leaf, TEMPLATE, true);
	simple_template_id(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "enum nested_name_specifier opt ID");
	new_leaf.clear();
	push_back(new_leaf, ENUM);
	nested_name_specifier(tab + 2, new_leaf);
	push_back(new_leaf, ID);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void class_key(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "class");
	new_leaf.clear();
	push_back(new_leaf, CLASS);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "struct");
	new_leaf.clear();
	push_back(new_leaf, STRUCT);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "union");
	new_leaf.clear();
	push_back(new_leaf, UNION);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void enum_specifier(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "enum_head { enumerator_list opt }");
	new_leaf.clear();
	enum_head(tab + 2, new_leaf);
	push_back(new_leaf, L_BRACE);
	enumerator_list(tab + 2, new_leaf);
	push_back(new_leaf, R_BRACE);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "enum_head { enumerator_list , }");
	new_leaf.clear();
	enum_head(tab + 2, new_leaf);
	push_back(new_leaf, L_BRACE);
	enumerator_list(tab + 2, new_leaf);
	push_back(new_leaf, COMMA);
	push_back(new_leaf, R_BRACE);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void enum_head(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "enum_key attribute_specifier_seq opt ID opt enum_base opt");
	new_leaf.clear();
	enum_key(tab + 2, new_leaf);
	attribute_specifier_seq(tab + 2, new_leaf);
	push_back(new_leaf, ID, true);
	enum_base(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "enum_key attribute_specifier_seq opt nested_name_specifier ID");
	new_leaf.clear();
	enum_key(tab + 2, new_leaf);
	attribute_specifier_seq(tab + 2, new_leaf);
	nested_name_specifier(tab + 2, new_leaf);
	push_back(new_leaf, ID);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "enum_base opt");
	new_leaf.clear();
	enum_base(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void opaque_enum_declaration(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "enum_key attribute_specifier_seq opt ID enum_base opt ;");
	new_leaf.clear();
	enum_key(tab + 2, new_leaf);
	attribute_specifier_seq(tab + 2, new_leaf);
	push_back(new_leaf, ID);
	enum_base(tab + 2, new_leaf);
	push_back(new_leaf, SEMICOLON);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void enum_key(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "enum");
	new_leaf.clear();
	push_back(new_leaf, ENUM);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "enum class");
	new_leaf.clear();
	push_back(new_leaf, ENUM);
	push_back(new_leaf, CLASS);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "enum struct");
	new_leaf.clear();
	push_back(new_leaf, ENUM);
	push_back(new_leaf, STRUCT);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void enum_base(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, ": type_specifier_seq");
	new_leaf.clear();
	push_back(new_leaf, COLON);
	type_specifier_seq(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void enumerator_list(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "enumerator_definition");
	new_leaf.clear();
	enumerator_definition(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "enumerator_list , enumerator_definition");
	new_leaf.clear();

	static int rs = 0;
	++rs;
	if(rs >= MAX_DEEP) {
		//push_back(leaf, TEMP);
		return;
	}

	enumerator_list(tab + 2, new_leaf);
	push_back(new_leaf, COMMA);
	enumerator_definition(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
	--rs;
}

void enumerator_definition(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "enumerator");
	new_leaf.clear();
	enumerator(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "enumerator = constant_expression");
	new_leaf.clear();
	enumerator(tab + 2, new_leaf);
	push_back(new_leaf, ASSIGN);
	constant_expression(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void enumerator(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "ID attribute_specifier_seq opt");
	new_leaf.clear();
	push_back(new_leaf, ID);
	attribute_specifier_seq(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}

void nested_name_specifier(int tab, leaf_t &leaf)
{
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

	static int rs = 0;
	++rs;
	if(rs >= MAX_DEEP) {
		//push_back(leaf, TEMP);
		return;
	}

	nested_name_specifier(tab + 2, new_leaf);
	push_back(new_leaf, ID);
	push_back(new_leaf, D_COLON);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "nested_name_specifier template opt simple_template_id ::");
	new_leaf.clear();

	if(rs >= MAX_DEEP) {
	//push_back(leaf, TEMP);
		return;
	}

	nested_name_specifier(tab + 2, new_leaf);
	push_back(new_leaf, TEMPLATE, true);
	simple_template_id(tab + 2, new_leaf);
	push_back(new_leaf, D_COLON);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
	--rs;
}

void namespace_name(int tab, leaf_t &leaf)
{
	leaf_t new_leaf, tmp_leaf;
	TAB_FUNCTION(tab);

	OUTPUT(tab + 1, "original_namespace_name");
	new_leaf.clear();
	original_namespace_name(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);

	OUTPUT(tab + 1, "namespace_alias");
	new_leaf.clear();
	namespace_alias(tab + 2, new_leaf);
	insert(tmp_leaf, new_leaf);
	push_back(leaf, tmp_leaf);
}


void attribute_specifier_seq(int tab, leaf_t &leaf)
{
	//TAB_FUNCTION(tab);
	//push_back(leaf, TEMP);
}

void class_name(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, CLASS_NAME);
}

void class_specifier(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, CLASS_SPECIFIER);
}

void constant_expression(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, CONSTANT_EXPRESSION);
}

void enum_name(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, ENUM_NAME);
}

void expression(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, EXPRESSION);
}

void namespace_alias(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, NAMESPACE_ALIAS);
}

void original_namespace_name(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, ORIGINAL_NAMESPACE_NAME);
}

void simple_template_id(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, SIMPLE_TEMPLATE_ID);
}

void typedef_name(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TYPEDEF_NAME);
}

void typename_specifier(int tab, leaf_t &leaf)
{
	TAB_FUNCTION(tab);
	push_back(leaf, TYPENAME_SPECIFIER);
}
