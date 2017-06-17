#include "public.h"

#define TERMINAL_FILE	"terminal-symbol.h"
#define UNTERMINAL_FILE	"unterminal-symbol.h"

int main(int argc, char *argv[])
{
	leaf_t code;
	str2code_map_t str2code;
	code2str_vec_t code2str;

//	init_data(argv[1], str2code, code2str);
	init_data(TERMINAL_FILE, str2code, code2str);
	init_data(UNTERMINAL_FILE, str2code, code2str);

	//statement(0, code);
	//try_block(0, code);
	//template_declaration(0, code);
	//primary_expression(0, code);

    decl_specifier_seq(0, code);
	cout << "size:" << code.size() << endl;
	output(code, code2str);
	return 0;
}

