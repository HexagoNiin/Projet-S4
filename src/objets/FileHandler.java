package objets;

import java.io.*;

public class FileHandler {
	private String filename;
	private int size;
	private Chunk data;
	
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
	
	public FileHandler() {
		filename = null;
		size = 0;
		data = null;
	}
	
	public void create(String filename) {
		this.filename = filename;
		data = new Chunk("");
	}
	
	public FileHandler(String filename, byte buffer []) {
		this.filename = filename;
		size = buffer.length;
		data = new Chunk(buffer, size);
	}
	
	public int read(String filename) {
		Inode i = VirtualDisk.inodes.get(filename);
		this.filename = filename;
		size = i.getSize();
		data = new Chunk(size);
		return data.read(i.getFirstByte());
	}
	
	public int read() {
		return this.read(filename);
	}
	
	public int read(Inode i) {
		return this.read(i.getFilename());
	}
	
	public int write() {
		if(VirtualDisk.inodes.get(filename) != null) return 2;
		System.out.println(VirtualDisk.inodes.get(filename));
		int code = data.write(SuperBlock.getFirstFreeBytes());
		if(code != 0) return code;
		VirtualDisk.inodes.add(filename, size, SuperBlock.getFirstFreeBytes());
		System.out.println(this);
		return 0;
	}
	
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
	
	public String toString() {
		return "Nom du fichier : " + filename + "\nTaille : " + size + " octets, " + Utils.compute_nstripe(Utils.compute_nblock(size)) + " bandes\nPosition : " + VirtualDisk.inodes.get(filename).getFirstByte() + "\nContenu :\n" + data;
	}
	
	public String content() {
		return data.content();
	}
	
	public Chunk getData() {
		return data;
	}
	
	public int getSize() {
		return size;
	}
}
