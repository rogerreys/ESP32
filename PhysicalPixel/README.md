# PhysicalPixel
# Arduino Interface
Este proyecto consiste en una interfaz gráfica desarrollada en Python que interactúa con un dispositivo Arduino. La interfaz permite encender y apagar un LED conectado al Arduino al mover el ratón dentro de una ventana gráfica.

## Requisitos

### Software
- Python 3.x
- Biblioteca `pyserial` de Python
- Biblioteca `tkinter` de Python (incluida en la instalación estándar de Python)
- Arduino IDE

## Instalación

### Python

1. Instalar las dependencias necesarias:
    ```sh
    pip install pyserial
    ```

2. Guardar el siguiente código Python en un archivo llamado `main.py`:


## Ejecución

1. Conectar el Arduino al puerto USB del ordenador.
2. Ejecutar el programa Python:
    ```sh
    python main.py
    ```

3. Mover el ratón dentro de la ventana gráfica. Cuando el cursor esté sobre la caja, el LED del Arduino se encenderá; de lo contrario, el LED se apagará.