import serial
import tkinter as tk


def main():
    # Inicializar la conexión serial (ajusta el puerto según sea necesario)
    port = serial.Serial('COM4', 9600)

    # Dimensiones de la ventana
    width, height = 200, 200
    box_size = 20

    # Posición inicial de la caja
    box_x, box_y = width // 2, height // 2

    def check_mouse_position(event):
        mouse_x, mouse_y = event.x, event.y

        if (box_x - box_size < mouse_x < box_x + box_size) and (box_y - box_size < mouse_y < box_y + box_size):
            canvas.itemconfig(box, outline='white', fill='green')
            port.write(b'H')
        else:
            canvas.itemconfig(box, outline='gray', fill='gray')
            port.write(b'L')

    # Crear la ventana principal
    root = tk.Tk()
    root.title("Arduino Interface")

    # Crear el lienzo
    canvas = tk.Canvas(root, width=width, height=height, bg='black')
    canvas.pack()

    # Dibujar la caja
    box = canvas.create_rectangle(box_x - box_size, box_y - box_size, box_x + box_size, box_y + box_size,
                                  outline='gray', fill='gray')

    # Detectar movimiento del ratón
    canvas.bind('<Motion>', check_mouse_position)

    # Iniciar el bucle principal de Tkinter
    root.mainloop()

    # Cerrar el puerto serial al finalizar
    port.close()


if __name__ == "__main__":
    main()
