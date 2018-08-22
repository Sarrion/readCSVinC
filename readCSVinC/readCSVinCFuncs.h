#pragma once
#include <string.h>
#include <math.h>

/* matrix dimension type:
used to informate about data set
dimensions */
typedef struct {
	int nrow;
	int ncol;
	double** matrix;
} matrx;

inline matrx getDim(const char *fileDir) {
	int nrow = 1, ncol = 1;

	/*________________________________open_file_and_check_it________________________________*/
	FILE *fi;
	errno_t err = fopen_s(&fi, fileDir, "r");
	if (err != 0) printf("Error in getDim function: unable to open the file.\n");

	/*________get_data_dimensions________*/
	char c = fgetc(fi);

	matrx Dim = { 1, 1 };
	while (c != '\n') {
		if (c == ',') Dim.ncol++;
		c = fgetc(fi);
	}
	while (c != EOF) {
		if (c == '\n') Dim.nrow++;
		c = fgetc(fi);
	}

	/*____final_formalities_and_result___*/
	fclose(fi);
	return Dim;
}

inline void displayMatrix(matrx M) {
	
	for (int a = 0; a < M.nrow; a++) {
		for (int b = 0; b < M.ncol; b++) {
			//printf("%i ", M[a][b]); // without pointers
			printf("%.2f ", *(*(M.matrix + a) + b)); // with pointers
		}
		printf("\n");
	}
	printf("\n");
}

inline matrx readCSV(const char* fileDir) {

	/*___________________get_data_dimensions____________________*/
	matrx dataDim = getDim("C:\\Users\\avicent\\Documents\\datos.txt");
	printf("Data dimensions: (%i, %i)\n\n", dataDim.nrow, dataDim.ncol);


	/*___________________variables_declaration__________________*/
	double** M;
	M = (double**)malloc(sizeof(double*) * dataDim.nrow);
	for (int row = 0; row < dataDim.nrow; row++) {
		M[row] = (double*)malloc(sizeof(double) * dataDim.ncol);
	}


	/*____________________open_file_and_check_it____________________*/
	FILE *fi;
	errno_t err = fopen_s(&fi, fileDir, "r");
	if (err != 0) printf("Error in readCSV function: unable to open file\n");


	/*________________csv_to_matrix_data_translation________________*/
	int i = 0, j = 0; //matrix positions
	int val_size = 2; // dynamic memory needed by val
	char* val = (char*)malloc(sizeof(char) * val_size);; // value to be passed to matrix
	char c; // character readed from data
	while (true) {
		c = fgetc(fi);
		switch (c) {
		case ',':
			*(*(M + i) + j) = (double)atof(val);
			j++;
			val_size = 2;
			val = (char*)realloc(val, sizeof(char) * val_size);
			break;
		case '\n':
			*(*(M + i) + j) = (double)atof(val);
			i++;
			j = 0;
			val_size = 2;
			val = (char*)realloc(val, sizeof(char) * val_size);
			break;
		case EOF:
			*(*(M + i) + j) = (double)atof(val);
			free(val);
			break;
		default:
			if (val_size == 2) {
				*val = c;
				*(val + 1) = '\0';
				val_size++;
			}
			else {
				val = (char*)realloc(val, sizeof(char) * val_size);
				*(val + val_size - 2) = c;
				*(val + val_size - 1) = '\0';
				val_size++;
			}
		}
		if (c == EOF) break;
	};

	fclose(fi);


	dataDim.matrix = M;
	return(dataDim);
}

inline double sum(double* vector, int length) {
	double result = 0;
	for (int i = 0; i < length; i++) {
		result = result + vector[i];
	}
	return result;
}

inline double sq(double value) {
	return value * value;
}

inline matrx corr(matrx M) {

	matrx result;
	result.ncol = M.ncol;
	result.nrow = M.ncol;
	result.matrix = (double**)malloc(sizeof(double*) * M.ncol);

	double* xy = (double*)malloc(sizeof(double) * M.nrow);
	double*x = (double*)malloc(sizeof(double) * M.nrow);
	double*y = (double*)malloc(sizeof(double) * M.nrow);
	double*x_square = (double*)malloc(sizeof(double) * M.nrow);
	double*y_square = (double*)malloc(sizeof(double) * M.nrow);


	for (int i = 0; i < M.ncol; i++) {
		result.matrix[i] = (double*)malloc(sizeof(double) * M.ncol);
	}

	for (int i = 0; i < M.ncol; i++) {
		for (int j = i + 1; j < M.ncol; j++) {
			
			// calculus of necessary elements for correlation computation
			for (int element = 0; element < M.nrow; element++) {
				x[element] = M.matrix[element][i];
				x_square[element] = sq(M.matrix[element][i]);
				y[element] = M.matrix[element][j];
				y_square[element] = sq(M.matrix[element][j]);
				xy[element] = M.matrix[element][i] * M.matrix[element][j];
			}

			int n = M.nrow;
			//printf("corr(%i, %i) = %.4f\n", i, j, (n*sum(xy, n) - sum(x, n)*sum(y, n)) / (sqrt(n*sum(x_square, n) - sum(x, n)*sum(x, n))*sqrt(n*sum(y_square, n) - sum(y, n)*sum(x, n))));
			//printf("(%i, %i) = %.4f\n", i, j, (sqrt(n*sum(x_square, n) - sum(x, n)*sum(x, n))*sqrt(n*sum(y_square, n) - sum(y, n)*sum(x, n))));
			result.matrix[i][j] = (n*sum(xy, n) - sum(x, n)*sum(y, n)) / (sqrt(n*sum(x_square, n) - sq(sum(x, n)))*sqrt(n*sum(y_square, n) - sq(sum(y, n))));
			result.matrix[j][i] = result.matrix[i][j];
		}
		result.matrix[i][i] = 1;
	}

	return result;
}


inline void writeCSV(matrx M, const char* filedir) {
	FILE* f;
	errno_t err = fopen_s(&f, filedir, "w");
	if (err != 0) printf("Error in writeDim function: unable to open the file.\n");

	for (int i = 0; i < M.nrow; i++) {
		for (int j = 0; j < M.ncol; j++) {
			fprintf(f, "%f", M.matrix[i][j]);
			if (j != M.nrow - 1) fprintf(f, ",");
		}
		fprintf(f, "\n");
	}

	fclose(f);
}