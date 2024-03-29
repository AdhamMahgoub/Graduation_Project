{
 "cells": [
  {
   "cell_type": "code",
   "execution_count": 3,
   "id": "4fe3101d",
   "metadata": {},
   "outputs": [],
   "source": [
    "import tkinter as tk\n",
    "from tkinter import ttk\n",
    "\n",
    "root = tk.Tk()\n",
    "root.geometry(\"250x250\")\n",
    "\n",
    "# Create a style object\n",
    "style = ttk.Style()\n",
    "\n",
    "# Configure the style to use a solid background color and update label styles\n",
    "style.configure(\n",
    "    \"Custom.TFrame\",\n",
    "    background=\"#F0F0F0\",  # Set a solid background color\n",
    ")\n",
    "\n",
    "style.configure(\n",
    "    \"Custom.TLabel\",\n",
    "    font=(\"Arial\", 14, \"bold\"),  # Update font style and size\n",
    "    foreground=\"#333333\",  # Set label text color\n",
    ")\n",
    "\n",
    "# Create a frame using the custom style\n",
    "frame = ttk.Frame(root, style=\"Custom.TFrame\")\n",
    "frame.pack(fill=tk.BOTH, expand=True)\n",
    "\n",
    "# Read the variables from the text files\n",
    "with open(\"Information/product.txt\", \"r\") as product_file:\n",
    "    product = product_file.read().strip()\n",
    "\n",
    "with open(\"Information/price.txt\", \"r\") as price_file:\n",
    "    price = price_file.read().strip()\n",
    "\n",
    "with open(\"Information/weight.txt\", \"r\") as weight_file:\n",
    "    weight = weight_file.read().strip()\n",
    "\n",
    "# Create the labels with the updated styles and variables\n",
    "title_label = ttk.Label(frame, text=\"Smart Retail System\", style=\"Custom.TLabel\")\n",
    "product_label = ttk.Label(frame, text=f\"Product: {product}\", style=\"Custom.TLabel\")\n",
    "price_label = ttk.Label(frame, text=f\"Total Price: ${price}\", style=\"Custom.TLabel\")\n",
    "weight_label = ttk.Label(frame, text=f\"Weight: {weight}kg\", style=\"Custom.TLabel\")\n",
    "\n",
    "title_label.pack(side=\"top\", pady=10)\n",
    "product_label.pack(side=\"top\", anchor=\"w\")\n",
    "weight_label.pack(anchor=\"w\")\n",
    "price_label.pack(side=\"bottom\", anchor=\"se\")\n",
    "\n",
    "root.mainloop()\n"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "id": "ee0dcb0e",
   "metadata": {},
   "outputs": [],
   "source": []
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "id": "45c413ec",
   "metadata": {},
   "outputs": [],
   "source": []
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "id": "8fe80b65",
   "metadata": {},
   "outputs": [],
   "source": []
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "id": "0448fe80",
   "metadata": {},
   "outputs": [],
   "source": []
  }
 ],
 "metadata": {
  "kernelspec": {
   "display_name": "Python 3 (ipykernel)",
   "language": "python",
   "name": "python3"
  },
  "language_info": {
   "codemirror_mode": {
    "name": "ipython",
    "version": 3
   },
   "file_extension": ".py",
   "mimetype": "text/x-python",
   "name": "python",
   "nbconvert_exporter": "python",
   "pygments_lexer": "ipython3",
   "version": "3.9.6"
  }
 },
 "nbformat": 4,
 "nbformat_minor": 5
}
