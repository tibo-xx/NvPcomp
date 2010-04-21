%require "2.4.1"
%skeleton "lalr1.cc"

%defines
%define namespace "NvPcomp"
%define parser_class_name "BParser"
%parse-param { NvPcomp::FlexScanner &scanner}
%parse-param { sourceBuffer &buffer }
%parse-param { symTable &table }
%parse-param { ast &asTree }
%parse-param { NvPcomp::tacTree &acTree }
%lex-param   { NvPcomp::FlexScanner &scanner }
%lex-param   { symTable &table }
%lex-param   { NvPcomp::tacTree &acTree }
%locations
%debug

%code requires {	
	#include <stdio.h>
	#include <sourceBuffer.h>
	#include <NvPcomp_logger.h>
	#include <symTable.h>
	#include <ast.h>
	#include <astNode.h>
	#include <tacTree.h>
	#include <ast_include.h>
	#include <iostream>
	
	#define YYDEBUG 1
	
	namespace NvPcomp {
		class FlexScanner;
	}
			
	typedef struct{
		double dval;
		int    ival;
		char	*sval;
		int    tval;
		astNode *astval;
		bool commentFound;
		NvPcomp::location comment_loc;
	} YYSTYPE;
	
	extern YYSTYPE yylval;
	extern int yydebug_;
	
}

%code {
			
	// Prototype for the yylex function
	static int yylex(NvPcomp::BParser::semantic_type * yylval, NvPcomp::BParser::location_type *loc, NvPcomp::FlexScanner &scanner, NvPcomp::symTable &table, NvPcomp::tacTree &acTree);
	
	// The last line printed to the output file.
	unsigned int BP_lastLine = 0;
	
	#define REDUCTION(spot) \
		yydebug_ = 0; \
		if(yylval.commentFound) { \
			LOG(PARSERLog, logLEVEL1) << "Comment Preceeding Reduction: at " << yylval.comment_loc; \
			yylval.commentFound = false; \
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

/* Reserved Keywords													*/
%token 	AUTO_TK			BREAK_TK 		CASE_TK 		CHAR_TK
%token 	CONST_TK 		CONTINUE_TK 	DEFAULT_TK		DO_TK			
%token	DOUBLE_TK		ELSE_TK 		ENUM_TK 		EXTERN_TK 		
%token	FLOAT_TK 		FOR_TK 			GOTO_TK 		IF_TK 			
%token	INT_TK 			LONG_TK 		REGISTER_TK		RETURN_TK 
%token	SHORT_TK		SIGNED_TK		SIZEOF_TK		STATIC_TK
%token	STRUCT_TK		SWITCH_TK 		TYPEDEF_TK		UNION_TK
%token	UNSIGNED_TK		VOID_TK 		VOLATILE_TK		WHILE_TK

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
		{ 
			REDUCTION(translation_unit:external_declaration)
			$<astval>$ = $<astval>1;
			$<astval>$ = new translation_unit_astNode("", yylloc, &acTree);
			asTree.getRoot()->addChild($<astval>$);
			$<astval>$->addChild($<astval>1);
		}
	| translation_unit external_declaration					
		{ 
			REDUCTION(translation_unit:translation_unit external_declaration)
			$<astval>$ = $<astval>1;
			$<astval>$->addChild($<astval>2);
		/*	$<astval>$ = new astNode("translation_unit");
			ast.addChild($<astval>$);
			$<astval>$->addChild($<astval>2); */
		}
	;

external_declaration
	: function_definition 		
		{
			REDUCTION(external_declaration:function_definition)
		}
	| declaration					
		{
			REDUCTION(external_declaration:declaration)
		}
	;

function_definition
	: declarator compound_statement	
		{
			REDUCTION(function_definition:declarator compound_statement)
			$<astval>$ = new function_definition_astNode("declarator compound_statement", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
		}
	| declarator declaration_list compound_statement							
		{
			REDUCTION(function_definition:declarator declaration_list compound_statement)
			$<astval>$ = new function_definition_astNode("declarator declaration_list compound_statement", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	| declaration_specifiers declarator compound_statement						
		{
			REDUCTION(function_definition:declaration_specifiers declarator compound_statement)
			$<astval>$ = new function_definition_astNode("declaration_specifiers declarator compound_statement", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	| declaration_specifiers declarator declaration_list compound_statement		
		{
			REDUCTION(function_definition:declaration_specifiers declarator declaration_list compound_statement)
			$<astval>$ = new function_definition_astNode("declaration_specifiers declarator declaration_list compound_statement", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
		}
	;

declaration
	: declaration_specifiers SEMICOLON_TK
		{
			REDUCTION(declaration:declaration_specifiers SEMICOLON_TK)
			NvPcomp::BParser::error(yyloc, "SYNTAX ERROR: Declaration does not declare anything");
		}
	| declaration_specifiers init_declarator_list SEMICOLON_TK 	
		{
			REDUCTION(declaration:declaration_specifiers init_declarator_list SEMICOLON_TK)
			$<astval>$ = new declaration_astNode(":declaration_specifiers init_declarator_list SEMICOLON_TK", yylloc, &acTree);
			$<astval>$->addChild($<astval>1); // declaration_specifiers
			$<astval>$->addChild($<astval>2); // init_declarator_list
			// Assign Types to all declarations in the list
			for (int i=0; i < $<astval>2->getNumberOfChildren(); i++)
			{
			  std::string error;
			  init_declarator_astNode* node = (init_declarator_astNode*) $<astval>2->getChild(i);
			  
			  std::cout << "i =" << i << " Node: " << node->getString() << " of type " << node->getType() << std::endl;
			  std::cout << " Val 1: " << $<astval>1->getString() << " of type " << $<astval>1->getType() << std::endl;
			  
			  if (!node->setSpecifiers((declaration_specifiers_astNode*) $<astval>1, &table, &(asTree.getVariableTable()), error))
			    NvPcomp::BParser::error(yyloc, error);
			} 
		}
	;

declaration_list
	: declaration
		{
			REDUCTION(declaration_list:declaration)
		}
	| declaration_list declaration								
		{
			REDUCTION(declaration_list:declaration_list declaration)
		/*	$<astval>$ = new astNode("declaration_list");
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2); */
		}
	;

declaration_specifiers
	: storage_class_specifier
		{
			REDUCTION(declaration_specifiers:storage_class_specifier)
			$<astval>$ = new declaration_specifiers_astNode("", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
		}
	| storage_class_specifier declaration_specifiers
		{
			REDUCTION(declaration_specifiers:storage_class_specifier declaration_specifiers)
		/*	$<astval>$ = new astNode("declaration_specifiers");
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2); */
			$<astval>$ = $<astval>2;
			$<astval>2->addChild($<astval>1);
		}
	| type_specifier
		{
			REDUCTION(declaration_specifiers:type_specifier)
			$<astval>$ = new declaration_specifiers_astNode("", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
		}
	| type_specifier declaration_specifiers						
		{
			REDUCTION(declaration_specifiers:type_specifier declaration_specifiers)
	/*		$<astval>$ = new astNode("declaration_specifiers");
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2); */
			$<astval>$ = $<astval>2;
			$<astval>2->addChild($<astval>1);
		}
	| type_qualifier
		{
			REDUCTION(declaration_specifiers:type_qualifier)
			$<astval>$ = new declaration_specifiers_astNode("", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
		}
	| type_qualifier declaration_specifiers
		{
			REDUCTION(declaration_specifiers:type_qualifier declaration_specifiers)
		/*	$<astval>$ = new astNode("declaration_specifiers");
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2); */
			$<astval>$ = $<astval>2;
			$<astval>2->addChild($<astval>1);
		}
	;

storage_class_specifier
	: AUTO_TK				
		{
			REDUCTION(storage_class_specifier:AUTO_TK)
		/*	$<astval>$ = new astNode("AUTO_TK", yylval.sval); */
	    }
	| REGISTER_TK			
		{
			REDUCTION(storage_class_specifier:REGISTER_TK)
        /*    $<astval>$ = new astNode("REGISTER_TK", yylval.sval); */
	    }
	| STATIC_TK
		{
			REDUCTION(storage_class_specifier:STATIC_TK)
       /*     $<astval>$ = new astNode("STATIC_TK", yylval.sval); */
	    }
	| EXTERN_TK
		{
			REDUCTION(storage_class_specifier:EXTERN_TK)
        /*    $<astval>$ = new astNode("EXTERN_TK", yylval.sval); */
	    }
	| TYPEDEF_TK
		{
			REDUCTION(storage_class_specifier:TYPEDEF_TK)
	  /*      $<astval>$ = new astNode("TYPEDEF_TK", yylval.sval); */
	    }
	;

type_specifier
	: VOID_TK
		{
			REDUCTION(type_specifier:VOID_TK)

		/*	$<astval>$ = new astNode("VOID_TK", yylval.sval); */


		}
	| CHAR_TK
		{
			REDUCTION(type_specifier:CHAR_TK)

		/*	$<astval>$ = new astNode("CHAR_TK", yylval.sval); */
		}
	| SHORT_TK
		{
			REDUCTION(type_specifier:SHORT_TK)

		/*	$<astval>$ = new astNode("SHORT_TK", yylval.sval); */

		}
	| INT_TK
		{
			REDUCTION(type_specifier:INT_TK)

		/*	$<astval>$ = new astNode("INT_TK", yylval.sval); */

		}
	| LONG_TK
		{
			REDUCTION(type_specifier:LONG_TK)

		/*	$<astval>$ = new astNode("LONG_TK", yylval.sval); */

		}
	| FLOAT_TK
		{
			REDUCTION(type_specifier:FLOAT_TK)

		/*	$<astval>$ = new astNode("FLOAT_TK", yylval.sval); */

		}
	| DOUBLE_TK
		{
			REDUCTION(type_specifier:DOUBLE_TK)

		/*	$<astval>$ = new astNode("DOUBLE_TK", yylval.sval); */

		}
	| SIGNED_TK
		{
			REDUCTION(type_specifier:SIGNED_TK)

		/*	$<astval>$ = new astNode("SIGNED_TK", yylval.sval); */

		}
	| UNSIGNED_TK
		{
			REDUCTION(type_specifier:UNSIGNED_TK)

		}
	| struct_or_union_specifier			
		{
			REDUCTION(type_specifier:struct_or_union_specifier)
		}
	| enum_specifier
		{
			REDUCTION(type_specifier:enum_specifier)
		}
	| TYPEDEF_NAME_TK
		{
			REDUCTION(type_specifier:TYPEDEF_NAME_TK)			
		}
	;

type_qualifier
	: CONST_TK							
		{
			REDUCTION(type_qualifier:CONST_TK)
			//~ $<astval>$ = new type_qualifier_astNode(":CONST_TK", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| VOLATILE_TK
		{
			REDUCTION(type_qualifier:VOLATILE_TK)
			//~ $<astval>$ = new type_qualifier_astNode(":VOLATILE_TK", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	;

struct_or_union_specifier
	: struct_or_union identifier OPEN_BRACE_TK scope_push struct_declaration_list CLOSE_BRACE_TK
		{
			REDUCTION(struct_or_union_specifier:struct_or_union identifier OPEN_BRACE_TK scope_push struct_declaration_list CLOSE_BRACE_TK); 
			SCOPE_POP();
			$<astval>$ = new struct_or_union_specifier_astNode(":struct_or_union identifier OPEN_BRACE_TK scope_push struct_declaration_list CLOSE_BRACE_TK", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
			$<astval>$->addChild($<astval>5);
			$<astval>$->addChild($<astval>6);
		}	
	| struct_or_union OPEN_BRACE_TK scope_push struct_declaration_list CLOSE_BRACE_TK
		{
			REDUCTION(struct_or_union_specifier:struct_or_union OPEN_BRACE_TK scope_push struct_declaration_list CLOSE_BRACE_TK) 
			SCOPE_POP();
			$<astval>$ = new struct_or_union_specifier_astNode(":struct_or_union OPEN_BRACE_TK scope_push struct_declaration_list CLOSE_BRACE_TK", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
			$<astval>$->addChild($<astval>5);
		}
	| struct_or_union identifier
		{
			REDUCTION(struct_or_union_specifier:struct_or_union identifier)
			$<astval>$ = new struct_or_union_specifier_astNode(":struct_or_union identifier", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
		}
	;

struct_or_union
	: STRUCT_TK
		{
			REDUCTION(struct_or_union:STRUCT_TK)
			//~ $<astval>$ = new struct_or_union_astNode(":STRUCT_TK", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| UNION_TK
		{
			REDUCTION(struct_or_union:UNION_TK)
			//~ $<astval>$ = new struct_or_union_astNode(":UNION_TK", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	;

struct_declaration_list
	: struct_declaration
		{
			REDUCTION(struct_declaration_list:struct_declaration)
			//~ $<astval>$ = new struct_declaration_list_astNode(":struct_declaration", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| struct_declaration_list struct_declaration
		{
			REDUCTION(struct_declaration_list:struct_declaration_list struct_declaration)
			$<astval>$ = new struct_declaration_list_astNode(":struct_declaration_list struct_declaration", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
		}
	;

init_declarator_list
	: init_declarator
		{
			REDUCTION(init_declarator_list:init_declarator)
			//~ $<astval>$ = new init_declarator_list_astNode("", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| init_declarator_list COMMA_TK init_declarator
		{
			REDUCTION(init_declarator_list:init_declarator_list COMMA_TK init_declarator)
			$<astval>$ = $<astval>1;
			$<astval>1->addChild($<astval>3);
		}
	;

init_declarator
	: declarator							
		{
			REDUCTION(init_declarator:declarator)
			//~ $<astval>$ = new init_declarator_astNode(":declarator", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| declarator EQUAL_TK initializer		
		{
			REDUCTION(init_declarator:declarator EQUAL_TK initializer)
			//~ $<astval>$ = new init_declarator_astNode(":declarator EQUAL_TK initializer", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
			//~ $<astval>$->addChild($<astval>3);
		}
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list SEMICOLON_TK		
		{
			REDUCTION(struct_declaration:specifier_qualifier_list struct_declarator_list SEMICOLON_TK)
			$<astval>$ = new struct_declaration_astNode("specifier_qualifier_list struct_declarator_list SEMICOLON_TK", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	;

specifier_qualifier_list
	: type_specifier
		{
			REDUCTION(specifier_qualifier_list:type_specifier)
			//~ $<astval>$ = new specifier_qualifier_list_astNode("type_specifier", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| type_specifier specifier_qualifier_list
		{
			REDUCTION(specifier_qualifier_list:type_specifier specifier_qualifier_list)
			$<astval>$ = new specifier_qualifier_list_astNode("type_specifier specifier_qualifier_list", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
		}
	| type_qualifier
		{
			REDUCTION(specifier_qualifier_list:type_qualifier)
			//~ $<astval>$ = new specifier_qualifier_list_astNode("type_qualifier", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| type_qualifier specifier_qualifier_list
		{
			REDUCTION(specifier_qualifier_list:type_qualifier specifier_qualifier_list)
			$<astval>$ = new specifier_qualifier_list_astNode("type_qualifier specifier_qualifier_list", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
		}
	;

struct_declarator_list
	: struct_declarator
		{
			REDUCTION(struct_declarator_list:struct_declarator)
			//~ $<astval>$ = new struct_declarator_list_astNode("struct_declarator", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| struct_declarator_list COMMA_TK struct_declarator
		{
			REDUCTION(struct_declarator_list:struct_declarator_list COMMA_TK struct_declarator)
			$<astval>$ = new struct_declarator_list_astNode("struct_declarator_list COMMA_TK struct_declarator", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	;

struct_declarator
	: declarator
		{
			REDUCTION(struct_declarator:declarator)
			//~ $<astval>$ = new struct_declarator_astNode("declarator", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| COLON_TK constant_expression
		{
			REDUCTION(struct_declarator:COLON_TK constant_expression)
			$<astval>$ = new struct_declarator_astNode("COLON_TK constant_expression", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
		}
	| declarator COLON_TK constant_expression
		{
			REDUCTION(struct_declarator:declarator COLON_TK constant_expression)
			$<astval>$ = new struct_declarator_astNode("declarator COLON_TK constant_expression", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	;

enum_specifier
	: ENUM_TK OPEN_BRACE_TK scope_push	enumerator_list CLOSE_BRACE_TK
		{
			REDUCTION(enum_specifier:ENUM_TK OPEN_BRACE_TK enumerator_list CLOSE_BRACE_TK); 
			SCOPE_POP();
			$<astval>$ = new enum_specifier_astNode("ENUM_TK OPEN_BRACE_TK enumerator_list CLOSE_BRACE_TK", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
		}
	| ENUM_TK identifier OPEN_BRACE_TK scope_push enumerator_list CLOSE_BRACE_TK
		{
			REDUCTION(enum_specifier:ENUM_TK identifier OPEN_BRACE_TK enumerator_list CLOSE_BRACE_TK); 
			SCOPE_POP();
			$<astval>$ = new enum_specifier_astNode("ENUM_TK identifier OPEN_BRACE_TK enumerator_list CLOSE_BRACE_TK", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
			$<astval>$->addChild($<astval>5);
		}
	| ENUM_TK identifier
		{
			REDUCTION(enum_specifier:)
			$<astval>$ = new enum_specifier_astNode("identifier", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
		}
	;

enumerator_list
	: enumerator
		{
			REDUCTION(enumerator_list:enumerator)
			//~ $<astval>$ = new enumerator_list_astNode("enumerator", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| enumerator_list COMMA_TK enumerator
		{
			REDUCTION(enumerator_list:enumerator_list COMMA_TK enumerator)
			$<astval>$ = new enumerator_list_astNode("enumerator_list COMMA_TK enumerator", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	;

enumerator
	: identifier
		{
			REDUCTION(enumerator:identifier)
			//~ $<astval>$ = new enumerator_astNode("identifier", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| identifier EQUAL_TK constant_expression
		{
			REDUCTION(enumerator:identifier EQUAL_TK constant_expression)
			$<astval>$ = new enumerator_astNode("identifier EQUAL_TK constant_expression", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	;

declarator
	: direct_declarator
		{
			REDUCTION(declarator:direct_declarator)
			//~ $<astval>$ = new declarator_astNode(":direct_declarator", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| pointer direct_declarator
		{
			REDUCTION(declarator:pointer direct_declarator)
			$<astval>$ = new declarator_astNode(":pointer direct_declarator", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
		}
	;

direct_declarator
	: identifier
		{
			REDUCTION(direct_declarator:identifier)
			//~ $<astval>$ = new direct_declarator_astNode("identifier", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| OPEN_PAREN_TK declarator CLOSE_PAREN_TK
		{
			REDUCTION(direct_declarator:OPEN_PAREN_TK declarator CLOSE_PAREN_TK)
			$<astval>$ = new direct_declarator_astNode("OPEN_PAREN_TK declarator CLOSE_PAREN_TK", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	| direct_declarator OPEN_BRACK_TK CLOSE_BRACK_TK
		{
			REDUCTION(direct_declarator:direct_declarator OPEN_BRACK_TK CLOSE_BRACK_TK)
			$<astval>$ = new direct_declarator_astNode("direct_declarator OPEN_BRACK_TK CLOSE_BRACK_TK", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	| direct_declarator OPEN_BRACK_TK constant_expression CLOSE_BRACK_TK		
		{
			REDUCTION(direct_declarator:direct_declarator OPEN_BRACK_TK constant_expression CLOSE_BRACK_TK)
			$<astval>$ = new direct_declarator_astNode("direct_declarator OPEN_BRACK_TK constant_expression CLOSE_BRACK_TK", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
		}
	| direct_declarator OPEN_PAREN_TK CLOSE_PAREN_TK
		{
			REDUCTION(direct_declarator:direct_declarator OPEN_PAREN_TK CLOSE_PAREN_TK)
			$<astval>$ = new direct_declarator_astNode("direct_declarator OPEN_PAREN_TK CLOSE_PAREN_TK", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	| direct_declarator OPEN_PAREN_TK parameter_type_list CLOSE_PAREN_TK
		{
			REDUCTION(direct_declarator:direct_declarator OPEN_PAREN_TK parameter_type_list CLOSE_PAREN_TK)
			$<astval>$ = new direct_declarator_astNode("direct_declarator OPEN_PAREN_TK parameter_type_list CLOSE_PAREN_TK", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
		}
	| direct_declarator OPEN_PAREN_TK identifier_list CLOSE_PAREN_TK
		{
			REDUCTION(direct_declarator:direct_declarator OPEN_PAREN_TK identifier_list CLOSE_PAREN_TK)
			$<astval>$ = new direct_declarator_astNode("direct_declarator OPEN_PAREN_TK identifier_list CLOSE_PAREN_TK", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
		}
	;

pointer
	: STAR_TK									
		{
			REDUCTION(pointer:STAR_TK)
			$<astval>$ = new pointer_astNode("", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
		}
	| STAR_TK type_qualifier_list
		{
			REDUCTION(pointer:STAR_TK type_qualifier_list)
			$<astval>$ = $<astval>2;
			$<astval>$->addChild($<astval>1);
		}
	| STAR_TK pointer
		{
			REDUCTION(pointer:STAR_TK pointer)
			$<astval>$ = $<astval>2;
			$<astval>$->addChild($<astval>1);
		}
	| STAR_TK type_qualifier_list pointer
		{
			REDUCTION(pointer:STAR_TK type_qualifier_list pointer)
			$<astval>$ = $<astval>3;
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>1);
		}
	;

type_qualifier_list
	: type_qualifier							
		{
			REDUCTION(type_qualifier_list:type_qualifier)
			$<astval>$ = new type_qualifier_list_astNode(":type_qualifier", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
		}
	| type_qualifier_list type_qualifier
		{
			REDUCTION(type_qualifier_list:type_qualifier_list type_qualifier)
			$<astval>$ = $<astval>1;
			$<astval>$->addChild($<astval>2);
		}
	;

parameter_type_list
	: parameter_list
		{
			REDUCTION(parameter_type_list:parameter_list)
			//~ $<astval>$ = new parameter_type_list_astNode("parameter_list", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| parameter_list COMMA_TK ELIPSIS_TK
		{
			REDUCTION(parameter_type_list:parameter_list COMMA_TK ELIPSIS_TK)
			$<astval>$ = new parameter_type_list_astNode("parameter_list COMMA_TK ELIPSIS_TK", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	;

parameter_list
	: parameter_declaration
		{
			REDUCTION(parameter_list:parameter_declaration)
			//~ $<astval>$ = new parameter_list_astNode("parameter_declaration", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| parameter_list COMMA_TK parameter_declaration
		{
			REDUCTION(parameter_list:parameter_list COMMA_TK parameter_declaration)
			$<astval>$ = new parameter_list_astNode("parameter_list COMMA_TK parameter_declaration", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	;

parameter_declaration
	: declaration_specifiers declarator
		{
			REDUCTION(parameter_declaration:declaration_specifiers declarator)
			$<astval>$ = new parameter_declaration_astNode("declaration_specifiers declarator", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
		}
	| declaration_specifiers
		{
			REDUCTION(parameter_declaration:declaration_specifiers)
			//~ $<astval>$ = new parameter_declaration_astNode("declaration_specifiers", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| declaration_specifiers abstract_declarator
		{
			REDUCTION(parameter_declaration:declaration_specifiers abstract_declarator)
			$<astval>$ = new parameter_declaration_astNode("declaration_specifiers abstract_declarator", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
		}
	;

identifier_list
	: identifier
		{
			REDUCTION(identifier_list:identifier)
			//~ $<astval>$ = new identifier_list_astNode("identifier", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| identifier_list COMMA_TK identifier
		{
			REDUCTION(identifier_list:identifier_list COMMA_TK identifier)
			$<astval>$ = new identifier_list_astNode("identifier_list COMMA_TK identifier", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	;

initializer
	: assignment_expression
		{
			REDUCTION(initializer:assignment_expression)
			//~ $<astval>$ = new initializer_astNode("assignment_expression", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| OPEN_BRACE_TK scope_push initializer_list CLOSE_BRACE_TK
		{
			REDUCTION(initializer:OPEN_BRACE_TK initializer_list CLOSE_BRACE_TK); 
			SCOPE_POP();
			$<astval>$ = new initializer_astNode("OPEN_BRACE_TK initializer_list CLOSE_BRACE_TK", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	| OPEN_BRACE_TK scope_push initializer_list COMMA_TK CLOSE_BRACE_TK	
		{
			REDUCTION(initializer:OPEN_BRACE_TK initializer_list COMMA_TK CLOSE_BRACE_TK); 
			SCOPE_POP();
			$<astval>$ = new initializer_astNode("OPEN_BRACE_TK initializer_list COMMA_TK CLOSE_BRACE_TK", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
		}
	;

initializer_list
	: initializer
		{
			REDUCTION(initializer_list:initializer)
			//~ $<astval>$ = new initializer_list_astNode("initializer", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| initializer_list COMMA_TK initializer
		{
			REDUCTION(initializer_list:initializer_list COMMA_TK initializer)
			$<astval>$ = new initializer_list_astNode("initializer_list COMMA_TK initializer", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	;

type_name
	: specifier_qualifier_list
		{
			REDUCTION(type_name:specifier_qualifier_list)
			//~ $<astval>$ = new type_name_astNode("specifier_qualifier_list", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| specifier_qualifier_list abstract_declarator
		{
			REDUCTION(type_name:specifier_qualifier_list abstract_declarator)
			$<astval>$ = new type_name_astNode("specifier_qualifier_list abstract_declarator", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
		}
	;

abstract_declarator
	: pointer
		{
			REDUCTION(abstract_declarator:pointer)
			//~ $<astval>$ = new abstract_declarator_astNode("pointer", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| direct_abstract_declarator
		{
			REDUCTION(abstract_declarator:direct_abstract_declarator)
			//~ $<astval>$ = new abstract_declarator_astNode("direct_abstract_declarator", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| pointer direct_abstract_declarator
		{
			REDUCTION(abstract_declarator:pointer direct_abstract_declarator)
			$<astval>$ = new abstract_declarator_astNode("pointer direct_abstract_declarator", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
		}
	;

direct_abstract_declarator
	: OPEN_PAREN_TK abstract_declarator CLOSE_PAREN_TK
		{
			REDUCTION(direct_abstract_declarator:OPEN_PAREN_TK abstract_declarator CLOSE_PAREN_TK)
			$<astval>$ = new direct_abstract_declarator_astNode("OPEN_PAREN_TK abstract_declarator CLOSE_PAREN_TK", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	| OPEN_BRACK_TK CLOSE_BRACK_TK
		{
			REDUCTION(direct_abstract_declarator:OPEN_BRACK_TK CLOSE_BRACK_TK)
			$<astval>$ = new direct_abstract_declarator_astNode("OPEN_BRACK_TK CLOSE_BRACK_TK", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
		}
	| OPEN_BRACK_TK constant_expression CLOSE_BRACK_TK
		{
			REDUCTION(direct_abstract_declarator:OPEN_BRACK_TK constant_expression CLOSE_BRACK_TK)
			$<astval>$ = new direct_abstract_declarator_astNode("OPEN_BRACK_TK constant_expression CLOSE_BRACK_TK", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	| direct_abstract_declarator OPEN_BRACK_TK CLOSE_BRACK_TK
		{
			REDUCTION(direct_abstract_declarator:direct_abstract_declarator OPEN_BRACK_TK CLOSE_BRACK_TK)
			$<astval>$ = new direct_abstract_declarator_astNode("direct_abstract_declarator OPEN_BRACK_TK CLOSE_BRACK_TK", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	| direct_abstract_declarator OPEN_BRACK_TK constant_expression CLOSE_BRACK_TK
		{
			REDUCTION(direct_abstract_declarator:direct_abstract_declarator OPEN_BRACK_TK constant_expression CLOSE_BRACK_TK)
			$<astval>$ = new direct_abstract_declarator_astNode("direct_abstract_declarator OPEN_BRACK_TK constant_expression CLOSE_BRACK_TK", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
		}
	| OPEN_PAREN_TK CLOSE_PAREN_TK
		{
			REDUCTION(direct_abstract_declarator:OPEN_PAREN_TK CLOSE_PAREN_TK)
			$<astval>$ = new direct_abstract_declarator_astNode("OPEN_PAREN_TK CLOSE_PAREN_TK", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
		}
	| OPEN_PAREN_TK parameter_type_list CLOSE_PAREN_TK
		{
			REDUCTION(direct_abstract_declarator:OPEN_PAREN_TK parameter_type_list CLOSE_PAREN_TK)
			$<astval>$ = new direct_abstract_declarator_astNode("OPEN_PAREN_TK parameter_type_list CLOSE_PAREN_TK", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	| direct_abstract_declarator OPEN_PAREN_TK CLOSE_PAREN_TK
		{
			REDUCTION(direct_abstract_declarator:direct_abstract_declarator OPEN_PAREN_TK CLOSE_PAREN_TK)
			$<astval>$ = new direct_abstract_declarator_astNode("direct_abstract_declarator OPEN_PAREN_TK CLOSE_PAREN_TK", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	| direct_abstract_declarator OPEN_PAREN_TK parameter_type_list CLOSE_PAREN_TK
		{
			REDUCTION(direct_abstract_declarator:direct_abstract_declarator OPEN_PAREN_TK parameter_type_list CLOSE_PAREN_TK)
			$<astval>$ = new direct_abstract_declarator_astNode("direct_abstract_declarator OPEN_PAREN_TK parameter_type_list CLOSE_PAREN_TK", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
		}
	;

statement
	: labeled_statement
		{
			REDUCTION(statement:labeled_statement)
			//~ $<astval>$ = new statement_astNode("labeled_statement", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| compound_statement
		{
			REDUCTION(statement:compound_statement)
			//~ $<astval>$ = new statement_astNode("compound_statement", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| expression_statement
		{
			REDUCTION(statement:expression_statement)
			//~ $<astval>$ = new statement_astNode("expression_statement", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| selection_statement
		{
			REDUCTION(statement:selection_statement)
			//~ $<astval>$ = new statement_astNode("selection_statement", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| iteration_statement
		{
			REDUCTION(statement:iteration_statement)
			//~ $<astval>$ = new statement_astNode("iteration_statement", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);	
		}
	| jump_statement
		{
			REDUCTION(statement:jump_statement)
			//~ $<astval>$ = new statement_astNode("jump_statement", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);		
		}
	;

labeled_statement
	: identifier COLON_TK statement
		{
			REDUCTION(labeled_statement:identifier COLON_TK statement)
			$<astval>$ = new labeled_statement_astNode("identifier COLON_TK statement", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	| CASE_TK constant_expression COLON_TK statement
		{
			REDUCTION(labeled_statement:CASE_TK constant_expression COLON_TK statement)
			$<astval>$ = new labeled_statement_astNode("CASE_TK constant_expression COLON_TK statement", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
		}
	| DEFAULT_TK COLON_TK statement
		{
			REDUCTION(labeled_statement:DEFAULT_TK COLON_TK statement)
			$<astval>$ = new labeled_statement_astNode("DEFAULT_TK COLON_TK statement", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	;

expression_statement
	: SEMICOLON_TK
		{
			REDUCTION(expression_statement:SEMICOLON_TK) 
			//~ $<astval>$ = new expression_statement_astNode("SEMICOLON_TK", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| expression SEMICOLON_TK
		{
			REDUCTION(expression_statement:expression SEMICOLON_TK)
			//~ $<astval>$ = new expression_statement_astNode("expression SEMICOLON_TK", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
			//~ $<astval>$->addChild($<astval>2);
		}
	;

scope_push
   : {SCOPE_PUSH()}

compound_statement
	: OPEN_BRACE_TK scope_push CLOSE_BRACE_TK
		{
			REDUCTION(compound_statement:OPEN_BRACE_TK CLOSE_BRACE_TK); 
			SCOPE_POP();
			$<astval>$ = new compound_statement_astNode("OPEN_BRACE_TK sCLOSE_BRACE_TK", yylloc, &acTree);
			//$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
		}
	| OPEN_BRACE_TK scope_push statement_list CLOSE_BRACE_TK
		{
			REDUCTION(compound_statement:OPEN_BRACE_TK statement_list CLOSE_BRACE_TK); 
			SCOPE_POP()
			$<astval>$ = new compound_statement_astNode("OPEN_BRACE_TK statement_list CLOSE_BRACE_TK", yylloc, &acTree);
			//$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	| OPEN_BRACE_TK scope_push declaration_list CLOSE_BRACE_TK
		{
			REDUCTION(compound_statement:OPEN_BRACE_TK declaration_list CLOSE_BRACE_TK); 
			SCOPE_POP();
			$<astval>$ = new compound_statement_astNode("OPEN_BRACE_TK declaration_list CLOSE_BRACE_TK", yylloc, &acTree);
			//$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	| OPEN_BRACE_TK scope_push declaration_list statement_list CLOSE_BRACE_TK
		{
			REDUCTION(compound_statement:OPEN_BRACE_TK declaration_list statement_list CLOSE_BRACE_TK);
			SCOPE_POP();
			$<astval>$ = new compound_statement_astNode("OPEN_BRACE_TK declaration_list statement_list CLOSE_BRACE_TK", yylloc, &acTree);
			//$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
		}
	;

statement_list
	: statement
		{
			REDUCTION(statement_list:statement)
			//~ $<astval>$ = new statement_list_astNode("statement", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| statement_list statement
		{
			REDUCTION(statement_list:statement_list statement)
			$<astval>$ = new statement_list_astNode("statement_list statement", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
		}
	;

selection_statement
	: IF_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK statement
		{
			REDUCTION(selection_statement:IF_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK statement)
			$<astval>$ = new selection_statement_astNode("IF_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK statement", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
			$<astval>$->addChild($<astval>5);
		}
	| IF_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK statement ELSE_TK statement
		{
			REDUCTION(selection_statement:IF_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK statement ELSE_TK statement)
			$<astval>$ = new selection_statement_astNode("IF_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK statement ELSE_TK statement", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
			$<astval>$->addChild($<astval>5);
			$<astval>$->addChild($<astval>6);
			$<astval>$->addChild($<astval>7);
		}	
	| SWITCH_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK statement
		{
			REDUCTION(selection_statement:SWITCH_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK statement)
			$<astval>$ = new selection_statement_astNode("SWITCH_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK statement", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
			$<astval>$->addChild($<astval>5);
		}
	;

iteration_statement
	: WHILE_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK statement
		{
			REDUCTION(iteration_statement:WHILE_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK statement)
			$<astval>$ = new iteration_statement_astNode("WHILE_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK statement", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
			$<astval>$->addChild($<astval>5);    
	     }
	| DO_TK statement WHILE_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK SEMICOLON_TK
		{
			REDUCTION(iteration_statement:DO_TK statement WHILE_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK SEMICOLON_TK)
			$<astval>$ = new iteration_statement_astNode("DO_TK statement WHILE_TK OPEN_PAREN_TK expression CLOSE_PAREN_TK SEMICOLON_TK", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
			$<astval>$->addChild($<astval>5);
			$<astval>$->addChild($<astval>6);
			$<astval>$->addChild($<astval>7);
	     }

	| FOR_TK OPEN_PAREN_TK SEMICOLON_TK SEMICOLON_TK CLOSE_PAREN_TK statement
		{
			REDUCTION(iteration_statement:FOR_TK OPEN_PAREN_TK SEMICOLON_TK SEMICOLON_TK CLOSE_PAREN_TK statement)
			$<astval>$ = new iteration_statement_astNode("FOR_TK OPEN_PAREN_TK SEMICOLON_TK SEMICOLON_TK CLOSE_PAREN_TK statement", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
			$<astval>$->addChild($<astval>5);
			$<astval>$->addChild($<astval>6);    
	    }
	| FOR_TK OPEN_PAREN_TK SEMICOLON_TK SEMICOLON_TK expression CLOSE_PAREN_TK statement							
		{
			REDUCTION(iteration_statement:FOR_TK OPEN_PAREN_TK SEMICOLON_TK SEMICOLON_TK expression CLOSE_PAREN_TK statement)
			$<astval>$ = new iteration_statement_astNode("FOR_TK OPEN_PAREN_TK SEMICOLON_TK SEMICOLON_TK expression CLOSE_PAREN_TK statement", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
			$<astval>$->addChild($<astval>5);
			$<astval>$->addChild($<astval>6);
			$<astval>$->addChild($<astval>7);
         }
	| FOR_TK OPEN_PAREN_TK SEMICOLON_TK expression SEMICOLON_TK CLOSE_PAREN_TK statement
		{
			REDUCTION(iteration_statement:FOR_TK OPEN_PAREN_TK SEMICOLON_TK expression SEMICOLON_TK CLOSE_PAREN_TK statement)
			$<astval>$ = new iteration_statement_astNode("FOR_TK OPEN_PAREN_TK SEMICOLON_TK expression SEMICOLON_TK CLOSE_PAREN_TK statement", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
			$<astval>$->addChild($<astval>5);
			$<astval>$->addChild($<astval>6);
			$<astval>$->addChild($<astval>7);
         }
	| FOR_TK OPEN_PAREN_TK SEMICOLON_TK expression SEMICOLON_TK expression CLOSE_PAREN_TK statement
		{
			REDUCTION(iteration_statement:FOR_TK OPEN_PAREN_TK SEMICOLON_TK expression SEMICOLON_TK expression CLOSE_PAREN_TK statement)
			$<astval>$ = new iteration_statement_astNode("FOR_TK OPEN_PAREN_TK SEMICOLON_TK expression SEMICOLON_TK expression CLOSE_PAREN_TK statement", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
			$<astval>$->addChild($<astval>5);
			$<astval>$->addChild($<astval>6);
			$<astval>$->addChild($<astval>7);
			$<astval>$->addChild($<astval>8);
         }
	| FOR_TK OPEN_PAREN_TK expression SEMICOLON_TK SEMICOLON_TK CLOSE_PAREN_TK statement
		{
			REDUCTION(iteration_statement:FOR_TK OPEN_PAREN_TK expression SEMICOLON_TK SEMICOLON_TK CLOSE_PAREN_TK statement)
			$<astval>$ = new iteration_statement_astNode("FOR_TK OPEN_PAREN_TK expression SEMICOLON_TK SEMICOLON_TK CLOSE_PAREN_TK statement", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
			$<astval>$->addChild($<astval>5);
			$<astval>$->addChild($<astval>6);
			$<astval>$->addChild($<astval>7);
		}
	| FOR_TK OPEN_PAREN_TK expression SEMICOLON_TK SEMICOLON_TK expression CLOSE_PAREN_TK statement
		{
			REDUCTION(iteration_statement:FOR_TK OPEN_PAREN_TK expression SEMICOLON_TK expression SEMICOLON_TK CLOSE_PAREN_TK statement)
			$<astval>$ = new iteration_statement_astNode("FOR_TK OPEN_PAREN_TK expression SEMICOLON_TK expression SEMICOLON_TK CLOSE_PAREN_TK statement", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
			$<astval>$->addChild($<astval>5);
			$<astval>$->addChild($<astval>6);
			$<astval>$->addChild($<astval>7);
			$<astval>$->addChild($<astval>8);
         }
	| FOR_TK OPEN_PAREN_TK expression SEMICOLON_TK expression SEMICOLON_TK CLOSE_PAREN_TK statement
		{
			REDUCTION(iteration_statement:FOR_TK OPEN_PAREN_TK expression SEMICOLON_TK expression SEMICOLON_TK CLOSE_PAREN_TK statement)
			$<astval>$ = new iteration_statement_astNode("FOR_TK OPEN_PAREN_TK expression SEMICOLON_TK expression SEMICOLON_TK CLOSE_PAREN_TK statement", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
			$<astval>$->addChild($<astval>5);
			$<astval>$->addChild($<astval>6);
			$<astval>$->addChild($<astval>7);
			$<astval>$->addChild($<astval>8);
         }
	| FOR_TK OPEN_PAREN_TK expression SEMICOLON_TK expression SEMICOLON_TK expression CLOSE_PAREN_TK statement
		{
			REDUCTION(iteration_statement:FOR_TK OPEN_PAREN_TK expression SEMICOLON_TK expression SEMICOLON_TK expression CLOSE_PAREN_TK statement)
			$<astval>$ = new iteration_statement_astNode("FOR_TK OPEN_PAREN_TK expression SEMICOLON_TK expression SEMICOLON_TK expression CLOSE_PAREN_TK statement", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
			$<astval>$->addChild($<astval>5);
			$<astval>$->addChild($<astval>6);
			$<astval>$->addChild($<astval>7);
			$<astval>$->addChild($<astval>8);
			$<astval>$->addChild($<astval>9);
         }
	;

jump_statement
	: GOTO_TK identifier SEMICOLON_TK			
		{
			REDUCTION(jump_statement:GOTO_TK identifier SEMICOLON_TK)
			$<astval>$ = new jump_statement_astNode("GOTO_TK identifier SEMICOLON_TK", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}	          
	| CONTINUE_TK SEMICOLON_TK
		{
			REDUCTION(jump_statement:CONTINUE_TK SEMICOLON_TK)
			$<astval>$ = new jump_statement_astNode("CONTINUE_TK SEMICOLON_TK", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
		}
	| BREAK_TK SEMICOLON_TK
		{
			REDUCTION(jump_statement:BREAK_TK SEMICOLON_TK)
			$<astval>$ = new jump_statement_astNode("BREAK_TK SEMICOLON_TK", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
		}
	| RETURN_TK SEMICOLON_TK
		{
			REDUCTION(jump_statement:RETURN_TK SEMICOLON_TK)
			$<astval>$ = new jump_statement_astNode("RETURN_TK SEMICOLON_TK", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
		}
	| RETURN_TK expression SEMICOLON_TK
		{
			REDUCTION(jump_statement:RETURN_TK expression SEMICOLON_TK)
			$<astval>$ = new jump_statement_astNode("RETURN_TK expression SEMICOLON_TK", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	;

expression
	: assignment_expression
		{
			REDUCTION(expression:assignment_expression)
			//~ $<astval>$ = new expression_astNode("assignment_expression", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| expression COMMA_TK assignment_expression
		{
			REDUCTION(expression:expression COMMA_TK assignment_expression)
			$<astval>$ = new expression_astNode("expression COMMA_TK assignment_expression", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	;

assignment_expression
	: conditional_expression
		{
			REDUCTION(assignment_expression:conditional_expression)
			//~ $<astval>$ = new assignment_expression_astNode("conditional_expression", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| unary_expression assignment_operator assignment_expression
		{
			REDUCTION(assignment_expression:unary_expression assignment_operator assignment_expression)
			expression_astNode *tempNode;
			$<astval>$ = new assignment_expression_astNode("unary_expression assignment_operator assignment_expression", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			
			tempNode = (expression_astNode *) $<astval>$;
			
			if(!tempNode->checkType(&table)) {
				///ToDo: Add more useful error messaging.
				NvPcomp::BParser::error(yyloc, "Type mismatch");
			}
			
		}
	;

assignment_operator
	: EQUAL_TK
		{
			REDUCTION(assignment_operator:EQUAL_TK)
/*	   		$<astval>$ = new assignment_operator_astNode(":=", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);*/
		}
	| MUL_ASSIGN_TK
		{
			REDUCTION(assignment_operator:MUL_ASSIGN_TK)
/*			$<astval>$ = new assignment_operator_astNode(":*=", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);*/
		}
	| DIV_ASSIGN_TK
		{
			REDUCTION(assignment_operator:DIV_ASSIGN_TK)
/*			$<astval>$ = new assignment_operator_astNode(":/=", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);*/
		}
	| MOD_ASSIGN_TK
		{
			REDUCTION(assignment_operator:MOD_ASSIGN_TK)
/*			$<astval>$ = new assignment_operator_astNode(":%=", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);*/
		}
	| ADD_ASSIGN_TK
		{
			REDUCTION(assignment_operator:ADD_ASSIGN_TK)
/* 			$<astval>$ = new assignment_operator_astNode(":+=", yylloc, &acTree);
 			$<astval>$->addChild($<astval>1);*/
		}
	| SUB_ASSIGN_TK
		{
			REDUCTION(assignment_operator:SUB_ASSIGN_TK)
/*			$<astval>$ = new assignment_operator_astNode(":-=", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);*/
		}
	| LEFT_ASSIGN_TK
		{
			REDUCTION(assignment_operator:LEFT_ASSIGN_TK)
/*			$<astval>$ = new assignment_operator_astNode(":<=", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);*/
		}
	| RIGHT_ASSIGN_TK
		{
			REDUCTION(assignment_operator:RIGHT_ASSIGN_TK)
/*			$<astval>$ = new assignment_operator_astNode(":>=", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);*/
		}
	| AND_ASSIGN_TK
		{
			REDUCTION(assignment_operator:AND_ASSIGN_TK)
/*			$<astval>$ = new assignment_operator_astNode(":&=", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);*/
		}
	| XOR_ASSIGN_TK
		{
			REDUCTION(assignment_operator:XOR_ASSIGN_TK)
/*			$<astval>$ = new assignment_operator_astNode(":^=", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);*/
		}
	| OR_ASSIGN_TK
		{
			REDUCTION(assignment_operator:OR_ASSIGN_TK)
/*			$<astval>$ = new assignment_operator_astNode(":|=", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);*/
		}
	;

conditional_expression
	: logical_or_expression
		{
			REDUCTION(conditional_expression:logical_or_expression)
			//~ $<astval>$ = new conditional_expression_astNode(":conditional_expression", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| logical_or_expression QUESTION_TK expression COLON_TK conditional_expression
		{
			REDUCTION(conditional_expression:logical_or_expression QUESTION_TK expression COLON_TK conditional_expression)
			$<astval>$ = new conditional_expression_astNode(":logical_or_expression ? expression : conditional_expression", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
			$<astval>$->addChild($<astval>5);
		}
	;

constant_expression
	: conditional_expression
		{
			REDUCTION(constant_expression:conditional_expression)
			//~ $<astval>$ = new constant_expression_astNode(":conditional_expression", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
			
		}
	;

logical_or_expression
	: logical_and_expression
		{
			REDUCTION(logical_or_expression:logical_and_expression)
			//~ $<astval>$ = new logical_or_expression_astNode(":logical_and_expression", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| logical_or_expression OR_OP_TK logical_and_expression
		{
			REDUCTION(logical_or_expression:logical_or_expression OR_OP_TK logical_and_expression)
			$<astval>$ = new logical_or_expression_astNode(":logical_or_expression AND_OP_TK logical_and_expression", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	;

logical_and_expression
	: inclusive_or_expression
		{
			REDUCTION(logical_and_expression:inclusive_or_expression)
			//~ $<astval>$ = new logical_and_expression_astNode(":inclusive_or_expression", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| logical_and_expression AND_OP_TK inclusive_or_expression
		{
			REDUCTION(logical_and_expression:logical_and_expression AND_OP_TK inclusive_or_expression)
			$<astval>$ = new logical_and_expression_astNode(":logical_and_expression AND_OP_TK inclusive_or_expression", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	;

inclusive_or_expression
	: exclusive_or_expression
		{
			REDUCTION(inclusive_or_expression:exclusive_or_expression)
			//~ $<astval>$ = new inclusive_or_expression_astNode(":inclusive_or_expression", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| inclusive_or_expression BIT_OR_TK exclusive_or_expression
		{
			REDUCTION(inclusive_or_expression:inclusive_or_expression BIT_OR_TK exclusive_or_expression)
			$<astval>$ = new inclusive_or_expression_astNode(":inclusive_or_expression BIT_OR_TK exclusive_or_expression", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	;

exclusive_or_expression
	: and_expression
		{
			REDUCTION(exclusive_or_expression:and_expression)
			//~ $<astval>$ = new exclusive_or_expression_astNode(":and_expression", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| exclusive_or_expression BIT_XOR_TK and_expression
		{
			REDUCTION(exclusive_or_expression:exclusive_or_expression BIT_XOR_TK and_expression)
			$<astval>$ = new exclusive_or_expression_astNode(":exclusive_or_expression ^ and_expression", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	;

and_expression
	: equality_expression
		{
			REDUCTION(and_expression:equality_expression)
			//~ $<astval>$ = new and_expression_astNode(":equality_expression", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| and_expression BIT_AND_TK equality_expression
		{
			REDUCTION(and_expression:and_expression BIT_AND_TK equality_expression)
			$<astval>$ = new and_expression_astNode(":and_expression & equality_expression", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	;

equality_expression
	: relational_expression
		{
			REDUCTION(equality_expression:relational_expression)
			//~ $<astval>$ = new equality_expression_astNode(":relational_expression", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| equality_expression EQ_OP_TK relational_expression
		{
			REDUCTION(equality_expression:equality_expression EQ_OP_TK relational_expression)
			$<astval>$ = new equality_expression_astNode(":equality_expression == relational_expression", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	| equality_expression NE_OP_TK relational_expression
		{
			REDUCTION(equality_expression:equality_expression NE_OP_TK relational_expression)
			$<astval>$ = new equality_expression_astNode(":equality_expression != relational_expression", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	;

relational_expression
	: shift_expression
		{
			REDUCTION(relational_expression:shift_expression)
			//~ $<astval>$ = new relational_expression_astNode(":shift_expression", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| relational_expression LT_TK shift_expression
		{
			REDUCTION(relational_expression:relational_expression LT_TK shift_expression)
			$<astval>$ = new relational_expression_astNode(":relational_expression < shift_expression", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	| relational_expression GT_TK shift_expression
		{
			REDUCTION(relational_expression:relational_expression GT_TK shift_expression)
			$<astval>$ = new relational_expression_astNode(":relational_expression > shift_expression", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	| relational_expression LE_OP_TK shift_expression
		{
			REDUCTION(relational_expression:relational_expression LE_OP_TK shift_expression)
			$<astval>$ = new relational_expression_astNode(":relational_expression <= shift_expression", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	| relational_expression GE_OP_TK shift_expression
		{
			REDUCTION(relational_expression:relational_expression GE_OP_TK shift_expression)
			$<astval>$ = new relational_expression_astNode(":relational_expression >= shift_expression", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	;

shift_expression
	: additive_expression
		{
			REDUCTION(shift_expression:additive_expression)
			//~ $<astval>$ = new shift_expression_astNode(":additive_expression", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| shift_expression LEFT_OP_TK additive_expression
		{
			REDUCTION(shift_expression:shift_expression LEFT_OP_TK additive_expression)
			$<astval>$ = new shift_expression_astNode(":shift_expression << additive_expression", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);			
		}
	| shift_expression RIGHT_OP_TK additive_expression
		{
			REDUCTION(shift_expression:shift_expression RIGHT_OP_TK additive_expression)
			$<astval>$ = new shift_expression_astNode(":shift_expression >> additive_expression", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	;

additive_expression
	: multiplicative_expression
		{
			REDUCTION(additive_expression:multiplicative_expression)
			//~ $<astval>$ = new additive_expression_astNode(":multiplicative_expression", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| additive_expression PLUS_TK multiplicative_expression				
		{
			REDUCTION(additive_expression:additive_expression PLUS_TK multiplicative_expression)
			$<astval>$ = new additive_expression_astNode(":additive_expression + multiplicative_expression", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	| additive_expression MINUS_TK multiplicative_expression
		{
			REDUCTION(additive_expression:additive_expression MINUS_TK multiplicative_expression)
			$<astval>$ = new additive_expression_astNode(":additive_expression - multiplicative_expression", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	;

multiplicative_expression
	: cast_expression
		{
			REDUCTION(multiplicative_expression:cast_expression)
			//~ $<astval>$ = new multiplicative_expression_astNode(":cast_expression", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| multiplicative_expression STAR_TK cast_expression
		{
			REDUCTION(multiplicative_expression:multiplicative_expression STAR_TK cast_expression)
			$<astval>$ = new multiplicative_expression_astNode(":* cast_expression", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	| multiplicative_expression DIV_TK cast_expression					
		{
			REDUCTION(multiplicative_expression:multiplicative_expression DIV_TK cast_expression)
			$<astval>$ = new multiplicative_expression_astNode(":/ cast_expression", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		} 
	| multiplicative_expression MOD_TK cast_expression
		{
			REDUCTION(multiplicative_expression:multiplicative_expression MOD_TK cast_expression)
			$<astval>$ = new multiplicative_expression_astNode(":% cast_expression", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	;

cast_expression
	: unary_expression
		{
			REDUCTION(cast_expression:unary_expression)
			//~ $<astval>$ = new cast_expression_astNode(":cast_expression", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| OPEN_PAREN_TK type_name CLOSE_PAREN_TK cast_expression
		{
			REDUCTION(cast_expression:OPEN_PAREN_TK type_name CLOSE_PAREN_TK cast_expression)
			$<astval>$ = new cast_expression_astNode(":cast_expression ( type name ) cast_expression", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
		}
	;

unary_expression
	: postfix_expression
		{
			REDUCTION(unary_expression:postfix_expression)
			//~ $<astval>$ = new unary_expression_astNode(":postfix_expression", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);			
		}
	| INC_OP_TK unary_expression
		{
			REDUCTION(unary_expression:INC_OP_TK unary_expression)
			$<astval>$ = new unary_expression_astNode(":++ unary_expression", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
		}
	| DEC_OP_TK unary_expression										
		{
			REDUCTION(unary_expression:DEC_OP_TK unary_expression)
			$<astval>$ = new unary_expression_astNode(":-- unary_expression", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);  
		}
	| unary_operator cast_expression
		{
			REDUCTION(unary_expression:unary_operator cast_expression)
	     	$<astval>$ = new unary_expression_astNode(":unary_operator cast_expression", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
		}
	| SIZEOF_TK unary_expression
		{
			REDUCTION(unary_expression:SIZEOF_TK unary_expression)
			$<astval>$ = new unary_expression_astNode(":sizeof unary_expression", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
		}
	| SIZEOF_TK OPEN_PAREN_TK type_name CLOSE_PAREN_TK
		{
			REDUCTION(unary_expression:SIZEOF_TK OPEN_PAREN_TK type_name CLOSE_PAREN_TK)
			$<astval>$ = new unary_expression_astNode(":sizeof ( type_name )", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
		}
	;

unary_operator
	: BIT_AND_TK
		{
			REDUCTION(unary_operator:BIT_AND_TK)
			//~ $<astval>$ = new unary_operator_astNode(":&", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| STAR_TK
		{
			REDUCTION(unary_operator:STAR_TK)
			//~ $<astval>$ = new unary_operator_astNode(":*", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| PLUS_TK
		{
			REDUCTION(unary_operator:PLUS_TK)
			//~ $<astval>$ = new unary_operator_astNode(":+", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| MINUS_TK
		{
			REDUCTION(unary_operator:MINUS_TK)
			//~ $<astval>$ = new unary_operator_astNode(":-", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| BIT_NOT_TK
		{
			REDUCTION(unary_operator:BIT_NOT_TK)
			//~ $<astval>$ = new unary_operator_astNode(":~", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| NOT_TK
		{
			REDUCTION(unary_operator:NOT_TK)
			//~ $<astval>$ = new unary_operator_astNode(":!", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	;

postfix_expression
	: primary_expression
		{
			REDUCTION(postfix_expression:primary_expression)
			//~ $<astval>$ = new postfix_expression_astNode(":primary_expression", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| postfix_expression OPEN_BRACK_TK expression CLOSE_BRACK_TK
		{
			REDUCTION(postfix_expression:postfix_expression OPEN_BRACK_TK expression CLOSE_BRACK_TK)
			$<astval>$ = new postfix_expression_astNode(":[ expression ]", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
		}
	| postfix_expression OPEN_PAREN_TK CLOSE_PAREN_TK
		{
			REDUCTION(postfix_expression:postfix_expression OPEN_PAREN_TK CLOSE_PAREN_TK)
			$<astval>$ = new postfix_expression_astNode(": ( )", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
		}
	| postfix_expression OPEN_PAREN_TK argument_expression_list CLOSE_PAREN_TK
		{
			REDUCTION(postfix_expression:postfix_expression OPEN_PAREN_TK argument_expression_list CLOSE_PAREN_TK)
			$<astval>$ = new postfix_expression_astNode(":argument_expression_list", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
			$<astval>$->addChild($<astval>4);
		}
	| postfix_expression PERIOD_TK identifier
		{
			REDUCTION(postfix_expression:postfix_expression PERIOD_TK identifier)
			$<astval>$ = new postfix_expression_astNode(":period_operator", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);	         
		}
	| postfix_expression PTR_OP_TK identifier
		{
			REDUCTION(postfix_expression:postfix_expression PTR_OP_TK identifier)
			$<astval>$ = new postfix_expression_astNode(":pointer_operator", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);     
		}
	| postfix_expression INC_OP_TK
		{
			REDUCTION(postfix_expression:postfix_expression INC_OP_TK)
			$<astval>$ = new postfix_expression_astNode(":increment_operator", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);      
		}
	| postfix_expression DEC_OP_TK
		{
			REDUCTION(postfix_expression:postfix_expression DEC_OP_TK)
			$<astval>$ = new postfix_expression_astNode(":decrement_operator", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
		}
	;

primary_expression
	: identifier
		{
			REDUCTION(primary_expression:identifier)
			//~ $<astval>$ = new primary_expression_astNode(":identifier", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| constant
		{
			REDUCTION(primary_expression:constant)
			//~ $<astval>$ = new primary_expression_astNode(":constant", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);			
		}
	| string
		{
			REDUCTION(primary_expression:string)
			//~ $<astval>$ = new primary_expression_astNode(":string", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);			
		}
	| OPEN_PAREN_TK expression CLOSE_PAREN_TK
		{
			REDUCTION(primary_expression:OPEN_PAREN_TK expression CLOSE_PAREN_TK)
			$<astval>$ = new primary_expression_astNode(":expression", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	;

argument_expression_list
	: assignment_expression
		{
			REDUCTION(argument_expression_list:assignment_expression)
			//~ $<astval>$ = new argument_expression_list_astNode(":assignment_expression", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);	
		}
	| argument_expression_list COMMA_TK assignment_expression
		{
			REDUCTION(argument_expression_list:argument_expression_list COMMA_TK assignment_expression)
			$<astval>$ = new argument_expression_list_astNode(":assignment_expression_list", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);	
			$<astval>$->addChild($<astval>2);
			$<astval>$->addChild($<astval>3);
		}
	;

constant
	: INTEGER_CONSTANT_TK				
		{
			REDUCTION(constant:INTEGER_CONSTANT_TK)
			//~ $<astval>$ = new constant_astNode(":integer", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| CHARACTER_CONSTANT_TK
		{
			REDUCTION(constant:CHARACTER_CONSTANT_TK)
			//~ $<astval>$ = new constant_astNode(":character", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| FLOATING_CONSTANT_TK
		{
			REDUCTION(constant:FLOATING_CONSTANT_TK)
			//~ $<astval>$ = new constant_astNode(":float", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	| ENUMERATION_CONSTANT_TK
		{
			REDUCTION(constant:ENUMERATION_CONSTANT_TK)
			//~ $<astval>$ = new constant_astNode(":enumeration", yylloc, &acTree);
			//~ $<astval>$->addChild($<astval>1);
		}
	;

string
	: STRING_LITERAL_TK
		{
			REDUCTION(string:STRING_LITERAL_TK)
			$<astval>$ = new string_astNode(":string", yylloc, &acTree);
			$<astval>$->addChild($<astval>1);
		}
	;

identifier
	: IDENTIFIER_TK
		{
			REDUCTION(identifier:IDENTIFIER_TK)
			$<astval>$->setString(yylval.sval);
		/*	$<astval>$ = new astNode("IDENTIFIER_TK", yylval.sval); */

		}
	;

%%
/************************************************************************/
/* Code																	*/
/************************************************************************/
// Error Function Implementation
void NvPcomp::BParser::error(const NvPcomp::BParser::location_type &loc, const std::string &msg) {
	LOG(ERRORLog, logLEVEL1) << buffer.bufferGetLineNoCR(loc.begin.line, loc.end.line);
	LOG(ERRORLog, logLEVEL1) << std::string(loc.begin.column - 1, ' ') <<"^-Error: " << msg << ": at location: " << loc << std::endl;
}

// Declare the Scanner and implement the yylex function
#include "NvPcompScanner.h"
static int yylex(NvPcomp::BParser::semantic_type * yylval, NvPcomp::BParser::location_type *loc, NvPcomp::FlexScanner &scanner, NvPcomp::symTable &table, NvPcomp::tacTree &acTree) {
	return scanner.yylex(yylval,loc, &table, &acTree);
}
