<b>Proiect la 'Sisteme Specializate cu Microprocesoare'</b>

Echipa:

IONASCU Bianca-Daniela (C114D)

TOADER Radu-Marian (C114C)

# Componenta proiect

1. In folderul 'doc' se afla: 
    1.1. folderul 'drawio' in care avem toate schemele necesare pentru documentatie
    1.2. folderul 'img' in care se regasesc toate imaginile folosite in documentatie
    1.3. folderul 'videoclipuri' in care se regaseste un videoclip in care prezentam functionarea programului (un demo al programului folosind interfata grafica)
    1.4. documentatia se afla in fisierul 'DOC.docx'
    1.5. cele 2 pdf-uri cu cerintele proiectului

2. In folderul 'gui' se afla codul pentru interfata grafica. Pentru a rula interfata grafica se poate deschide proiectul in VSCode si se poate rula din buton, dar tinand cont de faptul ca Main-ul 
se afla in main.py.

3. In folderul 'src' se afla codul sursa al aplicatiei. Toate fisierele sursa si headerele necesare programului. Acestea ar trebui adaugate intr-un proiect Keil.

# Configurare

## 1. Crearea unui Proiect în Keil uVision5

Urmați ghidul oferit la laborator pentru a crea un proiect în Keil uVision5.

## 2. Adăugarea Fișierelor Sursă

Adăugați toate sursele din folderul `src` în folderul proiectului. Faceți click dreapta pe `Source Group 1` și selectați sursele existente pentru a le adăuga.

## 3. Selectarea Surselor

Selectați toate sursele `.c` și `.h` și apăsați `add`.

## 4. Build și Load

Executați un `Build/Rebuild (F7)` urmat de `Load (F8)`.

## 5. Rularea Interfeței Grafice

Pentru a rula interfața grafică, trebuie instalate următoarele biblioteci Python:

- `PySide6.0` versiunea `6.6.0`
- `Pyserial` versiunea `3.5`
- `Pyqtgrapth` versiunea `0.13.3`
  Acestea se pot găsi și instala și din `requirements.txt`.

## 6. Rularea Interfeței

Rulați interfața grafică executând codul din `main.py`.

## 7. Interfața Grafică

La lansare, interfața grafică va afișa un grafic cu rezultatele obținute de la senzorul analog de sunet. Rezultatele sunt reprezentate prin barplot-uri colorate (verde, galben, roșu) în funcție de intensitatea sunetului.

## 8. Butoane de Control

În partea dreaptă se regăsesc 3 butoane:

- `Change LED order`: Schimbă ordinea de afișare a culorilor pe LED-ul de pe plăcuță.
- `Play music`: Pornește muzica pe buzzer.
- `Get light status`: Afișează datele senzorului de lumină în consolă.

Toate acestea vor transmite un mesaj sugestiv în consola de jos.

## 9. Input Text

Există și o căsuță de text în partea dreaptă unde se pot trimite mesaje ca input ce vor fi afișate în consolă. Alternativ, puteți trimite:

- `c` ↔ schimbă culoarea
- `m` ↔ pornește muzica
- `l` ↔ obține date despre lumină

Acestea sunt comenzile reale din spatele butoanelor.

## Exemplu Grafic

![Exemplu Grafic](https://github.com/radu011/SSM/blob/main/doc/img/interfataGrafica.png)
