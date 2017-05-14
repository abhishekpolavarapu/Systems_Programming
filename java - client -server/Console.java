import java.awt.Component;
import java.awt.Container;
import javax.swing.JApplet;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class Console {
    public static String title(Object object) {
        String string = object.getClass().toString();
        if (string.indexOf("class") != -1) {
            string = string.substring(6);
        }
        return string;
    }

    public static void run(JFrame jFrame, int n, int n2) {
        jFrame.setDefaultCloseOperation(3);
        jFrame.setSize(n, n2);
        jFrame.setVisible(true);
    }

    public static void run(JApplet jApplet, int n, int n2) {
        JFrame jFrame = new JFrame(Console.title(jApplet));
        jFrame.setDefaultCloseOperation(3);
        jFrame.getContentPane().add(jApplet);
        jFrame.setSize(n, n2);
        jApplet.init();
        jApplet.start();
        jFrame.setVisible(true);
    }

    public static void run(JPanel jPanel, int n, int n2) {
        JFrame jFrame = new JFrame(Console.title(jPanel));
        jFrame.setDefaultCloseOperation(3);
        jFrame.getContentPane().add(jPanel);
        jFrame.setSize(n, n2);
        jFrame.setVisible(true);
    }
}