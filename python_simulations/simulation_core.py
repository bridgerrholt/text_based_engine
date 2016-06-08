def isInt(s):
  try: 
    int(s)
    return True
  except ValueError:
    return False



def printSpeach(name, text):
  print name + ": " + text



def getOption(optionList):
  for index, option in enumerate(optionList):
    print str(index+1) + ": " + option[0]

  while True:
    inputStr = raw_input("> ")

    try:
      i = int(inputStr)
      if i >= 1 and i <= len(optionList):
        print optionList[i-1][1]
        return i

    except ValueError:
      pass

