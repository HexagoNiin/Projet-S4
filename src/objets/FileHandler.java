package objets;

import java.io.*;

/**
 * @author MARTIN Cedric, GAUTHIER Axel && EB-LEVADOUX Ugo
 *	
 */
public class FileHandler {
	private String filename;
	private int size;
	private Chunk data;
	
	/**
	 * FileHandler creation
	 * @param filename name of file
	 */
	public FileHandler(String filename) {
		System.out.println(filename);
		this.filename = filename;
		try {
			FileInputStream file = new FileInputStream(new File(filename));
			size = file.available();
			byte buffer[] = new byte[size];
			file.read(buffer);
			data = new Chunk(buffer, size);
			file.close();
		} catch(IOException e) {
			System.err.println("Le fichier n'a pas été correctement ouvert en lecture");
			e.printStackTrace();
			return;
		}
	}
	
	/**
	 * FileHandler creation
	 */
	public FileHandler() {
		filename = null;
		size = 0;
		data = null;
	}
	
	/**
	 * create new file with filename name 
	 * @param filename name of file
	 */
	public void create(String filename) {
		this.filename = filename;
		data = new Chunk("");
		VirtualDisk.inodes.add(filename, size, SuperBlock.getFirstFreeBytes());
	}
	
	/**
	 * FileHandler creation with filename name and buffer content
	 * @param filename name of file
	 * @param buffer content 
	 */
	public FileHandler(String filename, byte buffer []) {
		this.filename = filename;
		size = buffer.length;
		data = new Chunk(buffer, size);
	}
	
	/**
	 * read virtualdisk at filename name to fileHandler
	 * @param filename name of file
	 * @return firstbyte of file 
	 */
	public int read(String filename) {
		Inode i = VirtualDisk.inodes.get(filename);
		this.filename = filename;
		size = i.getSize();
		data = new Chunk(size);
		return data.read(i.getFirstByte());
	}
	
	/**
	 * read virtualdisk to fileHandler
	 * @return firstbyte of file
	 */
	public int read() {
		return this.read(filename);
	}
	
	/**
	 * read virtualdisk at i position to fileHandler
	 * @param i reading position of file
	 * @return firstbyte of file
	 * */
	public int read(Inode i) {
		return this.read(i.getFilename());
	}
	
	/**
	 * write fileHandler to virtualdisk
	 * @return firstbyte of file
	 */
	public int write() {
		if(VirtualDisk.inodes.get(filename) != null) return 2;
		System.out.println(VirtualDisk.inodes.get(filename));
		int code = data.write(SuperBlock.getFirstFreeBytes());
		if(code != 0) return code;
		VirtualDisk.inodes.add(filename, size, SuperBlock.getFirstFreeBytes());
		System.out.println(this);
		return 0;
	}
	
	/**
	 * host fileHandler
	 * @return 0 if OK else 1 if hosting issue
	 */
	public int toHost() {
		System.out.println(content());
		try {
			RandomAccessFile file = new RandomAccessFile(filename, "rw");
			file.write(data.content().getBytes());
			file.setLength(data.content().length());
			file.close();
		} catch (IOException e) {
			System.err.println("Problï¿½me rencontrï¿½ lors de l'ï¿½criture");
			e.printStackTrace();
			return 1;
		}
		return 0;
	}
	
	/* (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	public String toString() {
		return "Nom du fichier : " + filename + "\nTaille : " + size + " octets, " + Utils.compute_nstripe(Utils.compute_nblock(size)) + " bandes\nPosition : " + VirtualDisk.inodes.get(filename).getFirstByte() + "\nContenu :\n" + data;
	}
	
	/**
	 * retrieve buffer of fileHandler's data
	 * @return fileHandler's content
	 */
	public String content() {
		return data.content();
	}
	
	/**
	 * retrieve data of fileHandler
	 * @return data retrieved
	 */
	public Chunk getData() {
		return data;
	}
	
	/**
	 * retrieve size of fileHandler
	 * @return size retrieved
	 */
	public int getSize() {
		return size;
	}
}
