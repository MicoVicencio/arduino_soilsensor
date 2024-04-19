import serial
import tkinter as tk
from tkinter import Label, font

try:
    # Create a serial connection
    ser = serial.Serial('COM13', 9600)

    # Create the tkinter window
    root = tk.Tk()
    root.geometry("250x150")
    root.title("Arduino")

    # Create labels for display
    title = Label(root, text="Soil Moisture Monitor", font=(20))
    status = Label(root, text="Soil Sensor Status:", font=(20))
    pump = Label(root, text="Water Pump Status:", font=(20))
    status_d = Label(root, text="a", font=(20))
    pump_d = Label(root, text="a", font=(20))

    # Grid layout for labels
    title.grid(row=0, column=0, padx=5, pady=5)
    status.grid(row=1, column=0, pady=5, padx=5)
    pump.grid(row=2, column=0, padx=5, pady=5)
    status_d.grid(row=1, column=1, padx=5, pady=5)
    pump_d.grid(row=2, column=1, padx=5, pady=5)

    def update_status():
        while True:
          data = ser.readline().decode().strip()
          moisture_level = int(data)
          if moisture_level < 500:
                status_d.config(text="Wet")
                # Call a function to control the water pump
                # Example: control_pump(True) to turn on the pump
                pump_d.config(text="OFF")  # Update pump status label
          else:
                status_d.config(text="Dry")
                # Call a function to control the water pump
                # Example: control_pump(False) to turn off the pump
                pump_d.config(text="ON")  # Update pump status label
          root.update()
        

    # Start updating the status labels and sensor reading after GUI initialization
    update_status()
    root.mainloop()

except Exception as e:
    print("Error:", e)
