package objets;

import java.io.*;

public class Block {
	
	public final static int nBytes = 4;
	private byte [] data;

	public Block() {
		data = new byte[nBytes];
		for(int i = 0; i < nBytes; i++) {
			data[i] = 0;
		}
	}
	
	public Block(byte b) {
		data = new byte[nBytes];
		for(int i = 0; i < nBytes; i++) {
			data[i] = b;
		}
	}
	
	public Block(byte b []) {
		data = new byte[nBytes];
		for(int i = 0; i < nBytes; i++) {
			data[i] = b[i];
		}
	}
	
	public Block(int nb) {
		data = new byte[nBytes];
		for(int i = 0; i < nBytes; i++) {
			data[i] = (byte) nb;
		}
	}
	
	public Block(int nb[]) {
		data = new byte[nBytes];
		for(int i = 0; i < nBytes; i++) {
			data[i] = (byte) nb[i];
		}
	}
	
	public void setByte(byte data, int i) {
		this.data[i] = data;
	}
	
	
	public Byte getByte(int i) {
		return this.data[i];
	}
	
	
	/**
	 * @author Ugo EB-LEVADOUX, Axel GAUTHIER & Cedric MARTIN
	 * @param pos Position o� �crire le block
	 * @param disk_id Disk sur lequel �crire le block	
	 * @return Un entier indiquant si l'opération s'est bien passée (0 : OK, 1 : Erreur cast, 2 ; Erreur �criture) 
	 */
	
	public int write(int pos, File disk_id) {
		try {
			RandomAccessFile file = new RandomAccessFile(disk_id, "rw");
			file.seek(pos);
			file.write(data);
			file.close();
		} catch (IOException e) {
			System.err.println("Une erreur est survenue lors de l'�criture du bloc");
			e.printStackTrace();
			return 1;
		}
		return 0;
	}
	
	/**
	 * @author Ugo EB-LEVADOUX, Axel GAUTHIER & Cedric MARTIN
	 * @param pos Position du block à lire
	 * @param id_disk Index du disk avec le block à lire
	 * @return Un entier indiquant si l'op�ration s'est bien pass�e (0 : OK, 1 : Erreur d'ouverture, 2 : Erreur de lecture)
	 */
	public int read(int pos, File disk_id) {
		try {
			RandomAccessFile file = new RandomAccessFile(disk_id, "r");
			file.seek(pos);
			file.read(data);
			file.close();
			
		} catch (IOException e) {
			System.err.println("Une erreur est survenue lors de la lecture du bloc.");
			e.printStackTrace();
			return 1;
		}
		return 0;
	}
	
	/**
	 * @author Ugo EB-LEVADOUX, Axel GAUTHIER & Cedric MARTIN
	 * @param pos Position du block eronn�
	 * @param disks Tableau des disks utilis�s par le RAID
	 * @param id_disk Index du disk avec le block eronn�
	 * @param nbr_disks
	 * @return Un entier indiquant si l'op�ration s'est bien pass�e (0 : OK, 1 : Erreur lecture, 2 : Erreur �criture)
	 */
	
	public int repair(int pos, int id_disk) {
		Block block = new Block();
		for(int i = 0;i < VirtualDisk.nDisk; i++) {
			if(i != id_disk) {
				if(block.read(pos, VirtualDisk.storage[i]) == 0) {
					System.err.println("Une erreur est survenue, il y a au moins deux blocks qui ont ete corrompus.");
					return 1;
				}
				for(int j = 0;j < nBytes; j++) {
					this.data[i] = (byte)(this.data[i] ^ block.data[i]);
				}
			}
		}
		if(this.write(pos, VirtualDisk.storage[id_disk]) == 0) {
			return 0;
		}
		return 2;
	}
	
	
	public void	computeParity(Block blocks []) {
		data = blocks[0].data.clone();
		for(int i = 1; i < blocks.length; i++) {
			for(int j = 0; j < nBytes; j++) {
				data[j] ^= blocks[i].data[j];
			}
		}
	}
	
	/**
	 * @author Ugo EB-LEVADOUX, Axel GAUTHIER & Cedric MARTIN
	 * @param this bloc à afficher
	 */
	
	public String toString() {
		String buffer = "[";
		for(int i = 0; i < nBytes; i++) {
			buffer += String.format("%2h", data[i]);
			if(i != nBytes-1) buffer += ", ";
		}
		return buffer + "]";
	}
	
	public String content() {
		String buffer = "";
		for(int i = 0; i < nBytes && data[i] != 0; i++) {
			buffer += (char) data[i];
		}
		return buffer;
	}
}
