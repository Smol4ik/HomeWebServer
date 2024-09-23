from flask import Flask, jsonify, request
from flask_cors import CORS, cross_origin
from flask_socketio import SocketIO, emit

app = Flask(__name__)
CORS(app)
# socket = SocketIO(app)

dataLed = {"state": "off"}
dataTempHum = {
    "temperature": None,
    "humidity": None
}

# @socket.on('connect')
# def test_connect():
#     emit('connect-msg', {'data': 'Connected'})
#     print("Connected")
#
# @socket.on('disconnect')
# def test_disconnect():
#     print('Client disconnected')

@app.get("/get/data/led")
def get_led_state():
    try:
        return jsonify(dataLed), 200
    except:
        return "No LED data found", 404

@app.get("/get/data/temperature/humidity")
def get_temp_hum():
    try:
        return jsonify(dataTempHum), 200
    except:
        return "No temperature or humidity data found", 404

@app.post("/post/data/led")
def post_led_state():
    state_led = request.json
    dataLed["state"] = state_led["state"]
    return dataLed, 201

@app.post("/post/temperature/humidity")
def post_temp_hum_data():
    data_temp_hum = request.json
    dataTempHum["temperature"] = data_temp_hum["temperature"]
    dataTempHum["humidity"] = data_temp_hum["humidity"]
    print(dataTempHum)
    return dataTempHum, 201

# @app.post("/post/data")
# def post_function():
#     data_info = request.json
#     new_id = max(fakeDatabase.keys()) + 1
#     fakeDatabase[new_id] = {
#         "name": data_info['name']
#     }
#     return fakeDatabase, 201
#
# @app.delete("/delete_user<id>")
# def del_function(id):
#     try:
#         del fakeDatabase[int(id)]
#         return fakeDatabase, 204
#     except KeyError:
#         return f"Id not found", 404
#
# @app.put("/put/data<id>")
# def put_function(id):
#     put_data_info = request.json
#     fakeDatabase[int(id)] = {"name": put_data_info['name']}
#     return fakeDatabase
if __name__ == "__main__":
    app.run(host='0.0.0.0', port=5555, debug=True)

