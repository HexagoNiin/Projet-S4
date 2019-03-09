package objets;

import java.io.*;

public class Block {
	
	public final static int BLOCK_SIZE = 4;
	private byte [] data;

	public Block() {
		data = new byte[BLOCK_SIZE];
	}
	
	public void setData(byte [] data) {
		this.data = data.clone();
	}
	/**
	 * @author Ugo EB-LEVADOUX, Axel GAUTHIER & Cédric MARTIN
	 * @param pos Position où écrire le block
	 * @param disk_id Disk sur lequel écrire le block	
	 * @return Un entier indiquant si l'opÃ©ration s'est bien passÃ©e (0 : OK, 1 : Erreur cast, 2 ; Erreur écriture) 
	 */
	
	public int write_block(int pos, File disk_id)  {
		FileOutputStream fos = null;
		try {
			fos = new FileOutputStream(disk_id);
		} catch (FileNotFoundException e1) {
			System.err.println("Le fichier n'a pas ete correctement ouvert en ecriture.");
			e1.printStackTrace();
			return 2;
		}
		try {
			fos.write(this.data, pos, BLOCK_SIZE);
			fos.close();
			return 0;
		} catch (IOException e) {
			System.err.println("Une erreur est survenue lors de l'ecriture du fichier.");
			e.printStackTrace();
			return 1;
		}
	}
	
	/**
	 * @author Ugo EB-LEVADOUX, Axel GAUTHIER & Cédric MARTIN
	 * @param pos Position du block eronné
	 * @param disks Tableau des disks utilisés par le RAID
	 * @param id_disk Index du disk avec le block eronné
	 * @param nbr_disks
	 * @return Un entier indiquant si l'opération s'est bien passée (0 : OK, 1 : Erreur lecture, 2 : Erreur écriture)
	 */
	
	public int block_repair(int pos, File [] disks, int id_disk, int nbr_disks) {
		Block block = new Block();
		for(int i = 0;i < nbr_disks; i++) {
			if(i != id_disk) {
				if(block.read_block(pos, disks[i]) == 0) {
					System.err.println("Une erreur est survenue, il y a au moins deux blocks qui ont ete corrompus.");
					return 1;
				}
				for(int j = 0;j < BLOCK_SIZE; j++) {
					this.data[i] = (byte)(this.data[i] ^ block.data[i]);
				}
			}
		}
		if(this.write_block(pos, disks[id_disk]) == 0) {
			return 0;
		}
		return 2;
	}
	
	public int read_block(int pos, File disk) {
		//TODO
		return 0;
	}

}
