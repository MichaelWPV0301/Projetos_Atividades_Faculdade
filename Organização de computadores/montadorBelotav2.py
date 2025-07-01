# Aluno : Pedro Henrique Belota Gadelha
# Matrícula: 22401920

import sys  # Importa o módulo sys para interagir com o sistema, como acessar argumentos de linha de comando.
import os   # Importa o módulo os para interagir com o sistema operacional, como manipular caminhos de arquivo.
from enum import Enum  # Importa a classe Enum do módulo enum para criar enumerações.

# Constantes globais da montagem
CABECALHO_ARQUIVO = "v3.0 hex words plain\n"  # Define o cabeçalho padrão para o arquivo de saída.
TAMANHO_BYTE = 1  # Define o tamanho de um byte em bytes (usado para cálculo de bits).
BITS_TOTAIS = TAMANHO_BYTE * 8  # Calcula o número total de bits em um byte (1 byte * 8 bits/byte = 8 bits).
VALOR_MAXIMO = (1 << (BITS_TOTAIS - 1)) - 1  # Calcula o valor máximo para um número assinado de 8 bits (2^(8-1) - 1 = 127).
VALOR_MINIMO = -(1 << (BITS_TOTAIS - 1))     # Calcula o valor mínimo para um número assinado de 8 bits (-(2^(8-1)) = -128).
MASCARA_BITS = (1 << BITS_TOTAIS) - 1     # Cria uma máscara de bits para garantir que os valores caibam em 8 bits (2^8 - 1 = 255, ou 0xFF).
AJUSTE_NEGATIVO = (1 << BITS_TOTAIS)      # Valor para ajustar números negativos para sua representação de complemento de dois (2^8 = 256).
MEMORIA_LIMITE = 256                      # Define o tamanho máximo da memória em bytes (256 bytes).

# Enumeração com os códigos das instruções
class CodigoInstrucao(Enum):
    # Sobrescreve o método __new__ para permitir que cada membro da enumeração tenha um valor e um atributo adicional.
    def __new__(cls, opcode, usa_segundo_byte=False):
        obj = object.__new__(cls)  # Cria uma nova instância do objeto.
        obj._value_ = opcode       # Define o valor principal (opcode) do membro da enumeração.
        obj.usa_segundo_byte = usa_segundo_byte  # Atributo booleano indicando se a instrução usa um segundo byte (para operandos imediatos ou endereços).
        return obj

    # Definição das instruções com seus opcodes e indicação se usam segundo byte.
    LD = (0x00, False)   # Load
    ST = (0x10, False)   # Store
    DATA = (0x20, True)  # Carrega dado imediato
    JMPR = (0x30, False) # Jump Relative
    JMP = (0x40, True)   # Jump Absolute
    JC = (0x58, True)    # Jump if Carry
    JA = (0x54, True)    # Jump if Above
    JE = (0x52, True)    # Jump if Equal
    JZ = (0x51, True)    # Jump if Zero
    JCA = (0x5C, True)   # Jump if Carry and Above
    JCE = (0x5A, True)   # Jump if Carry and Equal
    JCZ = (0x59, True)   # Jump if Carry and Zero
    JAE = (0x56, True)   # Jump if Above and Equal
    JAZ = (0x55, True)   # Jump if Above and Zero
    JEZ = (0x53, True)   # Jump if Equal and Zero
    JCAE = (0x5E, True)  # Jump if Carry and Above and Equal
    JCAZ = (0x5D, True)  # Jump if Carry and Above and Zero
    JCEZ = (0x5B, True)  # Jump if Carry and Equal and Zero
    JAEZ = (0x57, True)  # Jump if Above and Equal and Zero
    JCAEZ = (0x5F, True) # Jump if Carry and Above and Equal and Zero
    CLF = (0x60, False)  # Clear Flags
    IN = (0x70, False)   # Input
    OUT = (0x78, False)  # Output
    ADD = (0x80, False)  # Add
    SHR = (0x90, False)  # Shift Right
    SHL = (0xA0, False)  # Shift Left
    NOT = (0xB0, False)  # Bitwise NOT
    AND = (0xC0, False)  # Bitwise AND
    OR = (0xD0, False)   # Bitwise OR
    XOR = (0xE0, False)  # Bitwise XOR
    CMP = (0xF0, False)  # Compare

# Classe para representar uma linha de instrução parsed (analisada).
class LinhaInstrucao:
    # Construtor da classe LinhaInstrucao.
    def __init__(self, operacao="", arg1="", arg2=""):
        self.operacao = operacao  # String que representa a operação (ex: "ADD", "JMP").
        self.arg1 = arg1          # String que representa o primeiro argumento (ex: "R0", "10").
        self.arg2 = arg2          # String que representa o segundo argumento (ex: "R1", "0xAF").

# Função para verificar os argumentos da linha de comando.
def verificar_argumentos():
    if len(sys.argv) != 3:  # Verifica se o número de argumentos é diferente de 3 (script, arquivo_entrada, arquivo_saida).
        print("Uso correto: python3 montador.py <entrada.asm> <saida.txt>") # Mensagem de uso correto.
        sys.exit(1)  # Sai do programa com código de erro.

    ext1 = os.path.splitext(sys.argv[1])[1].lower()  # Extrai a extensão do primeiro argumento (arquivo de entrada) e converte para minúsculas.
    ext2 = os.path.splitext(sys.argv[2])[1].lower()  # Extrai a extensão do segundo argumento (arquivo de saída) e converte para minúsculas.

    if ext1 != ".asm" or ext2 != ".txt":  # Verifica se as extensões são ".asm" e ".txt" respectivamente.
        print("Extensões devem ser .asm e .txt.") # Mensagem de erro de extensão.
        sys.exit(1)  # Sai do programa com código de erro.

# Função para carregar os arquivos de entrada e saída.
def carregar_arquivos():
    try:
        origem = open(sys.argv[1], "r")  # Abre o arquivo de entrada para leitura.
        destino = open(sys.argv[2], "w") # Abre o arquivo de saída para escrita.
        destino.write(CABECALHO_ARQUIVO) # Escreve o cabeçalho no arquivo de saída.
        return origem, destino           # Retorna os objetos de arquivo.
    except FileNotFoundError:  # Captura a exceção se o arquivo de entrada não for encontrado.
        print(f"O arquivo {sys.argv[1]} não foi encontrado.") # Mensagem de erro.
        sys.exit(1)  # Sai do programa com código de erro.

# Função para interpretar uma linha do código assembly.
def interpretar_linha(texto):
    texto_original = texto.strip()  # Mantém uma cópia do texto original sem espaços em branco no início/fim.
    texto = texto.upper().split(";")[0].strip()  # Converte para maiúsculas, remove comentários (a partir de ';') e espaços.
    texto = texto.replace(",", " ")  # Substitui vírgulas por espaços para facilitar a separação de argumentos.
    if not texto:  # Se a linha estiver vazia após processamento (ex: apenas comentário ou linha em branco).
        return None # Retorna None.
    if ":" in texto:  # Verifica se a linha contém um rótulo (label).
        label, rest = texto.split(":", 1)  # Divide a linha em rótulo e o restante após o ':'.
        if rest.strip():  # Se houver alguma instrução após o rótulo na mesma linha.
            partes = rest.strip().split()  # Divide o restante em partes (operação e argumentos).
            op = partes[0]  # A primeira parte é a operação.
            arg1 = partes[1] if len(partes) > 1 else None # O segundo é o primeiro argumento, se existir.
            arg2 = partes[2] if len(partes) > 2 else None # O terceiro é o segundo argumento, se existir.
            # Retorna uma lista contendo uma tupla (para o rótulo) e um objeto LinhaInstrucao (para a instrução).
            return [("LABEL", label.strip()), LinhaInstrucao(op, arg1, arg2)]
        return ("LABEL", label.strip())  # Retorna apenas o rótulo se não houver instrução na mesma linha.
    partes = texto.split()  # Se não houver rótulo, divide a linha diretamente em partes.
    if not partes:  # Se não houver partes (linha vazia ou apenas espaços).
        return None # Retorna None.
    op = partes[0]  # A primeira parte é a operação.
    arg1 = partes[1] if len(partes) > 1 else None # O segundo é o primeiro argumento, se existir.
    arg2 = partes[2] if len(partes) > 2 else None # O terceiro é o segundo argumento, se existir.
    return LinhaInstrucao(op, arg1, arg2) # Retorna um objeto LinhaInstrucao.

# Função para obter o índice de um registrador a partir do seu nome (ex: "R0" -> 0).
def obter_registrador(nome):
    if not nome or not nome.upper().startswith("R") or not nome[1:].isdigit(): # Verifica se o nome é válido (começa com 'R' e o restante é dígito).
        print(f"Registrador inválido: {nome}") # Mensagem de erro.
        sys.exit(1) # Sai do programa com código de erro.
    indice = int(nome[1])  # Extrai o dígito após o 'R' e converte para inteiro.
    if 0 <= indice <= 3:  # Verifica se o índice está no intervalo válido (0 a 3).
        return indice      # Retorna o índice do registrador.
    print(f"Registrador fora do intervalo válido: {nome}") # Mensagem de erro.
    sys.exit(1) # Sai do programa com código de erro.

# Função para localizar o objeto CodigoInstrucao a partir do nome da instrução.
def localizar_instrucao(nome):
    for codigo in CodigoInstrucao: # Itera sobre todos os membros da enumeração CodigoInstrucao.
        if codigo.name == nome:    # Se o nome do membro for igual ao nome fornecido.
            return codigo          # Retorna o objeto CodigoInstrucao correspondente.
    return None # Retorna None se a instrução não for encontrada.

# Função para converter um operando (valor imediato) para sua representação numérica.
def converter_operando(entrada):
    # Verifica se a entrada não é nula e não é um registrador ou as palavras-chave "DATA", "ADDR".
    if entrada and not entrada.startswith("R") and entrada not in {"DATA", "ADDR"}:
        try:
            if entrada.startswith("0X"): # Se começar com "0X", é um número hexadecimal.
                valor = int(entrada, 16) # Converte de hexadecimal.
            elif entrada.startswith("0B"): # Se começar com "0B", é um número binário.
                valor = int(entrada, 2)  # Converte de binário.
            else: # Caso contrário, é um número decimal.
                valor = int(entrada)     # Converte de decimal.
                if valor < VALOR_MINIMO or valor > VALOR_MAXIMO: # Verifica se o valor está dentro do intervalo permitido para 8 bits.
                    raise ValueError(f"valor fora do intervalo permitido: {valor} | [{VALOR_MINIMO},{VALOR_MAXIMO}]") # Lança erro se fora do intervalo.
                if valor < 0: # Se o valor for negativo.
                    valor += AJUSTE_NEGATIVO # Ajusta para representação de complemento de dois.
            return valor & MASCARA_BITS # Retorna o valor com a máscara para garantir 8 bits.
        except ValueError as e: # Captura erros de conversão de valor.
            print(e) # Imprime o erro.
            sys.exit(1) # Sai do programa com código de erro.
    return entrada # Retorna a entrada original se não for um valor imediato a ser convertido.

# Função para converter um operando de salto (endereço) que pode ser um rótulo.
def converter_operando_jump(entrada, labels):
    if entrada.upper() in labels: # Verifica se a entrada é um rótulo definido.
        return int(labels[entrada.upper()]) # Retorna o endereço numérico associado ao rótulo.
    return converter_operando(entrada) # Se não for rótulo, tenta converter como operando normal.

# Função principal para montar uma instrução e adicioná-la à memória.
def montar_instrucao(instrucao, memoria, posicao, labels):
    # Tratamento de pseudoinstruções: MOVE, CLR, HALT.
    if instrucao.operacao == "MOVE": # Pseudoinstrução MOVE (move o conteúdo de um registrador para outro).
        r1 = obter_registrador(instrucao.arg1) # Obtém o índice do primeiro registrador.
        r2 = obter_registrador(instrucao.arg2) # Obtém o índice do segundo registrador.
        # MOVE A, B é implementado como XOR A, B; XOR B, A (swap).
        # Primeiro XOR: R2 com R1 (XOR R2, R1)
        byte = CodigoInstrucao.XOR.value | (r2 << 2) | r1 # Combina o opcode de XOR com os registradores.
        memoria[posicao] = byte # Armazena o primeiro byte na memória.
        posicao += 1           # Incrementa a posição.
        # Segundo XOR: R1 com R2 (XOR R1, R2)
        byte = CodigoInstrucao.XOR.value | (r1 << 2) | r2 # Combina o opcode de XOR com os registradores.
        memoria[posicao] = byte # Armazena o segundo byte na memória.
        posicao += 1           # Incrementa a posição.
        return posicao         # Retorna a nova posição na memória.

    if instrucao.operacao == "CLR": # Pseudoinstrução CLR (limpa o conteúdo de um registrador para 0).
        byte1 = CodigoInstrucao.DATA.value | obter_registrador(instrucao.arg1) # Combina o opcode de DATA com o registrador.
        memoria[posicao] = byte1 # Armazena o primeiro byte (opcode + registrador).
        posicao += 1           # Incrementa a posição.
        memoria[posicao] = 0x00 # Armazena o segundo byte (valor 0).
        posicao += 1           # Incrementa a posição.
        return posicao         # Retorna a nova posição na memória.

    if instrucao.operacao == "HALT": # Pseudoinstrução HALT (para a execução do programa).
        memoria[posicao] = CodigoInstrucao.JMP.value # Armazena o opcode de JMP (salto incondicional).
        posicao += 1                               # Incrementa a posição.
        memoria[posicao] = posicao - 1             # O segundo byte é o endereço de salto, que é a própria instrução JMP (loop infinito).
        posicao += 1                               # Incrementa a posição.
        return posicao                             # Retorna a nova posição na memória.

    # Tratamento de instruções reais.
    codigo = localizar_instrucao(instrucao.operacao) # Localiza o objeto CodigoInstrucao para a operação.
    if not codigo: # Se a instrução não for reconhecida.
        print(f"Instrução desconhecida: {instrucao.operacao}") # Mensagem de erro.
        sys.exit(1) # Sai do programa com código de erro.

    byte1 = codigo.value # O primeiro byte é o valor do opcode da instrução.
    byte2 = 0x00         # Inicializa o segundo byte como 0 (será usado apenas se a instrução precisar).

    # Diferencia o tratamento de acordo com o tipo de instrução.
    if codigo.name in {"LD", "ST", "ADD", "SHR", "SHL", "NOT", "AND", "OR", "XOR", "CMP"}:
        op1 = obter_registrador(instrucao.arg1) # Obtém o índice do primeiro registrador.
        op2 = obter_registrador(instrucao.arg2) # Obtém o índice do segundo registrador.
        byte1 |= (op1 << 2) | op2 # Combina os bits dos registradores no primeiro byte (op1 nos bits 3-2, op2 nos bits 1-0).
    elif codigo.name == "DATA":
        op1 = obter_registrador(instrucao.arg1)    # Obtém o índice do registrador.
        op2 = converter_operando(instrucao.arg2) # Converte o operando imediato.
        byte1 |= op1 # Combina o registrador no primeiro byte (bits 1-0).
        byte2 = op2  # O segundo byte é o valor imediato.
    elif codigo.name in {"IN", "OUT"}:
        tipo1 = 1 if codigo.name == "OUT" else 0 # Define o bit para IN/OUT (bit 3).
        tipo0 = 1 if instrucao.arg1 == "ADDR" else 0 # Define o bit para ADDRESS/DATA (bit 2).
        op2 = obter_registrador(instrucao.arg2) # Obtém o índice do registrador.
        byte1 |= (tipo1 << 3) | (tipo0 << 2) | op2 # Combina os bits de tipo e o registrador no primeiro byte.
    elif codigo.name == "JMPR":
        op1 = obter_registrador(instrucao.arg1) # Obtém o índice do registrador (offset relativo).
        byte1 |= op1 # Combina o registrador no primeiro byte (bits 1-0).
    elif codigo.name == "CLF":
        byte1 = codigo.value # Para CLF, o primeiro byte é apenas o opcode.
    else: # Para todas as outras instruções de salto (que usam segundo byte para o endereço).
        byte2 = converter_operando_jump(instrucao.arg1, labels) # Converte o operando de salto (pode ser rótulo ou valor).

    # Verificação e armazenamento na memória.
    if posicao >= MEMORIA_LIMITE: # Verifica se a posição atual excede o limite da memória.
        print("Memória insuficiente para armazenar o programa.") # Mensagem de erro.
        sys.exit(1) # Sai do programa com código de erro.

    memoria[posicao] = byte1 # Armazena o primeiro byte da instrução na memória.
    posicao += 1             # Incrementa a posição.

    if codigo.usa_segundo_byte: # Se a instrução usa um segundo byte.
        if posicao >= MEMORIA_LIMITE: # Verifica novamente o limite da memória.
            print("Memória insuficiente para segundo byte da instrução.") # Mensagem de erro.
            sys.exit(1) # Sai do programa com código de erro.
        memoria[posicao] = byte2 # Armazena o segundo byte na memória.
        posicao += 1             # Incrementa a posição.

    return posicao # Retorna a nova posição na memória após a montagem da instrução.

# Função para gravar o conteúdo da memória no arquivo de saída.
def gravar_memoria(memoria, tamanho, arquivo_saida):
    for i in range(tamanho, MEMORIA_LIMITE): # Preenche o restante da memória com 0x00 se não estiver totalmente preenchida.
        memoria.append(0x00) # Adiciona 0x00 até o limite da memória.
    for i in range(MEMORIA_LIMITE): # Itera por toda a memória.
        arquivo_saida.write(f"{memoria[i]:02x} ") # Escreve cada byte em formato hexadecimal com dois dígitos e um espaço.
        if (i + 1) % 16 == 0: # A cada 16 bytes.
            arquivo_saida.write("\n") # Adiciona uma nova linha para formatar a saída.

# Função principal do montador.
def main():
    verificar_argumentos() # Chama a função para verificar os argumentos da linha de comando.
    arquivo_entrada, arquivo_saida = carregar_arquivos() # Chama a função para carregar os arquivos.

    memoria_ram = [0x00] * MEMORIA_LIMITE # Inicializa a memória RAM com zeros.
    posicao_atual = 0                     # Inicializa a posição atual de escrita na memória.
    linhas = arquivo_entrada.readlines()  # Lê todas as linhas do arquivo de entrada.

    labels = {}     # Dicionário para armazenar os rótulos e seus endereços.
    pos_tmp = 0     # Posição temporária para calcular os endereços dos rótulos na primeira passagem.
    instrucoes_lidas = [] # Lista para armazenar as instruções lidas (para a segunda passagem).

    # Primeira Passagem: Coleta de rótulos e cálculo de endereços.
    for linha in linhas: # Itera sobre cada linha do arquivo de entrada.
        resultado = interpretar_linha(linha) # Interpreta a linha.
        if resultado is None: # Se a linha for vazia ou apenas comentário.
            continue # Pula para a próxima linha.
        if isinstance(resultado, list): # Se a linha contém um rótulo e uma instrução.
            for item in resultado: # Itera sobre os itens da lista.
                if isinstance(item, tuple) and item[0] == "LABEL": # Se for um rótulo.
                    labels[item[1].upper()] = pos_tmp # Armazena o rótulo e sua posição temporária.
                elif isinstance(item, LinhaInstrucao): # Se for uma instrução.
                    instrucoes_lidas.append(item) # Adiciona a instrução à lista.
                    # Calcula o tamanho da instrução para atualizar a posição temporária.
                    if item.operacao == "MOVE":
                        pos_tmp += 2
                    elif item.operacao == "CLR":
                        pos_tmp += 2
                    elif item.operacao == "HALT":
                        pos_tmp += 2
                    else:
                        codigo = localizar_instrucao(item.operacao)
                        if codigo:
                            pos_tmp += 2 if codigo.usa_segundo_byte else 1
        elif isinstance(resultado, tuple) and resultado[0] == "LABEL": # Se a linha contém apenas um rótulo.
            labels[resultado[1].upper()] = pos_tmp # Armazena o rótulo e sua posição temporária.
        elif isinstance(resultado, LinhaInstrucao): # Se a linha contém apenas uma instrução.
            instrucoes_lidas.append(resultado) # Adiciona a instrução à lista.
            # Calcula o tamanho da instrução para atualizar a posição temporária.
            if resultado.operacao == "MOVE":
                pos_tmp += 2
            elif resultado.operacao == "CLR":
                pos_tmp += 2
            elif resultado.operacao == "HALT":
                pos_tmp += 2
            else:
                codigo = localizar_instrucao(resultado.operacao)
                if codigo:
                    pos_tmp += 2 if codigo.usa_segundo_byte else 1

    # Segunda Passagem: Montagem das instruções.
    for instrucao in instrucoes_lidas: # Itera sobre as instruções coletadas na primeira passagem.
        # Monta a instrução, usando os rótulos e seus endereços calculados, e atualiza a posição atual na memória real.
        posicao_atual = montar_instrucao(instrucao, memoria_ram, posicao_atual, labels)

    gravar_memoria(memoria_ram, posicao_atual, arquivo_saida) # Grava o conteúdo da memória no arquivo de saída.
    arquivo_entrada.close() # Fecha o arquivo de entrada.
    arquivo_saida.close()   # Fecha o arquivo de saída.
    print(f"Montagem concluída com sucesso. Arquivo gerado em {sys.argv[2]}") # Mensagem de sucesso.

main() # Chama a função principal para iniciar o montador.