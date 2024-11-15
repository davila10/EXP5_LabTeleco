# SUBSCRIBER
# Queda en un while eterno escuchando mensajes. 

HOST = "broker.emqx.io" # HOST
PORT = 1883 # PUERTO
topic = "lab/sensor"  # TÓPICO de subscripción

import paho.mqtt.subscribe as subscribe

while True: # TODO: de momento, solo se puede salir cerrando el terminal...

    msg = subscribe.simple(topic, hostname=HOST, port=PORT)
    print("%s %s" % (msg.topic, msg.payload))

    # Definir el string dado
    data = msg.payload

    # Convertir el string a un diccionario JSON
    import json
    decoded_data = json.loads(data.decode('utf-8'))

    # Extraer los valores
    grupo = decoded_data["sender"].split()[-1]  # Obtiene "X" de "GRUPO X"
    fecha, hora = decoded_data["date"].split(" - ")
    temperatura = decoded_data["temp"]
    humedad = decoded_data["hum"]

    # Crear el nuevo formato
    formatted_data = f"Grupo: {grupo}, Fecha-Hora: {fecha}, Temperatura: {temperatura} ◦C, Humedad: {humedad} %"

    # Escribir a un archivo .txt

    with open("data.txt", "w",encoding="utf-8") as file:
        file.write(formatted_data)