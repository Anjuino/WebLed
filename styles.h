const char mystyle[] PROGMEM = R"=====(
.slider {
  background-color: #00000052;
	scroll-snap-type: x mandatory;	
	display: flex;
	-webkit-overflow-scrolling: touch;
	overflow-x: scroll;
}
section {
	padding: 10px;
	min-width: 94vw;
	scroll-snap-align: start;
  position: relative;
}

td {
   width: 1%;
}
table, th, td {
   background-color: rgb(41 40 40 / 39%);
   text-align: center;     
   border: 4px solid white;
   margin-left: auto;
   margin-right: auto;
}

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
   font-size: 54px;
}  

input[type='checkbox'] {
    top: 6px;
    position: relative;
    width: 100px;
    height: 70px;
}

 input[type='range'] {
   accent-color: #ffb500;
   transform: scaleY(3.0);
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

 hr {
   margin: -40px auto;
    height: 60px;
    border: none;
    border-bottom: 4px solid #574545
 }
 
 body {
   font-family: system-ui;
   background: linear-gradient(1deg, #004677, #3f3d93, #850101, #6d008d, #813700, #0c8100, #8c0000, #ad0101, #5e7b00, #b90071b8, #01750a);
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
   padding-top: 15%;
   padding-left: 20px;
   padding-right: 20px;
 }

)=====";