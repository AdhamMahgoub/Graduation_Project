import re       #to be able to extract the numerical part

#the values that will be put in the string
values = [
    '0',        #weight 
    '0',        #IR         #Must be Number
    '0',        #Xa
    '0',        #Ya
    '0',        #Za
    '0',        #Xg
    '0',        #Yg
    '0',        #Zg
    '0'         #Heading
]

#this template to allow me to update the whole_text
whole_text_template = '''Weight = {} kg 
IR = {} 
Xa = {}
Ya = {}
Za = {}
Xg = {}
Yg = {}
Zg = {}
Heading = {} degrees'''

#the final string that will be saved/printed
whole_text = '''weight = {} kg 
IR = {} 
Xa = {}
Ya = {}
Za = {}
Xg = {}
Yg = {}
Zg = {}
Heading = {} degrees'''

#buffer received string (from Wifi)
#creating a buffer_received variable
buffer_received = "N/A"

# Format the whole_text with the updated values (1st time)
whole_text = whole_text_template.format(*values)

# Print initial text (all 0s)
print ("\n\n Initial whole_text = ")
print(whole_text) #print the string


########################    GUI     ########################
import tkinter as tk
from tkinter import ttk

root = tk.Tk()
root.geometry("250x250")

# Create a style object
style = ttk.Style()

# Configure the style to use a solid background color and update label styles
style.configure(
    "Custom.TFrame",
    background="#F0F0F0",  # Set a solid background color
)

style.configure(
    "Custom.TLabel",
    font=("Arial", 14, "bold"),  # Update font style and size
    foreground="#333333",  # Set label text color
)

# Create a frame using the custom style
frame = ttk.Frame(root, style="Custom.TFrame")
frame.pack(fill=tk.BOTH, expand=True)

# Create the labels with the updated styles and initial values
title_label = ttk.Label(frame, text="Smart Retail System", style="Custom.TLabel")
weight_label = ttk.Label(frame, text="Weight: 0kg", style="Custom.TLabel")
ir_label = ttk.Label(frame, text="IR: N/A", style="Custom.TLabel")
xa_label = ttk.Label(frame, text="Xa: N/A", style="Custom.TLabel")
ya_label = ttk.Label(frame, text="Ya: N/A", style="Custom.TLabel")
za_label = ttk.Label(frame, text="Za: N/A", style="Custom.TLabel")
xg_label = ttk.Label(frame, text="Xg: N/A", style="Custom.TLabel")
yg_label = ttk.Label(frame, text="Yg: N/A", style="Custom.TLabel")
zg_label = ttk.Label(frame, text="Zg: N/A", style="Custom.TLabel")
heading_label = ttk.Label(frame, text="Heading: N/A degrees", style="Custom.TLabel")

# Pack the labels
title_label.pack(side="top", pady=10)
weight_label.pack(anchor="w")
ir_label.pack(anchor="w")
xa_label.pack(anchor="w")
ya_label.pack(anchor="w")
za_label.pack(anchor="w")
xg_label.pack(anchor="w")
yg_label.pack(anchor="w")
zg_label.pack(anchor="w")
heading_label.pack(anchor="w")

# Function to update the labels with new values
def update_gui():
    weight, ir, xa, ya, za, xg, yg, zg, heading = map(float, values)
    weight_label.config(text=f"Weight: {weight}kg")
    ir_label.config(text=f"IR: {ir}")
    xa_label.config(text=f"Xa: {xa}")
    ya_label.config(text=f"Ya: {ya}")
    za_label.config(text=f"Za: {za}")
    xg_label.config(text=f"Xg: {xg}")
    yg_label.config(text=f"Yg: {yg}")
    zg_label.config(text=f"Zg: {zg}")
    heading_label.config(text=f"Heading: {heading} degrees")

# Example of how to call the function and update the labels
update_gui()
########################    End of GUI  ########################



while (1):
    #read the buffer_received from the user -- recplaced with http (written below)
    buffer_received = input("Enter the buffer_received: ") 

    '''
    ########################        HTTP        ########################
    import requests
    import time

    url = "http://192.168.4.1/temperature"
    response = requests.get(url)
    buffer_received = response.text

    print("\n\nbuffer received = ")
    print(buffer_received)
    time.sleep(0.5)  # delay for 0.5 seconds
    ########################        End of HTTP        ########################
'''



    #if the buffer contains the break character (-1), clear the buffer
    if "-1" in buffer_received:
        buffer_received = ""
    
    # Update values based on the buffer keywords
    buffer_keywords = ["Weight", "IR", "Xa", "Ya", "Za", "Xg", "Yg", "Zg", "Heading"]
    for keyword in buffer_keywords:
        if keyword in buffer_received:
            # Use regular expression to find numeric values (integers or floats)
            value = re.search(r"[-+]?\d*\.\d+|\d+", buffer_received).group()
            values[buffer_keywords.index(keyword)] = value
            break  # No need to continue checking other keywords if a match is found
    
    # Format the whole_text with the updated values
    whole_text = whole_text_template.format(*values)

    # Print the updated string
    update_gui()
    print ("\n\nwhole_text = ")
    print(whole_text)





