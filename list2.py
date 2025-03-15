from cmath import *
from scipy.stats import norm


mu = 445
dp = 65

def p_greater_than_x(x):
    return 1 - norm.cdf(x, loc=mu, scale=dp)

def p_less_than_x(x):
    return norm.cdf(x, loc=mu, scale=dp)

print(f'1.1. P(X > 490): {p_greater_than_x(490):.4f}')
print(f'1.2. P(X > 445): {p_greater_than_x(445):.4f}')
print(f'1.3. P(X > 380): {p_greater_than_x(380):.4f}')
print(f'1.4. P(X < 490): {p_less_than_x(490):.4f}')

p_375 = p_less_than_x(375)
p_485 = p_less_than_x(485)
print(f'1.5. P(375 < X < 485): {p_485 - p_375:.4f}')

def calculate_no(e):
    return 1 / (e**2)
    
def calculate_n(n, no):
    return (n * no) / (n + no)

e = 0.05
n = calculate_n(1000, calculate_no(e))

print(f'6.1. Tamanho da amostra: {n:.0f}')

n = calculate_n(5000, calculate_no(e))

print(f'6.2. Tamanho da amostra: {n:.0f}')


e = 0.01
p = 0.95

def calculate_n(e, p):
    return (p * (1 - p)) / (e**2)

n = calculate_n(e, p)

print(f'7. Tamanho da amostra: {n:.0f}')


a = 1 - 0.90
z_critic = norm.ppf(1 - a/2)
dp = 42
n = 50
mu = 220

print(f'8.1. Média de tempo de tela: {mu} minutos/dia')
print(f'8.2. Desvio padrão populacional: {dp} minutos/dia')
print(f'8.3. Tamanho da amostra: {n} alunos')
print(f'8.4. Valor crítico Z para um IC de 90%: {z_critic:.4f}')

e = dp / sqrt(n)
print(f'8.5. Erro padrão: {e:.4f}')

ic = z_critic * e

ic_min = mu - ic
ic_max = mu + ic

print(f'8.6. Intervalo de confiança de 90%: [{ic_min:.4f}, {ic_max:.4f}]')

a = 1 - 0.95
z_critic = norm.ppf(1 - a/2)
ic = z_critic * e

ic_min = mu - ic
ic_max = mu + ic

print(f'8.7. Intervalo de confiança de 95%: [{ic_min:.4f}, {ic_max:.4f}]')

n = 100
dp = 32
e = dp / sqrt(n)
a = 1 - 0.95
z_critic = norm.ppf(1 - a/2)
ic = z_critic * e

ic_min = mu - ic
ic_max = mu + ic

print(f'8.8. Intervalo de confiança de 95%: [{ic_min:.4f}, {ic_max:.4f}]')

n = 400
e = dp / sqrt(n)
a = 1 - 0.95
z_critic = norm.ppf(1 - a/2)
ic = z_critic * e

ic_min = mu - ic
ic_max = mu + ic

print(f'8.9. Intervalo de confiança de 95%: [{ic_min:.4f}, {ic_max:.4f}]')

a = 1 - 0.99
z_critic = norm.ppf(1 - a/2)
ic = z_critic * e

ic_min = mu - ic
ic_max = mu + ic

print(f'8.9.1. Intervalo de confiança de 99%: [{ic_min:.4f}, {ic_max:.4f}]\n')