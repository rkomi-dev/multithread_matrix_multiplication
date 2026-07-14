# Moltiplicazione di Matrici Multithread in C


Progetto finale  per il corso di **Sistemi Operativi** incentrato sulla concorrenza e sul calcolo parallelo tramite l'uso della libreria standard POSIX Threads (`pthread.h`) in linguaggio C.

---

## Descrizione del Progetto

Il progetto implementa la moltiplicazione di due matrici quadrate $A$ e $B$ di grandi dimensioni ($1000 \times 1000$) popolandole con valori casuali. 

Il calcolo viene parallelizzato sfruttando il paradigma del **Data Parallelism**:
* La matrice risultante $C$ viene idealmente suddivisa in blocchi orizzontali di righe.
* Ciascun thread creato si occupa di calcolare esclusivamente una determinata porzione di righe.
* **Sincronizzazione zero:** Poiché ogni thread scrive in aree di memoria completamente disgiunte della matrice risultante $C$ (e legge soltanto da $A$ e $B$), non si verificano *race condition* in scrittura. Questo evita l'uso di mutex o semafori, massimizzando le prestazioni computazionali senza overhead di locking.

---

## Struttura del Repository

* `multithread_matrici.c`: Versione ottimizzata per matrici di grandi dimensioni ($1000 \times 1000$) che accetta il numero di thread come argomento e restituisce il tempo preciso di calcolo.
* `performance.py`: Script in Python che automatizza l'esecuzione del benchmark su diverse configurazioni di thread (1, 2, 4, 8, 16) e genera un grafico delle prestazioni.

---

## Requisiti e Installazione

### Prerequisiti
* Un compilatore C 
* Libreria standard `pthread` 
* Python 3 e la libreria `matplotlib`

Per installare i requisiti Python:
```bash
pip install matplotlib
