int compute_parity_index(int i){
	int indPar;
	indPar = (i + NB_DISK - 1) / NB_DISK;
	return indPar;
}