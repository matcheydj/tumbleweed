# I have written the same program in Python, Ruby, and Go for the Apache Maven architecture. The program creates a web page that has a background scripted element that generates and stores as a vector a random list of words, store the words in an array, and output the selections as 16 separate buttons on the webpage, each button containing at least 3 of those many words to the user. The program will make the users choose up to 5 of a total of 16 (up to 5 out of 16 choices) and put their choices in a second table array, and using vectors display them as text, generated as svg drawn as close to how the letters appear on an interactive web page. Here are the codes:
# This file is for Ruby
require 'securerandom'

# A function to generate a random word of length n
def random_word(n)
  word = "" # Initialize the word
  alphabet = "abcdefghijklmnopqrstuvwxyz" # Define the alphabet
  n.times do
    r = SecureRandom.random_number(26) # Generate a random index
    word += alphabet[r] # Append a random letter
  end
  return word # Return the word
end

# A function to generate a random list of words of size m
def random_list(m)
  list = [] # Initialize the list
  m.times do
    n = SecureRandom.random_number(10) + 1 # Generate a random word length between 1 and 10
    list << random_word(n) # Generate a random word and add it to the list
  end
  return list # Return the list
end

# A function to create a button with a label
def create_button(label)
  puts "<button onclick=\"select(this)\">#{label}</button>" # Print the HTML code for the button
end

# A function to create a text element with a content
def create_text(content)
  puts "<text x=\"50%\" y=\"50%\" text-anchor=\"middle\" alignment-baseline=\"middle\" font-size=\"32\">#{content}</text>" # Print the SVG code for the text
end

# A function to join three words with spaces
def join_words(word1, word2, word3)
  return word1 + " " + word2 + " " + word3 # Return the joined words
end

# A global variable to store the user's choices
$choices = []
$choice_count = 0

# A global variable to store the timer value
$timer = 5

# A function to handle the user's selection of a button
def select(button)
  if $choice_count < 5 # If the user has not selected 5 buttons yet
    $choices << button # Add the button's label to the choices list
    $choice_count += 1 # Increment the choice count
    button.disabled = true # Disable the button
    if $choice_count == 5 # If the user has selected 5 buttons
      start_timer() # Start the timer and display it
    end
  end
end

# A function to start the timer and display it
def start_timer()
  puts "<svg width=\"100%\" height=\"100%\" viewBox=\"0 0 100 100\">" # Print the SVG tag
  create_text($timer.to_s) # Create a text element with the timer value
  puts "<animate id=\"timer\" attributeName=\"content\" values=\"5;4;3;2;1\" keyTimes=\"0;0.2;0.4;0.6;0.8;1\" dur=\"5s\" fill=\"freeze\"/>" # Animate the text to change the timer value
  puts "<set attributeName=\"display\" to=\"none\" begin=\"timer.end+1s\"/>" # Hide the text after the timer ends and waits for 1 second
  puts "</svg>" # Print the closing SVG tag
  puts "<script>" # Print the script tag
  puts "setTimeout(function() { display_choices(); }, 6000);" # Set a timeout to display the choices after 6 seconds
  puts "</script>" # Print the closing script tag
end

# A function to display the user's choices as text
def display
