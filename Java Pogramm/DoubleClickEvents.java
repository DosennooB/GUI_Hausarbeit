//Author: DosennooB



import javax.swing.*;
import javax.swing.event.MouseInputAdapter;
import java.awt.event.MouseEvent;


//Verwaltet die Mousevents die dem Basisfenster zugeordnet werden können.
public class DoubleClickEvents extends MouseInputAdapter {
    JComponent recht;
    DragWindowEvents dw;
    DoubleClickEvents(JComponent recht, DragWindowEvents dw){
        this.recht = recht;
        this.dw = dw;
    }

    @Override
    public void mouseClicked(MouseEvent e) {
        //zurücksetzen des Rechtecks
        if(e.getButton() == MouseEvent.BUTTON1){
            if(e.getClickCount()== 2){
                recht.setLocation(160-21,160-21);
            }
        }
        //Aktivieren und Deaktivieren der Drag Funktion
        if(e.getButton()== MouseEvent.BUTTON3){
            if(e.getClickCount() ==2){
                dw.toggleAktive();
            }
        }
    }
}
