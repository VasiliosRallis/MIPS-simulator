void strcpy(char* src, char* dest);

int entry(){
	char array1[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
	char array2[6];
	strcpy(array1, array2);
	return array2[0];
}

void strcpy(char* src, char* dest){
	while(*src){
		*dest++ = *src++;
	}
}


