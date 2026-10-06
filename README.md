# 🏠 GSM Based Home Automation System

A **GSM-based home automation system** developed using the **LPC21xx ARM7 microcontroller** and **UART0 serial communication**.

The project demonstrates how commands received through serial communication can be processed by a microcontroller to control electrical devices. In the current prototype, two LEDs are used to represent home appliances.

---

## 📌 Project Overview

The **GSM Based Home Automation System** is an embedded systems project designed to demonstrate remote control of home appliances using GSM communication.

The LPC21xx microcontroller communicates through **UART0**. Commands received through the UART interface are interpreted by the microcontroller, which then controls two output devices.

In the current implementation:

- Command `'1'` controls LED0.
- Command `'2'` controls LED1.
- Any other character turns both LEDs ON.
- The received character is also transmitted back through UART0.

The project is implemented using **Embedded C** and LPC21xx register-level programming.

---

# 🎯 Objectives

The main objectives of this project are:

- To understand **LPC21xx ARM7 microcontroller programming**
- To understand **UART communication**
- To interface GSM/serial communication with a microcontroller
- To control electrical devices remotely
- To understand GPIO configuration
- To understand UART transmit and receive operations
- To work with microcontroller registers
- To implement command-based device control
- To gain practical experience in Embedded C

---

# ✨ Features

### 📡 GSM/Serial Communication

The system uses **UART0** for communication with the external GSM/serial interface.

The UART configuration includes:

```c
PINSEL0 = 0X05;
U0LCR = 0X83;
U0DLL = 97;
U0LCR = 0X03;
```



---

### 💡 Two Device Control

Two LEDs are configured as output devices:

```c
#define led0 1<<4
#define led1 1<<3
```

The LEDs represent home appliances in the prototype.

---

### 🔢 Command-Based Control

The microcontroller receives a character through UART0.

| Command | Operation |
|---|---|
| `1` | Control LED0 |
| `2` | Control LED1 |
| Other character | Turn both LEDs ON |

The current source code implements this command logic directly in the main loop.

---

### 🔁 UART Echo

After receiving a character, the microcontroller transmits the same character back through UART0.

```c
ch = uart0_rx();
uart0_tx(ch);
```

This provides a simple way to verify that communication is working correctly.

---

# 🧠 Working Principle

The basic working principle is:

```text
        📱 Mobile Phone
              │
              │ GSM / SMS
              ↓
       ┌───────────────┐
       │ GSM Interface │
       └───────┬───────┘
               │
               │ UART
               ↓
       ┌───────────────┐
       │   LPC21xx     │
       │ Microcontroller│
       └───────┬───────┘
               │
       ┌───────┴────────┐
       ↓                ↓
    LED0              LED1
 Appliance 1       Appliance 2
```

The LPC21xx receives the command through UART0 and executes the corresponding control operation.

---

# 🔄 Program Flow

```text
             ┌──────────────────┐
             │  Program Start   │
             └────────┬─────────┘
                      ↓
             ┌──────────────────┐
             │ Configure GPIO   │
             └────────┬─────────┘
                      ↓
             ┌──────────────────┐
             │ Configure UART0  │
             └────────┬─────────┘
                      ↓
             ┌──────────────────┐
             │ Receive Command  │
             └────────┬─────────┘
                      ↓
             ┌──────────────────┐
             │ Echo Command     │
             └────────┬─────────┘
                      ↓
                ┌─────┴─────┐
                ↓           ↓
             Command 1   Command 2
                ↓           ↓
              LED0        LED1
                │           │
                └─────┬─────┘
                      ↓
             Other Character
                      ↓
                LED0 + LED1
                      ↓
                 Repeat
```

---

# 🔌 Hardware Components

The prototype can be implemented using:

| Component | Purpose |
|---|---|
| LPC21xx ARM7 Microcontroller | Main controller |
| GSM Module | Wireless communication |
| LED 0 | Appliance 1 indication |
| LED 1 | Appliance 2 indication |
| Power Supply | Provides required power |
| Serial/UART connection | Communication interface |

> **Note:** In the current source code, LEDs are used as the output devices. For an actual home appliance implementation, the LED outputs can be connected to relay driver circuitry instead of directly driving high-power loads.

---

# 🧩 Microcontroller Used

## LPC21xx ARM7

The project uses the LPC21xx family of ARM7 microcontrollers.

The source code includes:

```c
#include <LPC21XX.H>
```

The microcontroller handles:

- GPIO control
- UART communication
- Command processing
- Device control



---

# 📡 UART0 Communication

UART stands for:

**Universal Asynchronous Receiver Transmitter**

UART provides serial communication between the LPC21xx microcontroller and the external GSM/serial interface.

The project uses:

```text
UART0
```

for both transmission and reception.

---

## UART0 Configuration

The project configures the UART using:

```c
PINSEL0 = 0X05;
U0LCR = 0X83;
U0DLL = 97;
U0LCR = 0X03;
```



### PINSEL0

```c
PINSEL0 = 0X05;
```

This configures the required LPC21xx pins for UART0 functionality.

---

### U0LCR

```c
U0LCR = 0X83;
```

This temporarily enables access to the divisor latch registers while configuring the UART.

---

### U0DLL

```c
U0DLL = 97;
```

The divisor value is configured to obtain the required UART baud rate for the system clock configuration.

---

### U0LCR Again

```c
U0LCR = 0X03;
```

This returns the UART to normal operation after baud-rate configuration.

---

# 📥 UART Receive Function

The project uses:

```c
unsigned char uart0_rx(void)
{
    while(((U0LSR&(1<<0))==0));
    return U0RBR;
}
```

The function waits until a character is received.

### U0LSR Bit 0

```c
U0LSR & (1<<0)
```

checks whether the **Receiver Data Ready** condition is set.

When data is available:

```c
return U0RBR;
```

reads the received character from the UART0 Receiver Buffer Register.



---

# 📤 UART Transmit Function

The project uses:

```c
void uart0_tx(unsigned char d)
{
    while(((U0LSR&(1<<5))==0));
    U0THR=d;
}
```

The function waits until the transmitter is ready and then places the character into:

```c
U0THR
```

which is the UART0 Transmit Holding Register.

---

# 💡 LED Control

The project defines two LED outputs:

```c
#define led0 1<<4
#define led1 1<<3
```

The direction register is configured using:

```c
IODIR0 = led0 | led1;
```

This makes the corresponding GPIO pins outputs.

---

# 🔢 Command Processing

The main program continuously receives characters:

```c
while(1)
{
    ch = uart0_rx();
    uart0_tx(ch);

    if(ch == '1')
    {
        IOCLR0 = led0;
    }
    else if(ch == '2')
    {
        IOCLR0 = led1;
    }
    else
    {
        IOSET0 = led0 | led1;
    }
}
```



### Command `'1'`

```c
if(ch == '1')
{
    IOCLR0 = led0;
}
```

The LED0 output is cleared.

### Command `'2'`

```c
else if(ch == '2')
{
    IOCLR0 = led1;
}
```

The LED1 output is cleared.

### Other Commands

```c
else
{
    IOSET0 = led0 | led1;
}
```

Both outputs are set.

---

# 🔄 System Operation

The complete operation can be summarized as:

```text
1. GSM/serial device sends a command
              ↓
2. UART0 receives the command
              ↓
3. LPC21xx reads U0RBR
              ↓
4. Command is echoed through UART0
              ↓
5. Microcontroller checks the command
              ↓
6. Corresponding GPIO is controlled
              ↓
7. Appliance output changes
```

---

# 🏠 Real-World Appliance Interface

For a real home automation system, the LEDs in the prototype can be replaced with relay driver circuits.

Example:

```text
LPC21xx
   │
   ↓
GPIO Output
   │
   ↓
Relay Driver
   │
   ↓
Relay
   │
   ↓
Home Appliance
```

Possible appliances include:

- 💡 Light
- 🌀 Fan
- 📺 Television
- 🔌 Socket
- 💧 Water pump

**Important:** Mains-voltage appliances should not be connected directly to LPC21xx GPIO pins. Proper relay/driver circuitry and electrical isolation are required.

---

# 🛠️ Technologies Used

| Technology | Purpose |
|---|---|
| Embedded C | Firmware development |
| LPC21xx ARM7 | Main microcontroller |
| UART0 | Serial communication |
| GSM | Wireless communication |
| GPIO | Appliance control |
| LED | Prototype output device |
| Keil / ARM toolchain | Embedded development |
| Hex file | Microcontroller programming |

The repository contains both the C source file and a compiled `.hex` file.

---

# 📁 Project Structure

The current repository contains:

```text
GSM-BASED-HOME-AUTOMATION/
│
├── README.md
├── mini1.c
└── mini2.hex
```



---

# 📄 File Description

| File | Description |
|---|---|
| `mini1.c` | Main Embedded C source code |
| `mini2.hex` | Compiled hexadecimal firmware file |
| `README.md` | Project documentation |

---

# 💻 Software Requirements

The project can be developed using an ARM/LPC21xx-compatible embedded development environment.

Recommended tools:

- Keil µVision
- ARM7/LPC21xx device support
- Embedded C compiler
- Flash/programming utility

---

# ⚙️ How to Build

## Step 1: Open the Source Code

Open:

```text
mini1.c
```

in the LPC21xx-compatible development environment.

---

## Step 2: Select the Microcontroller

Select the appropriate **LPC21xx ARM7 device**.

---

## Step 3: Build the Project

Compile the source code and generate the required object and hexadecimal files.

The repository already contains:

```text
mini2.hex
```

which is the compiled firmware file.

---

## Step 4: Program the Microcontroller

Use a suitable LPC21xx programming/debugging interface to flash the generated `.hex` file into the microcontroller.

---

## Step 5: Connect GSM/Serial Interface

Connect the GSM/serial communication interface to the UART0 pins of the LPC21xx according to the hardware design.

---

## Step 6: Send Commands

Send the appropriate characters through the GSM/UART communication interface.

Example:

```text
'1'
'2'
```

The LPC21xx processes the received command and controls the corresponding output.

---

# 🧪 Example Operation

### Command 1

```text
User → GSM/UART → '1'
                  ↓
              LPC21xx
                  ↓
               LED0
```

The corresponding GPIO output is cleared.

---

### Command 2

```text
User → GSM/UART → '2'
                  ↓
              LPC21xx
                  ↓
               LED1
```

The corresponding GPIO output is cleared.

---

### Other Character

```text
User → GSM/UART → Other Character
                    ↓
                 LPC21xx
                    ↓
              LED0 + LED1
```

Both outputs are set.

---

# 🧠 Important Registers Used

| Register | Purpose |
|---|---|
| `PINSEL0` | Selects pin functions |
| `IODIR0` | Configures GPIO direction |
| `IOSET0` | Sets GPIO output bits |
| `IOCLR0` | Clears GPIO output bits |
| `U0LCR` | UART0 Line Control Register |
| `U0DLL` | UART0 Divisor Latch Low |
| `U0LSR` | UART0 Line Status Register |
| `U0RBR` | UART0 Receiver Buffer Register |
| `U0THR` | UART0 Transmit Holding Register |

---

# 📚 Embedded Concepts Demonstrated

This project provides practical experience with:

- ARM7 architecture
- LPC21xx microcontroller
- Embedded C
- GPIO programming
- UART communication
- Serial data transmission
- Serial data reception
- UART registers
- Pin multiplexing
- Bit manipulation
- Register-level programming
- GSM communication concept
- Command-based control
- Hardware interfacing

---

# 🎓 Learning Outcomes

After completing this project, you can explain:

### What is UART?

UART is a serial communication peripheral used to transmit and receive data asynchronously.

### What is GSM?

GSM is a cellular communication technology that can be used to send and receive SMS messages and other communication services.

### Why use UART with GSM?

GSM modules commonly communicate with microcontrollers through serial interfaces such as UART. The microcontroller can send AT commands and receive responses through UART.

### What is GPIO?

GPIO stands for **General Purpose Input/Output**. It allows the microcontroller to control or read external hardware.

### What is `U0RBR`?

`U0RBR` is the UART0 Receiver Buffer Register used to read received data.

### What is `U0THR`?

`U0THR` is the UART0 Transmit Holding Register used to transmit data.

### What is `U0LSR`?

`U0LSR` provides the status of UART0, including whether received data is available and whether the transmitter is ready.

---

# ⚠️ Current Limitations

The current repository is a **basic prototype**, so it has some limitations:

1. Only two output devices are demonstrated.
2. LEDs are used instead of actual appliances.
3. The current source processes individual characters rather than complete SMS command strings.
4. There is no password/authentication mechanism in the current code.
5. There is no LCD status display.
6. There is no feedback SMS mechanism.
7. There is no sensor monitoring.
8. There is no automatic scheduling.
9. The repository currently contains only a basic UART command-control implementation.

These limitations provide opportunities for further development.

---

# 🚀 Future Enhancements

The system can be expanded into a complete GSM-based smart home controller.

### 📱 SMS-Based Commands

Implement complete SMS commands such as:

```text
LIGHT1 ON
LIGHT1 OFF
FAN ON
FAN OFF
ALL ON
ALL OFF
STATUS
```

---

### 🔐 Security

Add:

- Password authentication
- Authorized mobile numbers
- OTP verification
- Command validation

---

### 📟 LCD Display

Add an LCD to display:

```text
GSM STATUS
DEVICE 1: ON
DEVICE 2: OFF
```

---

### 🔌 More Appliances

Increase the number of controlled devices:

```text
Device 1 → Light
Device 2 → Fan
Device 3 → TV
Device 4 → Pump
```

---

### 📩 Feedback SMS

The system can send confirmation messages:

```text
LIGHT 1 TURNED ON
```

or:

```text
FAN TURNED OFF
```

---

### 🌡️ Sensor Integration

Sensors can be added for:

- Temperature
- Gas leakage
- Fire detection
- Motion detection
- Light intensity

The system can then send emergency SMS alerts.

---

### 🌐 IoT Upgrade

The project can later be extended with:

- Wi-Fi
- Cloud monitoring
- Mobile application
- Web dashboard
- IoT device control

---

# 🌟 Advantages

- 📱 Remote device control
- 📡 GSM-based communication
- 🌐 Does not require local Wi-Fi for basic GSM communication
- ⚡ Fast command processing
- 💰 Low-cost prototype
- 🔧 Easy to expand
- 🧠 Good embedded-systems learning project
- 🔌 Demonstrates microcontroller-to-device interfacing

---

# 🏭 Applications

The concept can be used for:

- 🏠 Home automation
- 🏢 Office automation
- 🏭 Industrial device control
- 🌾 Agricultural equipment control
- 💡 Remote lighting control
- 💧 Water pump control
- 🔒 Remote security systems

---

# 🎓 Project Type

**Embedded Systems / ARM7 / GSM / Home Automation Project**

### Domain

```text
Embedded Systems
ARM7 Microcontroller
LPC21xx
GSM Communication
UART
GPIO
Home Automation
```

---

# 👨‍💻 Author

**Dhanush R**

GitHub:

[Dhanush R — GitHub](https://github.com/dhanush02012000-sketch?utm_source=chatgpt.com)

Project Repository:

[GSM-BASED-HOME-AUTOMATION — GitHub](https://github.com/dhanush02012000-sketch/GSM-BASED-HOME-AUTOMATION?utm_source=chatgpt.com)

---

# 📜 License

This project is developed for **educational and learning purposes**.

---

# ⭐ Project Highlights

```text
✔ LPC21xx ARM7 Microcontroller
✔ Embedded C
✔ GSM Communication
✔ UART0
✔ GPIO Control
✔ LED/Appliance Control
✔ Command-Based Operation
✔ UART Receive
✔ UART Transmit
✔ Register-Level Programming
✔ Hardware Interfacing
✔ Hex Firmware Generation
```

---

## ⭐ Acknowledgement

This project was developed as a practical exercise in **Embedded C, LPC21xx ARM7 microcontroller programming, UART communication, GPIO control, GSM interfacing, and home automation**.

The current repository demonstrates the fundamental communication and control mechanism that can be expanded into a complete GSM-based home automation system.
