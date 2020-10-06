//Author: DosennooB

import javax.swing.*;
import java.awt.*;
//Zeichtnet das Rechteck mit einem Kreuz in der Mitte.
//Zur besseren abgrenzung ist dies in blau gehalten.
public class Rechteck extends JComponent {
    @Override
    protected void paintComponent(Graphics recht){
        super.paintComponents(recht);
        recht.setColor(Color.BLUE);
        recht.fillRect(0,0,41,41);
        recht.setColor(Color.BLACK);
        recht.drawRect(0,0,41,41);
        recht.drawLine(17,20, 23,20);
        recht.drawLine(20,17,20,23);
    }
}
