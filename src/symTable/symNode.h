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
	std::string	_key;	
	std::string	_strType;
	NvPcomp::BParser::token::yytokentype _tok;
	NvPcomp::BParser::location_type _loc;
	
public:
	symNode(NvPcomp::BParser::token::yytokentype tok, \
			NvPcomp::BParser::location_type loc, \
			std::string key, \
			std::string strType);
	~symNode();
};



#endif /* SYMNODE_H_ */
