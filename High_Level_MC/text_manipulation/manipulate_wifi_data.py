import re #to be able to extract the numerical part

#the values that will be put in the string
values = [
    '10',       #weight 
    'YES',      #IR
    '0.5',      #Xa
    '0.1',      #Ya
    '0.8',      #Za
    '0.3',      #Xg
    '1.4',      #Yg
    '2.5',      #Zg
    '105'       #Heading
]

def display_gui():
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

    # Read the variables from the text files
    #product = product_file.read().strip()
    #price = price_file.read().strip()
    weight = values[0]

    # Create the labels with the updated styles and variables
    title_label = ttk.Label(frame, text="Smart Retail System", style="Custom.TLabel")
    #product_label = ttk.Label(frame, text=f"Product: {product}", style="Custom.TLabel")
    #price_label = ttk.Label(frame, text=f"Total Price: ${price}", style="Custom.TLabel")
    weight_label = ttk.Label(frame, text=f"Weight: {weight}kg", style="Custom.TLabel")

    title_label.pack(side="top", pady=10)
    #product_label.pack(side="top", anchor="w")
    weight_label.pack(anchor="w")
    #price_label.pack(side="bottom", anchor="se")

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

whole_text = whole_text_template.format(*values)

print(whole_text) #print the string

while (1):
    #buffer_received = "10 kg"
    #read the buffer_received from the user
    buffer_received = input("Enter the buffer_received: ")

    #if the buffer contains the break character (-1), clear the buffer
    if "-1" in buffer_received:
        buffer_received = ""
    
    # Update values based on the buffer keywords
    buffer_keywords = ["weight", "IR", "Xa", "Ya", "Za", "Xg", "Yg", "Zg", "Heading"]
    for keyword in buffer_keywords:
        if keyword in buffer_received:
            #value = ''.join(filter(str.isdigit, buffer_received))
            #values[buffer_keywords.index(keyword)] = value
            # Use regular expression to find numeric values (integers or floats)
            value = re.search(r"[-+]?\d*\.\d+|\d+", buffer_received).group()
            values[buffer_keywords.index(keyword)] = value
            break  # No need to continue checking other keywords if a match is found
    
    # Format the whole_text with the updated values
    whole_text = whole_text_template.format(*values)


    # Print the updated string
    # Send the whole_text string to a .txt file to be read by the GUI
    print(whole_text)
    display_gui()




