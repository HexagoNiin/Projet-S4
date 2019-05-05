package objets;

import java.io.*;

public class FileHandler {
	private String filename;
	private int size;
	private Chunk data;
	
	public FileHandler(String filename) {
		this.filename = filename;
		try {
			FileInputStream file = new FileInputStream(new File(filename));
			size = file.available();
			byte buffer[] = new byte[size];
			file.read(buffer);
			data = new Chunk(buffer, size);
			file.close();
		} catch(IOException e) {
			System.err.println("Le fichier n'a pas �t� correctement ouvert en lecture");
			e.printStackTrace();
			return;
		}
	}
	
	public FileHandler() {
		filename = null;
		size = 0;
		data = null;
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
	
	public int write() {
		int code = data.write(SuperBlock.getFirstFreeBytes());
		if(code != 0) return code;
		VirtualDisk.inodes.add(filename, size, SuperBlock.getFirstFreeBytes());
		return 0;
	}
	}
}
