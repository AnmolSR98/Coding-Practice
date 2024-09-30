import Data.Char

-- Exploring Strings and Character Literals

{- Use the reverse function to write a function that takes a string as input and returns True if
 it is a palindrome, and False otherwise.
-}
isPalindrome :: String -> Bool
isPalindrome a = (a == reverse(a))

{- A string in Haskell is simply a list of characters, and its type is denoted as String, which
 is a type synonym for [Char]. Run the following command and observe the value.
-}
isStringCharArray :: Bool
isStringCharArray =
    "Hello" == ['H', 'e', 'l', 'l', 'o']

{- Write a function that checks whether input character is a vowel (a, e, i, o, u, A, E, I, O, U)
 using the elem function. elem takes two inputs and checks if a value is an element of a list, 
 returning True if the value is found and False otherwise.
 Reminder: A string is a list of characters!

 Note: In Haskell, you can use backticks (`) to make any function that takes exactly two arguments 
 infix. This allows you to place the function between its two arguments instead of the usual prefix
 notation where the function comes before its arguments. So the following terms would be equivalent
 elem a b
 a `elem` b
 This notation might be useful to make the code more readable as it reminds the reader of the 
 conventional math notation a ∈ b.
-}

-- could have also just done a `elem` ""aeiouAEIOU"

isVowel :: Char -> Bool
isVowel c = if ((c == 'a') || (c == 'e') || (c == 'i') || (c == 'o') || (c == 'u')
                || (c == 'A') || (c == 'E') || (c == 'I') || (c == 'O') || (c == 'U')) then True
            else False

{- Use the ord and chr conversion functions to write a function that takes a character as input.
 If the character is an uppercase letter, return the corresponding lowercase letter; otherwise, 
 return the character unchanged.
-}
-- remember to use guards [DONE]
toLowercaseIfUpper :: Char -> Char
toLowercaseIfUpper c = if ((c >= 'A') && (c <= 'Z')) then chr( ord(c) + ord('a') - ord('A'))
                    else c

{- Write a function that takes an integer n and a character, and shifts the character 
 in by n positions using the Caesar cipher technique. Assume only lowercase letters aren passed,
 and the shift should wrap around (i.e., 'z' should become 'a').
-}
-- need to fix this with a mod to ensure z loops around to a [DONE]
caesarCipher :: Int -> Char -> Char
caesarCipher n c = if ( ord(c) + n > ord('z') ) then chr( (n mod 26) + ord(c) - 26 )
                else chr( n + ord(c) )

{- Write a function that takes a string as an input and concatenates a tab (\t) at the beginning,
 surrounds the string with double quotes (\"), and appends a newline (\n) at the end. 
 Challenge yourself and try to do it with two or less concatanation operations!
-}
addSpecialChars :: String -> String
addSpecialChars str = "\t\"" ++ str ++ "\"\n"

{- Complete the following function so that it takes a function and an input and checks whether the 
 function is a self-inverse function on the given input, meaning that applying it twice on an input 
 results in the initial input value. 
 Try it on the reverse function with example strings and observe the result.

 Note: In Haskell, Eq a is a type class constraint that ensures the type a supports equality 
 comparisons, When you see Eq a => in a function signature, it means that the type a must be a 
 member of the Eq type class so you can compare values of that type for equality.
 If you omit the (Eq a) => constraint in the type signature of the function, Haskell will throw a
 compiler error when you try to use the equality operator ==, since it doesn't know whether the
 type a supports equality comparison (Try omitting it to see the error!).
-}
--isSelfInverse :: (Eq a) => (a -> a) -> a -> Bool
--isSelfInverse f a = (f (a) == f.f(a))
    {- FILL HERE -}
