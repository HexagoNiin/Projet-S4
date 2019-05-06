package objets;

import java.io.*;


/**
 * @author MARTIN Cedric, GAUTHIER Axel && EB-LEVADOUX Ugo
 *	
 */
public class Block {
	
	public final static int nBytes = 4;
	private byte [] data;

	/**
	 * Block creation
	 */
	public Block() {
		data = new byte[nBytes];
		for(int i = 0; i < nBytes; i++) {
			data[i] = 0;
		}
	}
	
	/**
	 * Block creation
	 * @param b byte to store
	 */
	public Block(byte b) {
		data = new byte[nBytes];
		for(int i = 0; i < nBytes; i++) {
			data[i] = b;
		}
	}
	
	/**
	 * Block creation
	 * @param b byte array to store
	 */
	public Block(byte b []) {
		data = new byte[nBytes];
		for(int i = 0; i < nBytes; i++) {
			data[i] = b[i];
		}
	}
	
	/**
	 * Block creation
	 * @param nb int to store
	 */
	public Block(int nb) {
		data = new byte[nBytes];
		for(int i = 0; i < nBytes; i++) {
			data[i] = (byte) nb;
		}
	}
	
	/**
	 * Block creation
	 * @param nb int array to store
	 */
	public Block(int nb[]) {
		data = new byte[nBytes];
		for(int i = 0; i < nBytes; i++) {
			data[i] = (byte) nb[i];
		}
	}
	
	/**
	 * store data at i position
	 * @param data byte to store
	 * @param i storing position
	 */
	public void setByte(byte data, int i) {
		this.data[i] = data;
	}
		
	/**
	 * retrieve data at i position
	 * @param i retrieve position
	 * @return byte retrieved
	 */
	public Byte getByte(int i) {
		return this.data[i];
	}
	
	/**
	 * write block's data to disk at pos position
	 * @param pos writing position
	 * @param disk_id writing disk
	 * @return 0 if OK else 1 if writing issue 
	 */
	public int write(int pos, File disk_id) {
		try {
			RandomAccessFile file = new RandomAccessFile(disk_id, "rw");
			file.seek(pos);
			file.write(data);
			file.close();
		} catch (IOException e) {
			System.err.println("Une erreur est survenue lors de l'écriture du bloc");
			e.printStackTrace();
			return 1;
		}
		return 0;
	}
	
	/**
	 * read disk's data at pos position and store it in block
	 * @param pos reading position
	 * @param disk_id reading disk
	 * @return 0 if OK else 1 if reading issue
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
	 * repair disk at pos position
	 * @param pos repairing position
 	 * @param id_disk repairing disk
	 * @return 0 if OK else 1 if to much damage or 2 if repairing issue
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
	
	/**
	 * create compute parity block
	 * @param blocks blocks array 
	 */
	public void	computeParity(Block blocks []) {
		data = blocks[0].data.clone();
		for(int i = 1; i < blocks.length; i++) {
			for(int j = 0; j < nBytes; j++) {
				data[j] ^= blocks[i].data[j];
			}
		}
	}
	
	/* (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	public String toString() {
		String buffer = "[";
		for(int i = 0; i < nBytes; i++) {
			buffer += String.format("%2h", data[i]);
			if(i != nBytes-1) buffer += ", ";
		}
		return buffer + "]";
	}
	
	/**
	 * retrieve buffer of block's data
	 * @return block's content
	 */
	public String content() {
		String buffer = "";
		for(int i = 0; i < nBytes && data[i] != 0; i++) {
			buffer += (char) data[i];
		}
		return buffer;
	}
}
