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

public class Gui {

	private JFrame frmRaid;
	private JTextArea textArea;
	private JList list;
	private DefaultListModel model = new DefaultListModel();
	private JTextField sizeField;
	private JTextField textField_1;
	private JTextField textField_2;
	private final JButton EditButton = new JButton("");
	private JButton HostButton, RemoveButton, NewButton, LeaveButton;
	private final Action EditFile = new SwingAction();
	private final Action EditDone = new SwingAction_1();
	private final Action action = new SwingAction_2();
	private final Action action_1 = new SwingAction_3();
	private final Action action_2 = new SwingAction_4();
	private final Action action_3 = new SwingAction_5();
	
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
		frmRaid.setBounds(100, 100, 942, 589);
		frmRaid.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		SpringLayout springLayout = new SpringLayout();
		frmRaid.getContentPane().setLayout(springLayout);
		
		JPanel panel = new JPanel();
		springLayout.putConstraint(SpringLayout.NORTH, panel, 0, SpringLayout.NORTH, frmRaid.getContentPane());
		springLayout.putConstraint(SpringLayout.WEST, panel, 0, SpringLayout.WEST, frmRaid.getContentPane());
		springLayout.putConstraint(SpringLayout.SOUTH, panel, 554, SpringLayout.NORTH, frmRaid.getContentPane());
		springLayout.putConstraint(SpringLayout.EAST, panel, 936, SpringLayout.WEST, frmRaid.getContentPane());
		frmRaid.getContentPane().add(panel);
		SpringLayout sl_panel = new SpringLayout();
		panel.setLayout(sl_panel);
		
		textArea = new JTextArea();
		textArea.setLineWrap(true);
		textArea.setEditable(false);
		sl_panel.putConstraint(SpringLayout.NORTH, textArea, 10, SpringLayout.NORTH, panel);
		sl_panel.putConstraint(SpringLayout.WEST, textArea, -542, SpringLayout.EAST, panel);
		sl_panel.putConstraint(SpringLayout.SOUTH, textArea, 544, SpringLayout.NORTH, panel);
		sl_panel.putConstraint(SpringLayout.EAST, textArea, -10, SpringLayout.EAST, panel);
		panel.add(textArea);
		
		list = new JList();
		list.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				displayContent();
			}
		});
		sl_panel.putConstraint(SpringLayout.WEST, EditButton, 0, SpringLayout.WEST, list);
		sl_panel.putConstraint(SpringLayout.NORTH, list, 10, SpringLayout.NORTH, panel);
		sl_panel.putConstraint(SpringLayout.WEST, list, 10, SpringLayout.WEST, panel);
		sl_panel.putConstraint(SpringLayout.SOUTH, list, -194, SpringLayout.SOUTH, panel);
		sl_panel.putConstraint(SpringLayout.EAST, list, -10, SpringLayout.WEST, textArea);
		panel.add(list);
		list.setModel(model);
		
		sizeField = new JTextField();
		sizeField.setEditable(false);
		sl_panel.putConstraint(SpringLayout.NORTH, EditButton, 20, SpringLayout.SOUTH, sizeField);
		sl_panel.putConstraint(SpringLayout.SOUTH, EditButton, 70, SpringLayout.SOUTH, sizeField);
		sl_panel.putConstraint(SpringLayout.EAST, EditButton, 0, SpringLayout.EAST, sizeField);
		sl_panel.putConstraint(SpringLayout.NORTH, sizeField, 10, SpringLayout.SOUTH, list);
		sl_panel.putConstraint(SpringLayout.WEST, sizeField, 10, SpringLayout.WEST, panel);
		panel.add(sizeField);
		sizeField.setColumns(10);
		
		textField_1 = new JTextField();
		textField_1.setEditable(false);
		sl_panel.putConstraint(SpringLayout.NORTH, textField_1, 10, SpringLayout.SOUTH, list);
		sl_panel.putConstraint(SpringLayout.EAST, textField_1, -10, SpringLayout.WEST, textArea);
		panel.add(textField_1);
		textField_1.setColumns(10);
		
		textField_2 = new JTextField();
		textField_2.setEditable(false);
		sl_panel.putConstraint(SpringLayout.NORTH, textField_2, 10, SpringLayout.SOUTH, list);
		sl_panel.putConstraint(SpringLayout.WEST, textField_2, 13, SpringLayout.EAST, sizeField);
		sl_panel.putConstraint(SpringLayout.EAST, textField_2, -13, SpringLayout.WEST, textField_1);
		panel.add(textField_2);
		textField_2.setColumns(10);
		EditButton.setAction(EditFile);
		EditButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
			}
		});
		panel.add(EditButton);
		
		HostButton = new JButton("New button");
		HostButton.setAction(action);
		sl_panel.putConstraint(SpringLayout.NORTH, HostButton, 20, SpringLayout.SOUTH, textField_2);
		sl_panel.putConstraint(SpringLayout.WEST, HostButton, 0, SpringLayout.WEST, textField_2);
		sl_panel.putConstraint(SpringLayout.SOUTH, HostButton, 0, SpringLayout.SOUTH, EditButton);
		sl_panel.putConstraint(SpringLayout.EAST, HostButton, 0, SpringLayout.EAST, textField_2);
		panel.add(HostButton);
		
		RemoveButton = new JButton("New button");
		RemoveButton.setAction(action_1);
		sl_panel.putConstraint(SpringLayout.NORTH, RemoveButton, 20, SpringLayout.SOUTH, textField_1);
		sl_panel.putConstraint(SpringLayout.WEST, RemoveButton, 0, SpringLayout.WEST, textField_1);
		sl_panel.putConstraint(SpringLayout.SOUTH, RemoveButton, 0, SpringLayout.SOUTH, EditButton);
		sl_panel.putConstraint(SpringLayout.EAST, RemoveButton, -10, SpringLayout.WEST, textArea);
		panel.add(RemoveButton);
		
		NewButton = new JButton("New button");
		NewButton.setAction(action_2);
		sl_panel.putConstraint(SpringLayout.NORTH, NewButton, 10, SpringLayout.SOUTH, EditButton);
		sl_panel.putConstraint(SpringLayout.WEST, NewButton, 0, SpringLayout.WEST, list);
		sl_panel.putConstraint(SpringLayout.SOUTH, NewButton, 60, SpringLayout.SOUTH, EditButton);
		sl_panel.putConstraint(SpringLayout.EAST, NewButton, 0, SpringLayout.EAST, sizeField);
		panel.add(NewButton);
		
		LeaveButton = new JButton("New button");
		LeaveButton.setAction(action_3);
		sl_panel.putConstraint(SpringLayout.NORTH, LeaveButton, 10, SpringLayout.SOUTH, RemoveButton);
		sl_panel.putConstraint(SpringLayout.WEST, LeaveButton, 0, SpringLayout.WEST, textField_1);
		sl_panel.putConstraint(SpringLayout.SOUTH, LeaveButton, 0, SpringLayout.SOUTH, NewButton);
		sl_panel.putConstraint(SpringLayout.EAST, LeaveButton, -10, SpringLayout.WEST, textArea);
		panel.add(LeaveButton);
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
		}
	}
	
	
	private void addElement() {
		String name;
		if ( (name = JOptionPane.showInputDialog("Name File :")) != null) {
			if(VirtualDisk.inodes.get(name) == null) {
				FileHandler f = new FileHandler(name);
				if (f.write() == 0) {
					model.addElement(name);
				}
			}
		}
	}
	
	private void deleteElement() {
		int index = list.getSelectedIndex();
		if (index != -1) {
			VirtualDisk.inodes.delete(index);
			model.remove(index);
		}
	}
	
	private void hostElement() {
		int index = list.getSelectedIndex();
		if (index != -1) {
			FileHandler f = new FileHandler();
			f.read(VirtualDisk.inodes.get(index));
			f.toHost();
		}
	}
	
	
	private void leave() {
		if (JOptionPane.showConfirmDialog(null, "leave?") == 0)
			System.exit(0);
	}
	
	
	
	private class SwingAction extends AbstractAction {
		public SwingAction() {
			putValue(NAME, "EDIT");
			putValue(SHORT_DESCRIPTION, "Edit the selected file");
		}
		public void actionPerformed(ActionEvent e) {
			list.setEnabled(false);
			textArea.setEditable(true);
			EditButton.setAction(EditDone);
			HostButton.setEnabled(false);
			RemoveButton.setEnabled(false);
			NewButton.setEnabled(false);
			LeaveButton.setEnabled(false);
			
		}
	}	
	
	private class SwingAction_1 extends AbstractAction {
		public SwingAction_1() {
			putValue(NAME, "DONE");
			putValue(SHORT_DESCRIPTION, "Finalise the edition");
		}
		public void actionPerformed(ActionEvent e) {
			switch(JOptionPane.showConfirmDialog(null, "save?")) {
				case 0:
					int index = list.getSelectedIndex();
					if (index != -1) {
						String text = textArea.getText();
						String filename = VirtualDisk.inodes.get(index).getFilename();
						VirtualDisk.inodes.delete(filename);
						new FileHandler(filename, text.getBytes()).write();
						System.out.println("\nTable d'inodes : \n" + VirtualDisk.inodes + "\n");
					}
						
					break;
				
				case 1:
					
					break;
					
				case 2:
					return;
			}
			
			displayContent();
			textArea.setEditable(false);
			list.setEnabled(true);
			EditButton.setAction(EditFile);
			HostButton.setEnabled(true);
			RemoveButton.setEnabled(true);
			NewButton.setEnabled(true);
			LeaveButton.setEnabled(true);
		}
	}
	
	private class SwingAction_2 extends AbstractAction {
		public SwingAction_2() {
			putValue(NAME, "EXPORT");
			putValue(SHORT_DESCRIPTION, "Store from RAID to PC");
		}
		public void actionPerformed(ActionEvent e) {
			hostElement();
		}
	}
	
	private class SwingAction_3 extends AbstractAction {
		public SwingAction_3() {
			putValue(NAME, "REMOVE");
			putValue(SHORT_DESCRIPTION, "Delete the file");
		}
		public void actionPerformed(ActionEvent e) {
			deleteElement();
		}
	}
	private class SwingAction_4 extends AbstractAction {
		public SwingAction_4() {
			putValue(NAME, "NEW");
			putValue(SHORT_DESCRIPTION, "Add a new file");
		}
		public void actionPerformed(ActionEvent e) {
			addElement();
		}
	}
	private class SwingAction_5 extends AbstractAction {
		public SwingAction_5() {
			putValue(NAME, "LEAVE");
			putValue(SHORT_DESCRIPTION, "Leave RAID");
		}
		public void actionPerformed(ActionEvent e) {
			leave();
		}
	}
	
	
	
}