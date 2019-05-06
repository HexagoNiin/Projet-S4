package objets;

import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JButton;
import java.awt.BorderLayout;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.FlowLayout;
import javax.swing.SpringLayout;
import javax.swing.JTextField;
import java.awt.Component;
import javax.swing.Box;
import javax.swing.DefaultListModel;
import javax.swing.JSlider;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JEditorPane;
import javax.swing.JTextPane;
import javax.swing.ListModel;

import java.awt.Font;
import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.JPanel;
import java.awt.Color;
import javax.swing.JList;
import javax.swing.JRadioButton;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import javax.swing.JScrollBar;
import javax.swing.JTree;

public class Gui {

	private JFrame frmRaid;
	private JTextArea textArea;
	private JList list;
	private DefaultListModel model = new DefaultListModel();
	private JTextField sizeField;
	private JTextField informationField;
	private final JButton EditButton = new JButton("");
	private JButton HostButton, RemoveButton, ImportButton, LeaveButton, CreateButton;
	private Color buttonColor = new Color(104, 124, 196);
	private final Action EditFile = new SwingAction();
	private final Action EditDone = new SwingAction_1();
	private final Action Export = new SwingAction_2();
	private final Action Remove = new SwingAction_3();
	private final Action Import = new SwingAction_4();
	private final Action Leave = new SwingAction_5();
	private JScrollPane scrollPane;
	private JScrollPane scrollPane_1;
	private final Action Create = new SwingAction_6();
	
	/**
	 * Launch the application.
	 */
	public static void launch(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Gui window = new Gui();
					window.frmRaid.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public Gui() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frmRaid = new JFrame();
		frmRaid.setTitle("RAID 5");
		frmRaid.setResizable(false);
		frmRaid.setBounds(100, 100, 942, 577);
		frmRaid.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		SpringLayout springLayout = new SpringLayout();
		frmRaid.getContentPane().setLayout(springLayout);
		
		JPanel panel = new JPanel();
		springLayout.putConstraint(SpringLayout.SOUTH, panel, 0, SpringLayout.SOUTH, frmRaid.getContentPane());
		panel.setBackground(new Color(34, 34, 40));
		springLayout.putConstraint(SpringLayout.NORTH, panel, 0, SpringLayout.NORTH, frmRaid.getContentPane());
		springLayout.putConstraint(SpringLayout.WEST, panel, 0, SpringLayout.WEST, frmRaid.getContentPane());
		springLayout.putConstraint(SpringLayout.EAST, panel, 936, SpringLayout.WEST, frmRaid.getContentPane());
		frmRaid.getContentPane().add(panel);
		panel.setLayout(null);
		
		scrollPane_1 = new JScrollPane();
		scrollPane_1.setBounds(394, 10, 532, 524);
		panel.add(scrollPane_1);
		
		textArea = new JTextArea();
		textArea.setFont(new Font("Tahoma", Font.PLAIN, 15));
		textArea.setForeground(new Color(255, 255, 255));
		textArea.setBackground(new Color(53, 53, 64));
		textArea.setWrapStyleWord(true);
		scrollPane_1.setViewportView(textArea);
		textArea.setLineWrap(true);
		textArea.setEditable(false);
		
		sizeField = new JTextField();
		sizeField.setForeground(Color.WHITE);
		sizeField.setBackground(new Color(19, 19, 26));
		sizeField.setBounds(10, 370, 116, 22);
		sizeField.setEditable(false);
		panel.add(sizeField);
		sizeField.setColumns(10);
		
		informationField = new JTextField();
		informationField.setForeground(Color.WHITE);
		informationField.setBackground(new Color(19, 19, 26));
		informationField.setBounds(138, 370, 244, 22);
		informationField.setEditable(false);
		panel.add(informationField);
		informationField.setColumns(10);
		EditButton.setForeground(Color.WHITE);
		EditButton.setFont(new Font("Tahoma", Font.BOLD, 13));
		
		EditButton.setBounds(10, 412, 116, 50);
		EditButton.setBackground(buttonColor);
		EditButton.setAction(EditFile);
		EditButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
			}
		});
		panel.add(EditButton);
		
		HostButton = new JButton("New button");
		HostButton.setFont(new Font("Tahoma", Font.BOLD, 13));
		HostButton.setForeground(Color.WHITE);
		HostButton.setBackground(buttonColor);
		HostButton.setBounds(139, 412, 116, 50);
		HostButton.setAction(Export);
		panel.add(HostButton);
		
		RemoveButton = new JButton("New button");
		RemoveButton.setFont(new Font("Tahoma", Font.BOLD, 13));
		RemoveButton.setForeground(Color.WHITE);
		RemoveButton.setBackground(buttonColor);
		RemoveButton.setBounds(268, 412, 116, 50);
		RemoveButton.setAction(Remove);
		panel.add(RemoveButton);
		
		ImportButton = new JButton("New button");
		ImportButton.setFont(new Font("Tahoma", Font.BOLD, 13));
		ImportButton.setForeground(Color.WHITE);
		ImportButton.setBackground(buttonColor);
		ImportButton.setBounds(139, 472, 116, 50);
		ImportButton.setAction(Import);
		panel.add(ImportButton);
		
		LeaveButton = new JButton("New button");
		LeaveButton.setFont(new Font("Tahoma", Font.BOLD, 13));
		LeaveButton.setForeground(Color.WHITE);
		LeaveButton.setBackground(buttonColor);
		LeaveButton.setBounds(268, 472, 116, 50);
		LeaveButton.setAction(Leave);
		panel.add(LeaveButton);
		
		scrollPane = new JScrollPane();
		scrollPane.setBounds(10, 10, 372, 350);
		panel.add(scrollPane);
		
		list = new JList();
		list.setFont(new Font("Tahoma", Font.PLAIN, 14));
		list.setForeground(new Color(255, 255, 255));
		list.setBackground(new Color(53, 53, 64));
		scrollPane.setViewportView(list);
		list.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				displayContent();
			}
		});
		list.setModel(model);
		
		CreateButton = new JButton("New button");
		CreateButton.setFont(new Font("Tahoma", Font.BOLD, 13));
		CreateButton.setForeground(Color.WHITE);
		CreateButton.setBackground(buttonColor);
		CreateButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
			}
		});
		CreateButton.setAction(Create);
		CreateButton.setBounds(10, 474, 116, 47);
		panel.add(CreateButton);
	}
	
	private void displayContent() {
		int index = list.getSelectedIndex();
		if (index != -1) {
			String selected = list.getSelectedValue().toString();
			
			FileHandler f = new FileHandler();
			f.read(VirtualDisk.inodes.get(selected));
			
			String text = f.content();
			System.out.println(f);
			
			textArea.setText(text);
			int i = f.getSize();
			sizeField.setText(i + " byte" + (i>1?"s":""));
		} else {
			textArea.setText("");
			sizeField.setText("");
		}
	}
	
	private void createElement() {
		String name;
		if ( (name = JOptionPane.showInputDialog("Name File :")) != null) {
			FileHandler f = new FileHandler();
			f.create(name);
			
			model.addElement(name);
			information("File created");
		} else {
			information("");
		}
	}
	
	private void addElement() {
		String name;
		if ( (name = JOptionPane.showInputDialog("Name File :")) != null) {
			if(VirtualDisk.inodes.get(name) == null) {
				FileHandler f = new FileHandler(name);
				System.out.println("JE SUIS LA");
				if (f.write() == 0) {
					model.addElement(name);
				}
			} else {
				information("File already exists");
			}
		} else {
			information("");
		}
	}
	
	private void deleteElement() {
		int index = list.getSelectedIndex();
		if (index != -1) {
			VirtualDisk.inodes.delete(index);
			model.remove(index);
			information("File removed");
		} else {
			information("");
		}
		displayContent();
	}
	
	private void hostElement() {
		int index = list.getSelectedIndex();
		if (index != -1) {
			FileHandler f = new FileHandler();
			f.read(VirtualDisk.inodes.get(index));
			f.toHost();
			information("File hosted");
		} else {
			information("");
		}
	}
	
	
	private void leave() {
		if (JOptionPane.showConfirmDialog(null, "leave?","leave?",JOptionPane.YES_NO_OPTION) == 0)
			System.exit(0);
		else 
			information("");
	}
	
	private void information(String s) {
		informationField.setText(s);
	}
	
	private class SwingAction extends AbstractAction {
		public SwingAction() {
			putValue(NAME, "EDIT");
			putValue(SHORT_DESCRIPTION, "Edit the selected file");
		}
		public void actionPerformed(ActionEvent e) {
			information("Editing file");
			list.setEnabled(false);
			textArea.setEditable(true);
			EditButton.setAction(EditDone);
			HostButton.setEnabled(false);
			RemoveButton.setEnabled(false);
			ImportButton.setEnabled(false);
			LeaveButton.setEnabled(false);
			CreateButton.setEnabled(false);
			
		}
	}	
	
	private class SwingAction_1 extends AbstractAction {
		public SwingAction_1() {
			putValue(NAME, "DONE");
			putValue(SHORT_DESCRIPTION, "Finalise the edition");
		}
		public void actionPerformed(ActionEvent e) {
			information("Confirm");
			int index;
			switch(JOptionPane.showConfirmDialog(null, "save?")) {
				case 0:
					information("Saving file");
					index = list.getSelectedIndex();
					if (index != -1) {
						String text = textArea.getText();
						String filename = VirtualDisk.inodes.get(index).getFilename();
						VirtualDisk.inodes.delete(filename);
						new FileHandler(filename, text.getBytes()).write();
						System.out.println("\nTable d'inodes : \n" + VirtualDisk.inodes + "\n");
						information("File saved");
					} else {
						information("");
					}
					break;
				
				case 1:
					index = list.getSelectedIndex();
					if (index != -1)
						information("File unsaved");
					else 
						information("");
					break;
					
				case 2:
					information("Editing file");
					return;
			}
			displayContent();
			textArea.setEditable(false);
			list.setEnabled(true);
			EditButton.setAction(EditFile);
			HostButton.setEnabled(true);
			RemoveButton.setEnabled(true);
			ImportButton.setEnabled(true);
			LeaveButton.setEnabled(true);
			CreateButton.setEnabled(true);
		}
	}
	
	private class SwingAction_2 extends AbstractAction {
		public SwingAction_2() {
			putValue(NAME, "EXPORT");
			putValue(SHORT_DESCRIPTION, "Store from RAID to PC");
		}
		public void actionPerformed(ActionEvent e) {
			information("Hosting file");
			hostElement();
			
		}
	}
	
	private class SwingAction_3 extends AbstractAction {
		public SwingAction_3() {
			putValue(NAME, "REMOVE");
			putValue(SHORT_DESCRIPTION, "Delete the file");
		}
		public void actionPerformed(ActionEvent e) {
			information("Removing file");
			deleteElement();
			
		}
	}
	
	
	private class SwingAction_4 extends AbstractAction {
		public SwingAction_4() {
			putValue(NAME, "IMPORT");
			putValue(SHORT_DESCRIPTION, "Import a new file");
		}
		public void actionPerformed(ActionEvent e) {
			information("Importing file");
			addElement();
		}
	}
	
	private class SwingAction_5 extends AbstractAction {
		public SwingAction_5() {
			putValue(NAME, "LEAVE");
			putValue(SHORT_DESCRIPTION, "Leave RAID");
		}
		public void actionPerformed(ActionEvent e) {
			information("Leaving");
			leave();
		}
	}
	private class SwingAction_6 extends AbstractAction {
		public SwingAction_6() {
			putValue(NAME, "CREATE");
			putValue(SHORT_DESCRIPTION, "Create a new file");
		}
		public void actionPerformed(ActionEvent e) {
			information("Creating new file");
			createElement();
		}
	}
}