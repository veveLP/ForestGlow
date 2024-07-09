const char index_html[] PROGMEM = R"rawliteral(

<!DOCTYPE HTML>
<html>
<head>
    <title>Forest Glow</title>
    <meta name="viewport" content="width=device-width, initial-scale=1" charset="utf-8">
    <link rel="icon" href="data:,">
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }

        body {
            background-color: #303030;
            min-width: 100dvw;
            min-height: 100dvh;
            padding: 50px;
            color: whitesmoke;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
        }

        h3 {
            font-size: 1.5em;
            width: fit-content;
        }

        h3::after {
            display: block;
            content: " ";
            height: 1px;
            background-color: #504f4f;
            margin-top: 10px;
            margin-bottom: -5px;
        }

        #wrapper {
            max-width: 1320px;
            margin: 0 auto;
            display: grid;
            justify-content: space-between;
            grid-gap: 30px;
            grid-template-columns: repeat(auto-fit, minmax(400px, 1fr));
        }

        .card-container {
            display: flex;
            flex-direction: column;
            gap: 20px;
        }

        .card {
            padding: 20px;
            border-radius: 5px;
            background-color: #2a2a2a;
            display: flex;
            flex-direction: column;
            gap: 15px;
            height: 100%%;
            justify-content: space-between;
        }

        .input-label {
            display: flex;
            flex-direction: column;
            font-size: 1.1em;
        }

        .input-label input[type="text"] {
            height: 36px;
            border-radius: 5px;
            border: 1px solid #686868;
            background-color: #3B3B3B;
            margin-top: 5px;
            padding: 0 5px;
            color: whitesmoke;
            font-size: 1em;
        }

        .input-label input[type="text"]:disabled {
            height: 36px;
            border-radius: 5px;
            border: 1px solid #1d1d1d;
            background-color: #161616;
            margin-top: 5px;
            padding: 0 5px;
            color: whitesmoke;
            font-size: 1em;
        }

        .submit-button {
            height: 44px;
            border-radius: 5px;
            border: none;
            background-color: #004600;
            margin-top: 5px;
            color: whitesmoke;
            font-size: 1em;
            transition: .3s;
            cursor: pointer;
        }


        .submit-button:hover {
            transition: .3s;
            background-color: #004d00;

        }

        .input-label-rad {
            display: flex;
            flex-direction: row-reverse;
            justify-content: start;
            gap: 5px;
            font-size: 1.1em;
            position: relative;
            padding-left: 40px;
            cursor: pointer;
        }

        .input-label-rad input {
            position: absolute;
            opacity: 0;
            cursor: pointer;
        }

        .better-radio {
            position: absolute;
            top: 0;
            left: 0;
            height: 25px;
            width: 25px;
            background-color: #004d00;
            border-radius: 50%%;
        }

        .input-label-rad:hover input~.better-radio {
            background-color: #004d00;
        }

        .input-label-rad input:checked~.better-radio {
            background-color: #004d00;
        }

        .better-radio:after {
            content: "";
            position: absolute;
            display: none;
        }

        .input-label-rad input:checked~.better-radio:after {
            display: block;
        }

        .input-label-rad .better-radio:after {
            top: 5px;
            left: 5px;
            width: 15px;
            height: 15px;
            border-radius: 50%%;
            background: white;
        }

        .change-mode-group {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(100px, 1fr));
            gap: 10px;
            justify-self: flex-start;
        }

        .mode-switch {
            height: 50px;
            padding: 0 10px;
        }


        .mode-switch.active {
            background-color: #009b00;
        }

        .slider {
            -webkit-appearance: none;
            appearance: none;
            width: 100%%;
            height: 20px;
            border-radius: 10px;
            background: #d3d3d3;
            outline: none;
            opacity: 0.7;
            -webkit-transition: .2s;
            transition: opacity .2s;
        }

        .slider:hover {
            opacity: 1;
        }

        .slider::-webkit-slider-thumb {
            -webkit-appearance: none;
            appearance: none;
            width: 20px;
            height: 20px;
            background: #004d00;
            cursor: pointer;
            border-radius: 10px;
        }

        .slider::-moz-range-thumb {
            width: 20px;
            height: 20px;
            background: #004d00;
            cursor: pointer;
            border-radius: 10px;

        }

        input[type="color"] {
            height: 34px;

        }

        .duo-group {
            display: flex;
            width: 100%%;
            gap: 10px;
            height: 50px;
        }

        .duo-group label {
            width: 100%%;
        }

        input[type="time"] {
            height: 36px;
            border-radius: 5px;
            border: 1px solid #686868;
            background-color: #3B3B3B;
            margin-top: 5px;
            padding: 0 5px;
            color: whitesmoke;
            font-size: 1em;
        }

        .setting-group {
            display: flex;
            flex-direction: column;
            width: 100%;
            flex-grow: 1;
            gap: 15px;

        }

        .input-label-check {
            display: flex;
            flex-direction: row-reverse;
            justify-content: start;
            font-size: 1.1em;
            position: relative;
            padding-left: 40px;
            cursor: pointer;
        }

        .input-label-check input {
            position: absolute;
            opacity: 0;
            cursor: pointer;
            height: 0;
            width: 0;
        }

        .checkmark {
            position: absolute;
            top: 0;
            left: 0;
            height: 25px;
            width: 25px;
            border-radius: 5px;
            background-color: #004d00;
        }

        .input-label-check:hover input~.checkmark {
            background-color: #004d00;
        }

        .input-label-check input:checked~.checkmark {
            background-color: #004d00;
        }

        .checkmark:after {
            content: "";
            position: absolute;
            display: none;
        }

        .input-label-check input:checked~.checkmark:after {
            display: block;
        }

        .input-label-check .checkmark:after {
            left: 9px;
            top: 5px;
            width: 5px;
            height: 10px;
            border: solid white;
            border-width: 0 3px 3px 0;
            -webkit-transform: rotate(45deg);
            -ms-transform: rotate(45deg);
            transform: rotate(45deg);
        }

        @media screen and (max-width: 600px) {
            body {
                padding: 0;
            }

            #wrapper {
                max-width: 95%%;
                margin: 0 auto;
                display: flex;
                justify-content: space-between;
                gap: 30px;
                flex-direction: column;
            }
        }
    </style>
</head>

<body>
    <div id="wrapper">
        <div class="card-container">
            <form name="wifi-network-setting" class="card" onsubmit="handleWifiNetworkSettingSubmit(); return false">
                <h3>Nastavení Wi-Fi sítě</h3>
                <label class="input-label">
                    Název sítě:
                    <input name="wifi-name" type="text">
                </label>
                <label class="input-label">
                    Heslo:
                    <input name="wifi-password" type="text">
                </label>
                <input class="submit-button" type="submit" value="Uložit">
            </form>
        </div>

        <div class="card-container">
            <form name="wifi-setting" class="card" onsubmit="handleWifiSettingSubmit(); return false">
                <h3>Nastavení Wi-Fi</h3>
                <label class="input-label-rad">
                    Existující WiFi síť
                    <input value="1" name="wifi-setting" type="radio">
                    <span class="better-radio"></span>
                </label>
                <label class="input-label-rad">
                    Vlastní WiFi síť lampičky
                    <input value="0" name="wifi-setting" type="radio">
                    <span class="better-radio"></span>
                </label>
                <input class="submit-button" type="submit" value="Uložit">
            </form>
        </div>

        <div class="card-container">
            <form name="api-setting" class="card" onsubmit="handleApiSettingSubmit(); return false">
                <h3>Nastavení API</h3>
                <label class="input-label-rad">
                    Forestcraft
                    <input value="0" onchange="handleApiRadioChange()" name="api-setting" type="radio">
                    <span class="better-radio"></span>
                </label>
                <label class="input-label-rad">
                    Vlastní websocket
                    <input value="1" onchange="handleApiRadioChange()" name="api-setting" type="radio">
                    <span class="better-radio"></span>
                </label>
                <label class="input-label-rad">
                    MQTT
                    <input value="2" onchange="handleApiRadioChange()" name="api-setting" type="radio">
                    <span class="better-radio"></span>
                </label>
                <label class="input-label">
                    Název sítě:
                    <input id="api-setting-input" name="api-setting-input" disabled type="text">
                </label>
                <input class="submit-button" type="submit" value="Uložit">
            </form>
        </div>

        <div class="card-container">
            <form onsubmit="handleModeSubmit(); return false" name="mode-setting" class="card">
                <h3>Nastavení módu</h3>
                <div id="change-mode-group" class="change-mode-group">
                    <button name="mode-button" id="off-mode" onclick="handleModeButtonChange(this)"
                        class="submit-button mode-switch" value="0" type="button">OFF</button>
                    <button name="mode-button" id="api-mode" onclick="handleModeButtonChange(this)"
                        class="submit-button mode-switch" value="1" type="button">API</button>
                    <button name="mode-button" id="white-mode" onclick="handleModeButtonChange(this)"
                        class="submit-button mode-switch" value="2" type="button">White</button>
                    <button name="mode-button" id="rgb-mode" onclick="handleModeButtonChange(this)"
                        class="submit-button mode-switch" value="3" type="button">RGB</button>
                    <button name="mode-button" id="rainbow-mode" onclick="handleModeButtonChange(this)"
                        class="submit-button mode-switch" value="4" type="button">Rainbow</button>
                    <button name="mode-button" id="ambient-mode" onclick="handleModeButtonChange(this)"
                        class="submit-button mode-switch" value="5" type="button">Ambient</button>
                    <button name="mode-button" id="gradient-mode" onclick="handleModeButtonChange(this)"
                        class="submit-button mode-switch" value="6" type="button">Gradient</button>
                </div>
                <div class="duo-group">
                    <label style="display: none;" id="speed-input" class="input-label">
                        <span id="speed-information">Rychlost: </span>
                        <input id="speed-input-input" class="slider" name="speed-setting" onchange="handleSpeedChange()"
                            type="range" min="1" max="255">
                    </label>
                    <label style="display: none;" class="input-label" id="color1-input">
                        <span id="color1-information">Barva: </span>
                        <input id="color1-input-input" class="slider" name="color1-setting" type="color">

                    </label>

                    <label style="display: none;" class="input-label" id="color2-input">
                        <span id="color2-information">Barva: </span>
                        <input id="color2-input-input" class="slider" name="color2-setting" type="color">

                    </label>
                </div>
                <input class="submit-button" type="submit" value="Uložit">
            </form>
        </div>

        <div class="card-container">
            <form onsubmit="handleBrightnessSubmit(); return false" name="brightness-setting" class="card">
                <h3>Nastavení jasu</h3>
                <div id="brightness-mode-group" class="change-mode-group">
                    <button name="brightness-button" id="sunset-mode" onclick="handleBrightnessButtonChange(this)"
                        class="submit-button mode-switch" value="0" type="button">Západ slunce</button>
                    <button name="brightness-button" id="owntime-mode" onclick="handleBrightnessButtonChange(this)"
                        class="submit-button mode-switch" value="1" type="button">Vlastní čas</button>
                    <button name="brightness-button" id="sensor-mode" onclick="handleBrightnessButtonChange(this)"
                        class="submit-button mode-switch" value="2" type="button">Senzoru jasu</button>
                    <button name="brightness-button" id="manual-mode" onclick="handleBrightnessButtonChange(this)"
                        class="submit-button mode-switch" value="3" type="button">Manuální Nastavení</button>
                </div>
                <div class="duo-group">
                    <label style="display: none;" id="brightness-input" class="input-label">
                        <span id="brightness-information">Rychlost: </span>
                        <input id="brightness-input-input" class="slider" name="brightness-setting"
                            onchange="handleBrightnessManualChange()" type="range" min="1" max="255">
                    </label>
                    <label style="display: none;" id="start-time-input" class="input-label">
                        <span id="start-time-information">Čas ztlumení: </span>
                        <input id="start-time-input-input" class="slider" name="start-time-setting" type="time">
                    </label>
                    <label style="display: none;" id="end-time-input" class="input-label">
                        <span id="end-time-information">Čas zatmění: </span>
                        <input id="end-time-input-input" class="slider" name="end-time-setting" type="time">
                    </label>
                </div>
                <input class="submit-button" type="submit" value="Uložit">
            </form>
        </div>

        <div class="card-container">
            <form onsubmit="handleOtherSettingSubmit(); return false" name="other-setting" class="card">
                <h3>Ostatní nastavení</h3>
                <div class="setting-group">
                    <label class="input-label-check">
                        Pípák
                        <input name="beep-setting" type="checkbox" onclick='handleClickBeep();'>
                        <span class="checkmark"></span>

                    </label>
                    <label class="input-label-check">
                        Dotykové tlačítko
                        <input name="touch-setting" type="checkbox" onclick='handleClickButton();'>
                        <span class="checkmark"></span>
                    </label>
                    <label class="input-label-check">
                        Přijmat data mimo API mód
                        <input name="override-setting" type="checkbox" onclick='handleClickOverride();'>
                        <span class="checkmark"></span>
                    </label>
                </div>
                <input class="submit-button" type="submit" value="Restartovat">
            </form>
        </div>
    </div>

    <script>
        let brightnessMode = 0;
        let modeMode = 6;
        let wifiMode = 0;
        let apiSetting = 0;
        let checkedBeep = true;
        let checkedTouch = false;
        let speedRainbow = 150;
        let speedAmbient = 50;
        let colorRgb = "#7FFFD4";
        let colorGrad1 = "#F5F5DC";
        let colorGrad2 = "#7FFF00";
        let timeFrom = "00:00";
        let timeTo = "23:59";
        let manualSpeed = 30;
        let brightness = 100;


        var gateway = `ws://${window.location.hostname}:80/ws`; //this is for production
        //var gateway = `ws://10.202.168.169:8080/ws`; //if you see this than I forgot to remove it :)
        var websocket;
        function initWebSocket() {
        console.log('Trying to open a WebSocket connection...');
        websocket = new WebSocket(gateway);
        websocket.onopen    = onOpen;
        websocket.onclose   = onClose;
        websocket.onmessage = onMessage;
        }

        function onOpen(event) {
            console.log('Connection opened');
        }

        function onClose(event) {
            console.log('Connection closed');
            setTimeout(initWebSocket, 2000);
        }

        function onMessage(event) {
            let str = event.data;
            console.log(str)
            if(str.startsWith("alert:")) {
                str = str.replace("alert:","");
                alert(str);
                return;
            }
            if(!str.startsWith("init:")) {return;}
            str = str.replace("init:","");
            var arrayOfValues = str.split(',');

            document.forms["wifi-network-setting"]["wifi-name"].value = arrayOfValues[0]
            document.forms["wifi-network-setting"]["wifi-password"].value = arrayOfValues[1]
            modeMode = Number(arrayOfValues[2])
            brightnessMode = Number(arrayOfValues[3])
            colorRgb = rgbToHex(Number(arrayOfValues[4]),Number(arrayOfValues[5]),Number(arrayOfValues[6]))
            speedRainbow = Number(arrayOfValues[7])
            speedAmbient = Number(arrayOfValues[8])
            brightness = Number(arrayOfValues[9])
            timeFrom = formatTime(arrayOfValues[10])
            timeTo = formatTime(arrayOfValues[11])
            document.forms["api-setting"]["api-setting-input"].value = arrayOfValues[12]
            checkedBeep = Number(arrayOfValues[13])
            apiSetting = Number(arrayOfValues[14])
            checkedTouch = Number(arrayOfValues[15])
            colorGrad1 = rgbToHex(Number(arrayOfValues[16]),Number(arrayOfValues[17]),Number(arrayOfValues[18]))
            colorGrad2 = rgbToHex(Number(arrayOfValues[19]),Number(arrayOfValues[20]),Number(arrayOfValues[21]))
            wifiMode = Number(arrayOfValues[22])
            document.forms["other-setting"]["touch-wifi-setting"].checked = Number(arrayOfValues[23])
            document.forms["other-setting"]["override-setting"].checked = Number(arrayOfValues[24])

            init()
        }

        function init() {

            let brigthnessButtons = document.getElementById("brightness-mode-group").children;
            for (let button of brigthnessButtons) {
                if (button.value == brightnessMode) {
                    handleBrightnessButtonChange(button);
                }
            }

            let list = document.getElementById("change-mode-group").children;
            for (let item of list) {
                if (item.value == modeMode) {
                    handleModeButtonChange(item);
                }
            }

            document.forms["wifi-setting"]["wifi-setting"].value = wifiMode;
            document.forms["api-setting"]["api-setting"].value = apiSetting;
            let elem = document.forms["api-setting"]["api-setting-input"];

            if (parseInt(apiSetting) >= 1) {
                elem.disabled = false;
            } else {
                elem.disabled = true;
            }

            document.forms["other-setting"]["beep-setting"].checked = checkedBeep;
            document.forms["other-setting"]["touch-setting"].checked = checkedTouch;

            document.forms["brightness-setting"]["start-time-setting"].value = timeFrom;
            document.forms["brightness-setting"]["end-time-setting"].value = timeTo;
            document.forms["brightness-setting"]["brightness-input-input"].value = brightness;
        }

        init();
        initWebSocket();

        function formatTime(timeString) {

        const [hours, minutes] = timeString.split(':');


        const formattedHours = hours.padStart(2, '0');
        const formattedMinutes = minutes.padStart(2, '0');


        return `${formattedHours}:${formattedMinutes}`;
}

        function handleApiRadioChange() {
            let x = document.forms["api-setting"]["api-setting"].value;
            let elem = document.forms["api-setting"]["api-setting-input"];

            if (parseInt(x) >= 1) {
                elem.disabled = false;
            } else {
                elem.disabled = true;
            }
        }

        function handleModeButtonChange(e) {
            const modes = ["off", "api", "white", "rgb", "rainbow", "ambient", "gradient"]
            console.log(e)

            modes.forEach((mode) => {
                document.getElementById(`${mode}-mode`).classList.remove("active")
            })

            document.getElementById(e.id).classList.add("active")
            document.getElementById("speed-input").style.display = "none"
            document.getElementById("color2-input").style.display = "none"
            document.getElementById("color1-input").style.display = "none"

            if (e.id === "rgb-mode") {
                document.getElementById("color1-input").style.display = "flex"
                document.getElementById("color1-input-input").value = colorRgb
                document.getElementById("color1-information").innerText = "Barva:"

            }

            if (e.id === "rainbow-mode") {
                document.getElementById("speed-input").style.display = "flex"
                document.getElementById("speed-input-input").value = speedRainbow
                document.getElementById("speed-information").innerHTML = `Rychlost: ${Math.floor((100 / 255) * speedRainbow)}%%`

            }

            if (e.id === "ambient-mode") {
                document.getElementById("speed-input").style.display = "flex"
                document.getElementById("speed-input-input").value = speedAmbient
                document.getElementById("speed-information").innerHTML = `Rychlost: ${Math.floor((100 / 255) * speedAmbient)}%%`

            }

            if (e.id === "gradient-mode") {
                document.getElementById("color1-input").style.display = "flex"
                document.getElementById("color2-input").style.display = "flex"
                document.getElementById("color1-input-input").value = colorGrad1

                document.getElementById("color2-input-input").value = colorGrad2

                document.getElementById("color1-information").innerText = "Barva 1:"
                document.getElementById("color2-information").innerText = "Barva 2:"

            }



        }

        function handleBrightnessButtonChange(e) {
            const modes = ["sunset", "owntime", "sensor", "manual"]

            modes.forEach((mode) => {
                document.getElementById(`${mode}-mode`).classList.remove("active")
            })

            document.getElementById(e.id).classList.add("active")

            document.getElementById("brightness-input").style.display = "none"
            document.getElementById("end-time-input").style.display = "none"
            document.getElementById("start-time-input").style.display = "none"

            if (e.id === "owntime-mode") {
                document.getElementById("end-time-input").style.display = "flex"
                document.getElementById("start-time-input").style.display = "flex"
                document.getElementById("start-time-input-input").value = timeFrom
                document.getElementById("end-time-input-input").value = timeTo
            }

            if (e.id === "manual-mode") {
                document.getElementById("brightness-input").style.display = "flex"
                document.getElementById("brightness-input-input").value = brightness
                document.getElementById("brightness-information").innerText = `Jas: ${Math.floor((100 / 255) * brightness)}%%`
            }
        }


        function handleSpeedChange(e) {
            let x = document.forms["mode-setting"]["speed-setting"].value;
            document.getElementById(`speed-information`).innerText = `Rychlost: ${Math.floor((100 / 255) * x)}%%`

        }

        function handleBrightnessManualChange(e) {
            let x = document.forms["brightness-setting"]["brightness-setting"].value;
            document.getElementById(`brightness-information`).innerText = `Jas: ${Math.floor((100 / 255) * x)}%%`
        }



        function hexToRgb(hex) {
            let r = 0, g = 0, b = 0;

            if (hex.length == 4) {
                r = "0x" + hex[1] + hex[1];
                g = "0x" + hex[2] + hex[2];
                b = "0x" + hex[3] + hex[3];

            } else if (hex.length == 7) {
                r = "0x" + hex[1] + hex[2];
                g = "0x" + hex[3] + hex[4];
                b = "0x" + hex[5] + hex[6];
            }

            return "" + +r + "," + +g + "," + +b + "";
        }


        function rgbToHex(r, g, b) {
            r = Math.max(0, Math.min(255, r));
            g = Math.max(0, Math.min(255, g));
            b = Math.max(0, Math.min(255, b));

            return "#" + ((r << 16) | (g << 8) | b).toString(16).padStart(6, '0');
        }


        function handleWifiNetworkSettingSubmit() {
            let wifiName = document.forms["wifi-network-setting"]["wifi-name"].value;
            let wifiPassword = document.forms["wifi-network-setting"]["wifi-password"].value;
            websocket.send("wifi:"+wifiName+","+wifiPassword);
        }

        function handleWifiSettingSubmit() {
            let wifiMode = document.forms["wifi-setting"]["wifi-setting"].value;
             websocket.send("wifiMode:"+wifiMode);
        }

        function handleApiSettingSubmit() {
            let apiMode = document.forms["api-setting"]["api-setting"].value;
            let apiModeInput = document.forms["api-setting"]["api-setting-input"].value;
            websocket.send("apiSource:"+apiMode);
            setTimeout(() => {websocket.send("customURL:"+apiModeInput); }, 100);
        }

        function handleModeSubmit() {
            let buttonList = document.forms["mode-setting"]["mode-button"];
            let speed = document.forms["mode-setting"]["speed-setting"].value;
            let colorRGB = document.getElementById("color1-input-input").value;
            let color1 = document.forms["mode-setting"]["color1-setting"].value;
            let color2 = document.forms["mode-setting"]["color2-setting"].value;
            let mode = modeMode;

            for (let item of buttonList) {
                if (item.classList.contains("active")) {
                    mode = item.value;
                    let str = "mode:"+mode+"#";

                    if(mode == '3') {
                        str += hexToRgb(colorRGB);
                    }
                    if(mode == '4') {
                        str += "speed:"+speedRainbow;
                    }
                    if(mode == '5') {
                        str += "speed:"+speedAmbient
                    }
                    if(mode == '6') {
                        str += hexToRgb(colorGrad1);
                        str += ":"+hexToRgb(colorGrad2);
                    }
                    websocket.send(str);
                }
            }
        }


        function handleBrightnessSubmit() {
            let buttonList = document.forms["brightness-setting"]["brightness-button"];
            let brightness = document.forms["brightness-setting"]["brightness-setting"].value;
            let startTime = document.forms["brightness-setting"]["start-time-setting"].value;
            let endTime = document.forms["brightness-setting"]["end-time-setting"].value;
            let mode = brightnessMode;

            for (let item of buttonList) {
                if (item.classList.contains("active")) {
                    mode = item.value;
                    let str = "brightness:"+mode+":";
                    if(mode == '3') {
                       str += brightness
                    }
                    if(mode == '1') {
                       str += startTime+":"+endTime;
                    }
                    websocket.send(str);
                }
            }

        }


        function handleOtherSettingSubmit() {
            websocket.send("reset");
        }

        function handleClickBeep() {
            let beeper = document.forms["other-setting"]["beep-setting"].checked;
            websocket.send("beep:" + Number(beeper));
        }

        function handleClickButton() {
            let touchSensor = document.forms["other-setting"]["touch-setting"].checked;
            websocket.send("button:" + Number(touchSensor));
        }

        function handleClickOverride() {
            let touchSensor = document.forms["other-setting"]["override-setting"].checked;
            websocket.send("override:" + Number(touchSensor));
        }

    </script>
</body>

</html>

)rawliteral";
