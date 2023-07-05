import re
import threading
import requests
import tkinter as tk
from tkinter import ttk

values = ['0'] * 9

whole_text_template = '''Weight = {} kg 
IR = {} 
Xa = {}
Ya = {}
Za = {}
Xg = {}
Yg = {}
Zg = {}
Heading = {} degrees'''

whole_text = whole_text_template.format(*values)

buffer_received = "N/A"

root = tk.Tk()
root.geometry("500x500")
style = ttk.Style()
style.configure("Custom.TFrame", background="#F0F0F0")
style.configure("Custom.TLabel", font=("Arial", 14, "bold"), foreground="#333333")

frame = ttk.Frame(root, style="Custom.TFrame")
frame.pack(fill=tk.BOTH, expand=True)
separator1 = ttk.Separator(frame, orient='horizontal')
separator2 = ttk.Separator(frame, orient='horizontal')

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

def update_gui():
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

    file_name = 'Detection.txt'
    value = read_file_to_string(file_name)

    if value != "":
        product, price = value.split("\n")[:2]
    else:
        product = "NONE"
        price = "0"

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

    root.after(50, update_gui)

def fetch_data():
    global buffer_received, whole_text, values

    url = "http://192.168.4.1/temperature"
    response = requests.get(url)
    buffer_received = response.text

    print("\n\nbuffer received = ")
    print(buffer_received)

    buffer_keywords = ["Weight", "IR", "Xa", "Ya", "Za", "Xg", "Yg", "Zg", "Heading"]
    lines = buffer_received.splitlines()
    for line in lines:
        for keyword in buffer_keywords:
            if keyword in line:
                value = re.search(r"[-+]?\d*\.\d+|\d+", line).group()
                values[buffer_keywords.index(keyword)] = value

    whole_text = whole_text_template.format(*values)

    update_gui()
    print ("\n\nwhole_text = ")
    print(whole_text)

    threading.Timer(0.6, fetch_data).start()

def http_thread():
    fetch_data()

http_thread = threading.Thread(target=http_thread)
http_thread.daemon = True
http_thread.start()

root.after(50, update_gui)
root.mainloop()
