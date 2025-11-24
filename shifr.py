# Шифрует текст
def shifr(text):

    shifr_key = 'АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЬЫЪЭЮЯ'

    text = text.upper()

    result = ""

    for element in text:
        if shifr_key.find(element) >= 26:
            result += shifr_key[shifr_key.find(element) - 26]
        else:
            result += shifr_key[shifr_key.find(element) + 7]

    return result


# Дешифрует текст
def deshifr(text):

    shifr_key = 'АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЬЫЪЭЮЯ'

    text = text.upper()

    result = ""

    for element in text:
        if shifr_key.find(element) < 7:
            result += shifr_key[shifr_key.find(element) + 26]
        else:
            result += shifr_key[shifr_key.find(element) - 7]

    return result
