#pragma once
#include <string.h>


/* matrix dimension type:
used to informate about data set
dimensions */
typedef struct {
	int nrow;
	int ncol;
} Dim_t;

inline Dim_t getDim(const char *fileDir) {
	int nrow = 1, ncol = 1;

	/*________________________________open_file_and_check_it________________________________*/
	FILE *fi;
	errno_t err = fopen_s(&fi, fileDir, "r");
	if (err != 0) printf("Error in getDim function: unable to open the file.\n");

	/*________get_data_dimensions________*/
	char c = fgetc(fi);

	Dim_t Dim = { 1, 1 };
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

inline void readCSV(const char* fileDir, float** M) {

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
			*(*(M + i) + j) = (float)atof(val);
			j++;
			val_size = 2;
			val = (char*)realloc(val, sizeof(char) * val_size);
			break;
		case '\n':
			*(*(M + i) + j) = (float)atof(val);
			i++;
			j = 0;
			val_size = 2;
			val = (char*)realloc(val, sizeof(char) * val_size);
			break;
		case EOF:
			*(*(M + i) + j) = (float)atof(val);
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
}