-- Type Classes, Instances, Polymorphism, and Common Haskell Type Classes (With Examples)

-- 1. Type Classes and Instances

-- Type classes in Haskell define a set of functions that must be implemented by any type that is an instance of that class.

-- Question 1: Extend the `Describable` type class to include a function that compares two objects and returns whether they are "similar".
class Describable a where
    describe :: a -> String
    similarTo :: a -> a -> Bool

-- Example usage for Question 1:
-- This is a declaration, instances are needed to use this type class.

-- Question 2: Create an instance of `Describable` for the `Int` type. 
-- Describe integers and check if two numbers are within 10 units of each other to define "similarity".
instance Describable Int where
    describe x = undefined
    similarTo x y = undefined

-- Example usage:
-- For example, for `describe 42`, the output should be: "The number is 42"
-- For example, for `similarTo 42 50`, the output should be: True

-- Question 3: Create an instance of `Describable` for lists, where the description is "A list of length N" and similarity is based on having the same length.
instance Describable [a] where
    describe xs = undefined
    similarTo xs ys = undefined

-- Example usage:
-- For example, for `describe [1, 2, 3]`, the output should be: "A list of length 3"
-- For example, for `similarTo [1, 2, 3] [4, 5, 6]`, the output should be: True

-- Question 4: Write a polymorphic function that uses type class constraints.
areSimilar :: (Describable a) => a -> a -> Bool
areSimilar x y = undefined

-- Example usage:
-- For example, for `areSimilar [1, 2] [3, 4]`, the output should be: True


-- 2. Common Haskell Type Classes

-- The following are some of the most commonly used type classes in Haskell:

-- **Show Type Class**

-- The `Show` type class is used for types whose values can be represented as strings.
-- It provides the `show` function, which converts a value into a string.

-- Question 5: Create a custom data type and implement the `Show` type class for it.
data Person = Person String Int  -- Name and age

instance Show Person where
    show (Person name age) = undefined

-- Example usage:
-- For example, for `show (Person "Alice" 30)`, the output should be: "Person: Alice, Age: 30"

-- **Ord Type Class**

-- The `Ord` type class is used for types whose values can be compared in terms of ordering (less than, greater than, etc.).
-- It provides functions like `(<)`, `(>)`, and `compare`.

-- Question 6: Create a custom data type and implement the `Ord` type class for it.
data Rectangle = Rectangle Int Int  -- Width and height

instance Ord Rectangle where
    compare (Rectangle w1 h1) (Rectangle w2 h2) = undefined

-- Example usage:
-- For example, for `compare (Rectangle 3 4) (Rectangle 2 6)`, the output should be: EQ (since both areas are 12)

-- **Eq Type Class**

-- The `Eq` type class is for types that support equality testing.
-- It provides the `(==)` and `(/=)` functions.

-- Question 7: Implement the `Eq` type class for the `Rectangle` data type from above.
instance Eq Rectangle where
    (Rectangle w1 h1) == (Rectangle w2 h2) = undefined

-- Example usage:
-- For example, for `(Rectangle 3 4) == (Rectangle 2 6)`, the output should be: True

-- **Enum Type Class**

-- The `Enum` type class is used for types that have predecessors and successors.
-- This includes types like `Int`, `Char`, etc.

-- Question 8: Create a custom data type representing days of the week and make it an instance of `Enum`.
data Day = Monday | Tuesday | Wednesday | Thursday | Friday | Saturday | Sunday

instance Enum Day where
    toEnum n = undefined
    fromEnum x = undefined

-- Example usage:
-- For example, for `succ Monday`, the output should be: Tuesday
-- For example, for `pred Sunday`, the output should be: Saturday

-- **Bounded Type Class**

-- The `Bounded` type class is for types that have an upper and lower bound.

-- Question 9: Make `Day` an instance of `Bounded` where the bounds are `Monday` and `Sunday`.
instance Bounded Day where
    minBound = undefined
    maxBound = undefined

-- Example usage:
-- For example, for `minBound :: Day`, the output should be: Monday
-- For example, for `maxBound :: Day`, the output should be: Sunday


-- 3. Polymorphic Data Types

-- Polymorphic data types allow you to define data types with type parameters, making them flexible for different types.

-- Question 10: Define a polymorphic data type `Pair` that can hold two values of any type.
data Pair a b = Pair a b

-- Example usage:
-- For example, for `Pair 3 "hello"`, you have a pair of an `Int` and a `String`.

-- Question 11: Define a polymorphic data type `Box` that can hold a value of any type with a label.
data Box a = Box String a  -- Label and value

-- Example usage:
-- For example, for `Box "My Number" 42`, you have a box with a label "My Number" and an `Int` value.

-- Question 12: Write a function that extracts the value from a `Box`.
getValue :: Box a -> a
getValue (Box _ value) = undefined

-- Example usage:
-- For example, for `getValue (Box "My Number" 42)`, the output should be: 42


-- 4. Polymorphism

-- Polymorphism allows you to write functions that can operate on values of any type.

-- Question 13: Write a polymorphic function that takes a list of any type and reverses it without using the `reverse` function.
reverseList :: [a] -> [a]
reverseList [] = []
reverseList (x:xs) = undefined

-- Example usage:
-- For example, for `reverseList [1, 2, 3, 4]`, the output should be: [4, 3, 2, 1]

-- Question 14: Write a polymorphic function that takes two lists and checks if their lengths are the same.
sameLength :: [a] -> [b] -> Bool
sameLength xs ys = undefined

-- Example usage:
-- For example, for `sameLength [1, 2, 3] ['a', 'b', 'c']`, the output should be: True

-- 5. Polymorphic Type Classes

-- Question 15: Create a polymorphic type class `Mergeable` with a function `merge` that can merge two values of the same type.
class Mergeable a where
    merge :: a -> a -> a


-- Question 16: Create an instance of `Mergeable` for lists, where the merge function concatenates two lists.
instance Mergeable [a] where
    merge xs ys = undefined

-- Example usage:
-- For example, for `merge [1, 2] [3, 4]`, the output should be: [1, 2, 3, 4]

-- Question 17: Create an instance of `Mergeable` for numbers, where the merge function adds two numbers.
instance Mergeable Int where
    merge x y = undefined

-- Example usage:
-- For example, for `merge 10 20`, the output should be: 30

-- Question 18: Write a polymorphic function that takes any two `Mergeable` values and merges them.
mergeValues :: (Mergeable a) => a -> a -> a
mergeValues x y = undefined

-- Example usage:
-- For example, for `mergeValues [1, 2] [3, 4]`, the output should be: [1, 2, 3, 4]
