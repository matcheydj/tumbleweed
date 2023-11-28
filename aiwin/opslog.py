import os
import platform
import getpass
import logging

# Set up logging
logging.basicConfig(level=logging.DEBUG)

# Query system information
logging.info(f"System: {platform.system()}")
logging.info(f"Architecture: {platform.architecture()}")
logging.info(f"User: {getpass.getuser()}")

# Allow the user to select a folder for access
print("\nPlease select an option:")
print("1. Lix")
print("2. Mac")
print("3. Win")

choices = []
while len(choices) < 3:
    choice = input("\nEnter your choice (1-3): ")

    if choice in choices:
        logging.error("You have already made this choice. Please choose a different option.")
        continue

    if choice == '1':
        folder = '/path/to/lix/folder'
    elif choice == '2':
        folder = '/path/to/mac/folder'
    elif choice == '3':
        folder = '/path/to/win/folder'
    else:
        logging.error("Invalid choice.")
        continue

    choices.append(choice)

    # Display the contents of the selected folder
    try:
        print(f"\nContents of {folder}:")
        for filename in os.listdir(folder):
            print(filename)
    except PermissionError:
        logging.error(f"Permission denied: {folder}")
    except FileNotFoundError:
        logging.error(f"No such file or directory: {folder}")
    except Exception as e:
        logging.error(f"An error occurred: {e}")
