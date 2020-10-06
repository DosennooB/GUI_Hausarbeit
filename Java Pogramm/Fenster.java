//Author: DosennooB

import javax.swing.*;

//Hauptprogramm Initialisiert das Fenster und Funktionen
public class Fenster{
    static JComponent recht;
    public static void main(String[] args) {
        JFrame basis = new JFrame("Fenster");
        basis.setLayout(null);
        basis.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        basis.setSize(400,400);

        //Menu hinzu gefügt
        new MenueDialog().addMenue(basis);

        //Rechteck den Hauptfenster hinzu fügen
        recht = new Rechteck();
        recht.setBounds(160-21,160-21,41,41);
        basis.add(recht);

        //DragFunktion Initialisiert
        DragWindowEvents dragEvn = new DragWindowEvents();
        recht.addMouseListener(dragEvn);
        recht.addMouseMotionListener(dragEvn);

        //DoppelClickFunktion Initialisiert
        DoubleClickEvents dbclick = new DoubleClickEvents(recht, dragEvn);
        basis.addMouseListener(dbclick);
        
        basis.setVisible(true);
    }
    //Setzte rechteck an neue Position
    public static void setLocation(int x, int y){
        recht.setLocation(x-21, y-21);
    }

}
