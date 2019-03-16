package objets;

import java.io.*;

public class Stripe {
	
	private int nblocks;
	private Block [] stripe;
	
	public Stripe(int nblocks) {
		this.nblocks = nblocks;
		this.stripe = new Block[nblocks];
	}
	
	public int getNblocks() {
		return this.nblocks;
	}
	
	public Block getIStripe(int index) {
		return this.stripe[index];
	}
	
	public void setNblocks(int nblocks) {
		this.nblocks = nblocks;
	}
	
	public void setIStripe(Block block, int i) {
		this.stripe[i] = block;
	}
	
	/**
	 * 
	 * @param stripe La bande a ecrire sur le systeme.
	 * @param pos La position ou ecrire la bande sur le systeme.
	 * @param disks Systeme RAID.
	 * @return 0 si l'operation s'est bien passee, 1 s'il y a eu un probleme d'ecriture.
	 */
	
	public int write_stripes(int pos, File [] disks) {
		for(int i = 0; i < this.getNblocks(); i++) {
			if(this.getIStripe(i).write_block(pos, disks[i]) != 0) {
				System.err.println("Erreur lors de l'écriture de la bande.");
				return 1;
			}
		}
		return 0;
	} 
	
	/**
	 * Calcule le nombre de blocks necessaires pour ecrire une chaine de bytes sur le systeme RAID
	 * Prend en compte les blocks de parites.
	 * @param nb_disks Nombre de disks du systeme RAID.
	 * @return Nombre de blocks.
	 */
	public int compute_final_nblock(int nb_disks) {
		int nChunks = this.compute_nblock();
		int nStripes = this.compute_nstripe(nChunks);
		return nChunks + nStripes + ((nChunks + nStripes) / nb_disks);
	}

	
	public int compute_nstripe(int i) {
		return 0;
	}
	
	public int compute_parity_index(int i) {
		return 0;
	}
	
	public int compute_nblock() {
		return 0;
	}
	
	public Block compute_parity(Block [] blocks, int i) {
		return new Block();
	}

}
