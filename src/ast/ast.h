/**********************************************************************/
//! Abstract Syntax Tree
/*!
 * \class ast
 *
 * Description: Abstract Syntax Tree
 *
 * \author CMT, DRJ & BFB
 *
 */
/**********************************************************************/
#ifndef AST_H_
#define AST_H_

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <location.hh>
#include <position.hh>
#include <tacTree.h>
#include <astNode.h>
#include <NvPcomp_logger.h>

class ast {

	public:
		ast();
		~ast();		
};

#endif /* AST_H_ */
