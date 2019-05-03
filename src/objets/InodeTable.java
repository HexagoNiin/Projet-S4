package objets;

public class InodeTable {
	private Inode [] tab;
	public static int tabSize = 10;
	private int nbInodes;
	
	public InodeTable() {
		nbInodes = 0;
	}
	
	public int add(Inode inode) {
		tab[nbInodes] = inode;
		nbInodes++;
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
