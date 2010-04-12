/**********************************************************************/
//! Symbol table implementation for NvPcomp
/*!
 * \class symTable
 *
 * Description: The Symbol Table implementation for NvPcomp
 *
 * \author CMT, DRJ & BFB
 *
 */
/**********************************************************************/
#ifndef SYMTABLE_H_
#define SYMTABLE_H_

#include <symNode.h>
#include <string>
#include <vector>
#include <map>
#include <iterator>

// Logging line start
#define SYMLOG_START	"symTable: "

enum InsertResult {
	INSERT_SUCCESS,
	INSERT_SUCCESS_W_SHADOW,
	INSERT_FAIL_IN_CURRENT_LEVEL	
};

enum yytokentype {
  AUTO_TK = 258,
  BREAK_TK = 259,
  CASE_TK = 260,
  CHAR_TK = 261,
  CONST_TK = 262,
  CONTINUE_TK = 263,
  DEFAULT_TK = 264,
  DO_TK = 265,
  DOUBLE_TK = 266,
  ELSE_TK = 267,
  ENUM_TK = 268,
  EXTERN_TK = 269,
  FLOAT_TK = 270,
  FOR_TK = 271,
  GOTO_TK = 272,
  IF_TK = 273,
  INT_TK = 274,
  LONG_TK = 275,
  REGISTER_TK = 276,
  RETURN_TK = 277,
  SHORT_TK = 278,
  SIGNED_TK = 279,
  SIZEOF_TK = 280,
  STATIC_TK = 281,
  STRUCT_TK = 282,
  SWITCH_TK = 283,
  TYPEDEF_TK = 284,
  UNION_TK = 285,
  UNSIGNED_TK = 286,
  VOID_TK = 287,
  VOLATILE_TK = 288,
  WHILE_TK = 289,
  ERROR_TK = 290,
  RANGE_TK = 291,
  IDENTIFIER_TK = 292,
  INTEGER_CONSTANT_TK = 293,
  FLOATING_CONSTANT_TK = 294,
  CHARACTER_CONSTANT_TK = 295,
  ENUMERATION_CONSTANT_TK = 296,
  STRING_LITERAL_TK = 297,
  TYPEDEF_NAME_TK = 298,
  OPEN_BRACE_TK = 299,
  CLOSE_BRACE_TK = 300,
  OPEN_PAREN_TK = 301,
  CLOSE_PAREN_TK = 302,
  SEMICOLON_TK = 303,
  OPEN_BRACK_TK = 304,
  CLOSE_BRACK_TK = 305,
  COMMA_TK = 306,
  ELIPSIS_TK = 307,
  BIT_NOT_TK = 308,
  BIT_AND_TK = 309,
  BIT_OR_TK = 310,
  BIT_XOR_TK = 311,
  STAR_TK = 312,
  DIV_TK = 313,
  PLUS_TK = 314,
  MINUS_TK = 315,
  MOD_TK = 316,
  LT_TK = 317,
  LE_OP_TK = 318,
  GT_TK = 319,
  GE_OP_TK = 320,
  NOT_TK = 321,
  AND_OP_TK = 322,
  OR_OP_TK = 323,
  LEFT_OP_TK = 324,
  RIGHT_OP_TK = 325,
  EQUAL_TK = 326,
  ADD_ASSIGN_TK = 327,
  SUB_ASSIGN_TK = 328,
  MOD_ASSIGN_TK = 329,
  MUL_ASSIGN_TK = 330,
  DIV_ASSIGN_TK = 331,
  LEFT_ASSIGN_TK = 332,
  RIGHT_ASSIGN_TK = 333,
  AND_ASSIGN_TK = 334,
  XOR_ASSIGN_TK = 335,
  OR_ASSIGN_TK = 336,
  QUESTION_TK = 337,
  COLON_TK = 338,
  INC_OP_TK = 339,
  DEC_OP_TK = 340,
  PTR_OP_TK = 341,
  PERIOD_TK = 342,
  EQ_OP_TK = 343,
  NE_OP_TK = 344
};

namespace NvPcomp {
	class symTable {
	protected:
		std::vector<std::map< std::string, symNode *> *> _table;
		int _level;
	public:
		symTable();
		symTable(FILE*);
		~symTable();
		InsertResult insert(std::string key, symNode* node);
		int search(const std::string key, symNode* &Node, bool ignoreFirst);
		symNode *search_top(std::string key);
		void dump();
		bool push();
		bool pop();
	};
}

#endif /* SYMTABLE_H_ */
