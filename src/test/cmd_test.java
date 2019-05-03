package test;

import objets.*;

public class cmd_test {

	public static void main(String[] args) {
		VirtualDisk r5Disk = new VirtualDisk("systeme");
		Block b = new Block();
		b.setByte((byte) 1, 0);
		b.setByte((byte) 2, 1);
		b.setByte((byte) 3, 2);
		b.setByte((byte) 4, 3);
		b.write_block(0, r5Disk.getStorage()[0]);
		b.read_block(0, r5Disk.getStorage()[0]);
	}

}
