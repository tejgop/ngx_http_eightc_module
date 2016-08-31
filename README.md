# The EightC Module

Harness the power of an esoteric language in Nginx!

## Installing

Download the module and configure:

```bash
$ ./configure --add-dynamic-module=ngx_http_eightc_module/
$ make
$ make install
```

## EightC

EightC is an esoteric language for the web. It has 1000 cells (variables) by default.
Currently, EightC only supports one-level loops.

##### Example:

Put this in your `nginx.conf`:

```
location / {
  run_eightc "++++++ [ > ++++++++++ < - ] +++++ .";
}
```

When you reload Nginx, you should get the character 'A' when you send a request.

This is a hello world:

```
location / {
    run_eightc "+++++++ [ > ++++++++++ < - ] > ++.
                < ++ [ > ++++++++++ < - ] >  +++++++++ .
                +++++++ .
                .
                +++ .
                < ++++++++ [ > ---------- < - ] > + .
                < +++++ [ > +++++++++++ < - ] > .
                < ++++ [ > ++++++ < - ] > .
                +++ .
                ------ .
                -------- .
                < ++++++++ [ > -------- < - ] > --- .";
}
```


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
`#`|Add 48 to current cell (Number to ASCII)
`&`|Subtract 48 from current cell (ASCII to number)

## Todo

- [ ] Implement multi level loops
- [x] Add `,` command
