import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

# Lendo o CSV
dataframe = pd.read_csv("dados_5.csv")
x1 = dataframe.iloc[0, 1:].values
x2 = dataframe.iloc[1, 1:].values
x3 = dataframe.iloc[2, 1:].values
x4 = dataframe.iloc[4, 1:].values
x5 = dataframe.iloc[5, 1:].values
x6 = dataframe.iloc[6, 1:].values
x7 = dataframe.iloc[7, 1:].values
x8 = dataframe.iloc[8, 1:].values

y1  = dataframe.columns[1:].values
y2  = dataframe.iloc[3, 1:].values

# ----- Primeiro gráfico -----
plt.figure(figsize=(8, 5))
plt.plot(y1, x1, 'o-', linewidth=2, label='Busca Binaria')
plt.plot(y1, x2, 'o-', linewidth=2, label='Busca Sequencial')

plt.title("Busca Sequencial X Busca Binaria")
plt.xlabel("Quantidade de Elementos")
plt.ylabel("Tempos (s)")
plt.legend()

for i, value in enumerate(x1):
    plt.text(x1[i], value + 0.1, f'{value:.2f}', ha='center', va='bottom', fontsize=10)

for i, value in enumerate(x2):
    plt.text(x2[i], value + 0.1, f'{value:.2f}', ha='center', va='bottom', fontsize=10)

plt.grid()
plt.tight_layout()
plt.show()
plt.close()  # <- fecha o gráfico, liberando o terminal
# Espera do usuário para continuar


input("Pressione Enter para mostrar o segundo gráfico...")



# ----- Segundo gráfico -----
plt.figure(figsize=(8, 5))
plt.plot(y1, x1, 'o-', linewidth=2, label='Busca Binaria')
plt.plot(y1, x3, 'o-', linewidth=2, label='Busca Sequencial')

plt.title("Busca Sequencial: Lista Encadeada X Vetor")
plt.xlabel("Quantidade de Elementos")
plt.ylabel("Tempos (s)")
plt.legend()

for i, value in enumerate(x1):
    plt.text(x1[i], value + 0.1, f'{value:.2f}', ha='center', va='bottom', fontsize=10)

for i, value in enumerate(x3):
    plt.text(x3[i], value + 0.1, f'{value:.2f}', ha='center', va='bottom', fontsize=10)

plt.grid()
plt.tight_layout()
plt.show()



#Terceiro gráfico todos o sort Ruins: ------------------------------------------------------------------------------------

plt.figure(figsize=(8, 5))
plt.plot(y2, x4, 'o-', linewidth=2, label='Bolha')
plt.plot(y2, x5, 'o-', linewidth=2, label='Selection')
plt.plot(y2, x6, 'o-', linewidth=2, label='Inserction')

plt.title("Busca Sequencial: Lista Encadeada X Vetor")
plt.xlabel("Quantidade de Elementos")
plt.ylabel("Tempos (s)")
plt.legend()

for i, value in enumerate(x4):
    plt.text(x4[i], value + 0.1, f'{value:.2f}', ha='center', va='bottom', fontsize=10)

for i, value in enumerate(x5):
    plt.text(x5[i], value + 0.1, f'{value:.2f}', ha='center', va='bottom', fontsize=10)

for i, value in enumerate(x6):
    plt.text(x6[i], value + 0.1, f'{value:.2f}', ha='center', va='bottom', fontsize=10)


plt.grid()
plt.tight_layout()
plt.show()
plt.close()  
input("Pressione Enter para mostrar o segundo gráfico...")

#Quarto gráfico todos o sort bons: ------------------------------------------------------------------------------------

plt.figure(figsize=(8, 5))
plt.plot(y2, x7, 'o-', linewidth=2, label='quick')
plt.plot(y2, x8, 'o-', linewidth=2, label='merge')

plt.title("Busca Sequencial: Lista Encadeada X Vetor")
plt.xlabel("Quantidade de Elementos")
plt.ylabel("Tempos (s)")
plt.legend()

for i, value in enumerate(x7):
    plt.text(x7[i], value + 0.1, f'{value:.2f}', ha='center', va='bottom', fontsize=10)

for i, value in enumerate(x8):
    plt.text(x8[i], value + 0.1, f'{value:.2f}', ha='center', va='bottom', fontsize=10)

plt.grid()
plt.tight_layout()
plt.show()
