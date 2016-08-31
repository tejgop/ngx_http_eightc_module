# The EightC Module

Harness the power of an esoteric language in Nginx!

## EightC

EightC is an esoteric language for the web. It has 1000 cells (variables) by default.
Currently, EightC only supports one-level loops.


##### Commands:

Command|Description
-------|-----------
`+`|Add 1 to current cell
`-`|Subtract 1 from current cell
`>`|Go to next cell
`<`|Go to previous cell
`.`|Print ASCII value of current cell
`[`|If current cell equals 0, skip to corresponding `]`
`]`|If current cell is not 0, go back to corresponding `[`
`,`|Put one character of url arguments in current cell
`;`|Put one character of POST body in current cell


## Todo

- [ ] Implement multi level loops
- [ ] Add `,` command
- [ ] Add `;` command
