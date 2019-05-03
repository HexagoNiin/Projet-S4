package objets;

import java.io.*;

public class VirtualDisk {
	private static int number_of_files;
	private static SuperBlock super_block;
	private static InodeTable inodes;// tableau
	private static int ndisk;
	private static String raid; // type de RAID
    private static File [] storage; //tab[NUMBER_OF_DISKS];
    
    public VirtualDisk(String nom_rep) {
		File repertoire = new File("systeme");
		if(!(repertoire.exists() && repertoire.isDirectory())) {
			System.out.println("Impossible d'initialiser le disque virtuel : répertoire introuvable");
			return;
		}
    	storage = repertoire.listFiles();
    	/*Path chemin = Paths.get(nom_rep);
    	try (DirectoryStream<Path> stream = Files.newDirectoryStream(chemin)) {
    		int tailleStorage = 0;
    		for (Path file: stream) {
    	        tailleStorage++;
    	    }
    		storage = new File [tailleStorage];
    		tailleStorage = 0;
    	    for (Path file: stream) {
    	        storage[tailleStorage] = file;
    	        tailleStorage++;
    	    }
    	} catch (IOException | DirectoryIteratorException x) {
    	    // IOException can never be thrown by the iteration.
    	    // In this snippet, it can only be thrown by newDirectoryStream.
    	    System.err.println(x);
    	}*/ //JE SAIS PAS LIRE DES DOSSIERS EN JAVA C'EST L'ENFER
    	number_of_files = 0;
    }
    
    public VirtualDisk() {}
    
    public int getNDisk() { return ndisk; }
    
    public File [] getStorage() { return storage; }
}
