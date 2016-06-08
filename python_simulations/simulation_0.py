from simulation_core import *

def main():
  name = "John"
  printSpeach(name, "Hey! How are you?")

  option = getOption([
    ("Good", "I'm good."),
    ("Bad", "I'm not doin' so well.")
  ])

  if option == 1:
    printSpeach(name, "Me too!")

  elif option == 2:
    printSpeach(name, "Oh I'm sorry.")

if __name__ == "__main__":
  main()