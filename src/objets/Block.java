package objets;

import java.io.*;

public class Block {
	
	public final static int BLOCK_SIZE = 4;
	private byte [] data;

	public Block() {
		data = new byte[BLOCK_SIZE];
		for(int i = 0; i < BLOCK_SIZE; i++) {
			data[i] = (byte) '\0';
		}
	}
	
	public void setByte(byte data, int i) {
		this.data[i] = data;
	}
	/**
	 * @author Ugo EB-LEVADOUX, Axel GAUTHIER & Cedric MARTIN
	 * @param pos Position o� �crire le block
	 * @param disk_id Disk sur lequel �crire le block	
	 * @return Un entier indiquant si l'opération s'est bien passée (0 : OK, 1 : Erreur cast, 2 ; Erreur �criture) 
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
	 * @author Ugo EB-LEVADOUX, Axel GAUTHIER & Cedric MARTIN
	 * @param pos Position du block eronn�
	 * @param disks Tableau des disks utilis�s par le RAID
	 * @param id_disk Index du disk avec le block eronn�
	 * @param nbr_disks
	 * @return Un entier indiquant si l'op�ration s'est bien pass�e (0 : OK, 1 : Erreur lecture, 2 : Erreur �criture)
	 */
	
	public int block_repair(int pos, int id_disk) {
		Block block = new Block();
		for(int i = 0;i < (new VirtualDisk()).getNDisk(); i++) {
			if(i != id_disk) {
				if(block.read_block(pos, (new VirtualDisk()).getStorage()[i]) == 0) {
					System.err.println("Une erreur est survenue, il y a au moins deux blocks qui ont ete corrompus.");
					return 1;
				}
				for(int j = 0;j < BLOCK_SIZE; j++) {
					this.data[i] = (byte)(this.data[i] ^ block.data[i]);
				}
			}
		}
		if(this.write_block(pos, (new VirtualDisk()).getStorage()[id_disk]) == 0) {
			return 0;
		}
		return 2;
	}
	
	public int read_block(int pos, File disk) {
		//TODO
		return 0;
	}

}
