package test;

import objets.*;

public class cmd_test {

	public static void main(String[] args) {	
		new VirtualDisk("systeme");
		
		System.out.println("Écriture d'un block :");
		Block b = new Block(1);
		System.out.println(b.toString());
		b.write(0, VirtualDisk.storage[0]);
		
		System.out.println("Lecture d'un block :");
		b.read(0, VirtualDisk.storage[0]);
		System.out.println(b.toString());
		
		System.out.println();
	}

}
