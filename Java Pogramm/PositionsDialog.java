//Author: DosennooB

import javax.swing.*;
import java.text.NumberFormat;

//Der Dialog kann über MenueDialog aufgerufen werden gibt die eingegebene werte an Fenster.setlocation
public class PositionsDialog extends JDialog{

    PositionsDialog(JFrame f){
        super(f, true);
        setSize(160,160);
        JPanel base = new JPanel();

        base.setLayout(new BoxLayout(base, BoxLayout.Y_AXIS));

        JLabel textx = new JLabel("X Position");
        base.add(textx);

        //gibt gibt nur Werte zurück die Integer sind.
        JFormattedTextField posx = new JFormattedTextField(NumberFormat.getIntegerInstance());
        base.add(posx);

        JLabel texty = new JLabel("Y Position");
        base.add(texty);

        JFormattedTextField posy = new JFormattedTextField(NumberFormat.getIntegerInstance());
        base.add(posy);
        JButton ok = new JButton("Ok");
        base.add(ok);
        add(base);

        ok.addActionListener(e -> {
            Long lpx = (Long)posx.getValue();
            Long lpy = (Long)posy.getValue();

            Fenster.setLocation(lpx.intValue(),lpy.intValue());
            this.dispose();
        });
    }

}
