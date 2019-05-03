package objets;

public class SuperBlock {
	private int nb_blocks_used;
	private int first_free_bytes;
	
	public void update_first_free_bytes(int new_bytes) {
		this.first_free_bytes += new_bytes;
	}
}
