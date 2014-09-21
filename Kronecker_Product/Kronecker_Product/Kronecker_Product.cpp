#include "stdafx.h"
#include <iostream>

const int SIZE_EACH_VECTOR = 2;
const int KRONECKER_MAX_SIZE = 3;

float custom_pow(float base, int exp){
	float result = 1; for (int i = 0; i<exp; i++) result *= base;
	return result;
}

void print_vector(int *vec, int vec_size,char*msg){
	std::cout << msg <<"(";
	for (int i = 0; i < vec_size; i++) std::cout << vec[i] << ((i!=vec_size-1)?",":"");
	std::cout << ")"<<std::endl;
}

void init_vec(int*vec,int vecsize){
	for (int i = 0; i < vecsize; i++) vec[i] = 0;
}

int* split_vector(int*vec,int start, int length){
	int * splitted_vector = new int[length];
	int splitted_vector_i = 0;
	for (int i = start; i < length+start; i++) splitted_vector[splitted_vector_i++] = vec[i];
	return splitted_vector;
}

int * get_subvector(int *vec,int index_vec){
	return split_vector(vec, (index_vec - 1)*SIZE_EACH_VECTOR, SIZE_EACH_VECTOR);
}

int * kronecker(int * vec,int kron_dim){
	if (kron_dim <= 1 || kron_dim>KRONECKER_MAX_SIZE) return vec;
	int kronsize = (int) custom_pow(2, kron_dim);
	int * kronvec = new int[kronsize];
	init_vec(kronvec, kronsize);

	//SPLIT THE VECTOR INTO SEPARATE VECTORS OF SIZE 2 (EACH):
	int **vecdims = new int*[kron_dim];
	for (int i = 0; i < kron_dim; i++) vecdims[i] = get_subvector(vec, i + 1);

	//MAKE KRONECKER PRODUCT:
	int kron_i = 0;
	for (int i = 0; i < SIZE_EACH_VECTOR; i++) 
		for (int j = 0; j < SIZE_EACH_VECTOR; j++)
			if (kron_dim == 3) for (int k = 0; k < SIZE_EACH_VECTOR; k++) kronvec[kron_i++] = vecdims[0][i] * vecdims[1][j] * vecdims[2][k];
			else if (kron_dim == 2) kronvec[kron_i++] = vecdims[0][i] * vecdims[1][j];
			
	for (int i = 0; i < kron_dim; i++) delete []vecdims[i];
	delete [] vecdims;
	return kronvec;
}

int _tmain(int argc, _TCHAR* argv[]){
	int vec_dim =3;
	int vec_size = SIZE_EACH_VECTOR*vec_dim;
	
	int * vec = new int[vec_size];
	vec[0] = 0;	vec[1] = 1;
	vec[2] = 0;	vec[3] = 1;
	vec[4] = 0;	vec[5] = 1;
	print_vector(vec, vec_size, "Vector without kronecker:\n");
	
	int *kronvec = kronecker(vec, vec_dim);
	print_vector(kronvec, custom_pow(2, vec_dim), "Vector with kronecker:\n");

	delete []vec;
	delete []kronvec;
	std::cin.get();
	return 0;
}