from gpiozero import LED
from gpiozero import PWMLED
from gpiozero import Button
from time import sleep
from signal import pause

# 17 = red
# 27 = green
# 22 = blue
ledred = PWMLED(17)
red = LED(17)
green = LED(27)
ledgreen = PWMLED(27)
blue = LED(22)
ledblue = PWMLED(22)
button = Button(12, bounce_time=0.2)
cnt = 0

def lightble():
	ledblue = 0
	sleep(0.2)
	ledblue = 0.5
	sleep(0.2)
	ledblue = 1
	sleep(0.2)
	return

def lightgre():
	ledgreen = 0
	sleep(0.2)
	ledgreen = 0.5
	sleep(0.2)
	ledgreen = 1
	sleep(0.2)
	return

def lightred():
	ledred = 0
	sleep(0.2)
	ledred = 0.5
	sleep(0.2)
	ledred = 1
	sleep(0.2)
	return
def check():
	if button.is_pressed:
		cnt = (cnt + 1) % 2
		return True
	else:
		return False

def breathing():
	while True:
		if check(): 
			break
		lightred()
		if check(): 
			break
		lightgre()
		if check():
			break
		lightble()
	return 
	
def staying():
	while True:
		if check():
			break
	return 
	
def lighting():
	while True:
		red.blank()
		sleep(1)
	return 

if __name__ == '__main__':
	while True:
		if cnt % 2 == 1:
			breathing()
		else:
			staying()

		