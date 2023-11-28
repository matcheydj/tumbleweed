import os
import platform
import getpass

# Query system information
print(f"System: {platform.system()}")
print(f"Architecture: {platform.architecture()}")
print(f"User: {getpass.getuser()}")

# Allow the user to select a folder for access
print("\nPlease select an option:")
print("1. Lix")
print("2. Mac")
print("3. Win")

choice = input("\nEnter your choice (1-3): ")

if choice == '1':
    folder = '/path/to/lix/folder'
elif choice == '2':
    folder = '/path/to/mac/folder'
elif choice == '3':
    folder = '/path/to/win/folder'
else:
    print("Invalid choice.")
    exit(1)

# Display the contents of the selected folder
print(f"\nContents of {folder}:")
for filename in os.listdir(folder):
    print(filename)
