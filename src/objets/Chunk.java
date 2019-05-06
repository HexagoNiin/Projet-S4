package objets;


/**
 * @author MARTIN Cedric, GAUTHIER Axel && EB-LEVADOUX Ugo
 *	
 */
public class Chunk {
	private Stripe [] stripes;
	private int nStripes;

	/**
	 * Chunck creation
	 * @param nChars size of chunck
	 */
	public Chunk(int nChars) {
		nStripes = Utils.compute_nstripe(Utils.compute_nblock(nChars));
		stripes = new Stripe[nStripes];
		for(int i = 0; i < nStripes; i++) {
			stripes[i] = new Stripe();
		}
	}

	/**
	 * Chunck creation
	 * @param buffer writing byte area
	 * @param nChars size of chunck
	 */
	public Chunk(byte [] buffer, int nChars) {
		this(nChars);
		for(int i = 0; i < nStripes; i++) {
			System.out.println("Next Parity : " + VirtualDisk.nextParityPos);
			stripes[i] = new Stripe(Utils.subArray(buffer, i * (Stripe.nBlocks - 1) * Block.nBytes, (Stripe.nBlocks - 1) * Block.nBytes));
		}
	}

	/**
	 * Chunck creation
	 * @param buffer writing string
	 * @param nChars size of chunck
	 */
	public Chunk(String buffer, int nChars) {
		this(buffer.getBytes(), nChars);
	}
	
	/**
	 * Chunck creation
	 * @param buffer writing string
	 */
	public Chunk(String buffer) {
		this(buffer, buffer.length());
	}

	
	/**
	 * write Chunck on vistualdisk from starbyte position
	 * @param startbyte writing position
	 * @return 0 if OK else 1 if writing issue
	 */
	public int write(int startbyte) {
		for(int i = 0; i < nStripes; i++) {
			if (stripes[i].write(startbyte + (i * Stripe.nBlocks)) != 0) {
				System.err.println("Erreur lors de l'�criture du chunk.");
				return 1;
			}
		}
		return 0;
	}

	/**
	 * read Chunck on vistualdisk from starbyte position
	 * @param startbyte reading position
	 * @return 0 if OK else 1 if reading issue
	 */
	public int read(int startbyte) {
		for(int i = 0; i < nStripes; i++) {
			if(stripes[i].read(startbyte + (i * Stripe.nBlocks)) != 0) {
				System.err.println("Erreur lors de la lecture du chunk.");
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
		for(int i = 0; i < nStripes; i++) {
			if(i != 0) buffer += " ";
			buffer += stripes[i];
			if(i != nStripes - 1) buffer += ",\n";
		}
		return buffer + "]";
	}
	
	/**
	 * retrieve buffer of chunck's data
	 * @return chunck's content
	 */
	public String content() {
		String buffer = "";
		for(int i = 0; i < nStripes; i++) {
			buffer += stripes[i].content();
		}
		return buffer;
	}
}
