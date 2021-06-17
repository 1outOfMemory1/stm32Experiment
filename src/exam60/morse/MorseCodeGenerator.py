letterMorseStr = ".- -... -.-. -.. . ..-. --. .... .. .--- -.- .-.. -- -. --- .--. --.- .-. ... - ..- ...- .-- -..- -.-- --.."
letterStr = "abcdefghijklmnopqrstuvwxyz"
letterMorseList = letterMorseStr.split(" ")
letter = "yinhaonan"
morseMap = {}
for (index, ele) in enumerate(letterMorseList):
    morseMap[letterStr[index]] = ele
print(morseMap)
parseLetterStr = "yinhaonan"
parseLetterStr = parseLetterStr.lower()
for ele in parseLetterStr:
    temp = morseMap[ele]
    # print(temp,ele)
    for abc in temp:
        if abc == '-':
            print(
                "HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin,GPIO_PIN_RESET);\nHAL_Delay(1000);\nHAL_GPIO_WritePin("
                "LED_GPIO_Port, LED_Pin,GPIO_PIN_SET);\nHAL_Delay(600);")
        else:
            print(
                "HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin,GPIO_PIN_RESET);\nHAL_Delay(100);\nHAL_GPIO_WritePin("
                "LED_GPIO_Port, LED_Pin,GPIO_PIN_SET);\nHAL_Delay(600);")
    print("HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin,GPIO_PIN_SET);\nHAL_Delay(1000);")

''' 短灯
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin,GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin,GPIO_PIN_SET);
    HAL_Delay(600);
'''

''' 长灯    
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin,GPIO_PIN_RESET);
    HAL_Delay(1000);
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin,GPIO_PIN_SET);
    HAL_Delay(600);
'''
''' 空隙间隔
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin,GPIO_PIN_SET);
    HAL_Delay(600);
'''
