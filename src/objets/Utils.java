package objets;

public class Utils {
	public int compute_nblock(int nb_octets) {
		int nb_blocks = nb_octets / 4;
		if(nb_octets % 4 != 0) {
			nb_blocks++;
		}
		return nb_blocks;
	}
	
	/**
	 * Calcule le nombre de blocks necessaires pour ecrire une chaine de bytes sur le systeme RAID
	 * Prend en compte les blocks de parites.
	 * @param nb_disks Nombre de disks du systeme RAID.
	 * @return Nombre de blocks.
	 */
	/*public int compute_final_nblock(int nb_disks) {
		int nChunks = this.compute_nblock();
		int nStripes = this.compute_nstripe(nChunks);
		return nChunks + nStripes + ((nChunks + nStripes) / nb_disks);
	}*/

	
	public int compute_nstripe(int nb_blocks) {
		return nb_blocks / (new VirtualDisk().getNDisk() - 1) + ((nb_blocks % (new VirtualDisk().getNDisk() - 1) != 0) == true ? 1 : 0);
	}
	
	public int compute_parity_index(int numBande) {
		return (new VirtualDisk().getNDisk() - 1) - (numBande % new VirtualDisk().getNDisk());
	}
	
	public Block compute_parity(Block [] blocks, int i) {
		return new Block();
	}
}
