int read_strip(stripe_t &stripe, uint pos, FILE ** disk){
	stripe->nblock = NB_DISK - 1;
	stripe->stripe = malloc((NB_DISK - 1)* sizeof(block_t));
	

	for(int i = 0; i < NB_DISK - 1; i++){
		if (i != compute_parity_index(pos)){
			if (read_block(&stripe->stripe[i], pos , disk[i])){
			printf("erreur de lecture [read_block]\n");
			return 1;
			}
		}
	}
	
	return 0;
}

