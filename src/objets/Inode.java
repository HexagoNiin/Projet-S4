package objets;

import java.nio.ByteBuffer;

public class Inode {
	private String filename;
	private int size;
	private int firstByte;

	/**
	 * Inode creation
	 */
	public Inode() {
		filename = "";
		size = 0;
		firstByte = -1;
	}

	/**
	 * Inode creation
	 * @param filename name of file
	 * @param size size of file
	 * @param first_byte first position of file
	 */
	public Inode(String filename, int size, int first_byte) {
		this.filename = filename;
		this.size = size;
		this.firstByte = first_byte;
	}

	/**
	 * retrieve filename
	 * @return filename retrieved
	 */
	public String getFilename() {
		return filename;
	}

	/**
	 * retrieve size
	 * @return size retrieved
	 */
	public int getSize() {
		return size;
	}

	/**
	 * retrieve firstByte
	 * @return firstByte retrieved
	 */
	public int getFirstByte() {
		return firstByte;
	}

	/* (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	public String toString() {
		return "(" + firstByte + ", " + filename + ", " + size + ")";
	}

	/**
	 * if inode is empty
	 * @return true if empty else false
	 */
	public boolean empty() {
		return firstByte == -1;
	}

	public String writable() {
		byte [] sizeBytes = Utils.toBytes(size);
		byte [] firstByteBytes = Utils.toBytes(firstByte);
		System.out.println(sizeBytes + " " + firstByteBytes);
		return Utils.setSize(filename, 32) + sizeBytes.toString() + firstByteBytes.toString();
	}
}
