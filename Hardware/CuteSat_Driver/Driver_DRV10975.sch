EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 6
Title "Thesis CubeSat Driver Board"
Date "2022-01-09"
Rev "V.2.0"
Comp "FIBO"
Comment1 "Design By Thansak Pongpaket"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:CP_Small C6
U 1 1 61CA839E
P 5400 3350
F 0 "C6" H 5488 3396 50  0000 L CNN
F 1 "100uF" H 5488 3305 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_6.3x5.4_Nichicon" H 5400 3350 50  0001 C CNN
F 3 "~" H 5400 3350 50  0001 C CNN
	1    5400 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 3200 4850 3200
Wire Wire Line
	5400 3200 5400 3250
Connection ~ 5400 3200
$Comp
L Device:L_Small L1
U 1 1 61CAC02B
P 3000 3500
F 0 "L1" V 3185 3500 50  0000 C CNN
F 1 "47uH" V 3094 3500 50  0000 C CNN
F 2 "Inductor_SMD:L_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 3000 3500 50  0001 C CNN
F 3 "~" H 3000 3500 50  0001 C CNN
	1    3000 3500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2750 3500 2850 3500
Wire Wire Line
	2850 3500 2850 3700
Connection ~ 2850 3500
Wire Wire Line
	2850 3500 2900 3500
Wire Wire Line
	2550 3600 2550 3500
$Comp
L Device:C_Small C4
U 1 1 61CB2A4C
P 3200 3150
F 0 "C4" V 2971 3150 50  0000 C CNN
F 1 "0.1uF" V 3062 3150 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 3200 3150 50  0001 C CNN
F 3 "~" H 3200 3150 50  0001 C CNN
	1    3200 3150
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C5
U 1 1 61CB4F54
P 3400 2900
F 0 "C5" H 3492 2946 50  0000 L CNN
F 1 "0.1uF" H 3492 2855 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 3400 2900 50  0001 C CNN
F 3 "~" H 3400 2900 50  0001 C CNN
	1    3400 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 3000 3400 3200
Wire Wire Line
	3300 3150 3300 3300
Wire Wire Line
	3100 3150 3100 3400
Wire Wire Line
	4850 3200 4850 3300
Wire Wire Line
	4850 3300 4800 3300
Connection ~ 4850 3200
Wire Wire Line
	4850 3200 5400 3200
Wire Wire Line
	4800 3400 4800 3500
Wire Wire Line
	4800 3600 4800 3700
Wire Wire Line
	4800 3800 4800 3900
Text Label 4900 3900 0    50   ~ 0
U
Text Label 4900 3700 0    50   ~ 0
V
Text Label 4900 3500 0    50   ~ 0
W
$Comp
L power:GNDPWR #PWR07
U 1 1 61CB9675
P 5400 4000
F 0 "#PWR07" H 5400 3800 50  0001 C CNN
F 1 "GNDPWR" H 5404 3846 50  0000 C CNN
F 2 "" H 5400 3950 50  0001 C CNN
F 3 "" H 5400 3950 50  0001 C CNN
	1    5400 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 4100 4800 4000
Text HLabel 8600 2650 0    50   Input ~ 0
D2_DIR
Text HLabel 8600 2750 0    50   Input ~ 0
D2_speed
$Comp
L power:GND #PWR04
U 1 1 61CBCB58
P 2500 4150
F 0 "#PWR04" H 2500 3900 50  0001 C CNN
F 1 "GND" H 2505 3977 50  0000 C CNN
F 2 "" H 2500 4150 50  0001 C CNN
F 3 "" H 2500 4150 50  0001 C CNN
	1    2500 4150
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C2
U 1 1 61CBE913
P 2700 3850
F 0 "C2" H 2792 3896 50  0000 L CNN
F 1 "1uF" H 2792 3805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 2700 3850 50  0001 C CNN
F 3 "~" H 2700 3850 50  0001 C CNN
	1    2700 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C3
U 1 1 61CC08EA
P 2700 4050
F 0 "C3" H 2792 4096 50  0000 L CNN
F 1 "1uF" H 2792 4005 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 2700 4050 50  0001 C CNN
F 3 "~" H 2700 4050 50  0001 C CNN
	1    2700 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 3600 2500 3600
Connection ~ 2550 3600
Wire Wire Line
	2700 3950 2500 3950
Wire Wire Line
	2500 3600 2500 3950
Connection ~ 2700 3950
Connection ~ 2500 3950
Wire Wire Line
	2500 3950 2500 4150
Wire Wire Line
	2950 3800 2950 3750
Wire Wire Line
	2950 3750 2700 3750
Wire Wire Line
	3050 3950 3050 3900
Wire Wire Line
	2700 3950 3050 3950
Text HLabel 8600 2450 0    50   BiDi ~ 0
D2_SCL
Wire Wire Line
	3050 4000 3050 4150
Wire Wire Line
	3050 4150 2700 4150
Text HLabel 8600 2550 0    50   BiDi ~ 0
D2_SDA
Text Label 9250 4800 2    50   ~ 0
U
Text Label 9250 5000 2    50   ~ 0
V
Text Label 9250 5200 2    50   ~ 0
W
Wire Wire Line
	4800 4000 5400 4000
Wire Wire Line
	4900 3900 4800 3900
Wire Wire Line
	4900 3700 4800 3700
Wire Wire Line
	4900 3500 4800 3500
Text HLabel 3500 2700 2    50   Input ~ 0
+12V
Wire Wire Line
	3500 2700 3400 2700
Wire Wire Line
	3400 2700 3400 2800
Text HLabel 5500 3100 2    50   Input ~ 0
+12V
Wire Wire Line
	5500 3100 5400 3100
Wire Wire Line
	5400 3100 5400 3200
Text Label 3100 4300 0    50   ~ 0
D2_FG
Text Notes 2200 2600 0    79   ~ 0
Driver
Text Label 9450 2450 2    50   ~ 0
D2_SCL_I
Text Label 9450 2550 2    50   ~ 0
D2_SDA_I
Text Label 9450 2650 2    50   ~ 0
D2_DIR_I
Text Label 9550 2750 2    50   ~ 0
D2_SPEED_I
Wire Wire Line
	9550 2750 9100 2750
Wire Wire Line
	9100 2650 9450 2650
Wire Wire Line
	9450 2550 9100 2550
Wire Wire Line
	9100 2450 9450 2450
Text Label 5150 4200 2    50   ~ 0
D2_DIR_I
Text Label 5250 4300 2    50   ~ 0
D2_SPEED_I
Wire Wire Line
	5250 4300 4800 4300
Wire Wire Line
	4800 4200 5150 4200
Wire Wire Line
	3050 4000 3400 4000
Wire Wire Line
	3050 3900 3400 3900
Wire Wire Line
	3400 3800 2950 3800
Wire Wire Line
	2850 3700 3400 3700
Wire Wire Line
	3400 3600 2550 3600
Wire Wire Line
	3100 3500 3400 3500
Wire Wire Line
	3100 3400 3400 3400
Wire Wire Line
	3300 3300 3400 3300
Text Label 3100 4200 0    50   ~ 0
D2_SDA_I
Text Label 3100 4100 0    50   ~ 0
D2_SCL_I
Wire Wire Line
	3100 4100 3400 4100
Wire Wire Line
	3100 4200 3400 4200
Wire Wire Line
	3100 4300 3400 4300
$Comp
L Connector:TestPoint TP1
U 1 1 61CB4D28
P 3100 4400
F 0 "TP1" H 3042 4426 50  0000 R CNN
F 1 "TestPoint" H 3042 4517 50  0000 R CNN
F 2 "TestPoint:TestPoint_Pad_D1.5mm" H 3300 4400 50  0001 C CNN
F 3 "~" H 3300 4400 50  0001 C CNN
	1    3100 4400
	-1   0    0    1   
$EndComp
Wire Wire Line
	3100 4300 3100 4400
Text Notes 7700 3800 0    79   ~ 0
Motor Connector
Text Notes 8050 2050 0    79   ~ 0
Jumper
$Comp
L Connector_Generic:Conn_02x04_Odd_Even J?
U 1 1 61D69B0E
P 8800 2550
AR Path="/61BB4768/61D69B0E" Ref="J?"  Part="1" 
AR Path="/61CA50D9/61D69B0E" Ref="J2"  Part="1" 
F 0 "J2" H 8850 2867 50  0000 C CNN
F 1 "Pin Header 2*4" H 8850 2776 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x04_P2.54mm_Vertical" H 8800 2550 50  0001 C CNN
F 3 "~" H 8800 2550 50  0001 C CNN
	1    8800 2550
	1    0    0    -1  
$EndComp
Wire Notes Line
	6200 5250 1750 5250
Wire Notes Line
	1750 5250 1750 2250
Wire Notes Line
	1750 2250 6200 2250
Wire Notes Line
	6200 2250 6200 5250
$Comp
L Device:C_Small C?
U 1 1 61E73322
P 2650 3500
AR Path="/61BB4768/61E73322" Ref="C?"  Part="1" 
AR Path="/61CA50D9/61E73322" Ref="C1"  Part="1" 
F 0 "C1" V 2900 3450 50  0000 L CNN
F 1 "22uF" V 2800 3400 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 2650 3500 50  0001 C CNN
F 3 "~" H 2650 3500 50  0001 C CNN
	1    2650 3500
	0    -1   -1   0   
$EndComp
Wire Notes Line
	7900 1850 7900 2900
Wire Notes Line
	7900 2900 9700 2900
Wire Notes Line
	9700 2900 9700 1850
Wire Notes Line
	9700 1850 7900 1850
$Comp
L 1-84953-1:1-84953-1 J?
U 1 1 61E8CEB8
P 8000 4200
AR Path="/61BB4768/61E8CEB8" Ref="J?"  Part="1" 
AR Path="/61CA50D9/61E8CEB8" Ref="J3"  Part="1" 
F 0 "J3" H 8500 4465 50  0000 C CNN
F 1 "1-84953-1" H 8500 4374 50  0000 C CNN
F 2 "1-84953-1:1849531" H 8850 4300 50  0001 L CNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=showdoc&DocId=Customer+Drawing%7F84953%7FA3%7Fpdf%7FEnglish%7FENG_CD_84953_A3.pdf%7F1-84953-5" H 8850 4200 50  0001 L CNN
F 4 "1MM FPC HORZ.TOP CONT.ASSY 11P" H 8850 4100 50  0001 L CNN "Description"
F 5 "2.74" H 8850 4000 50  0001 L CNN "Height"
F 6 "TE Connectivity" H 8850 3900 50  0001 L CNN "Manufacturer_Name"
F 7 "1-84953-1" H 8850 3800 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "571-1-84953-1" H 8850 3700 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.co.uk/ProductDetail/TE-Connectivity/1-84953-1?qs=uUkeXfjQ8uQbyHjuXR99Yw%3D%3D" H 8850 3600 50  0001 L CNN "Mouser Price/Stock"
F 10 "1-84953-1" H 8850 3500 50  0001 L CNN "Arrow Part Number"
F 11 "https://www.arrow.com/en/products/1-84953-1/te-connectivity" H 8850 3400 50  0001 L CNN "Arrow Price/Stock"
	1    8000 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	9250 5200 9000 5200
Wire Wire Line
	9000 5100 9000 5200
Connection ~ 9000 5200
Wire Wire Line
	9000 5000 9000 4900
Wire Wire Line
	9000 5000 9250 5000
Connection ~ 9000 5000
Wire Wire Line
	9250 4800 9000 4800
Wire Wire Line
	9000 4700 9000 4800
Connection ~ 9000 4800
$Comp
L power:GND #PWR?
U 1 1 61E8CEC7
P 7900 4400
AR Path="/61BB4768/61E8CEC7" Ref="#PWR?"  Part="1" 
AR Path="/61CA50D9/61E8CEC7" Ref="#PWR070"  Part="1" 
F 0 "#PWR070" H 7900 4150 50  0001 C CNN
F 1 "GND" H 7905 4227 50  0000 C CNN
F 2 "" H 7900 4400 50  0001 C CNN
F 3 "" H 7900 4400 50  0001 C CNN
	1    7900 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 4300 7900 4300
Wire Wire Line
	7900 4300 7900 4400
Wire Wire Line
	8000 4200 7900 4200
Wire Wire Line
	7900 4200 7900 4300
Connection ~ 7900 4300
$Comp
L power:GND #PWR?
U 1 1 61E8CED2
P 9450 4600
AR Path="/61BB4768/61E8CED2" Ref="#PWR?"  Part="1" 
AR Path="/61CA50D9/61E8CED2" Ref="#PWR071"  Part="1" 
F 0 "#PWR071" H 9450 4350 50  0001 C CNN
F 1 "GND" H 9455 4427 50  0000 C CNN
F 2 "" H 9450 4600 50  0001 C CNN
F 3 "" H 9450 4600 50  0001 C CNN
	1    9450 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9450 4600 9000 4600
$Comp
L Connector:Conn_01x04_Male J?
U 1 1 61E8CED9
P 9200 4400
AR Path="/61BB4768/61E8CED9" Ref="J?"  Part="1" 
AR Path="/61CA50D9/61E8CED9" Ref="J8"  Part="1" 
F 0 "J8" H 9172 4282 50  0000 R CNN
F 1 "Pin Header 4p" H 9172 4373 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 9200 4400 50  0001 C CNN
F 3 "~" H 9200 4400 50  0001 C CNN
	1    9200 4400
	-1   0    0    1   
$EndComp
Wire Notes Line
	7550 3550 7550 5500
Wire Notes Line
	7550 5500 10000 5500
Wire Notes Line
	10000 5500 10000 3550
Wire Notes Line
	10000 3550 7550 3550
Connection ~ 4800 4000
Connection ~ 4800 3900
Connection ~ 4800 3700
Connection ~ 4800 3500
$Comp
L SamacSys_Parts:DRV10975ZPWPR IC1
U 1 1 61CA5364
P 3400 3200
F 0 "IC1" H 4100 3465 50  0000 C CNN
F 1 "DRV10975ZPWPR" H 4100 3374 50  0000 C CNN
F 2 "SamacSys_Parts:SOP65P640X120-25N" H 4650 3300 50  0001 L CNN
F 3 "http://www.ti.com/lit/gpn/drv10975" H 4650 3200 50  0001 L CNN
F 4 "12-V, 3-Phase, Sensorless BLDC Motor Controller" H 4650 3100 50  0001 L CNN "Description"
F 5 "1.2" H 4650 3000 50  0001 L CNN "Height"
F 6 "Texas Instruments" H 4650 2900 50  0001 L CNN "Manufacturer_Name"
F 7 "DRV10975ZPWPR" H 4650 2800 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "595-DRV10975ZPWPR" H 4650 2700 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.co.uk/ProductDetail/Texas-Instruments/DRV10975ZPWPR?qs=OfeFRKQgECjndtjc01v%2Fzg%3D%3D" H 4650 2600 50  0001 L CNN "Mouser Price/Stock"
F 10 "DRV10975ZPWPR" H 4650 2500 50  0001 L CNN "Arrow Part Number"
F 11 "https://www.arrow.com/en/products/drv10975zpwpr/texas-instruments?region=nac" H 4650 2400 50  0001 L CNN "Arrow Price/Stock"
	1    3400 3200
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR0105
U 1 1 61EFCE00
P 5400 3450
F 0 "#PWR0105" H 5400 3250 50  0001 C CNN
F 1 "GNDPWR" H 5404 3296 50  0000 C CNN
F 2 "" H 5400 3400 50  0001 C CNN
F 3 "" H 5400 3400 50  0001 C CNN
	1    5400 3450
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR0101
U 1 1 61E87DF0
P 4100 4800
F 0 "#PWR0101" H 4100 4600 50  0001 C CNN
F 1 "GNDPWR" H 4104 4646 50  0000 C CNN
F 2 "" H 4100 4750 50  0001 C CNN
F 3 "" H 4100 4750 50  0001 C CNN
	1    4100 4800
	1    0    0    -1  
$EndComp
$EndSCHEMATC
