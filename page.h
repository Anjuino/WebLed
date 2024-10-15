const char mypage[] PROGMEM = R"=====(
<!DOCTYPE html>
 <head>
    <meta charset="utf-8">
    <title>Led</title>
    <link rel='stylesheet' href='styles.css'>
 </head>

 <body onload="onload()">
    <div class="container">
       <div class="wrapper">
          <p> Выбрать обычный цвет</p>
          <input type="color" id = "hex" value="#FF0000">
          <button type="button" onclick="SetMode()"> Включить</button>
          <hr>
          <br>
          <p> Выбрать эффект</p>

          <select id="Numeffect" onchange="ChangeEffect()">
            <option value="1">Радуга</option>
            <option value="2">Бегущий огонь</option>
            <option value="3">Бегущие огни</option>
            <option value="4">Одиночные огни (случайные)</option>
            <option value="5">Вспышки</option>
            <option value="6">Смена цветов</option>
            <option value="7">Бегущий огонь 2</option>
            <option value="8">Хаос</option>
            <option value="9">2 бегущих огня</option>
          </select>

          <div class="container1"></div>

          <button type="button" onclick="Seteffect()">Задать эффект</button>

          <hr>
          <br>
          <p> Cкорость эффекта</p>

          <input id="Speed" type="range" min="1" max="20" step="1" onchange = "SetSpeed()">
          <hr>
          <br>

          <p> Яркость ленты</p>

          <input name="flevel" id="flying" type="range" min="1" max="100" step="1" onchange = "SetBlind()">
          <hr>
          <br>
          <button type="button" onclick="LedOff()">  Выключить ленту</button>
          <hr>
          <br>
          <button type="button" onclick="document.location='page.html'"> Настройки</button>
    </div>
  </div>   
</body>

<script>

function onload () {
   GetBlind();
   GetSpeed();
}

function ChangeEffect() 
{
  var i = Numeffect.value;
  if ((Numeffect.value == 2 || Numeffect.value == 7)) {
    const container = document.querySelector('.container1');
    if (container.innerHTML == "") {
      var inputt = document.createElement("p");
      inputt.textContent = 'Выбрать цвет эффекта';
      var input = document.createElement("input");
      input.setAttribute("type", "color");
      input.setAttribute("id", "hex1"); 
      input.setAttribute("value", "#FF0000");
      container.append(inputt);
      container.append(input);
    }
  }
  else {
    const container = document.querySelector('.container1');
    container.innerHTML = "";
  }
} 

function Seteffect() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
    }
  };
  var hex1 = document.getElementById("hex1");
  if (hex1) {
    var colorValue = document.getElementById("hex1").value;
    let [r,g,b] = hexToRgb (colorValue);
    xhttp.open("GET", "effects?Effects=" + Numeffect.value + "&R=" + r + "&G=" + g + "&B=" + b, true);
  } 
  else {
    xhttp.open("GET", "effects?Effects=" + Numeffect.value, true);
  }
  xhttp.send();
}

function SetMode() 
{
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
    }
  };
  var colorValue = document.getElementById("hex").value;
  let [r,g,b] = hexToRgb (colorValue);
  console.log(r);
  console.log(g);
  console.log(b);
  xhttp.open("GET", "mode?R=" + r + "&G=" + g + "&B=" + b, true);
  xhttp.send();
}

function hexToRgb(hex) 
{
  hex = hex.replace("#", "");

  var r = parseInt(hex.substring(0, 2), 16);
  var g = parseInt(hex.substring(2, 4), 16);
  var b = parseInt(hex.substring(4, 6), 16);   
  return [r, g, b];
}

function LedOff() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
    }
  };
  xhttp.open("GET", "ledoff?Mode=" + 250, true);
  xhttp.send();
}

function GetBlind() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      var State = this.responseText;
      document.getElementById("flying").value = State;
    }
  };
  xhttp.open("GET", "getBlind" , true);
  xhttp.send();
}

function GetSpeed() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      var State = this.responseText;
      document.getElementById("Speed").value = State;
    }
  };
  xhttp.open("GET", "getSpeed" , true);
  xhttp.send();
}

function SetBlind() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
    }
  };
  xhttp.open("GET", "blind?Blind=" + document.getElementById("flying").value, true);
  xhttp.send();
}

function SetSpeed() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
    }
  };
  xhttp.open("GET", "speed?Speed=" + document.getElementById("Speed").value, true);
  xhttp.send();
  }
</script>
)=====";