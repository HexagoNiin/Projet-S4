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
		Stripe s3 = new Stripe(chaine);
		System.out.println(s3);
		Stripe s4 = new Stripe(chaine);
		System.out.println(s4);
		Stripe s5 = new Stripe(chaine);
		System.out.println(s5);
		s1.write(0);
		
		System.out.println("\nLecture d'une stripe :");
		Stripe s2 = new Stripe();
		s2.read(0);
		System.out.println(s2);
		
		/* CHUNK */
		System.out.println("\n…criture d'un chunk :");
		String message = "Yo wot da fuk you're sniffing in a plastic bag, the boosta stincka glue to be the supa street fighter";
		Chunk c1 = new Chunk(message);
		System.out.println(c1.content() + " :\n" + c1);
		c1.write(0);
		
		System.out.println("\nLecture d'un chunk :");
		Chunk c2 = new Chunk(message.length());
		c2.read(0);
		System.out.println(c2.content() + " :\n" + c2);
		
		/*FILEHANDLER*/
		new VirtualDisk("systeme");
		System.out.println("\n…criture d'un fichier :");
		FileHandler f1 = new FileHandler("tests/paperboats.txt");
		f1.write();
		System.out.println(f1);
		
		System.out.println("\nLecture d'un fichier :");
		FileHandler f2 = new FileHandler();
		f2.read(VirtualDisk.inodes.get(0));
		f2.toHost();
		System.out.println(f2);
	}
}
