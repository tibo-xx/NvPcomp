%skeleton "lalr1.cc"

%defines
%define namespace "NvPcomp"
%define parser_class_name "BParser"
%parse-param { NvPcomp::FlexScanner &scanner }
%lex-param   { NvPcomp::FlexScanner &scanner }

%code requires {
	#include <stdio.h>
	namespace NvPcomp {
		class FlexScanner;
	}
}

%code {
	// Prototype for the yylex function
	static int yylex(NvPcomp::BParser::semantic_type * yylval, NvPcomp::FlexScanner &scanner);
}

/************************************************************************/
/* Definitions															*/
/************************************************************************/
%union
{
  double dval;
  int    ival;
}

/* Reserved Keywords													*/
%token 	AUTO_TK			BREAK_TK 		CASE_TK 		CHAR_TK
%token 	CONST_TK 		CONTINUE_TK 	DEFAULT_TK		DO_TK			
%token	DOUBLE_TK		ELSE_TK 		ENUM_TK 		EXTERN_TK 		
%token	FLOAT_TK 		FOR_TK 			GOTO_TK 		IF_TK 			
%token	INT_TK 			LONG_TK 		REGISTER_TK		RETURN_TK 
%token	SHORT_TK		SIGNED_TK		SIZEOF_TK		STATIC_TK
%token	STRUCT_TK		SWITCH_TK 		TYPEDEF_TK		UNION_TK
%token	UNSIGNED_TK		VOID_TK 		VOLATILE_TK		WHILE_TK
%token 	ELIPSIS_TK 		RANGE_TK

/* Language Tokens														*/
%token 	IDENTIFIER_TK 
%token 	INTEGER_CONSTANT_TK		FLOATING_CONSTANT_TK 	
%token	CHARACTER_CONSTANT_TK 	ENUMERATION_CONSTANT_TK
%token 	STRING_LITERAL_TK 
%token 	PTR_OP_TK 
%token 	INC_OP_TK 		DEC_OP_TK
%token 	LEFT_OP_TK 		RIGHT_OP_TK 
%token 	LE_OP_TK 		GE_OP_TK 		EQ_OP_TK 		NE_OP_TK
%token 	AND_OP_TK 		OR_OP_TK
%left 	ADD_ASSIGN_TK	SUB_ASSIGN_TK	MOD_ASSIGN_TK	MUL_ASSIGN_TK 	DIV_ASSIGN_TK
%token 	LEFT_ASSIGN_TK 	RIGHT_ASSIGN_TK AND_ASSIGN_TK 	XOR_ASSIGN_TK 
%token	OR_ASSIGN_TK
%token 	TYPEDEF_NAME_TK
/************************************************************************/
/* Grammar Rules														*/
/************************************************************************/
%%

translation_unit
	: external_declaration
	| translation_unit external_declaration
	;

external_declaration
	: function_definition
	| declaration
	;

function_definition
	: declarator compound_statement
	| declarator declaration_list compound_statement
	| declaration_specifiers declarator compound_statement
	| declaration_specifiers declarator declaration_list compound_statement
	;

declaration
	: declaration_specifiers ';'
	| declaration_specifiers init_declarator_list ';'
	;

declaration_list
	: declaration
	| declaration_list declaration
	;

declaration_specifiers
	: storage_class_specifier
	| storage_class_specifier declaration_specifiers
	| type_specifier
	| type_specifier declaration_specifiers
	| type_qualifier 
	| type_qualifier declaration_specifiers
	;

storage_class_specifier
	: AUTO_TK
	| REGISTER_TK
	| STATIC_TK
	| EXTERN_TK
	| TYPEDEF_TK
	;

type_specifier
	: VOID_TK
	| CHAR_TK
	| SHORT_TK
	| INT_TK
	| LONG_TK
	| FLOAT_TK 
	| DOUBLE_TK
	| SIGNED_TK
	| UNSIGNED_TK
	| struct_or_union_specifier
	| enum_specifier
	| TYPEDEF_NAME_TK
	;

type_qualifier
	: CONST_TK
	| VOLATILE_TK
	;

struct_or_union_specifier
	: struct_or_union identifier '{' struct_declaration_list '}'
	| struct_or_union '{' struct_declaration_list '}'
	| struct_or_union identifier
	;

struct_or_union
	: STRUCT_TK
	| UNION_TK
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

init_declarator_list
	: init_declarator
	| init_declarator_list ',' init_declarator
	;

init_declarator
	: declarator
	| declarator '=' initializer
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'
	;

specifier_qualifier_list
	: type_specifier
	| type_specifier specifier_qualifier_list
	| type_qualifier
	| type_qualifier specifier_qualifier_list
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' struct_declarator
	;

struct_declarator
	: declarator
	| ':' constant_expression
	| declarator ':' constant_expression
	;

enum_specifier
	: ENUM_TK '{' enumerator_list '}'
	| ENUM_TK identifier '{' enumerator_list '}'
	| ENUM_TK identifier
	;

enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;

enumerator
	: identifier
	| identifier '=' constant_expression
	;

declarator
	: direct_declarator
	| pointer direct_declarator
	;

direct_declarator
	: identifier
	| '(' declarator ')'
	| direct_declarator '[' ']'
	| direct_declarator '[' constant_expression ']'
	| direct_declarator '(' ')'
	| direct_declarator '(' parameter_type_list ')'
	| direct_declarator '(' identifier_list ')'
	;

pointer
	: '*'
	| '*' type_qualifier_list
	| '*' pointer
	| '*' type_qualifier_list pointer
	;

type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
	;

parameter_type_list
	: parameter_list
	| parameter_list ',' ELIPSIS_TK
	;

parameter_list
	: parameter_declaration
	| parameter_list ',' parameter_declaration
	;

parameter_declaration
	: declaration_specifiers declarator
	| declaration_specifiers
	| declaration_specifiers abstract_declarator
	;

identifier_list
	: identifier
	| identifier_list ',' identifier
	;

initializer
	: assignment_expression
	| '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	;

initializer_list
	: initializer
	| initializer_list ',' initializer
	;

type_name
	: specifier_qualifier_list
	| specifier_qualifier_list abstract_declarator
	;

abstract_declarator
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'
	| '[' ']'
	| '[' constant_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' constant_expression ']'
	| '(' ')'
	| '(' parameter_type_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_type_list ')'
	;

statement
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

labeled_statement
	: identifier ':' statement
	| CASE_TK constant_expression ':' statement
	| DEFAULT_TK ':' statement
	;

expression_statement
	: ';'
	| expression ';'
	;

compound_statement
	: '{' '}'
	| '{' statement_list '}'
	| '{' declaration_list '}'
	| '{' declaration_list statement_list '}'
	;

statement_list
	: statement
	| statement_list statement
	;

selection_statement
	: IF_TK '(' expression ')' statement
	| IF_TK '(' expression ')' statement ELSE_TK statement
	| SWITCH_TK '(' expression ')' statement
	;

iteration_statement
	: WHILE_TK '(' expression ')' statement
	| DO_TK statement WHILE_TK '(' expression ')' ';'
	| FOR_TK '(' ';' ';' ')' statement
	| FOR_TK '(' ';' ';' expression ')' statement
	| FOR_TK '(' ';' expression ';' ')' statement
	| FOR_TK '(' ';' expression ';' expression ')' statement
	| FOR_TK '(' expression ';' ';' ')' statement
	| FOR_TK '(' expression ';' ';' expression ')' statement
	| FOR_TK '(' expression ';' expression ';' ')' statement
	| FOR_TK '(' expression ';' expression ';' expression ')' statement
	;

jump_statement
	: GOTO_TK identifier ';'
	| CONTINUE_TK ';'
	| BREAK_TK ';'
	| RETURN_TK ';'
	| RETURN_TK expression ';'
	;

expression
	: assignment_expression
	| expression ',' assignment_expression
	;

assignment_expression
	: conditional_expression
	| unary_expression assignment_operator assignment_expression
	;

assignment_operator
	: '='
	| MUL_ASSIGN_TK
	| DIV_ASSIGN_TK
	| MOD_ASSIGN_TK
	| ADD_ASSIGN_TK
	| SUB_ASSIGN_TK
	| LEFT_ASSIGN_TK
	| RIGHT_ASSIGN_TK
	| AND_ASSIGN_TK
	| XOR_ASSIGN_TK
	| OR_ASSIGN_TK
	;

conditional_expression
	: logical_or_expression
	| logical_or_expression '?' expression ':' conditional_expression
	;

constant_expression
	: conditional_expression
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression OR_OP_TK logical_and_expression
	;

logical_and_expression
	: inclusive_or_expression
	| logical_and_expression AND_OP_TK inclusive_or_expression
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression '|' exclusive_or_expression
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression '^' and_expression
	;

and_expression
	: equality_expression
	| and_expression '&' equality_expression
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP_TK relational_expression
	| equality_expression NE_OP_TK relational_expression
	;

relational_expression
	: shift_expression
	| relational_expression '<' shift_expression
	| relational_expression '>' shift_expression
	| relational_expression LE_OP_TK shift_expression
	| relational_expression GE_OP_TK shift_expression
	;

shift_expression
	: additive_expression
	| shift_expression LEFT_OP_TK additive_expression
	| shift_expression RIGHT_OP_TK additive_expression
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression
	| additive_expression '-' multiplicative_expression
	;

multiplicative_expression
	: cast_expression
	| multiplicative_expression '*' cast_expression
	| multiplicative_expression '/' cast_expression
	| multiplicative_expression '%' cast_expression
	;

cast_expression
	: unary_expression
	| '(' type_name ')' cast_expression
	;

unary_expression
	: postfix_expression
	| INC_OP_TK unary_expression
	| DEC_OP_TK unary_expression
	| unary_operator cast_expression
	| SIZEOF_TK unary_expression
	| SIZEOF_TK '(' type_name ')'
	;

unary_operator
	: '&'
	| '*'
	| '+'
	| '-'
	| '~'
	| '!'
	;

postfix_expression
	: primary_expression
	| postfix_expression '[' expression ']'
	| postfix_expression '(' ')'
	| postfix_expression '(' argument_expression_list ')'
	| postfix_expression '.' identifier
	| postfix_expression PTR_OP_TK identifier
	| postfix_expression INC_OP_TK
	| postfix_expression DEC_OP_TK
	;

primary_expression
	: identifier
	| constant
	| string
	| '(' expression ')'
	;

argument_expression_list
	: assignment_expression
	| argument_expression_list ',' assignment_expression
	;

constant
	: INTEGER_CONSTANT_TK
	| CHARACTER_CONSTANT_TK
	| FLOATING_CONSTANT_TK
	| ENUMERATION_CONSTANT_TK
	;

string
	: STRING_LITERAL_TK
	;

identifier
	: IDENTIFIER_TK
	;

%%
/************************************************************************/
/* Code																	*/
/************************************************************************/
// Error Function Implementation
void NvPcomp::BParser::error(const NvPcomp::BParser::location_type &loc, const std::string &msg) {
	std::cerr << "Error: " << msg << std::endl;
}

// Declare the Scanner and implement the yylex function
#include "NvPcompScanner.h"
static int yylex(NvPcomp::BParser::semantic_type * yylval, NvPcomp::FlexScanner &scanner) {
	return scanner.yylex(yylval);
}

	
