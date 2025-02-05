# string reverse function
def reverseString(inputString: str):

    reverseString = ""
    for i in range(len(inputString)):
        reverseString += inputString[len(inputString) - 1 - i]

    return reverseString

# filtering out non alphabetical characters and converting to lower case for simplicity
def filterForAlpha(inputString: str):

    filteredString = ""
    for char in inputString:
        if char.isalpha():
            filteredString += char.lower()

    return filteredString

# simple palindrome checker function
def isPalindrome(inputString: str):

    filterInput  = filterForAlpha(inputString)
    return (filterInput == reverseString(filterInput))

# checking whether a string can be a palindrome
def canBePalindrome(inputString: str):

    # converting a string to a filtered format
    filterString = filterForAlpha(inputString)

    # setting up a dictionary to handle this problem
    letterNary = {}
    for i in range(26):
        letterNary[chr(ord("a") + i)] = 0

    # counting the instances of each letter
    for char in filterString:
        letterNary[char] += 1

    # variable for the number of odd occurring letters
    numOdds = 0

    # now checking each letter, at most there can be one letter that appears an odd amount of times
    for value in letterNary.values():
        if (value % 2 == 1):
            numOdds += 1
            if (numOdds >= 2):
                return False

    # assuming 0 or 1 numOdds, then we can make a palindrome
    return True

# palindrome complexity operation 
def getPalindromeComplexityOperation():
    return 0

def main():
    print(
    canBePalindrome("civic")
    )

if __name__ == '__main__':
    main() 