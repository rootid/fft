"command! : Overwrites command
:command! -range=% REL :<line1>,<line2>g/^\s*$/d
"To execute :'a,'b REL

"map! : Overwrites map
map ,rel :g/^\s*$/d<CR>
map ,m :%s/\/\//    /g<CR> 

noremap <silent> ,n :set number!<CR>
noremap <silent> ,p :set paste!<CR>
noremap <silent> ,l :set paste! <bar> set nu! <CR>
noremap ,c :'a,'bs/^/\/\//g<CR>

