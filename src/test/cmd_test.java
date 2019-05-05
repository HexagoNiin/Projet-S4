package test;

import objets.*;

public class cmd_test {

	public static void main(String[] args) {	
		new VirtualDisk("systeme");
		
		/* BLOCK */
		System.out.println("…criture d'un block :");
		Block b1 = new Block(1);
		System.out.println(b1);
		b1.write(0, VirtualDisk.storage[0]);
		
		System.out.println("\nLecture d'un block :");
		Block b2 = new Block();
		b2.read(0, VirtualDisk.storage[0]);
		System.out.println(b2);
		
		/* STRIPE */
		System.out.println("\n…criture d'une stripe :");
		byte chaine[] = "123456789abc".getBytes();
		Stripe s1 = new Stripe(chaine);
		System.out.println(s1);
		s1.write(0);
		
		System.out.println("\nLecture d'un block :");
		Stripe s2 = new Stripe();
		s2.read(0);
		System.out.println(s2);
		
		/* CHUNK */
	}

}
