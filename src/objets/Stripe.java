package objets;

public class Stripe {

	private static int nBlocks = 4;
	private Block [] stripe;

	public Stripe() {
		this.stripe = new Block[nBlocks];
	}

	public Stripe(Block blocks[]) {
		for(int i = 0; i < Stripe.nBlocks-1; i++) {
			this.stripe[i] = blocks[i];
		}
	}

	public Stripe(byte bytes[]) {
		for(int i = 0; i < Stripe.nBlocks-1; i++) {
			this.stripe[i] = new Block(bytes[i]);
		}
	}

	public Stripe(int entiers[]) {
		for(int i = 0; i < Stripe.nBlocks-1; i++) {
			this.stripe[i] = new Block(entiers[i]);
		}
		this.generateParity();
	}

	public void generateParity() {
		Block reference[] = new Block[nBlocks-1];
		int i = 0;
		int j = 0;
		while(j < nBlocks-1) {
			if(i != VirtualDisk.nextStripe) {
				reference[j] = stripe[i];
				i++;
			}
			j++;
		}
		VirtualDisk.nextStripe = (VirtualDisk.nextStripe + nBlocks-1) % nBlocks;
	}

	public int getNBlocks() {
		return Stripe.nBlocks;
	}

	public Block getIStripe(int index) {
		return this.stripe[index];
	}

	public void setNBlocks(int nblocks) {
		Stripe.nBlocks = nblocks;
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

	public int write(int pos) {
		for(int i = 0; i < this.getNBlocks(); i++) {
			if(this.getIStripe(i).write(pos, (new VirtualDisk()).getStorage()[i]) != 0) {
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

	public int read(int pos) {
		for(int i = 0; i < this.getNblocks(); i++) {
			if(this.getIStripe(i) = Block.read_block(pos, (new VirtualDisk()).getStorage()[i]) != 0) {
				System.err.println("Erreur lors de la lecture de la bande.");
				return 1;
			}
		}
		return 0;
	}

}
