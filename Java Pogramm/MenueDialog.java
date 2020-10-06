//Author: DosennooB

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

//Klasse baut die Menüleiste auf.
public class MenueDialog {
    JMenu versetzen = new JMenu("Versetzen");
    JMenuItem nPos = new JMenuItem("zur Position");
    JMenuBar mb = new JMenuBar();
    JFrame main = null;

    public void addMenue(JFrame f){
        versetzen.add(nPos);
        mb.add(versetzen);
        f.setJMenuBar(mb);
        main = f;
        //Ruft das Dialogfenster PositionsDialog auf
        nPos.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                PositionsDialog pd = new PositionsDialog(f);
                pd.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
                pd.setVisible(true);
            }
        });


    }


}
