import matplotlib.pyplot as plt

tempos = [0.1, 0.3, 5, 3.2]
elementos = [100000, 200000, 300000, 400000]
plots = plt.plot(elementos, tempos,'o-',linewidth=2)
plt.title("Gráfico Simples")
plt.xlabel("Quantidade de Elementos")
plt.ylabel("Tempos(S)")
for i,value in enumerate(tempos):
    plt.text(elementos[i], value+0.1, f'{value:.2f}', ha='center', va='bottom', fontsize=10)
    #plt.hlines(y=yval, xmin=0, xmax=xval, color='gray', linestyle='--', linewidth=1)
plt.grid()
plt.show()

input("Pressione Enter para fechar...")