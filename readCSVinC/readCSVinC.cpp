#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include "readCSVinCFuncs.h"

int main()
{
	/*_______reading_data_____________*/
	matrx M = readCSV("C:\\Users\\avicent\\Documents\\datos.txt");
	displayMatrix(readCSV("C:\\Users\\avicent\\Documents\\datos.txt"));

	/*_______correlation_matrix_______*/
	matrx cors = corr(M);
	printf("\n");
	printf("Correlation Matrix:\n\n");
	displayMatrix(cors);

	/*_______save_correlation_matrix__*/
	writeCSV(cors, "C:\\Users\\avicent\\Documents\\datos_correlation_matrix.txt");


	return 0;
}