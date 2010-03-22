//! Symbol table Node
/*! 
 * \class symNode
 *
 * Description
 *
 * \author CMT & DRJ
 *
 */
#ifndef SYMNODE_H_
#define SYMNODE_H_

#include <string>
#include <parse.hh>

class symNode {

private:
	std::string lineStr;
	std::string	key;
	long lineNum;
	
	
	
public:
	symNode();
	~symNode();
};



#endif /* SYMNODE_H_ */
