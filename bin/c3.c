/*! Compile test file 3
 *  \file c3.c
 *  \brief Demonstrates the ability of NvPcomp to generate code for 
 *  \brief the conditional (IF) statement
 *  \author CMT, DRJ & BFB
 */

int main () {
	int i;
	int j;
	i = 3;
	j = 1;
	
	if (i > 0)
		j++;
	
	return 1;
}
