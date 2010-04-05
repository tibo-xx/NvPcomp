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
SRC = 	 src/translation_unit_ast.cpp  src/external_declaration_ast.cpp  src/function_definition_ast.cpp  src/declaration_ast.cpp  src/declaration_list_ast.cpp  src/declaration_specifiers_ast.cpp  src/storage_class_specifier_ast.cpp  src/type_specifier_ast.cpp  src/type_qualifier_ast.cpp  src/struct_or_union_specifier_ast.cpp  src/struct_or_union_ast.cpp  src/struct_declaration_list_ast.cpp  src/init_declarator_list_ast.cpp  src/init_declarator_ast.cpp  src/struct_declaration_ast.cpp  src/specifier_qualifier_list_ast.cpp  src/struct_declarator_list_ast.cpp  src/struct_declarator_ast.cpp  src/enum_specifier_ast.cpp  src/enumerator_list_ast.cpp  src/enumerator_ast.cpp  src/declarator_ast.cpp  src/direct_declarator_ast.cpp  src/pointer_ast.cpp  src/type_qualifier_list_ast.cpp  src/parameter_type_list_ast.cpp  src/parameter_list_ast.cpp  src/parameter_declaration_ast.cpp  src/identifier_list_ast.cpp  src/initializer_ast.cpp  src/initializer_list_ast.cpp  src/type_name_ast.cpp  src/abstract_declarator_ast.cpp  src/direct_abstract_declarator_ast.cpp  src/statement_ast.cpp  src/labeled_statement_ast.cpp  src/expression_statement_ast.cpp  src/compound_statement_ast.cpp  src/statement_list_ast.cpp  src/selection_statement_ast.cpp  src/iteration_statement_ast.cpp  src/jump_statement_ast.cpp  src/expression_ast.cpp  src/assignment_expression_ast.cpp  src/assignment_operator_ast.cpp  src/conditional_expression_ast.cpp  src/constant_expression_ast.cpp  src/logical_or_expression_ast.cpp  src/logical_and_expression_ast.cpp  src/inclusive_or_expression_ast.cpp  src/exclusive_or_expression_ast.cpp  src/and_expression_ast.cpp  src/equality_expression_ast.cpp  src/relational_expression_ast.cpp  src/shift_expression_ast.cpp  src/additive_expression_ast.cpp  src/multiplicative_expression_ast.cpp  src/cast_expression_ast.cpp  src/unary_expression_ast.cpp  src/unary_operator_ast.cpp  src/postfix_expression_ast.cpp  src/primary_expression_ast.cpp  src/argument_expression_list_ast.cpp  src/constant_ast.cpp  src/string_ast.cpp  src/identifier_ast.cpp  src/leaf_ast.cpp  src/comment_ast.cpp 

OBJ = $(SRC:.cpp=.o)

TARGET = astlib.a

INCS = -I. -I../include/ 
INCS += -I./src/
INCS += -I./../parser/
INCS += -I./../logging/

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

