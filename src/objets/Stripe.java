package objets;

/**
 * @author MARTIN Cedric, GAUTHIER Axel && EB-LEVADOUX Ugo
 *	
 */
public class Stripe {

	public static int nBlocks = VirtualDisk.nDisk;
	private Block [] blocks;
	private int parityPos;

	/**
	 * Stripe creation
	 */
	public Stripe() {
		parityPos = VirtualDisk.nextParityPos;
		blocks = new Block[nBlocks];
		for(int i = 0; i < nBlocks; i++) {
			blocks[i] = new Block();
		}
	}
	
	/**
	 * Stripe creation
	 * @param bytes byte array to store
	 */
	public Stripe(byte bytes[]) {
		this();
		for(int i = 0; i < Stripe.nBlocks-1; i++) {
			blocks[i + (i>=parityPos?1:0)] = new Block(Utils.subArray(bytes, i * Block.nBytes, Block.nBytes));
		}
		this.generateParity();
	}

	/**
	 * generate parity to Stripe
	 */
	public void generateParity() {
		Block reference[] = new Block[nBlocks-1];
		int i = 0;
		int j = 0;
		while(i < nBlocks) {
			if(i != parityPos) {
				reference[j] = blocks[i];
				j++;
			}
			i++;
		}		
		blocks[parityPos].computeParity(reference);
		VirtualDisk.nextParityPos = (VirtualDisk.nextParityPos + nBlocks-1) % nBlocks;
	}

	/**
	 * retrieve number of blocks
	 * @return length retrieved
	 */
	public int getNBlocks() {
		return Stripe.nBlocks;
	}

	/**
	 * retrieve block at index position
	 * @param index retrieving position
	 * @return block retrieved
	 */
	public Block getIStripe(int index) {
		return this.blocks[index];
	}

	/**
	 * set the number of block
	 * @param nblocks number of block
	 */
	public void setNBlocks(int nblocks) {
		Stripe.nBlocks = nblocks;
	}

	/**
	 * set block at i position in stripe
	 * @param block to set in stripe
	 * @param i position to set in stripe
	 */
	public void setIStripe(Block block, int i) {
		this.blocks[i] = block;
	}

	/**
	 * write stripe at pos position in virtualdisk
	 * @param pos writing position
	 * @return 0 if OK else 1 if writing issue
	 */
	public int write(int pos) {
		//System.out.println("POS : " + pos);
		//System.out.println(Utils.compute_parity_index(pos/Block.nBytes));
		parityPos = Utils.compute_parity_index(pos / Block.nBytes);
		for(int i = 0; i < this.getNBlocks(); i++) {
			if(this.blocks[i].write(pos , VirtualDisk.storage[i]) != 0) {
				System.err.println("Erreur lors de l'écriture de la bande.");
				return 1;
			}
		}
		//System.out.println(this);
		return 0;
	}

	/**
	 * read virtualdisk at pos position and restore it in stripe 
	 * @param pos reading position
	 * @return 0 if OK else 1 if reading issue
	 */
	public int read(int pos) {
		parityPos = Utils.compute_parity_index(pos / Block.nBytes);
		for(int i = 0; i < Stripe.nBlocks; i++) {
			if(this.blocks[i].read(pos, VirtualDisk.storage[i]) != 0) {
				System.err.println("Erreur lors de la lecture de la bande.");
				return 1;
			}
		}
		return 0;
	}
	
	/* (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	public String toString() {
		String buffer = "[";
		for(int i = 0; i < nBlocks; i++) {
			if(i == parityPos) buffer += Color.RED_BRIGHT;
			buffer += blocks[i].toString();
			if(i == parityPos) buffer += Color.RESET;
			if(i != nBlocks-1) {
				buffer += ", ";
			}
		}
		return buffer + "]";
	}
	
	/**
	 * retrieve buffer of stripe's data
	 * @return stripe's content
	 */
	public String content() {
		String buffer = "";
		for(int i = 0; i < nBlocks; i++) {
			if(i != parityPos) {
				buffer += blocks[i].content();
			}
		}
		return buffer;
	}
	
	public String rawContent() {
		String buffer = "";
		for(int i = 0; i < nBlocks; i++) {
			if(i != parityPos) {
				buffer += blocks[i].rawContent();
			}
		}
		return buffer;
	}
}
