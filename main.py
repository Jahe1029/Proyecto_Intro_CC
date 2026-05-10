import random
import numpy as np
class cuerpo:
	def __init__(self, posicion : np.array, velocidad: np.array, acelerción: np.array):
		self.r = posicion
		self.v = velocidad
		self.a = acelerción
	
	def cout(self):
		print(self.r)
		print(self.v)
		print(self.a)
	
	def RK4(self, c ):
		print(np.sum(self.r + c.r))
def save_positions():
	with open("tierra.txt", "w") as f:
		for i in range(10):
			f.write(str(random.randint(1, 100)))
			f.write(",")
			f.write(str(random.randint(1, 100)))
			f.write("\n")
def main():
	tierra = cuerpo([1, 2, 2], [0, 0, 0], [4, 5, 4])
	# tierra.cout()
	marte = cuerpo([1, 2, 2], [0, 0, 0], [4, 5, 4])
	save_positions()
main()


