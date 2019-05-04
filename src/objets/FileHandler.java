package objets;

import java.io.*;

public class FileHandler {
	private String filename;
	private int size;
	private Chunk data;
	
	public FileHandler(String filename) {
		try {
			this.filename = filename;
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
		size = 0;
		data = null;
	}
	
	public int store() {
		data.write(startbyte);
		return 0;
	}
}
