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
#include <sstream>
#include <map>
#include <iterator>


#define MAXNAMELENGTH	9

// Logging line start
#define VARIABLELOG_START	"variableTable: "

typedef struct variableInfo {
	int memLocation;
	int size;	
} variableInfo;

class variableTable {
protected:
	std::map< std::string, variableInfo *> _table;
protected:
	bool search(const std::string key);
	std::string mangleName(std::string key, int suffix);
public:
	variableTable();
	~variableTable();
	std::string insert(std::string key, variableInfo *info);
	bool setMemLocation(std::string key, int memLocation);
	bool setVariableSize(std::string key, int size);
	bool setVariableInfo(std::string key, variableInfo *info_in);
	bool search(const std::string key, variableInfo *info);
};


#endif /* VARIABLETABLE_H_ */
