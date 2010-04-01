%require "2.4.1"
%skeleton "lalr1.cc"

%defines
%define namespace "NvPcomp"
%define parser_class_name "BParser"
%parse-param { NvPcomp::FlexScanner &scanner}
%parse-param { sourceBuffer &buffer }
%parse-param { symTable &table }
%parse-param { astNode &ast }
%lex-param   { NvPcomp::FlexScanner &scanner }
%lex-param   { symTable &table }
%locations
%debug

%code requires {	
	#include <stdio.h>
	#include <sourceBuffer.h>
	#include <NvPcomp_logger.h>
	#include <symTable.h>
	#include <ast.h>
	namespace NvPcomp {
		class FlexScanner;
	}
			
	typedef struct{
		double dval;
		int    ival;
		char	*sval;
		astNode *astval;
		bool commentFound;
		NvPcomp::location comment_loc;
	} YYSTYPE;
	
	extern YYSTYPE yylval;
}

%code {
			
	// Prototype for the yylex function
	static int yylex(NvPcomp::BParser::semantic_type * yylval, NvPcomp::BParser::location_type *loc, NvPcomp::FlexScanner &scanner, NvPcomp::symTable &table);
	
	// The last line printed to the output file.
	unsigned int BP_lastLine = 0;
	
	#define REDUCTION(spot) \
		if(yylval.commentFound) { \
			LOG(PARSERLog, logLEVEL1) << "Comment Preceeding Reduction: at " << yylval.comment_loc; \
			yylval.commentFound = false; \
			/*LOG(PARSERLog, logLEVEL1) << buffer.bufferGetLineNoCR(yylloc.begin.line, yylloc.end.line); \*/ \
		} \
		if(BP_lastLine != yylloc.begin.line) {	\
			LOG(PARSERLog, logLEVEL1) << buffer.bufferGetLineNoCR(yylloc.begin.line, yylloc.end.line); \
		} \
		LOG(PARSERLog, logLEVEL1) << std::string(yylloc.begin.column - 1, ' ') <<"^-Reduction: " << #spot << " at: " << yylloc; \
		BP_lastLine = yylloc.begin.line;
	
	#define SCOPE_PUSH() \
		LOG(PARSERLog, logLEVEL2) << "BParser: Scope push"; \
		table.push();
				
	#define SCOPE_POP() \
		LOG(PARSERLog, logLEVEL2) << "BParser: Scope pop"; \
		table.pop();
}

/************************************************************************/
/* Definitions															*/
/************************************************************************/
/*%union*/

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
	: external_declaration 									{ 
																REDUCTION(translation_unit:external_declaration)
																$<astval>$ = new astNode("translation_unit");
																ast.addChild($<astval>$);
																$<astval>$->addChild($<astval>1);
															}
	| translation_unit external_declaration					{ 
																REDUCTION(translation_unit:translation_unit external_declaration)
																$<astval>$ = new astNode("translation_unit");
																ast.addChild($<astval>$);
																$<astval>$->addChild($<astval>2);
															}
	;

external_declaration
	: function_definition 		{REDUCTION(external_declaration:function_definition)}
	| declaration					{REDUCTION(external_declaration:declaration)}
	;

function_definition
	: declarator compound_statement												{REDUCTION(function_definition:declarator compound_statement)}
	| declarator declaration_list compound_statement							{REDUCTION(function_definition:declarator declaration_list compound_statement)}
	| declaration_specifiers declarator compound_statement						{REDUCTION(function_definition:declaration_specifiers declarator compound_statement)
					$<astval>$ = new astNode("function_definition");
					$<astval>$->addChild($<astval>1);
					$<astval>$->addChild($<astval>2);
					$<astval>$->addChild($<astval>3);
					}
	| declaration_specifiers declarator declaration_list compound_statement		{REDUCTION(function_definition:declaration_specifiers declarator declaration_list compound_statement)}
	;

declaration
	: declaration_specifiers SEMICOLON_TK						{REDUCTION(declaration:declaration_specifiers SEMICOLON_TK)}
	| declaration_specifiers init_declarator_list SEMICOLON_TK 	
	  {
	  	REDUCTION(declaration:declaration_specifiers init_declarator_list SEMICOLON_TK)
	  	$<astval>$ = new astNode("declaration");
	  	$<astval>$->addChild($<astval>1);
	  	$<astval>$->addChild($<astval>2);
	  }
	;

declaration_list
	: declaration												{REDUCTION(declaration_list:declaration)}
	| declaration_list declaration								{REDUCTION(declaration_list:declaration_list declaration)
					$<astval>$ = new astNode("declaration_list");
					$<astval>$->addChild($<astval>1);
					$<astval>$->addChild($<astval>2);
					}
	;

declaration_specifiers
	: storage_class_specifier									{REDUCTION(declaration_specifiers:storage_class_specifier)}
	| storage_class_specifier declaration_specifiers			{REDUCTION(declaration_specifiers:storage_class_specifier declaration_specifiers)
					$<astval>$ = new astNode("declaration_specifiers");
					$<astval>$->addChild($<astval>1);
					$<astval>$->addChild($<astval>2);
					}
	| type_specifier	  											{REDUCTION(declaration_specifiers:type_specifier)}
	| type_specifier declaration_specifiers						{REDUCTION(declaration_specifiers:type_specifier declaration_specifiers)
					$<astval>$ = new astNode("declaration_specifiers");
					$<astval>$->addChild($<astval>1);
					$<astval>$->addChild($<astval>2);
					}
	| type_qualifier 											{REDUCTION(declaration_specifiers:type_qualifier)}
	| type_qualifier declaration_specifiers						{REDUCTION(declaration_specifiers:type_qualifier declaration_specifiers)
					$<astval>$ = new astNode("declaration_specifiers");
					$<astval>$->addChild($<astval>1);
					$<astval>$->addChild($<astval>2);
					}
	;

storage_class_specifier
	: AUTO_TK				{REDUCTION(storage_class_specifier:AUTO_TK)
               $<astval>$ = new astNode("AUTO_TK", yylval.sval);
	            }
	| REGISTER_TK			{REDUCTION(storage_class_specifier:REGISTER_TK)
               $<astval>$ = new astNode("REGISTER_TK", yylval.sval);
	            }
	| STATIC_TK				{REDUCTION(storage_class_specifier:STATIC_TK)
               $<astval>$ = new astNode("STATIC_TK", yylval.sval);
	            }
	| EXTERN_TK				{REDUCTION(storage_class_specifier:EXTERN_TK)
               $<astval>$ = new astNode("EXTERN_TK", yylval.sval);
	            }
	| TYPEDEF_TK			{REDUCTION(storage_class_specifier:TYPEDEF_TK)
	            $<astval>$ = new astNode("TYPEDEF_TK", yylval.sval);
	            }
	;

type_specifier
	: VOID_TK							{REDUCTION(type_specifier:VOID_TK)
										    $<astval>$ = new astNode("VOID_TK", yylval.sval);}
	| CHAR_TK							{REDUCTION(type_specifier:CHAR_TK)
										    $<astval>$ = new astNode("CHAR_TK", yylval.sval);}
	| SHORT_TK							{REDUCTION(type_specifier:SHORT_TK)
										    $<astval>$ = new astNode("SHORT_TK", yylval.sval);}
	| INT_TK							   {REDUCTION(type_specifier:INT_TK)
											 $<astval>$ = new astNode("INT_TK", yylval.sval);}
	| LONG_TK							{REDUCTION(type_specifier:LONG_TK)
										    $<astval>$ = new astNode("LONG_TK", yylval.sval);}
	| FLOAT_TK 							{REDUCTION(type_specifier:FLOAT_TK)
										    $<astval>$ = new astNode("FLOAT_TK", yylval.sval);}
	| DOUBLE_TK							{REDUCTION(type_specifier:DOUBLE_TK)
										    $<astval>$ = new astNode("DOUBLE_TK", yylval.sval);}
	| SIGNED_TK							{REDUCTION(type_specifier:SIGNED_TK)
										    $<astval>$ = new astNode("SIGNED_TK", yylval.sval);}
	| UNSIGNED_TK						{REDUCTION(type_specifier:UNSIGNED_TK)
										    $<astval>$ = new astNode("UNSIGNED_TK", yylval.sval);}
	| struct_or_union_specifier			{REDUCTION(type_specifier:struct_or_union_specifier)}
	| enum_specifier					{REDUCTION(type_specifier:enum_specifier)}
	| TYPEDEF_NAME_TK					{REDUCTION(type_specifier:TYPEDEF_NAME_TK)}
	;

type_qualifier
	: CONST_TK							{REDUCTION(type_qualifier:CONST_TK)
               $<astval>$ = new astNode("CONST_TK", yylval.sval);
   	         }
	| VOLATILE_TK						{REDUCTION(type_qualifier:VOLATILE_TK)
               $<astval>$ = new astNode("VOLATILE_TK", yylval.sval);
   	         }
	;

struct_or_union_specifier
	: struct_or_union identifier OPEN_BRACE_TK {SCOPE_PUSH()}
						struct_declaration_list CLOSE_BRACE_TK				{REDUCTION(struct_or_union_specifier:); SCOPE_POP();}	
	| struct_or_union OPEN_BRACE_TK {SCOPE_PUSH()}
						struct_declaration_list CLOSE_BRACE_TK							{REDUCTION(struct_or_union_specifier:) SCOPE_POP();}
	| struct_or_union identifier																	{REDUCTION(struct_or_union_specifier:)}
	;

struct_or_union
	: STRUCT_TK							{REDUCTION(struct_or_union:STRUCT_TK)}
	| UNION_TK							{REDUCTION(struct_or_union:UNION_TK)}
	;

struct_declaration_list
	: struct_declaration							{REDUCTION(struct_declaration_list:struct_declaration)}
	| struct_declaration_list struct_declaration	{REDUCTION(struct_declaration_list:struct_declaration_list struct_declaration)}
	;

init_declarator_list
	: init_declarator									{REDUCTION(init_declarator_list:init_declarator)}
	| init_declarator_list COMMA_TK init_declarator		{REDUCTION(init_declarator_list:init_declarator_list COMMA_TK init_declarator)
																		    $<astval>$ = new astNode("init_declarator_list");
																		    $<astval>$->addChild($<astval>1);
																		    $<astval>$->addChild($<astval>3);
																			
																		}
	;

init_declarator
	: declarator							{REDUCTION(init_declarator:declarator)}
	| declarator EQUAL_TK initializer		
		{REDUCTION(init_declarator:declarator EQUAL_TK initializer)
			$<astval>$ = new astNode("init_declarator");
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild(new astNode("EQUAL_TK", "="));
			$<astval>$->addChild($<astval>3);
		}
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list SEMICOLON_TK		{REDUCTION(struct_declaration:specifier_qualifier_list struct_declarator_list SEMICOLON_TK)}
	;

specifier_qualifier_list
	: type_specifier									{REDUCTION(specifier_qualifier_list:type_specifier)}
	| type_specifier specifier_qualifier_list			{REDUCTION(specifier_qualifier_list:type_specifier specifier_qualifier_list)}
	| type_qualifier									{REDUCTION(specifier_qualifier_list:type_qualifier)}
	| type_qualifier specifier_qualifier_list			{REDUCTION(specifier_qualifier_list:type_qualifier specifier_qualifier_list)}
	;

struct_declarator_list
	: struct_declarator										{REDUCTION(struct_declarator_list:struct_declarator)}
	| struct_declarator_list COMMA_TK struct_declarator		{REDUCTION(struct_declarator_list:struct_declarator_list COMMA_TK struct_declarator)}
	;

struct_declarator
	: declarator										{REDUCTION(struct_declarator:declarator)}
	| COLON_TK constant_expression						{REDUCTION(struct_declarator:COLON_TK constant_expression)}
	| declarator COLON_TK constant_expression			{REDUCTION(struct_declarator:declarator COLON_TK constant_expression)}
	;

enum_specifier
	: ENUM_TK OPEN_BRACE_TK {SCOPE_PUSH()}
							enumerator_list CLOSE_BRACE_TK				{REDUCTION(enum_specifier:ENUM_TK OPEN_BRACE_TK enumerator_list CLOSE_BRACE_TK); SCOPE_POP();}
	| ENUM_TK identifier OPEN_BRACE_TK {SCOPE_PUSH()}
							enumerator_list CLOSE_BRACE_TK				{REDUCTION(enum_specifier:ENUM_TK identifier OPEN_BRACE_TK enumerator_list CLOSE_BRACE_TK); SCOPE_POP();}
	| ENUM_TK identifier												{REDUCTION(enum_specifier:)}
	;

enumerator_list
	: enumerator												{REDUCTION(enumerator_list:enumerator)}
	| enumerator_list COMMA_TK enumerator						{REDUCTION(enumerator_list:enumerator_list COMMA_TK enumerator)}
	;

enumerator
	: identifier										{REDUCTION(enumerator:identifier)}
	| identifier EQUAL_TK constant_expression			{REDUCTION(enumerator:identifier EQUAL_TK constant_expression)}
	;

declarator
	: direct_declarator					{REDUCTION(declarator:direct_declarator)}
	| pointer direct_declarator			{REDUCTION(declarator:pointer direct_declarator)
													 $<astval>$ = new astNode("declarator");
													 $<astval>$->addChild($<astval>1);
													 $<astval>$->addChild($<astval>2);
													 }
	;

direct_declarator
	: identifier																{REDUCTION(direct_declarator:identifier)}
	| OPEN_PAREN_TK declarator CLOSE_PAREN_TK									{REDUCTION(direct_declarator:OPEN_PAREN_TK declarator CLOSE_PAREN_TK)
			$<astval>$ = new astNode("direct_declarator");
			$<astval>$->addChild($<astval>2);
			}
	| direct_declarator OPEN_BRACK_TK CLOSE_BRACK_TK							{REDUCTION(direct_declarator:direct_declarator OPEN_BRACK_TK CLOSE_BRACK_TK)
			$<astval>$ = new astNode("direct_declarator");
			$<astval>$->addChild($<astval>1);
			}
	| direct_declarator OPEN_BRACK_TK constant_expression CLOSE_BRACK_TK		{REDUCTION(direct_declarator:direct_declarator OPEN_BRACK_TK constant_expression CLOSE_BRACK_TK)
			$<astval>$ = new astNode("direct_declarator");
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>3);
			}
	| direct_declarator OPEN_PAREN_TK CLOSE_PAREN_TK							{REDUCTION(direct_declarator:direct_declarator OPEN_PAREN_TK CLOSE_PAREN_TK)
			$<astval>$ = new astNode("direct_declarator");
			$<astval>$->addChild($<astval>1);
			}
	| direct_declarator OPEN_PAREN_TK parameter_type_list CLOSE_PAREN_TK		{REDUCTION(direct_declarator:direct_declarator OPEN_PAREN_TK parameter_type_list CLOSE_PAREN_TK)
			$<astval>$ = new astNode("direct_declarator");
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>3);
			}
	| direct_declarator OPEN_PAREN_TK identifier_list CLOSE_PAREN_TK			{REDUCTION(direct_declarator:direct_declarator OPEN_PAREN_TK identifier_list CLOSE_PAREN_TK)
			$<astval>$ = new astNode("direct_declarator");
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>3);
			}
	;

pointer
	: STAR_TK									{REDUCTION(pointer:STAR_TK)
													 $<astval>$ = new astNode("STAR_TK", $<sval>1);}
	| STAR_TK type_qualifier_list				{REDUCTION(pointer:STAR_TK type_qualifier_list)}
	| STAR_TK pointer							{REDUCTION(pointer:STAR_TK pointer)}
	| STAR_TK type_qualifier_list pointer		{REDUCTION(pointer:STAR_TK type_qualifier_list pointer)}
	;

type_qualifier_list
	: type_qualifier							{REDUCTION(type_qualifier_list:type_qualifier)}
	| type_qualifier_list type_qualifier		{REDUCTION(type_qualifier_list:type_qualifier_list type_qualifier)}
	;

parameter_type_list
	: parameter_list							{REDUCTION(parameter_type_list:parameter_list)}
	| parameter_list COMMA_TK ELIPSIS_TK		{REDUCTION(parameter_type_list:parameter_list COMMA_TK ELIPSIS_TK)}
	;

parameter_list
	: parameter_declaration								{REDUCTION(parameter_list:parameter_declaration)}
	| parameter_list COMMA_TK parameter_declaration		{REDUCTION(parameter_list:parameter_list COMMA_TK parameter_declaration)
					$<astval>$ = new astNode("parameter_list");
					$<astval>$->addChild($<astval>1);
					$<astval>$->addChild($<astval>3);
					}
	;

parameter_declaration
	: declaration_specifiers declarator					{REDUCTION(parameter_declaration:declaration_specifiers declarator)
					$<astval>$ = new astNode("parameter_declaration");
					$<astval>$->addChild($<astval>1);
					$<astval>$->addChild($<astval>2);
					}
	| declaration_specifiers							{REDUCTION(parameter_declaration:declaration_specifiers)}
	| declaration_specifiers abstract_declarator		{REDUCTION(parameter_declaration:declaration_specifiers abstract_declarator)}
	;

identifier_list
	: identifier									{REDUCTION(identifier_list:identifier)}
	| identifier_list COMMA_TK identifier			{REDUCTION(identifier_list:identifier_list COMMA_TK identifier)}
	;

initializer
	: assignment_expression									{REDUCTION(initializer:assignment_expression)}
	| OPEN_BRACE_TK {SCOPE_PUSH()}
				initializer_list CLOSE_BRACE_TK				{REDUCTION(initializer:OPEN_BRACE_TK initializer_list CLOSE_BRACE_TK); SCOPE_POP();}
	| OPEN_BRACE_TK {SCOPE_PUSH()}
				initializer_list COMMA_TK CLOSE_BRACE_TK	{REDUCTION(initializer:OPEN_BRACE_TK initializer_list COMMA_TK CLOSE_BRACE_TK); SCOPE_POP()}
	;

initializer_list
	: initializer									{REDUCTION(initializer_list:initializer)}
	| initializer_list COMMA_TK initializer			{REDUCTION(initializer_list:initializer_list COMMA_TK initializer)}
	;

type_name
	: specifier_qualifier_list							{REDUCTION(type_name:specifier_qualifier_list)}
	| specifier_qualifier_list abstract_declarator		{REDUCTION(type_name:specifier_qualifier_list abstract_declarator)}
	;

abstract_declarator
	: pointer											{REDUCTION(abstract_declarator:pointer)}
	| direct_abstract_declarator						{REDUCTION(abstract_declarator:direct_abstract_declarator)}
	| pointer direct_abstract_declarator				{REDUCTION(abstract_declarator:pointer direct_abstract_declarator)}
	;

direct_abstract_declarator
	: OPEN_PAREN_TK abstract_declarator CLOSE_PAREN_TK										{REDUCTION(direct_abstract_declarator:OPEN_PAREN_TK abstract_declarator CLOSE_PAREN_TK)}
	| OPEN_BRACK_TK CLOSE_BRACK_TK															{REDUCTION(direct_abstract_declarator:OPEN_BRACK_TK CLOSE_BRACK_TK)}
	| OPEN_BRACK_TK constant_expression CLOSE_BRACK_TK										{REDUCTION(direct_abstract_declarator:OPEN_BRACK_TK constant_expression CLOSE_BRACK_TK)}
	| direct_abstract_declarator OPEN_BRACK_TK CLOSE_BRACK_TK								{REDUCTION(direct_abstract_declarator:direct_abstract_declarator OPEN_BRACK_TK CLOSE_BRACK_TK)}
	| direct_abstract_declarator OPEN_BRACK_TK constant_expression CLOSE_BRACK_TK			{REDUCTION(direct_abstract_declarator:direct_abstract_declarator OPEN_BRACK_TK constant_expression CLOSE_BRACK_TK)}
	| OPEN_PAREN_TK CLOSE_PAREN_TK															{REDUCTION(direct_abstract_declarator:OPEN_PAREN_TK CLOSE_PAREN_TK)}
	| OPEN_PAREN_TK parameter_type_list CLOSE_PAREN_TK										{REDUCTION(direct_abstract_declarator:OPEN_PAREN_TK parameter_type_list CLOSE_PAREN_TK)}
	| direct_abstract_declarator OPEN_PAREN_TK CLOSE_PAREN_TK								{REDUCTION(direct_abstract_declarator:direct_abstract_declarator OPEN_PAREN_TK CLOSE_PAREN_TK)}
	| direct_abstract_declarator OPEN_PAREN_TK parameter_type_list CLOSE_PAREN_TK			{REDUCTION(direct_abstract_declarator:direct_abstract_declarator OPEN_PAREN_TK parameter_type_list CLOSE_PAREN_TK)}
	;

statement
	: labeled_statement				{REDUCTION(statement:labeled_statement)}
	| compound_statement			{REDUCTION(statement:compound_statement)}
	| expression_statement			{REDUCTION(statement:expression_statement)}
	| selection_statement			{REDUCTION(statement:selection_statement)}
	| iteration_statement			{REDUCTION(statement:iteration_statement)}
	| jump_statement				{REDUCTION(statement:jump_statement)}
	;

labeled_statement
	: identifier COLON_TK statement							{REDUCTION(labeled_statement:identifier COLON_TK statement)}
	| CASE_TK constant_expression COLON_TK statement		{REDUCTION(labeled_statement:CASE_TK constant_expression COLON_TK statement)}
	| DEFAULT_TK COLON_TK statement							{REDUCTION(labeled_statement:DEFAULT_TK COLON_TK statement)}
	;

expression_statement
	: SEMICOLON_TK							{REDUCTION(expression_statement:SEMICOLON_TK)}
	| expression SEMICOLON_TK				{REDUCTION(expression_statement:expression SEMICOLON_TK)}
	;

compound_statement
	: OPEN_BRACE_TK {SCOPE_PUSH()}
				CLOSE_BRACE_TK											{REDUCTION(compound_statement:OPEN_BRACE_TK CLOSE_BRACE_TK); SCOPE_POP();
																		    $<astval>$ = new astNode("compound_statement");}
	| OPEN_BRACE_TK {SCOPE_PUSH()}
				statement_list CLOSE_BRACE_TK							{REDUCTION(compound_statement:OPEN_BRACE_TK statement_list CLOSE_BRACE_TK); SCOPE_POP()
																					$<astval>$ = new astNode("compound_statement");
																					 $<astval>$->addChild($<astval>3);}
	| OPEN_BRACE_TK {SCOPE_PUSH()}
				declaration_list CLOSE_BRACE_TK							{REDUCTION(compound_statement:OPEN_BRACE_TK declaration_list CLOSE_BRACE_TK); SCOPE_POP();
																					 $<astval>$ = new astNode("compound_statement");
																					 $<astval>$->addChild($<astval>3);}
	| OPEN_BRACE_TK {SCOPE_PUSH()}
				declaration_list statement_list CLOSE_BRACE_TK			{REDUCTION(compound_statement:OPEN_BRACE_TK declaration_list statement_list CLOSE_BRACE_TK); SCOPE_POP();
																					$<astval>$ = new astNode("compound_statement");
																					 $<astval>$->addChild($<astval>3);
																					 $<astval>$->addChild($<astval>4);}
	;

statement_list
	: statement							{REDUCTION(statement_list:statement)}
	| statement_list statement			{REDUCTION(statement_list:statement_list statement)
	         $<astval>$ = new astNode("statement_list");
	         $<astval>$->addChild($<astval>1);
	         $<astval>$->addChild($<astval>2);
	         }
	;

selection_statement
	: IF_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK statement							{REDUCTION(selection_statement:IF_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK statement)
				$<astval>$ = new astNode("selection_statement");
				$<astval>$->addChild(new astNode("IF_TK", "if"));
				$<astval>$->addChild($<astval>3);
				$<astval>$->addChild($<astval>5);
				}
	| IF_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK statement ELSE_TK statement			{REDUCTION(selection_statement:IF_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK statement ELSE_TK statement)
				$<astval>$ = new astNode("selection_statement");
				$<astval>$->addChild(new astNode("IF_TK", "if"));
				$<astval>$->addChild($<astval>3);
				$<astval>$->addChild($<astval>5);
				$<astval>$->addChild(new astNode("ELSE_TK", "else"));
				$<astval>$->addChild($<astval>7);
				}	
	| SWITCH_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK statement						{REDUCTION(selection_statement:SWITCH_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK statement)}
	;

iteration_statement
	: WHILE_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK statement													{REDUCTION(iteration_statement:WHILE_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK statement)
	      $<astval>$ = new astNode("iteration_statement");
         $<astval>$->addChild(new astNode("WHILE_TK", "while"));
         $<astval>$->addChild($<astval>3);
         $<astval>$->addChild($<astval>5);	      
	      }
	| DO_TK statement WHILE_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK SEMICOLON_TK									{REDUCTION(iteration_statement:DO_TK statement WHILE_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK SEMICOLON_TK)
	      $<astval>$ = new astNode("iteration_statement");
         $<astval>$->addChild(new astNode("DO_TK", "do"));
         $<astval>$->addChild($<astval>2);
         $<astval>$->addChild($<astval>5);	      
	      }

	| FOR_TK OPEN_PAREN_TK SEMICOLON_TK SEMICOLON_TK CLOSE_PAREN_TK statement										{REDUCTION(iteration_statement:FOR_TK OPEN_PAREN_TK SEMICOLON_TK SEMICOLON_TK CLOSE_PAREN_TK statement)
	      $<astval>$ = new astNode("iteration_statement");
         $<astval>$->addChild(new astNode("FOR_TK", "for"));
         $<astval>$->addChild($<astval>6);	      
	      }
	| FOR_TK OPEN_PAREN_TK SEMICOLON_TK SEMICOLON_TK expression CLOSE_PAREN_TK statement							{REDUCTION(iteration_statement:FOR_TK OPEN_PAREN_TK SEMICOLON_TK SEMICOLON_TK expression CLOSE_PAREN_TK statement)
	      $<astval>$ = new astNode("iteration_statement");
         $<astval>$->addChild(new astNode("FOR_TK", "for"));
         $<astval>$->addChild($<astval>5);
         $<astval>$->addChild($<astval>7);
         }
	| FOR_TK OPEN_PAREN_TK SEMICOLON_TK expression SEMICOLON_TK CLOSE_PAREN_TK statement							{REDUCTION(iteration_statement:FOR_TK OPEN_PAREN_TK SEMICOLON_TK expression SEMICOLON_TK CLOSE_PAREN_TK statement)
	      $<astval>$ = new astNode("iteration_statement");
         $<astval>$->addChild(new astNode("FOR_TK", "for"));
         $<astval>$->addChild($<astval>4);
         $<astval>$->addChild($<astval>7);
         }
	| FOR_TK OPEN_PAREN_TK SEMICOLON_TK expression SEMICOLON_TK expression CLOSE_PAREN_TK statement					{REDUCTION(iteration_statement:FOR_TK OPEN_PAREN_TK SEMICOLON_TK expression SEMICOLON_TK expression CLOSE_PAREN_TK statement)
	      $<astval>$ = new astNode("iteration_statement");
         $<astval>$->addChild(new astNode("FOR_TK", "for"));
         $<astval>$->addChild($<astval>4);
         $<astval>$->addChild($<astval>6);
         $<astval>$->addChild($<astval>8);
         }
	| FOR_TK OPEN_PAREN_TK expression SEMICOLON_TK SEMICOLON_TK CLOSE_PAREN_TK statement							{REDUCTION(iteration_statement:FOR_TK OPEN_PAREN_TK expression SEMICOLON_TK SEMICOLON_TK CLOSE_PAREN_TK statement)
	      $<astval>$ = new astNode("iteration_statement");
         $<astval>$->addChild(new astNode("FOR_TK", "for"));
         $<astval>$->addChild($<astval>3);
         $<astval>$->addChild($<astval>7);	      
	      }
	| FOR_TK OPEN_PAREN_TK expression SEMICOLON_TK SEMICOLON_TK expression CLOSE_PAREN_TK statement					{REDUCTION(iteration_statement:FOR_TK OPEN_PAREN_TK expression SEMICOLON_TK SEMICOLON_TK expression CLOSE_PAREN_TK statement)
	      $<astval>$ = new astNode("iteration_statement");
         $<astval>$->addChild(new astNode("FOR_TK", "for"));
         $<astval>$->addChild($<astval>3);
         $<astval>$->addChild($<astval>6);
         $<astval>$->addChild($<astval>8);
         }
	| FOR_TK OPEN_PAREN_TK expression SEMICOLON_TK expression SEMICOLON_TK CLOSE_PAREN_TK statement					{REDUCTION(iteration_statement:FOR_TK OPEN_PAREN_TK expression SEMICOLON_TK expression SEMICOLON_TK CLOSE_PAREN_TK statement)
	      $<astval>$ = new astNode("iteration_statement");
         $<astval>$->addChild(new astNode("FOR_TK", "for"));
         $<astval>$->addChild($<astval>3);
         $<astval>$->addChild($<astval>5);
         $<astval>$->addChild($<astval>8);
         }
	| FOR_TK OPEN_PAREN_TK expression SEMICOLON_TK expression SEMICOLON_TK expression CLOSE_PAREN_TK statement		{REDUCTION(iteration_statement:FOR_TK OPEN_PAREN_TK expression SEMICOLON_TK expression SEMICOLON_TK expression CLOSE_PAREN_TK statement)
	      $<astval>$ = new astNode("iteration_statement");
         $<astval>$->addChild(new astNode("FOR_TK", "for"));
         $<astval>$->addChild($<astval>3);
         $<astval>$->addChild($<astval>5);
         $<astval>$->addChild($<astval>7);
         $<astval>$->addChild($<astval>9);
         }
	;

jump_statement
	: GOTO_TK identifier SEMICOLON_TK			{REDUCTION(jump_statement:GOTO_TK identifier SEMICOLON_TK)}
	| CONTINUE_TK SEMICOLON_TK					{REDUCTION(jump_statement:CONTINUE_TK SEMICOLON_TK)}
	| BREAK_TK SEMICOLON_TK						{REDUCTION(jump_statement:BREAK_TK SEMICOLON_TK)}
	| RETURN_TK SEMICOLON_TK					{REDUCTION(jump_statement:RETURN_TK SEMICOLON_TK)}
	| RETURN_TK expression SEMICOLON_TK			{REDUCTION(jump_statement:RETURN_TK expression SEMICOLON_TK)}
	;

expression
	: assignment_expression							{REDUCTION(expression:assignment_expression)}
	| expression COMMA_TK assignment_expression		{REDUCTION(expression:expression COMMA_TK assignment_expression)}
	;

assignment_expression
	: conditional_expression											{REDUCTION(assignment_expression:conditional_expression)}
	| unary_expression assignment_operator assignment_expression		{REDUCTION(assignment_expression:unary_expression assignment_operator assignment_expression)}
	;

assignment_operator
	: EQUAL_TK					{REDUCTION(assignment_operator:EQUAL_TK)}
	| MUL_ASSIGN_TK				{REDUCTION(assignment_operator:MUL_ASSIGN_TK)}
	| DIV_ASSIGN_TK				{REDUCTION(assignment_operator:DIV_ASSIGN_TK)}
	| MOD_ASSIGN_TK				{REDUCTION(assignment_operator:MOD_ASSIGN_TK)}
	| ADD_ASSIGN_TK				{REDUCTION(assignment_operator:ADD_ASSIGN_TK)}
	| SUB_ASSIGN_TK				{REDUCTION(assignment_operator:SUB_ASSIGN_TK)}
	| LEFT_ASSIGN_TK			{REDUCTION(assignment_operator:LEFT_ASSIGN_TK)}
	| RIGHT_ASSIGN_TK			{REDUCTION(assignment_operator:RIGHT_ASSIGN_TK)}
	| AND_ASSIGN_TK				{REDUCTION(assignment_operator:AND_ASSIGN_TK)}
	| XOR_ASSIGN_TK				{REDUCTION(assignment_operator:XOR_ASSIGN_TK)}
	| OR_ASSIGN_TK				{REDUCTION(assignment_operator:OR_ASSIGN_TK)}
	;

conditional_expression
	: logical_or_expression																	{REDUCTION(conditional_expression:logical_or_expression)}
	| logical_or_expression QUESTION_TK expression COLON_TK conditional_expression			{REDUCTION(conditional_expression:logical_or_expression QUESTION_TK expression COLON_TK conditional_expression)}
	;

constant_expression
	: conditional_expression	{REDUCTION(constant_expression:conditional_expression)}
	;

logical_or_expression
	: logical_and_expression											{REDUCTION(logical_or_expression:logical_and_expression)}
	| logical_or_expression OR_OP_TK logical_and_expression				{REDUCTION(logical_or_expression:logical_or_expression OR_OP_TK logical_and_expression)}
	;

logical_and_expression
	: inclusive_or_expression											{REDUCTION(logical_and_expression:inclusive_or_expression)}
	| logical_and_expression AND_OP_TK inclusive_or_expression			{REDUCTION(logical_and_expression:logical_and_expression AND_OP_TK inclusive_or_expression)}
	;

inclusive_or_expression
	: exclusive_or_expression											{REDUCTION(inclusive_or_expression:exclusive_or_expression)}
	| inclusive_or_expression BIT_OR_TK exclusive_or_expression			{REDUCTION(inclusive_or_expression:inclusive_or_expression BIT_OR_TK exclusive_or_expression)}
	;

exclusive_or_expression
	: and_expression													{REDUCTION(exclusive_or_expression:and_expression)}
	| exclusive_or_expression BIT_XOR_TK and_expression					{REDUCTION(exclusive_or_expression:exclusive_or_expression BIT_XOR_TK and_expression)}
	;

and_expression
	: equality_expression												{REDUCTION(and_expression:equality_expression)}
	| and_expression BIT_AND_TK equality_expression						{REDUCTION(and_expression:and_expression BIT_AND_TK equality_expression)}
	;

equality_expression
	: relational_expression												{REDUCTION(equality_expression:relational_expression)}
	| equality_expression EQ_OP_TK relational_expression				{REDUCTION(equality_expression:equality_expression EQ_OP_TK relational_expression)}
	| equality_expression NE_OP_TK relational_expression				{REDUCTION(equality_expression:equality_expression NE_OP_TK relational_expression)}
	;

relational_expression
	: shift_expression													{REDUCTION(relational_expression:shift_expression)}
	| relational_expression LT_TK shift_expression						{REDUCTION(relational_expression:relational_expression LT_TK shift_expression)}
	| relational_expression GT_TK shift_expression						{REDUCTION(relational_expression:relational_expression GT_TK shift_expression)}
	| relational_expression LE_OP_TK shift_expression					{REDUCTION(relational_expression:relational_expression LE_OP_TK shift_expression)}
	| relational_expression GE_OP_TK shift_expression					{REDUCTION(relational_expression:relational_expression GE_OP_TK shift_expression)}
	;

shift_expression
	: additive_expression												{REDUCTION(shift_expression:additive_expression)}
	| shift_expression LEFT_OP_TK additive_expression					{REDUCTION(shift_expression:shift_expression LEFT_OP_TK additive_expression)}
	| shift_expression RIGHT_OP_TK additive_expression					{REDUCTION(shift_expression:shift_expression RIGHT_OP_TK additive_expression)}
	;

additive_expression
	: multiplicative_expression											{REDUCTION(additive_expression:multiplicative_expression)}
	| additive_expression PLUS_TK multiplicative_expression				{REDUCTION(additive_expression:additive_expression PLUS_TK multiplicative_expression)
										$<astval>$ = new astNode("additive_expression");											
										$<astval>$->addChild($<astval>1);
										$<astval>$->addChild(new astNode("PLUS_TK","+"));
										$<astval>$->addChild($<astval>3);
										}
	| additive_expression MINUS_TK multiplicative_expression			{REDUCTION(additive_expression:additive_expression MINUS_TK multiplicative_expression)
										$<astval>$ = new astNode("additive_expression");										
										$<astval>$->addChild($<astval>1);
										$<astval>$->addChild(new astNode("MINUS_TK","-"));
										$<astval>$->addChild($<astval>3);
										}
	;

multiplicative_expression
	: cast_expression													{REDUCTION(multiplicative_expression:cast_expression)}
	| multiplicative_expression STAR_TK cast_expression					{REDUCTION(multiplicative_expression:multiplicative_expression STAR_TK cast_expression	)
										$<astval>$ = new astNode("mutiplicative_expression");
										$<astval>$->addChild($<astval>1);
										$<astval>$->addChild(new astNode("STAR_TK","*"));
										$<astval>$->addChild($<astval>3);
										}
	| multiplicative_expression DIV_TK cast_expression					{REDUCTION(multiplicative_expression:multiplicative_expression DIV_TK cast_expression)
										$<astval>$ = new astNode("mutiplicative_expression");
										$<astval>$->addChild($<astval>1);
										$<astval>$->addChild(new astNode("DIV_TK","/"));
										$<astval>$->addChild($<astval>3);
										}
	| multiplicative_expression MOD_TK cast_expression					{REDUCTION(multiplicative_expression:multiplicative_expression MOD_TK cast_expression)
										$<astval>$ = new astNode("mutiplicative_expression");
										$<astval>$->addChild($<astval>1);
										$<astval>$->addChild(new astNode("MOD_TK","%"));
										$<astval>$->addChild($<astval>3);
										}
	;

cast_expression
	: unary_expression													{REDUCTION(cast_expression:unary_expression)}
	| OPEN_PAREN_TK type_name CLOSE_PAREN_TK cast_expression			{REDUCTION(cast_expression:OPEN_PAREN_TK type_name CLOSE_PAREN_TK cast_expression)}
	;

unary_expression
	: postfix_expression												{REDUCTION(unary_expression:postfix_expression)}
	| INC_OP_TK unary_expression										{REDUCTION(unary_expression:INC_OP_TK unary_expression)
	         $<astval>$ = new astNode("unary_expression");
	         $<astval>$->addChild(new astNode("INC_OP_TK", "++"));
	         $<astval>$->addChild($<astval>2);	         
	         }
	| DEC_OP_TK unary_expression										{REDUCTION(unary_expression:DEC_OP_TK unary_expression)
	         $<astval>$ = new astNode("unary_expression");
	         $<astval>$->addChild(new astNode("DEC_OP_TK", "--"));
	         $<astval>$->addChild($<astval>2);	         
	         }
	| unary_operator cast_expression									{REDUCTION(unary_expression:unary_operator cast_expression)
	         $<astval>$ = new astNode("unary_expression");
	         $<astval>$->addChild($<astval>1);
	         $<astval>$->addChild($<astval>2);	         
	         }
	| SIZEOF_TK unary_expression										{REDUCTION(unary_expression:SIZEOF_TK unary_expression)
	         $<astval>$ = new astNode("unary_expression");
	         $<astval>$->addChild(new astNode("SIZEOF_TK", "sizeof"));
	         $<astval>$->addChild($<astval>2);	         
	         }
	| SIZEOF_TK OPEN_PAREN_TK type_name CLOSE_PAREN_TK					{REDUCTION(unary_expression:SIZEOF_TK OPEN_PAREN_TK type_name CLOSE_PAREN_TK)
	         $<astval>$ = new astNode("unary_expression");
	         $<astval>$->addChild(new astNode("SIZEOF_TK", "sizeof"));
	         $<astval>$->addChild($<astval>3);	         
	         }
	;

unary_operator
	: BIT_AND_TK				{REDUCTION(unary_operator:BIT_AND_TK)}
	| STAR_TK					{REDUCTION(unary_operator:STAR_TK)}
	| PLUS_TK					{REDUCTION(unary_operator:PLUS_TK)}
	| MINUS_TK					{REDUCTION(unary_operator:MINUS_TK)}
	| BIT_NOT_TK				{REDUCTION(unary_operator:BIT_NOT_TK)}
	| NOT_TK					{REDUCTION(unary_operator:NOT_TK)}
	;

postfix_expression
	: primary_expression															{REDUCTION(postfix_expression:primary_expression)}
	| postfix_expression OPEN_BRACK_TK expression CLOSE_BRACK_TK					{REDUCTION(postfix_expression:postfix_expression OPEN_BRACK_TK expression CLOSE_BRACK_TK)}
	| postfix_expression OPEN_PAREN_TK CLOSE_PAREN_TK								{REDUCTION(postfix_expression:postfix_expression OPEN_PAREN_TK CLOSE_PAREN_TK)}
	| postfix_expression OPEN_PAREN_TK argument_expression_list CLOSE_PAREN_TK		{REDUCTION(postfix_expression:postfix_expression OPEN_PAREN_TK argument_expression_list CLOSE_PAREN_TK)}
	| postfix_expression PERIOD_TK identifier										{REDUCTION(postfix_expression:postfix_expression PERIOD_TK identifier)}
	| postfix_expression PTR_OP_TK identifier										{REDUCTION(postfix_expression:postfix_expression PTR_OP_TK identifier)}
	| postfix_expression INC_OP_TK													{REDUCTION(postfix_expression:postfix_expression INC_OP_TK)}
	| postfix_expression DEC_OP_TK													{REDUCTION(postfix_expression:postfix_expression DEC_OP_TK)}
	;

primary_expression
	: identifier														{REDUCTION(primary_expression:identifier)}
	| constant															{REDUCTION(primary_expression:constant)}
	| string															{REDUCTION(primary_expression:string)}
	| OPEN_PAREN_TK expression CLOSE_PAREN_TK							{REDUCTION(primary_expression:OPEN_PAREN_TK expression CLOSE_PAREN_TK)
																				    $<astval>$ = $<astval>2;}
	;

argument_expression_list
	: assignment_expression												{REDUCTION(argument_expression_list:assignment_expression)}
	| argument_expression_list COMMA_TK assignment_expression			{REDUCTION(argument_expression_list:argument_expression_list COMMA_TK assignment_expression)
               $<astval>$ = new astNode("argument_expression_list");
               $<astval>$->addChild($<astval>1);
               $<astval>$->addChild($<astval>3);
               }
	;

constant
	: INTEGER_CONSTANT_TK				{REDUCTION(constant:INTEGER_CONSTANT_TK)
												 $<astval>$ = new astNode("INTEGER_CONSTANT_TK", yylval.sval);}
	| CHARACTER_CONSTANT_TK				{REDUCTION(constant:CHARACTER_CONSTANT_TK)
												 $<astval>$ = new astNode("CHARACTER_CONSTANT_TK", yylval.sval);}
	| FLOATING_CONSTANT_TK				{REDUCTION(constant:FLOATING_CONSTANT_TK)
												 $<astval>$ = new astNode("FLOATING_CONSTANT_TK", yylval.sval);}
	| ENUMERATION_CONSTANT_TK			{REDUCTION(constant:ENUMERATION_CONSTANT_TK)
												 $<astval>$ = new astNode("ENUMERATION_CONSTANT_TK", yylval.sval);}
	;

string
	: STRING_LITERAL_TK					{REDUCTION(string:STRING_LITERAL_TK)
												 $<astval>$ = new astNode("STRING_LITERAL_TK", yylval.sval);}
	;

identifier
	: IDENTIFIER_TK						{REDUCTION(identifier:IDENTIFIER_TK)
												 $<astval>$ = new astNode("IDENTIFIER_TK", yylval.sval);}
	;

%%
/************************************************************************/
/* Code																	*/
/************************************************************************/
// Error Function Implementation
void NvPcomp::BParser::error(const NvPcomp::BParser::location_type &loc, const std::string &msg) {
	std::cerr << "Error: " << msg << ": at location: " << loc << std::endl;
}

// Declare the Scanner and implement the yylex function
#include "NvPcompScanner.h"
static int yylex(NvPcomp::BParser::semantic_type * yylval, NvPcomp::BParser::location_type *loc, NvPcomp::FlexScanner &scanner, NvPcomp::symTable &table) {
	return scanner.yylex(yylval,loc, &table);
}
