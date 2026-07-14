import subprocess
import matplotlib.pyplot as plt

# Numero di thread da testare
configurazioni_thread = [1, 2, 4, 8, 16]
tempi = []

print("Inizio benchmark...")

for num_thread in configurazioni_thread:
    print(
        f"Esecuzione con {num_thread} thread...", end="", flush=True
    )
    
    # Esegue il file C compilato passandogli il numero di thread come argomento
    risultato = subprocess.run(['./multithread_matrici', str(num_thread)], capture_output=True, text=True)
    
    # Prende il tempo stampato dal programma C
    tempo = float(risultato.stdout.strip())
    tempi.append(tempo)
    print(f" Completato in {tempo:.4f} secondi")

# Creazione del grafico
plt.figure(figsize=(8, 5))
plt.plot(configurazioni_thread, tempi, marker='o', linestyle='-', color='b', linewidth=2)

plt.title("Performance Moltiplicazione Matrici Multithread (1000x1000)", fontsize=14, fontweight='bold')
plt.xlabel("Numero di Thread", fontsize=12)
plt.ylabel("Tempo di Esecuzione (Secondi)", fontsize=12)
plt.xticks(configurazioni_thread)
plt.grid(True, linestyle='--', alpha=0.6)

# Salva l'immagine del grafico
plt.savefig('grafico_prestazioni.png')
print("\nGrafico salvato con successo come 'grafico_prestazioni.png'!")
plt.show()