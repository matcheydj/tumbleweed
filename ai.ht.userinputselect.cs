using System;
using System.IO;

class Program
{
    static void Main()
    {
        // Identify the device
        Console.WriteLine("Device Name: " + Environment.MachineName);
        
        // Query storage space
        foreach (DriveInfo drive in DriveInfo.GetDrives())
        {
            if (drive.IsReady)
            {
                Console.WriteLine("Drive: " + drive.Name);
                Console.WriteLine("  Available space: " + drive.AvailableFreeSpace);
                Console.WriteLine("  Total size: " + drive.TotalSize);
            }
        }

        // Query memory
        Console.WriteLine("Total Memory: " + Environment.WorkingSet);

        // Ask for user input to select settings
        Console.WriteLine("Please select a setting:");
        Console.WriteLine("1. I like UI");
        Console.WriteLine("2. I <3 UI");
        Console.WriteLine("3. I 8> UI");

        string input = Console.ReadLine();
        switch (input)
        {
            case "1":
                Console.WriteLine("You selected: I like UI");
                break;
            case "2":
                Console.WriteLine("You selected: I <3 UI");
                break;
            case "3":
                Console.WriteLine("You selected: I 8> UI");
                break;
            default:
                Console.WriteLine("Invalid selection");
                break;
        }
    }
}
