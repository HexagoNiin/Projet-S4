package test;

import objets.Gui;
import objets.VirtualDisk;

public class main {
	public static void main(String[] args) {
		new VirtualDisk("systeme");
		Gui.launch(null);
	}
}
