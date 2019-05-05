package objets;

public class Chunk {
	private Stripe [] stripes;
	private int nStripes;

	public Chunk(int nChars) {
		nStripes = Utils.compute_nstripe(Utils.compute_nblock(nChars));
		stripes = new Stripe[nStripes];
	}

	public Chunk(byte [] buffer, int nChars) {
		this(nChars);
		for(int i = 0; i < nStripes; i++) {
			stripes[i] = new Stripe(Utils.subArray(buffer, i * (Stripe.nBlocks - 1) * Block.nBytes, (Stripe.nBlocks - 1) * Block.nBytes));
		}
	}

	public Chunk(String buffer, int nChars) {
		this(buffer.getBytes(), nChars);
	}
	
	public Chunk(String buffer) {
		this(buffer, buffer.length());
	}

	/**
	 * Ecrit une chaine de bytes sur le systeme RAID.
	 * @param startbyte Position ou ecrire la bande sur le systeme RAID.
	 * @param disks Systeme RAID.
	 * @return 0 si OK, 1 si Erreur.
	 */
	public int write(int startbyte) {
		for(int i = 0; i < nStripes; i++) {
			if (stripes[i].write(startbyte + (i * Stripe.nBlocks * Block.nBytes)) != 0) {
				System.err.println("Erreur lors de l'�criture du chunk.");
				return 1;
			}
		}
		return 0;
	}

	public int read(int startbyte) {
		for(int i = 0; i < nStripes; i++) {
			if(stripes[i].read(startbyte + (i * Stripe.nBlocks * Block.nBytes)) != 0) {
				System.err.println("Erreur lors de la lecture du chunk.");
				return 1;
			}
		}
		return 0;
	}

	public String toString() {
		String buffer = "[";
		for(int i = 0; i < nStripes; i++) {
			if(i != 0) buffer += " ";
			buffer += stripes[i];
			if(i != nStripes - 1) buffer += ",\n";
		}
		return buffer + "]";
	}
	
	public String content() {
		String buffer = "";
		for(int i = 0; i < nStripes; i++) {
			buffer += stripes[i].content();
		}
		return buffer;
	}

	/**
	 * Transforme une partie du buffer en nb_disks - 1 blocks.
	 * La position courante sur le buffer est incremente du nombre de caracteres lu.
	 * @param nb_disks Nombre de disks du systeme
	 * @return nd_disks - 1 blocks
	 */
	/*private Stripe [] generate(byte [] buffer, int nChars)  {
		Stripe [] stripes = new Stripe[VirtualDisk.nDisk];

		byte [] writeBuffer = new byte [((new VirtualDisk()).getNDisk()-1) * Block.BLOCK_SIZE];
		int i = 0;
		int posStripe = 0;
		while (i < nChars) {
			for(int u = 0; u < writeBuffer.length ; u++) {

				writeBuffer[u] = buffer[i + u];
			}
			i += writeBuffer.length;

			stripes[posStripe] = new Stripe(writeBuffer);
			posStripe ++;

		}

		return stripes;
	}*/

	/**
	 * lit une chaine de bytes sur le systeme RAID.
	 * @param startbyte Position ou lire la bande sur le systeme RAID.
	 * @param disks Systeme RAID.
	 * @return Buffer l'ensemble des données lus.
	 **/
	/*public byte [] read(int startbyte) {
		Block block;
		byte [] buffer = new byte [nStripe * ((new VirtualDisk()).getNDisk()-1) * Block.BLOCK_SIZE];
		int pos = 0;

		if (this.preread(startbyte) != 0)
			return buffer;

		for(int i = 0; i < nStripe; i++) {
			for(int j = 0; j < VirtualDisk.nDisk; j++) {
				if ( Utils.compute_parity_index(startbyte + i) != j ) {
					block = stripes[i].getIStripe(j);
					for(int u = 0; u < Block.size; u++) {
						buffer[pos++] = block.getByte(u);
					}
				}
			}
		}
		return buffer;
	}*/

	/*private int preread(int startbyte) {
		for(int i = 0; i < nStripes; i++) {
			if (stripes[i].read(startbyte+i) != 0) {
				System.err.println("Erreur lors de l'écriture du chunck.");
				return 1;
			}
		}
		return 0;

	}*/
}
