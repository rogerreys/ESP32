import serial


def main(count=None):
    # Inicializar la conexión serial (ajusta el puerto según sea necesario)

    port = serial.Serial('COM4', 9600)

    print("Listening for button presses...")

    while True:
        if port.in_waiting > 0:  # Si hay datos disponibles para leer
            line = port.readline().decode('utf-8').strip()  # Leer la línea
            if line == "btn: on":
                count += 1
                print(f"Hello World {count}")


if __name__ == "__main__":
    main(0)
