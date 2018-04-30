# MathInterpreter
Simple interpreter for mathematical expressions written in C++

## Declare a function

```matlab
f(x, y) = x * y + 2
```

## Declare a variable

```matlab
n = 3
```

## Undefined values

Every identifier is `undefined` by default and get's it's value from user declarations.

## Literals

```matlab
34.123, .123, 54 - number
false, true - boolean
undefined
```

## Supported operations

```
a &[&] b - and between two booleans
a |[|] b - or between two booleans
!a - negation before a boolean

a + b - addition between two numbers
a - b - subtraction between two numbers
a * b - multiplication between two numbers
a / b - division between two numbers
a % b - modulo between two numbers
a ^ b - exponentiation between two numbers
+a - unary plus before a number
-a - unary minus before a number

() - parantheses to denote precedence
f(x, y) - function call
```

## Function calls

User functions can be called with any number of parameters. Not supplied values become undefined and the excess is ignored. This can be used to implement a JavaScript like function overloading like such:

```matlab
f(x, y) = x + (y != undefined : y : 5) + 2
```

## Built in functions

The language comes with the following built in functions:

```matlab
sin(x)
cos(x)
tan(x)
asin(x)
acos(x)
atan(x)
atan2(x, y)
sqrt(x)
```
Their parameters must always be supplied, contrary to user functions, and must all be numbers.

## Built in constants

The two built in constants are `PI` and `E`.
