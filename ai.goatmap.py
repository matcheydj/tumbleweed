import curses
import random
import requests
from geocoder import Nominatim
from requests_cache import CachedSession

# Cached API session for improved performance
session = CachedSession()

# Get maximum screen size
stdscr = curses.initscr()
sh, sw = stdscr.getmaxyx()

# Additional facts from previous version
additional_facts = [
    # Fact with reference
    "Bighorn sheep can run at speeds of up to 40 mph. [Source: [National Geographic](https://m.youtube.com/watch?v=gtTzh8_IbeI)]",
    "Bighorn sheep have a mating behavior called polygyny, meaning that one male mates with multiple females.",
    "Bighorn sheep have a reproductive season from November to December.",
    "Bighorn sheep are susceptible to health issues, especially diseases contracted from domestic livestock.",
    "Bighorn sheep are the largest wild sheep in North America.",
    "Bighorn sheep are not true goats, but belong to a separate genus called Oreamnos.",
    "Bighorn sheep have a keen sense of smell, which helps them detect predators and food sources.",
    "Bighorn sheep have a specialized digestive system that allows them to digest toxic plants that other animals cannot.",
    "Bighorn sheep are named after their large, curved horns that can weigh up to 30 pounds.",
    "Bighorn sheep are named after their mountainous habitat and their goat-like appearance.",
]

def main():
    curses.curs_set(0)
    stdscr.nodelay(1)
    stdscr.timeout(100)

    # Create new window
    w = curses.newwin(sh, sw, 0, 0)

    # Cursor coordinates
    cursor_y, cursor_x = sh // 2, sw // 2

    while True:
        # Draw cursor
        w.clear()
        w.addch(cursor_y, cursor_x, curses.ACS_DIAMOND)
        w.refresh()

        # Handle key presses
        key = stdscr.getch()

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

        # Display random fact after cursor movement
        display_random_fact(w, sh, sw)

    curses.endwin()

def get_map_data(lat, lon):
    # Fetch location details using Nominatim
    geolocator = Nominatim(user_agent="MyApplication")
    return geolocator.reverse(f"{lat},{lon}")

def display_random_fact(w, sh, sw):
    # Combine all facts from both sources
    all_facts = facts + additional_facts

    # Choose random fact
    fact = random.choice(all_facts)

    # Split fact into lines for display within window
    lines = fact.splitlines()

    # Calculate starting y-position for text
    start_y = max(0, cursor_y - len(lines) // 2)

    # Display lines within window bounds
    for i, line in enumerate(lines):
        if 0 <= start_y + i < sh:
            w.addstr(start_y + i, 0, line.ljust(sw))

def get_mountain_sheep_facts():
    # URL for Overpass API query
    url = "http://overpass-api.de/api/interpreter"

    # Query for mountain sheep and goat information
    query = """
    [out:json];
    area["name"="Europe"];
    (node"name"="Mountain Goat";
     node"name"="Mountain Sheep";
    );
    out body;
    """

    # Fetch data using cached session
    response = session.get(url, params={"data": query})
    data = response.json()

    # Extract information and return
    sheep_data = []
    for item in data["elements"]:
        # Get location details using Nominatim
        location = get_map_data(item["lat"], item["lon"]).address

        sheep_data
