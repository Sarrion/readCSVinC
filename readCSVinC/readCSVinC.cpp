#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include "readCSVinCFuncs.h"

int main()
{
	/*___________________reading_data_using_toniFuns____________*/
	Dim_t M = readCSV("C:\\Users\\avicent\\Documents\\datos.txt");


	/*___________________correlation_matrix_____________________*/
	Dim_t cors = corr(M);

	/*___________________displaying_data________________________*/
	printf("\n");
	printf("Correlation Matrix:\n\n");
	for (int a = 0; a < cors.nrow; a++) {
		for (int b = 0; b < cors.ncol; b++) {
			//printf("%i ", M[a][b]); // without pointers
			printf("%.2f ", cors.matrix[a][b]); // with pointers
		}
		printf("\n");
	}
	printf("\n");

	/*___________________final_formalities______________________*/
	return 0;
}