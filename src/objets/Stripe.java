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
	
	public int write_stripes(Stripe stripe, int pos, File [] disks) {
		for(int i = 0; i < stripe.getNblocks(); i++) {
			if(stripe.getIStripe(i).write_block(pos, disks[i]) != 0) {
				System.err.println("Erreur lors de l'écriture de la bande.");
				return 1;
			}
		}
		return 0;
	} 

}
