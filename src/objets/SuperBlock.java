package objets;

public class SuperBlock {
	public static int size = 4;
	//private static int nbBlocksUsed;
	private static int firstFreeBytes;
	
	public static void addFirstFreeBytes(int new_bytes) {
		firstFreeBytes += new_bytes;
	}
	
	public static int getFirstFreeBytes() {
		return firstFreeBytes;
	}
}
