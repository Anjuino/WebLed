const char SettingPage[] PROGMEM = R"=====(
<!DOCTYPE html>
 <head>
    <meta charset="utf-8">
    <title>Led</title>
    <link rel='stylesheet' href='styles.css'>
 </head>

 <body>
    <div class="container">
       <div class="wrapper">
          <p>Введите количество светодиодов</p>
          <input  type="text" maxlength="3" id="LedCount">
          <button type="button" onclick="SetCount()"> Задать</button>
          <hr>
          <br>
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