import serial
import tkinter as tk


def map_value(value, from_min, from_max, to_min, to_max):
    # Función para mapear un valor de un rango a otro
    return to_min + (float(value - from_min) / float(from_max - from_min) * (to_max - to_min))


def update_background():
    # Actualizar el color de fondo según los valores recibidos por el puerto serial
    global redValue, greenValue, blueValue

    if port.in_waiting > 0:
        in_string = port.readline().decode('utf-8').strip()
        if in_string:
            try:
                colors = [float(x) for x in in_string.split(",")]
                if len(colors) >= 3:
                    redValue = int(colors[0])
                    greenValue = int(colors[1])
                    blueValue = int(colors[2])
                    print(f"rgb: {redValue}, {greenValue}, {blueValue}")
            except ValueError:
                pass

    canvas.config(bg=f'#{redValue:02x}{greenValue:02x}{blueValue:02x}')
    root.after(100, update_background)  # Llama a esta función nuevamente después de 100 ms


# Inicializar la conexión serial (ajusta el puerto según sea necesario)
port = serial.Serial('COM4', 9600)

# Valores iniciales de color
redValue, greenValue, blueValue = 0, 0, 0

# Crear la ventana principal
root = tk.Tk()
root.title("Serial Color")

# Crear un lienzo para mostrar el color de fondo
canvas = tk.Canvas(root, width=200, height=200)
canvas.pack(fill=tk.BOTH, expand=True)

# Iniciar la actualización del color de fondo
root.after(100, update_background)

# Iniciar el bucle principal de Tkinter
root.mainloop()
