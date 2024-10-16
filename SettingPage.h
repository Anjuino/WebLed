const char SettingPage[] PROGMEM = R"=====(

<!DOCTYPE html>
 <head>
    <meta charset="utf-8">
    <title>Led</title>
    <link rel='stylesheet' href='styles.css'>
 </head>

 <body onload="onload()">
    <div class="container">
       <div class="wrapper">
         <p>Расписание</p>
         <table>
         <tr>
            <td>Выкл:</td>
            <td><input type="time" id="timeoff" onchange = "Ledofftime()"></input></td>
            <td><input type="checkbox" onclick="Ledofftime()" id="ledoff"> </input></td>
         </tr>
         <tr>
            <td>Вкл:</td>
            <td><input type="time" id="timeon"  onchange = "Ledontime()"></input></td>
            <td><input type="checkbox" onclick="Ledontime()" id="ledon"> </input></td>
         </tr>
      </table>
         <hr>
          <p>Введите количество светодиодов</p>
          <input  type="text" maxlength="3" id="LedCount"> </input>
          <button type="button" onclick="SetCount()"> Задать</button>
          <hr>
          <br>
          <button type="button" onclick="ResetWifi()"> Сбросить Wifi настройки</button>
          <hr>
          <br>
          <button type="button" onclick="document.location='/'"> На главную</button>
          <br>
          <br>
          <br>
          <br>
    </div>
  </div>   
</body>

<script>

function onload () {
   GetStateOnOff("Off");
   GetTime("Off");
   
   GetStateOnOff("On");
   GetTime("On");
}

function SetCount() {
   var xhttp = new XMLHttpRequest();
   xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
      setTimeout(function(){
      window.location.href = '/';
      }, 5000);
      alert("Контроллер будет перезагружен. Нажмите ОК для перехода на панель управления.");
      }
   };
   var CountLed = document.getElementById("LedCount").value;

   if (CountLed > 500) CountLed = 500;
   if (CountLed < 0)   CountLed = 0;

   xhttp.open("GET", "setcount?CountLed=" + CountLed, true);
   xhttp.send();
}

function GetStateOnOff(In1) {
   var xhttp = new XMLHttpRequest();
   xhttp.onreadystatechange = function() {

   if (this.readyState == 4 && this.status == 200) {
      var State = this.responseText;
      if (In1 == "Off") {
        if (State == "true") document.getElementById("ledoff").checked = true;
        else                 document.getElementById("ledoff").checked = false;
      }

      if (In1 == "On") {
        if (State == "true") document.getElementById("ledon").checked = true;
        else                 document.getElementById("ledon").checked = false;
      } 
      }
   };
   if (In1 == "On")   xhttp.open("GET", "getState?On=1", true);
   if (In1 == "Off")  xhttp.open("GET", "getState?Off=2", true);
   xhttp.send();
}

function GetTime(In1) {
   var xhttp = new XMLHttpRequest();
   xhttp.onreadystatechange = function() {

   if (this.readyState == 4 && this.status == 200) {
      var time = this.responseText;
      let arr = time.split(":");
      var timeH = parseInt(arr[0]);
      var timeM = parseInt(arr[1]);

      if (timeH >= 0 && timeH <= 9) timeH = "0" + timeH;
      if (timeM >= 0 && timeM <= 9) timeM = "0" + timeM;

      var timeAll = timeH + ":" + timeM;

      if (In1 == "Off") document.getElementById("timeoff").value = timeAll;
      if (In1 == "On") document.getElementById("timeon").value = timeAll;
   
   }
   };
   if (In1 == "On") xhttp.open("GET", "getTime?On=1", true);
   if (In1 == "Off") xhttp.open("GET", "getTime?Off=2", true);
   xhttp.send();
}

function Ledofftime() {
   var xhttp = new XMLHttpRequest();
   xhttp.onreadystatechange = function() {
   if (this.readyState == 4 && this.status == 200) {
      var Resp = this.responseText;
      if (Resp == "OK")     alert("Расписание включено");
      if (Resp == "false")  alert("Расписание отключено");
   }
   };
   var time  = document.getElementById("timeoff").value.toString();
   var state = document.getElementById("ledoff").checked;

   console.log(time);

   if (state) {
      if (time) {
         xhttp.open("GET", "ledofftime?state=" + state + "&T=" + time, true);
         xhttp.send();
      }
      else {
         alert("Время не установлено");
         document.getElementById("ledoff").checked = false;
      }
   }
   else {
      xhttp.open("GET", "ledofftime?state=" + state + "&T=" + time, true);
      xhttp.send();
   }
}

function Ledontime() {
   var xhttp = new XMLHttpRequest();
   xhttp.onreadystatechange = function() {
   if (this.readyState == 4 && this.status == 200) {
      var Resp = this.responseText;
      if (Resp == "OK")     alert("Расписание включено");
      if (Resp == "false")  alert("Расписание отключено");

   }
   };
   var time  = document.getElementById("timeon").value.toString();
   var state = document.getElementById("ledon").checked;

   console.log(time);

   if (state) {
      if (time) {
         xhttp.open("GET", "ledontime?state=" + state + "&T=" + time, true);
         xhttp.send();
      }
      else {
         alert("Время не установлено");
         document.getElementById("ledon").checked = false;
      }
   }
   else {
      xhttp.open("GET", "ledontime?state=" + state + "&T=" + time, true);
      xhttp.send();
   }
}

function ResetWifi() {

  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      alert("Контроллер будет перезагружен. Появится точка доступа ESPled.");
    }
  };

  xhttp.open("GET", "resetWifi", true);
  xhttp.send();
}

</script>
)=====";