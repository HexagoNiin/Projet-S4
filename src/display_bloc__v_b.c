void display_pos(uint pos, FILE disk){
	block_t block;
	
	if (read_block(&block, pos, disk)){
		printf("erreur de lecture [read_block]\n");
		return;
	}
	
	display_block(block);
}
	
char* itoh(int x){
  char *h;
  h = malloc(2 * sizeof(char));
  sprintf(h, "%x", x);
  return h;
}



void display_block(block_t block){
	int i;
	char *byteHex;
	
  for(i = 0; i < BLOCK_SIZE; i++){
	
	byteHex = itoh(block.data[i]);
    
	if (block.data[i] <= 9)
		printf("0");
	printf("%s ", byteHex);
  
  }

	printf("\n");
}
