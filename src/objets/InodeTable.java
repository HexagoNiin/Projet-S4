package objets;

import java.nio.ByteBuffer;

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
		tab[this.getUnused()] = new Inode(filename, size, first_byte);
		nbInodes++;
		SuperBlock.addFirstFreeBytes(Utils.compute_nstripe(Utils.compute_nblock(size)) * Block.nBytes);
		write();
		return 0;
	}
	
	public int add(Inode inode) {
		add(inode.getFilename(), inode.getSize(), inode.getFirstByte());
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
		tab[i] = new Inode();
		nbInodes--;
		return 0;
	}
	
	public int delete(String filename) {
		int i = 0;
		while(!tab[i].getFilename().equals(filename) && i < nbInodes) { i++; }
		if(i == nbInodes) { return -1; }
		tab[i] = new Inode();
		tab[i] = new Inode();
		nbInodes--;
		return 0;
	}
	
	public int getUnused() {
		for(int i = 0; i < tabSize; i++) {
			if(tab[i].getFirstByte() == -1) {
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
	
	public String toString() {
		String buffer = new String();
		for(int i = 0; i < nbInodes; i++) {
			buffer += "[" + i + "] " + tab[i] + "\n";
		}
		return buffer;
	}
	
	public int write() {
		for(int i = 0; i < tabSize; i++) {
			String rawWritable = tab[i].writable();
			System.out.println(rawWritable);
			String filename = rawWritable.substring(0, 32);
			int size = Utils.toInt(rawWritable.substring(32, 36).getBytes());
			int firstByte = Utils.toInt(rawWritable.substring(36, 40).getBytes());
			System.out.println(tab[i]);
			System.out.println(filename + "" + rawWritable.substring(32, 36) + Utils.toBytes(firstByte));
		}
		return 0;
	}
}
