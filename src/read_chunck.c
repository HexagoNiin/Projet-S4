int read_chunk(uchar *buffer, int nStripe, int startbyte, FILE **disk){
	stripe_t stripe;
	
	
	for(int i = 0; i < nStripe){
		read_strip(&stripe, startbyte + i, disk);
		for (int j = 0; j < stripe.nblock; j++){
			buffer[i*stripe.nblock + j] = stripe[j];
		}
	}
	
	return 0;
}










