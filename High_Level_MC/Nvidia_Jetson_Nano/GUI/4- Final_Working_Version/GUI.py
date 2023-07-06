import re       #to be able to extract the numerical part
import threading

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
root.geometry("500x500")

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

# Create a custom style for the label
style = ttk.Style()
style.configure("Custom.TLabe2", underline=True)

# Create a frame using the custom style
frame = ttk.Frame(root, style="Custom.TFrame")
frame.pack(fill=tk.BOTH, expand=True)

separator1 = ttk.Separator(frame, orient='horizontal')
separator2 = ttk.Separator(frame, orient='horizontal')


# Create the labels with the updated styles and initial values
title_label = ttk.Label(frame, text="Smart Retail System", style="Custom.TLabel")
weight_label = ttk.Label(frame, text="Weight: 0kg", style="Custom.TLabel")
ir_label = ttk.Label(frame, text="IR: N/A", style="Custom.TLabel")
xa_label = ttk.Label(frame, text="Xa: N/A", style="Custom.TLabel")
acceleration_label = ttk.Label(frame, text="Acceleration:", style="Custom.TLabel")
ya_label = ttk.Label(frame, text="Ya: N/A", style="Custom.TLabel")
za_label = ttk.Label(frame, text="Za: N/A", style="Custom.TLabel")
xg_label = ttk.Label(frame, text="Xg: N/A", style="Custom.TLabel")
yg_label = ttk.Label(frame, text="Yg: N/A", style="Custom.TLabel")
zg_label = ttk.Label(frame, text="Zg: N/A", style="Custom.TLabel")
heading_label = ttk.Label(frame, text="Heading: N/A degrees", style="Custom.TLabel")
ML_label = ttk.Label(frame, text="Object Detection:", style="Custom.TLabel")
product_label = ttk.Label(frame, text="Product: N/A", style="Custom.TLabel")
price_label = ttk.Label(frame, text="Price: N/A", style="Custom.TLabel")

# Pack the labels
title_label.pack(side="top", pady=10)
weight_label.pack(anchor="w")
ir_label.pack(anchor="w")
separator1.pack(fill='x', pady=10)
acceleration_label.pack(anchor="w")
xa_label.pack(anchor="w")
ya_label.pack(anchor="w")
za_label.pack(anchor="w")
xg_label.pack(anchor="w")
yg_label.pack(anchor="w")
zg_label.pack(anchor="w")
heading_label.pack(anchor="w")
separator2.pack(fill='x', pady=10)
ML_label.pack(anchor="w")
product_label.pack(anchor="w")
price_label.pack(anchor="w")

# Function to update the labels with new values
def update_gui():
    ########################    Habiba's  ########################
    def read_file_to_string(file_name):
        try:
            with open(file_name, 'r') as file:
                value = file.read()
                return value
        except FileNotFoundError:
            print(f"File '{file_name}' not found.")
            return None
        except Exception as e:
            print(f"An error occurred: {e}")
            return None

    # Replace 'readme.txt' with the actual path to your file
    file_name = 'Detection.txt'
    value = read_file_to_string(file_name)

    #if value is not None:
    #    print("File content:")
    #    print(value)

    if value != "":
        split_strings = value.split("\n")    
        product = split_strings[0]
        price = split_strings[1]
    if value == "":
        product = "NONE"
        price = "0"
    ########################    Habiba's  ########################

    weight, ir, xa, ya, za, xg, yg, zg, heading = map(float, values)
    weight_label.config(text=f"Weight: {weight}kg")
    ir_label.config(text=f"IR: {ir}")
    acceleration_label.config(text="### Acceleration ###")
    xa_label.config(text=f"Xa: {xa}")
    ya_label.config(text=f"Ya: {ya}")
    za_label.config(text=f"Za: {za}")
    xg_label.config(text=f"Xg: {xg}")
    yg_label.config(text=f"Yg: {yg}")
    zg_label.config(text=f"Zg: {zg}")
    heading_label.config(text=f"Heading: {heading} degrees")
    ML_label.config(text="### Object Detection ### ")
    product_label.config(text=f"Product: {product}")
    price_label.config(text=f"Price: {price}")
    


    root.after(50, update_gui)  # Threading: Schedule the function to run again after 50ms
    
# Example of how to call the function and update the labels
update_gui()
########################    End of GUI  ########################




def fetch_data():
    global buffer_received, whole_text
    import requests
    import time

    url = "http://192.168.4.1/temperature"
    response = requests.get(url)
    buffer_received = response.text

    print("\n\nbuffer received = ")
    print(buffer_received)

    # Update values based on the buffer keywords
    buffer_keywords = ["Weight", "IR", "Xa", "Ya", "Za", "Xg", "Yg", "Zg", "Heading"]
    lines = buffer_received.splitlines()   
    for line in lines:
        for keyword in buffer_keywords:
            if keyword in line:
                # Use regular expression to find numeric values (integers or floats)
                value = re.search(r"[-+]?\d*\.\d+|\d+", line).group()
                values[buffer_keywords.index(keyword)] = value
    
    # Format the whole_text with the updated values
    whole_text = whole_text_template.format(*values)

    # Print the updated string
    update_gui()
    print ("\n\nwhole_text = ")
    print(whole_text)

    # Threading: Call the fetch_data function again after 0.5 second using Timer
    threading.Timer(1, fetch_data).start()  

# Instead of the while loop, start the HTTP request in a separate thread
def http_thread():
    fetch_data()

# Start the HTTP thread
http_thread = threading.Thread(target=http_thread)
http_thread.daemon = True  # Allow the program to exit even if the thread is running
http_thread.start()

# Schedule the update_gui() function to be called from the main thread periodically
root.after(1000, update_gui) #50ms 

root.mainloop()



