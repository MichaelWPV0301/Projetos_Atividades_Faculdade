import matplotlib.pyplot as plt
from matplotlib.ticker import FuncFormatter
import numpy as np
import pandas as pd


def formatar(y,pos):
    if(y<1):
        return f"{y*1000:.2f}(ms)"

    
    return f"{y}s"
# Lendo o CSV


dataframe = pd.read_csv("~/Documentos/michael/Projetos_Atividades_Faculdade/AED2/Trabalho1/dados_5.csv")
x1 = dataframe.iloc[0, 1:].values
x2 = dataframe.iloc[1, 1:].values
x3 = dataframe.iloc[2, 1:].values
x4 = dataframe.iloc[3, 1:].values
x5 = dataframe.iloc[5, 1:].values
x6 = dataframe.iloc[6, 1:].values
x7 = dataframe.iloc[7, 1:].values
x8 = dataframe.iloc[8, 1:].values
x9 = dataframe.iloc[9, 1:].values

y1  = dataframe.columns[1:].values
y2  = dataframe.iloc[4, 1:].values

# ----- Primeiro gráfico -----
fig = plt.figure(figsize=(8, 5))
ax = fig.subplots()
plt.plot(y1, x1, 'o-', linewidth=2, label='Busca Sequencial')
plt.plot(y1, x2, 'o-', linewidth=2, label='Busca Binaria')

plt.title("Busca Sequencial X Busca Binaria")
plt.xlabel("Quantidade de Elementos")
plt.ylabel("Tempos (s)")
plt.legend()


ax.yaxis.set_major_formatter(FuncFormatter(formatar))
plt.grid()
plt.tight_layout()
plt.show()
plt.close()  # <- fecha o gráfico, liberando o terminal
# Espera do usuário para continuar





# ----- Segundo gráfico -----
fig = plt.figure(figsize=(8, 5))
ax = fig.subplots()
plt.plot(y1, x4, 'o-', linewidth=2, label='Busca Vetor')
plt.plot(y1, x3, 'o-', linewidth=2, label='Busca Lista Encadeada')

plt.title("Busca Sequencial: Lista Encadeada X Vetor")
plt.xlabel("Quantidade de Elementos")
plt.ylabel("Tempos (s)")
plt.legend()


ax.yaxis.set_major_formatter(FuncFormatter(formatar))
plt.grid()
plt.show()



#Terceiro gráfico todos o sort Ruins: ------------------------------------------------------------------------------------
fig = plt.figure(figsize=(8, 5))
ax = fig.subplots()
plt.plot(y2, x5, 'o-', linewidth=2, label='Bolha')
plt.plot(y2, x6, 'o-', linewidth=2, label='Selection')
plt.plot(y2, x7, 'o-', linewidth=2, label='Inserction')

plt.title("Ordenacao: Inserction X Selection X Bolha")
plt.xlabel("Quantidade de Elementos")
plt.ylabel("Tempos (s)")
plt.legend()

''''
for i, value in enumerate(x4):
    plt.text(x4[i], value + 0.1, f'{value:.2f}', ha='center', va='bottom', fontsize=10)

for i, value in enumerate(x5):
    plt.text(x5[i], value + 0.1, f'{value:.2f}', ha='center', va='bottom', fontsize=10)

for i, value in enumerate(x6):
    plt.text(x6[i], value + 0.1, f'{value:.2f}', ha='center', va='bottom', fontsize=10)
'''

ax.yaxis.set_major_formatter(FuncFormatter(formatar))
plt.grid()
plt.show()
plt.close()  

#Quarto gráfico todos o sort bons: ------------------------------------------------------------------------------------
fig = plt.figure(figsize=(8, 5))
ax = fig.subplots()
plt.plot(y2, x8, 'o-', linewidth=2, label='quick')
plt.plot(y2, x9, 'o-', linewidth=2, label='merge')

plt.title("Ordenacao: Inserction X Selection X Bolha")
plt.xlabel("Quantidade de Elementos")
plt.ylabel("Tempos (s)")
plt.legend()



ax.yaxis.set_major_formatter(FuncFormatter(formatar))
plt.grid()
plt.show()
