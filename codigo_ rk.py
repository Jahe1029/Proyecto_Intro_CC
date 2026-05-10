import numpy as np 
import math


def suma(a, b):
    sum = a + b
    return sum

x = suma(2,10)
print (x)
"""
def op(func, y_i, x_i):
     return func(y_i, x_i)
"""

def radio(y_i, x_i):
    r2=(y_i**2)+(x_i**2)
    return math.sqrt(r2)

"""
print(op(radio,3,4))
 
"""

def Rk_4(h, y_i, x_i, f):
    k1=(h*f(x_i, y_i))
    k2=(h*f(x_i + (0.5*h),  y_i + (0.5*k1)))
    k3=(h*f(x_i + (0.5*h),  y_i + (0.5*k2)))
    k4=(h*f(x_i + h,  y_i + k3))
    y_ii = y_i + (1/6 * (k1 + 2*k2 + 2*k3 + k4))
    return y_ii 

def fc (y, x):
    resultado =-2*x
    return resultado

e1 = Rk_4(0.001, 1.5, 1, fc)
print(e1)



"""
def operacion(func, valor):
    return func(valor)

def cuadrado(n):
    return n * n

resultado = operacion(cuadrado, 5)  # Pasamos 'cuadrado' como argumento
print(resultado)  # Salida: 25

"""