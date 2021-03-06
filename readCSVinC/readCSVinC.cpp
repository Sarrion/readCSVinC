#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include "readCSVinCFuncs.h"

int main()
{
	/*___________________get_data_dimensions____________________*/
	Dim_t dataDim = getDim("C:\\Users\\avicent\\Documents\\datos.txt");
	printf("Data dimensions: (%i, %i)\n\n", dataDim.nrow, dataDim.ncol);


	/*___________________variables_declaration__________________*/
	float** M;
	M = (float**)malloc(sizeof(float*) * dataDim.nrow);
	for (int row = 0; row < dataDim.nrow; row++) {
		M[row] = (float*)malloc(sizeof(float) * dataDim.ncol);
	}


	/*___________________reading_data_using_toniFuns____________*/
	readCSV("C:\\Users\\avicent\\Documents\\datos.txt", M);


	/*___________________displaying_data________________________*/
	for (int a = 0; a < dataDim.nrow; a++) {
		for (int b = 0; b < dataDim.ncol; b++) {
			//printf("%i ", M[a][b]); // without pointers
			printf("%.2f ", *(*(M + a) + b)); // with pointers
		}
		printf("\n");
	}
	printf("\n");


	/*___________________final_formalities______________________*/
	return 0;
}