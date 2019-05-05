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
	
	public int load() {
		return data.read(VirtualDisk.inodes.get(filename).getFirstByte());
	}
	
	public int write() {
		return data.write(SuperBlock.getFirstFreeBytes());
	}
}
