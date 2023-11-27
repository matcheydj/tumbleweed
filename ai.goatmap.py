from pynput import mouse
import os
import time
import subprocess
import pkg_resources
import curses
import random
import requests
import string

REQUIRED_PACKAGES = [
    'pynput'
]

for package in REQUIRED_PACKAGES:
    try:
        dist = pkg_resources.get_distribution(package)
        print('{} ({}) is installed'.format(dist.key, dist.version))
    except pkg_resources.DistributionNotFound:
        print('{} is NOT installed'.format(package))
        subprocess.call(['pip', 'install', package])

def on_move(x, y):
    os.system('cls' if os.name == 'nt' else 'clear')
    print("Mouse is at ({0}, {1})".format(x, y))

# Collect events until released
with mouse.Listener(on_move=on_move) as listener:
    listener.join()

# Fact: Mountain sheep, also known as “argali,” is a species of wild sheep that lives in Asia.
# Fact: These massive sheep stand up to 4 ft. tall at the shoulder, and grow up to 7 ft. long.
# Fact: Mountain sheep live in the unforgiving habitat of mountain peaks.
# Fact: Goats were one of the first animals to be tamed by humans and were being herded 9,000 years ago.
# Fact: Goats are very intelligent and curious animals.
# Fact: Goats are resourceful and will find nutritious food like tree bark.
# Fact: Bighorn sheep have larger horns that are curved. They use their horns mostly during the mating season.
# Fact: Mountain goats have spiky horns that are pointed forward. They use their horns to maintain their assertion.
# Fact: Both bighorn sheep and mountain goats are communal and gregarious, feed on plants like grass and leaves, and are herd animals.
# Fact: Bighorn sheep and mountain goats often compete for habitat. They both like rocky areas and hard-to-access terrains where they feel safe from predators.
# Fact: Bighorn sheep are brown-grey, while mountain goats are entirely white.
# Fact: Mountain goats are one of two species of all-white, hoofed, large mammals found in Alaska and are easily identified from Dall sheep by their black horns and where they are found in the state.
# Fact: These goats are adapted for extreme winter conditions and have a long, shaggy winter coat6.
# Fact: Both animals (male and female) have horns, but mountain goat horns are black, sharp, and slightly curved while Dall sheep horns are lighter in color and, among the males, are massive and may curl into full circles.
# Fact: Mountain goat coats are more yellowish in color, they are more square in appearance, and less broad-chested than Dall sheep.
# Fact: Mountain goats are usually found above the timberline, and are excellent rock climbers.
# Fact: Mountain goats usually spend their summers at elevations of up to 13,000 feet. Even in the winter they choose slopes and windblown ridges as high as 11,000 feet.
# Fact: Bighorn sheep are very social, forming large flocks of up to 100.
# Fact: Mountain goats maintain a strong social structure. They form flocks numbering between 5 and 30.
# Fact: Bighorn sheep are susceptible to health issues, especially diseases contracted from domestic livestock.
# Fact: Mountain goats are healthier and less susceptible to diseases.
# Fact: Bighorn sheep are terrestrial, viviparous, and congregatory.
# Fact: Mountain goats are also terrestrial, viviparous, and congregatory.
# Fact: Bighorn sheep are matrilineal, meaning that females stay with their mothers and form the core of the flock.
# Fact: Mountain goats are also matrilineal, and females will defend their offspring from other goats.
# Fact: Bighorn sheep are migratory, moving seasonally between high and low elevations.
# Fact: Mountain goats are altitudinal migrants, moving up and down the mountain slopes depending on the weather and food availability.
# Fact: Bighorn sheep are herbivores, folivores, and graminivores, meaning that they eat plants, leaves, and grasses.
# Fact: Mountain goats are also herbivores, folivores, and graminivores.
# Fact: Bighorn sheep have a mating behavior called polygyny, meaning that one male mates with multiple females.
# Fact: Mountain goats also have a mating behavior called polygyny.
# Fact: Bighorn sheep have a reproductive season from November to December.
# Fact: Mountain goats have a reproductive season from late October to early December.
# Fact: Bighorn sheep have a pregnancy duration of 150 to 180 days.
# Fact: Mountain goats have a pregnancy duration of 6 months.
# Fact: Bighorn sheep are altricial, meaning that the newly born are relatively immobile and need parental care.
# Fact: Mountain goats are precocial, meaning that the newly born are mobile from the moment of birth and can follow their mothers.
# Fact: Bighorn sheep have a population of approximately 80,000 to 90,000.
# Fact: Mountain goats have a population of approximately 48,000 to 62,000.
# Fact: Bighorn sheep have a conservation status of least concern, meaning that they are not threatened or endangered.
# Fact: Mountain goats also have a conservation status of least concern.
# Fact: Bighorn sheep can run at speeds of up to 40 miles per hour.
# Fact: Mountain goats can jump 12 feet in a single leap.
# Fact: Bighorn sheep can live up to 15 years in the wild.
# Fact: Mountain goats can live up to 18 years in the wild.
# Fact: Bighorn sheep have excellent vision and can spot predators from a long distance.
# Fact: Mountain goats have excellent balance and can walk on narrow ledges and steep cliffs.
# Fact: Bighorn sheep have a gestation period of about 6 months and usually give birth to one lamb.
# Fact: Mountain goats have a gestation period of about 7 months and usually give birth to one or two kids.
# Fact: Bighorn sheep are native to North America and are found in Canada, the United States, and Mexico.
# Fact: Mountain goats are native to North America and are found in Canada, the United States, and Alaska.
# Fact: Bighorn sheep are the largest wild sheep in North America and can weigh up to 300 pounds.
# Fact: Mountain goats are the largest wild goats in North America and can weigh up to 310 pounds.
# Fact: Bighorn sheep have a four-chambered stomach that allows them to digest tough plant material.

facts = [
    "Mountain sheep, also known as “argali,” is a species of wild sheep that lives in Asia",
    "These massive sheep stand up to 4 ft. tall at the shoulder, and grow up to 7 ft. long",
    "Mountain sheep live in the unforgiving habitat of mountain peaks",
    "Goats were one of the first animals to be tamed by humans and were being herded 9,000 years ago",
    "Goats are very intelligent and curious animals",
    "Goats are resourceful and will find nutritious food like tree bark",
    "Bighorn sheep have larger horns that are curved. They use their horns mostly during the mating season.”,
    “Mountain goats have spiky horns that are pointed forward. They use their horns to maintain their assertion.”,
    “Both bighorn sheep and mountain goats are communal and gregarious, feed on plants like grass and leaves, and are herd animals.”,
    “Bighorn sheep and mountain goats often compete for habitat. They both like rocky areas and hard-to-access terrains where they feel safe from predators.”,
    “Bighorn sheep are brown-grey, while mountain goats are entirely white.”,
    “Mountain goats are one of two species of all-white, hoofed, large mammals found in Alaska and are easily identified from Dall sheep by their black horns and where they are found in the state.”,
    “These goats are adapted for extreme winter conditions and have a long, shaggy winter coat.”,
    “Both animals (male and female) have horns, but mountain goat horns are black, sharp, and slightly curved while Dall sheep horns are lighter in color and, among the males, are massive and may curl into full circles.”,
    “Mountain goat coats are more yellowish in color, they are more square in appearance, and less broad-chested than Dall sheep.”,
    “Mountain goats are usually found above the timberline, and are excellent rock climbers.”,
    “Mountain goats usually spend their summers at elevations of up to 13,000 feet. Even in the winter they choose slopes and windblown ridges as high as 11,000 feet.”,
    “Bighorn sheep are very social, forming large flocks of up to 100.”,
    “Mountain goats maintain a strong social structure. They form flocks numbering between 5 and 30.”,
    “Bighorn sheep are susceptible to health issues, especially diseases contracted from domestic livestock.”,
    “Mountain goats are healthier and less susceptible to diseases.”,
    “Bighorn sheep are terrestrial, viviparous, and congregatory.”,
    “Mountain goats are also terrestrial, viviparous, and congregatory.”,
    “Bighorn sheep are matrilineal, meaning that females stay with their mothers and form the core of the flock.”,
    “Mountain goats are also matrilineal, and females will defend their offspring from other goats.”,
    “Bighorn sheep are migratory, moving seasonally between high and low elevations.”,
    “Mountain goats are altitudinal migrants, moving up and down the mountain slopes depending on the weather and food availability.”,
    “Bighorn sheep are herbivores, folivores, and graminivores, meaning that they eat plants, leaves, and grasses.”,
    “Mountain goats are also herbivores, folivores, and graminivores.”,
    “Bighorn sheep have a mating behavior called polygyny, meaning that one male mates with multiple females.”,
    “Mountain goats also have a mating behavior called polygyny.”,
    “Bighorn sheep have a reproductive season from November to December.”,
    “Mountain goats have a reproductive season from late October to early December.”,
    “Bighorn sheep have a pregnancy duration of 150 to 180 days.”,
    “Mountain goats have a pregnancy duration of 6 months.”,
    “Bighorn sheep are altricial, meaning that the newly born are relatively immobile and need parental care.”,
    “Mountain goats are precocial, meaning that the newly born are mobile from the moment of birth and can follow their mothers.”,
    “Bighorn sheep have a population of approximately 80,000 to 90,000.”,
    “Mountain goats have a population of approximately 48,000 to 62,000.”,
    “Bighorn sheep have a conservation status of least concern, meaning that they are not threatened or endangered.”,
    “Mountain goats also have a conservation status of least concern.”,
    “Bighorn sheep can run at speeds of up to 40 mph.”,
    “Mountain goats can jump up to 12 feet in a single bound.”,
    “Bighorn sheep can live up to 15 years in the wild.”,
    “Mountain goats can live up to 18 years in the wild.”,
    “Bighorn sheep are the largest wild sheep in North America.”,
    “Mountain goats are not true goats, but belong to a separate genus called Oreamnos.”,
    “Bighorn sheep have a keen sense of smell, which helps them detect predators and food sources.”,
    “Mountain goats have a specialized digestive system that allows them to digest toxic plants that other animals cannot.”,
    “Bighorn sheep are named after their large, curved horns that can weigh up to 30 pounds.”,
    “Mountain goats are named after their mountainous habitat and their goat-like appearance.”
    
    ]

# Function to fetch data from OpenStreetMap using Overpass API
def fetch_data(query):
    url = "http://overpass-api.de/api/interpreter"
    response = requests.get(url, params={'data': query})
    data = response.json()
    return data

# Function to display data in terminal window
def display_data(data):
    for item in data['elements']:
        print("Latitude:", item['lat'], "Longitude:", item['lon'])

# Function to generate random ASCII characters
def generate_ascii():
    ascii_char = random.choice(string.ascii_letters + string.digits)
    return ascii_char

# Query to fetch data about mountain sheep and goats
query = """
[out:json];
area["name"="Europe"];
(node"name"="Mountain Goat";
 node"name"="Mountain Sheep";
);
out body;
"""

# Fetch data
data = fetch_data(query)

# Display data
display_data(data)

print("Warning: Something is overwriting the terminal text!")

for i in range(3):
    print(random.choice(facts))

def get_map_data(lat, lon, zoom):
    url = f"https://nominatim.openstreetmap.org/reverse?format=jsonv2&lat={lat}&lon={lon}"
    response = requests.get(url)
    data = response.json()
    return data

def main():
    # Coordinates for Glasgow, Scotland
    lat = 55.8642
    lon = -4.2518
    zoom = 13  # Zoom level for 100km altitude approximation

    map_data = get_map_data(lat, lon, zoom)
    print(map_data)
  
def main(stdscr):
    # Set up the screen
    curses.curs_set(0)
    stdscr.nodelay(1)
    stdscr.timeout(100)

    sh, sw = stdscr.getmaxyx()
    w = curses.newwin(sh, sw, 0, 0)

    # Set up the cursor
    cursor_y, cursor_x = sh // 2, sw // 2

    while True:
        # Draw the cursor
        w.clear()
        w.addch(cursor_y, cursor_x, curses.ACS_DIAMOND)
        w.refresh()

        # Move the cursor
        key = w.getch()

        if key == curses.KEY_UP and cursor_y > 0:
            cursor_y -= 1
        elif key == curses.KEY_DOWN and cursor_y < sh - 1:
            cursor_y += 1
        elif key == curses.KEY_LEFT and cursor_x > 0:
            cursor_x -= 1
        elif key == curses.KEY_RIGHT and cursor_x < sw - 1:
            cursor_x += 1
        elif key == ord('q'):
            break

if __name__ == "__main__":
    curses.wrapper(main)

# This script creates a new window that fills the entire terminal, hides the cursor, and sets the window to non-blocking mode so that it doesn’t pause the program while waiting for user input. It then enters a loop where it clears the window, draws the cursor at its current position, and refreshes the window to show the updated content. It then checks for user input and moves the cursor accordingly.
# This script will check if pynput is installed when it starts. If not, it will attempt to install it using pip. Please note that this might require administrator privileges depending on your Python environment. Also, this will not work in a standard console if it doesn’t support mouse events.
