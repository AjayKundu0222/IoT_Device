#Simulation Steps:

# Setting Up the Simulation:
# For simplicity, we'll use Python to simulate the behavior of a Raspberry Pi.
import random
import time
import paho.mqtt.client as mqtt

# Simulate DHT11 Sensor Readings:
# Simulate temperature and humidity readings as if they were coming from a DHT11 sensor.
def simulate_sensor_readings():
    temperature = random.uniform(20, 30)
    humidity = random.uniform(40, 60)
    return temperature, humidity


# MQTT Callbacks:
# Define callback functions for MQTT events.
def on_connect(client, userdata, flags, rc):
    print("Connected to MQTT broker with result code " + str(rc))
    
def on_publish(client, userdata, mid):
    print("Message Published")


# MQTT Configuration:
# Set up MQTT parameters for communication.
mqtt_broker = "test.mosquitto.org"
mqtt_port = 1883
mqtt_topic = "environment/monitoring"

# MQTT Client Setup:
# Set up an MQTT client and connect to the broker.
mqtt_client = mqtt.Client()
mqtt_client.on_connect = on_connect
mqtt_client.on_publish = on_publish

mqtt_client.connect(mqtt_broker, mqtt_port, 60)
mqtt_client.loop_start()

# Simulate IoT Device Loop:
# Simulate a loop where the device reads sensor data and publishes it to the cloud platform using MQTT.
try:
    while True:
        temperature, humidity = simulate_sensor_readings()
        message = f"Temperature: {temperature:.2f}°C, Humidity: {humidity:.2f}%"
        mqtt_client.publish(mqtt_topic, message)
        print("Published:", message)
        time.sleep(5)  # Simulate reading every 5 seconds

except KeyboardInterrupt:
    mqtt_client.disconnect()
    print("Simulation terminated.")