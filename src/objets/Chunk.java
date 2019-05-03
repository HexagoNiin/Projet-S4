package objets;

public class Chunk {
	private Stripe [] stripes;
	private int nStripe;

	public Chunk(byte [] buffer, int nChars) {
		this.stripes = generate(buffer, nChars);
		this.nStripe = new Utils().compute_nstripe(new Utils().compute_nblock(nChars));
	}

	public Chunk(String Sbuffer, int nChars) {
		byte [] buffer = Sbuffer.getBytes().clone();
		this.stripes = generate(buffer, nChars);
		this.nStripe = new Utils().compute_nstripe(new Utils().compute_nblock(nChars));
	}

	/**
	 * Transforme une partie du buffer en nb_disks - 1 blocks.
	 * La position courante sur le buffer est incremente du nombre de caracteres lu.
	 * @param nb_disks Nombre de disks du systeme
	 * @return nd_disks - 1 blocks
	 */
	private Stripe [] generate(byte [] buffer, int nChars)  {
		Stripe [] stripes = new Stripe[(new VirtualDisk()).getNDisk()];

		byte [] writeBuffer = new byte [((new VirtualDisk()).getNDisk()-1) * Block.size];
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
	}

	/**
	 * Ecrit une chaine de bytes sur le systeme RAID.
	 * @param startbyte Position ou ecrire la bande sur le systeme RAID.
	 * @param disks Systeme RAID.
	 * @return 0 si OK, 1 si Erreur.
	 */
	public int write(int startbyte) {
		for(int i = 0; i < nStripe; i++) {
			if (stripes[i].write(startbyte+i) != 0) {
				System.err.println("Erreur lors de l'écriture du chunck.");
				return 1;
			}
		}
		return 0;
	}
	
	/**
	 * lit une chaine de bytes sur le systeme RAID.
	 * @param startbyte Position ou lire la bande sur le systeme RAID.
	 * @param disks Systeme RAID.
	 * @return 0 si OK, 1 si Erreur.
	 */
	public int read(int startbyte) {
		for(int i = 0; i < nStripe; i++) {
			if (stripes[i].read(startbyte+i) != 0) {
				System.err.println("Erreur lors de l'écriture du chunck.");
				return 1;
			}
		}
		return 0;
	}


}
