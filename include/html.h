const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
  <head>
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <style>
        html {
            font-family: Arial;
            display: inline-block;
            margin: 0px auto;
            text-align: center;
            color: white;
            background: #333333;
        }

        input[type=range] {
            -webkit-appearance: none;
            height: 40px;
            width: 90%;
        } 

        input[type=range]::-webkit-slider-thumb {
          -webkit-appearance: none;
            border: 1px solid #000000;
            height: 36px;
            width: 16px;
            border-radius: 3px;
            background: #ffffff;
            cursor: pointer;
            margin-top: -14px;
            box-shadow: 1px 1px 1px #000000, 0px 0px 1px #0d0d0d; 
        }
        
        input[type=range]:focus {
          outline: none;
        }
        
        input[type=range]::-ms-track {
          width: 100%;
          cursor: pointer;
          background: transparent; 
          border-color: transparent;
          color: transparent;
        }

        .slider_red {
            background: red;      
        }
        .slider_green {
            background: green;      
        }
        .slider_blue {
            background: blue;      
        }
        
        table {
          border-collapse: collapse;
        }
              
        td {
            border: 1px solid red;
        }
        
        td.color_sample {
          height: 40px;
          text-align: center;
        }

        button {
          background-color: #4CAF50; /* Green */
          border: none;
          color: white;
          padding: 15px 32px;
          text-align: center;
          text-decoration: none;
          display: inline-block;
          font-size: 16px;
        }
      </style>

      <script>
        window.onload = function() {
          var xhttp = new XMLHttpRequest();

          xhttp.open("PUT", "/load_scene", true);
          xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
              console.log(this.responseText);
            }
          };
          xhttp.send();
        }

        function colorChange_1(slider) {
          var red=parseInt(document.getElementById("red_value_1").innerHTML)
          var green=parseInt(document.getElementById("green_value_1").innerHTML)
          var blue=parseInt(document.getElementById("blue_value_1").innerHTML)

          if (slider.id=="slider_red_1") {
            red=slider.value;
            document.getElementById("red_value_1").innerHTML=red;
          }
          if (slider.id=="slider_green_1") {
            green=slider.value;
            document.getElementById("green_value_1").innerHTML=green;
          }
          if (slider.id=="slider_blue_1") {
            blue=slider.value;
            document.getElementById("blue_value_1").innerHTML=blue;
          }

          //document.getElementById("line_back_color_1").style.backgroundColor="rgb(" + red + "," + green + "," + blue + ")";
          set_color_line1(red,green,blue);
        }

        function colorChange_2(slider) {
          var red=parseInt(document.getElementById("red_value_2").innerHTML)
          var green=parseInt(document.getElementById("green_value_2").innerHTML)
          var blue=parseInt(document.getElementById("blue_value_2").innerHTML)

          if (slider.id=="slider_red_2") {
            red=slider.value;
            document.getElementById("red_value_2").innerHTML=red;
          }
          if (slider.id=="slider_green_2") {
            green=slider.value;
            document.getElementById("green_value_2").innerHTML=green;
          }
          if (slider.id=="slider_blue_2") {
            blue=slider.value;
            document.getElementById("blue_value_2").innerHTML=blue;
          }

          //document.getElementById("line_back_color_2").style.backgroundColor="rgb(" + red + "," + green + "," + blue + ")";
          set_color_line2(red,green,blue);
        }


        function set_color_line1(red,green,blue) {
          var xhttp = new XMLHttpRequest();
          var params = "red=" + red + "&green=" + green + "&blue=" + blue;

          xhttp.open("PUT", "/set_color_line1", true);
          xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
              //console.log(this.responseText);
            }
          };
          xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
          xhttp.send(params);
        }

        function set_color_line2(red,green,blue) {
          var xhttp = new XMLHttpRequest();
          var params = "red=" + red + "&green=" + green + "&blue=" + blue;

          xhttp.open("PUT", "/set_color_line2", true);
          xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
              //console.log(this.responseText);
            }
          };
          xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
          xhttp.send(params);
        }

        function saveScene() {
          var xhttp = new XMLHttpRequest();

          xhttp.open("PUT", "/save_scene", true);
          xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
              //console.log(this.responseText);
            }
          };
          xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
          xhttp.send();
        }

      </script>

    </head>
    <body>
        <h2>PlexiLed</h2>

        <table width="100%">
	        <tr>
            <td class="color_sample" colspan="2" id="line_back_color_2">
                  COLORE FONDO
            </td>        	
	        </tr>	
	        <tr>
            <td width="60px" id="red_value_2">
                  0
            </td>        	
            <td>
                  <input onchange="colorChange_2(this)" class="slider_red"  id="slider_red_2" type="range" min="0" max="255" value="0">
            </td>        	
	        </tr>	
	        <tr>
            <td id="green_value_2">
                  0
            </td>        	
            <td>
                  <input onchange="colorChange_2(this)" class="slider_green"  id="slider_green_2"  type="range" min="0" max="255" value="0">
            </td>        	
	        </tr>	
	        <tr>
            <td id="blue_value_2">
                  0
            </td>        	
            <td>
                  <input onchange="colorChange_2(this)" class="slider_blue"  id="slider_blue_2"  type="range" min="0" max="255" value="0">
            </td>        	
	        </tr>	
        </table>

        <hr/>

        <table width="100%">
	        <tr>
            <td class="color_sample" colspan="2" id="line_back_color_1">
                  COLORE LOGO
            </td>        	
	        </tr>	
	        <tr>
            <td width="60px" id="red_value_1">
                  0
            </td>        	
            <td>
                  <input onchange="colorChange_1(this)" class="slider_red" id="slider_red_1" type="range" min="0" max="255" value="0">
            </td>        	
	        </tr>	
	        <tr>
            <td id="green_value_1">
                  0
            </td>        	
            <td>
                  <input onchange="colorChange_1(this)" class="slider_green"  id="slider_green_1" type="range" min="0" max="255" value="0">
            </td>        	
	        </tr>	
	        <tr>
            <td id="blue_value_1">
                  0
            </td>        	
            <td>
                  <input onchange="colorChange_1(this)" class="slider_blue"  id="slider_blue_1"  type="range" min="0" max="255" value="0">
            </td>        	
	        </tr>	
        </table>

        <br/>

        <button onclick="saveScene()">SAVE</button>

    </body>
</html>
)rawliteral";