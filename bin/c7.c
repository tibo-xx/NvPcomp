/*! Compile test file 7
 *  \file c7.c
 *  \brief Demonstrates the ability of NvPcomp to handle declarations and
 *  \brief generate code for to process the FOR statement and the DO/WHILE
 *  \brief statement.    
 *  \author CMT, DRJ & BFB
 */

int main () {
	int i;
	int j = 1;
	
	
	for (i = 0; i < 5; i++)
		j++;
	
	do 
		j--;
		while (j > 0);
	
	return 1;
}
