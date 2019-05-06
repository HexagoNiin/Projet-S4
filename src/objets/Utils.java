package objets;

import java.nio.ByteBuffer;

public class Utils {

	/**
	 * give number of block for nb_octes bytes
	 * @param nb_octets number of byte
	 * @return number of block
	 */
	public static int compute_nblock(int nb_octets) {
		int nb_blocks = nb_octets / 4;
		if(nb_octets % 4 != 0) {
			nb_blocks++;
		}
		return nb_blocks;
	}

	/**
	 * give number of stripe for nb_octes bytes
	 * @param nb_octets number of byte
	 * @return number of stripe
	 */
	public static int compute_nstripe(int nb_blocks) {
		return nb_blocks / (VirtualDisk.nDisk - 1) + ((nb_blocks % (VirtualDisk.nDisk - 1) != 0) == true ? 1 : 0);
	}

	/**
	 * position of parity block for stripe
	 * @param numBande stripe's position
	 * @return parity block's position
	 */
	public static int compute_parity_index(int numBande) {
		return (VirtualDisk.nDisk - 1) - (numBande % VirtualDisk.nDisk);
	}

	/**
	 * resize original array from begin position with size size
	 * @param original resizing array
	 * @param begin resizing position
	 * @param size resizing size
	 * @return new SubArray
	 */
	public static byte [] subArray(byte [] original, int begin, int size) {
		byte newArray[] = new byte [size];
		for(int i = 0; i < size; i++) {
			if(i + begin >= original.length) {
				newArray[i] = 0;
			} else {
				newArray[i] = original[i + begin];
			}
		}
		return newArray;
	}

	/**
	 * Set a string's size
	 * @param s a string
	 * @param n the string's size
	 * @return a substring of s or s followed by some '\0'
	 */
	public static String setSize(String s, int n) {
		if(s.length() >= n) {
			return s.substring(0, n);
		} else {
			while(s.length() < n) {
				s += '\0';
			}
			return s;
		}
	}
	
	public static String trim(String s) {
		int i = 0;
		while(s.charAt(i) != 0) i++;
		return s.substring(0, i);
	}

	public static byte[] toBytes(int value) {
		return  ByteBuffer.allocate(4).putInt(value).array();
	}

	public static int toInt(byte[] bytes) {
	     return ByteBuffer.wrap(bytes).getInt();
	}
}
