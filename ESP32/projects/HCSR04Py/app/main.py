import requests
import time
import pyautogui


def fetch_distance(api_url):
    try:
        response = requests.get(api_url)
        if response.status_code == 200:
            data = response.json()  # Suponiendo que la respuesta es JSON
            return data.get("distance", None)
    except requests.RequestException as e:
        print(f"Error al leer la API: {e}")
        return None


def main():
    api_url = "http://esp32.local/api"
    while True:
        distance = fetch_distance(api_url)
        if distance is not None:
            if distance < 20:
                # pyautogui.hotkey('ctrl', 'd')
                pyautogui.hotkey('win', 'd')
                time.sleep(10)
        else:
            print("No se pudo obtener la distancia.")

        # time.sleep(2)


if __name__ == "__main__":
    print("Inicio")
    main()
