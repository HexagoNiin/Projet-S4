package objets;

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
	
	public int write_stripes(int pos) {
		for(int i = 0; i < this.getNblocks(); i++) {
			if(this.getIStripe(i).write_block(pos, (new VirtualDisk()).getStorage()[i]) != 0) {
				System.err.println("Erreur lors de l'écriture de la bande.");
				return 1;
			}
		}
		return 0;
	}

}
