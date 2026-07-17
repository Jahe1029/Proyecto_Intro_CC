import numpy as np

# Configuración de las órbitas
radios = [25, 200, 500]
factores = [1, 2, 3]

# Nombres de una sola palabra elegidos
nombres_archivos = ["eter.txt", "vortex.txt", "quimera.txt"]

# Generamos el barrido de tiempo (un ciclo completo del sistema)
tiempo = np.linspace(0, 2 * np.pi, 500)

# Generar y escribir cada archivo
for r, w, nombre in zip(radios, factores, nombres_archivos):
    # Ecuaciones paramétricas de la órbita en función del tiempo
    x = r * np.cos(w * tiempo)
    y = r * np.sin(w * tiempo)
    
    # Escritura limpia sin rodeos técnicos en los nombres
    with open(nombre, "w", encoding="utf-8") as f:
        for t_i, x_i, y_i in zip(tiempo, x, y):
            f.write(f"{x_i:.6f}\t{y_i:.6f}\t0\n")

print("Archivos creados: eter.txt, vortex.txt y quimera.txt")
