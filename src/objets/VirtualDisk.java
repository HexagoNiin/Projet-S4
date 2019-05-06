package objets;

import java.io.*;

public class VirtualDisk {
	public static int numberOfFiles;
	public static SuperBlock superBlock;
	public static InodeTable inodes = new InodeTable();// tableau
	public static int nDisk = 4;
	public static String raid; // type de RAID
	public static File [] storage = new File[nDisk]; //tab[NUMBER_OF_DISKS];
	public static int nextParityPos = nDisk-1;
    
    public VirtualDisk(String nom_rep) {
		File repertoire = new File(nom_rep);
		if(!(repertoire.exists() && repertoire.isDirectory())) {
			System.out.println("Impossible d'initialiser le disque virtuel : répertoire introuvable");
			return;
		}
		nextParityPos = nDisk-1;
    	storage = repertoire.listFiles();
    	nDisk = storage.length;
    	numberOfFiles = 0;
    }
    
    public VirtualDisk() {}
}
