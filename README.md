# Esp32-Led-Matrix
Da qui potete scaricare tutto quello che serve per utilizzare una o più matrici LED con Esp32 utilizzando la driver board di Futura Elettronica.
# Maggiori informazioni
Articolo dedicato: https://futuranet.it/prodotto/n-271-febbraio-2023-marzo-2023/?ref=13136

Link della driver board: https://futuranet.it/prodotto/board-controller-per-matrici-a-led/?ref=13136

# Librerie necessarie

https://github.com/mrfaptastic/ESP32-HUB75-MatrixPanel-DMA

# Convertire GIF
Per convertire le GIF, la procedura che ho seguito è la seguente:

1) dal sito https://ezgif.com/ modificare la GIF in un formato 64x64, 64x32, 16x16 in base al modello di matrice LED in uso
![Alt text](https://github.com/Dario-Ciceri/Futura-Elettronica-Esp32-Led-Matrix/blob/main/immagini/EZGIF.png)

![Alt text](https://github.com/Dario-Ciceri/Futura-Elettronica-Esp32-Led-Matrix/blob/main/immagini/RESIZE.png)

2) scaricare da questa repo github il file zip [image_to_c-master.zip](https://github.com/Dario-Ciceri/Futura-Elettronica-Esp32-Led-Matrix/blob/main/image_to_c-master.zip) ed estrarre il contenuto in una cartella

3) eseguire il terminale all'interno della cartella, per farlo basta aggiungere "cmd" prima del percorso della cartella
![Alt text](https://github.com/Dario-Ciceri/Futura-Elettronica-Esp32-Led-Matrix/blob/main/immagini/CMD.png)
![Alt text](https://github.com/Dario-Ciceri/Futura-Elettronica-Esp32-Led-Matrix/blob/main/immagini/CMD_IMTC.png)

4) all'interno del terminale eseguite "..\image_to_c-master\dist\Windows\image_to_c64.exe" e verificate che il file .exe funzioni
![Alt text](https://github.com/Dario-Ciceri/Futura-Elettronica-Esp32-Led-Matrix/blob/main/immagini/CMD_TEST.png)

5) ora potete convertire le GIF eseguendo una linea di comando composta da più parametri:  
   "..\image_to_c-master\dist\Windows\image_to_c64.exe" [GIF_INPUT] [FILE_H_OUTPUT]

6) esempio: "..\image_to_c-master\dist\Windows\image_to_c64.exe" "C:\Users\cicer\Downloads\ezgif.com-resize (2).gif" > "C:\Users\cicer\Downloads\ezgif.com-resize (2).h"
![Alt text](https://github.com/Dario-Ciceri/Futura-Elettronica-Esp32-Led-Matrix/blob/main/immagini/ESEMPIO.png)

![Alt text](https://github.com/Dario-Ciceri/Futura-Elettronica-Esp32-Led-Matrix/blob/main/immagini/GIF_CONVERTITA.png)

# N.B.: importante l'uso della parentesi angolare ">" per indicare alla sinistra l'input e a destra l'output con i relativi formati .gif e .h
