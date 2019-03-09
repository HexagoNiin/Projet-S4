package objets;

public class Utils {
	public int compute_nblock(int nb_octets) {
		int nb_blocks = nb_octets / 4;
		if(nb_octets % 4 != 0) {
			nb_blocks++;
		}
		return nb_blocks;
	}
}
