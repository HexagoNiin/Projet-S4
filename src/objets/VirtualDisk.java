package objets;

import java.io.*;
import java.nio.file.*;

public class VirtualDisk {
	private int number_of_files;
	private SuperBlock super_block;
	private TableInode inodes;// tableau
	private int ndisk;
	private String raid; // type de RAID
    private File [] storage; //tab[NUMBER_OF_DISKS];
    
    public VirtualDisk(String nom_rep) {
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
}
