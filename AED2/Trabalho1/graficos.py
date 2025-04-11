import matplotlib.pyplot as plt

tempos = [0.1, 0.3, 5, 3.2]
elementos = [100000, 200000, 300000, 400000]
lista = []
bars = plt.bar(elementos, tempos,linewidth=30,edgecolor="skyblue")
plt.title("Gráfico Simples")
plt.xlabel("Quantidade de Elementos")
plt.ylabel("Tempos(S)")
for bar in bars:
    yval = bar.get_height()  # Valor no eixo Y
    xval = bar.get_x() + bar.get_width()  # Posição no eixo X
    plt.text(xval-10000, yval+0.1, f'{yval:.2f}', va='center', ha='left', color='black')
plt.grid()
plt.show()
input("Pressione Enter para fechar...")