int fact(int n);

int entry(){
	int n = 5;
	return fact(n);
}


int fact(int n){
	if(n > 1)
		return n * fact(n - 1);
	else
		return 1;
}

