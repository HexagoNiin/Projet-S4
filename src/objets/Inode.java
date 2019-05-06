package objets;

import java.nio.ByteBuffer;

public class Inode {
	private String filename;
	private int size;
	private int firstByte;
	
	public Inode() {
		filename = "";
		size = 0;
		firstByte = -1;
	}
	
	public Inode(String filename, int size, int first_byte) {
		this.filename = filename;
		this.size = size;
		this.firstByte = first_byte;
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
	
	public String toString() {
		return "(" + firstByte + ", " + filename + ", " + size + ")";
	}
	
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
