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
 

def Rk_4(h, y_i, x_i, f):
    k1=(h*f(x_i, y_i))
    k2=(h*f(x_i + (0.5*h),  y_i + (0.5*k1)))
    k3=(h*f(x_i + (0.5*h),  y_i + (0.5*k2)))
    k4=(h*f(x_i + h,  y_i + k3))
    y_ii = y_i + (1/6 * (k1 + 2*k2 + 2*k3 + k4))
    return y_ii 
"""

def a_c(mu_j, mu_k, r_i, r_j, r_k): #formula de la aceleracción, debemos definir (mu_j, mu_k, r_i, r_j, r_k) como un array osea una lista
    a_c =-((mu_j*(r_i - r_j))/math.pow((np.linalg.norm(r_i - r_j)), 3))-((mu_k*(r_i - r_k))/math.pow((np.linalg.norm(r_i - r_k)), 3))
    return a_c


def f(s_m, a): #definimos la derivada dado un estado
    f(s_m,a)[0]=s_m[1]
    f(s_m,a)[1]=a_c(*(datos[:2] + [s_m[0]] + datos[3:]))  #aqui lo que hacemos es cambiar el valor de r_i ----> r_i+dela r y calculamos la aceleración
    return f(s_m, a)





def RK_4(h, s, f):
    k1=(h*f(s))
    k2=(h*f(s+(0.5*k1)))
    k3=(h*f(s+(0.5*k2)))
    k4=(h*f(s+(h*k3)))
    s = s + (1/6 * (k1 + 2*k2 + 2*k3 + k4))
    return s


def fc (y, x):         #Aqui se supone que debemos poner la ecuación de la aceleracion osea la de gravedad.
    resultado =-2*x
    return resultado
"""
e1 = Rk_4(0.001, 1.5, 1, fc)
print(e1)




def operacion(func, valor):
    return func(valor)

def cuadrado(n):
    return n * n

resultado = operacion(cuadrado, 5)  # Pasamos 'cuadrado' como argumento
print(resultado)  # Salida: 25

"""

# Definir los vectores
v1 = np.array([1, 2, 3])
v2 = np.array([4, 5, 6])

# Sumar vectores
r = v1 - v2
print(2*r)  # Resultado: [5 7 9]
