package objets;

public class InodeTable {
	private Inode [] tab;
	public static int tabSize = 10;
	private int nbInodes;
	
	public InodeTable() {
		nbInodes = 0;
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
}
