/**********************************************************************/
//! Assembly Language Writer for the Picoblaze 3 softcore processor
/*!
 * \class kcpsm3Writer
 *
 * Description: 
 *
 * \author CMT, DRJ & BFB
 *
 */
/**********************************************************************/
#ifndef KCPSM3WRITER_H_
#define KCPSM3WRITER_H_

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <iterator>
#include <tacTree.h>
#include <tacNode.h>
#include <sourceBuffer.h>
#include <variableTable.h>
#include <ast.h>
#include <astInfoTable.h>
#include <vector>
#include <map>
#include <NvPcomp_logger.h>

#define COMMENTCHAR		string(";")
#define TABSPACES		4
#define TABS(level)		string(level*TABSPACES, ' ')

#define SCRATCHSIZE		64

enum arithmeticType {
	Type1,
	Type2,
	Type3,
	Type4
};

class kcpsm3Writer {

public:
	kcpsm3Writer(NvPcomp::tacTree* treeIn,	\
				 ast* asTree, \
				 const char *outputFileName, \
				 const char *inputFileName);
	~kcpsm3Writer();
public:
	void genASM(void);
	
private:
	void outputHeader();
	void outputVariables();
	void outputRegisters();
	void outputStart();
	void outputMain();
	void outputISR();
	void outputFunction(vector<NvPcomp::tacNode> *tree, vector<NvPcomp::tacNode>::iterator &iter);
	void outputLabel(vector<NvPcomp::tacNode>::iterator &iter);
	void outputAssignment(vector<NvPcomp::tacNode>::iterator &iter);
	void analyzeFunctions();
	void outputBranch(vector<NvPcomp::tacNode>::iterator &iter);
	void outputFetch(vector<NvPcomp::tacNode>::iterator &iter);
	void outputCompareAndBranch(vector<NvPcomp::tacNode>::iterator &iter);
	void outputGeneric3AC(vector<NvPcomp::tacNode>::iterator &iter);
	void outputInitializations();
	void outputArithmetic(vector<NvPcomp::tacNode>::iterator &iter);
	void outputCall(vector<NvPcomp::tacNode>::iterator &iter);
	void outputArgs(vector<NvPcomp::tacNode>::iterator &iter);
	void outputReturn();
	void outputMultiply8bit();
	void outputDivide8bit();
	int findNumArgs();
private:
	bool isRegister(std::string str);
	bool isValue(std::string str);
	void integerArithmetic(vector<NvPcomp::tacNode>::iterator &iter, arithmeticType type);
	void longArithmetic(vector<NvPcomp::tacNode>::iterator &iter, arithmeticType type);
	void floatArithmetic(vector<NvPcomp::tacNode>::iterator &iter, arithmeticType type);
	int getValueType(std::string);
	void insertArray(vector<NvPcomp::tacNode>::iterator &iter);
private:
	// AST
	ast* _asTree;
		
	NvPcomp::tacTree *_tacTree;
	// Source code buffer.
	sourceBuffer _buffer;
	// Variable Table.
	variableTable *_variables;
	// Function Table.
	astInfoTable<functionDefinition> *_functions;
	// The last source line printed.
	int _lastBufferLine;
	// InputSourceFile
	const char *_inputFileName;
	//OutputFile
	const char *_outputFileName;
	// Output File Pointer
	FILE *_out;
	// Output Stream.
	std::ostringstream _os;
	// Current Tab Level;
	int _tabLevel;
	bool insertMult;
	bool insertDiv;
	bool insertedArray;
	
	// This is to hold on to array accesses.
	std::map< std::string, NvPcomp::tacNode *> _arrayMap;
};

#endif /* KCPSM3WRITER_H_ */
