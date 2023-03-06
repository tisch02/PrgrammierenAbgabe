# DHBW Stuttgart - Prgrammieren 1
Programmieren 1  
Informatik 22A  
Tino Schaare  
06.03.2023

## Dateistruktur
Das Programm nutzt neben der .exe noch zwei weitere Dateien:
1. **data.csv**: Diese Datei kann genutzt werden, um die Liste abzuspeichern. Sie wird automatisch vom Programm erstellt, wenn sie noch nicht vorhanden ist.
2. **names.txt**: Die Datei beinhaltet (ca. 100.000) Namen, die vom Programm genutzt werden, um Beispieldaensätz zu erstellen. Wichtig: die Datei muss sich im gleiche Ordner wie die .exe befinden.

Ordner  
├─ PrgrammierenAbgabe.exe  
├─ data.csv  
└─ names.txt  

## Parameter für den Aufruf
Das Programm kann optional mit folgenden Parametern aufgerufen:
- **-mm**: "Measure Mode". Aktiviert einen Modus, wo ergänzende Informationen angezeigt werden. 
So u.A. die Zeit, die benötigt wird, um einen Menüpunkt auszuführen oder die Pointer, die die Liste verknüpfen.
Der Modus kann zur Laufzeit auch über das Menü gewechselt werden.
- **-fl**: "Load from file": Wenn vorhanden, werden die Daten aus der data.csv beim Start automatisch geladen.
- **-sd \<count>** "Sample data": Generiert automatisch Beispieldatensätze. _Count_ gibt dabei die Anzahl an.
Diese Anzahl muss, mit einem Leerzeichen getrennt, direkt hinter -sd angegeben werden und muss zwischen 1 und 100000 liegen.

Soll -fl und -sd gleichzeitig genutzt werden, sollte -fl vor -sd angeführt werden, da sonst der Dialog angezeigt wird, um zu entscheiden, ob
die bestehenden Daten ergänzt oder überschrieben werden sollen.

**Beispiel**:
`PrgrammierenAbgabe.exe -mm -fl -sd 100` startet das Programm im *Measure Mode*, versucht die Daten aus der data.csv zu laden
und ergänzt noch 100 Beispieldatensätze.

## Unique selling point
Das Programm kann automatisch realistische Datensätze in großen Mengen generieren. Die Menge ist auf 100.000 begrenzt
(mehr wurde nicht getestet). Diese Daten können gut genutzt werden, um z.B. die beiden implementierten Sortieralgorithmen
zu testen.

### Sortier-Algorithmen
Implementiert sind *Bubblesort* und *Quicksort*. Die Liste wird aufsteigend anhand des Alters sortiert.
Die Algorithmen unterscheiden sich in ihrer mittleren Zeitkomplexität. (Bubblesort: n^2 vs. Quicksort: n*log(n))

Die Zeitunterschiede können gut mit dem *Measure Mode* analysiert werden. **Achtung!**: Bei einer Anzahl von 100.000 Elementen
kann das Programm beim *Bubblesort* sehr lange laufen. Quicksort benötigt für 100.000 elemente ca. 8 Minuten.

## Systeminformationen 

Folgende Spezifikationen hat das Entwicklungssystem, auf dem das Programm auch kompiliert wurde:
- Windows 11 Pro, Version 10.0.22621 Build 22621
- Entwicklung in CLion 2022.2.4
- Toolchain: MinGW (w64 9.0), CMake (3.23.2), Compiler: gcc.exe

## GitHub

Das Projekt ist auch auf unter folgenden Link auf GitHub einsehbar:
[GitHub.com](https://github.com/)


