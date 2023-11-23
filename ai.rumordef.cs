// Sure, here's a simple C# program that defines a `Rumor` class and populates a list of rumors from user input:

// ```csharp
using System;
using System.Collections.Generic;

public class Rumor
{
    public string Content { get; set; }
}

class Program
{
    static void Main(string[] args)
    {
        List<Rumor> rumors = new List<Rumor>();

        for (int i = 0; i < 5; i++)
        {
            Console.Write("Enter rumor " + (i + 1) + ": ");
            string rumorContent = Console.ReadLine();

            Rumor rumor = new Rumor { Content = rumorContent };
            rumors.Add(rumor);
        }

        Console.WriteLine("\nYou've entered the following rumors:");
        foreach (Rumor rumor in rumors)
        {
            Console.WriteLine("- " + rumor.Content);
        }
    }
}
```

// This program will prompt the user to enter the content of up to 5 rumors. Each rumor is stored as an instance of the `Rumor` class, which is then added to a list of rumors. After all rumors have been entered, the program will output the content of each rumor. Please note that this program does not validate the input. If the user enters nothing and just presses enter, an empty rumor will be added to the list. Also, the program does not check for duplicate rumors. If the user enters the same rumor more than once, it will be added to the list each time it is entered.
