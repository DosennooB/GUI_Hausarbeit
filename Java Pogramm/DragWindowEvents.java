//Author: DosennooB

import javax.swing.*;
import javax.swing.event.MouseInputAdapter;
import java.awt.*;
import java.awt.event.MouseEvent;


//Setzte den Mittelpunkt des Quadrates permanet auf die Spitze des Corsers wenn dieser gedrückt wird.
//Die Funktion kann deaktiviert und aktiviert werden.
//Funktionsaufbau insperiert bei
//https://tips4java.wordpress.com/2009/06/14/moving-windows/
public class DragWindowEvents extends MouseInputAdapter {
    private boolean aktive = true;
    @Override
    public void mousePressed(MouseEvent e) {
        if(e.getButton()== MouseEvent.BUTTON3) {
            Point t = e.getComponent().getParent().getMousePosition(true);
            if (t != null && aktive) {
                e.getComponent().setLocation(t.x - 21, t.y - 21);
            }
        }
    }

    @Override
    public void mouseDragged(MouseEvent e) {
        if(SwingUtilities.isRightMouseButton(e)) {
            Point t = e.getComponent().getParent().getMousePosition(true);
            //t ist null wenn ein Drag auserhalb des Fensters statt findet
            if (t != null && aktive) {
                e.getComponent().setLocation(t.x - 21, t.y - 21);
            }
        }
    }


    public void toggleAktive(){
        aktive = !aktive;
    }
}
