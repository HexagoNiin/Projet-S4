package stripe_utils;

import java.io.*;
import block_utils.Block;
import java.util.Arrays;

public class Chunk {
	private byte [] buffer;
	private int nChars;
	
	public Chunk(byte [] buffer, int nChars) {
		this.buffer = buffer.clone();
		this.nChars = nChars;
	}
	
	public int write_chunk(int startbyte, File [] disks) {
		int nChunks = 8; /*compute_block(nChars); */
		int nStripes = 64; /*compute_stripe(nChunks);*/
		int NB_DISK = 4; //faute de mieux
		Stripe [] stripes = new Stripe[nStripes];
		Block [] blocks = new Block[nChunks];
		
		for(int i = 0; i < nChunks; i += Block.BLOCK_SIZE) {
			blocks[i] = new Block();
			blocks[i].setData(Arrays.copyOfRange(this.buffer, i, i + Block.BLOCK_SIZE));
		}
		
		for(int i = 0; i < nStripes; i++) {
			int u = 0;
			stripes[i] = new Stripe(NB_DISK); //NB_DISK
			for(int j = 0; j < NB_DISK; j++) {
				if(j == 3) { //compute_parity_index(i)
					stripes[i].setIStripe(blocks[i * (NB_DISK - 1) + u], j); // compute_parity...
				} else {
					stripes[i].setIStripe(blocks[i * (NB_DISK - 1) + u], j);
				}
			}
		}
		
		
		return 0;
	}
}
