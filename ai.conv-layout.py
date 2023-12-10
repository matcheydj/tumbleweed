# Define the Morse Code dictionary
MORSE_CODE_DICT = {'A': '.-', 'B': '-...',
                    'C': '-.-.', 'D': '-..', 'E': '.',
                    'F': '..-.', 'G': '--.', 'H': '....',
                    'I': '..', 'J': '.---', 'K': '-.-',
                    'L': '.-..', 'M': '--', 'N': '-.',
                    'O': '---', 'P': '.--.', 'Q': '--.-',
                    'R': '.-.', 'S': '...', 'T': '-',
                    'U': '..-', 'V': '...-', 'W': '.--',
                    'X': '-..-', 'Y': '-.--', 'Z': '--..'}


# Generate random keyboard layouts
def generate_random_keyboard_layout(size=10):
    # Define possible characters
    characters = string.ascii_uppercase + string.ascii_lowercase + string.digits + string.punctuation + ' '
    return ''.join(random.sample(characters, size))


# Define functions for other keyboard layouts
def numbers_to_text(text):
    # Convert numbers to text
    return ''.join([chr(int(c) + ord('0')) for c in text])


def arabic_to_text(text):
    # Use a library like 'pyarabic' to convert Arabic text
    # (example implementation)
    import pyarabic.transliteration
    return pyarabic.transliteration.remove_diacritics(text)


def morse_to_text(morse_code):
    # Split Morse code into words and letters
    words = morse_code.split(' / ')
    decoded_message = ''

    for word in words:
        letters = word.split(' ')
        for letter in letters:
            # Get the key (letter) from the value (Morse code) in the dictionary
            decoded_letter = [key for key, value in MORSE_CODE_DICT.items() if value == letter]
            decoded_message += ''.join(decoded_letter)
        decoded_message += ' '

    return decoded_message


def assistive_type_to_text(text):
    # Define assistive type conversion logic here
    # This function needs further implementation based on the specific assistive type
    return text


# Define mappings for keyboard layouts and their functions
KEYBOARD_LAYOUTS = {
    'Morse code': morse_to_text,
    'Numbers': numbers_to_text,
    'Arabic': arabic_to_text,
    'Other assistive type': assistive_type_to_text,
}


def convert_to_html(text, keyboard_layout):
    # Convert text to HTML table
    rows = []
    for i, char in enumerate(text):
        converted_char = KEYBOARD_LAYOUTS[keyboard_layout](char)
        rows.append(f'<tr><td>{i+1}</td><td>{char}</td><td>{converted_char}</td></tr>')
    return f'<table><tr><th>Index</th><th>Character</th><th>Converted Text</th></tr>{"".join(rows)}</table>'


# Generate three random keyboard layouts
random_layouts = [generate_random_keyboard_layout() for _ in range(3)]

# Test the function with different keyboard layouts
for layout, text in [('Morse code', '... --- ... .--.'), ('Numbers', '12345'), ('Arabic', 'مرحبا'), ('Other assistive type', ':)')]:
    print(f'\nKeyboard layout: {layout}')
    print(convert_to_html(text, layout))

# Print the random keyboard layouts and their conversions
for layout in random_layouts:
    print(f'\nRandom keyboard layout: {layout}')
    print(convert_to_html(text, layout))
