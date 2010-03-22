%require "2.4.1"
%skeleton "lalr1.cc"

%defines
%define namespace "NvPcomp"
%define parser_class_name "BParser"
%parse-param { NvPcomp::FlexScanner &scanner}
%parse-param { sourceBuffer &buffer }
%lex-param   { NvPcomp::FlexScanner &scanner }
%locations
%debug

%code requires {	
	#include <stdio.h>
	#include <sourceBuffer.h>
	#include <NvPcomp_logger.h>
	
	namespace NvPcomp {
		class FlexScanner;
	}
}

%code {
	#define PRODUCTION(spot) \
		LOG(PARSERLog, logLEVEL1) << buffer.bufferGetLineNoCR(yylloc.begin.line, yylloc.end.line); \
		LOG(PARSERLog, logLEVEL1) << std::string(yylloc.begin.column - 1, ' ') <<"^-Production: " << #spot << " at: " << yylloc << std::endl;
	
	// Prototype for the yylex function
	static int yylex(NvPcomp::BParser::semantic_type * yylval, NvPcomp::BParser::location_type *loc, NvPcomp::FlexScanner &scanner);
}

/************************************************************************/
/* Definitions															*/
/************************************************************************/
%union
{
  double dval;
  int    ival;
  std::string *sval;
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

%token	COMMENT_TK

%token	ERROR_TK

%token 	RANGE_TK

%token 	IDENTIFIER_TK 
%token 	INTEGER_CONSTANT_TK		FLOATING_CONSTANT_TK 	
%token	CHARACTER_CONSTANT_TK 	ENUMERATION_CONSTANT_TK
%token 	STRING_LITERAL_TK 
%token 	TYPEDEF_NAME_TK

/* Block Tokens															*/
/*		{				}				(				)				*/
%token	OPEN_BRACE_TK	CLOSE_BRACE_TK	OPEN_PAREN_TK	CLOSE_PAREN_TK
/*		;																*/
%token	SEMICOLON_TK
/* Reference															*/
/*		[				]												*/
%token	OPEN_BRACK_TK	CLOSE_BRACK_TK
/* Sequencing															*/
/*		,				...												*/
%token	COMMA_TK		ELIPSIS_TK
/* Bitwise Logic Tokens												*/
/*		~				&				|				^				*/
%token	BIT_NOT_TK		BIT_AND_TK		BIT_OR_TK		BIT_XOR_TK
/* Arithmetic tokens													*/
/*		*				/				+				-				*/
%token	STAR_TK			DIV_TK			PLUS_TK			MINUS_TK
/*		%																*/
%token	MOD_TK
/* Order Relations 														*/
/*		<				<=				>				>=				*/
%token	LT_TK			LE_OP_TK 		GT_TK			GE_OP_TK
/* Boolean Logic 														*/
/*		!				&&				||								*/
%token	NOT_TK			AND_OP_TK 		OR_OP_TK		
/* Bitwise Shift 														*/
/*		<<				>>												*/
%token 	LEFT_OP_TK 		RIGHT_OP_TK
/* Assignment															*/
/*		=				+=				-=				%=				*/
%token	EQUAL_TK		ADD_ASSIGN_TK	SUB_ASSIGN_TK	MOD_ASSIGN_TK
/*		*=				/=												*/
%token	MUL_ASSIGN_TK 	DIV_ASSIGN_TK
/*		<<=				>>=				&=				^=				*/
%token 	LEFT_ASSIGN_TK 	RIGHT_ASSIGN_TK AND_ASSIGN_TK 	XOR_ASSIGN_TK 
/*		|=																*/
%token	OR_ASSIGN_TK
/* Conditional Evaluation												*/
/*		?				:												*/
%token	QUESTION_TK		COLON_TK
/* Increment and Decrement												*/
/*		++				--												*/
%token 	INC_OP_TK 		DEC_OP_TK
/* Member Selection														*/
/*		->				.												*/
%token 	PTR_OP_TK		PERIOD_TK 
/* Equality Testing														*/
/*		==				!=												*/
%token 	EQ_OP_TK 		NE_OP_TK
/************************************************************************/
/* Grammar Rules														*/
/************************************************************************/
%%

translation_unit
	: external_declaration
	| translation_unit external_declaration
	;

external_declaration
	: function_definition 		{PRODUCTION(external_declaration:function_definition)}
	| declaration				{PRODUCTION(external_declaration:declaration)}
	;

function_definition
	: declarator compound_statement	
	| declarator declaration_list compound_statement
	| declaration_specifiers declarator compound_statement
	| declaration_specifiers declarator declaration_list compound_statement
	;

declaration
	: declaration_specifiers SEMICOLON_TK						{PRODUCTION(declaration_specifiers SEMICOLON_TK)}
	| declaration_specifiers init_declarator_list SEMICOLON_TK 	{PRODUCTION(declaration_specifiers init_declarator_list SEMICOLON_TK)}
	;

declaration_list
	: declaration												{PRODUCTION(declaration_list:declaration)}
	| declaration_list declaration								{PRODUCTION(declaration_list:declaration_list declaration)}
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
	: struct_or_union identifier OPEN_BRACE_TK struct_declaration_list CLOSE_BRACE_TK	
	| struct_or_union OPEN_BRACE_TK struct_declaration_list CLOSE_BRACE_TK
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
	| init_declarator_list COMMA_TK init_declarator
	;

init_declarator
	: declarator
	| declarator EQUAL_TK initializer
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list SEMICOLON_TK
	;

specifier_qualifier_list
	: type_specifier
	| type_specifier specifier_qualifier_list
	| type_qualifier
	| type_qualifier specifier_qualifier_list
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list COMMA_TK struct_declarator
	;

struct_declarator
	: declarator
	| COLON_TK constant_expression
	| declarator COLON_TK constant_expression
	;

enum_specifier
	: ENUM_TK OPEN_BRACE_TK enumerator_list CLOSE_BRACE_TK
	| ENUM_TK identifier OPEN_BRACE_TK enumerator_list CLOSE_BRACE_TK
	| ENUM_TK identifier
	;

enumerator_list
	: enumerator
	| enumerator_list COMMA_TK enumerator
	;

enumerator
	: identifier
	| identifier EQUAL_TK constant_expression
	;

declarator
	: direct_declarator
	| pointer direct_declarator
	;

direct_declarator
	: identifier
	| OPEN_PAREN_TK declarator CLOSE_PAREN_TK
	| direct_declarator OPEN_BRACK_TK CLOSE_BRACK_TK
	| direct_declarator OPEN_BRACK_TK constant_expression CLOSE_BRACK_TK
	| direct_declarator OPEN_PAREN_TK CLOSE_PAREN_TK
	| direct_declarator OPEN_PAREN_TK parameter_type_list CLOSE_PAREN_TK
	| direct_declarator OPEN_PAREN_TK identifier_list CLOSE_PAREN_TK
	;

pointer
	: STAR_TK
	| STAR_TK type_qualifier_list
	| STAR_TK pointer
	| STAR_TK type_qualifier_list pointer
	;

type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
	;

parameter_type_list
	: parameter_list
	| parameter_list COMMA_TK ELIPSIS_TK
	;

parameter_list
	: parameter_declaration
	| parameter_list COMMA_TK parameter_declaration
	;

parameter_declaration
	: declaration_specifiers declarator
	| declaration_specifiers
	| declaration_specifiers abstract_declarator
	;

identifier_list
	: identifier
	| identifier_list COMMA_TK identifier
	;

initializer
	: assignment_expression
	| OPEN_BRACE_TK initializer_list CLOSE_BRACE_TK
	| OPEN_BRACE_TK initializer_list COMMA_TK CLOSE_BRACE_TK
	;

initializer_list
	: initializer
	| initializer_list COMMA_TK initializer
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
	: OPEN_PAREN_TK abstract_declarator CLOSE_PAREN_TK
	| OPEN_BRACK_TK CLOSE_BRACK_TK
	| OPEN_BRACK_TK constant_expression CLOSE_BRACK_TK
	| direct_abstract_declarator OPEN_BRACK_TK CLOSE_BRACK_TK
	| direct_abstract_declarator OPEN_BRACK_TK constant_expression CLOSE_BRACK_TK
	| OPEN_PAREN_TK CLOSE_PAREN_TK
	| OPEN_PAREN_TK parameter_type_list CLOSE_PAREN_TK
	| direct_abstract_declarator OPEN_PAREN_TK CLOSE_PAREN_TK
	| direct_abstract_declarator OPEN_PAREN_TK parameter_type_list CLOSE_PAREN_TK
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
	: identifier COLON_TK statement
	| CASE_TK constant_expression COLON_TK statement
	| DEFAULT_TK COLON_TK statement
	;

expression_statement
	: SEMICOLON_TK
	| expression SEMICOLON_TK
	;

compound_statement
	: OPEN_BRACE_TK CLOSE_BRACE_TK
	| OPEN_BRACE_TK statement_list CLOSE_BRACE_TK
	| OPEN_BRACE_TK declaration_list CLOSE_BRACE_TK
	| OPEN_BRACE_TK declaration_list statement_list CLOSE_BRACE_TK
	;

statement_list
	: statement
	| statement_list statement
	;

selection_statement
	: IF_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK statement
	| IF_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK statement ELSE_TK statement
	| SWITCH_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK statement
	;

iteration_statement
	: WHILE_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK statement
	| DO_TK statement WHILE_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK SEMICOLON_TK
	| FOR_TK OPEN_PAREN_TK SEMICOLON_TK SEMICOLON_TK CLOSE_PAREN_TK statement
	| FOR_TK OPEN_PAREN_TK SEMICOLON_TK SEMICOLON_TK expression CLOSE_PAREN_TK statement
	| FOR_TK OPEN_PAREN_TK SEMICOLON_TK expression SEMICOLON_TK CLOSE_PAREN_TK statement
	| FOR_TK OPEN_PAREN_TK SEMICOLON_TK expression SEMICOLON_TK expression CLOSE_PAREN_TK statement
	| FOR_TK OPEN_PAREN_TK expression SEMICOLON_TK SEMICOLON_TK CLOSE_PAREN_TK statement
	| FOR_TK OPEN_PAREN_TK expression SEMICOLON_TK SEMICOLON_TK expression CLOSE_PAREN_TK statement
	| FOR_TK OPEN_PAREN_TK expression SEMICOLON_TK expression SEMICOLON_TK CLOSE_PAREN_TK statement
	| FOR_TK OPEN_PAREN_TK expression SEMICOLON_TK expression SEMICOLON_TK expression CLOSE_PAREN_TK statement
	;

jump_statement
	: GOTO_TK identifier SEMICOLON_TK
	| CONTINUE_TK SEMICOLON_TK
	| BREAK_TK SEMICOLON_TK
	| RETURN_TK SEMICOLON_TK
	| RETURN_TK expression SEMICOLON_TK
	;

expression
	: assignment_expression
	| expression COMMA_TK assignment_expression
	;

assignment_expression
	: conditional_expression
	| unary_expression assignment_operator assignment_expression
	;

assignment_operator
	: EQUAL_TK
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
	| logical_or_expression QUESTION_TK expression COLON_TK conditional_expression
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
	| inclusive_or_expression BIT_OR_TK exclusive_or_expression
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression BIT_XOR_TK and_expression
	;

and_expression
	: equality_expression
	| and_expression BIT_AND_TK equality_expression
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP_TK relational_expression
	| equality_expression NE_OP_TK relational_expression
	;

relational_expression
	: shift_expression
	| relational_expression LT_TK shift_expression
	| relational_expression GT_TK shift_expression
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
	| additive_expression PLUS_TK multiplicative_expression
	| additive_expression MINUS_TK multiplicative_expression
	;

multiplicative_expression
	: cast_expression
	| multiplicative_expression STAR_TK cast_expression
	| multiplicative_expression DIV_TK cast_expression
	| multiplicative_expression MOD_TK cast_expression
	;

cast_expression
	: unary_expression
	| OPEN_PAREN_TK type_name CLOSE_PAREN_TK cast_expression
	;

unary_expression
	: postfix_expression
	| INC_OP_TK unary_expression
	| DEC_OP_TK unary_expression
	| unary_operator cast_expression
	| SIZEOF_TK unary_expression
	| SIZEOF_TK OPEN_PAREN_TK type_name CLOSE_PAREN_TK
	;

unary_operator
	: BIT_AND_TK
	| STAR_TK
	| PLUS_TK
	| MINUS_TK
	| BIT_NOT_TK
	| NOT_TK
	;

postfix_expression
	: primary_expression
	| postfix_expression OPEN_BRACK_TK expression CLOSE_BRACK_TK
	| postfix_expression OPEN_PAREN_TK CLOSE_PAREN_TK
	| postfix_expression OPEN_PAREN_TK argument_expression_list CLOSE_PAREN_TK
	| postfix_expression PERIOD_TK identifier
	| postfix_expression PTR_OP_TK identifier
	| postfix_expression INC_OP_TK
	| postfix_expression DEC_OP_TK
	;

primary_expression
	: identifier
	| constant
	| string
	| OPEN_PAREN_TK expression CLOSE_PAREN_TK
	;

argument_expression_list
	: assignment_expression
	| argument_expression_list COMMA_TK assignment_expression
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

comment
	: COMMENT_TK
	;

%%
/************************************************************************/
/* Code																	*/
/************************************************************************/
// Error Function Implementation
void NvPcomp::BParser::error(const NvPcomp::BParser::location_type &loc, const std::string &msg) {
	std::cerr << "Error: " << msg << " location: " << loc << std::endl;
}

// Declare the Scanner and implement the yylex function
#include "NvPcompScanner.h"
static int yylex(NvPcomp::BParser::semantic_type * yylval, NvPcomp::BParser::location_type *loc, NvPcomp::FlexScanner &scanner) {
	return scanner.yylex(yylval,loc);
}

	
