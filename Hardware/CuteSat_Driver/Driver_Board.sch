EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 6
Title "Thesis CubeSat Driver Board"
Date "2022-01-09"
Rev "V.2.0"
Comp "FIBO"
Comment1 "Design By Thansak Pongpaket"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 2000 3000 2000 1500
U 61CA50D9
F0 "Driver_DRV10975" 50
F1 "Driver_DRV10975.sch" 50
F2 "D2_DIR" I L 2000 3400 50 
F3 "D2_speed" I L 2000 3300 50 
F4 "D2_SCL" B R 4000 3300 50 
F5 "D2_SDA" B R 4000 3200 50 
F6 "+12V" I R 4000 3950 50 
$EndSheet
$Sheet
S 8350 1000 2000 1500
U 61CE4997
F0 "BusProtection" 50
F1 "BusProtection.sch" 50
F2 "I2C_SDA1" B R 10350 1500 50 
F3 "I2C_SDA" B L 8350 1700 50 
F4 "I2C_SCL1" B R 10350 1600 50 
F5 "I2C_SCL" B L 8350 1800 50 
F6 "I2C_SDA2" B R 10350 1850 50 
F7 "I2C_SCL2" B R 10350 1950 50 
$EndSheet
Text Label 10850 1500 2    50   ~ 0
sda_power1
Text Label 10850 1850 2    50   ~ 0
sda_power2
Text Label 10850 1950 2    50   ~ 0
scl_power2
Text Label 10850 1600 2    50   ~ 0
scl_power1
Text Label 7500 1450 2    50   ~ 0
sda_power1
Text Label 7500 1800 2    50   ~ 0
sda_power2
Text Label 7500 1900 2    50   ~ 0
scl_power2
Text Label 7500 1550 2    50   ~ 0
scl_power1
$Sheet
S 5000 1000 2000 1500
U 61BB7DDA
F0 "Power_Monitoring" 50
F1 "Power_Monitoring.sch" 50
F2 "Alert_INA238_2" O L 5000 1350 50 
F3 "Alert_INA238_1" O L 5000 1250 50 
F4 "Out_Sense2" O L 5000 1650 50 
F5 "Out_Sense1" O L 5000 1550 50 
F6 "+12_Driver1" O L 5000 1900 50 
F7 "+12_Driver2" O L 5000 2050 50 
F8 "+12_System" O L 5000 2200 50 
F9 "CS1_SDA" B R 7000 1450 50 
F10 "CS1_SCL" B R 7000 1550 50 
F11 "CS2_SDA" B R 7000 1800 50 
F12 "CS2_SCL" B R 7000 1900 50 
$EndSheet
$Sheet
S 1900 1000 2000 1500
U 61BB4768
F0 "Driver_MCF8316A" 50
F1 "Driver_MCF8316A.sch" 50
F2 "D1_DRVOFF" I L 1900 1750 50 
F3 "D1_SPEED" I L 1900 1350 50 
F4 "D1_SDA" B R 3900 1250 50 
F5 "D1_SCL" B R 3900 1350 50 
F6 "D1_DIR" I L 1900 1450 50 
F7 "D1_BREAK" I L 1900 1550 50 
F8 "+12V" I R 3900 1900 50 
$EndSheet
Text Label 4200 1250 2    50   ~ 0
SDA_D1
Text Label 4200 1350 2    50   ~ 0
SCL_D1
Text Label 4050 3200 0    50   ~ 0
SDA_D2
Text Label 4050 3300 0    50   ~ 0
SCL_D2
Wire Wire Line
	4050 3200 4000 3200
Wire Wire Line
	4050 3300 4000 3300
Text Label 7850 1700 0    50   ~ 0
SDA_Buspro
Text Label 7850 1800 0    50   ~ 0
SCL_Buspro
Wire Wire Line
	7850 1700 8350 1700
Wire Wire Line
	7850 1800 8350 1800
Text Label 3550 5650 2    50   ~ 0
SCL_D1
Text Label 3550 5750 2    50   ~ 0
SDA_D2
Text Label 3550 5850 2    50   ~ 0
SCL_D2
Text Label 3550 5950 2    50   ~ 0
SDA_Buspro
Text Label 3550 6050 2    50   ~ 0
SCL_Buspro
Text Label 4800 2200 0    50   ~ 0
12V
Wire Wire Line
	4800 2200 5000 2200
Text Label 2350 6350 0    50   ~ 0
12V
$Comp
L power:GND #PWR01
U 1 1 61F21E55
P 2450 6550
F 0 "#PWR01" H 2450 6300 50  0001 C CNN
F 1 "GND" H 2455 6377 50  0000 C CNN
F 2 "" H 2450 6550 50  0001 C CNN
F 3 "" H 2450 6550 50  0001 C CNN
	1    2450 6550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 6550 2450 6450
Wire Wire Line
	2450 6450 2550 6450
Wire Wire Line
	2350 6350 2550 6350
Text Label 3550 5550 2    50   ~ 0
SDA_D1
Wire Wire Line
	3050 5550 3550 5550
Wire Wire Line
	3550 5650 3050 5650
Wire Wire Line
	3050 5750 3550 5750
Wire Wire Line
	3550 5850 3050 5850
Wire Wire Line
	3050 5950 3550 5950
Wire Wire Line
	3550 6050 3050 6050
Text Label 1550 3300 0    50   ~ 0
D2_SPEED
Text Label 1550 3400 0    50   ~ 0
D2_DIR
Wire Wire Line
	1550 3300 2000 3300
Wire Wire Line
	1550 3400 2000 3400
Text Label 1450 1350 0    50   ~ 0
D1_SPEED
Text Label 1450 1450 0    50   ~ 0
D1_DIR
Wire Wire Line
	1450 1350 1900 1350
Wire Wire Line
	1450 1450 1900 1450
Text Label 1450 1550 0    50   ~ 0
D1_BREAK
Wire Wire Line
	1450 1550 1900 1550
Text Label 2100 5550 0    50   ~ 0
D1_SPEED
Text Label 2100 5650 0    50   ~ 0
D1_DIR
Wire Wire Line
	2100 5550 2550 5550
Wire Wire Line
	2100 5650 2550 5650
Text Label 2100 5750 0    50   ~ 0
D1_BREAK
Wire Wire Line
	2100 5750 2550 5750
Wire Wire Line
	1450 1750 1900 1750
Text Label 1450 1750 0    50   ~ 0
D1_DRVOFF
Wire Wire Line
	2100 5850 2550 5850
Text Label 2100 5850 0    50   ~ 0
D1_DRVOFF
Text Label 2100 5950 0    50   ~ 0
D2_SPEED
Text Label 2100 6050 0    50   ~ 0
D2_DIR
Wire Wire Line
	2100 5950 2550 5950
Wire Wire Line
	2100 6050 2550 6050
Text Label 4500 1250 0    50   ~ 0
AL_INA238_1
Text Label 4500 1350 0    50   ~ 0
AL_INA238_2
Text Label 4450 1550 0    50   ~ 0
ToADC_Sense1
Text Label 4450 1650 0    50   ~ 0
ToADC_Sense2
Wire Wire Line
	4450 1550 5000 1550
Wire Wire Line
	4450 1650 5000 1650
Wire Wire Line
	4500 1350 5000 1350
Wire Wire Line
	4500 1250 5000 1250
Wire Wire Line
	3900 1250 4200 1250
Wire Wire Line
	3900 1350 4200 1350
Wire Wire Line
	7000 1450 7500 1450
Wire Wire Line
	7000 1550 7500 1550
Wire Wire Line
	7000 1800 7500 1800
Wire Wire Line
	7000 1900 7500 1900
Wire Wire Line
	10350 1500 10850 1500
Wire Wire Line
	10350 1600 10850 1600
Wire Wire Line
	10350 1850 10850 1850
Wire Wire Line
	10350 1950 10850 1950
Text Label 2050 6150 0    50   ~ 0
AL_INA238_1
Text Label 2050 6250 0    50   ~ 0
AL_INA238_2
Wire Wire Line
	2050 6250 2550 6250
Wire Wire Line
	2050 6150 2550 6150
Text Label 3600 6150 2    50   ~ 0
ToADC_Sense1
Text Label 3600 6250 2    50   ~ 0
ToADC_Sense2
Wire Wire Line
	3050 6150 3600 6150
Wire Wire Line
	3050 6250 3600 6250
$Comp
L power:+3.3V #PWR02
U 1 1 61F8B289
P 3050 6350
F 0 "#PWR02" H 3050 6200 50  0001 C CNN
F 1 "+3.3V" V 3050 6450 50  0000 L CNN
F 2 "" H 3050 6350 50  0001 C CNN
F 3 "" H 3050 6350 50  0001 C CNN
	1    3050 6350
	0    1    1    0   
$EndComp
$Sheet
S 7150 4000 2000 1500
U 61F8D618
F0 "Power Input & Filter" 79
F1 "Power Input & Filter.sch" 79
$EndSheet
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 61FF1403
P 5050 5500
F 0 "H1" V 5287 5503 50  0000 C CNN
F 1 "MountingHole_Pad" V 5196 5503 50  0000 C CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 5050 5500 50  0001 C CNN
F 3 "~" H 5050 5500 50  0001 C CNN
	1    5050 5500
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 61FF2401
P 5050 5900
F 0 "H2" V 5287 5903 50  0000 C CNN
F 1 "MountingHole_Pad" V 5196 5903 50  0000 C CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 5050 5900 50  0001 C CNN
F 3 "~" H 5050 5900 50  0001 C CNN
	1    5050 5900
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H3
U 1 1 61FF296B
P 5050 6300
F 0 "H3" V 5287 6303 50  0000 C CNN
F 1 "MountingHole_Pad" V 5196 6303 50  0000 C CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 5050 6300 50  0001 C CNN
F 3 "~" H 5050 6300 50  0001 C CNN
	1    5050 6300
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H4
U 1 1 61FF2E55
P 5050 6700
F 0 "H4" V 5287 6703 50  0000 C CNN
F 1 "MountingHole_Pad" V 5196 6703 50  0000 C CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 5050 6700 50  0001 C CNN
F 3 "~" H 5050 6700 50  0001 C CNN
	1    5050 6700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5150 5500 5500 5500
Wire Wire Line
	5500 5500 5500 5900
Wire Wire Line
	5500 6700 5150 6700
Wire Wire Line
	5150 6300 5500 6300
Connection ~ 5500 6300
Wire Wire Line
	5500 6300 5500 6700
Wire Wire Line
	5500 5900 5150 5900
Connection ~ 5500 5900
Wire Wire Line
	5500 5900 5500 6300
Wire Wire Line
	5500 6700 5500 6800
Connection ~ 5500 6700
$Comp
L power:GND #PWR03
U 1 1 61FFBDE6
P 5500 6800
F 0 "#PWR03" H 5500 6550 50  0001 C CNN
F 1 "GND" H 5505 6627 50  0000 C CNN
F 2 "" H 5500 6800 50  0001 C CNN
F 3 "" H 5500 6800 50  0001 C CNN
	1    5500 6800
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x10_Odd_Even J1
U 1 1 61D5BE9B
P 2750 5950
F 0 "J1" H 2800 6567 50  0000 C CNN
F 1 "Pin header 2*10p" H 2800 6476 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x10_P2.54mm_Vertical" H 2750 5950 50  0001 C CNN
F 3 "~" H 2750 5950 50  0001 C CNN
	1    2750 5950
	1    0    0    -1  
$EndComp
Text Label 4700 1900 0    50   ~ 0
12V_D1
Text Label 4700 2050 0    50   ~ 0
12V_D2
Text Label 4200 1900 2    50   ~ 0
12V_D1
Text Label 4350 3950 2    50   ~ 0
12V_D2
Wire Wire Line
	4350 3950 4000 3950
Wire Wire Line
	4700 1900 5000 1900
Wire Wire Line
	4700 2050 5000 2050
Wire Wire Line
	3900 1900 4200 1900
$Comp
L power:+5VA #PWR0104
U 1 1 61E850F4
P 3050 6450
F 0 "#PWR0104" H 3050 6300 50  0001 C CNN
F 1 "+5VA" V 3050 6550 50  0000 L CNN
F 2 "" H 3050 6450 50  0001 C CNN
F 3 "" H 3050 6450 50  0001 C CNN
	1    3050 6450
	0    1    1    0   
$EndComp
$EndSCHEMATC
