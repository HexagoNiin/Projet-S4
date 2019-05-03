package objets;

public class InodeTable {
	private Inode [] tab;
	private int nbInodes;
	
	public InodeTable() {
		nbInodes = 0;
	}
	
	public int update_inode_table(Inode inode) {
		tab[nbInodes] = inode;
		nbInodes++;
		return 0;
	}
}
