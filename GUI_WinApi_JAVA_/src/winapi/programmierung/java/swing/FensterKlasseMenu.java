/*****************************************************************
 * Autor: Leonel Nguimatsia                                      *
 * @version: IntelliJ2021 JDK16                                  *
 * Hochschule: TH-Kloen                                          *
 * Ort: Deutz Technische Hochschule                              *
 * Webmail: leonel.nguimatsia_tsobguim@smail.th-koeln.de         *
 * Beschreibung: EntitaetKlasse FensterKlasseMenu                *
 *                                                               *
 *****************************************************************/

package winapi.programmierung.java.swing;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.File;



public class FensterKlasseMenu extends JFrame {

    //Deklaration der MenuBar und Einzelmenus

    private JMenuBar mbar = new JMenuBar();
    private JMenu menu1;
    private JMenuItem menuSimpelItem1A, mausZeigerSimpelItem;

    private  SimpelMenuListener simpelLis;  // Deklaration der Listener. Nur fuer der Menu gueltig

    private   MeinFensterListener fensterLis; // Deklaration der Listener. Nur fuer Das Windows beim Schliessen gueltig

    private  JFileChooser fileChooser; //Deklaration von FileChooser,für die Erstellung des Dialogfensters


    public FensterKlasseMenu() {

        //Eigenschaften der Fenster
        this.setTitle("GUI-Hausarbeit");  //Titel setzen
        this.setLocation(100, 200);  //Position setzen
        this.setSize(800, 580); // größe setzen
        this.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE); //Zum Schließen des Fensters
        this.initMenuKomponenten();    //Deklaration der initMenuKomponenten()-Methode für die Initalisierung der Komponenten
        this.ordneMenuKompomenten();   //Deklaration der ordneMenuKompomenten()-Methode zum Ordnen der Menu-Komponenten
        this.defintionMenuListener();  //Deklaration der defintionMenuListener()-Methode zur Definition der Listener
        this.addMenuListener();        //Methode zum Hinzufügen der Listener auf der Jeweilige Menu
        UIManager.put("OptionPane.noButtonText", "Nein"); // Zum Umbenennem der no Button auf dem MessageBox
        UIManager.put("OptionPane.yesButtonText", "Ja");  // Zum Umbenennem der Yes Button auf dem MessageBox
        UIManager.put("OptionPane.messageFont", new Font("Arial", Font.BOLD, 14)); //Sehr Wichtig für die Nachrichte der MessageBox
        this.setVisible(true);   //Sichtbarmachen des Frameinhalts
    }

        // initMenuKomponenten()-Methode für die Initalisierung der Komponenten
        public void initMenuKomponenten() {

            //Erzeugung der Einzel-Menus und Hinzufügen zur Menubar

            this.menu1 = new JMenu("Datei");
            this.mbar.add(menu1);

            //Erzeugung eines einfachen MenuItems fuer jeweilige  Menu

           this.menuSimpelItem1A = new JMenuItem("Schließen");
           this.menu1.add(menuSimpelItem1A);

            this.mausZeigerSimpelItem = new JMenuItem("Mauszeiger einlesen");
            this.mbar.add(mausZeigerSimpelItem);

        }

        //ordneMenuKompomenten()-Methode zum Ordnen der Menu-Komponenten
        public void ordneMenuKompomenten() {

            //Erzeugung der Einzel-Menu und  Hinzufügen zur Menubar
            this.setJMenuBar(mbar);   //Hinzufuegen zum Frame

        }

        //defintionMenuListener()-Methode zur Definition der Listener
        public void defintionMenuListener() {

            //Erzeugung eines Listeners zum MenuItem
            simpelLis = new SimpelMenuListener();

            fensterLis = new MeinFensterListener();

        }

        //Hinzufügen der Listener auf der Jeweilige Menu
        public void addMenuListener() {

            menuSimpelItem1A.addActionListener(simpelLis);  //Action Fuer der MenuItem "SChließen"
            mausZeigerSimpelItem.addActionListener(simpelLis); //Action fuer die MenuItem "Mauszeiger einlesen"

            this.addWindowListener(fensterLis); //Aktion Fuer Das Fenster beim Schließen

        }

    /**
     *
     * @param selectedFile
     * @return Cursor
     */
    public Cursor mauszeigerAendern(File selectedFile){

            try {

                BufferedImage img = ImageIO.read(selectedFile); //Einlesen der entsprechende Image beim Klichen
                Point hotSpotSmile = new Point(10,10); //Erzeugung der Hostpot
                return Toolkit.getDefaultToolkit().createCustomCursor(img, hotSpotSmile, "Cursor"); //Erzeugung der Mauszeiger

            }  catch (Exception ex) {

                //MessageBox beim falschen Eingabe der Dateien, Nur bmp-Format sind zulässig
                JOptionPane.showMessageDialog( FensterKlasseMenu.this, "Konnte Datei nicht finden","Fehler", JOptionPane.ERROR_MESSAGE);
            }

            return null;

        }

    /**
     *  Zusätzliche getExtension()-Methode zur prüfung der Extension der Bild-Format.
     * @param f
     * @return ext
     */
    private String getExtension(File f) {

        String ext = null;
        String s = f.getName();
        int i = s.lastIndexOf('.');

        if (i > 0 &&  i < s.length() - 1) {
            ext = s.substring(i+1).toLowerCase();
        }
        return ext;
    }


    /**
     * Erzeugung eines Listener Fuer Das Fenster beim Schließen
     */

    class MeinFensterListener extends WindowAdapter {

         @Override   // Aktion Beim Schließen des HauptFensters
         public void windowClosing(WindowEvent e) {

            int confirmed = JOptionPane.showConfirmDialog(FensterKlasseMenu.this,
                    "Wollen Sie gern wirklich das Schießen?", "Schließen Beim Verlassen Des Programm!!",
                    JOptionPane.YES_NO_OPTION);

            if (confirmed == JOptionPane.YES_OPTION) {

                System.exit(1);
            }
            return;

        }

    }

    //Listener für Auswahl eines einfachen Menu-Punkts

    class SimpelMenuListener implements ActionListener{


        @Override
        public void actionPerformed(ActionEvent e) {

            if(e.getActionCommand().equals("Schließen")){

                /*Aufruf der statischen Methode showConfirmDialog() zum Messagebox
               fuer die MenuItem Schließen */

                int eingabe = JOptionPane.showConfirmDialog(FensterKlasseMenu.this,"Möchten Sie Wirklick Schließen?",
                        "Bitte Warten!!",JOptionPane.YES_NO_OPTION);

                if(eingabe == JOptionPane.YES_OPTION){

                    System.exit(1);
                }
                return;
            }

            if(e.getActionCommand().equals("Mauszeiger einlesen")) {

                //Erzeugung des Objekt(meinDialog) mit Initialisierung der Parameter  für die Klasse DialogFenster
                DialogFenster meinDialog = new DialogFenster("bmp", "Nur Dateinamen in bmp-Format");
                meinDialog.initFileChooserDialogKomponet();  //Aufruf der Komponten der DialogFenster-Klasse, bevor der FileChosser erzeugt wird
                fileChooser = new JFileChooser("C:\\Users\\leone\\Desktop\\BMP_Image"); //Erzeugung der Filechooser und spezifizierung der Path des Verzeichnisses

                fileChooser.addPropertyChangeListener(new PropertyChangeListener() {
                    @Override
                    public void propertyChange(PropertyChangeEvent evt) {

                        if (JFileChooser.SELECTED_FILE_CHANGED_PROPERTY
                                .equals(evt.getPropertyName())) {
                            JFileChooser chooser = (JFileChooser) evt.getSource();


                            // The selected file should always be the same as newFile
                            File curFile = chooser.getSelectedFile();
                            if (getExtension(curFile).equals("bmp")) {

                                Cursor cursor = mauszeigerAendern(curFile);
                                if (cursor != null) {

                                    fileChooser.setCursor(cursor);
                                }

                            }
                            else{
                                //MessageBox beim falschen Eingabe der Dateien, Nur bmp-Format sind zulässig
                                JOptionPane.showMessageDialog( FensterKlasseMenu.this, "Die Datei soll im bmp-Format sein!!","Fehler", JOptionPane.ERROR_MESSAGE);
                            }

                        }

                    }
                });
                fileChooser.addChoosableFileFilter(meinDialog); // Hinzufügen des Filter auf dem Filechooser.
                fileChooser.setAcceptAllFileFilterUsed(true); //Setzen des Filters,damit alle Dateien sichtbar werden

                int result = fileChooser.showOpenDialog(FensterKlasseMenu.this); //Der Filechooser wird erstellt und an der "Mauszeiger einlesen" angehängt


                if (result == JFileChooser.APPROVE_OPTION) {

                    File selectedFile = fileChooser.getSelectedFile(); //Erzeugung der File

                    if (getExtension(selectedFile).equals("bmp")) {
                        Cursor cursor = mauszeigerAendern(selectedFile);
                        if (cursor != null) {

                            FensterKlasseMenu.this.setTitle(selectedFile.getName()); //Setzen des Titels auf dem HauptFenster
                            FensterKlasseMenu.this.setCursor(cursor);
                        }
                    }
                    else{
                        //MessageBox beim falschen Eingabe der Dateien, Nur bmp-Format sind zulässig
                        JOptionPane.showMessageDialog( FensterKlasseMenu.this, "Die Datei soll im bmp-Format sein!!","Fehler", JOptionPane.ERROR_MESSAGE);
                    }
                }

            }

            }
        }

        public static void main(String[] args) {

       // FensterKlasseMenu meinMenu = new FensterKlasseMenu();  //Erzeugung des Objekts (meinMenu) für die Klasse FensterKlasseMenu
            SwingUtilities.invokeLater(new Runnable(){
                public void run()
                {
                    new FensterKlasseMenu();
                }
            });

         }
    }
