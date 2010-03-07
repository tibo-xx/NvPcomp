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

class symTable {

private:
	std::vector<std::map< std::string, symNode *> *> _table;
public:
	symTable();
	~symTable();
	bool insert(std::string key, symNode node);
	symNode *search(std::string key);
	void dump();
	bool push();
	bool pop();
	
};

#endif /* SYMTABLE_H_ */
