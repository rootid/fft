if exists("loaded_myscript")
  finish 
endif
let loaded_myscript=1 

function! AddEmptyLineBelow()
  call append(line("."), "")
endfunction

noremap , <C-j> :call AddEmptyLineBelow()<CR>

" vim: set sw=2 nospell :
