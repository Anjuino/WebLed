const char mystyle[] PROGMEM = R"=====(
p,b {
   text-align: center;
 }
 
 input[type='text']{
   margin: 5%;
   margin-left: 38%;
   width: 25%;
   font-size: 50px;
 }

 input[type='time'] {

   margin-left: 5%;
   font-size: 40px;
 }  

 input[type='checkbox'] {
   top: 17px;
   position: relative;
   margin-left: 10%;
   width: 25%;
   height: 60px;
 }

 input[type='range'] {
   accent-color: #ffb500;
   transform: scaleY(5.0);
   height: 35px;
   width: 100%;
 }
 
 *{
   box-sizing: border-box;
 }
 
 input[type="color"] {
   margin-bottom: 40px;
   padding: 10px;
   height: 184px;
   width: 100%;
 }
 .span {
   text-align: center;
   margin-top: 15px;
   border: 5px double white;
 }
 
 hr {
   margin: -40px auto;
    height: 60px;
    border: none;
    border-bottom: 4px solid #574545
 }
 
 body {
   font-family: system-ui;
   background: linear-gradient(16deg, #004677, #3f3d93, #850101, #6d008d, #813700, #0c8100, #8c0000, #ad0101, #5e7b00, #b90071b8, #01750a);
   background-size: 2200% 2200%;
   animation: back 51s cubic-bezier(0.44, 0.17, 0.58, 0.92) infinite;
 }
 
 @-webkit-keyframes back {
   0%{background-position:0% 94%}
   50%{background-position:100% 7%}
   100%{background-position:0% 94%}
 }
 @keyframes back {
   0%{background-position:0% 94%}
   50%{background-position:100% 7%}
   100%{background-position:0% 94%}
 }
 
 #hr {
   margin: -40px auto 15px;
   height: 50px;
   border: none;
   border-bottom: 4px solid #0043ff;
 }
 #Numeffect {
   font-weight: 600;
   font-family: system-ui;
   text-align: center;
   border: 10px solid #00104b;
   margin-bottom: 30px;
   font-size: 50px;
   height: 90px;
   width: 100%;
 }
 @media screen and (max-width: 980px ) {
 
   body {
     font-weight: 600;
      font-size: 53px;
   }
 
   button {
     font-weight: 600;
     font-family: system-ui;
     border: 10px solid #00104b;
     background: white;
     width: 100%;
     font-size: 66px;
   }
 }
 
 .container {
   color: rgb(255, 255, 255);
   padding-top: 5%;
   padding-left: 20px;
   padding-right: 20px;
 }
)=====";