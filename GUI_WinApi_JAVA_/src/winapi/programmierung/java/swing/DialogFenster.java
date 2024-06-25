
/*****************************************************************
 * Autor: Leonel Nguimatsia                                      *
 * @version: IntelliJ2021 JDK16                                  *
 * Hochschule: TH-Kloen                                          *
 * Ort: Deutz Technische Hochschule                              *
 * Webmail: leonel.nguimatsia_tsobguim@smail.th-koeln.de         *
 * Beschreibung: EntitaetKlasse DialogKlasse                     *
 *                                                               *
 *****************************************************************/

package winapi.programmierung.java.swing;

import javax.swing.*;
import javax.swing.filechooser.FileFilter;
import java.io.File;

public class DialogFenster extends FileFilter  {

    private String extension;  // Deklaration der Attribut extension
    private String description; //Deklaration der Attribut Description

    //Konstruktor der Klasse DialogKlasse mit Parameter und Initialisierung dieser Paramter
    public DialogFenster(String extension, String description){

        this.initFileChooserDialogKomponet(); //Deklaration der initFileChooserDialogKomponet()-Methode für die Komponenten
        this.extension = extension;
        this.description = description;

    }

   //Implementierung der initFileChooserDialogKomponet()-Methode
    public void initFileChooserDialogKomponet(){

        UIManager.put("FileChooser.openDialogTitleText","DialogFenster"); // Zum Umbenennem der openDialogTitleText auf FileChooser-Fenster
        UIManager.put("FileChooser.lookInLabelText", "Suche In");         // Zum Umbenennem der lookInLabelText auf dem FileChooser-Fenster
        UIManager.put("FileChooser.openButtonText", "Übernehmen");        // Zum Umbenennem der openButtonText auf dem FileChooser-Fenster
        UIManager.put("FileChooser.cancelButtonText","Schließen");        // Zum Umbenennem der cancelButtonText auf dem FileChooser-Fenster
        UIManager.put("FileChooser.fileNameLabelText","DateiName");       // Zum Umbenennem der fileNameLabelText auf dem FileChooser-Fenster
        UIManager.put("FileChooser.filesOfTypeLabelText","DateiType");   // Zum Umbenennem der filesOfTypeLabelText auf dem FileChooser-Fenster

    }

    @Override //Methode accept für die FileFilter-Klasse
    public boolean accept(File file) {

        if (file.isDirectory()) {
            return true;
        }
        return file.getName().endsWith(extension);

    }


    @Override //Methode getDescription für die FileFilter-Klasse
    public String getDescription() {

        return description + String.format(" (*%s)", extension);
    }

 }
