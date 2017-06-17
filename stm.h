void statement(int tab, leaf_t &leaf);
void labeled_statement(int tab, leaf_t &leaf);
void expression_statement(int tab, leaf_t &leaf);
void compound_statement(int tab, leaf_t &leaf);
void statement_seq(int tab, leaf_t &leaf);
void selection_statement(int tab, leaf_t &leaf);
void condition(int tab, leaf_t &leaf);
void iteration_statement(int tab, leaf_t &leaf);
void for_init_statement(int tab, leaf_t &leaf);
void for_range_declaration(int tab, leaf_t &leaf);
void for_range_initializer(int tab, leaf_t &leaf);
void jump_statement(int tab, leaf_t &leaf);
void declaration_statement(int tab, leaf_t &leaf);
void block_declaration(int tab, leaf_t &leaf);
void braced_init_list(int tab, leaf_t &leaf);
void decl_specifier_seq(int tab, leaf_t &leaf);
void declarator(int tab, leaf_t &leaf);
void initializer_clause(int tab, leaf_t &leaf);
void expression(int tab, leaf_t &leaf);
void constant_expression(int tab, leaf_t &leaf);
void try_block(int tab, leaf_t &leaf);
void simple_declaration(int tab, leaf_t &leaf);