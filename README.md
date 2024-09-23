# HomeWebServer
This is my pet project in which I created a REST API web server in Flask and JavaScript to remotely control ESP boards via a web page. The Esp32 is connected to the server and it switches the LED on or off depending on which button is pressed on the page. The ESP8266 uses a temperature and humidity sensor to collect data and send it to the server. Initially, the board sends data 4 times every 15 seconds after startup, and then a POST request is made only when the temperature changes by 0.5 degrees or the humidity by 8%.

<img width="1440" alt="img" src="https://github.com/user-attachments/assets/874d7368-4a9b-4e71-91a6-c40b95ff3c46">
