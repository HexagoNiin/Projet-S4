package objets;


/**
 * @author MARTIN Cedric, GAUTHIER Axel && EB-LEVADOUX Ugo
 *	
 */
public class SuperBlock {
	public static int size = 4;
	private static int firstFreeBytes = Utils.compute_nstripe(Utils.compute_nblock(size + InodeTable.tabSize * 40)) * Stripe.nBlocks * Block.nBytes;
	
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
	
	/**
	 *  Write the SuperBlock on the disk
	 */
	public static void write() {
		System.out.println(Utils.toBytes(firstFreeBytes));
		new Chunk(Utils.toBytes(firstFreeBytes), size).write(0);
	}
	
	/**
	 * Read the SuperBlock on the disk
	 */
	public static void read() {
		Chunk c = new Chunk(size);
		c.read(0);
		System.out.println(Utils.toInt(c.rawContent().getBytes()));
	}
}
