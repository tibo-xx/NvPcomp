/**********************************************************************/
//! Variable table implementation for NvPcomp
/*!
 * \class variableTable
 *
 * Description: The Variable Table implementation for NvPcomp
 *
 * \author CMT, DRJ & BFB
 *
 */
/**********************************************************************/
#ifndef VARIABLETABLE_H_
#define VARIABLETABLE_H_

#include <string>
#include <map>
#include <iterator>

// Logging line start
#define VARIABLELOG_START	"variableTable: "

class variableTable {
protected:
	std::map< std::string, int> _table;
protected:
	bool search(const std::string key);	
public:
	variableTable();
	~variableTable();
	std::string insert(std::string key, int memLocation);
	void setMemLocation(std::string key, int memLocation);
	bool search(const std::string key, int &memLocation);
};


#endif /* VARIABLETABLE_H_ */
