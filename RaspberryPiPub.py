import paho.mqtt.client as mqtt
import time
print("Starting")
# Local MQTT Broker
broker = '127.0.0.1'  # Replace with broker's IP address
port = 1883

client = mqtt.Client()
client.connect(broker, port)

# The ESP32s when they setup will self identify using the FuseID - use this list to iterate through the windows
winNames = ['win0', 'win1', 'win2', 'win3', 'win4', 'win5', 'win6', 'win7', 'win8']

# This will send a color to the selected window - it is up to the ESP32 to do something with this color
# By changing the message the ESP32 can be triggered to do something different
def change_led_color(device_id, strip_id, r, g, b):
    color = f"{r},{g},{b}"
    topic = f"{device_id}/strip{strip_id}"
    client.publish(topic, color)
    print(topic, color)

# Example loop to alternate colors
while True:

    for i in range(9):

        # Set even colors to Red in the Panels and Green on the perimeters - odd numbers do the opposite
        # Then reverse the colors in the next pass

        if i % 2 == 0:

            change_led_color("win" + str(i), 1, 100, 0, 0)  # Set color to red
            change_led_color("win" + str(i), 2, 0, 100, 0)  # Set color to Green

        else:

            change_led_color("win" + str(i), 1, 0, 100, 0)  # Set color to Green
            change_led_color("win" + str(i), 2, 100, 0, 0)  # Set color to Red

        time.sleep(1)  # Wait for 1 seconds

    time.sleep(1)  # Wait for 1 seconds

    for i in range(9):

        if i % 2 == 0:

            change_led_color("win" + str(i), 2, 180, 0, 0)  # Set color to red
            change_led_color("win" + str(i), 1, 0, 180, 0)  # Set color to Green

        else:

            change_led_color("win" + str(i), 2, 0, 180, 0)  # Set color to Green
            change_led_color("win" + str(i), 1, 180, 0, 0)  # Set color to Red

        time.sleep(1)  # Wait for 1 seconds

    time.sleep(1)  # Wait for 1 seconds

