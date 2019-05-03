package objets;

public class SuperBlock {
	private int nbBlocksUsed;
	private int firstFreeBytes;
	
	public void setFirstFreeBytes(int new_bytes) {
		this.firstFreeBytes += new_bytes;
	}
}
