package objets;

public class Inode {
	private String filename;
	private int size;
	private int first_byte;
	private int nblock;
	
	public Inode(String filename, int size, int first_byte, int nblock) {
		super();
		this.filename = filename;
		this.size = size;
		this.first_byte = first_byte;
		this.nblock = nblock;
	}

	public String getFilename() {
		return filename;
	}

	public int getSize() {
		return size;
	}

	public int getFirst_byte() {
		return first_byte;
	}

	public int getNblock() {
		return nblock;
	}
	
}
