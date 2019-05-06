package objets;


/**
 * @author MARTIN Cedric, GAUTHIER Axel && EB-LEVADOUX Ugo
 *	
 */
public class SuperBlock {
	public static int size = 4;
	private static int firstFreeBytes;
	
	/**
	 * add new firstByte
	 * @param new_bytes adding firstByte
	 */
	public static void addFirstFreeBytes(int new_bytes) {
		firstFreeBytes += new_bytes;
	}
	
	/**
	 * retrieve firstByte
	 * @return firstByte retrieved
	 */
	public static int getFirstFreeBytes() {
		return firstFreeBytes;
	}
}
