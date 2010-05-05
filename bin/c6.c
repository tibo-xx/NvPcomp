/*! Compile test file 6
 *  \file c6.c
 *  \brief Demonstrates the ability of NvPcomp to handle declarations and
 *  \brief generate code for procedures with single nesting levels and
 *  \brief value/reference parameters.  
 *  \author CMT, DRJ & BFB
 */

int test (int x, int *y) {
	x++;
	y++;
}

int main () {
	int i, *j;
	i = 3;
	
	if (i > 0)
		test (i, j);
	
	return 1;
}
