# Jagged VERSION 0.11.18
**Jagged** is a scripting language that aims to be intuitive and fun for small and large projects.

# Special Behaviors
**Jagged** has many quirks that make it unique to script in.  Here is a list of just a few:

 - *Back-Parsing* - This lets you parse your code backwards using the ***^*** keyword.

 - *String Write Variables* - To call variables to write to, you reference them as a string literal. This means you can also write to variables specified by the return value of functions.
 - *Argumentless Function Calling* - Some standard library functions can be called with no arguments and exhibit special behavior.  For instance: if the _input_ function is called without any arguments it will return the inputted value without storing it in a variable.  It will also return the inputted value if there is a variable provided.

# Standard Functionality

 - *User Defined Functions and Returns* - Using the _exec("func name", "argument")_ and _return(value)_ function, users can define their own functions.
 - *Return Values For Functions* - Standard library and user defined functions can be called as arguments of other functions.  The argument parsed will be the return value of the function provided.
 - *Character Stream Based Interpreter* - The interpreter reads the code character by character, allowing for flexible formatting.
