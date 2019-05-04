package objets;

public class Stripe {

	public static int nBlocks = VirtualDisk.nDisk;
	private Block [] blocks;

	public Stripe() {
		this.blocks = new Block[nBlocks];
	}

	public Stripe(Block blocks[]) {
		for(int i = 0; i < Stripe.nBlocks-1; i++) {
			this.blocks[i] = blocks[i];
		}
	}

	public Stripe(byte bytes[]) {
		for(int i = 0; i < Stripe.nBlocks-1; i++) {
			this.blocks[i] = new Block(bytes[i]);
		}
	}

	public Stripe(int entiers[]) {
		for(int i = 0; i < Stripe.nBlocks-1; i++) {
			this.blocks[i] = new Block(entiers[i]);
		}
		this.generateParity();
	}

	public void generateParity() {
		Block reference[] = new Block[nBlocks-1];
		int i = 0;
		int j = 0;
		while(j < nBlocks-1) {
			if(i != VirtualDisk.nextParityPos) {
				reference[j] = blocks[i];
				i++;
			}
			j++;
		}
		blocks[VirtualDisk.nextParityPos] = Utils.compute_parity(reference, nBlocks-1);
		VirtualDisk.nextParityPos = (VirtualDisk.nextParityPos + nBlocks-1) % nBlocks;
	}

	public int getNBlocks() {
		return Stripe.nBlocks;
	}

	public Block getIStripe(int index) {
		return this.blocks[index];
	}

	public void setNBlocks(int nblocks) {
		Stripe.nBlocks = nblocks;
	}

	public void setIStripe(Block block, int i) {
		this.blocks[i] = block;
	}

	/**
	 *
	 * @param blocks La bande a ecrire sur le systeme.
	 * @param pos La position ou ecrire la bande sur le systeme.
	 * @param disks Systeme RAID.
	 * @return 0 si l'operation s'est bien passee, 1 s'il y a eu un probleme d'ecriture.
	 */

	public int write(int pos) {
		for(int i = 0; i < this.getNBlocks(); i++) {
			if(this.blocks[i].write(pos, VirtualDisk.storage[i]) != 0) {
				System.err.println("Erreur lors de l'écriture de la bande.");
				return 1;
			}
		}
		return 0;
	}

	/**
	 *
	 * @param blocks La bande a lire sur le systeme.
	 * @param pos La position ou lire la bande sur le systeme.
	 * @param disks Systeme RAID.
	 * @return 0 si l'operation s'est bien passee, 1 s'il y a eu un probleme de lecture.
	 */

	public int read(int pos) {
		for(int i = 0; i < Stripe.nBlocks; i++) {
			if(this.blocks[i].read(pos, VirtualDisk.storage[i]) != 0) {
				System.err.println("Erreur lors de la lecture de la bande.");
				return 1;
			}
		}
		return 0;
	}
	
	public String toString() {
		String buffer = "[";
		for(int i = 0; i < nBlocks; i++) {
			buffer += blocks[i].toString();
			if(i != nBlocks-1) {
				buffer += ", ";
			}
		}
		return buffer + "]";
	}
}
