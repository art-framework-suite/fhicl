document: table_body | prologs table_body

prologs: prolog | prolog prologs

prolog: BEGINPROLOG table_body ENDPROLOG

	/* ----- */

table: LBRACE table_body RBRACE

table_body: | table_items

table_items: table_item | table_item table_items

table_item: ALPHA_START_STRING COLON value | TARGET COLON value

/* ----- */

seq: LBRACKET seq_body RBRACKET

seq_body: | seq_items

seq_items: value | value COMMA seq_items

/* ----- */

value: atom | table | seq

atom: number | string | NIL | BOOL_TOK | REF

number: complex | simple_number

simple_number: UNSIGNED | REAL | INFINITY

string: ALPHA_START_STRING | NUM_START_STRING | DQUOTED | SQUOTED

complex: LPAREN simple_number COMMA simple_number RPAREN

