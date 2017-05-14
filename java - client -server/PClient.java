import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Container;
import java.awt.FlowLayout;
import java.awt.LayoutManager;
import java.awt.event.ActionListener;
import java.net.InetAddress;
import javax.swing.Box;
import javax.swing.JApplet;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.border.Border;
import javax.swing.border.TitledBorder;

public class Pclient
extends JApplet {
    static int ServerPORT = 10203;
    static int TypeStatus = 0;
    static JTextField InputLine = new JTextField(30);
    static JTextArea OutputArea = new JTextArea(10, 50);
    static JTextField host = new JTextField("localhost", 20);
    static JTextField port = new JTextField("10203", 6);
    static JCheckBox status = new JCheckBox("");
    static JButton start = new JButton("START");
    static JButton end = new JButton("END");
    static String InputTxt = new String();
    static String RHOST = "localhost";
    static InetAddress RHOSTIP;
    static int MyPort;

    public static void AppendLine(String string) {
        OutputArea.setText(string + "\n" + OutputArea.getText());
    }

    @Override
    public void init() {
        start.setBackground(Color.green);
        end.setBackground(Color.green);
        status.setBackground(Color.green);
        InputLine.setEditable(false);
        InputLine.setBackground(Color.yellow);
        OutputArea.setEditable(false);
        OutputArea.setBackground(Color.cyan);
        Container container = this.getContentPane();
        container.setLayout(new FlowLayout());
        JPanel jPanel = new JPanel();
        TitledBorder titledBorder = new TitledBorder(" Remote tserver");
        jPanel.setBorder(titledBorder);
        jPanel.setLayout(new BorderLayout());
        Box box = Box.createHorizontalBox();
        box.add(Box.createHorizontalStrut(10));
        box.add(new JLabel("remote host", 0));
        box.add(Box.createHorizontalStrut(5));
        box.add(host);
        box.add(Box.createHorizontalStrut(10));
        box.add(new JLabel("port number", 0));
        box.add(Box.createHorizontalStrut(5));
        box.add(port);
        box.add(Box.createHorizontalStrut(10));
        box.add(new JLabel("check for SPEAKER", 0));
        box.add(Box.createHorizontalStrut(5));
        box.add(status);
        box.add(Box.createHorizontalStrut(10));
        host.setBackground(Color.green);
        port.setBackground(Color.green);
        jPanel.add("North", box);
        Box box2 = Box.createHorizontalBox();
        box2.add(Box.createHorizontalStrut(150));
        box2.add(start);
        box2.add(Box.createHorizontalStrut(5));
        box2.add(end);
        box2.add(Box.createHorizontalStrut(5));
        jPanel.add("Center", box2);
        container.add(jPanel);
         var6_6 = new /* Unavailable Anonymous Inner Class!! */;
        end.addActionListener((ActionListener)var6_6);
        status.addActionListener((ActionListener)new /* Unavailable Anonymous Inner Class!! */);
         var7_7 = new /* Unavailable Anonymous Inner Class!! */;
        start.addActionListener((ActionListener)var7_7);
        JPanel jPanel2 = new JPanel();
        TitledBorder titledBorder2 = new TitledBorder(" Input ");
        jPanel2.setBorder(titledBorder2);
        jPanel2.setLayout(new FlowLayout());
        jPanel2.add(InputLine);
        container.add(jPanel2);
        JPanel jPanel3 = new JPanel();
        TitledBorder titledBorder3 = new TitledBorder(" Received Messages ");
        jPanel3.setBorder(titledBorder3);
        jPanel3.setLayout(new FlowLayout());
        jPanel3.add(new JScrollPane(OutputArea, 22, 31));
        container.add(jPanel3);
         var12_12 = new /* Unavailable Anonymous Inner Class!! */;
        InputLine.addActionListener((ActionListener)var12_12);
    }

    public static void main(String[] arrstring) {
        Pclient pclient = new Pclient();
        Console.run(pclient, 700, 400);
    }
}