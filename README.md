# Media-Reader
Un'applicazione gestionale con interfaccia grafica sviluppata in C++ per organizzare e gestire una libreria multimediale personale (Fumetti, Film e Album). Progetto sviluppato come prova pratica per l'esame universitario di Programmazione ad Oggetti.

## Tecnologie
* *Linguaggio:* C++ (C++17)
* * *Framework GUI:* Qt / Qt Widgets
* *Design Pattern:* Sviluppato con un solido approccio Object-Oriented e utilizzo del *Visitor Pattern* per l'esportazione dei dati.
* *Persistenza Dati:* Lettura, scrittura e salvataggio del catalogo tramite file JSON strutturati.

## Nota per l'esecuzione (Qt Creator)
Questo progetto è stato sviluppato per essere utilizzato nativamente tramite **Qt Creator**. 
Il codice base fa riferimento a versioni precedenti del framework Qt. Pertanto, l'ambiente ideale per la compilazione è una macchina (o macchina virtuale) con Qt Creator e librerie compatibili già configurate.

## Come avviare il progetto
Se si desidera compilare il progetto manualmente da terminale:
1. Generare il file di configurazione con `qmake`.
2. Compilare il sorgente eseguendo il comando `make`.
3. Avviare l'applicazione con `./mediaPAO`.
