#include "errorMessages.h"

int calculateDimensionsProduct(const int *arrayOfDimensions, const int subscriptPosition){
	int dimensionsProduct = 1;
	for(int i = 0; i < subscriptPosition; i++){
		dimensionsProduct *= arrayOfDimensions[i];
	}
	return dimensionsProduct;
}

int isValidArraySize(const int dimensions){
	if(dimensions < 2){
		return 0; 
	}
	return 1;
}

int isValidArrayOfSubscripts(const int *arrayOfDimensions, const int *arrayOfSubscripts, const int dimensions){
	for(int i = 0; i < dimensions; i++){
		if(arrayOfSubscripts[i] < 0 || arrayOfSubscripts[i] >= arrayOfDimensions[i]){
			return 0;
		}
	}
	return 1;
}

int isValidIndex(const int *arrayOfDimensions, const int index, const int dimensions){
	int maxValue = calculateDimensionsProduct(arrayOfDimensions, dimensions) - 1;
	if(index < 0 || index > maxValue){
		return 0;
	}
	return 1;
}

int sub2ind2D(const int *arrayOfDimensions, const int *arrayOfSubscripts){
	if(!isValidArrayOfSubscripts(arrayOfDimensions, arrayOfSubscripts, 2)){
		callErrorMessage(1);
		exit(EXIT_FAILURE);
	}
	int subscript = arrayOfSubscripts[0] * arrayOfDimensions[1] + arrayOfSubscripts[1];
	return subscript;
}

int sub2ind(const int *arrayOfDimensions, const int *arrayOfSubscripts, const int dimensions){
	if(!isValidArrayOfSubscripts(arrayOfDimensions, arrayOfSubscripts, dimensions)){
		callErrorMessage(1);
		exit(EXIT_FAILURE);
	}
	if(!isValidArraySize(dimensions)){
		callErrorMessage(3);
		exit(EXIT_FAILURE);
	}
	int subscriptPosition = dimensions - 1;
	int value = 0;
	value += sub2ind2D(arrayOfDimensions, arrayOfSubscripts);  
	if(subscriptPosition > 1){
		for(int i = subscriptPosition; i > 1; i--){
			int hypoDimensionsProduct = calculateDimensionsProduct(arrayOfDimensions, i);
			value += arrayOfSubscripts[i] * hypoDimensionsProduct; 
		}
	}
	return value;
}

void ind2sub2D(const int *arrayOfDimensions, const int index, int convertedIndex[]){
	if(!isValidIndex(arrayOfDimensions, index, 2)){
		callErrorMessage(2);
		exit(EXIT_FAILURE);
	}
	convertedIndex[1] = index % arrayOfDimensions[1];
	convertedIndex[0] = index / arrayOfDimensions[1];
}

void ind2sub(const int *arrayOfDimensions, const int dimensions, const int index, int convertedIndex[]){  
	if(!isValidIndex(arrayOfDimensions, index, dimensions)){
		callErrorMessage(2);
		exit(EXIT_FAILURE);
	}
	if(!isValidArraySize(dimensions)){
		callErrorMessage(3);
		exit(EXIT_FAILURE);
	}
	int subscriptPosition = dimensions - 1;
	if(subscriptPosition < 2){
		ind2sub2D(arrayOfDimensions, index, convertedIndex);
	}else{
		int hypoDimensionsProduct = calculateDimensionsProduct(arrayOfDimensions, subscriptPosition);
		convertedIndex[subscriptPosition] = index / hypoDimensionsProduct;	
		int newIndex = index % hypoDimensionsProduct;
		ind2sub(arrayOfDimensions, subscriptPosition, newIndex, convertedIndex);
	}
}
