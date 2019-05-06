package objets;


/**
 * @author MARTIN Cedric, GAUTHIER Axel && EB-LEVADOUX Ugo
 *	
 */
public class InodeTable {
	private Inode [] tab;
	public static int tabSize = 10;
	private int nbInodes;
	
	/**
	 * InodeTable creation
	 */
	public InodeTable() {
		nbInodes = 0;
		tab = new Inode[tabSize];
		for(int i = 0; i < tabSize; i++) {
			tab[i] = new Inode();
		}
	}
	
	/**
	 * add new element to InodeTable
	 * @param filename name of the new file
	 * @param size size of the new file
	 * @param first_byte first position of the new file
	 * @return 0 if OK
	 */
	public int add(String filename, int size, int first_byte) { //update_inode_table
		tab[this.getUnused()] = new Inode(filename, size, first_byte);
		nbInodes++;
		SuperBlock.addFirstFreeBytes(Utils.compute_nstripe(Utils.compute_nblock(size)) * Block.nBytes);
		return 0;
	}
	
	/**
	 * add new element to InodeTable
	 * @param inode adding element
	 * @return 0 if OK
	 */
	public int add(Inode inode) {
		add(inode.getFilename(), inode.getSize(), inode.getFirstByte());
		return 0;
	}
	
	/**
	 * delete element from InodeTable at pos position
	 * @param pos deleting position
	 * @return 0 if OK
	 */
	public int delete(int pos) {
		for(int i = pos; i <= nbInodes; i++) {
			tab[i] = tab[i++];
		}
		nbInodes--;
		return 0;
	}
	
	/**
	* delete inode element from InodeTable
	 * @param inode deleting element
	 * @return 0 if OK
	 */
	public int delete(Inode inode) {
		int i = 0;
		while(tab[i] != inode && i < nbInodes) { i++; }
		if(i == nbInodes) { return -1; }
		for(int j = i; j <= nbInodes; j++) {
			tab[j] = tab[j++];
		}
		tab[i] = new Inode();
		nbInodes--;
		return 0;
	}
	
	/**
	 * delete element from InodeTable with filename name
	 * @param filename deleting name
	 * @return 0 if OK
	 */
	public int delete(String filename) {
		int i = 0;
		while(!tab[i].getFilename().equals(filename) && i < nbInodes) { i++; }
		if(i == nbInodes) { return -1; }
		tab[i] = new Inode();
		tab[i] = new Inode();
		nbInodes--;
		return 0;
	}
	
	/**
	 * retrieve first unused inode
	 * @return first unused inode retrieved
	 */
	public int getUnused() {
		for(int i = 0; i < tabSize; i++) {
			if(tab[i].getFirstByte() == -1) {
				return i;
			}
		}
		return -1;
	}
	
	/**
	 * retrieve inode at pos position
	 * @param pos retrieving position 
	 * @return inode retrieved
	 */
	public Inode get(int pos) {
		return tab[pos];
	}
	
	/**
	 * retrieve inode with filename name
	 * @param filename retrieving name 
	 * @return inode retrieved
	 */
	public Inode get(String filename) {
		for(int i = 0; i < nbInodes; i++) {
			if(tab[i].getFilename().contentEquals(filename)) {
				return tab[i];
			}
		}
		return null;
	}
	
	/* (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	public String toString() {
		String buffer = new String();
		for(int i = 0; i < nbInodes; i++) {
			buffer += "[" + i + "] " + tab[i] + "\n";
		}
		return buffer;
	}
}
