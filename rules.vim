map ,s1 :%s/	//g<CR>
map ,s2 :%s/\(^\a\+\p\+\)/    \1/g<CR>
map ,s3 :%s/\(#\p\+\)/\r\1/g<CR>
map ,s4 :%s/\(^\d\+\p\+\)/\1\r#################################################################################/g

" Text formatting
"Set the line width 100
setl tw=100

"Make all matching lines = tw
"Pattern matching //a|A and format lines
argdo g/^\/\/\w\+/ normal gqq

"Pattern matching //a|A and format lines silently
silent argdo g/^\/\/\w\+/ normal gqq

"Pattern matching //a|A and format lines silently and dnt show errs
silent! argdo g/^\/\/\w\+/ normal gqq

"Use the Par to fmt lines > 100
:g/.\{100,\}/ .!par w100

"Diff betwn fdl and fdm

