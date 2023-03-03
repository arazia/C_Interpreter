# An Interpreter built from the ground-up using C
A student project used to learn how an interpreter works.

Currently, the interpreter supports 7 different 'tokens':
- INTEGER (Up to 20 bytes long)
- ADD (+)
- MINUS (-)
- MULT (*)
- DIV (/)
- LPARENT ( ( )
- RPARENT ( ) )

The interpreter follows the basic order of operations:
PARENTHESIS over MULT and DIV over ADD and MINUS

To run, enter the root directory:
`make`
