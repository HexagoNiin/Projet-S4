package objets;

public class InodeTable {
	private Inode [] tab;
	public static int tabSize = 10;
	private int nbInodes;
	
	public InodeTable() {
		nbInodes = 0;
		tab = new Inode[tabSize];
		for(int i = 0; i < tabSize; i++) {
			tab[i] = new Inode();
		}
	}
	
	public int add(String filename, int size, int first_byte) { //update_inode_table
		tab[nbInodes] = new Inode(filename, size, first_byte);
		nbInodes++;
		SuperBlock.setFirstFreeBytes(first_byte + size);
		return 0;
	}
	
	public int add(Inode inode) { //update_inode_table
		tab[nbInodes] = inode;
		nbInodes++;
		return 0;
	}
	
	public int delete(int pos) {
		for(int i = pos; i <= nbInodes; i++) {
			tab[i] = tab[i++];
		}
		nbInodes--;
		return 0;
	}
	
	public int delete(Inode inode) {
		int i = 0;
		while(tab[i] != inode && i < nbInodes) { i++; }
		if(i == nbInodes) { return -1; }
		for(int j = i; j <= nbInodes; j++) {
			tab[j] = tab[j++];
		}
		nbInodes--;
		return 0;
	}
	
	public int getUnused() {
		for(int i = 0; i < tabSize; i++) {
			if(tab[i].getFirstByte() == 0) {
				return i;
			}
		}
		return -1;
	}
	
	public Inode get(int pos) {
		return tab[pos];
	}
	
	public Inode get(String filename) {
		for(int i = 0; i < nbInodes; i++) {
			if(tab[i].getFilename().contentEquals(filename)) {
				return tab[i];
			}
		}
		return null;
	}
}
