/**********************************************************************/
//! Symbol table implementation for NvPcomp
/*!
 * \class symTable
 *
 * Description: The Symbol Table implementation for NvPcomp
 *
 * \author CMT & DRJ
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

#endif /* SYMTABLE_H_ */
