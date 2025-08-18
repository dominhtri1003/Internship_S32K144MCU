import tkinter as tk
from tkinter import messagebox, scrolledtext, ttk
import serial
import serial.tools.list_ports
import time
import threading
from datetime import datetime
from PIL import Image, ImageTk

# Biến global cho kết nối serial
ser = None

def send_time_date():
    global ser
    if not ser or not ser.is_open:
        messagebox.showerror("Error", "No active serial connection")
        return
    try:
        hour = int(hour_entry.get())
        minute = int(minute_entry.get())
        second = int(second_entry.get())
        day = int(day_entry.get())
        month = int(month_entry.get())
        year = int(year_entry.get())
        
        if not (0 <= hour < 24 and 0 <= minute < 60 and 0 <= second < 60):
            raise ValueError("Invalid time")
        
        if not (1 <= day <= 31 and 1 <= month <= 12 and year > 0):
            raise ValueError("Invalid date")
        
        year_high_byte = (year >> 8) & 0xFF
        year_low_byte = year & 0xFF

        data = [0xAA, 0x55, 0x01, hour, minute, second, day, month, year_high_byte, year_low_byte, 0x00, 0x75]
        checksum = calculate_checksum(data)
        data[10] = checksum

        ser.write(bytearray(data))
    except ValueError as e:
        messagebox.showerror("Error", str(e))
    except Exception as e:
        messagebox.showerror("Error", f"Can't send data: {e}")

def calculate_checksum(data):
    checksum = 0xFF
    for i in range(3, len(data) - 2):
        checksum ^= data[i]
        for _ in range(8):
            if checksum & 0x80:
                checksum = (checksum << 1) ^ 0x36
            else:
                checksum <<= 1
            checksum &= 0xFF
    return checksum

def receive_time_date():
    global ser
    if not ser or not ser.is_open:
        messagebox.showerror("Error", "No active serial connection")
        return
    try:
        ser.write(bytearray([0xAA, 0x55, 0x02, 0x75]))  
        start_time = time.time()

        while True:
            if ser.in_waiting >= 12:
                data = ser.read(12)
                if data[0] == 0xAA and data[1] == 0x55 and data[-1] == 0x75:
                    hour = data[3]
                    minute = data[4]
                    second = data[5]
                    day = data[6]
                    month = data[7]
                    year = (data[8] << 8) + data[9]

                    time_date_label.config(text=f"{hour:02d}:{minute:02d}:{second:02d} {day:02d}/{month:02d}/{year}")
                    messagebox.showinfo("Success", "Time and date received successfully!")
                else:
                    messagebox.showerror("Error", "Failed to receive valid data!")
                break
            elif time.time() - start_time > 2:  # Timeout after 2 seconds
                messagebox.showerror("Error", "Not enough data received within the timeout period!")
                break
    except Exception as e:
        messagebox.showerror("Error", f"Error receiving data: {e}")

def adjust_brightness():
    global ser
    if not ser or not ser.is_open:
        messagebox.showerror("Error", "No active serial connection")
        return
    try:
        brightness = int(brightness_entry.get())
        if not (1 <= brightness <= 15):
            raise ValueError("Intensity must be between 1 and 15")
        
        ser.write(bytearray([0xAA, 0x55, 0x03, brightness & 0xFF, 0x75]))
        messagebox.showinfo("Success", "Brightness adjusted successfully!")
    except ValueError as e:
        messagebox.showerror("Error", str(e))
    except Exception as e:
        messagebox.showerror("Error", f"Error adjusting brightness: {e}")

def send_display_mode():
    global ser
    if not ser or not ser.is_open:
        messagebox.showerror("Error", "No active serial connection")
        return
    try:
        mode = mode_combo.get()
        if mode == "Auto":
            mode_value = 0x01
        elif mode == "Date Only":
            mode_value = 0x02
        elif mode == "Time Only":
            mode_value = 0x03
        else:
            raise ValueError("Invalid mode selection")
        
        ser.write(bytearray([0xAA, 0x55, 0x02, mode_value, 0x75]))
        messagebox.showinfo("Success", "Display mode changed successfully!")
    except ValueError as e:
        messagebox.showerror("Error", str(e))
    except Exception as e:
        messagebox.showerror("Error", f"Error changing display mode: {e}")

def update_chatbox():
    global ser
    while True:
        if ser and ser.is_open and ser.in_waiting > 0:
            try:
                data = ser.readline().decode('utf-8').strip()
                if data:
                    chatbox.insert(tk.END, f"{data}\n")
                    chatbox.see(tk.END)
            except Exception as e:
                chatbox.insert(tk.END, f"Error reading data: {e}\n")
                chatbox.see(tk.END)
        time.sleep(0.1)

def update_com_ports():
    com_ports = [port.device for port in serial.tools.list_ports.comports()]
    com_combo['values'] = com_ports
    if com_ports:
        com_combo.set(com_ports[0])

def send_current_time():
    now = datetime.now()
    hour_entry.delete(0, tk.END)
    hour_entry.insert(0, now.hour)
    minute_entry.delete(0, tk.END)
    minute_entry.insert(0, now.minute)
    second_entry.delete(0, tk.END)
    second_entry.insert(0, now.second)
    day_entry.delete(0, tk.END)
    day_entry.insert(0, now.day)
    month_entry.delete(0, tk.END)
    month_entry.insert(0, now.month)
    year_entry.delete(0, tk.END)
    year_entry.insert(0, now.year)
    send_time_date()

def connect_serial():
    global ser
    try:
        port = com_combo.get()
        baud = int(baud_entry.get())
        ser = serial.Serial(port, baud, timeout=0.1)
        send_current_time()
    except Exception as e:
        messagebox.showerror("Error", f"Failed to connect: {e}")

def disconnect_serial():
    global ser
    if ser and ser.is_open:
        ser.close()
        messagebox.showinfo("Success", "Disconnected")
    else:
        messagebox.showinfo("Info", "No active connection")

# Tạo giao diện
root = tk.Tk()
root.title("S32K144 Interface")

logo_path = "/home/trido/Documents/Fsoft_Intern/logo_bachkhoa.png"
image = Image.open(logo_path)
image_resized = image.resize((200, 150), Image.ANTIALIAS)
photo = ImageTk.PhotoImage(image_resized)
image_label = tk.Label(root, image=photo)
image_label.place(x=0, y=0)

# Frame cho cấu hình COM port và tốc độ baud
hercules_frame = tk.Frame(root)
hercules_frame.pack(pady=10)

com_label = tk.Label(hercules_frame, text="COM Port:")
com_label.grid(row=0, column=0)
com_combo = ttk.Combobox(hercules_frame)
com_combo.grid(row=0, column=1)

baud_label = tk.Label(hercules_frame, text="Baud Rate:")
baud_label.grid(row=1, column=0)
baud_entry = tk.Entry(hercules_frame)
baud_entry.grid(row=1, column=1)
baud_entry.insert(0, "38400")  # Giá trị mặc định

connect_button = tk.Button(hercules_frame, text="Connect", command=connect_serial)
connect_button.grid(row=2, column=0, pady=5)
disconnect_button = tk.Button(hercules_frame, text="Disconnect", command=disconnect_serial)
disconnect_button.grid(row=2, column=1, pady=5)

# Frame cho gửi/nhận thời gian và ngày tháng
time_frame = tk.LabelFrame(root, text="Time and Date")
time_frame.pack(pady=10)

hour_label = tk.Label(time_frame, text="Hour:")
hour_label.grid(row=0, column=0)
hour_entry = tk.Entry(time_frame, width=5)
hour_entry.grid(row=0, column=1)

minute_label = tk.Label(time_frame, text="Minute:")
minute_label.grid(row=0, column=2)
minute_entry = tk.Entry(time_frame, width=5)
minute_entry.grid(row=0, column=3)

second_label = tk.Label(time_frame, text="Second:")
second_label.grid(row=0, column=4)
second_entry = tk.Entry(time_frame, width=5)
second_entry.grid(row=0, column=5)

day_label = tk.Label(time_frame, text="Day:")
day_label.grid(row=1, column=0)
day_entry = tk.Entry(time_frame, width=5)
day_entry.grid(row=1, column=1)

month_label = tk.Label(time_frame, text="Month:")
month_label.grid(row=1, column=2)
month_entry = tk.Entry(time_frame, width=5)
month_entry.grid(row=1, column=3)

year_label = tk.Label(time_frame, text="Year:")
year_label.grid(row=1, column=4)
year_entry = tk.Entry(time_frame, width=5)
year_entry.grid(row=1, column=5)

send_button = tk.Button(time_frame, text="Send Time and Date", command=send_time_date)
send_button.grid(row=2, column=0, columnspan=6, pady=5)

# Frame adjust intensity level
brightness_frame = tk.LabelFrame(root, text="Brightness Adjustment")
brightness_frame.pack(pady=10)

brightness_label = tk.Label(brightness_frame, text="Intensity (1-15):")
brightness_label.grid(row=0, column=0)
brightness_entry = tk.Entry(brightness_frame, width=5)
brightness_entry.grid(row=0, column=1)

brightness_button = tk.Button(brightness_frame, text="Adjust Brightness", command=adjust_brightness)
brightness_button.grid(row=0, column=2, padx=5)

# Frame choose display mode
mode_frame = tk.LabelFrame(root, text="Display Mode")
mode_frame.pack(pady=10)

mode_label = tk.Label(mode_frame, text="Mode:")
mode_label.grid(row=0, column=0)
mode_combo = ttk.Combobox(mode_frame, values=["Auto", "Date Only", "Time Only"])
mode_combo.grid(row=0, column=1)
mode_combo.current(0)

mode_button = tk.Button(mode_frame, text="Set Mode", command=send_display_mode)
mode_button.grid(row=0, column=2, padx=5)

# Chatbox serial output
chatbox_frame = tk.LabelFrame(root, text="Serial Output")
chatbox_frame.pack(pady=10, fill="both", expand=True)

chatbox = scrolledtext.ScrolledText(chatbox_frame, wrap=tk.WORD, height=10)
chatbox.pack(fill="both", expand=True)

threading.Thread(target=update_chatbox, daemon=True).start()

update_com_ports()

root.mainloop()
