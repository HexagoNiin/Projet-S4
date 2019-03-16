package objets;

import java.io.File;

public class Chunk {
	private byte [] buffer;
	private int nChars;
	private int posCurrent;
	
	public Chunk(byte [] buffer, int nChars) {
		this.buffer = buffer.clone();
		this.nChars = nChars;
		this.posCurrent = 0;
	}
	
	/**
	 * Transforme une partie du buffer en nb_disks - 1 blocks.
	 * La position courante sur le buffer est incremente du nombre de caracteres lu.
	 * @param nb_disks Nombre de disks du systeme
	 * @return nd_disks - 1 blocks
	 */
	public Block [] generateStripe(int nb_disks)  {
		Block [] blocks = new Block[nb_disks-1];
		for(int i = 0; i < nb_disks-1; i++) {
			for(int j = 0; j < Block.BLOCK_SIZE; i++) {
				if(posCurrent == nChars) {
					blocks[i].setByte((byte) '\0', j);
				} else {
					blocks[i].setByte(buffer[posCurrent], j);
					posCurrent++;
				}
			}
		}
		return blocks;
	}
	
	/**
	 * Ecrit une chaine de bytes sur le systeme RAID.
	 * @param startbyte Position ou ecrire la bande sur le systeme RAID.
	 * @param disks Systeme RAID.
	 * @return le nombre de bandes ecrite ou -1 s'il y a eu un probleme.
	 */
	public int write_chunk(int startbyte, File [] disks) {
		int NB_DISK = 4;
		Stripe stripe = new Stripe(NB_DISK);
		int nChunks = stripe.compute_final_nblock(NB_DISK);
		int nStripes = stripe.compute_nstripe(nChunks);
		
		for(int i = 0; i < nStripes; i++) {
			Block [] blocks = this.generateStripe(NB_DISK);
			int i_blocks = 0;
			
			for(int j = 0; j < NB_DISK; j++) {
				if(j == stripe.compute_parity_index(i)) {
					stripe.setIStripe(stripe.compute_parity(blocks, NB_DISK-1), j); // compute_parity...
				} else {
					stripe.setIStripe(blocks[i_blocks], j);
					i_blocks++;
				}
			}
			
			if(stripe.write_stripes(startbyte + (i * Block.BLOCK_SIZE), disks) == 1) {
				return -1;
			}
		}
		return nStripes;
	}

}
