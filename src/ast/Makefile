########################################################################
#
# basic Makefile for AST class library
#
########################################################################
# Tool Defines
########################################################################
CXXFLAGS = -O1 -g3 -Wall -fmessage-length=0
CXX = g++
########################################################################
# Sources
########################################################################
SRC = 	 src/translation_unit_astNode.cpp  src/external_declaration_astNode.cpp  src/function_definition_astNode.cpp  src/declaration_astNode.cpp  src/declaration_list_astNode.cpp  src/declaration_specifiers_astNode.cpp  src/storage_class_specifier_astNode.cpp  src/type_specifier_astNode.cpp  src/type_qualifier_astNode.cpp  src/struct_or_union_specifier_astNode.cpp  src/struct_or_union_astNode.cpp  src/struct_declaration_list_astNode.cpp  src/init_declarator_list_astNode.cpp  src/init_declarator_astNode.cpp  src/struct_declaration_astNode.cpp  src/specifier_qualifier_list_astNode.cpp  src/struct_declarator_list_astNode.cpp  src/struct_declarator_astNode.cpp  src/enum_specifier_astNode.cpp  src/enumerator_list_astNode.cpp  src/enumerator_astNode.cpp  src/declarator_astNode.cpp  src/direct_declarator_astNode.cpp  src/pointer_astNode.cpp  src/type_qualifier_list_astNode.cpp  src/parameter_type_list_astNode.cpp  src/parameter_list_astNode.cpp  src/parameter_declaration_astNode.cpp  src/identifier_list_astNode.cpp  src/initializer_astNode.cpp  src/initializer_list_astNode.cpp  src/type_name_astNode.cpp  src/abstract_declarator_astNode.cpp  src/direct_abstract_declarator_astNode.cpp  src/statement_astNode.cpp  src/labeled_statement_astNode.cpp src/compound_statement_astNode.cpp  src/statement_list_astNode.cpp  src/selection_statement_astNode.cpp  src/iteration_statement_astNode.cpp  src/jump_statement_astNode.cpp  src/expression_astNode.cpp  src/assignment_expression_astNode.cpp  src/assignment_operator_astNode.cpp  src/conditional_expression_astNode.cpp  src/constant_expression_astNode.cpp  src/logical_or_expression_astNode.cpp  src/logical_and_expression_astNode.cpp  src/inclusive_or_expression_astNode.cpp  src/exclusive_or_expression_astNode.cpp  src/and_expression_astNode.cpp  src/equality_expression_astNode.cpp  src/relational_expression_astNode.cpp  src/shift_expression_astNode.cpp  src/additive_expression_astNode.cpp  src/multiplicative_expression_astNode.cpp  src/cast_expression_astNode.cpp  src/unary_expression_astNode.cpp  src/unary_operator_astNode.cpp  src/postfix_expression_astNode.cpp  src/primary_expression_astNode.cpp  src/argument_expression_list_astNode.cpp  src/constant_astNode.cpp  src/string_astNode.cpp  src/identifier_astNode.cpp  src/root_astNode.cpp  src/comment_astNode.cpp src/leaf_astNode.cpp
src += ./src/expression_statement_astNode.cpp
SRC += ./ast.cpp
SRC += ./astNode.cpp
SRC += ./variableTable.cpp

OBJ = $(SRC:.cpp=.o)

TARGET = libast.a

INCS = -I. -I../include/ 
INCS += -I./src/
INCS += -I./../parser/
INCS += -I./../logging/
INCS += -I./../tac/
INCS += -I./../symTable/

# library paths
LIBS = -lstdc++

.SUFFIXES: .cpp

default: $(TARGET)

.cpp.o:
	$(CXX) $(INCS) $(CCFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	ar rcs $(TARGET) $(OBJ)

depend: dep

dep:
	makedepend -- $(CXXFLAGS) -- $(INCS) $(SRC)

clean:
	rm -f $(OBJ) $(TARGET)

