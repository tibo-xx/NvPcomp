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

// I need to rethink this whole type thing.
enum SymType {
	symInt,
	symLong,
	symFunction	
}

class symNode {

private:
	stl::string lineStr;
	stl::string	key;
	long lineNum;
	
	
	
public:
	symNode();
	~symNode();
	
	//bool operator ==( const symNode &other );
};



#endif /* SYMNODE_H_ */
