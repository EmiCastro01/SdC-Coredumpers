import requests
from msl.loadlib import Client64


class MiCliente(Client64):
    def __init__(self):
        super(MiCliente, self).__init__(module32="capa_ssup")

    def pedir_gini(self, valor):
        return self.request32("get_gini", valor)


def main():
    a_gini = input()

    url = f"https://api.worldbank.org/v2/en/country/AR/indicator/SI.POV.GINI?format=json&date={a_gini}&per_page=1"
    res = requests.get(url)
    data = res.json()

    if len(data) <= 1 or data[1] is None or len(data[1]) == 0:
        print("No hay info de este año")
        return

    indice = data[1][0].get("value")
    print("EL indice obtenido por Python es: ", indice)

    if indice is None:
        print("No hay info de este año")
        return

    cliente = MiCliente()
    resultado = cliente.pedir_gini(float(indice))
    print(f"El índice desde ASM es: {resultado}")


if __name__ == "__main__":
    main()
