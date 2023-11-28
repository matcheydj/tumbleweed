# Check if wget is installed
if (!(Get-Command wget -ErrorAction SilentlyContinue)) {
    Write-Host "wget could not be found. Please install wget and try again."
    exit
}

# Check if the script is running with administrator privileges
if (-NOT ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole] "Administrator")) {
    Write-Host "This script must be run as an Administrator. Please re-run this script as an Administrator."
    exit
}

# Check if Homebrew is installed
if (!(Get-Command brew -ErrorAction SilentlyContinue)) {
    Write-Host "Homebrew is not installed. Please install Homebrew and try again."
    exit
}

# Check if Wine is installed
if (!(Get-Command wine -ErrorAction SilentlyContinue)) {
    Write-Host "Wine is not installed. Please install Wine and try again."
    exit
}

# Check if tar is installed
if (!(Get-Command tar -ErrorAction SilentlyContinue)) {
    Write-Host "tar could not be found. Please install tar and try again."
    exit
}

# Download the GNU make source code
wget http://ftp.gnu.org/gnu/make/make-4.3.tar.gz -OutFile make-4.3.tar.gz

# Extract the tarball
tar -xzf make-4.3.tar.gz

# Change to the source directory
Set-Location -Path make-4.3

# Configure, build, and install
./configure
make
sudo make install

# Ask the user if they want to find PowerShell scripts
read -p "Do you want to find PowerShell scripts on your system? Answer with Y/n/N: " findScripts
if ($findScripts -eq 'Y') {
    # Find all .ps1 files in the current directory and its subdirectories
    Get-ChildItem -Path . -Filter *.ps1 -Recurse -ErrorAction SilentlyContinue | ForEach-Object {
        Write-Host $_.FullName
    }
}

# Ask the user if they want to check their system info
read -p "Do you want to check your system info? Answer with Y/n/N: " checkInfo
if ($checkInfo -eq 'Y') {
    Write-Host "System: $(uname)"
    Write-Host "Architecture: $(uname -m)"
}

# Ask the user if they want to raise privileges
read -p "Do you want to raise privileges? Answer with Y/n/N: " raisePrivileges
if ($raisePrivileges -eq 'Y') {
    # Add your code here to raise privileges
    # Allow the user to select an environment
echo -e "\nPlease select an option:"
echo "1. Linux"
echo "2. Mac (Homebrew)"
echo "3. Windows (Wine)"

read -p "Enter your choice (1-3): " choice

if ($choice -eq '1') {
    # Linux
    echo "Attempting to raise privileges on Linux..."
    sudo echo "Privileges raised."
} elseif ($choice -eq '2') {
    # Mac (Homebrew)
    echo "Attempting to raise privileges on Mac (Homebrew)..."
    sudo echo "Privileges raised."
} elseif ($choice -eq '3') {
    # Windows (Wine)
    echo "Attempting to raise privileges on Windows (Wine)..."
    Start-Process powershell -Verb runAs
} else {
    echo "Invalid choice."
}
    # echo "Something else."
}
