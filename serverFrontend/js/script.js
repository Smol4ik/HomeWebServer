const btnLedOn = document.getElementById('on-led')
const btnLedOff = document.getElementById('off-led')
const temperaturaValue = document.getElementById('temperatura-id')
const humidityValue = document.getElementById('humidity-id')
//const socket = io("http://127.0.0.1:5555")
/*
socket.on("connect", () => {
    console.log("Connect to server")
})

socket.on("connect-msg", (msg) => {
    console.log("Data from server:", msg)
})

socket.on("disconnect", () => {
    console.log("Disconnected from server")
})*/

function ledState(state) {
    fetch("http://127.0.0.1:5555/post/data/led", {
        headers: {
            "Content-Type": "application/json",
          },
        method: "POST",
        body:JSON.stringify({"state": state})
    })
}
function tempHumData() {
    fetch("http://127.0.0.1:5555/get/data/temperature/humidity")
    .then((res) => {
        if(!res.ok) {
            throw new Error(`HTTP err ${res.status}`)
        }
        return res.json()
    })
    .then((data) => {
        if("temperature" in data) {
            if(data["temperature"] == null) {
                temperaturaValue.innerText = ""
            }
            else {
                temperaturaValue.innerText = `${data["temperature"]} °C`
            }    
        }
        if("humidity" in data) {
            if(data["humidity"] == null) {
                humidityValue.innerText = ""
            }
            else {
                humidityValue.innerText = `${data["humidity"]} %`
            }
        }
    })
    .catch((err) => {
        if(err instanceof TypeError) {
            console.log("Server is down")
        }
        else {
            console.log(err)
        }
        
    })
}

btnLedOn.addEventListener('click', () => ledState("on"))
btnLedOff.addEventListener('click', () => ledState("off"))

setInterval(tempHumData, 5000)

/*btnGet.addEventListener('click', function(){
    fetch("http://127.0.0.1:5555/get_user")
    .then((res) => {
        if(!res.ok){
            throw new Error(`HTTP err ${res.status}`)
        }
        return res.json()
    } )
    .then((data) => {
        console.log(data)
        for(let key in data) {
            if('name' in data[key]) {
                let pTg = document.createElement('p')
                pTg.textContent = data[key].name
                mainDiv.appendChild(pTg)
            }
        }
    })
    .catch((error) => {
        console.log(error)
    })
})

btnPost.addEventListener('click', function(){
    fetch("http://127.0.0.1:5555/post/data", {
        headers: {
            "Content-Type": "application/json",
          },
        method: "POST",
        body: JSON.stringify({"name": areaForData.value})
    })
    .then(() => areaForData.value = "")
    //console.log(typeof(areaForData.value))
})
btnDelete.addEventListener('click', function(){
    const userId = areaForId.value
    fetch(`http://127.0.0.1:5555/delete_user${userId}`, {
        headers: {
            "Content-Type": "application/json",
          },
        method: "DELETE"
    })
})
btnPut.addEventListener('click', function() {
    const userId = areaForId.value
    const userData = areaForData.value
    fetch(`http://127.0.0.1:5555/put/data${userId}`, { 
        headers: {
            "Content-Type": "application/json",
          },
        method: "PUT",
        body: JSON.stringify({"name": userData})
    })
})*/