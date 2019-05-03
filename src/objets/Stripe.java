package objets;

public class Stripe {
	
	private static int nblocks = 4;
	private Block [] stripe;
	
	public Stripe() {
		this.stripe = new Block[nblocks];
	}
	
	public Stripe(Block blocks[]) {
		this.stripe = blocks;
	}
	
	public Stripe(byte bytes[]) {
		for(int i = 0; i < Stripe.nblocks; i++) {
			this.stripe[i] = new Block(bytes[i]);
		}
	}
	
	public Stripe(int entiers[]) {
		for(int i = 0; i < Stripe.nblocks; i++) {
			this.stripe[i] = new Block(entiers[i]);
		}
	}
	
	public int getNblocks() {
		return Stripe.nblocks;
	}
	
	public Block getIStripe(int index) {
		return this.stripe[index];
	}
	
	public void setNblocks(int nblocks) {
		Stripe.nblocks = nblocks;
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
	
	
	/**
	 * 
	 * @param stripe La bande a lire sur le systeme.
	 * @param pos La position ou lire la bande sur le systeme.
	 * @param disks Systeme RAID.
	 * @return 0 si l'operation s'est bien passee, 1 s'il y a eu un probleme de lecture.
	 */
	
	public int read_stripe(int pos) {
		for(int i = 0; i < this.getNblocks(); i++) {
			if(this.getIStripe(i) = Block.read_block(pos, (new VirtualDisk()).getStorage()[i]) != 0) {
				System.err.println("Erreur lors de la lecture de la bande.");
				return 1;
			}
		}
		return 0;
	}

}
