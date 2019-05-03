package test;

import objets.*;

public class cmd_test {

	public static void main(String[] args) {
		VirtualDisk r5Disk = new VirtualDisk("systeme");
		
		System.out.println("Écriture d'un block :");
		Block b = new Block();
		b.setByte((byte) 1, 0);
		b.setByte((byte) 2, 1);
		b.setByte((byte) 3, 2);
		b.setByte((byte) 4, 3);
		b.display();
		b.write(0, VirtualDisk.storage[0]);
		
		System.out.println("Lecture d'un block :");
		b.read(0, VirtualDisk.storage[0]);
		b.display();
		
		System.out.println();
	}

}
