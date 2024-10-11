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
         <p>Выкл:<input type="time" id="timeoff" onchange = "Ledofftime()"></input> <input type="checkbox" onclick="Ledofftime()" id="ledoff"> </input> </p>
         <hr>
          <p>Введите количество светодиодов</p>
          <input  type="text" maxlength="3" id="LedCount"> </input>
          <button type="button" onclick="SetCount()"> Задать</button>
          <hr>
          <br>
          <button type="button" onclick="ResetWifi()"> Сбросить Wifi настройки</button>
          <br>
          <br>
          <br>
          <br>
          <br>
          <br>
    </div>
  </div>   
</body>

<script>

function onload () {
   GetState();
   GetTime();
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

function GetState() {
   var xhttp = new XMLHttpRequest();
   xhttp.onreadystatechange = function() {

   if (this.readyState == 4 && this.status == 200) {
      var State = this.responseText;
      if (State == "true") document.getElementById("ledoff").checked = true;
      else                 document.getElementById("ledoff").checked = false;
      
      }
   };
   xhttp.open("GET", "getState", true);
   xhttp.send();
}

function GetTime() {
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

      document.getElementById("timeoff").value = timeAll;
   
   }
   };
   xhttp.open("GET", "getTime", true);
   xhttp.send();
}

function Ledofftime() {
   var xhttp = new XMLHttpRequest();
   xhttp.onreadystatechange = function() {
   if (this.readyState == 4 && this.status == 200) {
      var Resp = this.responseText;
      if (Resp == "OK")                          alert("Расписание включено");
      //if (Resp == "OKwithoutSheld")              alert("Время установлено, но расписание не включено");
      if (Resp == "false")                       alert("Расписание отключено");

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