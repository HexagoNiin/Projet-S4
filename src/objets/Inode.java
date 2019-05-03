package objets;

public class Inode {
	private String filename;
	private int size;
	private int firstByte;
	private int nBlock;
	
	public Inode(String filename, int size, int first_byte, int nblock) {
		super();
		this.filename = filename;
		this.firstByte = first_byte;
		this.nBlock = nblock;
	}

	public String getFilename() {
		return filename;
	}

	public int getSize() {
		return size;
	}

	public int getFirstByte() {
		return firstByte;
	}

	public int getNblock() {
		return nBlock;
	}
}
