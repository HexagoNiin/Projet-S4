package objets;

public class Stripe {

	public static int nBlocks = VirtualDisk.nDisk;
	private Block [] blocks;

	public Stripe() {
		this.blocks = new Block[nBlocks];
		for(int i = 0; i < nBlocks; i++) {
			blocks[i] = new Block();
		}
	}

	/*public Stripe(Block blocks[]) {
		this();
		int offset = 0;
		for(int i = 0; i < Stripe.nBlocks; i++) {
			if(i == VirtualDisk.nextParityPos) offset++;
			this.blocks[i] = blocks[i];
		}
		this.generateParity();
	}*/

	public Stripe(byte bytes[]) {
		this();
		for(int i = 0; i < Stripe.nBlocks-1; i++) {
			blocks[i + (i>=VirtualDisk.nextParityPos?1:0)] = new Block(Utils.subArray(bytes, i * Block.nBytes, Block.nBytes));
		}
		this.generateParity();
	}

	/*public Stripe(int entiers[]) {
		this();
		int offset = 0;
		for(int i = 0; i < Stripe.nBlocks; i++) {
			if(i == VirtualDisk.nextParityPos) offset++;
			this.blocks[i] = new Block(entiers[i]);
		}
		this.generateParity();
	}*/

	public void generateParity() {
		Block reference[] = new Block[nBlocks-1];
		int i = 0;
		int j = 0;
		while(i < nBlocks) {
			if(i != VirtualDisk.nextParityPos) {
				reference[j] = blocks[i];
				j++;
			}
			i++;
		}		
		blocks[VirtualDisk.nextParityPos].computeParity(reference);
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
	
	public String content() {
		String buffer = "";
		for(int i = 0; i < nBlocks; i++) {
			if(i != parityPos) {
				buffer += blocks[i].content();
			}
		}
		return buffer;
	}
}
