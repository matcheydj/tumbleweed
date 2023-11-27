# This is a funny script about a goat named Billy and a mountain sheep named Rocky

# Fact: Goats were one of the first animals to be tamed by humans and were being herded 9,000 years ago[^1^][3]
class Goat:
    def __init__(self, name):
        self.name = name

    # Fact: Goats are very intelligent and curious animals[^2^][2][^3^][11]
    def do_something(self):
        return self.name + " is doing something interesting!"

# Fact: Mountain sheep, also known as “argali,” is a species of wild sheep that lives in Asia[^3^][11]
class MountainSheep:
    def __init__(self, name):
        self.name = name

    # Fact: Mountain sheep live in the unforgiving habitat of mountain peaks[^3^][11]
    def do_something(self):
        return self.name + " is climbing a mountain!"

# Fact: Goats are resourceful and will find nutritious food like tree bark[^4^][6]
def eat(goat):
    return goat.name + " is eating tree bark!"

# Fact: Mountain sheep are stout-bodied mammals but also one of the smallest domesticated livestock worldwide[^3^][11]
def climb(mountain_sheep):
    return mountain_sheep.name + " is climbing a mountain!"

# Create a goat named Billy
billy = Goat("Billy")
print(billy.do_something())
print(eat(billy))

# Create a mountain sheep named Rocky
rocky = MountainSheep("Rocky")
print(rocky.do_something())
print(climb(rocky))
