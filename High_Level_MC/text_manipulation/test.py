#the values that will be put in the string
values = [
    '10',       #weight 
    'YES',    #IR
    '0.5',      #Xa
    '0.1',      #Ya
    '0.8',      #Za
    '0.3',      #Xg
    '1.4',      #Yg
    '2.5',      #Zg
    '105'       #Heading
]

#this template to allow me to update the whole_text
whole_text_template = '''weight = {} kg 
IR = {} 
Xa = {}
Ya = {}
Za = {}
Xg = {}
Yg = {}
Zg = {}
Heading = {} degrees'''

#the string that will be saved as a .txt
whole_text = '''weight = {} kg 
IR = {} 
Xa = {}
Ya = {}
Za = {}
Xg = {}
Yg = {}
Zg = {}
Heading = {} degrees'''

whole_text = whole_text_template.format(*values)

#buffer received string (from Wifi)
buffer_received = "weight = 110kg"

#extract number from the buffer_received string
number_in_buffer = ''.join(filter(str.isdigit, buffer_received))

#if the buffer contains the break character, clear the buffer
# -1 is the break character
if "-1" in buffer_received:
    buffer_received = ""

if "weight" in buffer_received:
    values[0] = number_in_buffer
if "IR" in buffer_received:
    values[1] = number_in_buffer
if "Xa" in buffer_received:
    values[2] = number_in_buffer
if "Ya" in buffer_received:
    values[3] = number_in_buffer
if "Za" in buffer_received:
    values[4] = number_in_buffer
if "Xg" in buffer_received:
    values[5] = number_in_buffer
if "Yg" in buffer_received:
    values[6] = number_in_buffer
if "Zg" in buffer_received:
    values[7] = number_in_buffer
if "Heading" in buffer_received:
    values[8] = number_in_buffer

whole_text = whole_text_template.format(*values)

print(whole_text) #print the string

#while (1):
    #buffer_received = "10 kg"
