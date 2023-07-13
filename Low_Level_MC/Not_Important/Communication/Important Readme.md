I send from the ATMEGA32 to the ESP8266 to the Jetson Nano Successfully 
Trial1: ATMEGA   > Arduino
Trial2: ATMEGA32 > ESP8266 > Jetson Nano


Codes: 
	- ATMEGA32: C:\Users\adham\Desktop\Graduation_Project\Low_Level_MC\2. Single_Modules\3. HX711
	- Arduino: C:\Users\adham\Desktop\Graduation_Project\Communication\2. Arduino_UART_test
	- ESP8266: C:\Users\adham\Desktop\Graduation_Project\Communication\3. ESP_receive_from_ATMEGA_and_send_to_Jetson_Nano
	- Jetson Nano: C:\Users\adham\Desktop\Graduation_Project\Communication\4. Jetson_Nano_Python 

Testing: 
	- ATMEGA32: tested & verified
	- Arduino: tested & verified
	- ESP8266: tested & verified
	- Jetson Nano: tested & verified


Connections: 
Trial1: 
	Arduino: 
		- Connected to the laptop using USB 
		- RX > TX 		TX > RX
	ATMEGA: 
		- takes power 5v from the converter (programmer is unpluged -- removed the blackhead but wires are still on)
		- reset is not connected	
	Ground: 
		- Connected ground on both (common ground)


Trial2: 
	ESP8266: 
		connected to the 3.3v using the converter
	ATMEGA32: 
		- reset is not connected 
		- tested on both of the following cases: 
			- 5v from the converter (programmer is unpluged -- removed the blackhead but wires are still on)
			- programmer conencted to the pc
	Ground:
		- Connected ground on both (common ground)


Notes: 
	- when switching between Arduino and ESP8266 don't forget to 
		- switch ports 
		- choose the correct board
	- don't forget to 
		- connect ground between two microcontrollers 
		- set sufficient delay in the ATMEGA code ~150ms 
	- no reset connection is needed for the ATMEGA32 

		