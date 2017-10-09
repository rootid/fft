:command -range=% REL :<line1>,<line2>g/^\s*$/d
map ,rel :g/^\s*$/d<CR>

noremap <silent> ,n :set number!<CR>
noremap <silent> ,p :set paste!<CR>
noremap <silent> ,l :set paste! <bar> set nu! <CR>
