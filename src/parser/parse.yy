%require "2.4.1"
%skeleton "lalr1.cc"

%defines
%define namespace "NvPcomp"
%define parser_class_name "BParser"
%parse-param { NvPcomp::FlexScanner &scanner}
%parse-param { sourceBuffer &buffer }
%parse-param { symTable &table }
%lex-param   { NvPcomp::FlexScanner &scanner }
%lex-param   { symTable &table }
%locations
%debug

%code requires {	
	#include <stdio.h>
	#include <sourceBuffer.h>
	#include <NvPcomp_logger.h>
	#include <symTable.h>
	
	namespace NvPcomp {
		class FlexScanner;
	}
}

%code {
			
	// Prototype for the yylex function
	static int yylex(NvPcomp::BParser::semantic_type * yylval, NvPcomp::BParser::location_type *loc, NvPcomp::FlexScanner &scanner, NvPcomp::symTable &table);
	
	// The last line printed to the output file.
	unsigned int BP_lastLine = 0;
	
	#define REDUCTION(spot) \
		if(BP_lastLine != yylloc.begin.line) {	\
			LOG(PARSERLog, logLEVEL1) << buffer.bufferGetLineNoCR(yylloc.begin.line, yylloc.end.line); \
		} \
		LOG(PARSERLog, logLEVEL1) << std::string(yylloc.begin.column - 1, ' ') <<"^-Production: " << #spot << " at: " << yylloc; \
		BP_lastLine = yylloc.begin.line;
	
	#define SCOPE_PUSH() \
		LOG(PARSERLog, logLEVEL2) << "BParser: Scope push"; \
		table.push(); \
		table.dump();
		
	#define SCOPE_POP() \
		LOG(PARSERLog, logLEVEL2) << "BParser: Scope pop"; \
		table.pop(); \
		table.dump();
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
	: function_definition 		{REDUCTION(external_declaration:function_definition)}
	| declaration				{REDUCTION(external_declaration:declaration)}
	;

function_definition
	: declarator compound_statement												{REDUCTION(function_definition:declarator compound_statement)}
	| declarator declaration_list compound_statement							{REDUCTION(function_definition:declarator declaration_list compound_statement)}
	| declaration_specifiers declarator compound_statement						{REDUCTION(function_definition:declaration_specifiers declarator compound_statement)}
	| declaration_specifiers declarator declaration_list compound_statement		{REDUCTION(function_definition:declaration_specifiers declarator declaration_list compound_statement)}
	;

declaration
	: declaration_specifiers SEMICOLON_TK						{REDUCTION(declaration_specifiers SEMICOLON_TK)}
	| declaration_specifiers init_declarator_list SEMICOLON_TK 	{REDUCTION(declaration_specifiers init_declarator_list SEMICOLON_TK)}
	;

declaration_list
	: declaration												{REDUCTION(declaration_list:declaration)}
	| declaration_list declaration								{REDUCTION(declaration_list:declaration_list declaration)}
	;

declaration_specifiers
	: storage_class_specifier									{REDUCTION(declaration_specifiers:storage_class_specifier)}
	| storage_class_specifier declaration_specifiers			{REDUCTION(declaration_specifiers:storage_class_specifier declaration_specifiers)}
	| type_specifier											{REDUCTION(declaration_specifiers:type_specifier)}
	| type_specifier declaration_specifiers						{REDUCTION(declaration_specifiers:type_specifier declaration_specifiers)}
	| type_qualifier 											{REDUCTION(declaration_specifiers:type_qualifier)}
	| type_qualifier declaration_specifiers						{REDUCTION(declaration_specifiers:type_qualifier declaration_specifiers)}
	;

storage_class_specifier
	: AUTO_TK				{REDUCTION(storage_class_specifier:AUTO_TK)}
	| REGISTER_TK			{REDUCTION(storage_class_specifier:REGISTER_TK)}
	| STATIC_TK				{REDUCTION(storage_class_specifier:STATIC_TK)}
	| EXTERN_TK				{REDUCTION(storage_class_specifier:EXTERN_TK)}
	| TYPEDEF_TK			{REDUCTION(storage_class_specifier:TYPEDEF_TK)}
	;

type_specifier
	: VOID_TK							{REDUCTION(type_specifier:VOID_TK)}
	| CHAR_TK							{REDUCTION(type_specifier:CHAR_TK)}
	| SHORT_TK							{REDUCTION(type_specifier:SHORT_TK)}
	| INT_TK							{REDUCTION(type_specifier:INT_TK)}
	| LONG_TK							{REDUCTION(type_specifier:LONG_TK)}
	| FLOAT_TK 							{REDUCTION(type_specifier:FLOAT_TK)}
	| DOUBLE_TK							{REDUCTION(type_specifier:DOUBLE_TK)}
	| SIGNED_TK							{REDUCTION(type_specifier:SIGNED_TK)}
	| UNSIGNED_TK						{REDUCTION(type_specifier:UNSIGNED_TK)}
	| struct_or_union_specifier			{REDUCTION(type_specifier:struct_or_union_specifier)}
	| enum_specifier					{REDUCTION(type_specifier:enum_specifier)}
	| TYPEDEF_NAME_TK					{REDUCTION(type_specifier:TYPEDEF_NAME_TK)}
	;

type_qualifier
	: CONST_TK							{REDUCTION(type_qualifier:CONST_TK)}
	| VOLATILE_TK						{REDUCTION(type_qualifier:VOLATILE_TK)}
	;

struct_or_union_specifier
	: struct_or_union identifier OPEN_BRACE_TK {SCOPE_PUSH()}
						struct_declaration_list CLOSE_BRACE_TK				{REDUCTION(struct_or_union_specifier:); SCOPE_POP();}	
	| struct_or_union OPEN_BRACE_TK {SCOPE_PUSH()}
						struct_declaration_list CLOSE_BRACE_TK							{REDUCTION(struct_or_union_specifier:) SCOPE_POP();}
	| struct_or_union identifier																	{REDUCTION(struct_or_union_specifier:)}
	;

struct_or_union
	: STRUCT_TK							{REDUCTION()}
	| UNION_TK							{REDUCTION()}
	;

struct_declaration_list
	: struct_declaration							{REDUCTION()}
	| struct_declaration_list struct_declaration							{REDUCTION()}
	;

init_declarator_list
	: init_declarator							{REDUCTION()}
	| init_declarator_list COMMA_TK init_declarator							{REDUCTION()}
	;

init_declarator
	: declarator							{REDUCTION()}
	| declarator EQUAL_TK initializer							{REDUCTION()}
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list SEMICOLON_TK							{REDUCTION()}
	;

specifier_qualifier_list
	: type_specifier							{REDUCTION()}
	| type_specifier specifier_qualifier_list							{REDUCTION()}
	| type_qualifier							{REDUCTION()}
	| type_qualifier specifier_qualifier_list							{REDUCTION()}
	;

struct_declarator_list
	: struct_declarator							{REDUCTION()}
	| struct_declarator_list COMMA_TK struct_declarator							{REDUCTION()}
	;

struct_declarator
	: declarator							{REDUCTION()}
	| COLON_TK constant_expression							{REDUCTION()}
	| declarator COLON_TK constant_expression							{REDUCTION()}
	;

enum_specifier
	: ENUM_TK OPEN_BRACE_TK {SCOPE_PUSH()}
							enumerator_list CLOSE_BRACE_TK							{REDUCTION(); SCOPE_POP();}
	| ENUM_TK identifier OPEN_BRACE_TK {SCOPE_PUSH()}
							enumerator_list CLOSE_BRACE_TK							{REDUCTION(); SCOPE_POP();}
	| ENUM_TK identifier							{REDUCTION()}
	;

enumerator_list
	: enumerator							{REDUCTION()}
	| enumerator_list COMMA_TK enumerator							{REDUCTION()}
	;

enumerator
	: identifier							{REDUCTION()}
	| identifier EQUAL_TK constant_expression							{REDUCTION()}
	;

declarator
	: direct_declarator							{REDUCTION()}
	| pointer direct_declarator							{REDUCTION()}
	;

direct_declarator
	: identifier							{REDUCTION()}
	| OPEN_PAREN_TK declarator CLOSE_PAREN_TK							{REDUCTION()}
	| direct_declarator OPEN_BRACK_TK CLOSE_BRACK_TK							{REDUCTION()}
	| direct_declarator OPEN_BRACK_TK constant_expression CLOSE_BRACK_TK							{REDUCTION()}
	| direct_declarator OPEN_PAREN_TK CLOSE_PAREN_TK							{REDUCTION()}
	| direct_declarator OPEN_PAREN_TK parameter_type_list CLOSE_PAREN_TK							{REDUCTION()}
	| direct_declarator OPEN_PAREN_TK identifier_list CLOSE_PAREN_TK							{REDUCTION()}
	;

pointer
	: STAR_TK							{REDUCTION()}
	| STAR_TK type_qualifier_list							{REDUCTION()}
	| STAR_TK pointer							{REDUCTION()}
	| STAR_TK type_qualifier_list pointer							{REDUCTION()}
	;

type_qualifier_list
	: type_qualifier							{REDUCTION()}
	| type_qualifier_list type_qualifier							{REDUCTION()}
	;

parameter_type_list
	: parameter_list							{REDUCTION()}
	| parameter_list COMMA_TK ELIPSIS_TK							{REDUCTION()}
	;

parameter_list
	: parameter_declaration							{REDUCTION()}
	| parameter_list COMMA_TK parameter_declaration							{REDUCTION()}
	;

parameter_declaration
	: declaration_specifiers declarator							{REDUCTION()}
	| declaration_specifiers							{REDUCTION()}
	| declaration_specifiers abstract_declarator							{REDUCTION()}
	;

identifier_list
	: identifier							{REDUCTION()}
	| identifier_list COMMA_TK identifier							{REDUCTION()}
	;

initializer
	: assignment_expression							{REDUCTION()}
	| OPEN_BRACE_TK {SCOPE_PUSH()}
				initializer_list CLOSE_BRACE_TK							{REDUCTION(); SCOPE_POP();}
	| OPEN_BRACE_TK {SCOPE_PUSH()}
				initializer_list COMMA_TK CLOSE_BRACE_TK							{REDUCTION(); SCOPE_POP()}
	;

initializer_list
	: initializer							{REDUCTION()}
	| initializer_list COMMA_TK initializer							{REDUCTION()}
	;

type_name
	: specifier_qualifier_list							{REDUCTION()}
	| specifier_qualifier_list abstract_declarator							{REDUCTION()}
	;

abstract_declarator
	: pointer							{REDUCTION()}
	| direct_abstract_declarator							{REDUCTION()}
	| pointer direct_abstract_declarator							{REDUCTION()}
	;

direct_abstract_declarator
	: OPEN_PAREN_TK abstract_declarator CLOSE_PAREN_TK							{REDUCTION()}
	| OPEN_BRACK_TK CLOSE_BRACK_TK							{REDUCTION()}
	| OPEN_BRACK_TK constant_expression CLOSE_BRACK_TK							{REDUCTION()}
	| direct_abstract_declarator OPEN_BRACK_TK CLOSE_BRACK_TK							{REDUCTION()}
	| direct_abstract_declarator OPEN_BRACK_TK constant_expression CLOSE_BRACK_TK							{REDUCTION()}
	| OPEN_PAREN_TK CLOSE_PAREN_TK							{REDUCTION()}
	| OPEN_PAREN_TK parameter_type_list CLOSE_PAREN_TK							{REDUCTION()}
	| direct_abstract_declarator OPEN_PAREN_TK CLOSE_PAREN_TK							{REDUCTION()}
	| direct_abstract_declarator OPEN_PAREN_TK parameter_type_list CLOSE_PAREN_TK							{REDUCTION()}
	;

statement
	: labeled_statement							{REDUCTION()}
	| compound_statement							{REDUCTION()}
	| expression_statement							{REDUCTION()}
	| selection_statement							{REDUCTION()}
	| iteration_statement							{REDUCTION()}
	| jump_statement							{REDUCTION()}
	;

labeled_statement
	: identifier COLON_TK statement							{REDUCTION()}
	| CASE_TK constant_expression COLON_TK statement							{REDUCTION()}
	| DEFAULT_TK COLON_TK statement							{REDUCTION()}
	;

expression_statement
	: SEMICOLON_TK							{REDUCTION()}
	| expression SEMICOLON_TK							{REDUCTION()}
	;

compound_statement
	: OPEN_BRACE_TK {SCOPE_PUSH()}
				CLOSE_BRACE_TK							{REDUCTION(); SCOPE_POP();}
	| OPEN_BRACE_TK {SCOPE_PUSH()}
				statement_list CLOSE_BRACE_TK							{REDUCTION(); SCOPE_POP()}
	| OPEN_BRACE_TK {SCOPE_PUSH()}
				declaration_list CLOSE_BRACE_TK							{REDUCTION(); SCOPE_POP();}
	| OPEN_BRACE_TK {SCOPE_PUSH()}
				declaration_list statement_list CLOSE_BRACE_TK							{REDUCTION(); SCOPE_POP();}
	;

statement_list
	: statement							{REDUCTION()}
	| statement_list statement							{REDUCTION()}
	;

selection_statement
	: IF_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK statement							{REDUCTION()}
	| IF_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK statement ELSE_TK statement							{REDUCTION()}
	| SWITCH_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK statement							{REDUCTION()}
	;

iteration_statement
	: WHILE_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK statement							{REDUCTION()}
	| DO_TK statement WHILE_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK SEMICOLON_TK							{REDUCTION()}
	| FOR_TK OPEN_PAREN_TK SEMICOLON_TK SEMICOLON_TK CLOSE_PAREN_TK statement							{REDUCTION()}
	| FOR_TK OPEN_PAREN_TK SEMICOLON_TK SEMICOLON_TK expression CLOSE_PAREN_TK statement							{REDUCTION()}
	| FOR_TK OPEN_PAREN_TK SEMICOLON_TK expression SEMICOLON_TK CLOSE_PAREN_TK statement							{REDUCTION()}
	| FOR_TK OPEN_PAREN_TK SEMICOLON_TK expression SEMICOLON_TK expression CLOSE_PAREN_TK statement							{REDUCTION()}
	| FOR_TK OPEN_PAREN_TK expression SEMICOLON_TK SEMICOLON_TK CLOSE_PAREN_TK statement							{REDUCTION()}
	| FOR_TK OPEN_PAREN_TK expression SEMICOLON_TK SEMICOLON_TK expression CLOSE_PAREN_TK statement							{REDUCTION()}
	| FOR_TK OPEN_PAREN_TK expression SEMICOLON_TK expression SEMICOLON_TK CLOSE_PAREN_TK statement							{REDUCTION()}
	| FOR_TK OPEN_PAREN_TK expression SEMICOLON_TK expression SEMICOLON_TK expression CLOSE_PAREN_TK statement							{REDUCTION()}
	;

jump_statement
	: GOTO_TK identifier SEMICOLON_TK							{REDUCTION()}
	| CONTINUE_TK SEMICOLON_TK							{REDUCTION()}
	| BREAK_TK SEMICOLON_TK							{REDUCTION()}
	| RETURN_TK SEMICOLON_TK							{REDUCTION()}
	| RETURN_TK expression SEMICOLON_TK							{REDUCTION()}
	;

expression
	: assignment_expression							{REDUCTION()}
	| expression COMMA_TK assignment_expression							{REDUCTION()}
	;

assignment_expression
	: conditional_expression							{REDUCTION()}
	| unary_expression assignment_operator assignment_expression							{REDUCTION()}
	;

assignment_operator
	: EQUAL_TK							{REDUCTION()}
	| MUL_ASSIGN_TK							{REDUCTION()}
	| DIV_ASSIGN_TK							{REDUCTION()}
	| MOD_ASSIGN_TK							{REDUCTION()}
	| ADD_ASSIGN_TK							{REDUCTION()}
	| SUB_ASSIGN_TK							{REDUCTION()}
	| LEFT_ASSIGN_TK							{REDUCTION()}
	| RIGHT_ASSIGN_TK							{REDUCTION()}
	| AND_ASSIGN_TK							{REDUCTION()}
	| XOR_ASSIGN_TK							{REDUCTION()}
	| OR_ASSIGN_TK							{REDUCTION()}
	;

conditional_expression
	: logical_or_expression							{REDUCTION()}
	| logical_or_expression QUESTION_TK expression COLON_TK conditional_expression							{REDUCTION()}
	;

constant_expression
	: conditional_expression							{REDUCTION()}
	;

logical_or_expression
	: logical_and_expression							{REDUCTION()}
	| logical_or_expression OR_OP_TK logical_and_expression							{REDUCTION()}
	;

logical_and_expression
	: inclusive_or_expression							{REDUCTION()}
	| logical_and_expression AND_OP_TK inclusive_or_expression							{REDUCTION()}
	;

inclusive_or_expression
	: exclusive_or_expression							{REDUCTION()}
	| inclusive_or_expression BIT_OR_TK exclusive_or_expression							{REDUCTION()}
	;

exclusive_or_expression
	: and_expression							{REDUCTION()}
	| exclusive_or_expression BIT_XOR_TK and_expression							{REDUCTION()}
	;

and_expression
	: equality_expression							{REDUCTION()}
	| and_expression BIT_AND_TK equality_expression							{REDUCTION()}
	;

equality_expression
	: relational_expression							{REDUCTION()}
	| equality_expression EQ_OP_TK relational_expression							{REDUCTION()}
	| equality_expression NE_OP_TK relational_expression							{REDUCTION()}
	;

relational_expression
	: shift_expression							{REDUCTION()}
	| relational_expression LT_TK shift_expression							{REDUCTION()}
	| relational_expression GT_TK shift_expression							{REDUCTION()}
	| relational_expression LE_OP_TK shift_expression							{REDUCTION()}
	| relational_expression GE_OP_TK shift_expression							{REDUCTION()}
	;

shift_expression
	: additive_expression							{REDUCTION()}
	| shift_expression LEFT_OP_TK additive_expression							{REDUCTION()}
	| shift_expression RIGHT_OP_TK additive_expression							{REDUCTION()}
	;

additive_expression
	: multiplicative_expression							{REDUCTION()}
	| additive_expression PLUS_TK multiplicative_expression							{REDUCTION()}
	| additive_expression MINUS_TK multiplicative_expression							{REDUCTION()}
	;

multiplicative_expression
	: cast_expression							{REDUCTION()}
	| multiplicative_expression STAR_TK cast_expression							{REDUCTION()}
	| multiplicative_expression DIV_TK cast_expression							{REDUCTION()}
	| multiplicative_expression MOD_TK cast_expression							{REDUCTION()}
	;

cast_expression
	: unary_expression							{REDUCTION()}
	| OPEN_PAREN_TK type_name CLOSE_PAREN_TK cast_expression							{REDUCTION()}
	;

unary_expression
	: postfix_expression							{REDUCTION()}
	| INC_OP_TK unary_expression							{REDUCTION()}
	| DEC_OP_TK unary_expression							{REDUCTION()}
	| unary_operator cast_expression							{REDUCTION()}
	| SIZEOF_TK unary_expression							{REDUCTION()}
	| SIZEOF_TK OPEN_PAREN_TK type_name CLOSE_PAREN_TK							{REDUCTION()}
	;

unary_operator
	: BIT_AND_TK							{REDUCTION()}
	| STAR_TK							{REDUCTION()}
	| PLUS_TK							{REDUCTION()}
	| MINUS_TK							{REDUCTION()}
	| BIT_NOT_TK							{REDUCTION()}
	| NOT_TK							{REDUCTION()}
	;

postfix_expression
	: primary_expression							{REDUCTION()}
	| postfix_expression OPEN_BRACK_TK expression CLOSE_BRACK_TK							{REDUCTION()}
	| postfix_expression OPEN_PAREN_TK CLOSE_PAREN_TK							{REDUCTION()}
	| postfix_expression OPEN_PAREN_TK argument_expression_list CLOSE_PAREN_TK							{REDUCTION()}
	| postfix_expression PERIOD_TK identifier							{REDUCTION()}
	| postfix_expression PTR_OP_TK identifier							{REDUCTION()}
	| postfix_expression INC_OP_TK							{REDUCTION()}
	| postfix_expression DEC_OP_TK							{REDUCTION()}
	;

primary_expression
	: identifier							{REDUCTION()}
	| constant							{REDUCTION()}
	| string							{REDUCTION()}
	| OPEN_PAREN_TK expression CLOSE_PAREN_TK							{REDUCTION()}
	;

argument_expression_list
	: assignment_expression							{REDUCTION()}
	| argument_expression_list COMMA_TK assignment_expression							{REDUCTION()}
	;

constant
	: INTEGER_CONSTANT_TK							{REDUCTION()}
	| CHARACTER_CONSTANT_TK							{REDUCTION()}
	| FLOATING_CONSTANT_TK							{REDUCTION()}
	| ENUMERATION_CONSTANT_TK							{REDUCTION()}
	;

string
	: STRING_LITERAL_TK							{REDUCTION()}
	;

identifier
	: IDENTIFIER_TK							{REDUCTION()}
	;

comment
	: COMMENT_TK							{REDUCTION()}
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
static int yylex(NvPcomp::BParser::semantic_type * yylval, NvPcomp::BParser::location_type *loc, NvPcomp::FlexScanner &scanner, NvPcomp::symTable &table) {
	if(&table == 0) 
		std::cout << "This sucks" << std::endl;
	return scanner.yylex(yylval,loc, &table);
}
