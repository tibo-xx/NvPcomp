/*!  Variable table implementation for NvPcomp
 *  \file astNode.h
 *  \class variableTable
 *  \brief The Variable Table implementation for NvPcomp
 *  \author CMT, DRJ & BFB
 */

#ifndef VARIABLETABLE_H_
#define VARIABLETABLE_H_

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <iterator>
#include <location.hh>
#include <position.hh>

#define MAXNAMELENGTH	8

// Logging line start
#define VARIABLELOG_START	"variableTable: "

typedef struct variableInfo {
	int memLocation;
	int size;
	int tokenType;
	bool isArray;
	int elements;
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
	bool search(const std::string key, variableInfo* &info);
	std::map< std::string, variableInfo *> *getTable();
	void print();
};


#endif /* VARIABLETABLE_H_ */
