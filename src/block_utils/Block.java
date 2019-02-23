package block_utils;

import java.io.*;

public class Block {
	
	private byte [] data = new byte[4];
	private final static int BLOCK_SIZE = 4;
	
	public Block(byte [] data) {
		this.data = data;
	}
	
	public int write_block(int pos, File disk_id)  {
		return 0;
	}
	
	public int block_repair(int pos, File [] disks, int disk_id) {
		return 0;
	}

}
