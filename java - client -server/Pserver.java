import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Container;
import java.awt.FlowLayout;
import java.awt.LayoutManager;
import java.awt.event.ActionListener;
import java.net.Socket;
import javax.swing.Box;
import javax.swing.JApplet;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.border.Border;
import javax.swing.border.TitledBorder;

public class Pserver
extends JApplet {
    static boolean[] IsFree;
    static boolean[] CltType;
    static String[] CltInfo;
    static Socket[] SockInfo;
    static boolean IsOpen;
    static JTextArea Output1;
    static JTextArea Output2;
    static JTextArea Output3;
    static JTextField port;
    static int MaxNumThreads;
    static int ServerPort;
    static Container cp;
    static JButton start;
    static JButton end;
    static JButton list;
    static JButton allow;
    static String ALIVEmsg;
    static String ALLOWmsg;
    static String ENDmsg;
    static String ACCEPTED;
    static String REJECTED;

    public static void Out1Append(String string) {
        Output1.setText(string + "\n" + Output1.getText());
    }

    public static void Out2Append(String string) {
        Output2.setText(string + "\n" + Output2.getText());
    }

    public static void Out3Append(String string) {
        Output3.setText(Output3.getText() + "\n" + string);
    }

    @Override
    public void init() {
        end.setBackground(Color.green);
        start.setBackground(Color.green);
        allow.setBackground(Color.red);
        allow.setEnabled(false);
        list.setBackground(Color.red);
        list.setEnabled(false);
        port.setBackground(Color.green);
        Output1.setEditable(false);
        Output1.setBackground(Color.orange);
        Output2.setEditable(false);
        Output2.setBackground(Color.cyan);
        Output3.setEditable(false);
        Output3.setBackground(Color.yellow);
        Box box = Box.createHorizontalBox();
        box.add(Box.createHorizontalStrut(5));
        box.add(new JLabel("Port", 0));
        box.add(Box.createHorizontalStrut(5));
        box.add(port);
        box.add(Box.createHorizontalStrut(5));
        box.add(start);
        box.add(Box.createHorizontalStrut(5));
        box.add(end);
        box.add(Box.createHorizontalStrut(5));
        box.add(allow);
        box.add(Box.createHorizontalStrut(5));
        Box box2 = Box.createHorizontalBox();
        box2.add(Box.createHorizontalStrut(150));
        box2.add(list);
        cp = this.getContentPane();
        cp.setLayout(new FlowLayout());
        cp.add(box);
         var3_3 = new /* Unavailable Anonymous Inner Class!! */;
        end.addActionListener((ActionListener)var3_3);
         var4_4 = new /* Unavailable Anonymous Inner Class!! */;
        allow.addActionListener((ActionListener)var4_4);
         var5_5 = new /* Unavailable Anonymous Inner Class!! */;
        start.addActionListener((ActionListener)var5_5);
         var6_6 = new /* Unavailable Anonymous Inner Class!! */;
        list.addActionListener((ActionListener)var6_6);
        IsFree = new boolean[MaxNumThreads];
        CltType = new boolean[MaxNumThreads];
        CltInfo = new String[MaxNumThreads];
        SockInfo = new Socket[MaxNumThreads];
        JPanel jPanel = new JPanel();
        TitledBorder titledBorder = new TitledBorder("SPEAKERS Threads Messages ");
        jPanel.setBorder(titledBorder);
        jPanel.setLayout(new BorderLayout());
        jPanel.add("North", new JScrollPane(Output1, 22, 31));
        cp.add(jPanel);
        JPanel jPanel2 = new JPanel();
        TitledBorder titledBorder2 = new TitledBorder("AUDIENCE Threads Messages ");
        jPanel2.setBorder(titledBorder2);
        jPanel2.setLayout(new BorderLayout());
        jPanel2.add("North", new JScrollPane(Output2, 22, 31));
        cp.add(jPanel2);
        JPanel jPanel3 = new JPanel();
        TitledBorder titledBorder3 = new TitledBorder("LIST Messages ");
        jPanel3.setBorder(titledBorder3);
        jPanel3.setLayout(new BorderLayout());
        jPanel3.add(box2);
        jPanel3.add("North", new JScrollPane(Output3, 22, 31));
        cp.add(jPanel3);
        for (int i = 0; i < MaxNumThreads; ++i) {
            Pserver.IsFree[i] = true;
            Pserver.CltType[i] = true;
            Pserver.CltInfo[i] = "";
        }
    }

    public static void main(String[] arrstring) {
        Pserver pserver = new Pserver();
        Console.run(pserver, 600, 700);
    }

    static {
        IsOpen = false;
        Output1 = new JTextArea(10, 50);
        Output2 = new JTextArea(10, 50);
        Output3 = new JTextArea(10, 50);
        port = new JTextField("10203", 5);
        MaxNumThreads = 15;
        ServerPort = 10203;
        start = new JButton("Start");
        end = new JButton("End");
        list = new JButton("List");
        allow = new JButton("Allow Questions");
        ALIVEmsg = "!ALIVE!";
        ALLOWmsg = "!FLOOR!";
        ENDmsg = "!BYBY!";
        ACCEPTED = "!ACCEPTED!";
        REJECTED = "!REJECTED!";
    }
}